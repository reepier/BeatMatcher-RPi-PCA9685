#include <cmath>

#include "spot.h"
#include "sysfcn.h"
#include "debug.h"

using namespace std;

// Original Fun Generation spots
SpotFixture spot_1(FunGeneration_RGBW_12x1W, 73, 8,       "Spot 9 (74)",     1);     
SpotFixture spot_2(FunGeneration_RGBW_12x1W, 81,  8,      "Spot 1 (82)",     2);     
SpotFixture spot_3(FunGeneration_RGBW_12x1W, 89, 8,       "Spot 8 (90)",     3);     
SpotFixture spot_4(FunGeneration_RGBW_12x1W, 97,  8,      "Spot 3 (98)",     4);     
SpotFixture spot_5(FunGeneration_RGBW_12x1W, 105,  8,     "Spot 2 (106)",    5);     
SpotFixture spot_6(FunGeneration_RGBW_12x1W, 113,  8,     "Spot 4 (114)",    6);

SpotFixture spot_7(FunGeneration_RGBW_12x1W, 121, 8,  "Spot 5 (122)",    7);     
SpotFixture spot_8(FunGeneration_RGBW_12x1W, 129, 8,  "Spot 6 (130)",    8);     
SpotFixture spot_9(FunGeneration_RGBW_12x1W, 137, 8,  "Spot 7 (138)",    9);  
SpotFixture spot_10(FunGeneration_RGBW_12x1W, 145, 8, "Spot 10 (146)",   10);
SpotFixture spot_11(FunGeneration_RGBW_12x1W, 153, 8, "Spot 11 (154)",   11);
SpotFixture spot_12(FunGeneration_RGBW_12x1W, 161, 8, "Spot 12 (162)",   12);

// New Shehds spots
SpotFixture spot_13(Shehds_RGBWAU_7x18W, 169, 10, "Spot 13 (170)", 13);
SpotFixture spot_14(Shehds_RGBWAU_7x18W, 179, 10, "Spot 14 (180)", 14);
SpotFixture spot_15(Shehds_RGBWAU_7x18W, 189, 10, "Spot 15 (190)", 15);
SpotFixture spot_16(Shehds_RGBWAU_7x18W, 199, 10, "Spot 16 (200)", 16);
SpotFixture spot_17(Shehds_RGBWAU_7x18W, 209, 10, "Spot 17 (210)", 17);
SpotFixture spot_18(Shehds_RGBWAU_7x18W, 219, 10, "Spot 18 (220)", 18);
SpotFixture spot_19(Shehds_RGBWAU_7x18W, 229, 10, "Spot 19 (230)", 19);
SpotFixture spot_20(Shehds_RGBWAU_7x18W, 239, 10, "Spot 20 (240)", 20);

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

DMX_vec FunGeneration_12x1W_buffer(const SpotFixture& spot){
    // return DMX_vec{    (uint8_t)((double)this->MASTER_DIMMER * this->active_animation->master / 255),
    return DMX_vec{      (uint8_t) (spot.master/255.0 * spot.rack->active_animation->master),
                         spot.RGBWout[R],
                         spot.RGBWout[G],
                         spot.RGBWout[B],
                         spot.RGBWout[W],
                         spot.prog,
                         spot.color_wheel,
                         spot.strobe
                    };
}

DMX_vec Shehds_10x8W_buffer(const SpotFixture& spot){
    // return DMX_vec{    (uint8_t)((double)this->MASTER_DIMMER * this->active_animation->master / 255),
    return DMX_vec{      spot.master,
                         spot.RGBWout[R],
                         spot.RGBWout[G],
                         spot.RGBWout[B],
                         spot.RGBWout[W],
                         spot.prog,
                         spot.color_wheel,
                         spot.strobe
                    };
}

DMX_vec Shehds_7x18W_buffer(const SpotFixture& spot){
    return DMX_vec{spot.master,
                   spot.RGBWout[R],
                   spot.RGBWout[G],
                   spot.RGBWout[B],
                   spot.RGBWout[W],
                   0,
                   0,
                   spot.strobe,
                   0,
                   0};
}

DMX_vec SpotFixture::buffer(){
    switch (this->type){
        case FunGeneration_RGBW_12x1W :
            return FunGeneration_12x1W_buffer(*this);
            break;
        case Shehds_RGBWAU_10x8W :
            return Shehds_10x8W_buffer(*this);
            break;
        case Shehds_RGBWAU_7x18W :
            return Shehds_7x18W_buffer(*this);
            break;
        default:    // return a black vector
            return DMX_vec(this->nCH, 0);
            break;
    }
}

/* --------------------------------------------------------------------
 #####  ######  ####### #######    ######     #     #####  #    #  #####  
#     # #     # #     #    #       #     #   # #   #     # #   #  #     # 
#       #     # #     #    #       #     #  #   #  #       #  #   #       
 #####  ######  #     #    #       ######  #     # #       ###     #####  
      # #       #     #    #       #   #   ####### #       #  #         # 
#     # #       #     #    #       #    #  #     # #     # #   #  #     # 
 #####  #       #######    #       #     # #     #  #####  #    #  #####  

/ ----------------------------------------------------------------------- */
// SpotRack front_rack(spot_vec{&spot_1, &spot_2, &spot_3, &spot_4}, "Front Rack", 1);
SpotRack front_rack(spot_vec{&spot_7, &spot_8, &spot_9, &spot_10, &spot_11, &spot_12}, "Front Rack", 1);
// SpotRack back_rack(spot_vec{&spot_5, &spot_6, &spot_7, &spot_8, &spot_9}, "Back Rack", 2);
SpotRack back_rack(spot_vec{&spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6}, "Back Rack", 2);
SpotRack back_rack2(spot_vec{&spot_13, &spot_14, &spot_15, &spot_16, &spot_17, &spot_18, &spot_19, &spot_20}, "SHEHDS Rack 2", 3);

