//
// unitext.cpp -- Unicode text support for MakMan/2
//
// Based on the PMUniText sample (DEV-SAMPLES-C-PMUniText): UTF-8 language files,
// GPI code page 1208 (UTF-8) drawing and owner-drawn menu items.  Unlike the sample, an
// item is only owner drawn when its text cannot be represented in the process
// code page, so Latin languages keep the native PM menu look.
//

#define INCL_DOS
#define INCL_GPI
#define INCL_WIN
#include "pmmain.hpp"
#include "pmvars.hpp"
#include "pmids.hpp"
#include "pmkeys.hpp"
#include "pmhelp.hpp"
#include "lang.h"
#include "unitext.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "uni.h"
#include "ulang.h"
}

#define MENU_PELS 16
#define CHECK_W   18
#define PAD        6
#define ACCEL_GAP 24
#define NBUILTIN   4

static const char *builtinFaces[NBUILTIN] = {
    "Times New Roman MT 30", "Droid Sans Combined", "Monotype Sans Duospace WT J",
    "Times New Roman WT J"
};

// keys of the language files, in the order of the STR_* ids of lang.h
static const char *str_keys[STR_COUNT] = {
    "MENU_GAME", "MENU_NEW", "MENU_PAUSE", "MENU_QUIT", "MENU_EXIT", "MENU_OPTIONS",
    "MENU_TILESET", "MENU_CLASSIC", "MENU_3D", "MENU_FUFITOS", "MENU_CONTROLS",
    "MENU_KEYBOARD", "MENU_JOYA", "MENU_JOYB", "MENU_CALIBRATE", "MENU_CALJOYSTICK_A",
    "MENU_CALJOYSTICK_B", "MENU_SOUND", "MENU_SOUND_ON", "MENU_SOUND_OFF", "MENU_PRIORITY",
    "MENU_PRI_NORMAL", "MENU_PRI_CRITICAL", "MENU_PRI_SERVER", "MENU_LANGUAGE",
    "MENU_SAVEONEXIT", "MENU_BACKGRND", "MENU_FRAME", "MENU_HELP", "MENU_ABOUT",
    "MENU_HELPINDEX", "MENU_HELPGEN", "MENU_HELPUSING", "HELP_TITLE", "HELP_MISSING",
    "ABOUT_TAGLINE", "ABOUT_VERSION", "ABOUT_PORT", "ABOUT_LICENSE", "HS_TITLE",
    "CAL_MSG", "CAL_TITLE", "HS_DLG_TITLE", "HS_CONGRATS", "HS_TEXT", "HS_ENTERNAME",
    "HS_BTN_OK", "HS_BTN_CANCEL",
    "MENU_KEYMAP", "KM_TITLE", "KM_TAB_KBD", "KM_TAB_JOY", "KM_A_LEFT", "KM_A_RIGHT", "KM_A_UP", "KM_A_DOWN", "KM_KBD_H1", "KM_KBD_H2", "KM_JOY_H1", "KM_JOY_H2", "KM_JOY_EN", "KM_OK", "KM_CANCEL", "KM_NONE", "KM_AXL", "KM_AXR", "KM_AXU", "KM_AXD", "KM_BTN"
};

// used when no lang\*.txt file can be found
static const char *builtin_en[STR_COUNT] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
    "MakMan/2 Help Window",
    "The help file %s was not found.\nPlease put it in the help folder next to the program.",
    "The ultimate PacMan for OS/2", "Version", "Open Watcom port 2026 by Martin Iturbide",
    "Free software - GNU General Public License v3", "Top 15 Players",
    "Leave the Joystick alone and click OK", "MakMan/2 Joystick Calibration",
    "Hall of Shame entry!", "Congratulations!",
    "You made it into the hall of shame, the top 15 performing users who waste their time with MakMan/2 on this machine!",
    "Enter your name:", "I'm so proud!", "I'm so ashamed",
    "~Key Mapping...", "Key Mapping", "Keyboard", "Joystick", "Move Left", "Move Right", "Move Up", "Move Down", "Click a box, then press the key", "for the action.", "Click a box, then press a joystick button", "or move the stick (Delete clears).", "~Enable Joystick", "OK", "Cancel", "None", "Axis L", "Axis R", "Axis Up", "Axis Down", "Btn %d"
};

