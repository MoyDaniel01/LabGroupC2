/*
 *
 * buzzer.h: Header file for buzzer-related functions
 *
 * Created by Zhao Zhang
 *
 */

#ifndef PWMBUZZER_H_
#define PWMBUZZER_H_
#include <stdint.h>

// Initialize the buzzer
void pwmbuzzerInit();

// Turn off the buzzer
void pwmbuzzerSet(int x, int y);

#endif /* PWMBUZZER_H_ */
