#include "animator.h"
#include "constant.h"
#include "wiringPi.h"



void AnimationManager::update(unsigned int t_current, const SoundAnalyzer &music){
        
        if (music.state_changed & (millis()-t_last_change_ms > TEMPO_ANIM_CHANGE)){
            time_to_change = true;
            t_last_change_ms = millis();
            animation_i = (animation_i+1) % n_animation;
            reset_period();

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

        }
        else{
            time_to_change=false;
        }
        
        if (music.state_changed){
            if (music.state == 1){
            flash = true;

            // TODO : Move to music module --> DECOUPLING between module is key
            music.t_beat_tracking_start = millis();
            }
            else{
            flash = false; //flash only if raw_beat tracking is OK
            }
        }
        
        if (music.state == BEAT_TRACKING && (millis()-music.t_beat_tracking_start) > MAX_CONT_FLASH){ // --> do not flash for more than 120s (eye confort)
            flash = false;
        }
        
        if (music.state == BAD_SIGNAL){
            set_color(color1, 255<<4,0<<4,0<<4);
            flash_master_BS(music.volume);
        }else{
            flash_master(music.new_beat, music.t_last_new_beat, flash, 60);
        }
}