#include <iostream>
#include <iomanip>
#include <string>
#include <wiringPi.h>

#include "debug.h"
#include "constant.h"
#include "LED.h"
#include "music.h"
#include "animator.h"
#include "sysfcn.h"

using namespace std;
 
void initialize() {
    
    // sysfcn_init(); // initialize sysfcn lib FIRST

    sampler.init();   // THEN initialize Music lib
    
    led.LED_init();   // initialize OLA & shit

    init_display();
}

LoopControler frame;

int main(){


    initialize();
    
    while (true){
        // Update general counters and timers
        frame.start_new_frame();
        
        // Record and process music sample         
        #ifndef FAKEMUSIC
        sampler.update();
        #else
        sampler.fake_analysis(frame.t_current_ms);
        #endif // !FAKEMUSIC

        animator.update(frame.t_current_ms, sampler);

        led.RGB = led.active_animation->new_frame(frame.t_current_ms, sampler.t_last_new_beat, animator.flash); 
        led.send();

        // display();
        display_curse();

        frame.wait_for_next();
    }
}