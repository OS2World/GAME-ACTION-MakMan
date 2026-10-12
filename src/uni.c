/*
 * uni.c -- Unicode text layer for plain PM applications (see uni.h)
 */

#include "uni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* UTF-8 helpers                                                       */
/* ------------------------------------------------------------------ */

int utf8_seqlen(unsigned char c)
{
    if (c < 0x80) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;                                  /* stray continuation byte */
}

unsigned long utf8_decode(const char *s, int n, int *used)
{
    unsigned char c = (unsigned char)s[0];
    int len = utf8_seqlen(c), k;
    unsigned long cp;

    if (n < 1) { if (used) *used = 0; return 0; }
    if (len > n) len = n;
    if (len == 1) { if (used) *used = 1; return c < 0x80 ? c : 0xFFFD; }
    cp = c & (0xFF >> (len + 1));
    for (k = 1; k < len; k++) {
        if (((unsigned char)s[k] & 0xC0) != 0x80) { if (used) *used = k; return 0xFFFD; }
        cp = (cp << 6) | ((unsigned char)s[k] & 0x3F);
    }
    if (used) *used = len;
    return cp;
}

int utf8_align(const char *s, int n, int k)
{
    int i = k;

    if (k >= n) return n;
    while (i > 0 && ((unsigned char)s[i] & 0xC0) == 0x80) i--;
    if (i == 0 && k > 0) i = utf8_seqlen((unsigned char)s[0]);
    return i > n ? n : i;
}

/* is the sequence at src[i..] well formed?  returns its length or 0 */
static int valid_seq(const unsigned char *src, long i, long len)
{
    unsigned char c = src[i];
    int l, k;
    unsigned long cp;

    if (c < 0x80) return 1;
    if (c < 0xC2 || c > 0xF4) return 0;                  /* continuation, overlong, > U+10FFFF */
    l = utf8_seqlen(c);
    if (i + l > len) return 0;
    cp = c & (0xFF >> (l + 1));
    for (k = 1; k < l; k++) {
        if ((src[i + k] & 0xC0) != 0x80) return 0;
        cp = (cp << 6) | (src[i + k] & 0x3F);
    }
    if ((l == 3 && cp < 0x800) || (l == 4 && (cp < 0x10000 || cp > 0x10FFFF))) return 0;
    if (cp >= 0xD800 && cp <= 0xDFFF) return 0;          /* surrogates are not UTF-8 */
    return l;
}

long utf8_sanitize(unsigned char *buf, long len, long *invalid, long *chars)
{
    unsigned char *out = (unsigned char *)malloc(len * 3 + 4);
    long i = 0, o = 0, inv = 0, ch = 0;

    if (!out) { if (invalid) *invalid = 0; if (chars) *chars = len; buf[len] = 0; return len; }
    while (i < len) {
        int l = valid_seq(buf, i, len);
        if (l) {
            memcpy(out + o, buf + i, l);
            o += l; i += l;
        } else {
            out[o++] = 0xEF; out[o++] = 0xBF; out[o++] = 0xBD;     /* U+FFFD */
            i++;
            inv++;
        }
        ch++;
    }
    out[o] = 0;
    memcpy(buf, out, o + 1);               /* caller provides len*3+4 bytes */
    if (invalid) *invalid = inv;
    if (chars) *chars = ch;
    free(out);
    return o;
}

/* ------------------------------------------------------------------ */
/* ULS, loaded at run time so no import library is needed              */
/* ------------------------------------------------------------------ */

typedef int (APIENTRY *PFN_CREATE)(USHORT *code_set, void **uobj);
typedef int (APIENTRY *PFN_FROMUCS)(void *uobj, USHORT **inbuf, size_t *inchars,
                                    void **outbuf, size_t *outbytes, size_t *subst);
typedef int (APIENTRY *PFN_FREE)(void *uobj);

static HMODULE     hUconv;
static PFN_CREATE  pfnCreate;
static PFN_FROMUCS pfnFromUcs;
static PFN_FREE    pfnFree;
typedef int (APIENTRY *PFN_TOUCS)(void *uobj, void **inbuf, size_t *inbytes,
                                  USHORT **outbuf, size_t *outchars, size_t *subst);
