#include <iostream>
#include <cmath>
#include <vector>


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
    log(4, __FILE__, " ",__func__);
    palette_magasine.push_back(    color_vec{red}    ,2   );
 // palette_magasine.push_back(    color_vec{sodium} ,1   );
 // palette_magasine.push_back(    color_vec{orange} ,1   );
 // palette_magasine.push_back(    color_vec{yellow} ,1   );
    palette_magasine.push_back(    color_vec{gold}   ,1   );
    palette_magasine.push_back(    color_vec{w_white}  ,1   );
 // palette_magasine.push_back(    color_vec{cyan}   ,1   );
    palette_magasine.push_back(    color_vec{blue}   ,2   );
    palette_magasine.push_back(    color_vec{purple} ,1   );
 // palette_magasine.push_back(    color_vec{magenta},1   );
 // palette_magasine.push_back(    color_vec{pink}   ,1   );
 // palette_magasine.push_back(    color_vec{green}  ,1   );
    
    palette_magasine.push_back(     color_vec{w_white, red}       ,1      );
 // palette_magasine.push_back(     color_vec{white, sodium}    ,1      );
 // palette_magasine.push_back(     color_vec{white, orange}    ,1      );
 // palette_magasine.push_back(     color_vec{white, yellow}    ,1      );
 // palette_magasine.push_back(     color_vec{white, gold}      ,1      );
 // palette_magasine.push_back(     color_vec{white, white}     ,1      );
 // palette_magasine.push_back(     color_vec{white, cyan}      ,1      );
    palette_magasine.push_back(     color_vec{w_white, blue}      ,1      );
    palette_magasine.push_back(     color_vec{w_white, purple}    ,1      );
 // palette_magasine.push_back(     color_vec{white, magenta}   ,1      );
 // palette_magasine.push_back(     color_vec{white, pink}      ,1      );
 // palette_magasine.push_back(     color_vec{white, green}     ,1      );


    palette_magasine.push_back(    color_vec{cyan, magenta}    ,1       );
    palette_magasine.push_back(    color_vec{gold, red}        ,3       );
    palette_magasine.push_back(    color_vec{gold, orange}     ,1       );
    palette_magasine.push_back(    color_vec{gold, sodium}     ,1       );
    palette_magasine.push_back(    color_vec{gold, blue}       ,1       );
    palette_magasine.push_back(    color_vec{red, blue}        ,3       );
    palette_magasine.push_back(    color_vec{magenta, blue}    ,3       );
    palette_magasine.push_back(    color_vec{red, purple}      ,3       );
    palette_magasine.push_back(    color_vec{gold, purple}     ,2       );
    palette_magasine.push_back(    color_vec{blue, purple}     ,1       );
    palette_magasine.push_back(    color_vec{cyan, purple}     ,1       );
    palette_magasine.push_back(    color_vec{cyan, red}        ,3       );
    palette_magasine.push_back(    color_vec{blue, cyan}       ,1       );
    palette_magasine.push_back(    color_vec{purple, magenta}  ,1       );
    palette_magasine.push_back(    color_vec{red, purple}      ,2       );
    
    // Nouveau
    palette_magasine.push_back(    color_vec{green, cyan}           ,1       );
    palette_magasine.push_back(    color_vec{blue, orange}          ,1       );
    palette_magasine.push_back(    color_vec{blue, sodium}          ,1       );
    palette_magasine.push_back(    color_vec{orange, blue, cyan}    ,1       );
    
    front_rack_init();
    back_rack_init();
    back_rack2_init();
    global_rack_init();
}

/** Based on the musical analysis (music.state) and the current time, this function 
 * decides when to switch animation
 * When it switches, it selects randomly within the animations list without trying to match
 * them by color or style 
 * */
