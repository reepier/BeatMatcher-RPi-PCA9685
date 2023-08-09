#include <iostream>
#include <cmath>

#include "animator.h"
#include "constant.h"
#include "wiringPi.h"
#include "sysfcn.h"
#include "LED.h"
#include "spot.h"
#include "spider.h"
#include "debug.h"

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
            log(1, "Animator random", " update");

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

DMX_vec fcn::RGBW(SimpleColor c, uint8_t intensity){
    switch (c)
    {
    case black:
        return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
        break;
    case red:
        return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);
        break;
    case green:
        return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 160.0/255*intensity);
        break;
    case blue:
        return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);
        break;
    case yellow:
        return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);
        break;
    case orange:
        return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);
        break;
    case sodium:
        return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);
        break;
    case cyan:
        return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);
        break;
    case purple:
        return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);
        break;    
    case magenta:
        return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);
        break;
    case pink:
        return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);
        break;
    case white:
        return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
        break;
    case gold:
        return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
        break;
    default:
        break;
    }
}

DMX_vec fcn::RGB(SimpleColor color, uint8_t intensity){
    DMX_vec ret;
    if (color == black || color == red || color == green || color == blue
        || color == cyan || color == magenta || color == pink || color == purple
        || color == yellow || color == orange || color == sodium){
        ret = fcn::RGBW(color, intensity);
        ret.pop_back();
    }
    
    else if (color == white){
        return RGB_norm(DMX_vec{255,90,17});
    }else if (color == gold){
        return fcn::RGB_norm(DMX_vec{255,42,7}, intensity);
    }
}
//  rgbw: color vector ; intensity : equivalent 8bit intensity
DMX_vec fcn::RGBW_norm(DMX_vec rgbw, uint8_t intensity){
    const int size = rgbw.size();
    DMX_vec ret(size);
    
    int sum = 0;
    for (int i=0; i<size; i++){
        sum += rgbw[i];
    }
    float gain = (float)intensity/sum;

    for (int i=0; i<size; i++){
        ret[i] = gain*rgbw[i];
    }
    return ret;
}
DMX_vec fcn::RGB_norm(DMX_vec rgb, uint8_t intensity){
    return fcn::RGBW_norm(rgb, intensity);
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
