#include <cmath>

#include "spot.h"
#include "sysfcn.h"
#include "debug.h"

using namespace std;

// Original Fun Generation spots
SpotFixture spot_1(FunGen_RGBW_12x1W, 73,    8,  "Spot 1 (@74)",    1);     
SpotFixture spot_2(FunGen_RGBW_12x1W, 81,    8,  "Spot 2 (@82)",    2);     //Salon
SpotFixture spot_3(FunGen_RGBW_12x1W, 89,    8,  "Spot 3 (@90)",    3);     
SpotFixture spot_4(FunGen_RGBW_12x1W, 97,    8,  "Spot 4 (@98)",    4);     
SpotFixture spot_5(FunGen_RGBW_12x1W, 105,   8,  "Spot 5 (@106)",   5);     //Salon
SpotFixture spot_6(FunGen_RGBW_12x1W, 113,   8,  "Spot 6 (@114)",   6);

SpotFixture spot_7(FunGen_RGBW_12x1W,   121, 8,   "Spot 7 (@122)",    7);     //Salon
SpotFixture spot_8(FunGen_RGBW_12x1W,   129, 8,   "Spot 8 (@130)",    8);     //Salon
SpotFixture spot_9(FunGen_RGBW_12x1W,   137, 8,   "Spot 9 (@138)",    9);  
SpotFixture spot_10(FunGen_RGBW_12x1W,  145, 8,   "Spot 10 (@146)",   10);
SpotFixture spot_11(FunGen_RGBW_12x1W,  153, 8,   "Spot 11 (@154)",   11);
SpotFixture spot_12(FunGen_RGBW_12x1W,  161, 8,   "Spot 12 (@162)",   12);

// New Shehds spots
SpotFixture spot_13(Shehds_RGBWAU_7x18W, 169, 10, "Spot 13 (@170) : SHEHDS RGBWAU", 13);
SpotFixture spot_14(Shehds_RGBWAU_7x18W, 179, 10, "Spot 14 (@180) : SHEHDS RGBWAU", 14);
SpotFixture spot_15(Shehds_RGBWAU_7x18W, 189, 10, "Spot 15 (@190) : SHEHDS RGBWAU", 15);
SpotFixture spot_16(Shehds_RGBWAU_7x18W, 199, 10, "Spot 16 (@200) : SHEHDS RGBWAU", 16);
SpotFixture spot_17(Shehds_RGBWAU_7x18W, 209, 10, "Spot 17 (@210) : SHEHDS RGBWAU", 17);
SpotFixture spot_18(Shehds_RGBWAU_7x18W, 219, 10, "Spot 18 (@220) : SHEHDS RGBWAU", 18);
SpotFixture spot_19(Shehds_RGBWAU_7x18W, 229, 10, "Spot 19 (@230) : SHEHDS RGBWAU", 19);
SpotFixture spot_20(Shehds_RGBWAU_7x18W, 239, 10, "Spot 20 (@240) : SHEHDS RGBWAU", 20);

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
    //TODO protect every fixture.buffer function from null active_animation pointer
    uint8_t active_animation_master = 255;  //default value
    uint8_t rack_master = 255;              //default value
    if (spot.rack != nullptr && spot.rack->active_animation != nullptr){
        active_animation_master = spot.rack->active_animation->master;
        rack_master             = spot.rack->master;
    }
    return DMX_vec{      (uint8_t) (rack_master/255.0 * spot.master/255.0 * active_animation_master),
                         spot.pixel[R],
                         spot.pixel[G],
                         spot.pixel[B],
                         spot.pixel[W],
                         spot.prog,
                         spot.color_wheel,
                         spot.strobe
                    };
}

DMX_vec Shehds_10x8W_buffer(const SpotFixture& spot){
    uint8_t active_animation_master = 255;  //default value
    uint8_t rack_master = 255;              //default value
    if (spot.rack != nullptr && spot.rack->active_animation != nullptr){
        active_animation_master = spot.rack->active_animation->master;
        rack_master             = spot.rack->master;
    }
    return DMX_vec{      (uint8_t) (rack_master/255.0 * spot.master/255.0 * active_animation_master),
                         spot.pixel[R],
                         spot.pixel[G],
                         spot.pixel[B],
                         spot.pixel[W],
                         spot.prog,
                         spot.color_wheel,
                         spot.strobe
                    };
}

DMX_vec Shehds_7x18W_buffer(const SpotFixture& spot){
    uint8_t active_animation_master = 255;  //default value
    uint8_t rack_master = 255;              //default value
    if (spot.rack != nullptr && spot.rack->active_animation != nullptr){
        active_animation_master = spot.rack->active_animation->master;
        rack_master             = spot.rack->master;
    }
    return DMX_vec{      (uint8_t) (rack_master/255.0 * spot.master/255.0 * active_animation_master),
                   spot.pixel[R],
                   spot.pixel[G],
                   spot.pixel[B],
                   spot.pixel[W],
                   spot.pixel[Amb],
                   spot.pixel[UV],
                   spot.strobe,
                   0,
                   0};
}

