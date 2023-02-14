#include <iostream>
#include <iomanip>
#include <string>
#include "debug.h"
#include "constant.h"
#include "LED.h"
#include "music.h"
#include "animator.h"
#include "sysfcn.h"
#include <wiringPi.h>

using namespace std;

// int mainloop_duration_ms = 30;

//TODO move to animator class/mosule
// int animation_i = 2;    // indice of the animation to run 
//TODO move to animator class/mosule
// Timer variables
// unsigned long last_animation_change_ms = millis();
//TODO move to animator class/mosule
// Flags
// bool flash = true;
// bool change_animation = true;
 
void initialize() {
    
    // sysfcn_init(); // initialize sysfcn lib FIRST

    sampler.init();    // THEN initialize Music lib
    
    LED_init();         // initialize OLA & shit
}


class LoopControler{
    public :
    unsigned long cpt = 0;
    bool first_loop = true;
    unsigned long t_previous_ms = 0;
    unsigned long t_current_ms = millis();
    unsigned long t_next_ms = 0;
    unsigned long loop_duration_ms = 0;

    void increment(){
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

LoopControler frame;

void debug();   // declaration of the display fucntion, definition at the end of thi smodule 


int main(){


    initialize();
    
    //TODO Move to a LoopControl class 
    //int t_previous_frame_ms = 0, t_current_frame_ms = millis(), t_next_frame_ms = 0;    //Timestamp in milliseconds

    while (true){

        frame.increment();
        
        // Use internal Beat Detector Program (default)
        
        // Music SAMPLING          
        #ifndef FAKEMUSIC
        sampler.update();
        #else
        sampler.fake_analysis(frame.t_current_ms);
        #endif // !FAKEMUSIC


        // TODO move all this code to an animator class/module
        // --------------------------------------------------------------------------------------------------------
        // --------------------------------------------------------------------------------------------------------
        // ANIMATOR
        // --------------------------------------------------------------------------------------------------------
        // Animation selector
        /* updates the current animation index (animation_i) whenever <state_changed> is TRUE.
        * Animation_i is of type int, it has 255 possible values (excessive)
        */
        animator.update(frame.t_current_ms, sampler);

        debug();

        frame.wait_for_next();

    }

  
}

// ---------------------------------------------------
// END MAIN()
// ---------------------------------------------------

/** Displays Critical variables in real time on the console */
  void debug(){

    cout << "\x1B[2J\x1B[H";// << flush;
    cout << "//// MUSIQUE /////" << '\n';
    cout << "Volume : " << string((int)(sampler.volume/1000.0*50), 'O') << '\n'; //sampler.volume << endl;
    cout << "Threshold : " << sampler.beat_threshold << '\n';
    cout << "ratio V/T : " << (float)sampler.volume/sampler.beat_threshold << '\n';
    cout << "sample Max/Min : " << sampler.deb_max << "/" << sampler.deb_min << '\n';
    cout << "Clip : " << sampler.clip << '\n';
    cout << "Beat : " << string(sampler.raw_beat, '!')  << '\n';
    cout << "State: " << sampler.state  << '\n';

    #ifdef FAKEMUSIC
    cout << "Next beat : " << (sampler.t_next_beat_ms - millis())/1000.0  << "s\n";
    cout << "Next break : " << (sampler.t_next_break_ms - millis())/1000.0  << "s\n";
    cout << "Next drop : " << (sampler.t_next_drop_ms - millis())/1000.0  << "s\n";
    #endif 
    
    
    cout << '\n' << "//// ANIMATOR /////" << '\n';
    cout << "Animation : " << animator.animation_i <<'\n';
    cout << "Flash : " << animator.flash << '\n';
    cout << "Last change " << (frame.t_current_ms - animator.t_last_change_ms)/1000 << "s\n";

    cout << "\n//// DMX CHANNELS /////" << '\n';

    cout << "\n//// GENERAL /////" << '\n';
    cout << "FPS : " << 1.0/frame.loop_duration_ms*1000.0 << "Hz\n";
    cout << "Elapsed time : " << millis()/1000.0 << " s\n";

    cout << "R/G/B : " << animator.rval << " / " << animator.gval << " / " << animator.bval << endl;
   /*
    for (int i=0; i<SAMPLE_SIZE; i++){
      int def_width = cout.width(4);
      cout << (int)sampler.signal[i][REAL] << " ";
    }
    cout << endl;
    */
      
     //cout << flush;


}




/* TODO BETTER
  - Figure out how Pi GPIO works (library, wiring, etc.) to rewrite state_display().
    OR debug() via console (more appropriate for now) 
*/