void AnimationManager::random_update(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

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
    log(4, __FILE__, " ",__func__);

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
void AnimationManager::show_update(){
    balise(__FILE__, " ", __LINE__, "animator Test update");
    log(4, __FILE__, " ",__func__);

    static color_vec current_palette;
    static int palette_lifespan;
    /** Animation switch occurs based on different principles :
     *  - (legacy) change when a MAX timer has elapsed AND when the Beat State changes
     *  - (new) Change when a custom, sequence specific  timer has elpased (i.e. -> to avoid long periods of stroboscopic animation); */
    if (  frame.first_loop
        || (sampler.state_changed && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE))
        || this->timer_elapsed()){

        balise(__FILE__, " ", __LINE__, "animator update condition met");

        if (frame.first_loop){
            current_palette = palette_magasine.get_random_palette();
            // palette_lifespan = 5;
        }

        if (frame.first_loop || palette_lifespan == 0){
            balise(__FILE__, " ", __LINE__, "animator palette update");
            // color_vec::size_type i = rand_min_max(0, colorPalettes.size());
            current_palette = palette_magasine.get_similar_palette(current_palette);
            switch(current_palette.size()){
	    	case 1 :
	    		palette_lifespan = PAL_LIFESPAN_MONO;
			    break;
		    case 2 :
			    palette_lifespan = PAL_LIFESPAN_BICO;
			    break;
		    default :
			    palette_lifespan = PAL_LIFESPAN_BICO;
			break;
            }

            log(1, "Color palette ", fcn::palette_to_string(current_palette, '/'));
   
        }

        BaseFixture* lead_fix;
        bool leader_OK = true;
        int trial_cpt = 0;
        do{
            // select a leader among Led bars, Front rack, and Laser
            balise(__FILE__, " ", __LINE__, "select leader fixture");
            // lead_fix = fcn::random_pick(fix_vec{&led, &front_rack, & laser, &spider}, {4,2,2,3});
            // lead_fix = fcn::random_pick(fix_vec{&addr_led, &front_rack, &laser}, {4, 2, 1});
            // lead_fix = &front_rack;
            lead_fix = fcn::random_pick(fix_vec{&addr_led, &front_rack}, {1, 1 });
            
            // activate leader animation
            balise(__FILE__, " ", __LINE__, "activate leader animation");
            leader_OK = lead_fix->activate_by_color(current_palette, leader);   // returns true if an animation matching all conditions was found
        }while(!leader_OK && ++trial_cpt<10);

        // reference the other fixtures as "backer fixtures" in a vector (for ease of acccess & modularity)
        balise(__FILE__, " ", __LINE__, "select backer fixture");
        fix_vec backer_fix;
        // for (auto fix : fix_vec{&addr_led, &front_rack, &laser}){
        for (auto fix : fix_vec{&addr_led, &front_rack}){
        // for (auto fix : fix_vec{&led, &front_rack}){
            if (fix != lead_fix){
                backer_fix.push_back(fix);
            }
        }
        // sort the backer fixtures in a random order
        random_device rd;
        mt19937 rng(rd());
        shuffle(backer_fix.begin(), backer_fix.end(), rng);

        /** pick randomly how many backer fixtures will light up to back the leader fixture
         *  40% of time there should be 2 backer (3 fixtures total)
         *  40% of time there should be 1 backer
         *  20% of time ther should be NO backer */
        int back_fix_n = 1;

        // log the results
        log(2, fcn::num_to_str(palette_lifespan), ") Leader->", lead_fix->name, " + ", fcn::num_to_str(back_fix_n), " backers");

        // activate backer animations based on the new settings
        balise(__FILE__, " ", __LINE__, "activate backer animation");
        for (int i = 0; i<backer_fix.size(); i++){
            if (i<back_fix_n)
                backer_fix[i]->activate_by_color(current_palette, backer);
            else
                backer_fix[i]->activate_none();
        }
        
        balise(__FILE__, " ", __LINE__, "activate backstage rack  animation");
        back_rack.activate_by_color(current_palette);   // deal with the backstage rack separately

        // spider.activate_by_color(current_palette);

        t_last_change_ms = frame.t_current_ms;
        palette_lifespan-- ;
    }

    // // Manage Lyre :
    // static time_t last_spider_switch = 0;
    // if (frame.first_loop || frame.t_current_ms - last_spider_switch > SPIDER_ANI_DURA){
    //     spider.activate_by_color(current_palette);
    //     // log(1, "Switch Spider animation --> ", spider.active_animation->description);
    //     last_spider_switch = frame.t_current_ms;
    // }
}

bool AnimationManager::test_animation(){
    log(4, __FILE__, " ",__func__);

    bool success = false;
    balise(fcn::num_to_str((int)vec_anim_id.size()).data());
    for(vector<string>::iterator anim_id_it = vec_anim_id.begin(); anim_id_it != vec_anim_id.end(); anim_id_it++){
        string s_anim_id = (*anim_id_it);
        balise(s_anim_id.data());

        for (auto fix : fixtures){
            balise(fix->name);
            success = fix->activate_by_ID(s_anim_id);
            if (success) {
                log(1, "Testing animation ", s_anim_id);
                break;
            }
        }

        if (!success){
            cout << "Animation ID prefix unknown..." << endl;
            success = false;
        }
    }
    return success;
}

// activates animations based on DMX data
bool AnimationManager::controled_animator(const DMX_vec data){

    // Test 1
    //extract DMX values in variables
    int i = 0;
    uint8_t spot_1_DIMMER = data[0];
    uint8_t spot_2_DIMMER = data[1];
    uint8_t Addr_LED_DIMMER = data[2];

    front_rack.activate_by_index(data[3]);
    front_rack.set_master(data[0]);

    back_rack.activate_by_index(data[4]);
    front_rack.set_master(data[1]);

    addr_led.activate_by_index(data[5]);
    addr_led.master = data[2];



    // // Last, set memorized data to current data and leave
    // WS_memorized_data.assign(data.at(WS_DIMMER), data.at(WS_C2)+1);
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

    if (ret) {
        this->reset_timer();   // reset timer when timer has elapsed
        log(2, "Stroboscopic animations time out...");
    }
    return ret;
}