DMX_vec SpotFixture::buffer(){
    switch (this->type){
        case FunGen_RGBW_12x1W :
            return FunGeneration_12x1W_buffer(*this);break;
        case Shehds_RGBWAU_10x8W :
            return Shehds_10x8W_buffer(*this);break;
        case Shehds_RGBWAU_7x18W :
            return Shehds_7x18W_buffer(*this);break;
        default:    // return a black vector
            return DMX_vec(this->nCH, 0);break;
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
SpotRack front_rack(spot_vec{&spot_2, &spot_5, &spot_7, &spot_8}, "Front Rack", 1);
SpotRack rack_15(spot_vec{&spot_1, &spot_3, &spot_4, &spot_6}, "Vert. Beams", 2);
SpotRack rack_40(spot_vec{&spot_9, &spot_10, &spot_11, &spot_12}, "Rack 2", 3);
SpotRack shehds_rack(spot_vec{&spot_13, &spot_14, &spot_15, &spot_16, &spot_17, &spot_18, &spot_19, &spot_20}, "SHEHDS Rack", 4);

/** Config Salon */
SpotRack back_rack(spot_vec{&spot_1, &spot_3, &spot_4, &spot_6}, "Back Rack", 2);


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
#######                               ######                       
#       #####   ####  #    # #####    #     #   ##    ####  #    # 
#       #    # #    # ##   #   #      #     #  #  #  #    # #   #  
#####   #    # #    # # #  #   #      ######  #    # #      ####   
#       #####  #    # #  # #   #      #   #   ###### #      #  #   
#       #   #  #    # #   ##   #      #    #  #    # #    # #   #  
#       #    #  ####  #    #   #      #     # #    #  ####  #    # 
    */    

// Define animation for the frontal spot rack
void front_rack_init(){

    //this->animations.push_back();
    // Animation 1 : Backgrnd color + random soft flashes
    front_rack.animations.push_back(new SpotRackAnimation0(&front_rack, black, " ", "FR.0", backer, 0));
    
/*
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
    // Fast frquency
#if SHOW_INTENSITY==0 or SHOW_INTENSITY>=2
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, red,      STRB_FAST, "S red strobe",      "FR.1.2.1",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, blue,     STRB_FAST, "S blue strobe",     "FR.1.2.2",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, purple,   STRB_FAST, "S purple strobe",   "FR.1.2.3",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, gold,     STRB_FAST, "S gold strobe",     "FR.1.2.4",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, sodium,   STRB_FAST, "S sodium strobe",   "FR.1.2.5",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, cyan,     STRB_FAST, "S cyan strobe",     "FR.1.2.6",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, w_white,  STRB_FAST, "S w_white strobe",  "FR.1.2.7",  leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation2(&front_rack, c_white,  STRB_FAST, "S c_white strobe",  "FR.1.2.8",  leader, 1));
#endif

    // 2. BUBBLES
    //Slow
#if SHOW_INTENSITY==0 or SHOW_INTENSITY<=2
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, red,     4000, 1500,  "S red bubbles",      "FR.2.1.1", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, blue,    4000, 1500,  "S blue bubbles",     "FR.2.1.2", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, purple,  4000, 1500,  "S purple bubbles",   "FR.2.1.3", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, cyan,    4000, 1500,  "S cyan bubbles",     "FR.2.1.4", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, w_white, 4000, 1500,  "S w_white bubbles",  "FR.2.1.5", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, c_white, 4000, 1500,  "S c_white bubbles",  "FR.2.1.6", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, gold,    4000, 1500,  "S gold bubbles",     "FR.2.1.7", backer, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, sodium,  4000, 1500,  "S sodium bubbles",   "FR.2.1.8", backer, 3));
#endif
#if SHOW_INTENSITY==0 or SHOW_INTENSITY>=1
    //Medium
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, red,     2000, 700,  "S red bubbles",      "FR.2.2.1", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, blue,    2000, 700,  "S blue bubbles",     "FR.2.2.2", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, purple,  2000, 700,  "S purple bubbles",   "FR.2.2.3", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, cyan,    2000, 700,  "S cyan bubbles",     "FR.2.2.4", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, w_white, 2000, 700,  "S w_white bubbles",  "FR.2.2.5", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, c_white, 2000, 700,  "S c_white bubbles",  "FR.2.2.6", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, gold,    2000, 700,  "S gold bubbles",     "FR.2.2.7", any, 3));
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, black, sodium,  2000, 700,  "S sodium bubbles",   "FR.2.2.8", any, 3));
#endif

    // 3. BEAT
#if SHOW_INTENSITY==0 or SHOW_INTENSITY>=2
    //Monochrome flashes, no background
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, red,        black,  "red beat",      "FR.3.1.1", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, blue,       black,  "blue beat",     "FR.3.1.2", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, purple,     black,  "purple beat",   "FR.3.1.3", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,       black,  "gold beat",     "FR.3.1.4", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, sodium,     black,  "sodium beat",   "FR.3.1.5", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,       black,  "cyan beat",     "FR.3.1.6", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,    black,  "w_white beat",  "FR.3.1.7", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, c_white,    black,  "c_white beat",  "FR.3.1.8", leader, 1));
    //Monochrome flashes, with background
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, c_white,    red,        "ColdWhite beat, red backgd",     "FR.3.2.1", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,    red,        "Warmwhite beat, red backgd",     "FR.3.2.2", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,       red,        "Gold beat, red backgd",          "FR.3.2.3", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, c_white,    purple,     "ColdWhite beat, purple backgd",  "FR.3.2.4", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, w_white,    purple,     "Warmwhite beat, purple backgd",  "FR.3.2.5", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, gold,       purple,     "Gold beat, purple backgd",       "FR.3.2.6", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,       red,        "Cyan beat, red backgd",          "FR.3.2.7", leader, 1));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, cyan,       purple,     "Cyan beat, purple backgd",       "FR.3.2.8", leader, 1));
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


/** TESTS & DEV */



    //AUTOCOLOR Animations
    // Animation type 0 : Fixed color
    front_rack.animations.push_back(new SpotRackAnimation0(&front_rack, "Couleur", "FR.0.1", any, 1, 255));
    // Animation type 1.1 : Random BUBBLES
    // Slow Bubbles
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, gaussian, /*Flash Period*/ 4000, /*Flash Length*/ 1500, "Slow Bubbles", "FR.1.1.1", backer, 1));
    // Fast bubbles
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, gaussian, /*Flash Period*/ 1000, /*Flash Length*/ 600, "Fast Bubbles", "FR.1.1.2", any, 1));
    
    // Animation type 1.2 : Random STROBE
    //Slow strobe
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, square, /*Flash Period*/ 800, /*Flash Length*/ 1000/FRATE, "Slow Rand. Strobe", "FR.1.2.1", any, 1));
    //Fast strobe
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, square, /*Flash Period*/ 300, /*Flash Length*/ 1000/FRATE, "Mid. Rand. Strobe", "FR.1.2.2", any, 1));
    //Very Fast strobe
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, square, /*Flash Period*/ 100, /*Flash Length*/ 1000/FRATE, "Fast Rand. Strobe", "FR.1.2.3", any, 1));

    // Animation type 1.3 : Random CHASER
    //Slow Chaser
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, square, /*Flash Period*/ 4000, /*Flash Length*/ 1500, "Slow Rand. Chaser", "FR.1.3.1", any, 1));
    //Fast Chaser
    front_rack.animations.push_back(new SpotRackAnimation1(&front_rack, square, /*Flash Period*/ 1000, /*Flash Length*/ 600, "Fast Rand. Chaser", "FR.1.3.2", any, 1));


    // Animation type 4 : Analog BEAT
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, 1.0, "Analog Flash (100%) ", "FR.4.1", any));
    front_rack.animations.push_back(new SpotRackAnimation4(&front_rack, 0.7, "Analog Flash (70%)", "FR.4.2", any));
    
    // Animation type 5 : Digital BEAT
    front_rack.animations.push_back(new SpotRackAnimation5(&front_rack, "Digital Flash", "FR.5", leader, 1, 255));

    

    front_rack.activate_none();
};


        /**
######     #     #####  #    #       #   ####### 
#     #   # #   #     # #   #       ##   #       
#     #  #   #  #       #  #       # #   #       
######  #     # #       ###          #   ######  
#   #   ####### #       #  #         #         # 
#    #  #     # #     # #   #        #   #     # 
#     # #     #  #####  #    #     #####  ##### 
        */

