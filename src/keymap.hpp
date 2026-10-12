//
// keymap.hpp -- keyboard and joystick mapping of MakMan/2 ("Key Mapping..." dialog)
//

#define ACT_LEFT      0
#define ACT_RIGHT     1
#define ACT_UP        2
#define ACT_DOWN      3
#define KM_ACTIONS    4

VOID  KmInit(VOID);                          // after the joystick driver was opened and KmLoad()
BOOL  KmLoad(HINI hini);                     // mappings from MAKMAN.INI; FALSE when none saved
VOID  KmSave(HINI hini);
INT   KmKeyAction(MPARAM mp1, MPARAM mp2);   // WM_CHAR -> action (ACT_*) or -1
VOID  KmJoyPoll(VOID);                       // game thread, once per tick: sets the move
VOID  KmDialog(HWND hwndOwner);              // the dialog

// implemented in makengine.cpp
VOID  Eng_SetMove(INT action);
