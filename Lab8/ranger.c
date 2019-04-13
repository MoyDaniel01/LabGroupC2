

#include <stdint.h>
#include <stdbool.h>
#include <ranger.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>
#include <driverlib/timer.c>

#define	PORT			GPIO_PORTB_BASE
#define PIN			    GPIO_PIN_3
#define PERIPH			SYSCTL_PERIPH_GPIOB
#define TPERIPH         SYSCTL_PERIPH_TIMER3
#define TBASE           TIMER3_BASE

void rangerInit() {
    SysCtlPeripheralEnable(TPERIPH);
    SysCtlPeripheralEnable(PERIPH);
    GPIOPinTypeTimer(PORT, PIN);
    GPIOPinConfigure(GPIO_PB3_T3CCP1);
    TimerConfigure(TBASE,(TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_TIME_UP) );
    TimerControlEvent(TBASE, TIMER_B, TIMER_EVENT_BOTH_EDGES);
    TimerEnable(TBASE, TIMER_B);
}

 void sendStartPulse () {
    GPIOPinTypeGPIOOutput(PORT, PIN);
    GPIOPinWrite(PORT,PIN,0);
    waitUs(2);
    GPIOPinWrite(PORT,PIN,PIN);
    waitUs(5);
    GPIOPinWrite(PORT,PIN,0);
    GPIOPinTypeTimer(PORT, PIN);
    GPIOPinConfigure(GPIO_PB3_T3CCP1);
    TimerIntClear(TBASE,TIMER_CAPB_EVENT);
}