// Define animation for the background spot rack
void rack_15_init(){
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black,         black,       100000, 1000,   " ", "R15.0", backer, 0));
    
    //Very Slow & overlapping Bubbles
    // Monochrome bubbles, no background
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black, red,    gaussian, 4000, 15000, "VS red bubbles",     "R15.1.1.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black, purple, gaussian, 4000, 15000, "VS purple bubbles",  "R15.1.1.2", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black, gold,   gaussian, 4000, 15000, "VS gold bubbles",    "R15.1.1.3", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black, sodium, gaussian, 4000, 15000, "VS sodium bubbles",  "R15.1.1.4", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black, cyan,   gaussian, 4000, 15000, "VS cyan bubbles",    "R15.1.1.5", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, black, sodium, gaussian, 4000, 15000, "VS sodium bubbles",  "R15.1.1.6", any, 1));
    //Monochrome bubbles, same color background
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,     red,    gaussian, 5000, 7000, "VS red bubbles, red backgd",        "R15.1.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple,  purple, gaussian, 5000, 7000, "VS purple bubbles, purple backgd",  "R15.1.2.2", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, gold,    gold,   gaussian, 5000, 7000, "VS gold bubbles, gold backgd",      "R15.1.2.3", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, sodium,  sodium, gaussian, 5000, 7000, "VS sodium bubbles, sodium backgd",  "R15.1.2.4", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, sodium,  sodium, gaussian, 5000, 7000, "VS sodium bubbles, sodium backgd",  "R15.1.2.6", any, 1));
    //Monochrome on different color background
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,     gold,    gaussian, 5000, 70000, "VS gold bubbles, red backgd",      "R15.1.3.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,     sodium,  gaussian, 5000, 70000, "VS sodium bubbles, red backgd",    "R15.1.3.2", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,     purple,  gaussian, 5000, 70000, "VS purple bubbles, red backgd",    "R15.1.3.3", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple,  gold,    gaussian, 5000, 70000, "VS gold bubbles, purple backgd",   "R15.1.3.4", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple,  sodium,  gaussian, 5000, 70000, "VS sodium bubbles, purple backgd", "R15.1.3.5", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,     cyan,    gaussian, 5000, 70000, "VS cyan bubbles, red backgd",      "R15.1.3.6", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple,  cyan,    gaussian, 5000, 70000, "VS cyan bubbles, purple backgd",   "R15.1.3.7", any, 1));

    //Short & scarces pulses
    // Monochrome
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,    red,    square, 15000, 50, "red flashes, red background",         "R15.2.1.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple, purple, square, 15000, 50, "purple flashes, purple background",   "R15.2.1.1", any, 1));
    //Bicolor
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,    gold,    square, 15000, 50, "gold flashes, red background",      "R15.2.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,    sodium,  square, 15000, 50, "cyan flashes, red background",      "R15.2.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,    purple,  square, 15000, 50, "purple flashes, red background",    "R15.2.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, red,    cyan,    square, 15000, 50, "cyan flashes, red background",      "R15.2.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple, gold,    square, 15000, 50, "gold flashes, purple background",   "R15.2.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple, sodium,  square, 15000, 50, "sodium flashes, purple background", "R15.2.2.1", any, 1));
    rack_15.animations.push_back(new SpotRackAnimation1(&rack_15, purple, cyan,    square, 15000, 50, "cyan flashes, purple background",   "R15.2.2.1", any, 1));


    rack_15.activate_none();
};