// SpotRack global_rack(spot_vec{&spot_1,&spot_2,&spot_3,&spot_4,&spot_5,&spot_6,&spot_7,&spot_8,&spot_9,&spot_10,&spot_11,&spot_12}, "Global Rack", 1);

/*
### #     # ### #######        #######               
 #  ##    #  #     #           #        ####  #    # 
 #  # #   #  #     #           #       #    # ##   # 
 #  #  #  #  #     #           #####   #      # #  # 
 #  #   # #  #     #    ###    #       #      #  # # 
 #  #    ##  #     #    ###    #       #    # #   ## 
### #     # ###    #    ###    #        ####  #    # 
*/
    /**
    ####### ######  ####### #     # ####### 
    #       #     # #     # ##    #    #    
    #       #     # #     # # #   #    #    
    #####   ######  #     # #  #  #    #    
    #       #   #   #     # #   # #    #    
    #       #    #  #     # #    ##    #    
    #       #     # ####### #     #    #    
    */    

// Define animation for the frontal spot rack
void front_rack_init(){

    //this->animations.push_back();
    // Animation 1 : Backgrnd color + random soft flashes
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,         black,       8000, 1000,   " ", "FR.0", backer, 0));
    

    // Animation 1 : Random Bursts of color
#if SHOW_INTENSITY == 1 or SHOW_INTENSITY == 0 
    // gaussian bursts (short & slow) --> to be used as backer animation with LED (or else)
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       4000, 1500,   "white slow bubbles",       "FR.2.2.6",     leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    gold,        4000, 1500,   "gold slow bubbles",        "FR.2.2.5",     leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    cyan,        4000, 1500,   "cyan slow bubbles",        "FR.2.2.7",     leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    red,         4000, 1500,   "red slow bubbles",         "FR.2.2.1",     leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    blue,        4000, 1500,   "blue slow bubbles",        "FR.2.2.8",     leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    pink,        4000, 1500,   "pink slow bubbles",        "FR.2.2.11",    leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    magenta,     4000, 1500,   "magenta slow bubbles",     "FR.2.2.10",    leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    purple,      4000, 1500,   "purple slow bubbles",      "FR.2.2.9",     leader, 2));   
#endif 
#if SHOW_INTENSITY >= 2 or SHOW_INTENSITY == 0
    // gaussian bursts (short & fast) --> to be used as solo animation during breaks
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       1000, 600,   "WWhite fast bubbles",       "FR.2.1.6", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    gold,        1000, 600,   "gold fast bubbles",        "FR.2.1.5", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    cyan,        1000, 600,   "cyan fast bubbles",        "FR.2.1.7", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    red,         1000, 600,   "red fast bubbles",         "FR.2.1.1", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    blue,        1000, 600,   "blue fast bubbles",        "FR.2.1.8", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    pink,        1000, 600,   "pink fast bubbles",        "FR.2.1.11", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    magenta,     1000, 600,   "magenta fast bubbles",     "FR.2.1.10", leader, 2));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    purple,      1000, 600,   "purple fast bubbles",      "FR.2.1.9", leader, 2));
#endif 

    // Animation 2: Stroboscope --> To be used as LEAD animation
    // Very Fast
#if SHOW_INTENSITY == 3 or SHOW_INTENSITY == 0
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, w_white,     STRB_FASTEST, "WWhite, VFAST strobe",     "FR.1.1.6",     leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, gold,      STRB_FASTEST, "gold, VFAST strobe",      "FR.1.1.5",     leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, cyan,      STRB_FASTEST, "cyan, VFAST strobe",      "FR.1.1.7",     leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, red,       STRB_FASTEST, "red, VFAST strobe",       "FR.1.1.1",     leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, blue,      STRB_FASTEST, "blue, 8 strobe",          "FR.1.1.8",     leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, pink,      STRB_FASTEST, "pink, VFAST strobe",      "FR.1.1.11",    leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, magenta,   STRB_FASTEST, "magenta, VFAST strobe",   "FR.1.1.10",    leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, purple,    STRB_FASTEST, "purple, VFAST strobe",    "FR.1.1.9",     leader, 1));
    
#endif
    // Slow strobe
#if SHOW_INTENSITY >= 2 or SHOW_INTENSITY == 0
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, w_white,     STRB_SLOW, "WWhite, SLW strobe",     "FR.1.4.6",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, gold,      STRB_SLOW, "gold, SLW strobe",      "FR.1.4.5",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, cyan,      STRB_SLOW, "cyan, SLW strobe",      "FR.1.4.7",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, red,       STRB_SLOW, "red, SLW strobe",       "FR.1.4.1",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, blue,      STRB_SLOW, "blue, SLW strobe",      "FR.1.4.8",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, pink,      STRB_SLOW, "pink, SLW strobe",      "FR.1.4.11", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, magenta,   STRB_SLOW, "magenta, SLW strobe",   "FR.1.4.10", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, purple,    STRB_SLOW, "purple, SLW strobe",    "FR.1.4.9",  leader, 1));
#endif
    // // gaussian bursts -> square mode
    // // SLOW square bursts
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       square,  200, 300,       "fast white chaser",   "FR.3.2", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       square,  200, 600,       "fast white chaser",   "FR.3.3", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    sevika_pink, square,  100, 200,       "fast sevika_pink chaser",   "FR.3.4", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    sevika_pink, square,  50, 50,         "super fast sevika_pink chaser",   "FR.3.5", leader, 2));

    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 50, 50,     "super fast hextech sevika chaser",   "FR.3.6.1", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 100, 200,     "fast hextech sevika chaser",   "FR.3.6", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 500, 500,     "slow hextech sevika chaser",   "FR.3.7", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 500, 1000,     "slow hextech sevika chaser",  "FR.3.8", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 100, 200,     "slow hextech sevika chaser",   "FR.3.9", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 100, 200,     "slow hextech sevika chaser",   "FR.3.10", leader, 2));



    //Animation 4 -> Original Beatmatcher
