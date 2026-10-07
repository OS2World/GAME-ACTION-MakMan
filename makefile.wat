# Makefile for MakMan/2 (Open Watcom C++ on OS/2 / ArcaOS)
# wmake 2.0.1 on ArcaOS - explicit per-file rules, prerequisites on ONE line.

BINDIR  = bin
SRCDIR  = src

!ifndef WATCOM
WATCOM  = C:\WATCOM
!endif

WIPFC   = wipfc

!ifndef OS2TK
OS2TK   = C:\OS2TK45
!endif

CC      = wpp386
LINK    = wlink
RC      = wrc

CFLAGS  = -bt=os2 -mf -5 -fpi -Oaxt -W3 -ze -d0 -i=$(OS2TK)\h -i=$(SRCDIR)

RCFLAGS = -r -bt=os2 -i=$(OS2TK)\h -i=$(SRCDIR) -i=.

LFLAGS  = system os2v2_pm option stack=65536 option start=_cstart_ option map=$(BINDIR)\makman.map

OBJS    = $(BINDIR)\pmmain.obj $(BINDIR)\pmprocs.obj $(BINDIR)\pmvars.obj $(BINDIR)\pmhelp.obj $(BINDIR)\makman.obj $(BINDIR)\makengine.obj $(BINDIR)\gpiengine.obj $(BINDIR)\diveengine.obj $(BINDIR)\tile.obj $(BINDIR)\backtile.obj $(BINDIR)\playfield.obj $(BINDIR)\sprite.obj $(BINDIR)\ghost.obj $(BINDIR)\mmpm2sound.obj

HDR     = $(SRCDIR)\pmmain.hpp $(SRCDIR)\pmvars.hpp $(SRCDIR)\pmids.hpp $(SRCDIR)\lang.h

HLPS    = $(BINDIR)\help\MakMan_en.hlp $(BINDIR)\help\MakMan_es.hlp $(BINDIR)\help\MakMan_nl.hlp $(BINDIR)\help\MakMan_de.hlp $(BINDIR)\help\MakMan_fr.hlp $(BINDIR)\help\MakMan_it.hlp

all : $(BINDIR)\makman.exe $(HLPS) .SYMBOLIC

$(BINDIR) :
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)\makman.exe : $(OBJS) $(BINDIR)\makman.res
	@echo Linking makman.exe...
	@$(LINK) $(LFLAGS) name $(BINDIR)\makman.exe file $(BINDIR)\pmmain.obj, $(BINDIR)\pmprocs.obj, $(BINDIR)\pmvars.obj, $(BINDIR)\pmhelp.obj, $(BINDIR)\makman.obj, $(BINDIR)\makengine.obj, $(BINDIR)\gpiengine.obj, $(BINDIR)\diveengine.obj, $(BINDIR)\tile.obj, $(BINDIR)\backtile.obj, $(BINDIR)\playfield.obj, $(BINDIR)\sprite.obj, $(BINDIR)\ghost.obj, $(BINDIR)\mmpm2sound.obj library os2386.lib, mmpm2.lib, plib3r.lib, clib3r.lib
	@echo Binding resources...
	@$(RC) -q -bt=os2 $(BINDIR)\makman.res $(BINDIR)\makman.exe
	@if exist $(BINDIR)\makman.exe echo BUILD OK makman

$(BINDIR)\makman.res : $(SRCDIR)\makman.rc $(SRCDIR)\pmids.hpp $(SRCDIR)\about.dlg $(SRCDIR)\highscore.dlg $(SRCDIR)\makman.ico $(BINDIR)
	@echo Compiling src\makman.rc
	@$(RC) $(RCFLAGS) -fo=$@ $(SRCDIR)\makman.rc

$(BINDIR)\pmmain.obj : $(SRCDIR)\pmmain.cpp $(HDR) $(SRCDIR)\pmkeys.hpp $(BINDIR)
	@echo Compiling src\pmmain.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\pmmain.cpp

$(BINDIR)\pmprocs.obj : $(SRCDIR)\pmprocs.cpp $(HDR) $(BINDIR)
	@echo Compiling src\pmprocs.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\pmprocs.cpp

$(BINDIR)\pmvars.obj : $(SRCDIR)\pmvars.cpp $(HDR) $(BINDIR)
	@echo Compiling src\pmvars.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\pmvars.cpp

$(BINDIR)\pmhelp.obj : $(SRCDIR)\pmhelp.cpp $(HDR) $(BINDIR)
	@echo Compiling src\pmhelp.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\pmhelp.cpp

