#include <iostream>
#include <iomanip>
#include <string>
#include "debug.h"
#include "constant.h"
#include "LED.h"
#include "music.h"
#include "sysfcn.h"
#include <wiringPi.h>

using namespace std;

//TODO move to animator class/mosule
int animation_i = 2;    // indice of the animation to run 

//TODO move to animator class/mosule
// Timer variables
unsigned long last_animation_change_ms = millis();
int mainloop_duration_ms = 30;

//TODO move to animator class/mosule
// Flags
bool flash = true;
bool change_animation = true;
 
void initialize() {
    
    // sysfcn_init(); // initialize sysfcn lib FIRST

    sampler.init();    // THEN initialize Music lib
    
    LED_init();         // initialize OLA & shit
}

int main(){

    initialize();

    //TODO Move to a LoopControl class 
    int t_previous_frame_ms = 0, t_current_frame_ms = millis(), t_next_frame_ms = 0;    //Timestamp in milliseconds

    while (true){
        //TODO Move to a LoopControl class 
        static bool first_loop = true;
        static int cpt = 0;

        //TODO Move to a LoopControl class
        // update frame timers
        t_previous_frame_ms = t_current_frame_ms;
        t_current_frame_ms = millis();                  //TODO : use millis() only once and pass t_current_frame_ms as argument to every function
        t_next_frame_ms = t_current_frame_ms + 1000 / FRATE;
        mainloop_duration_ms = t_current_frame_ms - t_previous_frame_ms;

        // Use internal Beat Detector Program (default)
            
            // MUSIC RECORDING            
            #ifndef FAKEMUSIC
            sampler.record();

            // SAMPLE PROCESSING
            sampler.process_record();
            #else
            sampler.fake_analysis();
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
            int n_animation = 10;
            
            if (sampler.state_changed & (millis()-last_animation_change_ms > TEMPO_ANIM_CHANGE)){
                change_animation = true;
                last_animation_change_ms = millis();
                animation_i = (animation_i+1) % n_animation;
                reset_period();

                // INSERT_ANIM_SWITCH
            }
            else{
                change_animation=false;
            }
            
            if (sampler.state_changed){
                if (sampler.state == 1){
                flash = true;
                sampler.beat_tracking_start = millis();
                }
                else{
                flash = false; //flash only if raw_beat tracking is OK
                }
            }
            
            if (sampler.state == BEAT_TRACKING && (millis()-sampler.beat_tracking_start) > MAX_CONT_FLASH){ // --> do not flash for more than 120s (eye confort)
                flash = false;
            }
            // TODO : This block shall be relocated to the place marked with INSERT_ANIM_SWITCH
            switch (animation_i){
            case 0:
                // Warm Flashes
                set_color(color1, 255<<4, 150<<4, 80<<4);   // flash RGBor
                set_color(color2, 30<<4,100<<4, 1<<4,7<<4, 0<<4,0<<4);  // back color wave settings (Rmax, Rmin, Gmax,...)
            break;
            case 1:
                // Sodium Flashes
                set_color(color1, 255<<4, 50<<4, 10<<4);
                set_color(color2, 15<<4,50<<4, 0<<4,5<<4, 0<<4,0<<4);      
            break;
            case 2:
            // Very Warm
                set_color(color1, 255<<4, 150<<4, 80<<4);
                set_color(color2, 30<<4,100<<4, 1<<4,7<<4, 0<<4,0<<4);      
            break;
            case 3:
                //BLACK BACKGROUND RED flashes
                set_color(color1, 255<<4, 0<<4, 0<<4);
                set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);
            break;
            case 4:
                // Slide to pink palette introducing blue
                set_color(color1, 255<<4, 150<<4, 80<<4);
                set_color(color2, 30<<4,100<<4, 0<<4, 0<<4, 0<<4,10<<4);
            break;
            case 5:
                //BLACK BACKGROUND PINK flashes
                set_color(color1, 0<<4, 0<<4, 255<<4);
                set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4); 
            break;
            case 6:
                // reduce red, increase blue
                set_color(color1, 255<<4, 100<<4, 80<<4);
                set_color(color2, 0<<4,80<<4, 0<<4,0<<4, 0<<4,20<<4);
            break;
            case 7:
                // reduce red, increase blue
                set_color(color1, 255<<4, 100<<4, 80<<4);
                set_color(color2, 0<<4,50<<4, 0<<4,0<<4, 0<<4,80<<4);     
            break;
            case 8:
                // Mostly blue
                set_color(color1, 255<<4, 100<<4, 80<<4);
                set_color(color2, 0<<4,20<<4, 0<<4, 0<<4, 0<<4,100<<4);      
            break;
            case 9:
                //BLACK BACKGROUND BLUE flashes
                set_color(color1, 0<<4, 0<<4, 255<<4);
                set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);
            break;
            case 10:
            // Introduce green to slide towards cyan - yellow palette
                set_color(color1, 255<<4, 100<<4, 80<<4);
                set_color(color2, 0<<4,10<<4, 0<<4,10<<4, 0<<4,100<<4);  
            break;
            case 11:
                // Sodium Flashes
                set_color(color1, 255<<4, 30<<4, 0<<4);
                set_color(color2, 15<<4,50<<4, 0<<4,5<<4, 0<<4,0<<4);
            break;
            case 12:
                //BLACK BACKGROUND with WHITE FLASHES
                set_color(color1, 255<<4, 100<<4, 80<<4);
                set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);
            break;
            }

           
            if (sampler.state == BAD_SIGNAL){
                set_color(color1, 255<<4,0<<4,0<<4);
                flash_master_BS(sampler.volume);
            }else{
                flash_master(sampler.new_beat, sampler.last_new_beat, flash, 60);
            }

            debug();

        //TODO : move this block to a LoopControl class
        if (first_loop) first_loop = false;
        cpt++;
        while(micros() < 1000*t_next_frame_ms){delayMicroseconds(100);} // wait for the next frame

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
    cout << '\n';
    cout << "//// ANIMATOR /////" << '\n';
    cout << "State Machine : ";
    switch(sampler.state){
        case 1:
            cout << "BEAT TRACKING" << '\n';
        break;
        case 2:
            cout << "BREAK" << '\n';
        break;
        case 3:
            cout << "BAD SIGNAL" << '\n';
        break;
    }
    cout << '\n';
    cout << "//// DMX CHANNELS /////" << '\n';// << endl;
    

    cout << "fps : " << 1.0/mainloop_duration_ms*1000 << "Hz\n";
    cout << "Elapsed time : " << setprecision(2) << millis()/1000.0 << "s" << endl;
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