/**
######                          #         ###   
#     #   ##    ####  #    #    #    #   #   #  
#     #  #  #  #    # #   #     #    #  #     # 
######  #    # #      ####      #    #  #     # 
#   #   ###### #      #  #      ####### #     # 
#    #  #    # #    # #   #          #   #   #  
#     # #    #  ####  #    #         #    ###   
        */

// Define animation for the background spot rack
void rack_40_init(){
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black,         black,       100000, 1000,   " ", "R40.0", backer, 0));
    
    //Very Slow & overlapping Bubbles
    // Monochrome bubbles, no background
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black, red,    gaussian, 5000, 10000, "VS red bubbles",     "R40.1.1.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black, purple, gaussian, 5000, 10000, "VS purple bubbles",  "R40.1.1.2", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black, gold,   gaussian, 5000, 10000, "VS gold bubbles",    "R40.1.1.3", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black, sodium, gaussian, 5000, 10000, "VS sodium bubbles",  "R40.1.1.4", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black, cyan,   gaussian, 5000, 10000, "VS cyan bubbles",    "R40.1.1.5", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, black, sodium, gaussian, 5000, 10000, "VS sodium bubbles",  "R40.1.1.6", any, 1));
    //Monochrome bubbles, same color background
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,     red,    gaussian, 5000, 10000, "VS red bubbles, red backgd",        "R40.1.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple,  purple, gaussian, 5000, 10000, "VS purple bubbles, purple backgd",  "R40.1.2.2", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, gold,    gold,   gaussian, 5000, 10000, "VS gold bubbles, gold backgd",      "R40.1.2.3", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, sodium,  sodium, gaussian, 5000, 10000, "VS sodium bubbles, sodium backgd",  "R40.1.2.4", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, sodium,  sodium, gaussian, 5000, 10000, "VS sodium bubbles, sodium backgd",  "R40.1.2.6", any, 1));
    //Monochrome on different color background
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,     gold,    gaussian, 5000, 10000, "VS gold bubbles, red backgd",      "R40.1.3.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,     sodium,  gaussian, 5000, 10000, "VS sodium bubbles, red backgd",    "R40.1.3.2", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,     purple,  gaussian, 5000, 10000, "VS purple bubbles, red backgd",    "R40.1.3.3", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple,  gold,    gaussian, 5000, 10000, "VS gold bubbles, purple backgd",   "R40.1.3.4", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple,  sodium,  gaussian, 5000, 10000, "VS sodium bubbles, purple backgd", "R40.1.3.5", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,     cyan,    gaussian, 5000, 10000, "VS cyan bubbles, red backgd",      "R40.1.3.6", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple,  cyan,    gaussian, 5000, 10000, "VS cyan bubbles, purple backgd",   "R40.1.3.7", any, 1));

    //Short & scarces pulses
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,    gold,    square, 10000, 50, "gold flashes, red background",      "R40.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,    sodium,  square, 10000, 50, "cyan flashes, red background",      "R40.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,    purple,  square, 10000, 50, "purple flashes, red background",    "R40.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, red,    cyan,    square, 10000, 50, "cyan flashes, red background",      "R40.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple, gold,    square, 10000, 50, "gold flashes, purple background",   "R40.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple, sodium,  square, 10000, 50, "sodium flashes, purple background", "R40.2.1", any, 1));
    rack_40.animations.push_back(new SpotRackAnimation1(&rack_40, purple, cyan,    square, 10000, 50, "cyan flashes, purple background",   "R40.2.1", any, 1));

    rack_40.activate_none();
};

        /**
######                           #####  #     # ####### #     # ######   #####  
#     #   ##    ####  #    #    #     # #     # #       #     # #     # #     # 
#     #  #  #  #    # #   #     #       #     # #       #     # #     # #       
######  #    # #      ####       #####  ####### #####   ####### #     #  #####  
#   #   ###### #      #  #            # #     # #       #     # #     #       # 
#    #  #    # #    # #   #     #     # #     # #       #     # #     # #     # 
#     # #    #  ####  #    #     #####  #     # ####### #     # ######   #####  
        */
