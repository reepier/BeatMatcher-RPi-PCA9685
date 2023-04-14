#pragma once

#include "constant.h"
#include "wiringPi.h"

/*  
    Uncomment the following line to compile a DEBUG version (no DMX Rx function,
    Serial plotter activated). Comment out the following line to reverse to
    "NORMAL MODE" (DMX Rx activated, Serial plotter unavailabe)
*/
#define FAKEMUSIC

/** TODO
 * - Delete this module if it really is as useless as it looks
*/

// TODO : Move this class elsewhere
class LoopControler{
    public :
    unsigned long cpt = 0;
    bool first_loop = true;
    unsigned long t_previous_ms = 0;
    unsigned long t_current_ms = millis();
    unsigned long t_next_ms = 0;
    unsigned long loop_duration_ms = 0;

    void start_new_frame(){
        t_previous_ms = t_current_ms;
        t_current_ms = millis();
        t_next_ms = t_current_ms + 1000/FRATE;

        loop_duration_ms = t_current_ms - t_previous_ms;
    }
    void wait_for_next(){
        while(micros() < 1000*t_next_ms) {delayMicroseconds(100); } // wait for the next frame
        if (first_loop) first_loop = false;
        cpt++;
    }
};


void init_display();
void display();
void display_curse();



