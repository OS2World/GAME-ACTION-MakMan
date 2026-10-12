//
// unitext.hpp -- Unicode text support for MakMan/2 (language files, menus, About)
//
// Texts come from the UTF-8 files lang\*.txt next to makman.exe.  Menu items whose
// text cannot be shown in the process code page are owner drawn through GPI code
// page 1208 (UTF-8, see uni.c); everything else stays a normal PM text item.
//

BOOL  Uni_Init(int argc, char *argv[]);       // after the frame and its menu exist
VOID  Uni_Done(VOID);
VOID  Uni_SelectByCode(const char *code);     // "en", "ja", ... (falls back to "en")
VOID  set_language(int idx);                  // idx = position in the Language menu
BOOL  Uni_AltKey(MPARAM mp1, MPARAM mp2);     // Alt+mnemonic for owner-drawn top-level items
VOID  Uni_PaintAbout(HWND hwndDlg);           // texts of the About box
VOID  Uni_DrawHighscoreTitle(HPS hps, long width, long y);

// high score entry dialog and names (UTF-8 in topNames[], drawn with GPI code page 1208)
VOID  Uni_LayoutHighscoreDlg(HWND hwndDlg);   // WM_INITDLG: room for the translated label
VOID  Uni_PaintHighscoreDlg(HWND hwndDlg);    // heading, text and label
VOID  Uni_DrawButton(PUSERBUTTON ub, int strId, int suffix = 0);   // BN_PAINT of an owner-drawn button;
                                                          // suffix: a letter appended after a space (0 = none)
VOID  Uni_DrawUtf8(HPS hps, long x, long y, const char *utf8, int pels, LONG color);
VOID  Uni_NameFromEntry(const char *cp, char *utf8, int max);   // entry field -> UTF-8
VOID  Uni_NameToCp(const char *utf8, char *cp, int max);        // UTF-8 -> code page ('?' if lost)

// dialog texts: an "MMUniText" control draws the text of a language file key
VOID  Uni_SetText(HWND hwndDlg, USHORT id, int strId, int suffix, int center);
