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

    	mov.w	#0, R4

    	inc 	R4
    	inc 	R4
    	incd 	R4
    	incd 	R4

    	dec 	R4
    	dec 	R4
    	decd 	R4
    	decd 	R4

    	mov.w	#Consts, R5

    	mov.b	@R5, R6

    	inc 	R5

    	mov.b	@R5, R7

    	inc 	R5

		mov.w	@R5, R8

    	incd 	R5

		mov.w	@R5, R9

    	jmp		main


;-------------------------------------------------------------------------------
; Memory Allocation
;-------------------------------------------------------------------------------

		.data
		.retain

Consts: .short	1234h
		.short	5678h
		.short	9ABCh

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
            