static const struct { USHORT id; int str; } menumap[] = {
    { IDM_SUBMENU_GAME,     STR_MENU_GAME },        { IDM_NEW,          STR_MENU_NEW },
    { IDM_PAUSE,            STR_MENU_PAUSE },       { IDM_QUIT_GAME,    STR_MENU_QUIT },
    { IDM_EXIT,             STR_MENU_EXIT },        { IDM_SUBMENU_OPTS, STR_MENU_OPTIONS },
    { IDM_SUBMENU_TILESET,  STR_MENU_TILESET },     { IDM_T_CLASSIC,    STR_MENU_CLASSIC },
    { IDM_T_3D,             STR_MENU_3D },          { IDM_T_NEWLOOK,    STR_MENU_FUFITOS },
    { IDM_SUBMENU_CONTROLS, STR_MENU_CONTROLS },    { IDM_KEYBOARD,     STR_MENU_KEYBOARD },
    { IDM_JOY_A,            STR_MENU_JOYA },        { IDM_JOY_B,        STR_MENU_JOYB },
    { IDM_SUBMENU_CAL,      STR_MENU_CALIBRATE },   { IDM_CAL_A,        STR_MENU_CALJOYSTICK_A },
    { IDM_CAL_B,            STR_MENU_CALJOYSTICK_B },{ IDM_SUBMENU_SOUND, STR_MENU_SOUND },
    { IDM_SOUND_ON,         STR_MENU_SOUND_ON },    { IDM_SOUND_OFF,    STR_MENU_SOUND_OFF },
    { IDM_SUBMENU_PRI,      STR_MENU_PRIORITY },    { IDM_PRI_NORMAL,   STR_MENU_PRI_NORMAL },
    { IDM_PRI_CRIT,         STR_MENU_PRI_CRITICAL },{ IDM_PRI_SERVER,   STR_MENU_PRI_SERVER },
    { IDM_SUBMENU_LANG,     STR_MENU_LANGUAGE },    { IDM_SAVEONEXIT,   STR_MENU_SAVEONEXIT },
    { IDM_BACKGRND,         STR_MENU_BACKGRND },    { IDM_FRAME,        STR_MENU_FRAME },
    { IDM_SUBMENU_HELP,     STR_MENU_HELP },        { IDM_HELPINDEX,    STR_MENU_HELPINDEX },
    { IDM_HELPEXTENDED,     STR_MENU_HELPGEN },     { IDM_HELPHELPFORHELP, STR_MENU_HELPUSING },
    { IDM_HELPABOUT,        STR_MENU_ABOUT },
    { IDM_KEYMAPPING,       STR_MENU_KEYMAP }
};

static LANG  langs[MAX_LANGS];
static int   nlang, cur = -1, enIdx = -1;
static char  langDir[CCHMAXPATH];
static char  face[FACESIZE] = "Times New Roman MT 30";
static int   faceCovers = 1;
static int   forceOwner = 0, forcePlain = 0;
static PFNWP oldMenuProc, oldFrameProc, oldSubProc;
static HWND  hooked[32];
static int   nhooked;

static char     trbuf[STR_COUNT][300];
static USHORT   trdone[STR_COUNT];
static int      trgen = 1;

// ------------------------------------------------------------------------------
// texts
// ------------------------------------------------------------------------------

static const char *get_text(const char *key, int *n)
{
    const char *p = NULL;

    if (cur >= 0)    p = lang_get(&langs[cur], key, n);
    if (!p && enIdx >= 0) p = lang_get(&langs[enIdx], key, n);
    return p;
}

const char *trw(int id, int *n)
{
    const char *p = (id >= 0 && id < STR_COUNT) ? get_text(str_keys[id], n) : NULL;

    if (!p) p = uni_ascii((id >= 0 && id < STR_COUNT && builtin_en[id]) ? builtin_en[id] : "", n);
    return p;
}

// process code page text; English when the language needs other characters
char *tr(int id)
{
    int n;
    const char *p;

    if (id < 0 || id >= STR_COUNT) return (char *)"";
    if (trdone[id] == trgen) return trbuf[id];
    p = trw(id, &n);
    if (!uls_representable(p, n) && enIdx >= 0 && enIdx != cur) {
        const char *e = lang_get(&langs[enIdx], str_keys[id], &n);
        if (e) p = e;
    }
    uls_to_cp(p, n, trbuf[id], sizeof(trbuf[id]));
    trdone[id] = (USHORT)trgen;
    return trbuf[id];
}

const char *Uni_LangCode(VOID)
{
    return (cur >= 0) ? langs[cur].code : "en";
}

// ------------------------------------------------------------------------------
// font that really contains the characters of the active language
// ------------------------------------------------------------------------------

static VOID resolve_face(VOID)
{
    char cand[NBUILTIN + 8][FACESIZE];
    int ncand = 0, i, ns = 0, n;
    char sample[900];
    const char *p;
    char tmp[256], *tok;

    if (cur < 0) return;
    strncpy(tmp, langs[cur].fonts, sizeof(tmp) - 1); tmp[sizeof(tmp) - 1] = 0;
    for (tok = strtok(tmp, ","); tok && ncand < 8; tok = strtok(NULL, ",")) {
        while (*tok == ' ') tok++;
        if (*tok) { strncpy(cand[ncand], tok, FACESIZE - 1); cand[ncand][FACESIZE - 1] = 0; ncand++; }
    }
    for (i = 0; i < NBUILTIN; i++) strcpy(cand[ncand++], builtinFaces[i]);

    p = langs[cur].name;
    if (p) { n = utf8_align(p, langs[cur].nameLen, 250); memcpy(sample, p, n); ns = n; }
    p = get_text("MENU_GAME", &n);
    if (p) { n = utf8_align(p, n, 250); memcpy(sample + ns, p, n); ns += n; }
    p = get_text("ABOUT_TAGLINE", &n);
    if (p) { n = utf8_align(p, n, 250); memcpy(sample + ns, p, n); ns += n; }
    sample[ns] = 0;

    for (i = 0; i < ncand; i++)
        if (uni_covers(cand[i], sample, ns)) { strcpy(face, cand[i]); faceCovers = 1; return; }
    strcpy(face, cand[0]);
    faceCovers = 0;
}