#if SHOW_INTENSITY >= 2 or SHOW_INTENSITY == 0
    // Monochrome background
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,       red,  "Red background",      "FR.4.0.1",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,    sodium,  "Sodium background",   "FR.4.0.2",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,    orange,  "Orange background",   "FR.4.0.3",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,    yellow,  "Yellow background",   "FR.4.0.4",   backer,   false));
//  // front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,      gold,  "Gold background",     "FR.4.0.5",   backer,   false));
//  // front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,     w_white,  "WWhite background",    "FR.4.0.6",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,      cyan,  "Cyan background",     "FR.4.0.7",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,      blue,  "Blue background",     "FR.4.0.8",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,    purple,  "Purple background",   "FR.4.0.9",   backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,   magenta,  "Magenta background",  "FR.4.0.10",  backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,      pink,  "Pink background",     "FR.4.0.11",  backer,   false));
//     front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, black,     green,  "Green background",    "FR.4.0.12",  backer,   false));
    
    // Monochrome Flash
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, red,       black,  "Red Flashes",      "FR.4.1.1", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, sodium,    black,  "Sodium Flashes",   "FR.4.1.2", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, orange,    black,  "Orange Flashes",   "FR.4.1.3", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, yellow,    black,  "Yellow Flashes",   "FR.4.1.4", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,      black,  "Gold Flashes",     "FR.4.1.5", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     black,  "WWhite Flashes",    "FR.4.1.6", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,      black,  "Cyan Flashes",     "FR.4.1.7", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, blue,      black,  "Blue Flashes",     "FR.4.1.8", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, purple,    black,  "Purple Flashes",   "FR.4.1.9", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, magenta,   black,  "Magenta Flashes",  "FR.4.1.10", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, pink,      black,  "Pink Flashes",     "FR.4.1.11", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, green,     black,  "Green Flashes",    "FR.4.1.12", leader));

    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, red,       red,       "Red Flashes, Red Background",          "FR.4.2.1" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, sodium,    sodium,    "Sodium Flashes, Sodium Background",    "FR.4.2.2" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, orange,    orange,    "Orange Flashes, Orange Background",    "FR.4.2.3" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, yellow,    yellow,    "Yellow Flashes, Yellow Background",    "FR.4.2.4" , leader));
 // front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,      gold,      "Gold Flashes, Gold Background",        "FR.4.2.5" , leader));
 // front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     w_white,     "White Flashes, White Background",      "FR.4.2.6" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,      cyan,      "Cyan Flashes, Cyan Background",        "FR.4.2.7" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, blue,      blue,      "Blue Flashes, Blue Background",        "FR.4.2.8" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, purple,    purple,    "Purple Flashes, Purple Background",    "FR.4.2.9" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, magenta,   magenta,   "Magenta Flashes, Magenta Background",  "FR.4.2.10" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, pink,      pink,      "Pink Flashes, Pink Background",        "FR.4.2.11" , leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, green,     green,     "Green Flashes, Green Background",      "FR.4.2.12" , leader));

    // White Flash with monochrome background
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     red,     "White Flashes, Red background",      "FR.4.3.1", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     sodium,  "White Flashes, Sodium background",   "FR.4.3.2", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     orange,  "White Flashes, Orange background",   "FR.4.3.3", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     yellow,  "White Flashes, Yellow background",   "FR.4.3.4", leader));
 // front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     gold,    "White Flashes, Gold background",     "FR.4.3.5", leader));
 // front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     w_white,   "White Flashes, White background",    "FR.4.3.6", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     cyan,    "White Flashes, Cyan background",     "FR.4.3.7", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     blue,    "White Flashes, Blue background",     "FR.4.3.8", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     purple,  "White Flashes, Purple background",   "FR.4.3.9", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     magenta, "White Flashes, Magenta background",  "FR.4.3.10", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     pink,    "White Flashes, Pink background",     "FR.4.3.11", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,     green,   "White Flashes, Green background",    "FR.4.3.12", leader));
    
    // Bicolor animation based on color palettes
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     red,       "cyan Flashes, red background",         "FR.4.6.1", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     magenta,   "cyan Flashes, magenta background",     "FR.4.6.2", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,     purple,    "gold Flashes, purple background",      "FR.4.6.3", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,     red,       "gold Flashes, red background",         "FR.4.6.4", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,     orange,    "gold Flashes, orange background",      "FR.4.6.5", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,     sodium,    "gold Flashes, sodium background",      "FR.4.6.6", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     purple,    "cyan Flashes, purple background",      "FR.4.6.7", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, pink,     purple,    "pink Flashes, purple background",      "FR.4.6.8", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     pink,      "cyan Flashes, pink background",        "FR.4.6.9", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     green,     "cyan Flashes, green background",        "FR.4.6.10", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, green,    cyan,      "green Flashes, cyan background",        "FR.4.6.11", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     orange,    "cyan Flashes, orange background",        "FR.4.6.12", leader));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,     sodium,    "cyan Flashes, sodium background",        "FR.4.6.13", leader));
#endif

    // Animation 1 -> CHASER MODE (TEST) (square shaped waves)
    // SLOW
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       square,  1000, 600,      "white chaser",                   "FR.3.1",   leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       square,  200, 300,       "fast white chaser",              "FR.3.2",   leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    w_white,       square,  200, 600,       "fast white chaser",              "FR.3.3",   leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    sevika_pink, square,  100, 200,       "fast sevika_pink chaser",        "FR.3.4",   leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    sevika_pink, square,  50, 100,        "super fast sevika_pink chaser",  "FR.3.5",   leader, 2));

    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 50, 50,     "super fast hextech sevika chaser",   "FR.3.6.1", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan, shimmer_purple}, square, 100, 50,     "fast hextech sevika chaser",   "FR.3.6", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 500, 500,     "slow hextech sevika chaser",   "FR.3.7", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 500, 1000,     "slow hextech sevika chaser",  "FR.3.8", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 100, 200,     "slow hextech sevika chaser",   "FR.3.7", leader, 2));
    // front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black,    color_vec{sevika_pink,hextech_cyan}, square, 100, 200,     "slow hextech sevika chaser",   "FR.3.7", leader, 2));

    //TODO add fast Chaser flashes (square parameter)
    front_rack.activate_none();
};


        /**
        ######     #     #####  #    # 
        #     #   # #   #     # #   #  
        #     #  #   #  #       #  #   
        ######  #     # #       ###    
        #     # ####### #       #  #   
        #     # #     # #     # #   #  
        ######  #     #  #####  #    # 
        */

