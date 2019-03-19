/*
 * seg7.c: Communication functions with the TiM1637 chip used with the Groove 4-digit 7-segment display.
 *
 * Created by Zhao Zhang for ECE 367 labs at UIC, fall 2016.
 *
 * TiM1637 uses an I2C-like protocol, but it is not I2C-compatible. See the data sheet of TiM1637 for the
 * required timing.  It uses the same signal forms for the START, STOP and data bits of I2C, the data byte format
 * is similar, but it does not follow the packet format (address byte followed by data bytes) of I2C.
 *
 * It seems that the only practical way is to use bit-banging, as did in this program file. Note that bit-banging
 * is not CPU-efficient and should be avoided whenever possible.
 */

#include <stdint.h>
#include <stdbool.h>
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include "launchpad.h"
#include <driverlib/adc.h>
#include "ras.h"

void rasInit()
{
// Enable the ADC0 peripheral
SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
// Configure ADC0, sequencer #0

while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    { }

ADCSequenceConfigure(ADC0_BASE, 0 ,ADC_TRIGGER_PROCESSOR, 0);
// Configure the sequencer, can have multiple steps
ADCSequenceStepConfigure(ADC0_BASE,0,0,ADC_CTL_IE|ADC_CTL_CH7 );
ADCSequenceStepConfigure(ADC0_BASE,0, 1 ,ADC_CTL_IE| ADC_CTL_END| ADC_CTL_CH6);

ADCSequenceEnable(ADC0_BASE, 0);
}

