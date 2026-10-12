/*
 * ulang.h -- UTF-8 language files (lang\*.txt) loaded at run time
 *
 * File format (UTF-8, optional BOM, LF or CRLF):
 *     # comment
 *     KEY=value            \n = line break, \ = backslash
 * Reserved keys: LANG_NAME (native name), LANG_ENGLISH (ASCII name),
 * FONT (comma separated preferred faces).  All other keys are texts.
 */

#ifndef ULANG_H
#define ULANG_H

#include "uni.h"

#ifdef __cplusplus
extern "C" {

#endif

#define MAX_LANGS 32            /* menu ids IDM_LANG_EN .. +31 */

typedef struct {
    char    *key;                 /* ASCII, upper case */
    char    *val;                 /* UTF-8, zero terminated */
    int      n;                   /* bytes in val */
} LENTRY;

typedef struct {
    char     code[24];            /* file name without extension */
    char     path[CCHMAXPATH];
    LENTRY  *e;
    int      ne;
    char     english[64];         /* LANG_ENGLISH (ASCII) */
    char     fonts[256];          /* FONT, as in the file */
    const char *name;             /* LANG_NAME, native script (UTF-8) */
    int      nameLen;             /* bytes */
    long     bytes, chars, invalid;
} LANG;

/* Finds dir\*.txt (dir ends with a backslash), loads them, sorted by
 * code.  Returns the number of languages. */
int  lang_scan(const char *dir, LANG *arr, int max);
void lang_free(LANG *arr, int count);

/* Text of a key in one language, or NULL when absent. */
const char *lang_get(const LANG *l, const char *key, int *n);     /* *n = bytes */

#ifdef __cplusplus
}
#endif

#endif
