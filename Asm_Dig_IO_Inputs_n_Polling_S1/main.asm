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

init:
			bis.b	#BIT0, &P1DIR			; Set P1.0 as an output. P1.0 = LED
			bic.b	#BIT0, P1OUT			; Set initial value of LED1 to 0

			bic.b	#BIT1, &P4DIR			; Set P4.1 as an input. P4.1 = S1
			bis.b	#BIT1, &P4REN			; Enable pull up/down resistor on P4.1
			bis.b	#BIT1, &P4OUT			; Make the resistor a pull up

			bic.b	#LOCKLPM5, &PM5CTL0		; Disable Digital I/O low power default

main:

poll_S1:
			bit.b	#BIT1, &P4IN			; Test p4.1 if > 0 , no press and Z=0
			jnz		poll_S1

toggle_LED1:
			xor.b	#BIT0, &P1OUT			; toggle P1.1 by XOR'ing it with a 1

			mov.w	#0FFFFh, R4				; Delay loop

delay:
			dec.w	R4
			jnz		delay

			jmp 	main
                                            

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
            
