
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inc/hw_memmap.h>
#include <inc/hw_adc.h>
#include <driverlib/pin_map.h>
#include <driverlib/adc.h>
#include <driverlib/sysctl.h>
#include "driverlib/gpio.h"
#include "launchpad.h"
#include "seg7.h"
#include "seg7digit.h"
#include "Ranger.h"

uint32_t convert = 1;
extern void
stopWatchIncrement(seg7Display_t* seg7Display);
extern void
stopWatchReset(seg7Display_t* seg7Display);
extern void
stopWatchMax(seg7Display_t* seg7Display);
extern void
stopWatchMaxFt(seg7Display_t* seg7Display);


enum {
    Reset, Run, Pause
}  sysState = Pause;
seg7Display_t seg7Display = {
    0, 10, 0, 10, 1
};
void
stopWatchUpdate(uint32_t time)
{
    seg7DigitUpdate(&seg7Display);
    schdCallback(stopWatchUpdate, time + 10);
}


void
checkRanger(uint32_t time)
{
    int code = pbRead();
    uint32_t ft = 0;
    uint32_t in = 0;
    uint32_t mm = 0;
    uint32_t delay;
    sendStartPulse();
    mm = rangerDetect();
    in = mm / 25.4;
    ft = in / 12;
    in = in - (ft * 12);
    switch (code) {
        case 1:
            if(sysState == Pause){
                sysState = Run;
            }
            else if(sysState == Run){
                sysState = Pause;
                stopWatchReset(&seg7Display);
            }

            delay = 250;
            break;

        case 2:

            if(sysState == Run){
                if(convert == 1){
                    convert = 0;
                }
                else if(convert == 0){
                    convert = 1;
                }
            }

            delay = 250;
            break;
        default:
            delay = 50;
        }
    if(sysState == Run){
        if(convert == 0){
            seg7Display.colon = 0;
                if(mm > 9999){
                    stopWatchMax(&seg7Display);
                }
                else{
                    seg7Display.d1 = mm % 10;
                    seg7Display.d2 = (mm / 10) %10;
                    seg7Display.d3 = (mm / 100) % 10;
                    seg7Display.d4 = mm / 1000;
                }
            }
            else if(convert == 1){
                seg7Display.colon = 1;
                if(ft > 99){
                    stopWatchMaxFt(&seg7Display);
                }
                else{
                    seg7Display.d1 = in % 10;
                    seg7Display.d2 = in / 10;
                    seg7Display.d3 = ft % 10;
                    seg7Display.d4 = ft / 10;
                }
            }
    }
    schdCallback(checkRanger, time + delay);
}


int main(void)
{
    lpInit();
    seg7Init();
    rangerInit();

    seg7DigitUpdate(&seg7Display);
    schdCallback(stopWatchUpdate, 1000);
    schdCallback(checkRanger, 1010);

    while (true) {
        schdExecute();
    }
}
