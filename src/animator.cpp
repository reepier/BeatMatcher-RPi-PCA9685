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


/**
   #                                                    #     #               
  # #   #    # # #    #   ##   ##### #  ####  #    #    ##   ##  ####  #####  
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   #    # # # # #    # #    # 
#     # # #  # # # ## # #    #   #   # #    # # #  #    #  #  # #      #    # 
####### #  # # # #    # ######   #   # #    # #  # #    #     # #  ### #####  
#     # #   ## # #    # #    #   #   # #    # #   ##    #     # #    # #   #  
#     # #    # # #    # #    #   #   #  ####  #    #    #     #  ####  #    # 

*/

void AnimationManager::init(){
    palette_magasine.push_back(    color_vec{red}    ,2   );
    palette_magasine.push_back(    color_vec{sodium} ,1   );
    palette_magasine.push_back(    color_vec{orange} ,1   );
 // palette_magasine.push_back(    color_vec{yellow} ,1   );
 // palette_magasine.push_back(    color_vec{gold}   ,1   );
 // palette_magasine.push_back(    color_vec{white}  ,1   );
 // palette_magasine.push_back(    color_vec{cyan}   ,1   );
    palette_magasine.push_back(    color_vec{blue}   ,2   );
    palette_magasine.push_back(    color_vec{purple} ,1   );
 // palette_magasine.push_back(    color_vec{magenta},1   );
 // palette_magasine.push_back(    color_vec{pink}   ,1   );
 // palette_magasine.push_back(    color_vec{green}  ,1   );
    
    palette_magasine.push_back(     color_vec{white, red}       ,1      );
 // palette_magasine.push_back(     color_vec{white, sodium}    ,1      );
 // palette_magasine.push_back(     color_vec{white, orange}    ,1      );
 // palette_magasine.push_back(     color_vec{white, yellow}    ,1      );
 // palette_magasine.push_back(     color_vec{white, gold}      ,1      );
 // palette_magasine.push_back(     color_vec{white, white}     ,1      );
 // palette_magasine.push_back(     color_vec{white, cyan}      ,1      );
    palette_magasine.push_back(     color_vec{white, blue}      ,1      );
    palette_magasine.push_back(     color_vec{white, purple}    ,1      );
 // palette_magasine.push_back(     color_vec{white, magenta}   ,1      );
 // palette_magasine.push_back(     color_vec{white, pink}      ,1      );
 // palette_magasine.push_back(     color_vec{white, green}     ,1      );


    palette_magasine.push_back(    color_vec{cyan, magenta}    ,1       );
    palette_magasine.push_back(    color_vec{gold, red}        ,3       );
    palette_magasine.push_back(    color_vec{gold, orange}     ,1       );
    palette_magasine.push_back(    color_vec{gold, sodium}     ,1       );
    palette_magasine.push_back(    color_vec{red, blue}        ,3       );
    palette_magasine.push_back(    color_vec{red, purple}      ,3       );
    palette_magasine.push_back(    color_vec{gold, purple}     ,2       );
    palette_magasine.push_back(    color_vec{blue, purple}     ,1       );
    palette_magasine.push_back(    color_vec{cyan, purple}     ,1       );
    palette_magasine.push_back(    color_vec{cyan, red}        ,3       );
    palette_magasine.push_back(    color_vec{blue, cyan}       ,1       );

}

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
            color_vec palette = this->palette_magasine.get_random_palette();
            
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

// The purpose of this animation is to test ranges of animations or play with different control logics
void AnimationManager::test_update(){
    static color_vec current_palette;
    static int palette_lifespan;
    /** Animation switch occurs based on different principles :
     *  - (legacy) change when a MAX timer has elapsed AND when the Beat State changes
     *  - (new) Change when a custom, sequence specific  timer has elpased (i.e. -> to avoid long periods of stroboscopic animation); */
    if (  frame.first_loop
        || (sampler.state_changed && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE))
        || this->timer_elapsed()){


        if (frame.first_loop){
            current_palette = palette_magasine.get_random_palette();
            palette_lifespan = 5;
        }

        if (frame.first_loop || palette_lifespan == 0){
            // color_vec::size_type i = rand_min_max(0, colorPalettes.size());
            current_palette = palette_magasine.get_similar_palette(current_palette);
            // switch(current_palette.size()){
	    	// case 1 :
	    	// 	palette_lifespan = 2;
			//     break;
		    // case 2 :
			//     palette_lifespan = 5;
			//     break;
		    // default :
			//     palette_lifespan = 5;
			// break;
            // }   
	        palette_lifespan = 1;
        }

        // select a leader among Led bars, Front rack, and Laser
        auto lead_fix = fcn::random_pick(fix_vec{&led, &front_rack, & laser}, {4, 2, 1});
        
        // reference the other fixtures as "backer fixtures" in a vector (for ease of acccess & modularity)
        fix_vec backer_fix;
        for (auto fix : fix_vec{&led, &front_rack, &laser}){
            if (fix->name != lead_fix->name){
                backer_fix.push_back(fix);
            }
        }
        // sort the backer fixtures in a random order
        random_device rd;
        mt19937 rng(rd());
        shuffle(backer_fix.begin(), backer_fix.end(), rng);

        /** pick randomly how many backer fixtures will light up to back the leader fixture
         *  3 time out of 6 there should be 2 backer (3 fixtures total)
         *  2 time out of 6 there should be 1 backer
         *  1 tme out of 6 there should be NO backer */
        int back_fix_n = fcn::random_pick( int_vec{2,1,0}, int_vec{3,2,1} );

        lead_fix->activate_by_color(current_palette, leader);
        for (int i = 0; i<backer_fix.size(); i++){
            if (i<back_fix_n)
                backer_fix[i]->activate_by_color(current_palette, backer);
            else
                backer_fix[i]->activate_none();
        }
        back_rack.activate_by_color(current_palette);   // deal with the backstage rack separately

        // log the results
        log(1, "Color palette ", fcn::palette_to_string(current_palette, '/')," ", fcn::num_to_str(palette_lifespan), " | Leader->", lead_fix->name, " ", fcn::num_to_str(back_fix_n), " backers");
        
        t_last_change_ms = frame.t_current_ms;
        palette_lifespan-- ;
    }

    //TODO : randomize the number of backer animations (between 0 to 2)
    //TODO : give different weight to every palette so that 

    static time_t last_spider_switch = 0;
    // Manage Lyre :
    if (frame.t_current_ms - last_spider_switch > SPIDER_ANI_DURA){
        spider.activate_random();
        // log(1, "Switch Spider animation --> ", spider.active_animation->description);
        last_spider_switch = frame.t_current_ms;
    }

}