// Define animation for the background spot rack
void back_rack_init(){
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,         black,       100000, 1000,   " ", "BR.0", backer, 0));
    
    // random burst -> slow round bubbles
    // Monochrome Background
#if SHOW_INTENSITY <= 2  or SHOW_INTENSITY == 0  
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,      3000, 1500, "Red background",        "BR.1", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, sodium,   3000, 1500, "Sodium background",     "BR.2", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, orange,   3000, 1500, "Orange background",     "BR.3", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, yellow,   3000, 1500, "Yellow background",     "BR.4", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, gold,     3000, 1500, "Gold background",       "BR.5", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, w_white,    3000, 1500, "White background",      "BR.6", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, cyan,     3000, 1500, "Cyan background",       "BR.7", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, blue,     3000, 1500, "Blue background",       "BR.8", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,   3000, 1500, "Purple background",     "BR.9", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, magenta,  3000, 1500, "Magenta background",    "BR.10", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, pink,     3000, 1500, "Pink background",       "BR.11", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, green,    3000, 1500, "Green background",      "BR.12", backer, 1));

    // Color Bubbles on Black background
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, red,      3000, 1500, "Red bubbles",     "BR.1.1.1", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, sodium,   3000, 1500, "Sodium bubbles",  "BR.1.1.2", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, orange,   3000, 1500, "Orange bubbles",  "BR.1.1.3", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, yellow,   3000, 1500, "Yellow bubbles",  "BR.1.1.4", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, gold,     3000, 1500, "Gold bubbles",    "BR.1.1.5", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, w_white,    3000, 1500, "White bubbles",   "BR.1.1.6", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, cyan,     3000, 1500, "Cyan bubbles",    "BR.1.1.7", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, blue,     3000, 1500, "Blue bubbles",    "BR.1.1.8", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, purple,   3000, 1500, "Purple bubbles",  "BR.1.1.9", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, magenta,  3000, 1500, "Magenta bubbles", "BR.1.1.10", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, pink,     3000, 1500, "Pink bubbles",    "BR.1.1.11", backer));
    // back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black, green,    3000, 1500, "Green bubbles",   "BR.1.1.12", backer));
    
    // Color Bubbles on same color background
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,      red,      3000, 1500, "Red bubbles, Red background",         "BR.1.1.2.1", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, sodium,   sodium,   3000, 1500, "Sodium bubbles, Sodium background",   "BR.1.1.2.2", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, orange,   orange,   3000, 1500, "Orange bubbles, Orange background",   "BR.1.1.2.3", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, yellow,   yellow,   3000, 1500, "Yellow bubbles, Yellow background",   "BR.1.1.2.4", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, gold,     gold,     3000, 1500, "Gold bubbles, Gold background",       "BR.1.1.2.5", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, w_white,    w_white,    3000, 1500, "White bubbles, White background",     "BR.1.1.2.6", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, cyan,     cyan,     3000, 1500, "Cyan bubbles, Cyan background",       "BR.1.1.2.7", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, blue,     blue,     3000, 1500, "Blue bubbles, Blue background",       "BR.1.1.2.8", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,   purple,   3000, 1500, "Purple bubbles, Purple background",   "BR.1.1.2.9", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, magenta,  magenta,  3000, 1500, "Magenta bubbles, Magenta background", "BR.1.1.2.10", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, pink,     pink,     3000, 1500, "Pink bubbles, Pink background",       "BR.1.1.2.11", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, green,    green,    3000, 1500, "Green bubbles, Green background",     "BR.1.1.2.12", backer, 1));
    // White Bubbles on colored background
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,     w_white,  3000, 1500, "White bubbles, Red background",      "BR.1.1.3.1", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, sodium,  w_white,  3000, 1500, "White bubbles, Sodium background",   "BR.1.1.3.2", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, orange,  w_white,  3000, 1500, "White bubbles, Orange background",   "BR.1.1.3.3", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, yellow,  w_white,  3000, 1500, "White bubbles, Yellow background",   "BR.1.1.3.4", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, gold,    w_white,  3000, 1500, "White bubbles, Gold background",     "BR.1.1.3.5", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, w_white,   w_white,  3000, 1500, "White bubbles, White background",    "BR.1.1.3.6", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, cyan,    w_white,  3000, 1500, "White bubbles, Cyan background",     "BR.1.1.3.7", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, blue,    w_white,  3000, 1500, "White bubbles, Blue background",     "BR.1.1.3.8", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,  w_white,  3000, 1500, "White bubbles, Purple background",   "BR.1.1.3.9", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, magenta, w_white,  3000, 1500, "White bubbles, Magenta background",  "BR.1.1.3.10", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, pink,    w_white,  3000, 1500, "White bubbles, Pink background",     "BR.1.1.3.11", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, green,   w_white,  3000, 1500, "White bubbles, Green background",    "BR.1.1.3.12", backer, 1));

    // Color Bubbles on different color background
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,     blue,   3000, 1500, "blue bubbles, red background",       "BR.1.1.4.1", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, blue,    red,    3000, 1500, "red bubbles, blue background",       "BR.1.1.4.2", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,     cyan,   3000, 1500, "cyan bubbles, red background",       "BR.1.1.4.3", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, magenta, cyan,   3000, 1500, "cyan bubbles, magenta background",   "BR.1.1.4.4", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,  gold,   3000, 1500, "gold bubbles, purple background",    "BR.1.1.4.5", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,     gold,   3000, 1500, "gold bubbles, red background",       "BR.1.1.4.6", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, orange,  gold,   3000, 1500, "gold bubbles, orange background",    "BR.1.1.4.7", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, sodium,  gold,   3000, 1500, "gold bubbles, sodium background",    "BR.1.1.4.8", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,  cyan,   3000, 1500, "cyan bubbles, purple background",    "BR.1.1.4.9", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,  pink,   3000, 1500, "pink bubbles, purple background",    "BR.1.1.4.10", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,  cyan,   3000, 1500, "cyan bubbles, purple background",    "BR.1.1.4.11", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, pink,    cyan,   3000, 1500, "cyan bubbles, pink background",      "BR.1.1.4.12", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,  red,    3000, 1500, "purple bubbles,red background",      "BR.1.1.4.13", backer, 1));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,     purple, 3000, 1500, "red bubbles, purple background",     "BR.1.1.4.14", backer, 1));
#endif 

    // SLOW CHASER bursts (square bursts)
