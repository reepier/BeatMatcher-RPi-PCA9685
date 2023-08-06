#include <iostream>
#include <cmath>

#include "animator.h"
#include "constant.h"
#include "wiringPi.h"
#include "sysfcn.h"
#include "LED.h"
#include "spot.h"
#include "spider.h"

using namespace std;

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
            balise("Activate random spider animation (init)");
            spider.activate_random();
        }

        if (sampler.state_changed && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE)){
            t_last_change_ms = frame.t_current_ms;

            led.activate_random();
            //spot_g.activate_random();
            front_rack.activate_random();
            balise("Activate random spider animation");
            spider.activate_random();
        }
}


bool AnimationManager::test_animation(){
    bool success = false;

    if (s_anim_id.find("LED.") != string::npos){   // if animation's ID contains "LED"
        success = led.activate_by_ID(s_anim_id);
    }
    else if (s_anim_id.find("SPOT.") != string::npos){ // if animation's ID contains "SPOT"
        success = spot_g.activate_by_ID(s_anim_id);
    }
    else if (s_anim_id.find("FR.") != string::npos){   // if animation's ID contains "FR" (Front Rack)
        success = front_rack.activate_by_ID(s_anim_id);
    }
    else if (s_anim_id.find("BR.") != string::npos){   // if animation's ID contains "BR" (BackgroundRack)
        success = back_rack.activate_by_ID(s_anim_id);
    }
    else if (s_anim_id.find("SPI.") != string::npos){   // if animation's ID contains "SPI" (SPIder)
        success = spider.activate_by_ID(s_anim_id);
    }
    else{
        cout << "Animation ID prefix unknown... Prgram ended" << endl;
        success = false;
    }
    return success;
}


AnimationManager animator;


// toggles blackout boolean
void BaseFixture::blackout(bool b){
    this->b_blackout = b;
}

//TODO move BaseFixure and BaseAnimation functions in basefixture.h and baseanimation.h
// select and init an animtion randomly picked wihtin the list 
void BaseFixture::activate_random(){
    balise("Select");
    this->active_animation = this->animations[ rand()%this->animations.size() ];
    balise("Init");
    this->active_animation->init();
} 


// select and init an animation with its ID. If the ID cannot be found within the existing animations, does nothing.
bool BaseFixture::activate_by_ID(string id){
    bool found_it = false;
    
    for (vector<BaseAnimation*>::iterator anim_it = this->animations.begin(); anim_it != this->animations.end(); anim_it++){
        if ((*anim_it)->id == id){
            found_it = true;
            this->active_animation = (*anim_it);
            this->active_animation->init();
        }
    }
    if (!found_it){
        cout << "Animation ID unknown... Program ended" << endl;
    }
    return found_it;
}


// -----------------------------------
// USEFULL FUNCTIONS
// -----------------------------------
// TODO
#include <sstream>

DMX_vec fcn::RGBW(SimpleColor c){
    switch (c)
    {
    case black:
        return DMX_vec{0,0,0,0};
        break;
    case red:
        return DMX_vec{255,0,0,0};
        break;
    case green:
        return DMX_vec{0,255,0,0};
        break;
    case blue:
        return DMX_vec{0,0,255,0};
        break;
    case yellow:
        return DMX_vec{255,255,0,0};
        break;
    case cyan:
        return DMX_vec{0,255,255,0};
        break;
    case magenta:
        return DMX_vec{255,0,255,0};
        break;
    case white:
        return DMX_vec{0,0,0,255};
        break;
    default:
        break;
    }
}
DMX_vec fcn::RGB(SimpleColor c){
    switch (c)
    {
    case black:
        return DMX_vec{0,0,0};
        break;
    case red:
        return DMX_vec{255,0,0};
        break;
    case green:
        return DMX_vec{0,255,0};
        break;
    case blue:
        return DMX_vec{0,0,255};
        break;
    case yellow:
        return DMX_vec{255,255,0};
        break;
    case cyan:
        return DMX_vec{0,255,255};
        break;
    case magenta:
        return DMX_vec{255,0,255};
        break;
    case white:
        return DMX_vec{255,255,255};
        break;
    default:
        break;
    }
}
//  rgbw: color vector ; intensity : equivalent 8bit intensity
DMX_vec fcn::RGBW_norm(DMX_vec rgbw, uint8_t intensity){
    DMX_vec ret(4);
    if (rgbw.size() != 4){
        ret = DMX_vec{0,0,0,0};
    }else{
        

        int input_int = rgbw[R]+rgbw[G]+rgbw[B]+rgbw[W];
        float gain = (float)intensity/input_int;
        ret[R] = gain * rgbw[R];
        ret[G] = gain * rgbw[G];
        ret[B] = gain * rgbw[B];
        ret[W] = gain * rgbw[W];
    }
    return ret;
}
DMX_vec fcn::RGB_norm(DMX_vec rgbw, uint8_t intensity){
    DMX_vec ret(3);
    if (rgbw.size() != 3){
        ret = DMX_vec{0,0,0};
    }else{
        

        int input_int = rgbw[R]+rgbw[G]+rgbw[B];
        float gain = (float)intensity/input_int;
        ret[R] = gain * rgbw[R];
        ret[G] = gain * rgbw[G];
        ret[B] = gain * rgbw[B];
    }
    return ret;
}

string fcn::DMXvec_to_str(DMX_vec data, char sep){
    string ret;
    for (DMX_vec::iterator px=data.begin(); px!=data.end(); px++){
        ostringstream oss;
        oss<<(int)(*px);
        string sub_ret = oss.str();
        int sz = sub_ret.size();
        if (sz < 3){
            sub_ret.insert(0, string(3-sz, ' '));
        }

        ret.append(sub_ret);
        if ( !( (px+1)==data.end()) ){
            ret.push_back(sep);
        }
    }
    return ret;
}
std::string fcn::num_to_str(int val){
    ostringstream oss;
    oss<<val;
    return oss.str();
}
std::string fcn::num_to_str(uint8_t val){
    ostringstream oss;
    oss<<(int)val;
    return oss.str();
}
