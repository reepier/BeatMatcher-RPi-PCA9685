#include <iostream>
#include <cmath>

#include "animator.h"
#include "constant.h"
#include "wiringPi.h"
#include "sysfcn.h"
#include "LED.h"

/** Based on the musical analysis (music.state) and the current time, this function 
 * decides when to switch animation from one to another.
 * 
 * INPUTS :
 * t_current_ms : call time in millisecond
 * music : object containing the music analysis result.
 * 
 * OUTPUTS :
 * animtion_i : the index of the animation to run
 * OR
 * Directly call the animation function directly (led.animation[i].run();)
 * */
void AnimationManager::update(unsigned int t_current_ms, const SoundAnalyzer &music){

        if (music.state_changed && (t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE)){
            t_last_change_ms = t_current_ms;
            animation_i = (animation_i+1) % led.animation.size();
            led.active_animation = led.animation[animation_i].get_ptr();
            led.active_animation->init();
        }

        //flash only if the beat is tracked is OK
        if (music.state == BEAT)
            flash = true;
        else
            flash = false; 

        // --> do not flash for more than XXX seconds contiuously
        if (music.state == BEAT && (t_current_ms-music.t_beat_tracking_start) > MAX_CONT_FLASH){
            flash = false;
        }

        // std::cout << "DEBUG: juste avant la nouvelle image" << std::endl;
        led.RGB = led.active_animation->new_frame(t_current_ms, music.t_last_new_beat, flash); 
        //led.RGB = led.animation[animation_i].new_frame(t_current_ms, music.t_last_new_beat, flash); 
        
        led.send();
        // flash_master(t_current_ms, music.t_last_new_beat, flash, 60);
}


// TODO move to LEDANimation::new_frame()
/** Computes the RGB values to send to the led display based on :
 * @param t : t current time 
 * @param t_last_beat_ms : timestamp of the last beat detected 
 * @param flash : if true, the function will display a bright flash for every beat
 * @param fade_rate_ms : duration of the flash's exponential decay */
// void AnimationManager::flash_master(unsigned long t, unsigned long t_last_beat_ms, bool flash, int fade_rate_ms){

    
//         // TODO remplacer ce qui suit par une syntaxe du genre :
//         // ledfix.animation[animation_i].run(argss)

    
// }

// TODO move to LEDANimation::new_frame()
// alternative to flash_master (use it when beat is not discernible)
// void AnimationManager::flash_master_BS(int vol){
//   // secondary flashing mode
//   // the LED display the color contained in flash_RGB array but with an intensity following the volume
//   float intensity = sqrt((float)map(vol, 0, 180, 5, 255)/255);
  
//   set_LEDcolor(intensity*(float)flash_RGB[0], intensity*(float)flash_RGB[1], intensity*(float)flash_RGB[2]);
// }

// TODO remove
// void AnimationManager::set_color(int rgb[], int c0, int c1, int c2, int c3, int c4, int c5){
//     rgb[0]=c0;
//     rgb[1]=c1;
//     rgb[2]=c2;
//     rgb[3]=c3;
//     rgb[4]=c4;
//     rgb[5]=c5;
// }

// void AnimationManager::reset_period(){
//   periods[0] = 1000*rand_min_max(MIN_T, MAX_T);
//   periods[1] = 1000*rand_min_max(MIN_T, MAX_T);
//   periods[2] = 1000*rand_min_max(MIN_T, MAX_T);
//   periods[3] = 1000*rand_min_max(MIN_T, MAX_T);
//   periods[4] = 1000*rand_min_max(MIN_T, MAX_T);
//   periods[5] = 1000*rand_min_max(MIN_T, MAX_T); 
// }

AnimationManager animator;