static PFN_TOUCS   pfnToUcs;
static void       *uobj;
static ULONG       ulCp = 850;

int uls_init(void)
{
    char   fail[64];
    ULONG  cp[4], cb = 0;
    USHORT name[24];
    char   tmp[24];
    int    i;

    if (uobj) return 1;                          /* already initialised */
    if (DosQueryCp(sizeof(cp), cp, &cb) == 0) ulCp = cp[0];
    if (DosLoadModule(fail, sizeof(fail), "UCONV", &hUconv) != 0) return 0;
    if (DosQueryProcAddr(hUconv, 0, "UniCreateUconvObject", (PFN *)&pfnCreate) ||
        DosQueryProcAddr(hUconv, 0, "UniUconvFromUcs", (PFN *)&pfnFromUcs) ||
        DosQueryProcAddr(hUconv, 0, "UniFreeUconvObject", (PFN *)&pfnFree)) {
        DosFreeModule(hUconv); hUconv = 0;
        return 0;
    }
    DosQueryProcAddr(hUconv, 0, "UniUconvToUcs", (PFN *)&pfnToUcs);   /* optional */
    sprintf(tmp, "IBM-%lu", (unsigned long)ulCp);
    for (i = 0; tmp[i]; i++) name[i] = (USHORT)tmp[i];
    name[i] = 0;
    if (pfnCreate(name, &uobj) != 0) {
        DosFreeModule(hUconv); hUconv = 0; uobj = NULL;
        return 0;
    }
    return 1;
}

ULONG uls_codepage(void) { return ulCp; }

int uls_to_cp(const char *s, int n, char *out, int outmax)
{
    int i = 0, o = 0;

    while (i < n && o < outmax - 1) {
        int used = 1;
        unsigned long cp = utf8_decode(s + i, n - i, &used);
        i += used > 0 ? used : 1;
        if (cp < 0x80) {                   /* ASCII needs no table */
            out[o++] = (char)cp;
        } else if (uobj && cp <= 0xFFFF) {
            USHORT  in[2];
            USHORT *pin = in;
            char    buf[8];
            void   *pout = buf;
            size_t  inchars = 1, outbytes = sizeof(buf), subst = 0;
            int     rc;

            in[0] = (USHORT)cp; in[1] = 0;
            rc = pfnFromUcs(uobj, &pin, &inchars, &pout, &outbytes, &subst);
            if (rc == 0 && subst == 0 && sizeof(buf) - outbytes > 0 &&
                o + (int)(sizeof(buf) - outbytes) < outmax) {
                int k, cnt = (int)(sizeof(buf) - outbytes);
                for (k = 0; k < cnt; k++) out[o++] = buf[k];
            } else {
                out[o++] = '?';
            }
        } else {
            out[o++] = '?';
        }
    }
    out[o] = 0;
    return o;
}


/* UCS-2 character -> UTF-8 (BMP only), returns bytes written */
static int put_utf8(unsigned c, char *out)
{
    if (c < 0x80)  { out[0] = (char)c; return 1; }
    if (c < 0x800) { out[0] = (char)(0xC0 | (c >> 6)); out[1] = (char)(0x80 | (c & 0x3F)); return 2; }
    out[0] = (char)(0xE0 | (c >> 12)); out[1] = (char)(0x80 | ((c >> 6) & 0x3F)); out[2] = (char)(0x80 | (c & 0x3F));
    return 3;
}

int uls_from_cp(const char *in, char *out, int outmax)
{
    USHORT w[300];
    int n = 0, i, o = 0;

    if (outmax < 1) return 0;
    if (uobj && pfnToUcs) {
        void   *pin = (void *)in;
        USHORT *pout = w;
        size_t  inbytes = strlen(in), outchars = 299, subst = 0;

        if (pfnToUcs(uobj, &pin, &inbytes, &pout, &outchars, &subst) == 0) n = (int)(pout - w);
        else n = -1;
    } else n = -1;
    if (n < 0) {                                           /* Latin-1 fallback */
        for (n = 0; in[n] && n < 299; n++) w[n] = (unsigned char)in[n];
    }
    for (i = 0; i < n; i++) {
        char b[4];
        int k = put_utf8(w[i], b);
        if (o + k >= outmax) break;
        memcpy(out + o, b, k);
        o += k;
    }
    out[o] = 0;
    return o;
}

