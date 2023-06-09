#pragma once

#include "wiringPi.h"
#include "constant.h"


int map(int, int,int,int,int); //tested ok
int rand_min_max(int, int); // tested ok


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


    // This function will break if the Pi stays on for too long (~24h). This is due to micros() overflowing and going ack to 0.
    // TODO : fix it
    void wait_for_next(){
        while(micros() < 1000*t_next_ms) {
            // std::cout << t_current_ms << " / " << micros()/1000 << " / " << t_next_ms  << std::endl;
            delayMicroseconds(100); } // wait for the next frame

        if (first_loop) first_loop = false;
        cpt++;
    }
};

extern LoopControler frame;
