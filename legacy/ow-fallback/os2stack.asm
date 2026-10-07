; os2stack.asm
; Provides a STACK-class segment so the OS/2 LX loader gets a valid
; e32_ss in the EXE header.  Without this, wlink sets e32_ss=0 and
; OS/2 returns ERROR_INVALID_STACKSEG (SYS0189) before calling the
; entry point.  The actual runtime stack size is set by OPTION STACK
; in the makefile link step.

        .386

STACK   SEGMENT para stack 'STACK'
        DB 4096 DUP (0)
STACK   ENDS

        END
