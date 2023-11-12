#include <cmath>

#include "spot.h"
#include "sysfcn.h"
#include "debug.h"

using namespace std;

SpotFixture spot_1(73,  8, "Spot 1 (74)", 1);     
SpotFixture spot_2(81,  8, "Spot 2 (82)", 2);     
SpotFixture spot_3(89,  8, "Spot 3 (90)", 3);     
SpotFixture spot_4(97,  8, "Spot 4 (98)", 4);     
SpotFixture spot_5(105, 8, "Spot 5 (106)", 5);     
SpotFixture spot_6(113, 8, "Spot 6 (114)", 6);     
SpotFixture spot_7(121, 8, "Spot 7 15° (122)", 7);  

// SpotFixture spot_8(130, 8, "Spot 8 (130)");     

/* --------------------------------------------------------------------

 #####  ######  ####### ####### 
#     # #     # #     #    #    
#       #     # #     #    #    
 #####  ######  #     #    #    
      # #       #     #    #    
#     # #       #     #    #    
 #####  #       #######    #    

/ ----------------------------------------------------------------------- */




/* --------------------------------------------------------------------
 #####  ######  ####### #######    ######     #     #####  #    #  #####  
#     # #     # #     #    #       #     #   # #   #     # #   #  #     # 
#       #     # #     #    #       #     #  #   #  #       #  #   #       
 #####  ######  #     #    #       ######  #     # #       ###     #####  
      # #       #     #    #       #   #   ####### #       #  #         # 
#     # #       #     #    #       #    #  #     # #     # #   #  #     # 
 #####  #       #######    #       #     # #     #  #####  #    #  #####  

/ ----------------------------------------------------------------------- */
SpotRack front_rack(spot_vec{&spot_1, &spot_2, &spot_3, &spot_4}, "Front Rack", 1);
SpotRack back_rack(spot_vec{&spot_5, &spot_6, &spot_7}, "Back Rack", 2);

