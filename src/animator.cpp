#include <iostream>
#include <cmath>

#include "animator.h"
#include "constant.h"
#include "wiringPi.h"
#include "sysfcn.h"
#include "LED.h"
#include "spot.h"

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

            led.active_animation = led.animations[ rand()%led.animations.size() ];
            led.active_animation->init();

            spot.active_animation = spot.animations[ rand()%spot.animations.size() ];
            spot.active_animation->init(); 
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

}


AnimationManager animator;