#if SHOW_INTENSITY >= 2 or SHOW_INTENSITY == 0  
    // Monocrhome slow chaser 
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,      red,        square,  3000, 3000,      "red chaser",      "BR.1.2.1.1",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, sodium,   sodium,     square,  3000, 3000,      "sodium chaser",   "BR.1.2.1.2",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, orange,   orange,     square,  3000, 3000,      "orange chaser",   "BR.1.2.1.3",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, yellow,   yellow,     square,  3000, 3000,      "yellow chaser",   "BR.1.2.1.4",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, gold,     gold,       square,  3000, 3000,      "gold chaser",     "BR.1.2.1.5",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, w_white,    w_white,      square,  3000, 3000,      "white chaser",    "BR.1.2.1.6",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, cyan,     cyan,       square,  3000, 3000,      "cyan chaser",     "BR.1.2.1.7",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, blue,     blue,       square,  3000, 3000,      "blue chaser",     "BR.1.2.1.8",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,   purple,     square,  3000, 3000,      "purple chaser",   "BR.1.2.1.9",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, magenta,  magenta,    square,  3000, 3000,      "magenta chaser",  "BR.1.2.1.10",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, pink,     pink,       square,  3000, 3000,      "pink chaser",     "BR.1.2.1.11",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, green,    green,      square,  3000, 3000,      "green chaser",    "BR.1.2.1.12",  backer, 2, 100));

    // slow chaser with black background
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,      red,        square,  3000, 3000,      "red chaser",       "BR.1.2.2.1",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,   sodium,     square,  3000, 3000,      "sodium chaser",       "BR.1.2.2.2",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,   orange,     square,  3000, 3000,      "orange chaser",       "BR.1.2.2.3",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,   yellow,     square,  3000, 3000,      "yellow chaser",       "BR.1.2.2.4",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,     gold,       square,  3000, 3000,      "gold chaser",       "BR.1.2.2.5",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,    w_white,      square,  3000, 3000,      "white chaser",       "BR.1.2.2.6",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,     cyan,       square,  3000, 3000,      "cyan chaser",       "BR.1.2.2.7",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,     blue,       square,  3000, 3000,      "blue chaser",       "BR.1.2.2.8",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,   purple,     square,  3000, 3000,      "purple chaser",       "BR.1.2.2.9",   backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,  magenta,    square,  3000, 3000,      "magenta chaser",       "BR.1.2.2.10",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,     pink,       square,  3000, 3000,      "pink chaser",       "BR.1.2.2.11",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, black,    green,      square,  3000, 3000,      "green chaser",       "BR.1.2.2.12",  backer, 2, 100));

    // White slow chaser with color background
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, red,      w_white,        square,  3000, 3000,      "white chaser, red background",     "BR.1.2.3.1",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, sodium,   w_white,        square,  3000, 3000,      "white chaser, sodium background",  "BR.1.2.3.2",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, orange,   w_white,        square,  3000, 3000,      "white chaser, orange background",  "BR.1.2.3.3",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, yellow,   w_white,        square,  3000, 3000,      "white chaser, yellow background",  "BR.1.2.3.4",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, gold,     w_white,        square,  3000, 3000,      "white chaser, gold background",    "BR.1.2.3.5",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, w_white,    w_white,        square,  3000, 3000,      "white chaser, white background",   "BR.1.2.3.6",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, cyan,     w_white,        square,  3000, 3000,      "white chaser, cyan background",    "BR.1.2.3.7",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, blue,     w_white,        square,  3000, 3000,      "white chaser, blue background",    "BR.1.2.3.8",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, purple,   w_white,        square,  3000, 3000,      "white chaser, purple background",  "BR.1.2.3.9",  backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, magenta,  w_white,        square,  3000, 3000,      "white chaser, magenta background", "BR.1.2.3.10", backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, pink,     w_white,        square,  3000, 3000,      "white chaser, pink background",    "BR.1.2.3.11", backer, 2, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack, green,    w_white,        square,  3000, 3000,      "white chaser, green background",   "BR.1.2.3.12", backer, 2, 100));

    // Color chaser on different color background
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   blue,   red,      square, 3000, 3000, "blue chaser, red background",       "BR.1.2.4.1", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   red,    blue,     square, 3000, 3000, "red chaser, blue background",       "BR.1.2.4.2", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   cyan,   red,      square, 3000, 3000, "cyan chaser, red background",       "BR.1.2.4.3", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   cyan,   magenta,  square, 3000, 3000, "cyan chaser, magenta background",   "BR.1.2.4.4", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   gold,   purple,   square, 3000, 3000, "gold chaser, purple background",    "BR.1.2.4.5", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   gold,   red,      square, 3000, 3000, "gold chaser, red background",       "BR.1.2.4.6", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   gold,   orange,   square, 3000, 3000, "gold chaser, orange background",    "BR.1.2.4.7", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   gold,   sodium,   square, 3000, 3000, "gold chaser, sodium background",    "BR.1.2.4.8", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   cyan,   purple,   square, 3000, 3000, "cyan chaser, purple background",    "BR.1.2.4.9", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   pink,   purple,   square, 3000, 3000, "pink chaser, purple background",    "BR.1.2.4.10", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   cyan,   purple,   square, 3000, 3000, "cyan chaser, purple background",    "BR.1.2.4.11", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   cyan,   pink,     square, 3000, 3000, "cyan chaser, pink background",      "BR.1.2.4.12", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   red,    purple,   square, 3000, 3000, "purple chaser, red background",     "BR.1.2.4.13", backer, 1, 100));
    back_rack.animations.push_back(new SpotRackAnimation1(&back_rack,   purple, red,      square, 3000, 3000, "red chaser, purple background",     "BR.1.2.4.14", backer, 1, 100));