void SpotRack::init(){
    balise(1, "Rack initialized with ", fcn::num_to_str(this->rack_size).data(), " spots !");

    switch (this->id){

        /**
        ####### ######  ####### #     # ####### 
        #       #     # #     # ##    #    #    
        #       #     # #     # # #   #    #    
        #####   ######  #     # #  #  #    #    
        #       #   #   #     # #   # #    #    
        #       #    #  #     # #    ##    #    
        #       #     # ####### #     #    #    
        */
        case 1: //Front Rack
        //this->animations.push_back();
        // Animation 1 : Backgrnd color + random soft flashes
        this->animations.push_back(new SpotRackAnimation1(this, black,         black,       8000, 1000,   " ", "FR.0", backer));

        

        // Animation 2: Stroboscope --> To be used as LEAD animation
        // Very Fast
        this->animations.push_back(new SpotRackAnimation2(this, white,     STRB_FASTEST, "white, VFAST strobe",     "FR.1.1.6",     leader));
        this->animations.push_back(new SpotRackAnimation2(this, gold,      STRB_FASTEST, "gold, VFAST strobe",      "FR.1.1.5",     leader));
        this->animations.push_back(new SpotRackAnimation2(this, cyan,      STRB_FASTEST, "cyan, VFAST strobe",      "FR.1.1.7",     leader));
        this->animations.push_back(new SpotRackAnimation2(this, red,       STRB_FASTEST, "red, VFAST strobe",       "FR.1.1.1",     leader));
        this->animations.push_back(new SpotRackAnimation2(this, blue,      STRB_FASTEST, "blue, 8 strobe",          "FR.1.1.8",     leader));
        this->animations.push_back(new SpotRackAnimation2(this, pink,      STRB_FASTEST, "pink, VFAST strobe",      "FR.1.1.11",    leader));
        this->animations.push_back(new SpotRackAnimation2(this, magenta,   STRB_FASTEST, "magenta, VFAST strobe",   "FR.1.1.10",    leader));
        this->animations.push_back(new SpotRackAnimation2(this, purple,    STRB_FASTEST, "purple, VFAST strobe",    "FR.1.1.9",     leader));


        this->animations.push_back(new SpotRackAnimation2(this, white,     STRB_SLOW, "white, SLW strobe",     "FR.1.4.6",  leader));
        this->animations.push_back(new SpotRackAnimation2(this, gold,      STRB_SLOW, "gold, SLW strobe",      "FR.1.4.5",  leader));
        this->animations.push_back(new SpotRackAnimation2(this, cyan,      STRB_SLOW, "cyan, SLW strobe",      "FR.1.4.7",  leader));
        this->animations.push_back(new SpotRackAnimation2(this, red,       STRB_SLOW, "red, SLW strobe",       "FR.1.4.1",  leader));
        this->animations.push_back(new SpotRackAnimation2(this, blue,      STRB_SLOW, "blue, SLW strobe",      "FR.1.4.8",  leader));
        this->animations.push_back(new SpotRackAnimation2(this, pink,      STRB_SLOW, "pink, SLW strobe",      "FR.1.4.11", leader));
        this->animations.push_back(new SpotRackAnimation2(this, magenta,   STRB_SLOW, "magenta, SLW strobe",   "FR.1.4.10", leader));
        this->animations.push_back(new SpotRackAnimation2(this, purple,    STRB_SLOW, "purple, SLW strobe",    "FR.1.4.9",  leader));

        // Animation 1
        // Bubbles (short & fast) --> to be used as solo animation during breaks
        this->animations.push_back(new SpotRackAnimation1(this, black,    white,       1500, 600,   "white fast bubbles",       "FR.2.1.6", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    gold,        1500, 600,   "gold fast bubbles",        "FR.2.1.5", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    cyan,        1500, 600,   "cyan fast bubbles",        "FR.2.1.7", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    red,         1500, 600,   "red fast bubbles",         "FR.2.1.1", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    blue,        1500, 600,   "blue fast bubbles",        "FR.2.1.8", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    pink,        1500, 600,   "pink fast bubbles",        "FR.2.1.11", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    magenta,     1500, 600,   "magenta fast bubbles",     "FR.2.1.10", leader));
        this->animations.push_back(new SpotRackAnimation1(this, black,    purple,      1500, 600,   "purple fast bubbles",      "FR.2.1.9", leader));
        // Bubbles (short & slower) --> to be used as backer animation with LED (or else)
        this->animations.push_back(new SpotRackAnimation1(this, black,    white,       2500, 400,   "white slow bubbles",       "FR.2.2.6", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    gold,        2500, 400,   "gold slow bubbles",        "FR.2.2.5", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    cyan,        2500, 400,   "cyan slow bubbles",        "FR.2.2.7", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    red,         2500, 400,   "red slow bubbles",         "FR.2.2.1", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    blue,        2500, 400,   "blue slow bubbles",        "FR.2.2.8", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    pink,        2500, 400,   "pink slow bubbles",        "FR.2.2.11", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    magenta,     2500, 400,   "magenta slow bubbles",     "FR.2.2.10", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black,    purple,      2500, 400,   "purple slow bubbles",      "FR.2.2.9", backer));

        break;

        /**
        ######     #     #####  #    # 
        #     #   # #   #     # #   #  
        #     #  #   #  #       #  #   
        ######  #     # #       ###    
        #     # ####### #       #  #   
        #     # #     # #     # #   #  
        ######  #     #  #####  #    # 
        */
        case 2: //Back Rack
        this->animations.push_back(new SpotRackAnimation1(this, black,         black,       100000, 1000,   " ", "BR.0", backer));
        // Monochrome Background
        this->animations.push_back(new SpotRackAnimation1(this, red,      3000, 1500, "Red background",        "BR.1", backer));
        this->animations.push_back(new SpotRackAnimation1(this, sodium,   3000, 1500, "Sodium background",     "BR.2", backer));
        this->animations.push_back(new SpotRackAnimation1(this, orange,   3000, 1500, "Orange background",     "BR.3", backer));
        this->animations.push_back(new SpotRackAnimation1(this, yellow,   3000, 1500, "Yellow background",     "BR.4", backer));
        this->animations.push_back(new SpotRackAnimation1(this, gold,     3000, 1500, "Gold background",       "BR.5", backer));
        this->animations.push_back(new SpotRackAnimation1(this, white,    3000, 1500, "White background",      "BR.6", backer));
        this->animations.push_back(new SpotRackAnimation1(this, cyan,     3000, 1500, "Cyan background",       "BR.7", backer));
        this->animations.push_back(new SpotRackAnimation1(this, blue,     3000, 1500, "Blue background",       "BR.8", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,   3000, 1500, "Purple background",     "BR.9", backer));
        this->animations.push_back(new SpotRackAnimation1(this, magenta,  3000, 1500, "Magenta background",    "BR.10", backer));
        this->animations.push_back(new SpotRackAnimation1(this, pink,     3000, 1500, "Pink background",       "BR.11", backer));
        this->animations.push_back(new SpotRackAnimation1(this, green,    3000, 1500, "Green background",      "BR.12", backer));
        
        // Color Bubbles on Black background
        this->animations.push_back(new SpotRackAnimation1(this, black, red,      3000, 1500, "Red bubbles",     "BR.1.1.1", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, sodium,   3000, 1500, "Sodium bubbles",  "BR.1.1.2", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, orange,   3000, 1500, "Orange bubbles",  "BR.1.1.3", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, yellow,   3000, 1500, "Yellow bubbles",  "BR.1.1.4", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, gold,     3000, 1500, "Gold bubbles",    "BR.1.1.5", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, white,    3000, 1500, "White bubbles",   "BR.1.1.6", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, cyan,     3000, 1500, "Cyan bubbles",    "BR.1.1.7", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, blue,     3000, 1500, "Blue bubbles",    "BR.1.1.8", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, purple,   3000, 1500, "Purple bubbles",  "BR.1.1.9", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, magenta,  3000, 1500, "Magenta bubbles", "BR.1.1.10", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, pink,     3000, 1500, "Pink bubbles",    "BR.1.1.11", backer));
        this->animations.push_back(new SpotRackAnimation1(this, black, green,    3000, 1500, "Green bubbles",   "BR.1.1.12", backer));
        // Color Bubbles on same color background
        this->animations.push_back(new SpotRackAnimation1(this, red,      red,      3000, 1500, "Red bubbles, Red background",         "BR.1.2.1", backer));
        this->animations.push_back(new SpotRackAnimation1(this, sodium,   sodium,   3000, 1500, "Sodium bubbles, Sodium background",   "BR.1.2.2", backer));
        this->animations.push_back(new SpotRackAnimation1(this, orange,   orange,   3000, 1500, "Orange bubbles, Orange background",   "BR.1.2.3", backer));
        this->animations.push_back(new SpotRackAnimation1(this, yellow,   yellow,   3000, 1500, "Yellow bubbles, Yellow background",   "BR.1.2.4", backer));
        this->animations.push_back(new SpotRackAnimation1(this, gold,     gold,     3000, 1500, "Gold bubbles, Gold background",       "BR.1.2.5", backer));
        this->animations.push_back(new SpotRackAnimation1(this, white,    white,    3000, 1500, "White bubbles, White background",     "BR.1.2.6", backer));
        this->animations.push_back(new SpotRackAnimation1(this, cyan,     cyan,     3000, 1500, "Cyan bubbles, Cyan background",       "BR.1.2.7", backer));
        this->animations.push_back(new SpotRackAnimation1(this, blue,     blue,     3000, 1500, "Blue bubbles, Blue background",       "BR.1.2.8", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,   purple,   3000, 1500, "Purple bubbles, Purple background",   "BR.1.2.9", backer));
        this->animations.push_back(new SpotRackAnimation1(this, magenta,  magenta,  3000, 1500, "Magenta bubbles, Magenta background", "BR.1.2.10", backer));
        this->animations.push_back(new SpotRackAnimation1(this, pink,     pink,     3000, 1500, "Pink bubbles, Pink background",       "BR.1.2.11", backer));
        this->animations.push_back(new SpotRackAnimation1(this, green,    green,    3000, 1500, "Green bubbles, Green background",     "BR.1.2.12", backer));
        // White Bubbles on colored background
        this->animations.push_back(new SpotRackAnimation1(this, red,     white,  3000, 1500, "White bubbles, Red background",      "BR.1.3.1", backer));
        this->animations.push_back(new SpotRackAnimation1(this, sodium,  white,  3000, 1500, "White bubbles, Sodium background",   "BR.1.3.2", backer));
        this->animations.push_back(new SpotRackAnimation1(this, orange,  white,  3000, 1500, "White bubbles, Orange background",   "BR.1.3.3", backer));
        this->animations.push_back(new SpotRackAnimation1(this, yellow,  white,  3000, 1500, "White bubbles, Yellow background",   "BR.1.3.4", backer));
        this->animations.push_back(new SpotRackAnimation1(this, gold,    white,  3000, 1500, "White bubbles, Gold background",     "BR.1.3.5", backer));
        this->animations.push_back(new SpotRackAnimation1(this, white,   white,  3000, 1500, "White bubbles, White background",    "BR.1.3.6", backer));
        this->animations.push_back(new SpotRackAnimation1(this, cyan,    white,  3000, 1500, "White bubbles, Cyan background",     "BR.1.3.7", backer));
        this->animations.push_back(new SpotRackAnimation1(this, blue,    white,  3000, 1500, "White bubbles, Blue background",     "BR.1.3.8", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,  white,  3000, 1500, "White bubbles, Purple background",   "BR.1.3.9", backer));
        this->animations.push_back(new SpotRackAnimation1(this, magenta, white,  3000, 1500, "White bubbles, Magenta background",  "BR.1.3.10", backer));
        this->animations.push_back(new SpotRackAnimation1(this, pink,    white,  3000, 1500, "White bubbles, Pink background",     "BR.1.3.11", backer));
        this->animations.push_back(new SpotRackAnimation1(this, green,   white,  3000, 1500, "White bubbles, Green background",    "BR.1.3.12", backer));

        // Color Bubbles on different color background
        this->animations.push_back(new SpotRackAnimation1(this, red,     blue,   3000, 1500, "blue bubbles, red background",       "BR.1.4.1", backer));
        this->animations.push_back(new SpotRackAnimation1(this, blue,    red,    3000, 1500, "red bubbles, blue background",       "BR.1.4.2", backer));
        this->animations.push_back(new SpotRackAnimation1(this, red,     cyan,   3000, 1500, "cyan bubbles, red background",       "BR.1.4.3", backer));
        this->animations.push_back(new SpotRackAnimation1(this, magenta, cyan,   3000, 1500, "cyan bubbles, magenta background",   "BR.1.4.4", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,  gold,   3000, 1500, "gold bubbles, purple background",    "BR.1.4.5", backer));
        this->animations.push_back(new SpotRackAnimation1(this, red,     gold,   3000, 1500, "gold bubbles, red background",       "BR.1.4.6", backer));
        this->animations.push_back(new SpotRackAnimation1(this, orange,  gold,   3000, 1500, "gold bubbles, orange background",    "BR.1.4.7", backer));
        this->animations.push_back(new SpotRackAnimation1(this, sodium,  gold,   3000, 1500, "gold bubbles, sodium background",    "BR.1.4.8", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,  cyan,   3000, 1500, "cyan bubbles, purple background",    "BR.1.4.9", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,  pink,   3000, 1500, "pink bubbles, purple background",    "BR.1.4.10", backer));
        this->animations.push_back(new SpotRackAnimation1(this, purple,  cyan,   3000, 1500, "cyan bubbles, purple background",    "BR.1.4.11", backer));
        this->animations.push_back(new SpotRackAnimation1(this, pink,    cyan,   3000, 1500, "cyan bubbles, pink background",      "BR.1.4.12", backer));
        
        break;
        default:
        break;
    }

    this->activate_by_index(0);
}

