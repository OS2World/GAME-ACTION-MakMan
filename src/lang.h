/*
 * lang.h  --  text ids for MakMan/2
 *
 * The texts are no longer compiled in: they come from the UTF-8 language
 * files lang\*.txt (see unitext.cpp).  The ids below select a key of such a
 * file; the order must match str_keys[] in unitext.cpp.
 */

#ifndef LANG_H
#define LANG_H

enum {
    STR_MENU_GAME = 0,
    STR_MENU_NEW,
    STR_MENU_PAUSE,
    STR_MENU_QUIT,
    STR_MENU_EXIT,
    STR_MENU_OPTIONS,
    STR_MENU_TILESET,
    STR_MENU_CLASSIC,
    STR_MENU_3D,
    STR_MENU_FUFITOS,
    STR_MENU_CONTROLS,
    STR_MENU_KEYBOARD,
    STR_MENU_JOYA,
    STR_MENU_JOYB,
    STR_MENU_CALIBRATE,
    STR_MENU_CALJOYSTICK_A,
    STR_MENU_CALJOYSTICK_B,
    STR_MENU_SOUND,
    STR_MENU_SOUND_ON,
    STR_MENU_SOUND_OFF,
    STR_MENU_PRIORITY,
    STR_MENU_PRI_NORMAL,
    STR_MENU_PRI_CRITICAL,
    STR_MENU_PRI_SERVER,
    STR_MENU_LANGUAGE,
    STR_MENU_SAVEONEXIT,
    STR_MENU_BACKGRND,
    STR_MENU_FRAME,
    STR_MENU_HELP,
    STR_MENU_ABOUT,
    STR_MENU_HELPINDEX,
    STR_MENU_HELPGEN,
    STR_MENU_HELPUSING,
    STR_HELP_TITLE,
    STR_HELP_MISSING,
    STR_ABOUT_TAGLINE,
    STR_ABOUT_VERSION,
    STR_ABOUT_PORT,
    STR_ABOUT_LICENSE,
    STR_HS_TITLE,
    STR_CAL_MSG,
    STR_CAL_TITLE,
    STR_HS_DLG_TITLE,
    STR_HS_CONGRATS,
    STR_HS_TEXT,
    STR_HS_ENTERNAME,
    STR_HS_BTN_OK,
    STR_HS_BTN_CANCEL,
    STR_MENU_KEYMAP,
    STR_KM_TITLE,
    STR_KM_TAB_KBD,
    STR_KM_TAB_JOY,
    STR_KM_A_LEFT,
    STR_KM_A_RIGHT,
    STR_KM_A_UP,
    STR_KM_A_DOWN,
    STR_KM_KBD_H1,
    STR_KM_KBD_H2,
    STR_KM_JOY_H1,
    STR_KM_JOY_H2,
    STR_KM_JOY_EN,
    STR_KM_OK,
    STR_KM_CANCEL,
    STR_KM_NONE,
    STR_KM_AXL,
    STR_KM_AXR,
    STR_KM_AXU,
    STR_KM_AXD,
    STR_KM_BTN,
    STR_COUNT
};

/* Text in the process code page, for APIs that cannot take UTF-8 (message
   boxes, help window title).  When the language needs characters that the
   code page lacks, the English text is returned instead. */
char *tr(int id);

/* Text as UTF-8 (zero terminated); *n receives the length in bytes. */
const char *trw(int id, int *n);

/* Code of the active language ("en", "ja", ...), file name of its help. */
const char *Uni_LangCode(void);

#endif /* LANG_H */
