; pwmled.asm: Assembly PWM-LED functions
; Lab 7, ECE 266, Fall 2018
; Created by Zhao Zhang

; Include C header files
                .cdecls "stdint.h","stdbool.h","inc/hw_memmap.h","driverlib/sysctl.h","driverlib/gpio.h","driverlib/pin_map.h","driverlib/timer.h","pwmbuzzer.h"

                .text

; Field and any other declarations
TIMER0          .field  WTIMER0_BASE
PORT            .field  GPIO_PORTC_BASE
PIN_ROUTE_1     .field  GPIO_PC5_WT0CCP1

;
; void ledPwmSet(int pulsePeriod, int pulseWidthRed, int pulseWidthGreen, int pulseWidthBlue)
;
; Set color of the on-board LED by setting the intensity of the primary colors
;
                .asmfunc
pwmbuzzerSet       PUSH    {lr, r1, r0}

                ; Set the period and duty cycle length for the read sub-LED
                ;   call TimerLoadSet(TIMER0, TIMER_B, pulsePeriod)
                ;   call TimerMatchSet(TIMER0, TIMER_B, pulsePeriodRed)
                ;   Note that r0, r1, r2 each holds a pwm_t type, with
                LDR     r0, TIMER0                  ; r0 = TIMER0
                MOV     r1, #TIMER_B                ; r1 = TIMER_B
                LDR     r2, [sp, #0]                ; r2 = pulsePeriod (pushed r0 in stack)
                BL      TimerLoadSet                ; call TimerLoadSet

                LDR     r0, TIMER0                  ; r0 = TIMER0
                MOV     r1, #TIMER_B                ; r1 = TIMER_B
                LDR     r2, [sp, #4]                ; r2 = pulseWidthRed (pushed r1 in stack)
                BL      TimerMatchSet



                ADD     sp, #8                     ; release the stack space for r3, r2, r1, r0
                POP     {pc}
                .endasmfunc

