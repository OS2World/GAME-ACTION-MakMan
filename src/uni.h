/*
 * uni.h -- Unicode text layer for plain PM applications
 *
 * Strings are kept as UTF-8 (code page 1208), exactly as they come from the
 * language files.  GPI draws them directly: the logical font is created with
 * usCodePage = 1208 and GpiSetCp(hps, 1208), and the length arguments are in
 * BYTES.  No conversion to UCS-2 is needed for drawing.  Everything PM cannot
 * display natively (menus, title bar) goes through ULS conversion into the
 * process code page or through owner drawing.
 *
 * Findings from probe\probe.c and probe\probe1208.c on ArcaOS 5.1
 * (documented in README.md):
 *   - a font created with code page 1208 draws UTF-8 text identically to the
 *     same text as UCS-2 in code page 1200 (the font's code page decides,
 *     GpiSetCp on a font created for 1200 does not work)
 *   - "Droid Sans Combined", "Times New Roman MT 30" and the WT J fonts
 *     contain Kana, Kanji/Hanzi and Hangul glyphs
 */

#ifndef UNI_H
#define UNI_H

#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UNI_CP 1208L          /* UTF-8 */

/* ---- UTF-8 helpers ------------------------------------------------ */

/* Replaces malformed sequences in buf (len bytes, room for len*3+4 bytes) by
 * U+FFFD (EF BF BD).  *invalid counts them, *chars the code points.  Returns
 * the new length; the buffer is zero terminated. */
long utf8_sanitize(unsigned char *buf, long len, long *invalid, long *chars);

int  utf8_seqlen(unsigned char lead);                 /* bytes of the sequence (1..4) */
/* Decodes one code point at s (n bytes left); *used gets the sequence length. */
unsigned long utf8_decode(const char *s, int n, int *used);
/* Largest k2 <= k that does not cut a sequence inside (k2 == n is allowed);
 * at least one character when k > 0. */
int  utf8_align(const char *s, int n, int k);

/* ---- ULS (UCONV.DLL), loaded at run time ------------------------- */

int  uls_init(void);          /* 1 = ULS available, 0 = ASCII fallback */
/* UTF-8 -> current process code page; unmappable characters become '?' */
int  uls_to_cp(const char *utf8, int n, char *out, int outmax);
/* process code page -> UTF-8 (bytes written, 0 terminated; never cuts a character) */
int  uls_from_cp(const char *in, char *out, int outmax);
/* 1 when every character of s exists in the process code page (needs no owner drawing) */
int  uls_representable(const char *utf8, int n);
ULONG uls_codepage(void);

/* ---- fonts and drawing ------------------------------------------ */

#define UNI_LCID 7L           /* local character set id used for text */

/* Select face at pels (device pels) for code page 1208 into hps.
 * Returns 1 when the face exists (FONT_MATCH).  Always pair with
 * uni_end(). */
int  uni_begin(HPS hps, const char *face, int pels, ULONG *oldcp);
void uni_end(HPS hps, ULONG oldcp);

/* n is the length in BYTES of the UTF-8 string s */
int  uni_width(HPS hps, const char *s, int n);
int  uni_height(HPS hps);                       /* line height in pels */
int  uni_descender(HPS hps);
void uni_draw(HPS hps, long x, long y, const char *s, int n);

/* Does this face draw a visible glyph for every character of s? */
int  uni_covers(const char *face, const char *s, int n);

/* Frees the ULS object and the coverage-test bitmap. */
void uni_done(void);

/* ASCII is valid UTF-8: returns s and its length. */
const char *uni_ascii(const char *s, int *n);

#ifdef __cplusplus
}
#endif

#endif