void shehds_rack_init(){
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, black,  black,       100000, 1000,   " ", "BR2.0", backer, 0));

    // Monochrome SLOW & Overlapping chaser
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, black, red, square, 25000, 120000, "VS Red random chaser", "SR.1.1", any, 1));  
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, black, purple, square, 25000, 120000, "VS Red random chaser", "SR.1.1", any, 1));  

    //Bicolor SLOW & Overlapping Chaser
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, red,     purple,   square, 25000, 30000, "VS purple chaser, red background",    "SR.2.1", any, 1));  
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, red,     gold,     square, 25000, 30000, "VS gold chaser, red background",      "SR.2.2", any, 1));  
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, purple,  gold,     square, 25000, 30000, "VS gold chaser, purple background",   "SR.2.3", any, 1));  
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, purple,  sodium,   square, 25000, 30000, "VS sodium chaser, purple background", "SR.2.4", any, 1));  
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, purple,  cyan,     square, 25000, 30000, "VS cyan chaser, purple background",   "SR.2.5", any, 1));  

    //Short pulses over BACKGROUND color
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, red,    gold,    square, 30000, 50, "gold flashes, red background",      "SR.3.1", any, 1));
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, red,    sodium,  square, 30000, 50, "cyan flashes, red background",      "SR.3.1", any, 1));
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, red,    purple,  square, 30000, 50, "purple flashes, red background",    "SR.3.1", any, 1));
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, red,    cyan,    square, 30000, 50, "cyan flashes, red background",      "SR.3.1", any, 1));
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, purple, gold,    square, 30000, 50, "gold flashes, purple background",   "SR.3.1", any, 1));
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, purple, sodium,  square, 30000, 50, "sodium flashes, purple background", "SR.3.1", any, 1));
    shehds_rack.animations.push_back(new SpotRackAnimation1(&shehds_rack, purple, cyan,    square, 30000, 50, "cyan flashes, purple background",   "SR.3.1", any, 1));

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
// TODO support light colors
DMX_vec FunGeneration_12x1W_RGBW(simpleColor c, int intensity){
    switch (c){
    case black:           return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);break;
    case red:             return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);break;
    case green:           return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 161.0/255*intensity);break;
    case blue:            return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);break;
    case yellow:          return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);break;
    case orange:          return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);break;
    case sodium:          return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);break;
    case cyan:            return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);break;
    case purple:          return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);break;    
    case magenta:         return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);break;
    case pink:            return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);break;
    case w_white:         return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);break;
    case c_white:         return fcn::RGBW_norm(DMX_vec{255,230,213,255}, 180.0/255*intensity);break;
    case gold:            return fcn::RGBW_norm(DMX_vec{255,40,0,180}, intensity);break;
    case light_blue:      return fcn::RGBW_norm(DMX_vec{50,64,255,0}, intensity);break;
    case light_cyan:      return fcn::RGBW_norm(DMX_vec{0,219,255,100}, intensity);break;
    case light_green:     return fcn::RGBW_norm(DMX_vec{30,255,30,100}, intensity);break;
    case light_magenta:   return fcn::RGBW_norm(DMX_vec{255,70,240,0}, intensity);break;
    case light_pink:      return fcn::RGBW_norm(DMX_vec{255,50,100,0}, intensity);break;
    case light_purple:    return fcn::RGBW_norm(DMX_vec{180,63,255,0}, intensity);break;
    case light_red:       return fcn::RGBW_norm(DMX_vec{255,20,20,0}, intensity);break;
    // case sevika_pink:     return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);break;
    // case hextech_cyan:    return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);break;
    // case shimmer_purple:  return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);break;
    default:              return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);break;
    }
}