#endif

    back_rack.activate_none();
};

        /**
        ######     #     #####  #    #     #####     
        #     #   # #   #     # #   #     #     #    
        #     #  #   #  #       #  #            #    
        ######  #     # #       ###        #####     
        #     # ####### #       #  #      #       ###
        #     # #     # #     # #   #     #       ###
        ######  #     #  #####  #    #    ####### ###
        */
void back_rack2_init(){
    back_rack2.animations.push_back(new SpotRackAnimation1(&back_rack2, black,  black,       100000, 1000,   " ", "BR.0", backer, 0));
        
}

// Define animation for the global spot rack (including both frontal and background spots);
void global_rack_init(){};

/*
 #####  ######  ####### #######    ######   #####  ######  #     # 
#     # #     # #     #    #       #     # #     # #     # #  #  # 
#       #     # #     #    #       #     # #       #     # #  #  # 
 #####  ######  #     #    #       ######  #  #### ######  #  #  # 
      # #       #     #    #       #   #   #     # #     # #  #  # 
#     # #       #     #    #       #    #  #     # #     # #  #  # 
 #####  #       #######    #       #     #  #####  ######   ## ##  
*/

DMX_vec FunGeneration_12x1W_RGBW(simpleColor c, int intensity){
    switch (c){
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
    case w_white:
        return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
        break;
    case c_white:
        return fcn::RGBW_norm(DMX_vec{255,230,213,255}, 180.0/255*intensity);
        break;
    case gold:
        return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
        break;
    case sevika_pink :
        return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);
        break;
    case hextech_cyan :
        return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);
        break;
    case shimmer_purple :
        return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);
        break;
    default:
        return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
        break;
    }
}

DMX_vec Shehds_10x8W_RGBW(simpleColor c, int intensity){
    switch (c){
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
        case w_white:
            return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
            break;
        case c_white:
        return fcn::RGBW_norm(DMX_vec{255,230,213,255}, 180.0/255*intensity);
        break;
        case gold:
            return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
            break;
        case sevika_pink :
            return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);
            break;
        case hextech_cyan :
            return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);
            break;
        case shimmer_purple :
            return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);
            break;
        default:
            return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
            break;
    }
}

DMX_vec Shehds_7x18W_RGBW(simpleColor c, int intensity){
    switch (c){
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
        case w_white:
            return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
            break;
        case c_white:
        return fcn::RGBW_norm(DMX_vec{255,230,213,255}, 180.0/255*intensity);
        break;
        case gold:
            return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
            break;
        case sevika_pink :
            return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);
            break;
        case hextech_cyan :
            return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);
            break;
        case shimmer_purple :
            return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);
            break;
        default:
            return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
            break;
    }
}


DMX_vec SpotFixture::RGBW(simpleColor c, int intensity){
    switch (this->type){
        case FunGeneration_RGBW_12x1W :
            return FunGeneration_12x1W_RGBW(c, intensity);
            break;
        case Shehds_RGBWAU_10x8W :
            return Shehds_10x8W_RGBW(c, intensity);
            break;
        case Shehds_RGBWAU_7x18W :
            return Shehds_7x18W_RGBW(c, intensity);
            break;
        
        default :
            break;
    }
}

/**
######                          ######   #####  ######  #     # 
#     #   ##    ####  #    #    #     # #     # #     # #  #  # 
#     #  #  #  #    # #   #     #     # #       #     # #  #  # 
######  #    # #      ####      ######  #  #### ######  #  #  # 
#   #   ###### #      #  #      #   #   #     # #     # #  #  # 
#    #  #    # #    # #   #     #    #  #     # #     # #  #  # 
#     # #    #  ####  #    #    #     #  #####  ######   ## ##  
*/

