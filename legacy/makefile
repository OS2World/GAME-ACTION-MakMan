# makefile
# Created by IBM WorkFrame/2 MakeMake at 2:19:34 on 21 Jan 1996
#
# The actions included in this make file are:
#  Compile::Resource Compiler
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind

.SUFFIXES: .cpp .obj .rc .res 

.all: \
    F:\WORK\makman\makman.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

.cpp.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /O /Fo"%|dpfF.obj" /C %s

F:\WORK\makman\makman.exe: \
    F:\WORK\makman\tile.obj \
    F:\WORK\makman\backtile.obj \
    F:\WORK\makman\diveengine.obj \
    F:\WORK\makman\ghost.obj \
    F:\WORK\makman\gpiengine.obj \
    F:\WORK\makman\makengine.obj \
    F:\WORK\makman\makman.obj \
    F:\WORK\makman\mmpm2sound.obj \
    F:\WORK\makman\playfield.obj \
    F:\WORK\makman\pmhelp.obj \
    F:\WORK\makman\pmmain.obj \
    F:\WORK\makman\pmprocs.obj \
    F:\WORK\makman\pmvars.obj \
    F:\WORK\makman\sprite.obj \
    F:\WORK\makman\makman.res \
    {$(LIB)}mmpm2.lib \
    {$(LIB)}makman.def
    @echo " Link::Linker "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /de /br /noe"
     /FeF:\WORK\makman\makman.exe 
     mmpm2.lib 
     CPPOPA3.OBJ 
     makman.def
     F:\WORK\makman\tile.obj
     F:\WORK\makman\backtile.obj
     F:\WORK\makman\diveengine.obj
     F:\WORK\makman\ghost.obj
     F:\WORK\makman\gpiengine.obj
     F:\WORK\makman\makengine.obj
     F:\WORK\makman\makman.obj
     F:\WORK\makman\mmpm2sound.obj
     F:\WORK\makman\playfield.obj
     F:\WORK\makman\pmhelp.obj
     F:\WORK\makman\pmmain.obj
     F:\WORK\makman\pmprocs.obj
     F:\WORK\makman\pmvars.obj
     F:\WORK\makman\sprite.obj
<<
    rc.exe F:\WORK\makman\makman.res F:\WORK\makman\makman.exe

F:\WORK\makman\makman.res: \
    F:\WORK\makman\makman.rc \
    {$(INCLUDE)}highscore.dlg \
    {$(INCLUDE)}about.dlg \
    tiles\makman.ico \
    {$(INCLUDE)}PmIDs.hpp \
    {$(INCLUDE)}PmMain.hpp

F:\WORK\makman\sprite.obj: \
    F:\WORK\makman\sprite.cpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}sprite.hpp

F:\WORK\makman\pmvars.obj: \
    F:\WORK\makman\pmvars.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp

F:\WORK\makman\pmprocs.obj: \
    F:\WORK\makman\pmprocs.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmids.hpp \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}PmHelp.hpp \
    {F:\WORK\makman;$(INCLUDE);}joyos2.h \
    {F:\WORK\makman;$(INCLUDE);}pmkeys.hpp

F:\WORK\makman\pmmain.obj: \
    F:\WORK\makman\pmmain.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmids.hpp \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}PmHelp.hpp \
    {F:\WORK\makman;$(INCLUDE);}joyos2.h \
    {F:\WORK\makman;$(INCLUDE);}pmkeys.hpp

F:\WORK\makman\pmhelp.obj: \
    F:\WORK\makman\pmhelp.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp

F:\WORK\makman\playfield.obj: \
    F:\WORK\makman\playfield.cpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}backtile.hpp \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}sprite.hpp

F:\WORK\makman\mmpm2sound.obj: \
    F:\WORK\makman\mmpm2sound.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}mmpm2sound.hpp

F:\WORK\makman\makman.obj: \
    F:\WORK\makman\makman.cpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}sprite.hpp \
    {F:\WORK\makman;$(INCLUDE);}makman.hpp

F:\WORK\makman\makengine.obj: \
    F:\WORK\makman\makengine.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmids.hpp \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}ghost.hpp \
    {F:\WORK\makman;$(INCLUDE);}sprite.hpp \
    {F:\WORK\makman;$(INCLUDE);}PmHelp.hpp \
    {F:\WORK\makman;$(INCLUDE);}makman.hpp \
    {F:\WORK\makman;$(INCLUDE);}joyos2.h \
    {F:\WORK\makman;$(INCLUDE);}levels.inc

F:\WORK\makman\gpiengine.obj: \
    F:\WORK\makman\gpiengine.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}pmids.hpp

F:\WORK\makman\ghost.obj: \
    F:\WORK\makman\ghost.cpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp \
    {F:\WORK\makman;$(INCLUDE);}sndengine.hpp \
    {F:\WORK\makman;$(INCLUDE);}ghost.hpp \
    {F:\WORK\makman;$(INCLUDE);}sprite.hpp

F:\WORK\makman\diveengine.obj: \
    F:\WORK\makman\diveengine.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}pmids.hpp

F:\WORK\makman\backtile.obj: \
    F:\WORK\makman\backtile.cpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h \
    {F:\WORK\makman;$(INCLUDE);}backtile.hpp \
    {F:\WORK\makman;$(INCLUDE);}playfield.hpp

F:\WORK\makman\tile.obj: \
    F:\WORK\makman\tile.cpp \
    {F:\WORK\makman;$(INCLUDE);}pmMain.hpp \
    {F:\WORK\makman;$(INCLUDE);}pmVars.hpp \
    {F:\WORK\makman;$(INCLUDE);}makEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}VideoEngine.hpp \
    {F:\WORK\makman;$(INCLUDE);}tile.hpp \
    {F:\WORK\makman;$(INCLUDE);}debug.h