// ------------------------------------------------------------------------------
// labels: "~Mnemonic" and "Text<TAB>Accelerator"
// ------------------------------------------------------------------------------

typedef struct { char t[600]; int n; int mn; int mnLen; unsigned long mnch; char a[80]; int an; } PLABEL;   // bytes

static VOID parse_label(const char *lab, PLABEL *o)
{
    int i = 0, k = 0, inAcc = 0;

    o->mn = -1; o->mnLen = 0; o->mnch = 0; o->an = 0;
    while (lab[i]) {
        if (lab[i] == 0x09 && !inAcc) { inAcc = 1; i++; continue; }
        if (inAcc) { if (o->an < 78) o->a[o->an++] = lab[i]; i++; continue; }
        if (lab[i] == '~' && o->mn < 0 && lab[i + 1]) {        // mnemonic: the next character
            int used = 0;
            o->mnch = utf8_decode(lab + i + 1, (int)strlen(lab + i + 1), &used);
            o->mn = k; o->mnLen = used;
            i++;
            continue;
        }
        if (k < 590) o->t[k++] = lab[i];
        i++;
    }
    o->t[k] = 0; o->n = k;
    o->a[o->an] = 0;
}

static unsigned long upc(unsigned long c) { return (c >= 'a' && c <= 'z') ? c - 32 : c; }

static const char *label_for(USHORT id, int *n)
{
    int i;

    if (id >= IDM_LANG_EN && id < IDM_LANG_EN + MAX_LANGS) {
        int k = id - IDM_LANG_EN;
        if (k < nlang && langs[k].name) { if (n) *n = langs[k].nameLen; return langs[k].name; }
        return NULL;
    }
    for (i = 0; i < (int)(sizeof(menumap) / sizeof(menumap[0])); i++)
        if (menumap[i].id == id) return get_text(str_keys[menumap[i].str], n);
    return NULL;
}

static int needs_owner(const char *lab, int n)
{
    if (forcePlain) return 0;
    return forceOwner || !uls_representable(lab, n);
}

// ------------------------------------------------------------------------------
// applying the texts to the menu
// ------------------------------------------------------------------------------

static VOID hook_submenu(HWND h);

static VOID walk_menu(HWND hm)
{
    SHORT cnt = SHORT1FROMMR(WinSendMsg(hm, MM_QUERYITEMCOUNT, 0, 0));
    SHORT pos;

    for (pos = 0; pos < cnt; pos++) {
        SHORT id = SHORT1FROMMR(WinSendMsg(hm, MM_ITEMIDFROMPOSITION, MPFROMSHORT(pos), 0));
        MENUITEM mi;
        const char *lab;
        int n;

        if (!WinSendMsg(hm, MM_QUERYITEM, MPFROM2SHORT(id, FALSE), MPFROMP(&mi))) continue;
        if (mi.afStyle & MIS_SEPARATOR) continue;
        lab = label_for((USHORT)id, &n);
        if (lab) {
            if (needs_owner(lab, n)) {
                mi.afStyle = (USHORT)((mi.afStyle & ~MIS_TEXT) | MIS_OWNERDRAW);
                mi.hItem   = (ULONG)lab;
                WinSendMsg(hm, MM_SETITEM, MPFROM2SHORT(0, FALSE), MPFROMP(&mi));
            } else {
                char txt[300];
                if (mi.afStyle & MIS_OWNERDRAW) {
                    mi.afStyle = (USHORT)((mi.afStyle & ~MIS_OWNERDRAW) | MIS_TEXT);
                    mi.hItem   = 0;
                    WinSendMsg(hm, MM_SETITEM, MPFROM2SHORT(0, FALSE), MPFROMP(&mi));
                }
                uls_to_cp(lab, n, txt, sizeof(txt));
                WinSendMsg(hm, MM_SETITEMTEXT, MPFROMSHORT(id), MPFROMP(txt));
            }
        }
        if (mi.afStyle & MIS_SUBMENU) {
            hook_submenu(mi.hwndSubMenu);
            walk_menu(mi.hwndSubMenu);
        }
    }
}

static VOID rebuild_language_items(VOID)
{
    MENUITEM mi;
    HWND sub;
    int i;

    if (!WinSendMsg(hwndMenu, MM_QUERYITEM, MPFROM2SHORT(IDM_SUBMENU_LANG, TRUE), MPFROMP(&mi))) return;
    sub = mi.hwndSubMenu;
    for (i = 0; i < MAX_LANGS; i++)
        WinSendMsg(sub, MM_DELETEITEM, MPFROM2SHORT(IDM_LANG_EN + i, FALSE), 0);
    for (i = 0; i < nlang; i++) {
        MENUITEM ni;
        memset(&ni, 0, sizeof(ni));
        ni.iPosition = MIT_END;
        ni.afStyle   = MIS_TEXT;
        ni.id        = (USHORT)(IDM_LANG_EN + i);
        WinSendMsg(sub, MM_INSERTITEM, MPFROMP(&ni), MPFROMP(langs[i].english));
    }
}

