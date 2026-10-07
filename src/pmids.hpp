//
// pmids.hpp -- resource and menu ID definitions for MakMan/2
//
// ID ranges (per project standard):
//   100-199  Game menu items
//   200-299  Options menu items
//   300-399  Language menu items
//   900-999  Help menu items
//  1000-1099 Submenu cascade IDs (for MM_SETITEMTEXT at runtime)
//

// Bitmaps
#define IDB_BACK_1       41

// Resource ID
#define IDR_MAIN               1

// ---- Submenu cascade IDs (1000-1099) ----
#define IDM_SUBMENU_GAME      1000
#define IDM_SUBMENU_OPTS      1001
#define IDM_SUBMENU_TILESET   1002
#define IDM_SUBMENU_CONTROLS  1003
#define IDM_SUBMENU_CAL       1004
#define IDM_SUBMENU_SOUND     1005
#define IDM_SUBMENU_PRI       1006
#define IDM_SUBMENU_LANG      1007
#define IDM_SUBMENU_HELP      1008

// ---- Game menu: 100-199 ----
#define IDM_NEW              101
#define IDM_PAUSE            102
#define IDM_QUIT_GAME        103
#define IDM_EXIT             104

// ---- Options menu: 200-299 ----
#define IDM_T_CLASSIC        201
#define IDM_T_3D             202
#define IDM_T_NEWLOOK        203
#define IDM_KEYBOARD         204
#define IDM_JOY_A            205
#define IDM_JOY_B            206
#define IDM_CAL_A            207
#define IDM_CAL_B            208
#define IDM_SOUND_ON         209
#define IDM_SOUND_OFF        210
#define IDM_PRI_NORMAL       211
#define IDM_PRI_CRIT         212
#define IDM_PRI_SERVER       213
#define IDM_SAVEONEXIT       214
#define IDM_BACKGRND         215
#define IDM_FRAME            216

// ---- Language menu: 300-399 ----
#define IDM_LANG_EN          300
#define IDM_LANG_ES          301
#define IDM_LANG_NL          302
#define IDM_LANG_DE          303
#define IDM_LANG_FR          304
#define IDM_LANG_IT          305

// ---- Help menu: 900-999 ----
#define IDM_HELPINDEX        901
#define IDM_HELPEXTENDED     902
#define IDM_HELPHELPFORHELP  903
#define IDM_HELPABOUT        999

// ---- Help table and panels ----
#define MAIN_HELP_TABLE      2000
#define SUBTABLE_MAIN        2001
#define SUBTABLE_ABOUT       2002
#define PANEL_INTRO          2100
#define PANEL_GOAL           2101
#define PANEL_CONTROLS       2102
#define PANEL_SCORING        2103
#define PANEL_GAMEMENU       2104
#define PANEL_OPTMENU        2105
#define PANEL_HELPMENU       2106
#define PANEL_CMDLINE        2107
#define PANEL_COPYRIGHT      2108

// ---- Internal message IDs ----
#define IDM_ENGINE           666

// ---- String table IDs ----
#define IDS_TITLEBAR          1
#define IDS_ERRORTITLE        2
#define IDS_ERRORMSG          3
#define IDS_ERROR_OUTOFMEMORY 4
#define IDS_UNKNOWNMSG        5
#define IDS_CANNOTLOADSTRING  6
#define IDS_ENGINEERROR       7
#define IDS_DIVETOOMANY       8
#define IDS_DIVENODRIVER      9
#define IDS_DIVENODIRECT     10

// ---- Dialog IDs ----
#define IDD_ABOUTBOX        1001
#define IDD_HIGHSCORE       1002
#define IDC_OK                 1
#define IDC_CANCEL             2
#define IDC_HELP               3
#define IDC_ICON               4
#define DID_HIGHNAME        1003

#define MSGBOXID             222
