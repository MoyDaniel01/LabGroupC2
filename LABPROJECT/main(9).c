

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "launchpad.h"
#include "pwmled.h"
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/adc.h>
#include "pwmbuzzer.h"
#include <stdio.h>

typedef enum {On, Off} OnOff_t;
static OnOff_t buzzerState = On;
int note[12][9];
void initNote(int note[12][9]){

//octave 0
note[0][0]=3058104;//C
note[1][0]=2886836;//C#
note[2][0]=2724795;//D
note[3][0]=2570694;//D#
note[4][0]=2427184;//E
note[5][0]=2290426;//F
note[6][0]=2162630;//F#
note[7][0]=2040816;//G
note[8][0]=1926040;//G#
note[9][0]=1818182;//A
note[10][0]=1715854;//A#
note[11][0]=1619695;//B

//octave 1
note[0][1]=1529052;//C
note[1][1]=1443001;//C#
note[2][1]=1362027;//D
note[3][1]=1285678;//D#
note[4][1]=1213592;//E
note[5][1]=1145475;//F
note[6][1]=1071811;//F#
note[7][1]=1020408;//G
note[8][1]=963206;//G#
note[9][1]=909091;//A
note[10][1]=858074;//A#
note[11][1]=809848;//B

//octave 2
note[0][2]=764456;//C
note[1][2]=721542;//C#
note[2][2]=681051;//D
note[3][2]=642822;//D#
note[4][2]=606745;//E
note[5][2]=572692;//F
note[6][2]=540546;//F#
note[7][2]=510209;//G
note[8][2]=481575;//G#
note[9][2]=454545;//A
note[10][2]=429034;//A#
note[11][2]=404953;//B

//octave 3
note[0][3]=382234;//C
note[1][3]=360776;//C#
note[2][3]=340530;//D
note[3][3]=321419;//D#
note[4][3]=303380;//E
note[5][3]=286352;//F
note[6][3]=270270;//F#
note[7][3]=255102;//G
note[8][3]=240790;//G#
note[9][3]=227273;//A
note[10][3]=214519;//A#
note[11][3]=202478;//B

//octave 4
note[0][4]=191110;//C
note[1][4]=180388;//C#
note[2][4]=170265;//D
note[3][4]=160705;//D#
note[4][4]=151685;//E
note[5][4]=143172;//F
note[6][4]=135139;//F#
note[7][4]=127551;//G
note[8][4]=120395;//G#
note[9][4]=113636;//A
note[10][4]=107259;//A#
note[11][4]=101239;//B

//octave 5
note[0][5]=95557;//C
note[1][5]=90192;//C#
note[2][5]=85131;//D
note[3][5]=80354;//D#
note[4][5]=75844;//E
note[5][5]=71586;//F
note[6][5]=67568;//F#
note[7][5]=63776;//G
note[8][5]=60197;//G#
note[9][5]=56818;//A
note[10][5]=53629;//A#
note[11][5]=50619;//B

//octave 6
note[0][6]=47778;//C
note[1][6]=45097;//C#
note[2][6]=42566;//D
note[3][6]=40176;//D#
note[4][6]=37922;//E
note[5][6]=35793;//F
note[6][6]=33784;//F#
note[7][6]=31888;//G
note[8][6]=30098;//G#
note[9][6]=28409;//A
note[10][6]=26815;//A#
note[11][6]=25310;//B

//octave 7
note[0][7]=23889;//C
note[1][7]=22548;//C#
note[2][7]=21283;//D
note[3][7]=20088;//D#
note[4][7]=18961;//E
note[5][7]=17897;//F
note[6][7]=16897;//F#
note[7][7]=15944;//G
note[8][7]=15040;//G#
note[9][7]=14205;//A
note[10][7]=13407;//A#
note[11][7]=12655;//B

//octave 8
note[0][8]=11945;//C
note[1][8]=11274;//C#
note[2][8]=10641;//D
note[3][8]=10044;//D#
note[4][8]=9480;//E
note[5][8]=8948;//F
note[6][8]=8446;//F#
note[7][8]=7972;//G
note[8][8]=7525;//G#
note[9][8]=7102;//A
note[10][8]=6704;//A#
note[11][8]=6327;//B
}

void callbackBuzzerPlay(uint32_t time)                    // the scheduled time
{
    uint32_t delay = 10;

static char userinput=0;//note or octave input by user using keyboard
static uint32_t Oct=4;//starting octave
static uint32_t play=0;//note to be played in

scanf("%c",&userinput);

if (userinput <= 8){
    Oct=userinput;
}
if (userinput=='c'){
    play=note[0][Oct];
}
else if (userinput=='C'){
    play=note[1][Oct];
}
else if (userinput=='d'){
    play=note[2][Oct];
}
else if (userinput=='D'){
    play=note[3][Oct];
}
else if (userinput=='e'){
    play=note[4][Oct];
}
else if (userinput=='f'){
    play=note[5][Oct];
}
else if (userinput=='F'){
    play=note[6][Oct];
}
else if (userinput=='g'){
    play=note[7][Oct];
}
else if (userinput=='G'){
    play=note[8][Oct];
}
else if (userinput=='a'){
    play=note[9][Oct];
}
else if (userinput=='A'){
    play=note[10][Oct];
}
else if (userinput=='B'){
    play=note[11][Oct];
}
else{
    play=0;
}
switch (buzzerState)
        {
        case On:
            pwmbuzzerSet(0,0);//sets volume and pitch to 0
            buzzerState = Off;
            delay = 250;
            break;

        case Off:
            pwmbuzzerSet(play,1000);//sets volume and pitch based on the note pressed and octive active
            buzzerState = On;
            delay = 250;
            break;
    }

    // schedule the next callback
    schdCallback(callbackBuzzerPlay, time + delay);
}


void main(void)
{
    lpInit();
    pwmbuzzerInit();
    initNote(note);
    // Schedule the first callback events for LED flashing and push button checking.
    // Those trigger callback chains. The time unit is millisecond.

    schdCallback(callbackBuzzerPlay,1002);

    // Loop forever
    while (true)
    {
        schdExecute();
    }
}