VOID set_language(int idx)
{
    int i;

    if (nlang == 0) return;                      // no language files: keep the resource menu
    if (idx < 0 || idx >= nlang) idx = (enIdx >= 0) ? enIdx : 0;
    cur = idx;
    trgen++;
    resolve_face();
    walk_menu(hwndMenu);
    for (i = 0; i < nlang; i++)
        WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(IDM_LANG_EN + i, TRUE),
                   MPFROM2SHORT(MIA_CHECKED, (i == cur) ? MIA_CHECKED : 0));
    WinSendMsg(hwndFrame, WM_UPDATEFRAME, MPFROMLONG(FCF_MENU), 0);
    WinInvalidateRect(hwndMenu, NULL, TRUE);
    WinInvalidateRect(hwndClient, NULL, TRUE);
    if (hwndFrame) HelpInit();
                   // the help file follows the language
}

VOID Uni_SelectByCode(const char *code)
{
    int i, idx = -1;

    for (i = 0; i < nlang; i++)
        if (code && !stricmp(langs[i].code, code)) { idx = i; break; }
    set_language(idx);
}

// ------------------------------------------------------------------------------
// owner drawn items; PM sends the messages to the owner of the menu (the frame)
// ------------------------------------------------------------------------------

static MRESULT owner_msg(ULONG msg, MPARAM mp2, int *handled)
{
    *handled = 0;
    switch (msg) {
    case WM_MEASUREITEM: {
        POWNERITEM poi = (POWNERITEM)PVOIDFROMMP(mp2);
        const char *lab = (const char *)poi->hItem;
        HPS hps;
        ULONG ocp;
        PLABEL pl;
        int w = 0, h = MENU_PELS + 6;

        if (!lab) break;
        parse_label(lab, &pl);
        hps = WinGetPS(poi->hwnd);
        if (uni_begin(hps, face, MENU_PELS, &ocp)) {
            w = uni_width(hps, pl.t, pl.n);
            if (pl.an && poi->hwnd != hwndMenu) w += ACCEL_GAP + uni_width(hps, pl.a, pl.an);
            h = uni_height(hps) + 4;
        }
        uni_end(hps, ocp);
        WinReleasePS(hps);
        w += 2 * PAD + (poi->hwnd == hwndMenu ? 0 : CHECK_W);
        poi->rclItem.xLeft = 0; poi->rclItem.yBottom = 0;
        poi->rclItem.xRight = w; poi->rclItem.yTop = h;
        *handled = 1;
        return MRFROMSHORT((SHORT)h);
    }

    case WM_DRAWITEM: {
        POWNERITEM poi = (POWNERITEM)PVOIDFROMMP(mp2);
        const char *lab = (const char *)poi->hItem;
        HPS hps;
        ULONG ocp;
        LONG bg, fg;
        PLABEL pl;
        POINTL pt;
        int hil, chk, dis, bar, itemH;

        if (!lab) break;
        parse_label(lab, &pl);
        hil = (poi->fsAttribute & MIA_HILITED) != 0;
        chk = (poi->fsAttribute & MIA_CHECKED) != 0;
        dis = (poi->fsAttribute & MIA_DISABLED) != 0;
        bar = (poi->hwnd == hwndMenu);
        bg = hil ? SYSCLR_MENUHILITEBGND : SYSCLR_MENU;
        fg = dis ? SYSCLR_MENUDISABLEDTEXT : (hil ? SYSCLR_MENUHILITE : SYSCLR_MENUTEXT);

        hps = WinGetPS(poi->hwnd);
        WinFillRect(hps, &poi->rclItem, bg);
        GpiSetColor(hps, fg);
        itemH = (int)(poi->rclItem.yTop - poi->rclItem.yBottom);
        if (uni_begin(hps, face, MENU_PELS, &ocp)) {
            long tx, by;
            int lineH = uni_height(hps), desc = uni_descender(hps);

            tx = poi->rclItem.xLeft + PAD + (bar ? 0 : CHECK_W);
            by = poi->rclItem.yBottom + (itemH - lineH) / 2 + desc;
            uni_draw(hps, tx, by, pl.t, pl.n);
            if (pl.mn >= 0) {                                   // underline the mnemonic
                long ux = tx + uni_width(hps, pl.t, pl.mn);
                long uw = uni_width(hps, pl.t + pl.mn, pl.mnLen);
                pt.x = ux;      pt.y = by - 2; GpiMove(hps, &pt);
                pt.x = ux + uw; pt.y = by - 2; GpiLine(hps, &pt);
            }
            if (pl.an && !bar)                                  // accelerator, right aligned
                uni_draw(hps, poi->rclItem.xRight - PAD - uni_width(hps, pl.a, pl.an), by, pl.a, pl.an);
        }
        uni_end(hps, ocp);
        if (chk && !bar) {                                      // check mark
            long x = poi->rclItem.xLeft + 4, y = poi->rclItem.yBottom + itemH / 2;
            pt.x = x;      pt.y = y;     GpiMove(hps, &pt);
            pt.x = x + 4;  pt.y = y - 5; GpiLine(hps, &pt);
            pt.x = x + 11; pt.y = y + 5; GpiLine(hps, &pt);
        }
        WinReleasePS(hps);
        poi->fsAttribute    &= ~(MIA_CHECKED | MIA_HILITED | MIA_FRAMED | MIA_DISABLED);
        poi->fsAttributeOld &= ~(MIA_CHECKED | MIA_HILITED | MIA_FRAMED | MIA_DISABLED);
        *handled = 1;
        return MRFROMLONG(TRUE);
    }
    }
    return 0;
}