int uls_representable(const char *s, int n)
{
    int i = 0;

    while (i < n) {
        int used = 1;
        unsigned long cp = utf8_decode(s + i, n - i, &used);
        char b[16];
        int k;

        i += used > 0 ? used : 1;
        if (cp < 0x80) continue;
        k = uls_to_cp(s + i - used, used, b, sizeof(b));
        if (k == 0 || (k == 1 && b[0] == '?')) return 0;
    }
    return 1;
}

/* ------------------------------------------------------------------ */
/* fonts and drawing                                                   */
/* ------------------------------------------------------------------ */

int uni_begin(HPS hps, const char *face, int pels, ULONG *oldcp)
{
    FATTRS fat;
    SIZEF  sz;
    LONG   rc;

    *oldcp = GpiQueryCp(hps);
    memset(&fat, 0, sizeof(fat));
    fat.usRecordLength = sizeof(FATTRS);
    strncpy(fat.szFacename, face, FACESIZE - 1);
    fat.usCodePage = (USHORT)UNI_CP;     /* UTF-8: the font decides how GPI reads the bytes */
    fat.fsFontUse  = FATTR_FONTUSE_OUTLINE | FATTR_FONTUSE_TRANSFORMABLE;
    GpiDeleteSetId(hps, UNI_LCID);
    rc = GpiCreateLogFont(hps, NULL, UNI_LCID, &fat);
    if (rc != FONT_MATCH) return 0;
    GpiSetCharSet(hps, UNI_LCID);
    sz.cx = MAKEFIXED(pels, 0);
    sz.cy = MAKEFIXED(pels, 0);
    GpiSetCharBox(hps, &sz);
    GpiSetCp(hps, UNI_CP);
    return 1;
}

void uni_end(HPS hps, ULONG oldcp)
{
    if (oldcp) GpiSetCp(hps, oldcp);
    GpiSetCharSet(hps, LCID_DEFAULT);
    GpiDeleteSetId(hps, UNI_LCID);
}

#define CHUNK 200            /* bytes per GPI call, stays below 512; never cuts a character */

int uni_width(HPS hps, const char *s, int n)
{
    POINTL pt[TXTBOX_COUNT];
    int total = 0;

    while (n > 0) {
        int c = utf8_align(s, n, n > CHUNK ? CHUNK : n);
        if (GpiQueryTextBox(hps, (LONG)c, (PCH)s, TXTBOX_COUNT, pt))
            total += (int)(pt[TXTBOX_CONCAT].x - pt[TXTBOX_BOTTOMLEFT].x);
        s += c; n -= c;
    }
    return total;
}

int uni_height(HPS hps)
{
    FONTMETRICS fm;
    SIZEF sz;
    int h = 0;

    if (GpiQueryFontMetrics(hps, sizeof(fm), &fm)) h = (int)fm.lMaxBaselineExt;
    if (GpiQueryCharBox(hps, &sz)) {
        int box = (int)(sz.cy >> 16);
        if (h < box) h = box + box / 4;      /* metrics not scaled: estimate */
    }
    return h;
}

int uni_descender(HPS hps)
{
    FONTMETRICS fm;
    if (GpiQueryFontMetrics(hps, sizeof(fm), &fm)) return (int)fm.lMaxDescender;
    return 0;
}

void uni_draw(HPS hps, long x, long y, const char *s, int n)
{
    POINTL pt;

    pt.x = x; pt.y = y;
    while (n > 0) {
        int c = utf8_align(s, n, n > CHUNK ? CHUNK : n);
        GpiCharStringAt(hps, &pt, (LONG)c, (PCH)s);
        s += c; n -= c;
        if (n > 0) pt.x = x + uni_width(hps, s - c, c);    /* next piece */
    }
}

const char *uni_ascii(const char *s, int *n)
{
    if (n) *n = (int)strlen(s);
    return s;
}