AnimationManager animator;


/** 
######                          #######                                     
#     #   ##    ####  ######    #       # #    # ##### #    # #####  ###### 
#     #  #  #  #      #         #       #  #  #    #   #    # #    # #      
######  #    #  ####  #####     #####   #   ##     #   #    # #    # #####  
#     # ######      # #         #       #   ##     #   #    # #####  #      
#     # #    # #    # #         #       #  #  #    #   #    # #   #  #      
######  #    #  ####  ######    #       # #    #   #    ####  #    # ###### 
  */

// toggles blackout boolean
void BaseFixture::blackout(bool b){
    this->b_blackout = b;
}

// deactivate fixture (display the "BLACK" animations)
bool BaseFixture::activate_none(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    this->active_animation = this->animations[0]; // IMPORTANT : the first animation mut ALWAYS be a complete blackout (all color/position channels to 0)
    this->active_animation->init();
}

// selects and init the i_th animation within the list (i being the argument).
// If i out of range, select the first (black) 
bool BaseFixture::activate_by_index(int i){
    // log(4, __FILE__, " ",__LINE__, " ", __func__);
    if (i < this->animations.size())
        this->active_animation = this->animations[i];
    else
        this->active_animation = this->animations[0];
    this->active_animation->init();
    log(1, "Activating ", active_animation->id, ":", active_animation->description);
}

// select and init an animtion randomly picked wihtin the list 
bool BaseFixture::activate_random(bool include_black){
    log(4, __FILE__, " ",__LINE__, " ", __func__);
    if (include_black)
        this->active_animation = this->animations[ rand()%(this->animations.size())];
    else
        this->active_animation = this->animations[ rand()%(this->animations.size()-1) +1];
    this->active_animation->init();
}

// select and init an animation with its ID. If the ID cannot be found within the existing animations, does nothing.
bool BaseFixture::activate_by_ID(string id){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

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
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    int n_anim = this->animations.size();
    anim_vec candidates;
    int_vec probas;
    // copy the fixture's animation list
        anim_vec fixtures_anim_list = this->animations;
        fixtures_anim_list.erase(fixtures_anim_list.begin());    // avoid black (first) animation

    bool found_it = false;
    this->activate_none(); // start by resetting the fixture to the black animation

    // cout << "Palette : " << fcn::palette_to_string(arg_palette, '/');
    // cout << ((arg_type == leader) ? "  (lead.)" : (arg_type == backer) ? "  (back.)" : "  (any)")  <<  endl;

    // cout << "Animations : " << endl;
    // for (auto anim : fixtures_anim_list){
    //     cout << anim->id << " : " << fcn::palette_to_string(anim->color_palette, '/') << endl;
    // }

    // Parse through the animations'list (in a random order) and select the first anim that matches the palette
    // All the animation's color must be listed int h
        for(auto each_animation : fixtures_anim_list){
            bool animation_match = true;   // starts true & becomes false if (at least) one of the animation's attributes does not match the functions arguments (animation color & type) 
            
            // check the compatibility between the current animation's & the argument type
            animation_match =  arg_type == any || each_animation->type == any || each_animation->type == arg_type ;

            // for each of the animation's colors, check if they are compatible with the argument color palette
            if(animation_match){
                for (auto each_animation_color : each_animation->color_palette){
                    bool color_match = false;   // becomes true if the current color matches on of the palette's color
                    for (auto each_arg_palette_color : arg_palette){
                        color_match = color_match || (each_animation_color == each_arg_palette_color);
                    }
                    animation_match = animation_match && color_match;
                }
            }

            // if the animation is a match, activate it and exit the for loop and return true, else deactivate the fixture (by activating the black animation)
            if (animation_match){

                candidates.push_back(each_animation);
                probas.push_back(each_animation->priority);

                // found_it = true;
                // this->activate_by_ID(each_animation->id);
                // break;
            }
        }

        // cout << "Candidates : " << endl; 
        // for (auto anim : candidates){
        //     cout << anim->id << " : " << fcn::palette_to_string(anim->color_palette, '/') << "\t";
        //     cout << ((anim->type == leader) ? "  (lead.)" : (anim->type == backer) ? "  (back.)" : "  (any)")  <<  endl;

        // }


    balise(__FILE__, " ", __LINE__, "candidat animations found");
    if (candidates.size()>0){
        BaseAnimation* anim = fcn::random_pick(candidates, probas);
        this->activate_by_ptr(anim);
        found_it=true;

        // cout << "Winner : " << endl; 
        // cout << anim->id << " : " << fcn::palette_to_string(anim->color_palette, '/') << endl;
        
    }

    return found_it;
}   

bool BaseFixture::activate_by_ptr(BaseAnimation * anim_ptr){
    this->active_animation = anim_ptr;
    this->active_animation->init();
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