// enabled owner-drawn item of menu window hm whose mnemonic is ch (id, or -1)
static int find_mnemonic(HWND hm, USHORT ch, MENUITEM *out)
{
    SHORT cnt = SHORT1FROMMR(WinSendMsg(hm, MM_QUERYITEMCOUNT, 0, 0));
    SHORT pos;

    for (pos = 0; pos < cnt; pos++) {
        SHORT id = SHORT1FROMMR(WinSendMsg(hm, MM_ITEMIDFROMPOSITION, MPFROMSHORT(pos), 0));
        MENUITEM mi;
        const char *lab;
        PLABEL pl;
        int n;

        if (!WinSendMsg(hm, MM_QUERYITEM, MPFROM2SHORT(id, FALSE), MPFROMP(&mi))) continue;
        if ((mi.afStyle & MIS_SEPARATOR) || !(mi.afStyle & MIS_OWNERDRAW) ||
            (mi.afAttribute & MIA_DISABLED)) continue;      // text items: PM does it itself
        lab = label_for((USHORT)id, &n);
        if (!lab) continue;
        parse_label(lab, &pl);
        if (pl.mn >= 0 && upc(pl.mnch) == upc(ch)) { *out = mi; return id; }
    }
    return -1;
}

static VOID activate_item(HWND hm, USHORT id, const MENUITEM *mi)
{
    if (mi->afStyle & MIS_SUBMENU) {
        WinSendMsg(hm, MM_SELECTITEM, MPFROM2SHORT(id, FALSE), MPFROM2SHORT(0, FALSE));
    } else {
        WinSendMsg(hwndMenu, MM_ENDMENUMODE, MPFROMSHORT(TRUE), 0);
        WinPostMsg(hwndClient, WM_COMMAND, MPFROM2SHORT(id, CMDSRC_MENU),
                   MPFROM2SHORT(CMDSRC_MENU, FALSE));
    }
}

static MRESULT EXPENTRY SubMenuProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    if (msg == WM_CHAR) {
        USHORT fs = SHORT1FROMMP(mp1);
        if ((fs & KC_CHAR) && !(fs & KC_KEYUP) && !(fs & (KC_ALT | KC_CTRL))) {
            MENUITEM mi;
            int id = find_mnemonic(hwnd, SHORT1FROMMP(mp2), &mi);
            if (id >= 0) { activate_item(hwnd, (USHORT)id, &mi); return MRFROMLONG(TRUE); }
        }
    }
    return oldSubProc(hwnd, msg, mp1, mp2);
}

static VOID hook_submenu(HWND h)
{
    int i;
    PFNWP p;

    for (i = 0; i < nhooked; i++) if (hooked[i] == h) return;
    if (nhooked >= 32) return;
    p = WinSubclassWindow(h, SubMenuProc);
    if (p) { if (!oldSubProc) oldSubProc = p; hooked[nhooked++] = h; }
}

static MRESULT EXPENTRY MenuProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    if (msg == WM_MEASUREITEM || msg == WM_DRAWITEM) {
        int h;
        MRESULT r = owner_msg(msg, mp2, &h);
        if (h) return r;
    }
    return oldMenuProc(hwnd, msg, mp1, mp2);
}

static MRESULT EXPENTRY FrameProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    if (msg == WM_MEASUREITEM || msg == WM_DRAWITEM) {
        int h;
        MRESULT r = owner_msg(msg, mp2, &h);
        if (h) return r;
    }
    return oldFrameProc(hwnd, msg, mp1, mp2);
}

// Alt+letter in the client: open an owner-drawn top-level menu.  PM does not set
// KC_CHAR for Alt combinations, so the character code is used directly.
BOOL Uni_AltKey(MPARAM mp1, MPARAM mp2)
{
    USHORT fs = SHORT1FROMMP(mp1);
    MENUITEM mi;
    int id;

    if (!(fs & KC_ALT) || (fs & (KC_KEYUP | KC_CTRL)) || SHORT1FROMMP(mp2) <= 0x20) return FALSE;
    id = find_mnemonic(hwndMenu, SHORT1FROMMP(mp2), &mi);
    if (id < 0) return FALSE;
    WinSendMsg(hwndMenu, MM_STARTMENUMODE, MPFROM2SHORT(TRUE, FALSE), 0);
    WinSendMsg(hwndMenu, MM_SELECTITEM, MPFROM2SHORT(id, FALSE), MPFROM2SHORT(0, FALSE));
    return TRUE;
}

// ------------------------------------------------------------------------------
// About box and high score screen
// ------------------------------------------------------------------------------

static VOID draw_centered(HPS hps, const char *s, int n, long cx, long y)
{
    uni_draw(hps, (cx - uni_width(hps, s, n)) / 2, y, s, n);
}

