@echo off
rem =========================================================================
rem Compile script for MakMan/2 (Open Watcom C on OS/2 / ArcaOS)
rem Run from the project root:  compile-wat.cmd
rem =========================================================================

rem Auto-detect Watcom installation (OS/2 typical paths)
if "%WATCOM%"=="" (
    if exist C:\WATCOM\binp\wpp386.exe (
        set WATCOM=C:\WATCOM
    ) else if exist C:\WATCOM2\binp\wpp386.exe (
        set WATCOM=C:\WATCOM2
    ) else if exist D:\WATCOM\binp\wpp386.exe (
        set WATCOM=D:\WATCOM
    ) else (
        echo ERROR: Watcom not found. Set WATCOM environment variable.
        exit 1
    )
)

rem Watcom OS/2 tools live in binp
if exist %WATCOM%\binp\wpp386.exe (
    set PATH=%WATCOM%\binp;%PATH%
) else (
    set PATH=%WATCOM%\bin;%PATH%
)

rem Auto-detect OS/2 Toolkit
if "%OS2TK%"=="" (
    if exist C:\OS2TK45\h\os2.h (
        set OS2TK=C:\OS2TK45
    ) else (
        echo WARNING: OS2TK not set, defaulting to C:\OS2TK45
        set OS2TK=C:\OS2TK45
    )
)

rem Environment for Open Watcom on OS/2
set PATH=%WATCOM%\bin;%PATH%
set INCLUDE=%WATCOM%\h;%OS2TK%\h;src;%INCLUDE%
set LIB=%WATCOM%\lib386;%WATCOM%\lib386\os2;%OS2TK%\lib;%LIB%
set WIPFC=%WATCOM%\wipfc

rem Make sure bin\ and bin\help\ exist (help files go next to makman.exe)
if not exist bin md bin
if not exist bin\help md bin\help

set LOGFILE=compile-wat.log

echo ========================================== > %LOGFILE%
echo MakMan/2 Build Log >> %LOGFILE%
echo Date: %DATE% Time: %TIME% >> %LOGFILE%
echo WATCOM=%WATCOM% >> %LOGFILE%
echo OS2TK=%OS2TK% >> %LOGFILE%
echo ========================================== >> %LOGFILE%
echo. >> %LOGFILE%

echo Building MakMan/2 with Open Watcom...
echo WATCOM=%WATCOM%
echo OS2TK=%OS2TK%
echo Log: %LOGFILE%
echo.

echo --- Open Watcom runtime libraries --- >> %LOGFILE%
for %%L in (clib3r.lib plib3r.lib math387r.lib emu387.lib noemu387.lib) do (
    if exist %WATCOM%\lib386\os2\%%L (echo FOUND %WATCOM%\lib386\os2\%%L >> %LOGFILE%) else (echo MISSING %%L in %WATCOM%\lib386\os2 >> %LOGFILE%)
    if exist %WATCOM%\lib386\%%L echo FOUND %WATCOM%\lib386\%%L >> %LOGFILE%
)
dir %WATCOM%\lib386\os2\*.lib >> %LOGFILE% 2>&1
echo ------------------------------------- >> %LOGFILE%

echo [CLEAN] Running wmake clean...
wmake -f makefile.wat clean >> %LOGFILE% 2>&1

set FAILED=0
echo [BUILD] Running wmake all...
wmake -f makefile.wat all >> %LOGFILE% 2>&1
if errorlevel 1 set FAILED=1

rem Show the build output on screen
type %LOGFILE%

if "%FAILED%"=="1" goto failed
if exist bin\makman.exe (
    echo.
    echo BUILD OK
    echo BUILD OK >> %LOGFILE%
    exit 0
)
:failed
echo.
echo BUILD FAILED
echo BUILD FAILED >> %LOGFILE%
exit 1
