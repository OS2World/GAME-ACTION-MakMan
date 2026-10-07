// owrt_stubs.cpp -- self-contained C runtime + C++ stubs for MakMan/2
//
// OW compiles calls to malloc() as references to "malloc_" (trailing
// underscore via OW stdlib.h #pragma aux).  No OW runtime libs are
// installed on this ArcaOS system, so this file provides everything
// needed: memory, file I/O, strings, time/random, printf, C++ runtime.
// All implemented with OS/2 DosXxx APIs (from os2386.lib, already linked).

#define INCL_DOSPROCESS
#define INCL_DOSMEMMGR
#define INCL_DOSFILEMGR
#define INCL_DOSDATETIME
#define INCL_ERRORS
#include <os2.h>
#include <stdarg.h>

#ifndef OPEN_FLAGS_NO_INHERIT
#define OPEN_FLAGS_NO_INHERIT 0x0080
#endif
#ifndef NO_ERROR
#define NO_ERROR 0
#endif

// ====================================================================
// Section 1: Memory  (malloc_ / free_)
// Bridge exports the trailing-underscore name via #pragma aux.
// ====================================================================

extern "C" void* brg_malloc_(unsigned sz);
#pragma aux brg_malloc_ "malloc_"
extern "C" void* brg_malloc_(unsigned sz) {
    PVOID p = NULL;
    DosAllocMem(&p, sz ? sz : 1, PAG_COMMIT | PAG_READ | PAG_WRITE);
    return p;
}

extern "C" void brg_free_(void* p);
#pragma aux brg_free_ "free_"
extern "C" void brg_free_(void* p) {
    if (p) DosFreeMem(p);
}

// ====================================================================
// Section 2: File I/O  (fopen_ / fclose_ / fread_ / fflush_)
// FILE* is really a pointer to this tiny struct.
// ====================================================================

struct MY_FILE {
    HFILE hf;
    int   eof;
};

extern "C" void* brg_fopen_(const char* path, const char* mode);
#pragma aux brg_fopen_ "fopen_"
extern "C" void* brg_fopen_(const char* path, const char* mode) {
    ULONG action = 0;
    ULONG openFlags  = OPEN_ACTION_FAIL_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS;
    ULONG openMode   = OPEN_FLAGS_NO_INHERIT | OPEN_ACCESS_READONLY | OPEN_SHARE_DENYWRITE;
    // write mode
    if (mode && (mode[0] == 'w' || mode[0] == 'a')) {
        openFlags = OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS;
        openMode  = OPEN_FLAGS_NO_INHERIT | OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE;
    }
    HFILE hf = NULLHANDLE;
    APIRET rc = DosOpen((PSZ)path, &hf, &action, 0, FILE_NORMAL,
                        openFlags, openMode, NULL);
    if (rc != NO_ERROR) return NULL;
    MY_FILE* mf = (MY_FILE*)brg_malloc_(sizeof(MY_FILE));
    if (!mf) { DosClose(hf); return NULL; }
    mf->hf  = hf;
    mf->eof = 0;
    return mf;
}

extern "C" int brg_fclose_(void* fp);
#pragma aux brg_fclose_ "fclose_"
extern "C" int brg_fclose_(void* fp) {
    if (!fp) return -1;
    MY_FILE* mf = (MY_FILE*)fp;
    DosClose(mf->hf);
    brg_free_(mf);
    return 0;
}

extern "C" unsigned brg_fread_(void* buf, unsigned sz, unsigned count, void* fp);
#pragma aux brg_fread_ "fread_"
extern "C" unsigned brg_fread_(void* buf, unsigned sz, unsigned count, void* fp) {
    if (!fp || !buf || !sz || !count) return 0;
    MY_FILE* mf = (MY_FILE*)fp;
    ULONG total = (ULONG)sz * (ULONG)count;
    ULONG actual = 0;
    APIRET rc = DosRead(mf->hf, buf, total, &actual);
    if (rc != NO_ERROR || actual == 0) { mf->eof = 1; return 0; }
    if (actual < total) mf->eof = 1;
    return (unsigned)(actual / sz);
}

extern "C" int brg_fflush_(void* fp);
#pragma aux brg_fflush_ "fflush_"
extern "C" int brg_fflush_(void* fp) {
    // write-mode flush not needed (game only reads files)
    (void)fp;
    return 0;
}

// ====================================================================
// Section 3: String functions  (strcmp_ / strlwr_)
// ====================================================================