VOID Uni_PaintAbout(HWND hwndDlg)
{
    HPS hps;
    ULONG ocp;
    SWP swpOk, swpHead;
    RECTL rc;
    char line[500];
    const char *p;
    int n, k, lines = 0;
    struct { const char *s; int n; } L[5];
    long top, bottom, y;

    WinQueryWindowRect(hwndDlg, &rc);
    if (!WinQueryWindowPos(WinWindowFromID(hwndDlg, DID_OK), &swpOk)) return;
    if (!WinQueryWindowPos(WinWindowFromID(hwndDlg, 101), &swpHead)) return;
    top    = swpHead.y - 4;
    bottom = swpOk.y + swpOk.cy + 4;

    p = trw(STR_ABOUT_TAGLINE, &n);   L[lines].s = p; L[lines++].n = n;
    {                                                      // "Version 1.1"
        const char *v = trw(STR_ABOUT_VERSION, &n);
        int i, m = 0;
        n = utf8_align(v, n, 300);
        memcpy(line, v, n); m = n;
        line[m++] = ' ';
        for (i = 0; szAppVersion[i] && m < 490; i++) line[m++] = szAppVersion[i];
        line[m] = 0;
        L[lines].s = line; L[lines++].n = m;
    }
    p = uni_ascii("(C) Copyright 1995 Markellos J. Diorinos", &n);
    L[lines].s = p; L[lines++].n = n;
    p = trw(STR_ABOUT_PORT, &n);      L[lines].s = p; L[lines++].n = n;
    p = trw(STR_ABOUT_LICENSE, &n);   L[lines].s = p; L[lines++].n = n;

    hps = WinGetPS(hwndDlg);
    GpiSetColor(hps, SYSCLR_WINDOWSTATICTEXT);
    if (uni_begin(hps, face, 14, &ocp)) {
        int lh = uni_height(hps), desc = uni_descender(hps);
        long span = top - bottom;
        long gap = (span - lines * lh) / (lines + 1);

        if (gap < 0) gap = 0;
        y = top - gap;
        for (k = 0; k < lines; k++) {
            y -= lh;
            draw_centered(hps, L[k].s, L[k].n, rc.xRight - rc.xLeft, y + desc);
            y -= gap;
        }
    }
    uni_end(hps, ocp);
    WinReleasePS(hps);
}

VOID Uni_DrawHighscoreTitle(HPS hps, long width, long y)
{
    char head[80];
    char buf[500];
    const char *t;
    ULONG ocp;
    int n, m;

    sprintf(head, "%s v%s ", szAppName, szAppVersion);
    m = (int)strlen(head);
    memcpy(buf, head, m);
    t = trw(STR_HS_TITLE, &n);
    n = utf8_align(t, n, 380);
    memcpy(buf + m, t, n); m += n;
    buf[m] = 0;
    GpiSetColor(hps, CLR_RED);
    if (uni_begin(hps, face, 22, &ocp))
        draw_centered(hps, buf, m, width, y);
    uni_end(hps, ocp);
}

// ------------------------------------------------------------------------------
// high score entry dialog, buttons and names
// ------------------------------------------------------------------------------

#define HS_MARGIN 14
#define HS_PELS   14

// largest k (1..len) with width(p[0..k)) <= maxw
static int fit_chars(HPS hps, const char *p, int len, int maxw)
{
    int lo = utf8_align(p, len, 1), hi = len;          // at least one character

    if (uni_width(hps, p, len) <= maxw) return len;
    while (lo < hi) {
        int mid = utf8_align(p, len, (lo + hi + 1) / 2);   // always on a character boundary
        if (mid <= lo) break;
        if (uni_width(hps, p, mid) <= maxw) lo = mid; else hi = utf8_align(p, len, mid - 1);
    }
    return lo;
}

// wrapped paragraph; *top is the top of the next line, the text moves down
static VOID draw_wrapped(HPS hps, long x, long *top, int maxw, const char *p, int len)
{
    int lineH = uni_height(hps), desc = uni_descender(hps);

    while (len > 0) {
        int fit = fit_chars(hps, p, len, maxw), brk = fit, draw;

        if (fit < len) {
            int i, sp = 0;
            for (i = fit; i > 0; i--) if (p[i - 1] == ' ') { sp = i; break; }
            if (sp > 0) brk = sp;                         // word break; CJK breaks anywhere
        }
        draw = brk;
        while (draw > 0 && p[draw - 1] == ' ') draw--;
        uni_draw(hps, x, *top - (lineH - desc), p, draw);
        *top -= lineH;
        p += brk; len -= brk;
    }
}

VOID Uni_LayoutHighscoreDlg(HWND hwndDlg)
{
    HPS hps;
    ULONG ocp;
    RECTL rc;
    SWP swp;
    HWND hwndEntry = WinWindowFromID(hwndDlg, DID_HIGHNAME);
    int n, lw = 0;
    const char *p = trw(STR_HS_ENTERNAME, &n);

    WinQueryWindowRect(hwndDlg, &rc);
    if (!WinQueryWindowPos(hwndEntry, &swp)) return;
    hps = WinGetPS(hwndDlg);
    if (uni_begin(hps, face, HS_PELS, &ocp)) lw = uni_width(hps, p, n);
    uni_end(hps, ocp);
    WinReleasePS(hps);
    {
        long x = HS_MARGIN + lw + 10;
        long w = (rc.xRight - rc.xLeft) - x - HS_MARGIN;
        if (w < 80) w = 80;
        WinSetWindowPos(hwndEntry, NULLHANDLE, x, swp.y, w, swp.cy, SWP_MOVE | SWP_SIZE);
    }
}