/* ------------------------------------------------------------------ */
/* glyph coverage test: render into a memory bitmap and compare with   */
/* what the face draws for the unassigned code U+0378                  */
/* ------------------------------------------------------------------ */

#define COV 56

static HAB     hab;
static HDC     hdcMem;
static HPS     hpsMem;
static HBITMAP hbmMem;

static int cov_setup(void)
{
    SIZEL sizl;
    LONG  fmt[2];
    BITMAPINFOHEADER2 bmih;

    if (hpsMem) return 1;
    hab = WinQueryAnchorBlock(HWND_DESKTOP);
    sizl.cx = COV; sizl.cy = COV;
    hdcMem = DevOpenDC(hab, OD_MEMORY, "*", 0L, NULL, NULLHANDLE);
    if (!hdcMem) return 0;
    hpsMem = GpiCreatePS(hab, hdcMem, &sizl, PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC);
    if (!hpsMem) return 0;
    if (!GpiQueryDeviceBitmapFormats(hpsMem, 2L, fmt)) { fmt[0] = 1; fmt[1] = 8; }
    memset(&bmih, 0, sizeof(bmih));
    bmih.cbFix = sizeof(BITMAPINFOHEADER2);
    bmih.cx = COV; bmih.cy = COV;
    bmih.cPlanes = (USHORT)fmt[0]; bmih.cBitCount = (USHORT)fmt[1];
    hbmMem = GpiCreateBitmap(hpsMem, &bmih, 0L, NULL, NULL);
    if (!hbmMem || GpiSetBitmap(hpsMem, hbmMem) == HBM_ERROR) return 0;
    return 1;
}

static long cov_render(const char *ch, int len, unsigned long *hash)
{
    POINTL pt, p;
    RECTL  rcl;
    long   x, y, cnt = 0, bg;
    unsigned long h = 5381;

    rcl.xLeft = 0; rcl.yBottom = 0; rcl.xRight = COV; rcl.yTop = COV;
    WinFillRect(hpsMem, &rcl, CLR_WHITE);
    p.x = 0; p.y = 0;
    bg = GpiQueryPel(hpsMem, &p);
    GpiSetColor(hpsMem, CLR_BLACK);
    pt.x = 4; pt.y = 12;
    GpiCharStringAt(hpsMem, &pt, (LONG)len, (PCH)ch);
    for (y = 0; y < COV; y++)
        for (x = 0; x < COV; x++) {
            p.x = x; p.y = y;
            if (GpiQueryPel(hpsMem, &p) != bg) {
                cnt++;
                h = h * 33 + (unsigned long)(x * 131 + y);
            }
        }
    *hash = h;
    return cnt;
}

int uni_covers(const char *face, const char *s, int n)
{
    ULONG oldcp;
    unsigned long hNone, h;
    long pNone, p;
    int i = 0, checked = 0, ok = 1;
    static const char none[] = "\xCD\xB8";       /* U+0378, unassigned */

    if (!cov_setup()) return 1;                  /* cannot test: assume yes */
    if (!uni_begin(hpsMem, face, 28, &oldcp)) { uni_end(hpsMem, oldcp); return 0; }
    pNone = cov_render(none, 2, &hNone);
    while (i < n && checked < 6) {
        int used = utf8_seqlen((unsigned char)s[i]);
        if (i + used > n) used = n - i;
        if ((unsigned char)s[i] < 0x80) { i += used; continue; }   /* Latin is always there */
        checked++;
        p = cov_render(s + i, used, &h);
        if (p == 0 || (p == pNone && h == hNone)) { ok = 0; break; }
        i += used;
    }
    uni_end(hpsMem, oldcp);
    return ok;
}

void uni_done(void)
{
    if (hpsMem) {
        GpiSetBitmap(hpsMem, NULLHANDLE);
        if (hbmMem) GpiDeleteBitmap(hbmMem);
        GpiDestroyPS(hpsMem);
        DevCloseDC(hdcMem);
        hpsMem = NULLHANDLE; hbmMem = NULLHANDLE; hdcMem = NULLHANDLE;
    }
    if (uobj)  { pfnFree(uobj); uobj = NULL; }
    if (hUconv) { DosFreeModule(hUconv); hUconv = 0; }
}
