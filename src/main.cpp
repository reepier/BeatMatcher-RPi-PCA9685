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
    #ifdef DEBUG
    cout << "Init. Sampler..." << endl;
    sampler.init();   // THEN initialize Music lib
    #endif // DEBUG
    
    cout << "Init. Leds..." << endl;
    led.LED_init();   // initialize OLA & shit
    cout << "Init. Debug..." << endl;
    init_display();
}

LoopControler frame;

int main(){

    // cout << "Initialization..." << endl;
    initialize();
    
    while (true){
        // cout << "Start new frame..." << endl;
        // Update general counters and timers
        frame.start_new_frame();
        
        // cout << "Record sample..." << endl;
        // Record and process music sample
        // cout << "Process sample..." << endl;         
        // #ifndef FAKEMUSIC
        sampler.update(frame.t_current_ms);
        // #else
        // sampler.fake_analysis(frame.t_current_ms);
        // #endif // !FAKEMUSIC
        // cout << "Run animator..." << endl;
        animator.update(frame.t_current_ms, sampler);

        // cout << "Compute new frame..." << endl;
        led.RGB = led.active_animation->new_frame(frame.t_current_ms, sampler.t_last_new_beat, animator.flash); 
        
        // cout << "Send frame..." << endl;
        led.send();

        // cout << "Debug..." << endl;
        // display();
        display_curse();

        frame.wait_for_next();
    }
}