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
void AnimationManager::update(){
        // initialization
        if (frame.cpt == 0){
            led.activate_random();
            //spot_g.activate_random();
            front_rack.activate_random();
        }

        if (sampler.state_changed && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE)){
            t_last_change_ms = frame.t_current_ms;

            led.activate_random();
            //spot_g.activate_random();
            front_rack.activate_random();
        }
}


void AnimationManager::test(){

    if (s_anim_id.find("LED") != std::string::npos){   // if animation's ID contains "LED"
        // select the right animation and activate it
        led.activate_by_ID(s_anim_id);
    }
    else if (s_anim_id.find("SPOT") != std::string::npos){
        spot_g.activate_by_ID(s_anim_id);
    }
    else if (s_anim_id.find("SFRONT") != std::string::npos){

    }
    else if (s_anim_id.find("SBACK") != std::string::npos){

    }
}


AnimationManager animator;


// toggles blackout boolean
void BaseFixture::blackout(bool b){
    this->b_blackout = b;
}

// randomly select and init an animtion wihtin the list 
void BaseFixture::activate_random(){
    this->active_animation = this->animations[ rand()%this->animations.size() ];
    this->active_animation->init();
} 


// select and init an animation based on its ID. If the ID cannot be found within the existing animations, does nothing.
void BaseFixture::activate_by_ID(std::string id){
    for (std::vector<BaseAnimation*>::iterator anim_it = this->animations.begin(); anim_it != this->animations.end(); anim_it++){
        if ((*anim_it)->id == id){
            this->active_animation = (*anim_it);
            this->active_animation->init();
        }
    } 
}