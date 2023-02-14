#include "animator.h"
#include "constant.h"
#include "wiringPi.h"
#include "sysfcn.h"
#include "LED.h"

#include <cmath>

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
        
        if (music.state == BEAT){
            flash = true;
        }
        else{
            flash = false; //flash only if raw_beat tracking is OK
        }
        
        if (music.state == BEAT && (millis()-music.t_beat_tracking_start) > MAX_CONT_FLASH){ // --> do not flash for more than 120s (eye confort)
            flash = false;
        }
        
        if (music.state == BAD_SIGNAL){
            set_color(color1, 255<<4,0<<4,0<<4);
            flash_master_BS(music.volume);
        }else{
            flash_master(music.new_beat, music.t_last_new_beat, flash, 60);
        }
}

//TODO move to animator class/module
//TODO : raw_beat argument is useless --> remove it...  the beat_t timer is enough to compute the exponential decay
void AnimationManager::flash_master(bool raw_beat, unsigned long beat_t, bool flash, int fade_rate){
    unsigned long t = millis();

    //TODO : use more explicit naming (rgb instead of color)
    // color2[] stores [redmin, redmax, greenmin, green max...]
    back_color[0] = (color2[0]+color2[1])/2 
                    + (color2[1]-color2[0])/4
                            *(sin(2*3.14*t/period[0])+sin(2*3.14*t/period[1]));
    back_color[1] = (color2[2]+color2[3])/2 
                    + (color2[3]-color2[2])/4
                            *(sin(2*3.14*t/period[2])-sin(2*3.14*t/period[3]));
    back_color[2] = (color2[4]+color2[5])/2 
                    + (color2[5]-color2[4])/4
                            *(sin(2*3.14*t/period[4])-sin(2*3.14*t/period[5]));
                                
    if (raw_beat && flash){
        rgb_color(color1[1], color1[2], color1[2]);
    }
    else{
        if (flash){
            coef = exp(-(float)(t-beat_t)/fade_rate);
        }
        else{
            coef = 0;  
        }
        rgb_color(back_color[0]+coef*(color1[0]-back_color[0]), back_color[1]+coef*(color1[1]-back_color[1]), back_color[2]+coef*(color1[2]-back_color[2]));
    }
}

void AnimationManager::flash_master_BS(int vol){
  // secondary flashing mode
  // the LED display the color contained in color1 array but with an intensity following the volume
  float intensity = sqrt((float)map(vol, 0, 180, 5, 255)/255);
  
  rgb_color(intensity*(float)color1[0], intensity*(float)color1[1], intensity*(float)color1[2]);
}

//TODO move to animator class/module
void AnimationManager::set_color(int rgb[], int c0, int c1, int c2, int c3, int c4, int c5){
    rgb[0]=c0;
    rgb[1]=c1;
    rgb[2]=c2;
    rgb[3]=c3;
    rgb[4]=c4;
    rgb[5]=c5;
}

void AnimationManager::reset_period(){
  // randomSeed(analogRead(musicpin));
  period[0] = 1000*rand_min_max(MIN_T, MAX_T);
  period[1] = 1000*rand_min_max(MIN_T, MAX_T);
  period[2] = 1000*rand_min_max(MIN_T, MAX_T);
  period[3] = 1000*rand_min_max(MIN_T, MAX_T);
  period[4] = 1000*rand_min_max(MIN_T, MAX_T);
  period[5] = 1000*rand_min_max(MIN_T, MAX_T); 
}

AnimationManager animator;