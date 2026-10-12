# GAME-ACTION-MakMan

Version 1.3 — A PacMan clone for OS/2 and ArcaOS.

Originally written in 1995 by Markellos J. Diorinos. This version is an
Open Watcom port with enhanced menus, keyboard shortcuts, Unicode text in
12 languages (UTF-8 language files, including Japanese, Chinese, Korean,
Russian and Greek), online help, and settings persistence.

## Controls

| Input | Action |
|-------|--------|
| Ctrl+N | New Game |
| Ctrl+P | Pause / Resume |
| Ctrl+Q | Quit current game |
| Ctrl+X | Exit application |
| Ctrl+B | Background Run toggle |
| Ctrl+F | Frame Controls (borderless) toggle |
| Arrow keys | Move MakMan (default) |

The keys and the joystick are set in **Options - Key Mapping...**, a window with two pages:

- **Keyboard** - click a box and press the key for each direction.
- **Joystick** - tick *Enable Joystick*, choose Joystick A or B, click a box and press a joystick
  button or push the stick (Delete clears); *Calibrate A* / *Calibrate B* set the centre of the stick.

The keyboard and the joystick work together. The mapping is saved in `MAKMAN.INI`; the old
Options - Controls submenu is gone.

## Build Instructions

Requires Open Watcom C/C++ and the OS/2 Toolkit 4.5 headers.

```
compile-wat.cmd
```

Or directly:

```
wmake -f makefile.wat all
```

Output is placed in `bin\makman.exe`, the help files in `bin\help` and the language files in `bin\lang`.

## Project Layout

```
src/            Source files (.cpp, .hpp, .h, .rc, .dlg, .def, .ico)
bin/            Build output (.exe, .obj, .res, .map)
doc/            Documentation (Readme.txt, Changelog.txt, License.txt)
help/           IPF help sources, one per language (built to bin/help/*.hlp)
lang/           UTF-8 language files (copied next to makman.exe in bin/lang)
tiles/          Classic tile graphics
newtiles/       Fufitos tile graphics
3dtiles/        3D Look tile graphics
sounds/         Game audio (WAV, MID)
legacy/         Original unmodified source kept for reference
makefile.wat    Open Watcom build file
compile-wat.cmd OS/2 CMD build script
```

## Changelog Summary

**1.3 (2026-10-12)** — Options - Key Mapping... (keyboard keys and joystick A/B with buttons, stick directions
and calibration; replaces the Controls submenu); MMPM/2 is loaded at run time, so the game starts and
runs without sound when MMIO.DLL cannot start (it used to quit at once, before any window).

**1.2.1 (2026-10-08)** — text is drawn as UTF-8 through GPI code page 1208; the UTF-8 to UCS-2 conversion
is gone (same layer as PMUniText 0.3).

**1.2 (2026-10-07)** — Unicode support: UTF-8 language files in `lang/` (12 languages), menus and
dialogs drawn with GPI code page 1200 where the code page falls short, translated high score entry
(names stored as UTF-8), mnemonics and accelerator text for all menus, `-plainmenus` /
`-unicodemenus` switches; fixed an uninitialised ghost animation phase that could trap the game.

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
