#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <wiringPi.h>

#include "debug.h"
#include "constant.h"
#include "LED.h"
#include "music.h"
#include "animator.h"
#include "sysfcn.h"
#include "config.h"

using namespace std;
 
void initialize() {
    
    #ifndef FAKEMUSIC
        balise("Init. Sampler...");
        sampler.init();   // THEN initialize Music lib
    #endif // FAKEMUISC
    
    balise("Init. Leds...");
    led.LED_init();   // initialize OLA & shit

    balise("Init. Debug...");
    init_display();
}

bool process_arguments(int n, char* args[]){
    for (int i=1; i<=n-1; i++){
        char* arg = args[i];

        if (strcmp(arg, "--noled") == 0){
            b_NO_LED = true;
        }
        else if (strcmp(arg, "--nomusic") == 0){
            b_NO_MUSIC = true;
        }
        else if(strcmp(arg, "--nocurses") == 0){
            b_CURSES == false;
        }
        else{
            return false;
        }
    }

    return true;
}

LoopControler frame;

int main(int argc, char* argv[]){

    balise("Initialization...");
    if(!process_arguments(argc, argv)){
        cout << "Initialization failed : unknown argument(s) passed" << endl;
        return -1;
    }
    initialize();
    
    while (true){
        // Update general counters and timers
        balise("Start new frame...");
        frame.start_new_frame();
        
        // Record and process music sample 
        balise("Record & process sample...");   
        sampler.update(frame.t_current_ms);

        balise("Run animator...");
        animator.update(frame.t_current_ms, sampler);

        balise("Compute new frame...");
        led.RGB = led.active_animation->new_frame(frame.t_current_ms, sampler.t_last_new_beat, animator.flash); 
        
        balise("Send frame...");
        led.send();

        balise("Debug...");
        // display();
        display_curse();

        balise("Wait next frame...");
        frame.wait_for_next();
    }
}