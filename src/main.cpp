#include <iostream>
#include <iomanip>
#include <string>
#include "debug.h"
#include "constant.h"
#include "LED.h"
#include "music.h"
#include "sysfcn.h"

using namespace std;

// Counters
int animation_i = 2;


// Timer variables
unsigned long last_change_anim = millis();
int main_loop_duration = 30;

// Flags
bool flash = true;
bool animation_change = true;
 
void setup() {
    // initialize sysfcn lib FIRST
    sysfcn_init();
    // THEN
    // initialize Music lib
    sampler.init();
    // initialize OLA & shit
    LED_init();
}

int main(){

  setup();

  bool first_loop = true;
  int cpt = 0;

  int prev_frame = 0, this_frame = millis(), next_frame = 0;

    while (true){
        // update frame timers
        prev_frame = this_frame;
        this_frame = millis();
        next_frame = this_frame + 1000 / FRATE;
        main_loop_duration = this_frame-prev_frame;

        // Use internal Beat Detector Program (default)
            //----------------------------------------------
            // MUSIC RECORDING
            //Sampling loop --> period : sampling_period
            
            #ifndef FAKEMUSIC
            sampler.record();
            //---------------------------------------------------------------------
            // SAMPLE PROCESSING
            sampler.process_record();
            #else
            sampler.fake_analysis();
            #endif // !FAKEMUSIC

            // --------------------------------------------------------------------------------------------------------
            // --------------------------------------------------------------------------------------------------------
            // ANIMATOR
            // --------------------------------------------------------------------------------------------------------
            // Animation selector
            /* updates the current animation index (animation_i) whenever <state_change> is TRUE.
            * Animation_i is of type int, it has 255 possible values (excessive)
            */
            int n_animation = 10;
            
            if (sampler.state_change & (millis()-last_change_anim > TEMPO_ANIM_CHANGE)){
                animation_change = true;
                last_change_anim = millis();
                animation_i = (animation_i+1) % n_animation;
                reset_period();
                // call set_colors here
            }
            else{
                animation_change=false;
            }
            
            if (sampler.state_change){
                if (sampler.system_state == 1){
                flash = true;
                sampler.beat_tracking_start = millis();
                }
                else{
                flash = false; //flash only if beat tracking is OK
                }
            }
            
            if (sampler.system_state == 1 && (millis()-sampler.beat_tracking_start) > MAX_CONT_FLASH){ // --> do not flash for more than 120s (eye confort)
                flash = false;
            }
            
                // move this block to a "set_colors" function in led.cpp
                // call set_colors() right after reset_period()
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

            if (sampler.system_state != 3){
                flash_master(sampler.new_beat, sampler.last_new_beat, flash, 60);
            }
            else{
                set_color(color1, 255<<4,0<<4,0<<4);
                flash_master_BS(sampler.volume);
            }


            debug();


        if (first_loop)
            first_loop = false;

        cpt++;
        // cout << sampler.volume << endl;
        // wait for the next frame
        // while(millis() < next_frame){}

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
    cout << "Threshold : " << sampler.beat_thresh << '\n';
    cout << "ratio V/T : " << (float)sampler.volume/sampler.beat_thresh << '\n';
    cout << "sample Max/Min : " << sampler.deb_max << "/" << sampler.deb_min << '\n';
    cout << "Clip : " << sampler.clip << '\n';
    cout << "Beat : " << string(sampler.beat, '!')  << '\n';
    cout << '\n';
    cout << "//// ANIMATOR /////" << '\n';
    cout << "State Machine : ";
    switch(sampler.system_state){
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
    

    cout << "fps : " << 1.0/main_loop_duration*1000 << "Hz\n";
    cout << "Elapsed time : " << setprecision(2) << millis()/1000.0 << "s" << endl;
   /*
    for (int i=0; i<SAMP_N; i++){
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