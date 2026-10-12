/*
 * lang.c -- UTF-8 language files, see lang.h
 */

#include "ulang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void add_entry(LANG *l, const char *key, int klen, const unsigned char *val, long vlen)
{
    unsigned char *tmp;
    long i, o = 0, inv = 0, n;
    LENTRY *ne;
    char *k;

    tmp = (unsigned char *)malloc(vlen * 3 + 4);       /* room for utf8_sanitize */
    if (!tmp) return;
    for (i = 0; i < vlen; i++) {                 /* \n and \ escapes */
        if (val[i] == '\\' && i + 1 < vlen && val[i + 1] == 'n')  { tmp[o++] = '\n'; i++; }
        else if (val[i] == '\\' && i + 1 < vlen && val[i + 1] == '\\') { tmp[o++] = '\\'; i++; }
        else if (val[i] == '\\' && i + 1 < vlen && val[i + 1] == 't')  { tmp[o++] = '\t'; i++; }
        else tmp[o++] = val[i];
    }
    tmp[o] = 0;
    {
        long ch = 0;
        n = utf8_sanitize(tmp, o, &inv, &ch);          /* the text stays UTF-8 */
        l->chars += ch;
    }
    l->invalid += inv;

    ne = (LENTRY *)realloc(l->e, (l->ne + 1) * sizeof(LENTRY));
    if (!ne) { free(tmp); return; }
    l->e = ne;
    k = (char *)malloc(klen + 1);
    for (i = 0; i < klen; i++) k[i] = (char)((key[i] >= 'a' && key[i] <= 'z') ? key[i] - 32 : key[i]);
    k[klen] = 0;
    l->e[l->ne].key = k;
    l->e[l->ne].val = (char *)tmp;
    l->e[l->ne].n = (int)n;
    l->ne++;
}

static int load_one(LANG *l)
{
    FILE *f;
    long size, pos = 0;
    unsigned char *buf;
    int i;

    f = fopen(l->path, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = (unsigned char *)malloc(size + 1);
    if (!buf) { fclose(f); return 0; }
    size = (long)fread(buf, 1, size, f);
    fclose(f);
    l->bytes = size;
    if (size >= 3 && buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF) pos = 3;   /* BOM */

    while (pos < size) {
        long ls = pos, le;
        const unsigned char *eq = NULL;
        long j;

        while (pos < size && buf[pos] != '\n') pos++;
        le = pos;
        if (pos < size) pos++;
        while (le > ls && buf[le - 1] == '\r') le--;
        if (le <= ls || buf[ls] == '#') continue;
        for (j = ls; j < le; j++) if (buf[j] == '=') { eq = buf + j; break; }
        if (!eq) continue;
        add_entry(l, (const char *)(buf + ls), (int)(eq - (buf + ls)), eq + 1, le - (eq + 1 - buf));
    }
    free(buf);

    l->english[0] = 0; l->fonts[0] = 0; l->name = NULL; l->nameLen = 0;
    for (i = 0; i < l->ne; i++) {
        if (!strcmp(l->e[i].key, "LANG_NAME")) { l->name = l->e[i].val; l->nameLen = l->e[i].n; }
        else if (!strcmp(l->e[i].key, "LANG_ENGLISH")) {
            int k;
            for (k = 0; k < l->e[i].n && k < 63; k++) l->english[k] = (char)l->e[i].val[k];
            l->english[k] = 0;
        } else if (!strcmp(l->e[i].key, "FONT")) {
            int k;
            for (k = 0; k < l->e[i].n && k < 255; k++) l->fonts[k] = (char)l->e[i].val[k];
            l->fonts[k] = 0;
        }
    }
    if (!l->english[0]) strcpy(l->english, l->code);
    return 1;
}

int lang_scan(const char *dir, LANG *arr, int max)
{
    HDIR hdir = HDIR_CREATE;
    FILEFINDBUF3 ffb;
    ULONG cnt = 1;
    char pat[CCHMAXPATH];
    int n = 0, i, j;

    strcpy(pat, dir);
    strcat(pat, "*.txt");
    if (DosFindFirst(pat, &hdir, FILE_NORMAL, &ffb, sizeof(ffb), &cnt, FIL_STANDARD) == 0) {
        do {
            if (n < max) {
                char *dot;
                memset(&arr[n], 0, sizeof(LANG));
                {
                    int k;
                    for (k = 0; ffb.achName[k] && k < (int)sizeof(arr[n].code) - 1; k++)
                        arr[n].code[k] = ffb.achName[k];
                }
                dot = strrchr(arr[n].code, '.');
                if (dot) *dot = 0;
                strcpy(arr[n].path, dir);
                strcat(arr[n].path, ffb.achName);
                if (load_one(&arr[n])) n++;
                else lang_free(&arr[n], 1);
            }
            cnt = 1;
        } while (DosFindNext(hdir, &ffb, sizeof(ffb), &cnt) == 0);
        DosFindClose(hdir);
    }
    for (i = 1; i < n; i++) {                    /* sort by code */
        LANG t = arr[i];
        for (j = i - 1; j >= 0 && stricmp(arr[j].code, t.code) > 0; j--) arr[j + 1] = arr[j];
        arr[j + 1] = t;
    }
    return n;
}

void lang_free(LANG *arr, int count)
{
    int i, k;
    for (i = 0; i < count; i++) {
        for (k = 0; k < arr[i].ne; k++) { free(arr[i].e[k].key); free(arr[i].e[k].val); }
        free(arr[i].e);
        arr[i].e = NULL; arr[i].ne = 0;
    }
}

const char *lang_get(const LANG *l, const char *key, int *n)
{
    int i;
    for (i = 0; i < l->ne; i++)
        if (!strcmp(l->e[i].key, key)) {
            if (n) *n = l->e[i].n;
            return l->e[i].val;
        }
    return NULL;
}
