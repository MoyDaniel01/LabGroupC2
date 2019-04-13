
				.cdecls "stdint.h","stdbool.h","inc/hw_memmap.h","driverlib/pin_map.h","driverlib/sysctl.h","driverlib/gpio.h","driverlib/timer.h", "Ranger.h"

                .text
				.global rangerDetect

Periph  .field     SYSCTL_PERIPH_TIMER3
PeriphB .field     SYSCTL_PERIPH_GPIOB
Event   .field 	   TIMER_CAPB_EVENT
Base    .field     TIMER3_BASE
Port    .field     GPIO_PORTB_BASE
Speed   .field 	   170
Freq    .field     50000


rangerDetect


				PUSH {lr}


				BL sendStartPulse

first_take	LDR r0 , Base
				MOV r1, #0;
				BL  TimerIntStatus
				CMP r0 , #0
				BEQ first_take

				LDR  r0, Base
				MOV r1, #TIMER_B
				BL   TimerValueGet
				PUSH {r0}

				LDR r0, Base
				LDR r1,Event
				BL TimerIntClear

second_take	LDR r0 , Base
				MOV r1, #0;
				BL  TimerIntStatus
				CMP r0 , #0
				BEQ second_take

				LDR  r0, Base
		       	MOV r1, #TIMER_B

				BL   TimerValueGet
				PUSH {r0}

				LDR r0, Base
				MOV r1, #TIMER_B
				BL TimerIntClear

				POP{r1,r0}

				SUB r0, r0,r1

				LDR r1, Speed
				MUL r0 , r0, r1
				LDR r1, Freq
				UDIV r0, r0, r1;



				POP {PC}




