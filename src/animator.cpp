#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

// #include "LED.h"
// #include "animator.h"
// #include "spot.h"
// #include "spider.h"
#include "wiringPi.h"
#include "sysfcn.h"
#include "debug.h"
#include "fixtures.h"

using namespace std;


/**-------------------------------------------------------------------------------------------
                 _                 _   _                __  __                                    
     /\         (_)               | | (_)              |  \/  |                                   
    /  \   _ __  _ _ __ ___   __ _| |_ _  ___  _ __    | \  / | __ _ _ __   __ _  __ _  ___ _ __  
   / /\ \ | '_ \| | '_ ` _ \ / _` | __| |/ _ \| '_ \   | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '__| 
  / ____ \| | | | | | | | | | (_| | |_| | (_) | | | |  | |  | | (_| | | | | (_| | (_| |  __/ |    
 /_/    \_\_| |_|_|_| |_| |_|\__,_|\__|_|\___/|_| |_|  |_|  |_|\__,_|_| |_|\__,_|\__, |\___|_|    
 -------------------------------------------------------------------------------  __/ | -------   
                                                                                 |___/             */

/** Based on the musical analysis (music.state) and the current time, this function 
 * decides when to switch animation
 * When it switches, it selects randomly within the animations list without trying to match
 * them by color or style 
 * */
void AnimationManager::random_update(){

        if (  frame.first_loop
              || (sampler.state_changed && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE))){
            
            log(1, "Change animation randomly");
            t_last_change_ms = frame.t_current_ms;

            for(fix_vec::iterator fix = fixtures.begin(); fix != fixtures.end(); fix++){
                (*fix)->activate_random();
            }
        }
}

void AnimationManager::palette_update(){
    
    if (  frame.first_loop
              || (sampler.state_changed && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE))){
            
            t_last_change_ms = frame.t_current_ms;

            // select color theme
            int i = rand_min_max(0, colorPalette.size());
            color_vec palette = colorPalette[i];
            
            // log it
            str_vec palette_literal;
            for (auto col : palette){
                palette_literal.push_back(colorName[(int)col]);
            }
            log(1, "Change animation to color palette : ", fcn::vec_to_str(palette_literal, '/'));

            for(fix_vec::iterator fix = fixtures.begin(); fix != fixtures.end(); fix++){
                (*fix)->activate_by_color(palette);
            }
        }
    // color_vec palette = 
    // select animations matching the theme for each fixture
}

bool AnimationManager::test_animation(){
    bool success = false;
    balise(fcn::num_to_str((int)vec_anim_id.size()).data());
    for(vector<string>::iterator anim_id_it = vec_anim_id.begin(); anim_id_it != vec_anim_id.end(); anim_id_it++){
        string s_anim_id = (*anim_id_it);
        balise(s_anim_id.data());
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
    }
    return success;
}

AnimationManager animator;


/** ----------------------------------------------------------
  ____                    ______ _      _                  
 |  _ \                  |  ____(_)    | |                 
 | |_) | __ _ ___  ___   | |__   ___  _| |_ _   _ _ __ ___ 
 |  _ < / _` / __|/ _ \  |  __| | \ \/ / __| | | | '__/ _ \
 | |_) | (_| \__ \  __/  | |    | |>  <| |_| |_| | | |  __/
 |____/ \__,_|___/\___|  |_|    |_/_/\_\\__|\__,_|_|  \___|
 ---------------------------------------------------------------
 */

// toggles blackout boolean
void BaseFixture::blackout(bool b){
    this->b_blackout = b;
}

// deactivate fixture (display the "BLACK" animations)
bool BaseFixture::activate_none(){
    this->active_animation = this->animations[0];
    this->active_animation->init();
}

// selects and init the i_th animation within the list (i being the argument).
// If i out of range, select the first (black) 
bool BaseFixture::activate_by_index(int i){
    if (i < this->animations.size())
        this->active_animation = this->animations[i];
    else
        this->active_animation = this->animations[0];
    this->active_animation->init();
}

// select and init an animtion randomly picked wihtin the list 
bool BaseFixture::activate_random(){
    this->active_animation = this->animations[ rand()%this->animations.size() ];
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

/* Activates an animation whose colors match the ones in palette passed as an argument.
   All of the selected animations color must be listed in the palette, but all the palette's 
   color do not have to be listed in the animation's colors */
bool BaseFixture::activate_by_color(color_vec palette){
    int n_anim = this->animations.size();

    // copy the fixture's animation list
        anim_vec fixtures_anim_list = this->animations;

    // randomize the list item's order
        random_device rd;
        mt19937 rng(rd());
        shuffle(fixtures_anim_list.begin(), fixtures_anim_list.end(), rng);

    bool found_it = false;
    // Parse through the animations'list (in a random order) and select the first anim that matches the palette
    // All the animation's color must be listed int h
        for(auto current_animation : fixtures_anim_list){
            bool animation_match = true;   // becomes false if (at least) one of the animation's color does not match the palette 
            // for each of the animation color
            for (auto animation_color : (*current_animation).color_palette){
                bool color_match = false;   // becomes true if the current color matches on of the palette's color
                for (auto palette_color : palette){
                    color_match = color_match || (animation_color == palette_color);
                }
                animation_match = animation_match && color_match;
            }

            // if the animation is a match, activate it and exit the for loop , else deactivate
            if (animation_match){
                this->activate_by_ID(current_animation->id);
                break;
            }else{
                this->activate_none();
            }
        }
}   

/** -----------------------------------
  ______                _   _                 
 |  ____|              | | (_)                
 | |__ _   _ _ __   ___| |_ _  ___  _ __  ___ 
 |  __| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 | |  | |_| | | | | (__| |_| | (_) | | | \__ \
 |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
-----------------------------------
*/

#include <sstream>

DMX_vec fcn::RGBW(simpleColor c, uint8_t intensity){
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

DMX_vec fcn::RGB(simpleColor color, uint8_t intensity){
    DMX_vec ret;
    if (color == black || color == red || color == green || color == blue
        || color == cyan || color == magenta || color == pink || color == purple
        || color == yellow || color == orange || color == sodium){
        ret = fcn::RGBW(color, intensity);
        ret.pop_back();
        return ret;
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
    float gain = (intensity==-1) ? 1.0:(float)intensity/sum;

    for (int i=0; i<size; i++){
        ret[i] = gain*rgbw[i];
    }
    return ret;
}
DMX_vec fcn::RGB_norm(DMX_vec rgb, uint8_t intensity){
    return fcn::RGBW_norm(rgb, intensity);
}

string fcn::vec_to_str(DMX_vec data, char sep){
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
string fcn::vec_to_str(int_vec data, char sep){
    string ret;
    for (int_vec::iterator px=data.begin(); px!=data.end(); px++){
        ostringstream oss;
        oss<<(*px);
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
string fcn::vec_to_str(str_vec data, char sep){
    string ret;
    for (str_vec::iterator vec_element=data.begin(); vec_element!=data.end(); vec_element++){
        ostringstream oss;
        oss<<(*vec_element);
        string sub_ret = oss.str();

        ret.append(sub_ret);
        if ( !( (vec_element+1)==data.end()) ){
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
std::string fcn::num_to_str(double val){
    ostringstream oss;
    oss<<val;
    return oss.str();
}

int_vec fcn::convert_8_to_12bits(DMX_vec in_vec){
    const int sz = in_vec.size();
    int_vec ret;
    for (int i=0; i<sz;i++){
        ret.push_back((int)(in_vec[i])*16);
    }
    return ret;
}
