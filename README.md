# GAME-ACTION-MakMan

Version 1.1 — A PacMan clone for OS/2 and ArcaOS.

Originally written in 1995 by Markellos J. Diorinos. This version is an
Open Watcom port with enhanced menus, keyboard shortcuts, 6-language
support, and settings persistence.

![MakMan ScreenShot](/doc/MakMan.png)

## Controls

| Input | Action |
|-------|--------|
| Ctrl+N | New Game |
| Ctrl+P | Pause / Resume |
| Ctrl+Q | Quit current game |
| Ctrl+X | Exit application |
| Ctrl+B | Background Run toggle |
| Ctrl+F | Frame Controls (borderless) toggle |
| Arrow keys | Move MakMan |

## Build Instructions

Requires Open Watcom C/C++ and the OS/2 Toolkit 4.5 headers.

```
compile-wat.cmd
```

Or directly:

```
wmake -f makefile.wat all
```

Output is placed in `bin\makman.exe`.

## Project Layout

```
src/            Source files (.cpp, .hpp, .h, .rc, .dlg, .def, .ico)
bin/            Build output (.exe, .obj, .res, .map)
doc/            Documentation (Readme.txt, Changelog.txt, License.txt)
help/           IPF help sources, one per language (built to bin/help/*.hlp)
tiles/          Classic tile graphics
newtiles/       Fufitos tile graphics
3dtiles/        3D Look tile graphics
sounds/         Game audio (WAV, MID)
legacy/         Original unmodified source kept for reference
makefile.wat    Open Watcom build file
compile-wat.cmd OS/2 CMD build script
```

## Changelog Summary

**1.1 (2026-09-10)** — Open Watcom port; Game/Options/Help menu structure;
Ctrl+N/P/Q/X/B/F accelerators; Pause Game and Quit Game items; 6-language
runtime support; Language submenu; Save Settings on Exit; Background Run;
Frame Controls toggle; online help in 6 languages; BLDLEVEL; STACKSIZE fixed to 65536.

**1.00 (1995)** — Original release by Markellos J. Diorinos. PacMan clone
for OS/2 using DIVE and GPI rendering, MMPM/2 sound, joystick support,
three tile sets, high score table.

## License

GNU GPL v3 — see [doc/License.txt](doc/License.txt)

## Authors

- Markellos J. Diorinos (original author, 1995)
- Martin Iturbide (Open Watcom port, 2026)

## Links

- https://www.os2world.com/games
- https://github.com/OS2World/GAME-ACTION-MakMan
