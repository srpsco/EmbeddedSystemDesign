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

	mov.w	#Block1, R4	; put the value 2000h into R6 to be used asa an address

	mov.w	@R4+, R5	; copy data at addr held in R4 into R5, then R4+2-->R4
    mov.w	@R4+, R6	; copy data at addr held in R4 into R6, then R4+2-->R4
    mov.w	@R4+, R7	; copy data at addr held in R4 into R7, then R4+2-->R4

    mov.b	@R4+, R8	; copy data at addr held in R4 into R8, then R4+1-->R4
	mov.b	@R4+, R9	; copy data at addr held in R4 into R9, then R4+1-->R4
	mov.b	@R4+, R10	; copy data at addr held in R4 into R10, then R4+1-->R4

	jmp 	main

;-------------------------------------------------------------------------------
; Memory Allocation
;-------------------------------------------------------------------------------

		.data	; allocate vars in data memory
		.retain	; keep these statements even if not used

Block1: .short 1122h, 3344h, 5566h, 7788h, 99AAh

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
            