bool AnimationManager::test_animation(){
    bool success = false;
    balise(fcn::num_to_str((int)vec_anim_id.size()).data());
    for(vector<string>::iterator anim_id_it = vec_anim_id.begin(); anim_id_it != vec_anim_id.end(); anim_id_it++){
        string s_anim_id = (*anim_id_it);
        balise(s_anim_id.data());

        for (auto fix : fixtures){
            success = fix->activate_by_ID(s_anim_id);
            if (success) break;
        }

        if (!success){
            cout << "Animation ID prefix unknown..." << endl;
            success = false;
        }
    }
    return success;
}

AnimationManager animator;


/** ----------------------------------------------------------
######                          #######                                     
#     #   ##    ####  ######    #       # #    # ##### #    # #####  ###### 
#     #  #  #  #      #         #       #  #  #    #   #    # #    # #      
######  #    #  ####  #####     #####   #   ##     #   #    # #    # #####  
#     # ######      # #         #       #   ##     #   #    # #####  #      
#     # #    # #    # #         #       #  #  #    #   #    # #   #  #      
######  #    #  ####  ######    #       # #    #   #    ####  #    # ###### 
 --------------------------------------------------------------- */

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
            return found_it;
        }
    }

    return found_it;
}

/* Activates an animation whose colors match the ones in palette passed as an argument.
   All of the selected animations color must be listed in the palette, but all the palette's 
   color do not have to be listed in the animation's colors */
bool BaseFixture::activate_by_color(color_vec arg_palette, AnimationType arg_type){
    int n_anim = this->animations.size();

    // copy the fixture's animation list
        anim_vec fixtures_anim_list = this->animations;
        fixtures_anim_list.erase(fixtures_anim_list.begin());    // avoid black animation

    // randomize the list item's order
        random_device rd;
        mt19937 rng(rd());
        shuffle(fixtures_anim_list.begin(), fixtures_anim_list.end(), rng);

    bool found_it = false;
    this->activate_none(); // start by resetting the fixture to the black animation
    // Parse through the animations'list (in a random order) and select the first anim that matches the palette
    // All the animation's color must be listed int h
        for(auto each_animation : fixtures_anim_list){
            bool animation_match = true;   // starts true & becomes false if (at least) one of the animation's attributes does not match the functions arguments (animation color & type) 
            
            // check the compatibility between the current animation's & the argument type
            animation_match =  arg_type == any || each_animation->type == any || each_animation->type == arg_type ;

            // for each of the animation's colors, check if they are compatible with the argument color palette
            if(animation_match){
                for (auto each_animation_color : (*each_animation).color_palette){
                    bool color_match = false;   // becomes true if the current color matches on of the palette's color
                    for (auto each_arg_palette_color : arg_palette){
                        color_match = color_match || (each_animation_color == each_arg_palette_color);
                    }
                    animation_match = animation_match && color_match;
                }
            }

            // if the animation is a match, activate it and exit the for loop and return true, else deactivate the fixture (by activating the black animation)
            if (animation_match){
                found_it = true;
                this->activate_by_ID(each_animation->id);
                break;
            }
        }

    return found_it;
}   


void AnimationManager::set_timer(time_t duration_ms){
    this->timer_start_ms = frame.t_current_ms;
    this->timer_duration_ms = duration_ms;
    this->timer_end_ms = frame.t_current_ms + duration_ms;
}
void AnimationManager::reset_timer(){
    this->timer_start_ms = 0;
    this->timer_duration_ms = 0;
    this-> timer_end_ms = 0;
}
bool AnimationManager::timer_elapsed(){
    bool ret = this->timer_start_ms == 0 && this->timer_duration_ms == 0 && this->timer_end_ms == 0 ? false : 
             frame.t_current_ms - this->timer_start_ms > this->timer_duration_ms ? true : false;

    if (ret) this->reset_timer();   // reset timer when timer has elapsed
    return ret;
}

/** -----------------------------------
#######                                                   
#       #    # #    #  ####  ##### #  ####  #    #  ####  
#       #    # ##   # #    #   #   # #    # ##   # #      
#####   #    # # #  # #        #   # #    # # #  #  ####  
#       #    # #  # # #        #   # #    # #  # #      # 
#       #    # #   ## #    #   #   # #    # #   ## #    # 
#        ####  #    #  ####    #   #  ####  #    #  ####  
-----------------------------------                 */
#include <sstream>

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

string fcn::palette_to_string(color_vec cols, char sep){
    str_vec palette_literal;
        for (auto col : cols){
            palette_literal.push_back(colorName[(int)col]);
        }
    return fcn::vec_to_str(palette_literal, sep);
}


std::string fcn::num_to_str(int val){
    ostringstream oss;
    oss<<val;
    return oss.str();
}
std::string fcn::num_to_str(time_t val){
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