DMX_vec Shehds_10x8W_RGBW(simpleColor c, int intensity){
    switch (c){
        case black:             return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);break;
        case red:               return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);break;
        case green:             return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 161.0/255*intensity);break;
        case blue:              return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);break;
        case yellow:            return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);break;
        case orange:            return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);break;
        case sodium:            return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);break;
        case cyan:              return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);break;
        case purple:            return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);break;    
        case magenta:           return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);break;
        case pink:              return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);break;
        case w_white:           return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);break;
        case c_white:           return fcn::RGBW_norm(DMX_vec{255,230,213,255}, 180.0/255*intensity);break;
        case gold:              return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);break;
        // case sevika_pink:       return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);break;
        // case hextech_cyan:      return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);break;
        // case shimmer_purple:    return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);break;
        default:                return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);break;
    }
}

DMX_vec Shehds_7x18W_RGBWAU(simpleColor c, int intensity){
    switch (c){
        case black:          return fcn::RGBW_norm(DMX_vec{0,0,0,0,0,0}, -1);break;
        case red:            return fcn::RGBW_norm(DMX_vec{255,0,0,0,0,0}, -1);break;
        case green:          return fcn::RGBW_norm(DMX_vec{4,255,0,0,0,0}, -1);break;
        case blue:           return fcn::RGBW_norm(DMX_vec{0,5,255,0,0,0}, -1); break;
        case yellow:         return fcn::RGBW_norm(DMX_vec{255,126,0,0,70,0}, -1);break;
        case orange:         return fcn::RGBW_norm(DMX_vec{255,47,0,0,255,0}, -1);break;
        case sodium:         return fcn::RGBW_norm(DMX_vec{255,20,0,0,255,0}, -1);break;
        case cyan:           return fcn::RGBW_norm(DMX_vec{0,233,255,0,0,0}, -1);break;
        case purple:         return fcn::RGBW_norm(DMX_vec{96,0,255,0,0,255}, -1);break;    
        case magenta:        return fcn::RGBW_norm(DMX_vec{159,0,255,0,0,255}, -1);break;
        case pink:           return fcn::RGBW_norm(DMX_vec{255,0,137,0,0,0}, -1);break;
        case w_white:        return fcn::RGBW_norm(DMX_vec{221,104,0,255,167,0}, -1);break;
        case c_white:        return fcn::RGBW_norm(DMX_vec{255,227,200,255,0,0}, -1);break;
        case gold:           return fcn::RGBW_norm(DMX_vec{255,58,0,49,134,0}, -1);break;
        // case sevika_pink:    return fcn::RGBW_norm(DMX_vec{255,0,27,0,0,0}, -1);break;
        // case hextech_cyan:   return fcn::RGBW_norm(DMX_vec{0,153,255,0,0,0}, -1);break;
        // case shimmer_purple: return fcn::RGBW_norm(DMX_vec{190,0,255,0,0,0}, -1);break;
        default:             return fcn::RGBW_norm(DMX_vec{0,0,0,0,0,0}, -1);break;
    }
}


DMX_vec SpotFixture::RGBW(simpleColor c, int intensity){
    switch (this->type){
        case FunGen_RGBW_12x1W :    return FunGeneration_12x1W_RGBW(c, intensity);break;
        case Shehds_RGBWAU_10x8W :  return Shehds_10x8W_RGBW(c, intensity);break;
        case Shehds_RGBWAU_7x18W :  return Shehds_7x18W_RGBWAU(c, intensity);break;
        
        default :    break;
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

DMX_vec SpotRack::RGBW(simpleColor c, int intensity){ //TODO delete
    // log(4, __FILE__, " ", __LINE__, " ",__func__);

    switch (c)
    {
    case black:           return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);break;
    case red:             return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);break;
    case green:           return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 161.0/255*intensity);break;
    case blue:            return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);break;
    case yellow:          return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);break;
    case orange:          return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);break;
    case sodium:          return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);break;
    case cyan:            return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);break;
    case purple:          return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);break;    
    case magenta:         return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);break;
    case pink:            return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);break;
    case w_white:         return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);break;
    case gold:            return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);break;
    // case sevika_pink :    return fcn::RGBW_norm(DMX_vec{255,0,11,0}, intensity);break;
    // case hextech_cyan :   return fcn::RGBW_norm(DMX_vec{0,153,255,0}, intensity);break;
    // case shimmer_purple:  return fcn::RGBW_norm(DMX_vec{245,0,255,0}, intensity);break;
    default:              return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);break;
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
  ###          ######                             #####                              
 #   #         #     # #        ##   # #    #    #     #  ####  #       ####  #####  