$(BINDIR)\makman.obj : $(SRCDIR)\makman.cpp $(SRCDIR)\tile.hpp $(SRCDIR)\playfield.hpp $(SRCDIR)\sprite.hpp $(BINDIR)
	@echo Compiling src\makman.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\makman.cpp

$(BINDIR)\makengine.obj : $(SRCDIR)\makengine.cpp $(HDR) $(BINDIR)
	@echo Compiling src\makengine.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\makengine.cpp

$(BINDIR)\gpiengine.obj : $(SRCDIR)\gpiengine.cpp $(HDR) $(BINDIR)
	@echo Compiling src\gpiengine.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\gpiengine.cpp

$(BINDIR)\diveengine.obj : $(SRCDIR)\diveengine.cpp $(HDR) $(BINDIR)
	@echo Compiling src\diveengine.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\diveengine.cpp

$(BINDIR)\tile.obj : $(SRCDIR)\tile.cpp $(HDR) $(SRCDIR)\tile.hpp $(BINDIR)
	@echo Compiling src\tile.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\tile.cpp

$(BINDIR)\backtile.obj : $(SRCDIR)\backtile.cpp $(SRCDIR)\tile.hpp $(SRCDIR)\backtile.hpp $(SRCDIR)\playfield.hpp $(BINDIR)
	@echo Compiling src\backtile.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\backtile.cpp

$(BINDIR)\playfield.obj : $(SRCDIR)\playfield.cpp $(SRCDIR)\tile.hpp $(SRCDIR)\backtile.hpp $(SRCDIR)\playfield.hpp $(SRCDIR)\sprite.hpp $(BINDIR)
	@echo Compiling src\playfield.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\playfield.cpp

$(BINDIR)\sprite.obj : $(SRCDIR)\sprite.cpp $(SRCDIR)\tile.hpp $(SRCDIR)\playfield.hpp $(SRCDIR)\sprite.hpp $(BINDIR)
	@echo Compiling src\sprite.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\sprite.cpp

$(BINDIR)\ghost.obj : $(SRCDIR)\ghost.cpp $(SRCDIR)\tile.hpp $(SRCDIR)\playfield.hpp $(SRCDIR)\ghost.hpp $(SRCDIR)\sprite.hpp $(BINDIR)
	@echo Compiling src\ghost.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\ghost.cpp

$(BINDIR)\mmpm2sound.obj : $(SRCDIR)\mmpm2sound.cpp $(SRCDIR)\pmvars.hpp $(SRCDIR)\sndengine.hpp $(SRCDIR)\mmpm2sound.hpp $(BINDIR)
	@echo Compiling src\mmpm2sound.cpp
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\mmpm2sound.cpp

$(BINDIR)\help :
	@if not exist $(BINDIR)\help mkdir $(BINDIR)\help

$(BINDIR)\help\MakMan_en.hlp : help\MakMan_en.ipf $(BINDIR)\help
	@echo Compiling help\MakMan_en.ipf
	@$(WIPFC) -o $@ help\MakMan_en.ipf

$(BINDIR)\help\MakMan_es.hlp : help\MakMan_es.ipf $(BINDIR)\help
	@echo Compiling help\MakMan_es.ipf
	@$(WIPFC) -o $@ help\MakMan_es.ipf

$(BINDIR)\help\MakMan_nl.hlp : help\MakMan_nl.ipf $(BINDIR)\help
	@echo Compiling help\MakMan_nl.ipf
	@$(WIPFC) -o $@ help\MakMan_nl.ipf

$(BINDIR)\help\MakMan_de.hlp : help\MakMan_de.ipf $(BINDIR)\help
	@echo Compiling help\MakMan_de.ipf
	@$(WIPFC) -l de_DE -o $@ help\MakMan_de.ipf

$(BINDIR)\help\MakMan_fr.hlp : help\MakMan_fr.ipf $(BINDIR)\help
	@echo Compiling help\MakMan_fr.ipf
	@$(WIPFC) -l fr_FR -o $@ help\MakMan_fr.ipf

$(BINDIR)\help\MakMan_it.hlp : help\MakMan_it.ipf $(BINDIR)\help
	@echo Compiling help\MakMan_it.ipf
	@$(WIPFC) -o $@ help\MakMan_it.ipf

clean : .SYMBOLIC
	@if exist $(BINDIR)\*.obj del $(BINDIR)\*.obj >nul
	@if exist $(BINDIR)\*.res del $(BINDIR)\*.res >nul
	@if exist $(BINDIR)\*.exe del $(BINDIR)\*.exe >nul
	@if exist $(BINDIR)\*.map del $(BINDIR)\*.map >nul
	@if exist $(BINDIR)\help\*.hlp del $(BINDIR)\help\*.hlp >nul
	@echo Clean complete
