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
    //TODO move palette definition to a dedicated funciton (for readabiliyt)

//--------------------------------------------------------------------------------
// Warehouse color palette
// Flames (red to hot colors)
    palette_magasine.push_back( color_vec{red},             1);
    palette_magasine.push_back( color_vec{gold, red},       2);
    // palette_magasine.push_back( color_vec{sodium, red},     1);
    palette_magasine.push_back( color_vec{w_white, red},    1);
// Wabi colors
    palette_magasine.push_back(color_vec{light_purple, red},      1);
    palette_magasine.push_back(color_vec{light_purple, purple},      1);
    palette_magasine.push_back(color_vec{gold, purple},     1);
    palette_magasine.push_back(color_vec{gold, blue},     2);
    palette_magasine.push_back(color_vec{gold, sodium},     2);

    palette_magasine.push_back(color_vec{light_cyan, red},        1);
    palette_magasine.push_back(color_vec{light_cyan, purple},     1);
// Tricolor
    // palette_magasine.push_back(color_vec{gold, purple, red},        1);
    // palette_magasine.push_back(color_vec{purple, sodium, red},      1);
    // palette_magasine.push_back(color_vec{gold, cyan, red},          1);
    // palette_magasine.push_back(color_vec{gold, cyan, purple},       1);

//--------------------------------------------------------------------------------
// Dasncefloor color palette
// Flames (red to hot colors)
    palette_magasine_2.push_back( color_vec{red},             1);
    palette_magasine_2.push_back( color_vec{gold, red},       1);
    palette_magasine_2.push_back( color_vec{sodium, red},     1);
    palette_magasine_2.push_back( color_vec{w_white, red},    1);
    palette_magasine_2.push_back( color_vec{c_white, red},    1);
// Wabi colors
    palette_magasine_2.push_back(color_vec{purple, red},      1);
    palette_magasine_2.push_back(color_vec{gold, purple},     1);
    palette_magasine_2.push_back(color_vec{gold, purple},     1);
    palette_magasine_2.push_back(color_vec{sodium, purple},   1);

    palette_magasine_2.push_back(color_vec{cyan, red},        1);
    palette_magasine_2.push_back(color_vec{cyan, purple},     1);
// Other color
    palette_magasine_2.push_back(color_vec{blue},           1);
    palette_magasine_2.push_back(color_vec{blue, red},      1);
    palette_magasine_2.push_back(color_vec{blue, cyan},     1);
    palette_magasine_2.push_back(color_vec{blue, c_white},  1);
    palette_magasine_2.push_back(color_vec{blue, w_white},  1);
    palette_magasine_2.push_back(color_vec{blue, gold},  1);
    palette_magasine_2.push_back(color_vec{blue, purple},   1);
    palette_magasine_2.push_back(color_vec{purple, c_white},  1);
    palette_magasine_2.push_back(color_vec{purple, w_white},  1);

//--------------------------------------------------------------------------------
// Warehouse color palette
// Flames (red to hot colors)
    palette_magasine.push_back( color_vec{red},             1);
    palette_magasine.push_back( color_vec{gold, red},       2);
    palette_magasine.push_back( color_vec{sodium, red},     1);
    palette_magasine.push_back( color_vec{w_white, red},    1);
// Wabi colors
    palette_magasine.push_back(color_vec{purple, red},      1);
    palette_magasine.push_back(color_vec{gold, purple},     1);
    palette_magasine.push_back(color_vec{gold, purple},     2);
    palette_magasine.push_back(color_vec{sodium, purple},   1);

    palette_magasine.push_back(color_vec{cyan, red},        1);
    palette_magasine.push_back(color_vec{cyan, purple},     1);
// Tricolor
    palette_magasine.push_back(color_vec{gold, purple, red},        1);
    palette_magasine.push_back(color_vec{purple, sodium, red},      1);
    palette_magasine.push_back(color_vec{gold, cyan, red},          1);
    palette_magasine.push_back(color_vec{gold, cyan, purple},       1);