extern "C" int brg_strcmp_(const char* a, const char* b);
#pragma aux brg_strcmp_ "strcmp_"
extern "C" int brg_strcmp_(const char* a, const char* b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return  1;
    while (*a && *b && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

extern "C" char* brg_strlwr_(char* s);
#pragma aux brg_strlwr_ "strlwr_"
extern "C" char* brg_strlwr_(char* s) {
    if (!s) return s;
    for (char* p = s; *p; p++)
        if (*p >= 'A' && *p <= 'Z') *p += 32;
    return s;
}

// ====================================================================
// Section 4: Time and random  (time_ / rand_ / srand_)
// ====================================================================

static unsigned long s_rand_seed = 1;

extern "C" long brg_time_(long* t);
#pragma aux brg_time_ "time_"
extern "C" long brg_time_(long* t) {
    // Approximate UNIX timestamp from DosGetDateTime (good enough for seeding)
    DATETIME dt = {0};
    DosGetDateTime(&dt);
    // rough seconds: days-since-1970 * 86400 + hms
    // years 1970..2099: leap-year estimate
    int y = dt.year - 1970;
    long days = (long)y * 365L + (long)(y / 4);
    static const int mdays[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    days += mdays[dt.month > 0 ? dt.month - 1 : 0];
    if (dt.month > 2 && (dt.year % 4) == 0) days++;
    days += dt.day - 1;
    long secs = days * 86400L + (long)dt.hours * 3600L +
                (long)dt.minutes * 60L + (long)dt.seconds;
    if (t) *t = secs;
    return secs;
}

extern "C" void brg_srand_(unsigned seed);
#pragma aux brg_srand_ "srand_"
extern "C" void brg_srand_(unsigned seed) {
    s_rand_seed = (unsigned long)seed;
}

extern "C" int brg_rand_(void);
#pragma aux brg_rand_ "rand_"
extern "C" int brg_rand_(void) {
    s_rand_seed = s_rand_seed * 1103515245UL + 12345UL;
    return (int)((s_rand_seed >> 16) & 0x7FFF);
}

// ====================================================================
// Section 5: Formatted output  (sprintf_ / fprintf_)
// Minimal implementation: %d %i %u %x %X %s %c %% with width/flags.
// ====================================================================

static void uitoa_base(char* out, unsigned long v, int base, int upper) {
    static const char lo[] = "0123456789abcdef";
    static const char up[] = "0123456789ABCDEF";
    const char* d = upper ? up : lo;
    char tmp[32];
    int n = 0;
    if (!v) { tmp[n++] = '0'; }
    else    { while (v) { tmp[n++] = d[v % base]; v /= (unsigned)base; } }
    for (int i = 0; i < n; i++) out[i] = tmp[n - 1 - i];
    out[n] = '\0';
}

static int my_strlen(const char* s) {
    int n = 0; while (s[n]) n++; return n;
}

static int my_vsprintf(char* buf, const char* fmt, va_list ap) {
    char* out = buf;
    for (; *fmt; fmt++) {
        if (*fmt != '%') { *out++ = *fmt; continue; }
        fmt++;
        // flags
        int left = 0, zero_pad = 0, lng = 0;
        if (*fmt == '-') { left = 1; fmt++; }
        if (*fmt == '0') { zero_pad = 1; fmt++; }
        // width
        int width = 0;
        while (*fmt >= '0' && *fmt <= '9') { width = width*10 + (*fmt-'0'); fmt++; }
        if (*fmt == 'l') { lng = 1; fmt++; }

        char tmp[64];
        const char* s = NULL;
        int neg = 0;

        switch (*fmt) {
        case 'd': case 'i': {
            long v = lng ? va_arg(ap, long) : (long)va_arg(ap, int);
            if (v < 0) { neg = 1; v = -v; }
            uitoa_base(tmp + (neg ? 1 : 0), (unsigned long)v, 10, 0);
            if (neg) tmp[0] = '-';
            s = tmp;
            break; }
        case 'u': {
            unsigned long v = lng ? va_arg(ap, unsigned long) : (unsigned long)va_arg(ap, unsigned);
            uitoa_base(tmp, v, 10, 0); s = tmp; break; }
        case 'x': {
            unsigned long v = lng ? va_arg(ap, unsigned long) : (unsigned long)va_arg(ap, unsigned);
            uitoa_base(tmp, v, 16, 0); s = tmp; break; }
        case 'X': {
            unsigned long v = lng ? va_arg(ap, unsigned long) : (unsigned long)va_arg(ap, unsigned);
            uitoa_base(tmp, v, 16, 1); s = tmp; break; }
        case 's':
            s = va_arg(ap, const char*);
            if (!s) s = "(null)";
            break;
        case 'c':
            tmp[0] = (char)va_arg(ap, int); tmp[1] = '\0'; s = tmp; break;
        case '%':
            *out++ = '%'; continue;
        default:
            *out++ = '%'; *out++ = *fmt; continue;
        }

        int len = my_strlen(s);
        int pad = (width > len) ? (width - len) : 0;
        if (!left && pad) {
            char pc = (zero_pad && *fmt != 's') ? '0' : ' ';
            for (int i = 0; i < pad; i++) *out++ = pc;
        }
        for (int i = 0; i < len; i++) *out++ = s[i];
        if (left && pad) for (int i = 0; i < pad; i++) *out++ = ' ';
    }
    *out = '\0';
    return (int)(out - buf);
}

extern "C" int brg_sprintf_(char* buf, const char* fmt, ...);
#pragma aux brg_sprintf_ "sprintf_"
extern "C" int brg_sprintf_(char* buf, const char* fmt, ...) {
    va_list ap; va_start(ap, fmt);
    int r = my_vsprintf(buf, fmt, ap);
    va_end(ap);
    return r;
}

extern "C" int brg_fprintf_(void* fp, const char* fmt, ...);
#pragma aux brg_fprintf_ "fprintf_"
extern "C" int brg_fprintf_(void* fp, const char* fmt, ...) {
    // debug output removed; this is a no-op
    (void)fp; (void)fmt;
    return 0;
}

// ====================================================================
// Section 6: operator new / delete  (via DosAllocMem)
// ====================================================================

void* operator new(unsigned sz) {
    PVOID p = NULL;
    DosAllocMem(&p, sz ? sz : 1, PAG_COMMIT | PAG_READ | PAG_WRITE);
    return p;
}
void operator delete(void* p) { if (p) DosFreeMem(p); }
void* operator new[](unsigned sz) {
    PVOID p = NULL;
    DosAllocMem(&p, sz ? sz : 1, PAG_COMMIT | PAG_READ | PAG_WRITE);
    return p;
}
void operator delete[](void* p) { if (p) DosFreeMem(p); }

// ====================================================================
// Section 7: C++ runtime stubs  (exact OBJ names via #pragma aux)
// ====================================================================

extern "C" void wcpp_pure_error_(void);
#pragma aux wcpp_pure_error_ "__wcpp_4_pure_error__"
extern "C" void wcpp_pure_error_(void) { DosExit(EXIT_PROCESS, 255); }

extern "C" void wcpp_undefed_cdtor_(void);
#pragma aux wcpp_undefed_cdtor_ "__wcpp_4_undefed_cdtor__"
extern "C" void wcpp_undefed_cdtor_(void) {}

extern "C" void* wcpp_ctor_arr_(void* mem, unsigned count, unsigned elem_size,
                                 void* (*ctor)(void*, char), void* (*dtor)(void*, char));
#pragma aux wcpp_ctor_arr_ "__wcpp_4_ctor_array_storage_gs__"
extern "C" void* wcpp_ctor_arr_(void* mem, unsigned count, unsigned elem_size,
                                 void* (*ctor)(void*, char), void* (*dtor)(void*, char)) {
    char* p = (char*)mem;
    for (unsigned i = 0; i < count; i++) ctor(p + i * elem_size, 1);
    (void)dtor;
    return mem;
}

extern "C" void wcpp_dtor_arr_(void* arr, unsigned count, unsigned elem_size,
                                void* (*dtor)(void*, char));
#pragma aux wcpp_dtor_arr_ "__wcpp_4_dtor_array_store__"
extern "C" void wcpp_dtor_arr_(void* arr, unsigned count, unsigned elem_size,
                                void* (*dtor)(void*, char)) {
    if (!count || !dtor) return;
    char* p = (char*)arr + (count - 1) * elem_size;
    for (unsigned i = 0; i < count; i++, p -= elem_size) dtor(p, 2);
}

extern "C" void wcpp_data_init_(void);
#pragma aux wcpp_data_init_ "___wcpp_4_data_init_fs_root_"
extern "C" void wcpp_data_init_(void) {}

// ====================================================================
// Section 8: Startup
// ====================================================================

extern int MakManMain(int, char**);

/* OW watcall convention appends a trailing underscore to all symbols, so
   extern "C" _cstart_ would be emitted as _cstart__ (double trailing).
   wlink's default entry point is _cstart_ (single trailing underscore).
   #pragma aux forces the exact symbol name, bypassing watcall mangling. */
extern "C" void owrt_cstart_(void);
#pragma aux owrt_cstart_ "_cstart_"
extern "C" void owrt_cstart_(void) {
    MakManMain(0, NULL);
    DosExit(EXIT_PROCESS, 0);
}