void SpotRack::init_back(){
    this->rack_size = this->spots.size();
    //this->animations.push_back();
}

/**
######   #####  ######  #     #    #######               
#     # #     # #     # #  #  #    #        ####  #    # 
#     # #       #     # #  #  #    #       #    # ##   # 
######  #  #### ######  #  #  #    #####   #      # #  # 
#   #   #     # #     # #  #  #    #       #      #  # # 
#    #  #     # #     # #  #  #    #       #    # #   ## 
#     #  #####  ######   ## ##     #        ####  #    # 
*/

DMX_vec SpotRack::RGBW(simpleColor c, int intensity){
    switch (c)
    {
    case black:
        return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
        break;
    case red:
        return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);
        break;
    case green:
        return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 161.0/255*intensity);
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

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####                 #   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     #               ##   
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #                    # #   
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####     #####       #   
####### #   # #  #  #     # #######    #     #  #     # #   # #       #                #   
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     #                #   
#     # #     # ### #     # #     #    #    ### ####### #     #  #####               ##### 
*/
void SpotRackAnimation1::init(){
    BaseAnimation::init();
    this->fixture->reset_spots();

    this->p_ms = vector<int>{rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms)};
    
    const int n_spot = this->fixture->spots.size();
    this->t_next.resize(n_spot);
    this->t_prev.resize(n_spot);
    for (int i=0; i<n_spot; i++){
        t_next[i] = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2);
        t_prev[i] = 0;
    }
}