//--------------------------------------------------------------------------------
// Dasncefloor color palette
// Flames (red to hot colors)
    palette_magasine_2.push_back( color_vec{red},             1);
    palette_magasine_2.push_back( color_vec{gold, red},       1);
    palette_magasine_2.push_back( color_vec{sodium, red},     1);
    palette_magasine_2.push_back( color_vec{w_white, red},    1);
    palette_magasine_2.push_back( color_vec{c_white, red},    1);
// Wabi colors
    palette_magasine_2.push_back(color_vec{purple, red},      1);
    palette_magasine_2.push_back(color_vec{gold, purple},     1);
    palette_magasine_2.push_back(color_vec{gold, purple},     1);
    palette_magasine_2.push_back(color_vec{sodium, purple},   1);

    palette_magasine_2.push_back(color_vec{cyan, red},        1);
    palette_magasine_2.push_back(color_vec{cyan, purple},     1);
// Other color
    palette_magasine_2.push_back(color_vec{blue},           1);
    palette_magasine_2.push_back(color_vec{blue, red},      1);
    palette_magasine_2.push_back(color_vec{blue, cyan},     1);
    palette_magasine_2.push_back(color_vec{blue, c_white},  1);
    palette_magasine_2.push_back(color_vec{blue, w_white},  1);
    palette_magasine_2.push_back(color_vec{blue, gold},  1);
    palette_magasine_2.push_back(color_vec{blue, purple},   1);
    palette_magasine_2.push_back(color_vec{purple, c_white},  1);
    palette_magasine_2.push_back(color_vec{purple, w_white},  1);

