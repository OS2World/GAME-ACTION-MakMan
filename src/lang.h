/*
 * lang.h  --  6-language runtime string table for MakMan/2
 */

#ifndef LANG_H
#define LANG_H

#define LANG_EN    0
#define LANG_ES    1
#define LANG_NL    2
#define LANG_DE    3
#define LANG_FR    4
#define LANG_IT    5
#define LANG_COUNT 6

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
    STR_COUNT
};

extern int current_lang;
extern const char *lang_strings[LANG_COUNT][STR_COUNT];
#define tr(id) ((char*)lang_strings[current_lang][(id)])

#endif /* LANG_H */