DMX_vec SpotRack::RGBW(simpleColor c, int intensity){
    // log(4, __FILE__, " ", __LINE__, " ",__func__);

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
    case w_white:
        return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
        break;
    case gold:
        return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
        break;
    case sevika_pink :
        return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);
        break;
    case hextech_cyan :
        return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);
        break;
    case shimmer_purple :
        return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);
        break;
    default:
        return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
        break;
    }
}

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  ##### 
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     #
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #      
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  ##### 
####### #   # #  #  #     # #######    #     #  #     # #   # #       #
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     #
#     # #     # ### #     # #     #    #    ### ####### #     #  ##### 
*/

/*
   #          ######                                            
  ##          #     # #    # #####  #####  #      ######  ####  
 # #          #     # #    # #    # #    # #      #      #      
   #          ######  #    # #####  #####  #      #####   ####  
   #   ###    #     # #    # #    # #    # #      #           # 
   #   ###    #     # #    # #    # #    # #      #      #    # 
 ##### ###    ######   ####  #####  #####  ###### ######  ####  
*/
// Bubbles
void SpotRackAnimation1::init(){
    log(4, __FILE__, " ", __LINE__, " ",__func__, " ", this->fixture->name, " ", this->id);

    BaseAnimation::init();
    
    this->fixture->reset_spots();
    
    // for (auto spot : this->fixture->spots){
    //     spot->master = this->master;
    // }

    this->p_ms = vector<int>{rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms)};
    
    const int n_spot = this->fixture->spots.size();
    // this->t_next.resize(n_spot);
    // this->t_prev.resize(n_spot);
    // this->spot_flash_color.resize(n_spot);
    this->flashes = vector<flash_vec>(n_spot, flash_vec(2));

    for (int i_spot=0; i_spot<n_spot; i_spot++){
        flashes[i_spot][i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, n_spot*rand_const_ms*2); 
        flashes[i_spot][i_prev].time = 0;
        flashes[i_spot][i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_spot][i_prev].color = black;
    }

    // log(1,  __FILE__, " ", __LINE__, " ",__func__, " Palette : ", fcn::palette_to_string(this->flash_colors, '/'));

}

void SpotRackAnimation1::new_frame(){
    log(4, __FILE__, " ", __LINE__, " ",__func__);

    BaseAnimation::new_frame();

    long t = frame.t_current_ms;       // for readability
    int n_spot = this->fixture->rack_size;   // for readability
    
    // update 5 sinewaves of different period
    vector<double> s = {sin(2*M_PI*t/p_ms[0]), sin(2*M_PI*t/p_ms[1]), sin(2*M_PI*t/p_ms[2]), sin(2*M_PI*t/p_ms[3]), sin(2*M_PI*t/p_ms[4]) };
    
    // for each spot "i" of the rack
    for (int i_spot=0; i_spot < n_spot; i_spot++){

        auto current_spot = this->fixture->spots[i_spot];              // for readability
        auto &current_spot_flashes = flashes[i_spot];                  // for readability
        auto &current_spot_next_flash = flashes[i_spot][i_next];       // for readability
        auto &current_spot_prev_flash = flashes[i_spot][i_prev];       // for readability
        time_t &t_next = current_spot_next_flash.time;
        time_t &t_prev = current_spot_prev_flash.time;
        simpleColor &c_next = current_spot_next_flash.color;
        simpleColor &c_prev = current_spot_prev_flash.color;

        // log(4, __FILE__, " ", __LINE__, " ",__func__, " Mark2 , ", fcn::num_to_str(i_spot));

        const pixel     ani_backgd_RGBW = fixture->RGBW(back_color, SPOTRACK_ANI1_BkG_INTENSITY_LOW);
        pixel           frame_backgd_RGBW = {0,0,0,0};

        //TODO remove fluctuation !!
        // compute fluctuating background color values :
            frame_backgd_RGBW[R] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[R] * (1 + fluct_col*s[(i_spot+0)%5]))  ,0),255);
            frame_backgd_RGBW[G] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[G] * (1 + fluct_col*s[(i_spot+1)%5]))  ,0),255);
            frame_backgd_RGBW[B] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[B] * (1 + fluct_col*s[(i_spot+2)%5]))  ,0),255);
            frame_backgd_RGBW[W] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[W] * (1 + fluct_col*s[(i_spot+3)%5]))  ,0),255);
        // ------------------------------- limit to 0-255 ---------------- Spot Intensity    *  RGBW pixel intensity                            ;
        
        // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
            double flash_intensity; // 0 by default
            if (flash_activation){
                // when the flash passes, compute the next flash timestamp and update prev flash
                if (t > t_next){
                    
                    t_prev = t_next;
                    t_next = t_next + rand_min_max(this->flash_len, 2*n_spot*this->rand_const_ms);
                    c_prev = c_next;
                    c_next = fcn::random_pick(this->flash_colors);
                    
                    // log (2 , fcn::num_to_str(t_prev-t), " ", fcn::num_to_str(t_next-t), " Selection parmi ", fcn::palette_to_string(this->flash_colors, '/'), " -> ", colorName[(int)c_next]);
                    // this->t_prev[i_spot] = this->t_next[i_spot];
                    // this->t_next[i_spot] = this->t_next[i_spot] + rand_min_max(this->flash_len, 2*n_spot*this->rand_const_ms);
                    // if (fixture->id == 1) log(1, fixture->name, " ", fcn::num_to_str(i_spot), "/", fcn::num_to_str(n_spot)," ",  fixture->spots[i_spot]->name, " ", fcn::num_to_str((double)(t_next[i_spot]-t_prev[i_spot])/1000.0));
                }

                // flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                switch (this->flash_shape){
                    case square :
                        flash_intensity = fcn::square(t, t_prev, flash_len, 0.0,1.0) + fcn::square(t, t_next, flash_len, 0.0,1.0);
                        break;
                    case gaussian2 :
                        flash_intensity = fcn::gaussian2(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian2(t, t_next, flash_len, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                        break;
                    default :
                        flash_intensity = fcn::gaussian(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian(t, t_next, flash_len, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                        break;
                }

            }else{
                flash_intensity = 0.0;
            }

            DMX_vec frame_flash_RGBW = (t-t_prev > t_next-t) ? fixture->RGBW(c_next) : this->fixture->RGBW(c_prev);
            current_spot->RGBWout[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[R] + flash_intensity * frame_flash_RGBW[R]  ),0),255); 
            current_spot->RGBWout[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[G] + flash_intensity * frame_flash_RGBW[G]  ),0),255);
            current_spot->RGBWout[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[B] + flash_intensity * frame_flash_RGBW[B]  ),0),255);
            current_spot->RGBWout[W] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[W] + flash_intensity * frame_flash_RGBW[W]  ),0),255);
    }
}