//---------------------------------------------------------------------------------
    //TEST Palette
    test_palette.push_back( color_vec{gold, red},                 1);
    // test_palette.push_back( color_vec{blue},                1);
    // test_palette.push_back( color_vec{purple},              1);
    // test_palette.push_back( color_vec{gold},                1);
    // test_palette.push_back( color_vec{w_white,  red},       1);
    // test_palette.push_back( color_vec{c_white,  blue},      1);
    // test_palette.push_back( color_vec{gold,     purple},    1);
    // test_palette.push_back( color_vec{gold,     red},       1);

    front_rack_init();
    rack_15_init();
    rack_40_init();
    shehds_rack_init();
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
            lead_fix = fcn::random_pick(fix_vec{&addr_led, &spot_rack_1}, {1, 1 });
            
            // activate leader animation
            balise(__FILE__, " ", __LINE__, "activate leader animation");
            leader_OK = lead_fix->activate_by_color(current_palette, leader);   // returns true if an animation matching all conditions was found
        }while(!leader_OK && ++trial_cpt<10);

        // reference the other fixtures as "backer fixtures" in a vector (for ease of acccess & modularity)
        balise(__FILE__, " ", __LINE__, "select backer fixture");
        fix_vec backer_fix;
        // for (auto fix : fix_vec{&addr_led, &front_rack, &laser}){
        for (auto fix : fix_vec{&addr_led, &spot_rack_1}){
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
        spot_rack_2.activate_by_color(current_palette);   // deal with the backstage rack separately

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

/*
#     #                                          #####                       
##   ##   ##   #    # # #    # #    # #    #    #     # #    #  ####  #    # 
# # # #  #  #   #  #  # ##  ## #    # ##  ##    #       #    # #    # #    # 
#  #  # #    #   ##   # # ## # #    # # ## #     #####  ###### #    # #    # 
#     # ######   ##   # #    # #    # #    #          # #    # #    # # ## # 
#     # #    #  #  #  # #    # #    # #    #    #     # #    # #    # ##  ## 
#     # #    # #    # # #    #  ####  #    #     #####  #    #  ####  #    #
*/
void AnimationManager::nov30_maximum_update(){

    time_ms t = frame.t_current_ms;                             // for code readability
    static color_vec warehouse_palette, dancefloor_palette;     // color palette for each zone

// -------------------------------------------------------------------------------------------------
// WareHouse LIGHTING ---------------------------------------------------------------------------------
    // Racks of spots
    // change each fixture's active animation when a timer expires. timers are initialized on a constant +- random value
    // use palette_magasine
    
    // update Warehouse palette
    static time_ms last_wh_palette_chg_ms;
    if (warehouse_palette.size()==0 || t-last_wh_palette_chg_ms > WAREH_TEMPO_PALETTE){ // if palette is empty or palette timer elapsed
        warehouse_palette = palette_magasine.get_similar_palette(warehouse_palette);    // 
        last_wh_palette_chg_ms = t;
        log(1, "New warehouse color palette : ", fcn::palette_to_string(warehouse_palette, '/'));
    }

    // update Warehouse fixture animation
    fix_vec warehouse_fixtures = {&spot_rack_3, &spot_rack_2, &spot_rack_4, &laserbox1};  // list of fixtures in the warehouse
    const int n_wareh_fix =  warehouse_fixtures.size();                         // number of fixtures
    static vector<time_t> warehouse_timestp(n_wareh_fix, 0);                    // for each fixture, stores the timestamp of the next animation change

    for(auto i_fix = 0; i_fix<n_wareh_fix; i_fix++){
        if(t - warehouse_timestp[i_fix] > 0){
            warehouse_fixtures[i_fix]->activate_by_color(warehouse_palette);    // activate a new animation
            warehouse_timestp[i_fix] = t + rand_min_max(2*WAREH_TEMPO_ANI/3, 4*WAREH_TEMPO_ANI/3);                                       // store current time as timestamp
            // log(2, warehouse_fixtures[i_fix]->name, " : ", warehouse_fixtures[i_fix]->active_animation->id, " - ", warehouse_fixtures[i_fix]->active_animation->description);
        }
    }
    
    // RED Rayz
    // update randomly every 30 seconds
    // if (t - redrayz.active_animation->t_animation_start_ms > 30000){
    //     redrayz.activate_random();
    // }

// -------------------------------------------------------------------------------------------------
// Dancefloor LIGHTING --------------------------------------------------------------------------------
/** RULES
 *  - Change color palette WHEN palette timer has elapsed AND music transitions to BEAT --> t-last_dc_palette_chg_ms > DANCEFL_TEMPO_PALETTE
 *  - Major Change in animation (pick leader & update all active ani) WHEN 
 *          palette just changed OR a long musical BREAK just reached its DROP
 *  - Minor change in animation (change 1 fixture active ani without changing leader/backer config) WHEN 
 *          timer elapsed since last transition AND music transitions to BEAT
 *  - Major change has priority over minor change  
 */


    // Update Dancefloor color palette periodically (but wait for music transition still)
    static time_ms last_dc_palette_chg_ms;
    static bool FORCE_full_ani_update = false;
    if (dancefloor_palette.size()==0 || (t-last_dc_palette_chg_ms > DANCEFL_TEMPO_PALETTE) && (sampler.state_changed && sampler.state == BEAT)){ // if palette is empty or palette timer elapsed
        FORCE_full_ani_update == true;  // set FLAG
        dancefloor_palette = palette_magasine_2.get_similar_palette(warehouse_palette);    // gt a new palette, close to the one used in the warehouse
        last_dc_palette_chg_ms = t;
        log(1, "New dancefloor color palette : ", fcn::palette_to_string(dancefloor_palette, '/'));
    }

    // On musical condition, update active Animation for one, or more fixtures
    fix_vec dancefloor_fixtures = {&addr_led, &spot_rack_1};                 // define list of fixtures
    static BaseFixture * leader = fcn::random_pick(dancefloor_fixtures);    // leading fixtures (initialization just in case)
    static time_ms t_last_df_ani_change = 0;

    // MAJOR UPDATE
    // when music goes from SUSTAINED BREAK to BEAT or when palette changes, update all fixtures (also when palette just change)
    if (frame.first_loop || (sampler.state == BEAT && sampler.previous_state==SUSTAINED_BREAK)
                         || FORCE_full_ani_update){
        FORCE_full_ani_update = false; // reset flag
        bool pick_success;
        int trial_cpt = 1;
        do{
            pick_success = true;    //initial value
            if (trial_cpt > 10) {   // if too many fails, log incident & CHANGE palette
                log(1, "Error trying to find a match for ", fcn::palette_to_string(dancefloor_palette, '/'));
                dancefloor_palette = palette_magasine_2.get_similar_palette(warehouse_palette);
            }
            
            leader = fcn::random_pick(dancefloor_fixtures, int_vec{3,1});
            for (auto fix : dancefloor_fixtures){
                AnimationType ani_type = fix == leader ? AnimationType::leader : AnimationType::backer;
                fix->activate_by_color(dancefloor_palette, ani_type);
            }

            trial_cpt++;
        }while(!pick_success); // pick_success is true if working colorplaette / leader / backer combination works, false otherwise
        t_last_df_ani_change = t;
   
    // MINOR UPDATE    -- only if no major update has occured during cycle
    // if enough time has elapsed since last change, when music transition to BEAT, update some fixtures without changing leader
    }else if(((t-t_last_df_ani_change > DANCEFL_TEMPO_ANI) && (sampler.state_changed && sampler.state==BEAT))){
        BaseFixture *fix = fcn::random_pick(dancefloor_fixtures, int_vec{1,2}); // pick a fixture (backer spots have more chance to be picked)
        AnimationType ani_type = fix == leader ? AnimationType::leader : AnimationType::backer;
        fix->activate_by_color(dancefloor_palette, ani_type);

        t_last_df_ani_change = t;
    }

}

void AnimationManager::autocolor_update(){ // test function to develop the AUTOCOLOR feature
    static color_vec palette;
    static int palette_lifespan = 3;
    
    //when time to change animation
    if (frame.first_loop
        || (sampler.state_changed && sampler.state == BEAT) && (frame.t_current_ms-t_last_change_ms > TEMPO_ANIM_CHANGE)
        || this->timer_elapsed()){

        // when time to change color palette
        if (frame.first_loop || palette_lifespan == 0){
            // pick a random palette from the mag
            palette = palette_magasine.get_random_palette();
            palette_lifespan = 2; //reset palette lifespan
            log(1, __FILE__, " ",__func__, " ", fcn::palette_to_string(palette, '/'));
        }

        //activate an animation using autocolor
        // front_rack.activate_autocolor(palette);
        spot_rack_1.activate_random(palette);
        addr_led.activate_random(palette);
        palette_lifespan--; //decrease palette lifespan
    }
}

//TODO update to support AUTOCOLOR
bool AnimationManager::test_animation_update(){
    log(4, __FILE__, " ",__func__);

    bool success = false;
    balise(fcn::num_to_str((int)cli_anim_id.size()).data());
    
    for(vector<string>::iterator anim_id_it = cli_anim_id.begin(); anim_id_it != cli_anim_id.end(); anim_id_it++){
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


/*####  #     #    #    #          #     # ####### ######  ####### 
#     # #     #   # #   #          ##   ## #     # #     # #       
#     # #     #  #   #  #          # # # # #     # #     # #       
#     # #     # #     # #          #  #  # #     # #     # #####   
#     # #     # ####### #          #     # #     # #     # #       
#     # #     # #     # #          #     # #     # #     # #       
######   #####  #     # #######    #     # ####### ######  ####### */

/** Activates animations based on received DMX control data or automatic sequence 
 * limitations : only works for addressable LED for now but support can easily be extended to other fixtures */
bool AnimationManager::controled_update(){
/* automatic sequencer :  -------------------------------------------------------------------------
    Define When the time is right to change animation base on music analysis & different timers
    This sewuencer runs constantly in parallel with  the input commands system
    WHen external settings are set to "manual", the automatic sequencer keeps doing its job in the background in case
     external setting goes back to "automatic" */
// update automatic palette when required
    static color_vec auto_palette;              //contains automatic colors
    bool auto_palette_update = false;           //
    static time_t last_palette_update_ms = 0;   //
    // choose a palette randomly at first
    if(frame.first_loop){
        auto_palette = palette_magasine.get_random_palette();
        last_palette_update_ms = frame.t_current_ms;
        auto_palette_update = true;
        if (animator.external_palette.empty()) //only display the update if external setting is set to "automatic main palette"
            log(1, "Automatic palette update : ", fcn::palette_to_string(auto_palette));
    // Then update palette every time a timer elapses AND a long break ends
    }else if((sampler.state_changed && sampler.previous_state == SUSTAINED_BREAK) && (frame.t_current_ms - last_palette_update_ms > DANCEFL_TEMPO_PALETTE)){
        auto_palette = palette_magasine.get_similar_palette(auto_palette);
        last_palette_update_ms = frame.t_current_ms;
        auto_palette_update = true;
        if (animator.external_palette.empty()) //only display the update if external setting is set to "automatic main palette"
            log(1, "Automatic palette update : ", fcn::palette_to_string(auto_palette));
    }

// Define fixtures installed
    fix_vec fixs = {&addr_led, &spot_rack_1, &spot_rack_2, &spot_rack_3, &spot_rack_4, &lasergroup1, &lasergroup2};

//update animation automaticaaly when required
    bool auto_ani_update = false;
    static time_t last_ani_update_ms = 0;
    //choose an animation randomly at first & change whenever Beat stat changes & a timer elapses
    if(frame.first_loop || sampler.state_changed && sampler.state == BEAT && frame.t_current_ms-last_ani_update_ms > DANCEFL_TEMPO_ANI){
        auto_ani_update = true;
        last_ani_update_ms = frame.t_current_ms;
        log(1, "Automatic animation update");
    }

//For each fixture installed, update animation manually when required
for (auto fix : fixs){

    bool manual_update = false; // turns true if new external control data is found
    
    // update animation manually when manual input parameters (palette, animation) change
    if (animator.new_external_palette || fix->new_external_palette || fix->new_external_animation){
        manual_update = true;
    }

// determines which setting is manual & which is automatic
    bool automatic_main_palette = animator.external_palette.empty();
    bool automatic_fix_palette = fix->external_palette.empty() && animator.external_palette.empty();
    bool automatic_fix_ani = fix->external_animation==0;

// APPLY UPDATE to fixture: 
    // if input command is received or automatic settings change (palette or animation), change animation
    if(manual_update || auto_ani_update && automatic_fix_ani || auto_palette_update && automatic_fix_palette){
        color_vec final_palette;
        // choose color palette by order of priority : manual fixture palette > manual main palette > automatic palette
        if(fix->external_palette.empty() == false){ //use external fixture's palette if available
            final_palette = fix->external_palette;
        }else if(animator.external_palette.empty() == false){   // else use external main palette if available
            final_palette = animator.external_palette;
        }else{      // else use auto palette (if both main & fixture palette are set to AUTO in the external controler)
            final_palette = auto_palette;
        }
        // choose animation by order of priority (external animation > automatic animation)
        if(fix->external_animation != 0){       // use external animation if available
            fix->activate_by_index(fix->external_animation, final_palette);
        }else{          // choose random animation
            fix->activate_random(final_palette);
        }
    }

    // reset new_XXX flags once they have been used
    fix->new_external_animation = false;
    fix->new_external_palette = false;
}
    animator.new_external_palette = false;

    /*Observed bugs :
        - when program is launched, with all external control to 0, there is no activae animation until first break
            *->might just be bad luck (random animation selection sometimes returns the BLACK animation)
        - When led palette is set to MANUAL, the automatic palette update triggers an animation change. It should not. The new
         animation keeps the led manual palette.
        - When led animation is set to MANUAL, the automatic palette update triggers an animation change. It should not. */
}

void AnimationManager::set_timer(time_t duration_ms){
    this->timer_start_ms = frame.t_current_ms;
    this->timer_duration_ms = duration_ms;
    this->timer_end_ms = frame.t_current_ms + duration_ms;
}
void AnimationManager::reset_timer(){
    this->timer_start_ms = 0;
    this->timer_duration_ms = 0;
    this->timer_end_ms = 0;
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
bool BaseFixture::activate_by_index(int i){ //obsolete with autocolor
    // log(4, __FILE__, " ",__LINE__, " ", __func__);
    if (i < this->animations.size())
        this->active_animation = this->animations[i];
    else
        this->active_animation = this->animations[0];
    
    if (this->active_animation->autocolor == false)
        this->active_animation->init();
    else
        this->active_animation->init(animator.palette_magasine.get_random_palette());   //just in cazse this function is used abusively 
    log(2, "Activating ", active_animation->id, ":", active_animation->description);
}
bool BaseFixture::activate_by_index(int i, const color_vec& palette){ //autocolor variant
    // log(4, __FILE__, " ",__LINE__, " ", __func__);
    if (i < this->animations.size())
        this->active_animation = this->animations[i];
    else
        this->active_animation = this->animations[0];
    this->active_animation->init(palette);
    log(2, "Activating ", active_animation->id, ":", active_animation->description, '\t', fcn::palette_to_string(palette));
}

// select and init an animtion randomly picked wihtin the list 
bool BaseFixture::activate_random(bool include_black){
    log(4, __FILE__, " ",__LINE__, " ", __func__);
    if (include_black)
        this->active_animation = this->animations[ rand()%(this->animations.size())];
    else
        this->active_animation = this->animations[ rand()%(this->animations.size()-1) +1];
    
    if (this->active_animation->autocolor == false)
        this->active_animation->init();
    else
        this->active_animation->init(animator.palette_magasine.get_random_palette());   //just in cazse this function is used abusively 
        
}
bool BaseFixture::activate_random(const color_vec& palette, bool include_black){  //autocolor variant 
    log(4, __FILE__, " ",__LINE__, " ", __func__);
    if (include_black)
        this->active_animation = this->animations[ rand()%(this->animations.size())];
    else
        this->active_animation = this->animations[ rand()%(this->animations.size()-1) +1];
    
    if(this->active_animation->autocolor){
        this->active_animation->init(palette);
    }else{
        this->active_animation->init();
    }
    log(2, "Activating ", active_animation->id, ":", active_animation->description, '\t', fcn::palette_to_string(palette));
}

// select and init an animation with its ID. If the ID cannot be found within the existing animations, does nothing.
bool BaseFixture::activate_by_ID(string id){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    bool found_it = false;
    
    for (vector<BaseAnimation*>::iterator anim_it = this->animations.begin(); anim_it != this->animations.end(); anim_it++){
        if ((*anim_it)->id == id){
            found_it = true;
            this->active_animation = (*anim_it);
            if(this->active_animation->autocolor){
                this->active_animation->init(animator.palette_magasine.get_random_palette()); //Quick n Dirty fix to animation testing to support AUTOCOLOR
            }else{
                this->active_animation->init();
            }
            return found_it;
        }
    }

    return found_it;
}

bool BaseFixture::activate_by_ID(string id, const color_vec& palette){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    bool found_it = false;
    
    for (vector<BaseAnimation*>::iterator anim_it = this->animations.begin(); anim_it != this->animations.end(); anim_it++){
        if ((*anim_it)->id == id){
            found_it = true;
            this->active_animation = (*anim_it);
            this->active_animation->init(palette);
            return found_it;
        }
    }

    return found_it;
}

/* Activates an animation whose colors match the ones in palette passed as an argument.
   All of the selected animations color must be listed in the palette, but all the palette's 
   color do not have to be listed in the animation's colors
   
   ATTENTION !! AUTOCOLOR shall make this function & feature obsolete --> do not use both*/
bool BaseFixture::activate_by_color(color_vec arg_palette, AnimationType arg_type){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    int n_anim = this->animations.size(); //for readability
    anim_vec candidates;                    // contains candidate animations (animations that match criterias)
    int_vec prios;                          // contains the priorities of such animations
    
    // copy the fixture's animation list
    anim_vec fixtures_anim_list = this->animations;
    fixtures_anim_list.erase(fixtures_anim_list.begin());    // avoid black (first) animation

    bool found_it = false;  //flag that turns true when final animation is found
    this->activate_none(); // start by resetting the fixture to the black animation in case no match is found

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
                candidates.push_back(each_animation);       // store the animation in vector
                prios.push_back(each_animation->priority); // store the animation probability setting in other vector
            }
        }


    balise(__FILE__, " ", __LINE__, "candidate animations listed");
    if (candidates.size()>0){
        BaseAnimation* anim = fcn::random_pick(candidates, prios);
        this->activate_by_ptr(anim);
        found_it=true;
    }

    return found_it;
}   

/*Activates an animation using autocolor feature. */
bool BaseFixture::activate_autocolor(color_vec& palette){
    // log(1, this->name, " ", __func__);
    int n_anim = this->animations.size(); //for readability
    anim_vec candidates;                    // contains candidate animations (animations that match criterias)
    int_vec prios;                          // contains the priorities of such animations

    // copy the fixture's animation list
    anim_vec fixtures_anim_list = this->animations;
    fixtures_anim_list.erase(fixtures_anim_list.begin());    // avoid black (first) animation
    
    bool found_it = false;  //flag that turns true when final animation is found
    this->activate_none(); // start by resetting the fixture to the black animation in case no match is found

    // Parse the fixture's animation list
        /* pick animation matching the following criteria :
            - autocolor = true
            - authorised color*/
    for(auto each_animation : fixtures_anim_list){
        bool animation_match;
        // check the compatibility between the current animation's & the argument type
        animation_match = each_animation->is_autocolor_compatible(palette);

        // if the animation is a match, activate it and exit the for loop and return true, else deactivate the fixture (by activating the black animation)
        if (animation_match){
            candidates.push_back(each_animation);      // store the animation in vector
            prios.push_back(each_animation->priority); // store the animation probability setting in other vector
        }
        

    }

    // log(2, "Candidates listed ");
    if (candidates.size()>0){
        BaseAnimation* anim = fcn::random_pick(candidates, prios);
        this->activate_by_ptr(anim, palette);
        found_it=true;
        // log(2, "Selected : ", anim->id);
    }else{
        // log(2, "no candidates");
    }

    return found_it;
}

bool BaseFixture::activate_by_ptr(BaseAnimation * anim_ptr){
    this->active_animation = anim_ptr;
    this->active_animation->init();
}
bool BaseFixture::activate_by_ptr(BaseAnimation * anim_ptr, const color_vec& palette){
    this->active_animation = anim_ptr;
    this->active_animation->init(palette);
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

std::string fcn::ms_to_hhmmssms(time_ms input_ms){
    ostringstream oss;
    int hou = input_ms/1000/60/60;
    int min = (input_ms-hou*60*60*1000)/1000/60;
    int sec = (input_ms-hou*60*60*1000-min*60*1000)/1000;
    int ms = (input_ms-hou*60*60*1000-min*60*1000-sec*1000);
    oss << hou << ":" << min << ":" << sec << ":" << ms;
    return oss.str();
}
std::string fcn::ms_to_hhmmss(time_ms input_ms){
    ostringstream oss;
    int hou = input_ms/1000/60/60;
    int min = (input_ms-hou*60*60*1000)/1000/60;
    int sec = (input_ms-hou*60*60*1000-min*60*1000)/1000;
    int ms = (input_ms-hou*60*60*1000-min*60*1000-sec*1000);
    oss << hou << ":" << min << ":" << sec;
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