void SpotRackAnimation1::new_frame(){
    BaseAnimation::new_frame();

    long t = frame.t_current_ms;       // for readability
    int n_spot = this->fixture->rack_size;   // for readability
    
    // update 5 sinewaves of different period
    vector<double> s = {sin(2*M_PI*t/p_ms[0]), sin(2*M_PI*t/p_ms[1]), sin(2*M_PI*t/p_ms[2]), sin(2*M_PI*t/p_ms[3]), sin(2*M_PI*t/p_ms[4]) };
    
    // for each spot "i" of the rack
    for (int i_spot=0; i_spot < n_spot; i_spot++){
        DMX_vec backgd_RGBW(4);        
        // compute the background color values : 
            backgd_RGBW[R] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[R] * (1 + fluct_col*s[(i_spot+0)%5]))  ,0),255);
            backgd_RGBW[G] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[G] * (1 + fluct_col*s[(i_spot+1)%5]))  ,0),255);
            backgd_RGBW[B] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[B] * (1 + fluct_col*s[(i_spot+2)%5]))  ,0),255);
            backgd_RGBW[W] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[W] * (1 + fluct_col*s[(i_spot+3)%5]))  ,0),255);
        // ------------------------------- limit to 0-255 ---------------- Spot Intensity    *  RGBW pixel intensity                            ;
        
        // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
            double flash_intensity; // 0 by default
            if (flash_activation){
                // when the flash passes, compute the next flash timestamp and update prev flash
                if (t > this->t_next[i_spot]){

                    this->t_prev[i_spot] = this->t_next[i_spot];
                    this->t_next[i_spot] = this->t_next[i_spot] + rand_min_max(this->flash_len, 2*n_spot*this->rand_const_ms);
                    // if (fixture->id == 1) log(1, fixture->name, " ", fcn::num_to_str(i_spot), "/", fcn::num_to_str(n_spot)," ",  fixture->spots[i_spot]->name, " ", fcn::num_to_str((double)(t_next[i_spot]-t_prev[i_spot])/1000.0));
                }

                int t_next = this->t_next[i_spot];        // for readability
                int t_prev = this->t_prev[i_spot];        // for readability  

                flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
            }else{
                flash_intensity = 0.0;
            }   
            this->fixture->spots[i_spot]->RGBWout[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * backgd_RGBW[R] + flash_intensity * this->flash_color[R]  ),0),255); 
            this->fixture->spots[i_spot]->RGBWout[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * backgd_RGBW[G] + flash_intensity * this->flash_color[G]  ),0),255);
            this->fixture->spots[i_spot]->RGBWout[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * backgd_RGBW[B] + flash_intensity * this->flash_color[B]  ),0),255);
            this->fixture->spots[i_spot]->RGBWout[W] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * backgd_RGBW[W] + flash_intensity * this->flash_color[W]  ),0),255);
    }
}