/*
 #####          #####                                    
#     #        #     # ##### #####   ####  #####  ###### 
      #        #         #   #    # #    # #    # #      
 #####          #####    #   #    # #    # #####  #####  
#       ###          #   #   #####  #    # #    # #      
#       ###    #     #   #   #   #  #    # #    # #      
####### ###     #####    #   #    #  ####  #####  ###### 
*/
// Stroboscope
void SpotRackAnimation2::shake(){  //randomizes the strob speeds on request
    log(4, __FILE__, " ", __LINE__, " ",__func__);

    for (DMX_vec::iterator spd = this->strobe_spds.begin(); spd != this->strobe_spds.end(); spd++){
        (*spd) = (strobe_min<strobe_max)? rand_min_max( this->strobe_min , this->strobe_max ) : this->strobe_max; // initialize each strobe with a slightly different frequency
        // log(1, "Min:", fcn::num_to_str(strobe_min), " Max:", fcn::num_to_str(strobe_max), " picked", fcn::num_to_str((*spd)));

    }
}

void SpotRackAnimation2::init(){
    log(4, __FILE__, " ", __LINE__, " ",__func__);

    BaseAnimation::init();
    this->fixture->reset_spots();
    // for (auto spot : this->fixture->spots){
    //     spot->master = this->master;
    // }

    this->t_next_shake = frame.t_current_ms + 2000;
    this->shake();
    animator.set_timer(STROBE_ANI_DURA);
    // log(2, "Stroboscopic animation started, timer set to ", STROBE_ANI_DURA, "ms");
    // log(1, "Min:", fcn::num_to_str(strobe_min), " Max:", fcn::num_to_str(strobe_max));

}

void SpotRackAnimation2::new_frame(){
    log(4, __FILE__, " ", __LINE__, " ",__func__);

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
        if (sampler.state == BEAT)
            spots[i]->RGBWout  = this->fixture->RGBW(this->color); //TODO replace rack.RGBW with spot.RGBW
        else    
            spots[i]->RGBWout  = this->fixture->RGBW(black);


        spots[i]->strobe = (int)(this->strobe_spds[i]); // min(max( (int)(this->strobe_spds[i] * (1 + delta*sin(i*M_PI/3 + 2*M_PI*t/3000)))  ,0),255);
        // spots[i]->strobe = min(max( rand_min_max(this->strobe_spds[i] * (1-delta) , this->strobe_spds[i] * (1+delta))  ,0),255);
    }
}

/*
 #####          #####                                     
#     #        #     # #    #   ##    ####  ###### #####  
      #        #       #    #  #  #  #      #      #    # 
 #####         #       ###### #    #  ####  #####  #    # 
      # ###    #       #    # ######      # #      #####  
#     # ###    #     # #    # #    # #    # #      #   #  
 #####  ###     #####  #    # #    #  ####  ###### #    # 
*/
//TODO finish
void SpotRackAnimation3::init(){
    BaseAnimation::init();
    this->fixture->reset_spots();
    // for (auto spot : this->fixture->spots){
    //     spot->master = this->master;
    // }
    
}

void SpotRackAnimation3::new_frame(){
    BaseAnimation::new_frame();


}

/*
#              ######                      
#    #         #     # ######   ##   ##### 
#    #         #     # #       #  #    #   
#    #         ######  #####  #    #   #   
####### ###    #     # #      ######   #   
     #  ###    #     # #      #    #   #   
     #  ###    ######  ###### #    #   #
*/
void SpotRackAnimation4::init(){
    BaseAnimation::init();
    this->fixture->reset_spots();
    for (auto spot : this->fixture->spots){
        spot->master = this->master;
    }
}

void SpotRackAnimation4::new_frame(){
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    pixel backgd_RGB = this->fixture->RGBW(back_color, 20);
    pixel flash_RGB = this->fixture->RGBW(flash_color);
    pixel final_RGB(4);

    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    if (param_activate_flash && auto_activate_flash)
    {
         
        final_RGB[R] = (1-pow(coef, 0.2)) * backgd_RGB[R] + coef * flash_RGB[R];
        final_RGB[G] = (1-pow(coef, 0.2)) * backgd_RGB[G] + coef * flash_RGB[G];
        final_RGB[B] = (1-pow(coef, 0.2)) * backgd_RGB[B] + coef * flash_RGB[B];
    }
    else
    {
        final_RGB[R] = backgd_RGB[R];
        final_RGB[G] = backgd_RGB[G];
        final_RGB[B] = backgd_RGB[B];
    }
    
    for (auto spot : this->fixture->spots){
        spot->RGBWout = final_RGB;
    }
}