#     #        #     # #       #  #  # ##   #    #       #    # #      #    # #    # 
#     #        ######  #      #    # # # #  #    #       #    # #      #    # #    # 
#     # ###    #       #      ###### # #  # #    #       #    # #      #    # #####  
 #   #  ###    #       #      #    # # #   ##    #     # #    # #      #    # #   #  
  ###   ###    #       ###### #    # # #    #     #####   ####  ######  ####  #    # 
  */
// PLAIN COLOR : display one color on all every spot of the rack
void SpotRackAnimation0::init(){
    BaseAnimation::init();

    for (auto spot : this->fixture->spots){
        spot->pixel = spot->RGBW(this->color);
    }
}
void SpotRackAnimation0::init(const color_vec& palette){
    //AUTOCOLOR init
    switch (palette.size())
    {
    case 0:
        this->color = black;        break;
    default:
        this->color = palette[0];   break;
    }

    // STANDARD init
    SpotRackAnimation0::init();
}

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

}
void SpotRackAnimation1::init(const color_vec& palette){
    //AUTOCOLOR init
    switch (palette.size())
    {
    case 0:     this->flash_colors=color_vec{black},        this->back_color=black;
        break;
    case 1:     this->flash_colors=color_vec{palette[0]},   this->back_color=palette[0];
        break;
    case 2:     this->flash_colors=color_vec{palette[0]},   this->back_color=palette[1];
        break;
    default:    this->flash_colors=color_vec{black},        this->back_color=black;
        break;
    }
    // log(3, this->name, " init with palette ", fcn::palette_to_string(palette));
    //STANDARD init
    SpotRackAnimation1::init();
    
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
        auto pixel_size = current_spot->pixel.size();
        time_t &t_next = current_spot_next_flash.time;
        time_t &t_prev = current_spot_prev_flash.time;
        simpleColor &c_next = current_spot_next_flash.color;
        simpleColor &c_prev = current_spot_prev_flash.color;

        // log(4, __FILE__, " ", __LINE__, " ",__func__, " Mark2 , ", fcn::num_to_str(i_spot));

        const pixel     ani_backgd_RGBW = current_spot->RGBW(back_color, SPOTRACK_ANI1_BkG_INTENSITY_LOW);
        pixel           frame_backgd_RGBW = current_spot->RGBW(black);
        // log(1, "Pixel size : ", fcn::num_to_str((int)pixel_size));

        // compute fluctuating background color values :
            // frame_backgd_RGBW[R] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[R] * (1 + fluct_col*s[(i_spot+0)%5]))  ,0),255);
            // frame_backgd_RGBW[G] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[G] * (1 + fluct_col*s[(i_spot+1)%5]))  ,0),255);
            // frame_backgd_RGBW[B] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[B] * (1 + fluct_col*s[(i_spot+2)%5]))  ,0),255);
            // frame_backgd_RGBW[W] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * ani_backgd_RGBW[W] * (1 + fluct_col*s[(i_spot+3)%5]))  ,0),255);
            for (auto i_subpix = 0; i_subpix<pixel_size; i_subpix++){
                frame_backgd_RGBW[i_subpix] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%s.size()]) * ani_backgd_RGBW[i_subpix] * (1 + fluct_col*s[(i_spot+i_subpix)%s.size()]))  ,0),255);
            }
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

            DMX_vec frame_flash_RGBW = (t-t_prev > t_next-t) ? current_spot->RGBW(c_next) : current_spot->RGBW(c_prev);
            // current_spot->RGBWout[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[R] + flash_intensity * frame_flash_RGBW[R]  ),0),255); 
            // current_spot->RGBWout[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[G] + flash_intensity * frame_flash_RGBW[G]  ),0),255);
            // current_spot->RGBWout[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[B] + flash_intensity * frame_flash_RGBW[B]  ),0),255);
            // current_spot->RGBWout[W] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * frame_backgd_RGBW[W] + flash_intensity * frame_flash_RGBW[W]  ),0),255);
            for (auto i_subpix = 0 ; i_subpix<pixel_size; i_subpix++){
                 current_spot->pixel[i_subpix] = min(max( (int)( (1.0-pow(flash_intensity, 0.4)) * frame_backgd_RGBW[i_subpix] + flash_intensity * frame_flash_RGBW[i_subpix]  ),0),255); 
            }
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
            spots[i]->pixel  = this->fixture->spots[i]->RGBW(this->color);
        else    
            spots[i]->pixel  = this->fixture->spots[i]->RGBW(black);


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
//TODO finish or delete
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
#                 #                                          ######                      
#    #           # #   #    #   ##   #       ####   ####     #     # ######   ##   ##### 
#    #          #   #  ##   #  #  #  #      #    # #    #    #     # #       #  #    #   
#    #         #     # # #  # #    # #      #    # #         ######  #####  #    #   #   
####### ###    ####### #  # # ###### #      #    # #  ###    #     # #      ######   #   
     #  ###    #     # #   ## #    # #      #    # #    #    #     # #      #    #   #   
     #  ###    #     # #    # #    # ######  ####   ####     ######  ###### #    #   #
