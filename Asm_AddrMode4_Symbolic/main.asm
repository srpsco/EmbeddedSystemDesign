;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main:

	mov.w 	Const1, R4	; copy contents at address label Const1 into R4
	mov.w 	R4, Var1	; copy contents from R4 into address label Var1

	mov.w	Const2, R5	; copy contents at address label Const2h into R5
	mov.w	R5, Var2	; copy contents from R5 into address label Var2

;-------------------------------------------------------------------------------
; Memory Allocation
;-------------------------------------------------------------------------------

	.data		; go to data memory (2000h)
	.retain		; keep this section even if not used

Const1:	.short	1234h 	; init 1st word to 1234h
Const2: .short	0CAFEh	; init 2nd word to CAFEh

Var1: 	.space 2		; reserve 3rd word
Var2: 	.space 2		; reserve 4th word

                                            

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