VOID Uni_PaintHighscoreDlg(HWND hwndDlg)
{
    HPS hps;
    ULONG ocp;
    RECTL rc;
    SWP swpEntry, swpTitle;
    int n;
    long top, ty;
    const char *p;

    WinQueryWindowRect(hwndDlg, &rc);
    if (!WinQueryWindowPos(WinWindowFromID(hwndDlg, DID_HIGHNAME), &swpEntry)) return;
    ty = 0;
    if (WinQueryWindowPos(WinWindowFromID(hwndDlg, FID_TITLEBAR), &swpTitle)) ty = swpTitle.cy;
    top = rc.yTop - ty - HS_MARGIN;

    hps = WinGetPS(hwndDlg);
    if (uni_begin(hps, face, 22, &ocp)) {                      // heading
        GpiSetColor(hps, CLR_RED);
        p = trw(STR_HS_CONGRATS, &n);
        draw_wrapped(hps, HS_MARGIN, &top, (int)(rc.xRight - rc.xLeft) - 2 * HS_MARGIN, p, n);
        top -= 6;
    }
    uni_end(hps, ocp);
    if (uni_begin(hps, face, HS_PELS, &ocp)) {                 // explanation and label
        int lh = uni_height(hps), desc = uni_descender(hps);
        GpiSetColor(hps, SYSCLR_WINDOWSTATICTEXT);
        p = trw(STR_HS_TEXT, &n);
        draw_wrapped(hps, HS_MARGIN, &top, (int)(rc.xRight - rc.xLeft) - 2 * HS_MARGIN, p, n);
        p = trw(STR_HS_ENTERNAME, &n);
        uni_draw(hps, HS_MARGIN, swpEntry.y + (swpEntry.cy - lh) / 2 + desc, p, n);
    }
    uni_end(hps, ocp);
    WinReleasePS(hps);
}

// ------------------------------------------------------------------------------
// dialog texts: "MMUniText" controls and owner-drawn buttons
// ------------------------------------------------------------------------------

#define UT_PELS 16

// the text of a label without mnemonic markers ("~" and "(~X)") and accelerator,
// optionally followed by a space and a letter
static int plain_text(const char *lab, int n, int suffix, char *out, int max)
{
    int i = 0, k = 0;

    while (i < n && k < max - 4) {
        if (lab[i] == 0x09) break;
        if (lab[i] == '(' && i + 3 < n && lab[i + 1] == '~' && lab[i + 3] == ')') { i += 4; continue; }
        if (lab[i] == '~') { i++; continue; }
        out[k++] = lab[i++];
    }
    if (suffix) { out[k++] = ' '; out[k++] = (char)suffix; }
    out[k] = 0;
    return k;
}

// window words: 0 = STR id, 4 = suffix letter, 8 = 1 when centered
static MRESULT EXPENTRY UniTextProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    if (msg == WM_PAINT) {
        HPS hps = WinBeginPaint(hwnd, NULLHANDLE, NULL);
        RECTL rc;
        ULONG id = WinQueryWindowULong(hwnd, 0);
        int dis = !WinIsWindowEnabled(hwnd);

        WinQueryWindowRect(hwnd, &rc);
        WinFillRect(hps, &rc, SYSCLR_DIALOGBACKGROUND);
        if (id > 0 && id < STR_COUNT) {
            char txt[600];
            int n, tn, pels;
            const char *p = trw((int)id, &n);
            ULONG ocp;

            tn = plain_text(p, n, (int)WinQueryWindowULong(hwnd, 4), txt, sizeof(txt));
            GpiSetColor(hps, dis ? SYSCLR_MENUDISABLEDTEXT : SYSCLR_WINDOWSTATICTEXT);
            for (pels = UT_PELS; pels >= 9; pels--) {      // smaller until it fits
                int ok = uni_begin(hps, face, pels, &ocp);
                if (ok) {
                    int w = uni_width(hps, txt, tn);
                    if (w <= rc.xRight - rc.xLeft || pels == 9) {
                        int lh = uni_height(hps), desc = uni_descender(hps);
                        long x = WinQueryWindowULong(hwnd, 8) ? (rc.xRight - rc.xLeft - w) / 2 : 0;
                        if (x < 0) x = 0;
                        uni_draw(hps, x, (rc.yTop - rc.yBottom - lh) / 2 + desc, txt, tn);
                        uni_end(hps, ocp);
                        break;
                    }
                }
                uni_end(hps, ocp);
                if (!ok) break;
            }
        }
        WinEndPaint(hps);
        return 0;
    }
    return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