/**
   #    #     # ###               #####     
  # #   ##    #  #               #     #    
 #   #  # #   #  #                     #    
#     # #  #  #  #      #####     #####     
####### #   # #  #               #          
#     # #    ##  #               #          
#     # #     # ###              #######    
*/
void SpotRackAnimation2::shake(){  //randomizes the strob speeds on request
    for (DMX_vec::iterator spd = this->strobe_spds.begin(); spd != this->strobe_spds.end(); spd++){
        (*spd) = (strobe_min<strobe_max)? rand_min_max( this->strobe_min , this->strobe_max ) : this->strobe_max; // initialize each strobe with a slightly different frequency
        // log(1, "Min:", fcn::num_to_str(strobe_min), " Max:", fcn::num_to_str(strobe_max), " picked", fcn::num_to_str((*spd)));

    }
}

void SpotRackAnimation2::init(){
    BaseAnimation::init();

    this->t_next_shake = frame.t_current_ms + 2000;
    this->shake();

    // log(1, "Min:", fcn::num_to_str(strobe_min), " Max:", fcn::num_to_str(strobe_max));

}

void SpotRackAnimation2::new_frame(){
    BaseAnimation::new_frame();
    
    // for readability
    spot_vec spots = this->fixture->spots;
    int n_spots = spots.size();
    unsigned long t = frame.t_current_ms;

    if (((long)frame.t_current_ms - (long)this->t_next_shake) > 0){
        this->shake();
        this->t_next_shake += 2000; 
    }
    for (int i = 0; i<n_spots; i++){
        spots[i]->RGBWout  = this->fixture->RGBW(this->color);

        spots[i]->strobe = (int)(this->strobe_spds[i]); // min(max( (int)(this->strobe_spds[i] * (1 + delta*sin(i*M_PI/3 + 2*M_PI*t/3000)))  ,0),255);
        // spots[i]->strobe = min(max( rand_min_max(this->strobe_spds[i] * (1-delta) , this->strobe_spds[i] * (1+delta))  ,0),255);
    }
}