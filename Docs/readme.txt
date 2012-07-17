MAKMAN/2
========
An infamous P*cMan clone, named after it's stupendous author!
After tedious beta testing, we've finally reached v1.0!

-------
License
-------

<MAKMAN IS NOW FREEWARE UNDER THE GNU GPL LICENSE>

--------
Features
--------
+ original P*cMan sounds
+ 18 levels ( 9 field designs, each with 2 difficulty levels)
+ multiple sprite librarys and the ability to create your own sprites
+ DIVE and PM support
+ high score tracking

----------
Known Bugs
----------
- the startup music brings the machine to a halt
- If the program starts off-screen, use Alt+F7 to move it in screen
  and exit the program (thereby saving the new position)



-------
Install
-------

Just unpack it all to some directory (like X:\games\makman).
The bitmap sets are contained in respective directories
(3dtiles for 3D look bitmaps, tiles for the classics e.t.c.)

Remember to use -d while unziping and to use a decent unzip programm
(like InfoZIP's zip/unzip) since not all programs support long filenames and
extended attributes. The early version of PKUNZIP for OS/2 arent capable of
long filenames and EAs.

Version 1.0 no longer needs to be installed on a HPFS drive. FAT drives will
do too.

-----------------
Your own tilesets
-----------------

All you need to create your own tilesets is OS/2 ( and I suppose you allready
have that ). You can take one of the two existing tilesets (classic/3D/new) and
simply edit the tiles with the OS/2 icon editor. Voila!

One common palette is used for all bitmaps which is loaded from the file
makman.pal (each tileset has its own makman.pal). Again, you can create and
save your own palette using the OS/2 icon editor.

The same applies for the sounds too (they can be edited with MMPM/2).
If the dot sound is too long for your hardware configuration (i.e. makes
the game jerky) try replacing dot.wav with dot_short.wav (also included).

-----
Usage
-----

Launching
---------
From command line or WPS object, all the same to me... :>

Oh yes, two parameters are recognized:
 'makman dive' uses the DIVE graphics output engine
 'makman gpi' uses the GPI/PM output engine which is the default.

Make sure that the working directory is set to that where the exe resides,
otherwise MakMan won't be able to find the icons/sound.

Game
----
You may start a new game by clicking on ...new or pressing F2!

Options
-------
Tile Set->
  you may select between the two alternative tile sets
  (i'm still waiting for your designs).
  The tile set can not be changed while you're playing
Controls->
  Select between Keyboard, Joystick A or B.
  Joysticks are available only if detected.
  The IBM joystick driver is required.
  I noticed that the calibration values returned
  by the driver weren't correct for my Gravis Analog
  Joystick, so I provided a little calibration utility
  that simple reads the value of the joystick when it's
  resting.
  If you notice that your pacman is acting by itself, 
  calibrate your joystick.
Sound->
  can be turned on or off.
  If you have PROBLEMS (or no MMPM2 installed)
  try setting the sound to OFF before starting
  a new game.
Priority->
  Set's the priority of the game thread (ONLY!).
  Usefull if you have other processes on the normal
  priority level (like watchcat) that make MakMan
  a bit jerky.

Help
----
You're on your own. 
What did you expect anyway??



Keep in touch,

Markellos J. Diorinos

e-mail    : markellos@artlogic.gr
snailmail : N.Plastira 19, 54250 Thessaloniki, Greece
            Haagstr. 17 #110, 91054 Erlangen, Germany

--------
history:
--------

ver 1.00 :
    + MakMan is now installable on a FAT drive
    + a new tileset is included (newtiles - foufitos)
    + 9 designs and 18 levels
    + various bugfixes

ver 0.80 :
    + saves/restores all parameters
    + highscore table
    + changed thread distribution and usage
    + many small bugfixes
    + pause game when window focus lost
    + now using IBM VisualAge C++ 3.0


ver 0.60 :
    + now saves/restores window position
    + blue palette fixed for 65K/16M modes
      for both DIVE and GPI modes
    + fixed a small bug in Joystick driver detection
    + never released for the public


ver 0.41 :
    + fixed some faulty field designs
      that would play after eating all dots
    + fixed window positioning/activation


ver 0.40 :
    + introduction of the Sound engine using MMPM/2
    + first try on a high-score table
    + priority change for the game thread
    + Joystick support


ver 0.20 :
    + Speed up GPI Graphics Engine
      which is now the default output method
    + added 'dive' parameter to instruct MakMan
      to use the DIVE output engine
    + SMVDD.SYS is no longer part of the distribution package
      (since DIVE is no longer required)


ver 0.10 :
    + Added PM Window in the program
    + Change DIVE code to use DIVE.DLL (no more direct memory access)
    + added 'gpi' command line switch and GPI Bitbliting alternatively
      to DIVE
    + some internal tidying up
    + compiled with MetaWare High C/C++
    + source is no longer part of the distribution package
      ( though available at no cost to anyone who cares )
    + WatchCat used for debug output
      (you shouldn't need watchcat, but if found, a few status
       messages are send to the watchcat debuging module)


ver 0.03 :
    - initial pre-release of MakMan/2 with BC++ 1.0 for OS/2