*/
void SpotRackAnimation4::init(){
    BaseAnimation::init(); //TODO check with debug if this really works ??
    // Resets spots values (pixel & master) to clear any remainder of the previous active animation
    this->fixture->reset_spots();
}

// Special init() function for automatic color definition (in addition to standard init() function)
void SpotRackAnimation4::init(const color_vec& palette){
    // AUTOCOLOR init : assign front & back color based on passed color palette color_vec&
    color_vec color_palette = palette;  //useless ?
    //TODO protect against empty palette --> set all black in this case
    this->flash_color = color_palette[0];       // first palette color is the flash color
    if (color_palette.size()>1){
        this->back_color = color_palette[1];    // second color (if exists) is the back color
    }else{      
        this-> back_color = black;              // back color is  black otherwise
    }

    // then call the "STANDARD" init() function for stuff unrelated to autocolor
    SpotRackAnimation4::init();
}

void SpotRackAnimation4::new_frame(){
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    const int n_unit = this->fixture->spots.size();

    // enable / disable
    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);
    
    // for each new beat, sort segments in random order
    if (sampler.new_beat)
        units_index = fcn::randomized_vector(units_index);
        
    // Compute intensity value based on time elapsed since last beat
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    // compute number of spots flashing at once
    int n_unit_on = density * n_unit;


    for (int i=0; i<n_unit; i++){
        auto current_spot = this->fixture->spots[units_index[i]];

        pixel backgd_RGB    = current_spot->RGBW(back_color, 20);
        pixel flash_RGB     = current_spot->RGBW(flash_color);
        pixel final_RGB     = current_spot->RGBW(black); //initialization before calculations
        
        if (param_activate_flash && auto_activate_flash && i<n_unit_on){
            for(auto i_subpix = 0; i_subpix<final_RGB.size(); i_subpix++){
                final_RGB[i_subpix] = (1-pow(coef, 0.2)) * backgd_RGB[i_subpix] + coef * flash_RGB[i_subpix];
            }
        }else{
            final_RGB = backgd_RGB;
        }
    
        current_spot->pixel = final_RGB;
    }
}

/*
#######        ######                                    ######                      
#              #     # #  ####  # #####   ##   #         #     # ######   ##   ##### 
#              #     # # #    # #   #    #  #  #         #     # #       #  #    #   
######         #     # # #      #   #   #    # #         ######  #####  #    #   #   
      # ###    #     # # #  ### #   #   ###### #         #     # #      ######   #   
#     # ###    #     # # #    # #   #   #    # #         #     # #      #    #   #   
 #####  ###    ######  #  ####  #   #   #    # ######    ######  ###### #    #   #   
*/
void SpotRackAnimation5::init(){
    BaseAnimation::init();
}
void SpotRackAnimation5::init(const color_vec& palette){
    //AUTOCOLOR init
    switch (palette.size())
    {
    case 0:     this->flash_color=black,        this->back_color=black;
        break;
    case 1:     this->flash_color=palette[0];   this->back_color=palette[0];
        break;
    case 2:     this->flash_color=palette[0],   this->back_color=palette[1];
        break;
    default:    this->flash_color=black,        this->back_color=black;
        break;
    }

    //Standard init
    SpotRackAnimation5::init();
}

void SpotRackAnimation5::new_frame(){
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size();
    

    bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/; //TODO useless ?

    // for each new beat, sort segments in random order
    if (sampler.new_beat){
        units_index = fcn::randomized_vector(units_index);
        // log(2, "BEAT");
    }

    // compute intensity value
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    //derive number of segments to turn on
    int n_unit_on = coef * n_unit;
    n_unit_on = max(1, n_unit_on);    // keep at least one random spot on between beats
    // log(3, "N spot ON : ", fcn::num_to_str(n_unit_on));

    //chose which segments to turn on
    for (int i=0; i<n_unit; i++){
        SpotFixture *current_spot = this->fixture->spots[units_index[i]];   //for readability

        pixel flash_RGB  = current_spot->RGBW(this->flash_color);
        pixel backgd_RGB = current_spot->RGBW(this->back_color, 20);
        
        if (i<n_unit_on){
            current_spot->pixel = flash_RGB;
        }else{
            current_spot->pixel = backgd_RGB;
        }
    }
}