VOID Uni_SetText(HWND hwndDlg, USHORT id, int strId, int suffix, int center)
{
    HWND h = WinWindowFromID(hwndDlg, id);

    if (!h) return;
    WinSetWindowULong(h, 0, (ULONG)strId);
    WinSetWindowULong(h, 4, (ULONG)suffix);
    WinSetWindowULong(h, 8, (ULONG)center);
    WinInvalidateRect(h, NULL, FALSE);
}

VOID Uni_DrawButton(PUSERBUTTON ub, int strId, int suffix)
{
    HPS hps = ub->hps;
    RECTL rc;
    POINTL pt;
    ULONG ocp;
    int hil = (ub->fsState & BDS_HILITED) != 0;
    int dis = (ub->fsState & BDS_DISABLED) != 0;
    int def = (ub->fsState & BDS_DEFAULT) != 0;
    const char *p;
    int n;

    WinQueryWindowRect(ub->hwnd, &rc);
    WinFillRect(hps, &rc, SYSCLR_BUTTONMIDDLE);
    GpiSetColor(hps, hil ? SYSCLR_BUTTONDARK : SYSCLR_BUTTONLIGHT);          // top and left edge
    pt.x = rc.xLeft;      pt.y = rc.yBottom;     GpiMove(hps, &pt);
    pt.x = rc.xLeft;      pt.y = rc.yTop - 1;    GpiLine(hps, &pt);
    pt.x = rc.xRight - 1; pt.y = rc.yTop - 1;    GpiLine(hps, &pt);
    GpiSetColor(hps, hil ? SYSCLR_BUTTONLIGHT : SYSCLR_BUTTONDARK);          // bottom and right edge
    pt.x = rc.xRight - 1; pt.y = rc.yBottom;     GpiLine(hps, &pt);
    pt.x = rc.xLeft;      pt.y = rc.yBottom;     GpiLine(hps, &pt);
    if (def) {                                                              // default button frame
        GpiSetColor(hps, CLR_BLACK);
        pt.x = rc.xLeft + 1;      pt.y = rc.yBottom + 1;  GpiMove(hps, &pt);
        pt.x = rc.xRight - 2;     pt.y = rc.yTop - 2;
        GpiBox(hps, DRO_OUTLINE, &pt, 0, 0);
    }
    char txt[600];
    int tn;
    p = trw(strId, &n);
    tn = plain_text(p, n, suffix, txt, sizeof(txt));
    if (uni_begin(hps, face, HS_PELS, &ocp)) {
        int lh = uni_height(hps), desc = uni_descender(hps), w = uni_width(hps, txt, tn);
        long x = (rc.xRight - rc.xLeft - w) / 2 + (hil ? 1 : 0);
        long y = (rc.yTop - rc.yBottom - lh) / 2 + desc - (hil ? 1 : 0);
        GpiSetColor(hps, dis ? SYSCLR_MENUDISABLEDTEXT : CLR_BLACK);
        uni_draw(hps, x, y, txt, tn);
    }
    uni_end(hps, ocp);
}

VOID Uni_DrawUtf8(HPS hps, long x, long y, const char *utf8, int pels, LONG color)
{
    ULONG ocp;

    GpiSetColor(hps, color);
    if (uni_begin(hps, face, pels, &ocp)) uni_draw(hps, x, y, utf8, (int)strlen(utf8));
    uni_end(hps, ocp);
}

VOID Uni_NameFromEntry(const char *cp, char *utf8, int max)
{
    uls_init();
    uls_from_cp(cp, utf8, max);
}

VOID Uni_NameToCp(const char *utf8, char *cp, int max)
{
    uls_init();
    uls_to_cp(utf8, (int)strlen(utf8), cp, max);
}

// ------------------------------------------------------------------------------
// start / stop
// ------------------------------------------------------------------------------

BOOL Uni_Init(int argc, char *argv[])
{
    PTIB ptib;
    PPIB ppib;
    char *p;
    int i;

    for (i = 1; i < argc; i++) {
        if (!stricmp(argv[i], "-plainmenus"))   forcePlain = 1;
        if (!stricmp(argv[i], "-unicodemenus")) forceOwner = 1;
    }
    uls_init();
    WinRegisterClass(habMain, "MMUniText", (PFNWP)UniTextProc, CS_SIZEREDRAW, 12);

    langDir[0] = 0;
    DosGetInfoBlocks(&ptib, &ppib);
    if (DosQueryModuleName(ppib->pib_hmte, sizeof(langDir), langDir) == 0) {
        p = strrchr(langDir, '\\');
        if (p) p[1] = 0; else langDir[0] = 0;
    }
    strcat(langDir, "lang\\");
    nlang = lang_scan(langDir, langs, MAX_LANGS);
    for (i = 0; i < nlang; i++)
        if (!stricmp(langs[i].code, "en")) enIdx = i;

    // menu hooks: the frame receives WM_MEASUREITEM / WM_DRAWITEM
    oldFrameProc = WinSubclassWindow(hwndFrame, FrameProc);
    oldMenuProc  = WinSubclassWindow(hwndMenu, MenuProc);
    if (nlang) rebuild_language_items();
    return nlang > 0;
}

VOID Uni_Done(VOID)
{
    lang_free(langs, nlang);
    uni_done();
}
