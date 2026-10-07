.* MakMan/2 help - en
:userdoc.

:h1 res=2100.About MakMan/2
:i1.About MakMan/2
:p.
MakMan/2 is a maze game in the style of PacMan for OS/2 and ArcaOS. It was written in 1995 by Markellos J. Diorinos; this version is an Open Watcom port with menus in six languages, keyboard shortcuts, online help and saved settings.
:p.
Guide MakMan through the maze, eat all the dots and keep away from the ghosts.
:p.
More information&colon.
:p.
:link reftype=hd res=2101.How to play:elink.
.br
:link reftype=hd res=2102.Controls:elink.
.br
:link reftype=hd res=2103.Scoring:elink.
.br
:link reftype=hd res=2104.Game menu:elink.
.br
:link reftype=hd res=2105.Options menu:elink.
.br
:link reftype=hd res=2106.Help menu:elink.
.br
:link reftype=hd res=2107.Command line:elink.
.br
:link reftype=hd res=2108.Copyright:elink.


:h1 res=2101.How to play
:i1.How to play
:ul compact.
:li.Choose New from the Game menu (Ctrl+N) to start a game. MakMan starts with three lives, shown as small MakMan figures at the top left of the maze. The score is shown at the top right.
:li.Eat all the small dots in the maze to complete the level. A new level follows.
:li.The ghosts chase MakMan. Touching a ghost costs a life. When the last life is lost the game is over.
:li.The large flashing dots are power dots. After eating one, the ghosts can be eaten for a short time and give points. The ghosts look different while they can be eaten.
:li.From time to time a fruit appears in the maze. Eat it before it disappears to get bonus points.
:li.Pause the game with Ctrl+P and stop it with Ctrl+Q.
:li.When no game is running, the high score table is shown. The best 15 scores are kept; if your score is good enough, you are asked for your name at the end of the game.
:eul.

:h1 res=2102.Controls
:i1.Controls
:p.
With the keyboard, the arrow keys left, right, up and down move MakMan. To use a joystick, choose Joystick A or Joystick B in Options - Controls; you can also calibrate it there. While a joystick is active, the keyboard does not steer MakMan.
:p.
:dl break=all.
:dt.Arrow keys
:dd.Move MakMan.
:dt.Ctrl+N
:dd.New game.
:dt.Ctrl+P
:dd.Pause / resume.
:dt.Ctrl+Q
:dd.Quit the current game.
:dt.Ctrl+X
:dd.Exit MakMan/2.
:dt.Ctrl+B
:dd.Background Run on / off.
:dt.Ctrl+F
:dd.Frame Controls - hide / show the title bar and the menu.
:dt.F1
:dd.Help.
:edl.

:h1 res=2103.Scoring
:i1.Scoring
:dl break=all.
:dt.Small dot
:dd.10 points.
:dt.Power dot
:dd.50 points.
:dt.Ghosts eaten with one power dot
:dd.200, 400, 800 and 1600 points, one after the other.
:dt.Fruit
:dd.The value appears when it is eaten and depends on the level.
:dt.Extra life
:dd.At 10000 points, then at 20000, 40000 and so on (it doubles each time).
:edl.

:h1 res=2104.Game menu
:i1.Game menu
:dl break=all.
:dt.New
:dd.Starts a new game.
:dt.Pause Game
:dd.Pauses the game, or resumes it when it is already paused. Only available while a game is running.
:dt.Quit Game
:dd.Stops the current game and returns to the high score screen. Only available while a game is running.
:dt.Exit
:dd.Closes MakMan/2.
:edl.

:h1 res=2105.Options menu
:i1.Options menu
:dl break=all.
:dt.Tile Set
:dd.Chooses the graphics of the maze and the characters&colon. Classic, 3D Look or Fufitos. The tile set can only be changed while no game is running.
:dt.Controls
:dd.Chooses Keyboard or a joystick (Joystick A or B), and calibrates a joystick.
:dt.Sound
:dd.Switches the sound effects on or off.
:dt.Priority
:dd.Sets the priority of the game (Normal, Critical or Server). Use Critical or Server only if the game runs unevenly on a busy system.
:dt.Language
:dd.Changes the language of the menus and of this help (English, Espanol, Nederlands, Deutsch, Francais, Italiano).
:dt.Background Run
:dd.When switched off, the game pauses automatically when the window loses the focus.
:dt.Frame Controls
:dd.Hides or shows the title bar and the menu. Press Ctrl+F again to show them again.
:dt.Save Settings on Exit
:dd.When checked, which is the default, your settings are saved in MAKMAN.INI when you exit. The high scores are always saved.
:edl.

:h1 res=2106.Help menu
:i1.Help menu
:dl break=all.
:dt.Help index
:dd.Shows the index of this help.
:dt.General help
:dd.Shows the general help, starting with the first topic.
:dt.Using help
:dd.Explains how to use the help window.
:dt.About MakMan/2
:dd.Shows version and author information.
:edl.

:h1 res=2107.Command line
:i1.Command line
:p.
MakMan/2 uses GPI graphics by default. A parameter on the command line selects the graphics mode&colon.
:dl break=all.
:dt.makman
:dd.GPI graphics (default, recommended).
:dt.makman gpi
:dd.The same as above.
:dt.makman dive
:dd.DIVE graphics. Needs a DIVE-capable display driver.
:edl.

:h1 res=2108.Copyright
:i1.Copyright
:p.
MakMan/2 version 1.1
:p.
Copyright (C) 1995 Markellos J. Diorinos. Open Watcom port and enhancements, 2026.
:p.
Released as open source under the GNU General Public License version 3. See doc\License.txt.
:p.
This software is provided as is, without warranty of any kind.

:euserdoc.
