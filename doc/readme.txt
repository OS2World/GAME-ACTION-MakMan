MakMan/2 for OS/2 - Version 1.1
================================


OVERVIEW
--------
MakMan/2 is a full color, full sound PacMan clone for OS/2 and ArcaOS,
originally written in 1995 by Markellos J. Diorinos. This version is an
Open Watcom port with enhanced menus, keyboard shortcuts, six-language
support, online help and settings persistence. MakMan/2 is free software
released under the GNU General Public License (see LICENSE below).

Features:
  - 18 levels with 9 different maze designs
  - 3 different tile sets (Classic, 3D Look, Fufitos), with the ability
    to design your own
  - MMPM/2 sound
  - High score tracking (best 15 scores)
  - Joystick support (keyboard or joystick A / B, with calibration)
  - GPI and DIVE graphics modes
  - Menus and online help in English, Espanol, Nederlands, Deutsch,
    Francais and Italiano


HOW TO PLAY
-----------
Select Game > New (Ctrl+N) to start a new game.
Guide MakMan through the maze eating all dots while avoiding ghosts.
Eat the large flashing dots to temporarily allow eating the ghosts.
Fruit appears from time to time for bonus points.

Scoring:
  Small dot               10 points
  Large dot               50 points
  Ghosts (one power dot)  200, 400, 800, 1600 points in turn
  Extra life              at 10000 points, then 20000, 40000, ...


CONTROLS
--------
  Ctrl+N        New Game
  Ctrl+P        Pause / Resume
  Ctrl+Q        Quit current game
  Ctrl+X        Exit application
  Ctrl+B        Toggle Background Run
  Ctrl+F        Toggle Frame Controls (borderless mode)
  F1            Help
  Arrow keys    Move MakMan


MENUS
-----
  Game > New            Start a new game (Ctrl+N)
  Game > Pause Game     Pause or resume (Ctrl+P)
  Game > Quit Game      Stop current game (Ctrl+Q)
  Game > Exit           Close the application (Ctrl+X)

  Options > Tile Set    Choose tile graphics (Classic, 3D, Fufitos)
  Options > Controls    Choose input device (Keyboard, Joystick A/B)
  Options > Sound       Enable or disable sound
  Options > Priority    Set thread priority
  Options > Language    Switch display language (menus and help)
  Options > Background Run  Keep game running when window loses focus
  Options > Frame Controls  Hide/show title bar and menu (Ctrl+F)
  Options > Save Settings on Exit   On by default

  Help > Help index / General help / Using help   Online help
  Help > About MakMan/2...  Version and author information


GRAPHICS MODES
--------------
  The game supports two graphics modes selected at startup:
    MakMan          Use GPI rendering (default, recommended)
    MakMan gpi      Same as above
    MakMan dive     Use DIVE rendering (requires DIVE-capable display driver)


REQUIREMENTS
------------
  ArcaOS 5.x or OS/2 Warp 4
  At least 800x600 screen resolution, about 1 MB of disk space
  MMPM/2 for sound (included with ArcaOS and OS/2 Warp)
  DIVE-capable display driver (optional, for DIVE mode only)


FILE LIST
---------
  bin\makman.exe    The game executable
  bin\help\         Online help, one file per language (MakMan_en.hlp, ...)
  doc\readme.txt    This file
  doc\Changelog.txt Change history
  doc\License.txt   GNU General Public License version 3
  tiles\            Classic tile graphics
  newtiles\         Fufitos tile graphics
  3dtiles\          3D Look tile graphics
  sounds\           Game sound files (WAV, MID)
  help\             Help sources (.ipf), one per language
  src\              Source code

  The tiles, newtiles, 3dtiles and sounds folders must be in the folder
  the game is started from (normally next to makman.exe).


SOURCE CODE AND BUILD INSTRUCTIONS
----------------------------------
  The source code is in the src folder (C++, OS/2 PM and MMPM/2). The
  sounds and bitmaps are not part of the sources; they are in the folders
  listed above. Building requires Open Watcom C/C++ (including wipfc)
  and the OS/2 Toolkit 4.5 headers.

    compile-wat.cmd

  Or directly:

    wmake -f makefile.wat all

  Output is placed in bin\makman.exe and bin\help\MakMan_xx.hlp.

  A note from the original author: this was his first PM/MMPM program,
  so do not assume that the techniques used are always the best. The
  sound engine was coded overnight and is still a bit messy.


HISTORY
-------
  MakMan/2 1.0 (1995) was released by Markellos J. Diorinos as shareware
  for OS/2 (PM and DIVE). The source code was later released under the
  GNU GPL. Version 1.1 (2026) is the Open Watcom port. See
  doc\Changelog.txt for details.


LICENSE
-------
  MakMan/2 is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details. The full text is in
  doc\License.txt.


AUTHORS
-------
  Markellos J. Diorinos  (original author, 1995)
  Martin Iturbide        (Open Watcom port and enhancements, 2026)
