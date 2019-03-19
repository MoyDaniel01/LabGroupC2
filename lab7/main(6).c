/*
 * main.c: Starter code for Lab 7, Spring 2019
 *
 * Created by Zhao Zhang
 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "launchpad.h"
#include "ras.h"
#include "pwmled.h"
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/adc.h>
//#include "pwmbuzzer.h"
uint32_t data[2]={0,0};
// LED-related constant
#define LED_PWM_PERIOD          5000
#define LED_MAX_PULSE_WIDTH     100
#define BUZZER_PWM_PERIOD       5000
#define BUZZER_MAX_PULSE_WIDTH  100

/*
 * Task 1: Play a sine pattern on LED
 */

typedef struct
{
    int pwmPeriod;              // PWM period for LED
    int maxPulseWidth;          // maximum pulse width
} LedState_t;
typedef struct
{ int pwmPeriodBuzzer;
  int maxPulseWidthBuzzer;
} BuzzerState_t;

static LedState_t led =
        { LED_PWM_PERIOD /* PWM Period */, LED_MAX_PULSE_WIDTH *.4 /* Multiply factor */};

// A sine function that uses degree as input. It converts degree to radian and then
// calls the sin() function of the C library.
static BuzzerState_t buzzer = { BUZZER_PWM_PERIOD /* PWM Period */, BUZZER_MAX_PULSE_WIDTH *.4 /* Multiply factor */};
static inline double sine(uint16_t degree)
{
    double radian = 2 * M_PI * ((double) (degree % 360) / 360);
    return sin(radian);
}

// LED playing callback function
void callbackLedPlay(uint32_t time)
{
    static uint16_t angle = 0;      // the degree of angle, used for calculating sine value
    int delay = 5;                  // the callback delay in ms

    rasInput(data);
    // Calculate PWM parameters for red, blue, and green sub-LEDs using sine function.
    // Use phase shift of 60, 30, and 0 degrees for red, blue, and green
    led.maxPulseWidth=(data[0]*100)/4095;
    int pulseWidthRed = sine(angle + 72) * led.maxPulseWidth;
    int pulseWidthBlue = sine(angle + 36) * led.maxPulseWidth;
    int pulseWidthGreen = sine(angle) * led.maxPulseWidth;

    // Set the PWM parameters for the three sub-LEDs
    ledPwmSet(led.pwmPeriod, pulseWidthRed, pulseWidthBlue, pulseWidthGreen);

    // Advance the angle by one degree, so a play period is 360 * 5 = 1800 ms
    angle = (angle + 1) % 360;

    // Schedule the next callback



    schdCallback(callbackLedPlay, time + delay);
}
void callbackBuzzerPlay(uint32_t time)                    // the scheduled time
{
    uint32_t delay = 10;
    rasInput(data);
uint32_t pulsewidth= (data[0]*57333)/4095;
        // Turn the buzzer on and off alternatively
        // Adjust the time values to control the sound intensity
        switch (buzzerState)
        {
        case On:
            buzzerOff();
            buzzerState = Off;
            delay = 2988;                           // off for 2988 ms
            break;

        case Off:
            buzzerOn();
            buzzerState = On;
            delay = 200;                            // on for 12 ms
            break;
    }

    // schedule the next callback
    schdCallback(callbackBuzzerPlay, time + delay);
}
void main(void)
{
    lpInit();
    ledPwmInit();
    rasInit();

    // Schedule the first callback events for LED flashing and push button checking.
    // Those trigger callback chains. The time unit is millisecond.
    schdCallback(callbackLedPlay, 1002);

    // Loop forever
    while (true)
    {
        schdExecute();
    }
}
