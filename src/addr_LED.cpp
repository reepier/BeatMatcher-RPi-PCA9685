#include <algorithm>

using namespace std;

#include "addr_LED.h"

AddressableLED addr_led(1, 0, 3*NUM_PIX, "Addressable LEDs", 1, 180);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */


void AddressableLED::init(){
    // declare animations here
    animations.push_back(new AddrLEDAnimation1(this, black,  black,  " ",    "PIX.0.0", backer));


// ANIMATION 1 : Analog Flash on Beat (Original Beatmatcher animation)
    // Monochrome background
    animations.push_back(new AddrLEDAnimation1(this, black,       red,  "Red background",      "PIX.1.1.0.1",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    sodium,  "Sodium background",   "PIX.1.1.0.2",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    orange,  "Orange background",   "PIX.1.1.0.3",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    yellow,  "Yellow background",   "PIX.1.1.0.4",   backer,   false));
 // animations.push_back(new AddrLEDAnimation1(this, black,      gold,  "Gold background",     "PIX.1.1.0.5",   backer,   false));
 // animations.push_back(new AddrLEDAnimation1(this, black,     white,  "White background",    "PIX.1.1.0.6",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,      cyan,  "Cyan background",     "PIX.1.1.0.7",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,      blue,  "Blue background",     "PIX.1.1.0.8",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    purple,  "Purple background",   "PIX.1.1.0.9",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,   magenta,  "Magenta background",  "PIX.1.1.0.10",  backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,      pink,  "Pink background",     "PIX.1.1.0.11",  backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,     green,  "Green background",    "PIX.1.1.0.12",  backer,   false));
    
    // Monochrome Flash
    animations.push_back(new AddrLEDAnimation1(this, red,       black,  "Red Flashes",      "PIX.1.1.1.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    black,  "Sodium Flashes",   "PIX.1.1.1.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    black,  "Orange Flashes",   "PIX.1.1.1.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    black,  "Yellow Flashes",   "PIX.1.1.1.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,      black,  "Gold Flashes",     "PIX.1.1.1.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     black,  "White Flashes",    "PIX.1.1.1.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      black,  "Cyan Flashes",     "PIX.1.1.1.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      black,  "Blue Flashes",     "PIX.1.1.1.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    black,  "Purple Flashes",   "PIX.1.1.1.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   black,  "Magenta Flashes",  "PIX.1.1.1.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      black,  "Pink Flashes",     "PIX.1.1.1.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     black,  "Green Flashes",    "PIX.1.1.1.12", leader));

    animations.push_back(new AddrLEDAnimation1(this, red,       red,       "Red Flashes, Red Background",          "PIX.1.1.2.1" , leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    sodium,    "Sodium Flashes, Sodium Background",    "PIX.1.1.2.2" , leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    orange,    "Orange Flashes, Orange Background",    "PIX.1.1.2.3" , leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    yellow,    "Yellow Flashes, Yellow Background",    "PIX.1.1.2.4" , leader));
 // animations.push_back(new AddrLEDAnimation1(this, gold,      gold,      "Gold Flashes, Gold Background",        "PIX.1.1.2.5" , leader));
 // animations.push_back(new AddrLEDAnimation1(this, white,     white,     "White Flashes, White Background",      "PIX.1.1.2.6" , leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      cyan,      "Cyan Flashes, Cyan Background",        "PIX.1.1.2.7" , leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      blue,      "Blue Flashes, Blue Background",        "PIX.1.1.2.8" , leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    purple,    "Purple Flashes, Purple Background",    "PIX.1.1.2.9" , leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   magenta,   "Magenta Flashes, Magenta Background",  "PIX.1.1.2.10" , leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      pink,      "Pink Flashes, Pink Background",        "PIX.1.1.2.11" , leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     green,     "Green Flashes, Green Background",      "PIX.1.1.2.12" , leader));

    // White Flash with monochrome background
    animations.push_back(new AddrLEDAnimation1(this, white,     red,     "White Flashes, Red background",      "PIX.1.1.3.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     sodium,  "White Flashes, Sodium background",   "PIX.1.1.3.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     orange,  "White Flashes, Orange background",   "PIX.1.1.3.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     yellow,  "White Flashes, Yellow background",   "PIX.1.1.3.4", leader));
 // animations.push_back(new AddrLEDAnimation1(this, white,     gold,    "White Flashes, Gold background",     "PIX.1.1.3.5", leader));
 // animations.push_back(new AddrLEDAnimation1(this, white,     white,   "White Flashes, White background",    "PIX.1.1.3.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     cyan,    "White Flashes, Cyan background",     "PIX.1.1.3.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     blue,    "White Flashes, Blue background",     "PIX.1.1.3.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     purple,  "White Flashes, Purple background",   "PIX.1.1.3.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     magenta, "White Flashes, Magenta background",  "PIX.1.1.3.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     pink,    "White Flashes, Pink background",     "PIX.1.1.3.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     green,   "White Flashes, Green background",    "PIX.1.1.3.12", leader));
    
    // Monochrome Flashes with white background --> Low intensity white looks like SHIT !!
    // animations.push_back(new AddrLEDAnimation1(this, red,     white,    " Red Flashes, White background",      "PIX.1.4.1"));
    // animations.push_back(new AddrLEDAnimation1(this, sodium,  white,    " Sodium Flashes, White background",   "PIX.1.4.2"));
    // animations.push_back(new AddrLEDAnimation1(this, orange,  white,    " Orange Flashes, White background",   "PIX.1.4.3"));
    // animations.push_back(new AddrLEDAnimation1(this, yellow,  white,    " Yellow Flashes, White background",   "PIX.1.4.4"));
    // animations.push_back(new AddrLEDAnimation1(this, gold,    white,    " Gold Flashes, White background",     "PIX.1.4.5"));
    // animations.push_back(new AddrLEDAnimation1(this, white,   white,    " White Flashes, White background",    "PIX.1.4.6"));
    // animations.push_back(new AddrLEDAnimation1(this, cyan,    white,    " Cyan Flashes, White background",     "PIX.1.4.7"));
    // animations.push_back(new AddrLEDAnimation1(this, blue,    white,    " Blue Flashes, White background",     "PIX.1.4.8"));
    // animations.push_back(new AddrLEDAnimation1(this, purple,  white,    " Purple Flashes, White background",   "PIX.1.4.9"));
    // animations.push_back(new AddrLEDAnimation1(this, magenta, white,    " Magenta Flashes, White background",  "PIX.1.4.10"));
    // animations.push_back(new AddrLEDAnimation1(this, pink,    white,    " Pink Flashes, White background",     "PIX.1.4.11"));
    // animations.push_back(new AddrLEDAnimation1(this, green,   white,    " Green Flashes, White background",    "PIX.1.4.12"));

    // Bicolor animation based on color palettes
    animations.push_back(new AddrLEDAnimation1(this, cyan,     red,       "cyan Flashes, red background",         "PIX.1.1.6.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     magenta,   "cyan Flashes, magenta background",     "PIX.1.1.6.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     purple,    "gold Flashes, purple background",      "PIX.1.1.6.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     red,       "gold Flashes, red background",         "PIX.1.1.6.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     orange,    "gold Flashes, orange background",      "PIX.1.1.6.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     sodium,    "gold Flashes, sodium background",      "PIX.1.1.6.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     purple,    "cyan Flashes, purple background",      "PIX.1.1.6.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,     purple,    "pink Flashes, purple background",      "PIX.1.1.6.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     pink,      "cyan Flashes, pink background",        "PIX.1.1.6.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     green,     "cyan Flashes, pink background",        "PIX.1.1.6.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,    cyan,      "cyan Flashes, pink background",        "PIX.1.1.6.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     orange,    "cyan Flashes, pink background",        "PIX.1.1.6.12", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     sodium,    "cyan Flashes, pink background",        "PIX.1.1.6.13", leader));
    
// ANIMATION 1.2 : Analog Flash --> random segments
    // Monochrome Flash
    animations.push_back(new AddrLEDAnimation1(this, red,       black,  seg, 0.75,   "Red Flashes",      "PIX.1.2.1.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    black,  seg, 0.75,   "Sodium Flashes",   "PIX.1.2.1.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    black,  seg, 0.75,   "Orange Flashes",   "PIX.1.2.1.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    black,  seg, 0.75,   "Yellow Flashes",   "PIX.1.2.1.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,      black,  seg, 0.75,   "Gold Flashes",     "PIX.1.2.1.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     black,  seg, 0.75,   "White Flashes",    "PIX.1.2.1.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      black,  seg, 0.75,   "Cyan Flashes",     "PIX.1.2.1.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      black,  seg, 0.75,   "Blue Flashes",     "PIX.1.2.1.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    black,  seg, 0.75,   "Purple Flashes",   "PIX.1.2.1.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   black,  seg, 0.75,   "Magenta Flashes",  "PIX.1.2.1.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      black,  seg, 0.75,   "Pink Flashes",     "PIX.1.2.1.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     black,  seg, 0.75,   "Green Flashes",    "PIX.1.2.1.12", leader));

// ANIMATION 1.3 : Analog Flash --> random bars
    // Monochrome Flash
    animations.push_back(new AddrLEDAnimation1(this, red,       black,  bar, 0.6,   "Red Flashes",      "PIX.1.3.1.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    black,  bar, 0.6,   "Sodium Flashes",   "PIX.1.3.1.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    black,  bar, 0.6,   "Orange Flashes",   "PIX.1.3.1.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    black,  bar, 0.6,   "Yellow Flashes",   "PIX.1.3.1.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,      black,  bar, 0.6,   "Gold Flashes",     "PIX.1.3.1.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     black,  bar, 0.6,   "White Flashes",    "PIX.1.3.1.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      black,  bar, 0.6,   "Cyan Flashes",     "PIX.1.3.1.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      black,  bar, 0.6,   "Blue Flashes",     "PIX.1.3.1.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    black,  bar, 0.6,   "Purple Flashes",   "PIX.1.3.1.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   black,  bar, 0.6,   "Magenta Flashes",  "PIX.1.3.1.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      black,  bar, 0.6,   "Pink Flashes",     "PIX.1.3.1.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     black,  bar, 0.6,   "Green Flashes",    "PIX.1.3.1.12", leader));

// ANIMATION 1.3 : Analog Flash --> random pix
    // Monochrome Flash
    animations.push_back(new AddrLEDAnimation1(this, red,       black,  pix, 0.7,   "Red Flashes",      "PIX.1.4.1.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    black,  pix, 0.7,   "Sodium Flashes",   "PIX.1.4.1.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    black,  pix, 0.7,   "Orange Flashes",   "PIX.1.4.1.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    black,  pix, 0.7,   "Yellow Flashes",   "PIX.1.4.1.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,      black,  pix, 0.7,   "Gold Flashes",     "PIX.1.4.1.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     black,  pix, 0.7,   "White Flashes",    "PIX.1.4.1.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      black,  pix, 0.7,   "Cyan Flashes",     "PIX.1.4.1.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      black,  pix, 0.7,   "Blue Flashes",     "PIX.1.4.1.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    black,  pix, 0.7,   "Purple Flashes",   "PIX.1.4.1.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   black,  pix, 0.7,   "Magenta Flashes",  "PIX.1.4.1.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      black,  pix, 0.7,   "Pink Flashes",     "PIX.1.4.1.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     black,  pix, 0.7,   "Green Flashes",    "PIX.1.4.1.12", leader));

// ANIMATION 2 : Segmented flash
    animations.push_back(new AddrLEDAnimation2(this, white,  black,  seg,   "White flashes, black background",      "PIX.2.1.1"));
    animations.push_back(new AddrLEDAnimation2(this, gold,   black,  seg,   "Gold flashes, black background",       "PIX.2.1.2"));
    animations.push_back(new AddrLEDAnimation2(this, red,    black,  seg,   "Red flashes, back background",         "PIX.2.1.3"));
    animations.push_back(new AddrLEDAnimation2(this, cyan,   red,    seg,   "Cyan flashes, red background",         "PIX.2.1.4"));
    
    animations.push_back(new AddrLEDAnimation2(this, white,  black,  bar,   "White flashes, black background",      "PIX.2.2.1"));
    animations.push_back(new AddrLEDAnimation2(this, gold,   black,  bar,   "Gold flashes, black background",       "PIX.2.2.2"));
    animations.push_back(new AddrLEDAnimation2(this, red,    black,  bar,   "Red flashes, back background",         "PIX.2.2.3"));
    animations.push_back(new AddrLEDAnimation2(this, cyan,   red,    bar,   "Cyan flashes, red background",         "PIX.2.2.4"));

    animations.push_back(new AddrLEDAnimation2(this, white,  black,  pix,   "White flashes, black background",      "PIX.2.3.1"));
    animations.push_back(new AddrLEDAnimation2(this, gold,   black,  pix,   "Gold flashes, black background",       "PIX.2.3.2"));
    animations.push_back(new AddrLEDAnimation2(this, red,    black,  pix,   "Red flashes, black background",         "PIX.2.3.3"));
    animations.push_back(new AddrLEDAnimation2(this, cyan,   red,    pix,   "Cyan flashes, red background",         "PIX.2.3.4"));
    
// Animation 3 : Noise
//          (Unfiltered)
    animations.push_back(new AddrLEDAnimation3(this, white, "White noise",      "PIX.3.1.1"));
    animations.push_back(new AddrLEDAnimation3(this, gold,  "Gold noise",       "PIX.3.1.2"));
    animations.push_back(new AddrLEDAnimation3(this, red,   "Red noise",        "PIX.3.1.3"));
    animations.push_back(new AddrLEDAnimation3(this, pink,  "Pink noise",       "PIX.3.1.4"));
//          (Filtered)
    animations.push_back(new AddrLEDAnimation3(this, white, true, "White noise",      "PIX.3.2.1"));
    animations.push_back(new AddrLEDAnimation3(this, gold,  true, "Gold noise",       "PIX.3.2.2"));
    animations.push_back(new AddrLEDAnimation3(this, red,   true, "Red noise",        "PIX.3.2.3"));
    animations.push_back(new AddrLEDAnimation3(this, pink,  true, "Pink noise",       "PIX.3.2.4"));

// Animation 4 : Random bursts
    animations.push_back(new AddrLEDAnimation4(this, red, color_vec{white}, gaussian, bar, 500, 1000, "White bubbles, Red bg", "PIX.4.1.1", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red}, gaussian, bar, 500, 1000, "Red bubbles, Black bg", "PIX.4.1.2", leader, 1, 255));

    animations.push_back(new AddrLEDAnimation4(this, red, color_vec{white}, square, bar, 50, 1000/FRATE, "White bubbles, Red bg", "PIX.4.2.1", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red}, square, bar, 50, 1000/FRATE, "Red bubbles, Black bg", "PIX.4.2.2", leader, 1, 255));


    this->activate_none();
}

// spits out an ordered vector containing every subpixel value (0-256)
//TODO Add support for fixture Master & Animation Master
DMX_vec AddressableLED::buffer(){
    DMX_vec data(NUM_SUBPIX);
    
    int i_data = 0;
    for (auto pix : this->pixels){        
        for (auto sub_pix : pix){
            data[i_data++] = sub_pix;
        }
    }
    return data;
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
//TODO calibrate colors
DMX_vec AddressableLED::RGB(simpleColor c, int intensity){
    // log(4, __FILE__, " ",__LINE__, " ", __func__);

    DMX_vec temp;
    int ref_int = 255;          // reference intensity, set for each color to get a constnat luminosity trhoughtou the palette
    // store in vector temp the color vector of norm 255
    switch (c){
        case black:
            temp = fcn::RGB_norm(DMX_vec{0,0,0});
            break;
        case red:
            temp = fcn::RGB_norm(DMX_vec{255,0,0});
            break;
        case green:
            ref_int = 70; 
            temp = fcn::RGB_norm(DMX_vec{0,255,0});
            break;
        case blue:
            ref_int = 40;
            temp = fcn::RGB_norm(DMX_vec{0,0,255});
            break;
        case yellow:
            ref_int = 180;
            temp = fcn::RGB_norm(DMX_vec{255,87,0});
            break;
        case orange:
            temp = fcn::RGB_norm(DMX_vec{255,35,0});
            break;
        case sodium:
            temp = fcn::RGB_norm(DMX_vec{255,16,0});
            break;
        case cyan:
            ref_int = 90;
            temp = fcn::RGB_norm(DMX_vec{0,184,255});
            break;
        case purple:
            ref_int = 200;
            temp = fcn::RGB_norm(DMX_vec{180,0,255});
            break;    
        case magenta:
            ref_int = 220;
            temp = fcn::RGB_norm(DMX_vec{255,0,197});
            break;
        case pink:
            ref_int = 240;
            temp = fcn::RGB_norm(DMX_vec{255,0,86});
            break;
        case white:
            temp = fcn::RGB_norm(DMX_vec{255,95,17});
            break;
        case gold:
            temp = fcn::RGB_norm(DMX_vec{255,50,3});
            break;
        default:
            temp = fcn::RGB_norm(DMX_vec{0,0,0});
            break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity==-1 ? -1 : (int)ref_int * intensity/255.0);
}





/*
   #    #     # ### #     #    #    ####### ### ####### #     #              #   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    #             ##   
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   #            # #   
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #   #####      #   
####### #   # #  #  #     # #######    #     #  #     # #   # #              #   
#     # #    ##  #  #     # #     #    #     #  #     # #    ##              #   
#     # #     # ### #     # #     #    #    ### ####### #     #            ####*/
void AddrLEDAnimation1::init(){
    BaseAnimation::init();
}

void AddrLEDAnimation1::new_frame(){
    balise("Addr LED Ani1 New frames...");
    BaseAnimation::new_frame();
    
    // local variables for readability
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size();

    balise("Addr LED Ani1 New frames 1");
    // enable / disable
    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);
    
    // for each new beat, sort segments in random order
    if (sampler.new_beat)
        units_index = fcn::randomized_vector(units_index);

    balise("Addr LED Ani1 New frames 1");
    // precompute pixel values
    pixel backgd_RGB = this->fixture->RGB(back_color, 20);
    pixel flash_RGB = this->fixture->RGB(flash_color);
    pixel final_mix_RGB(3);

    balise("Addr LED Ani1 New frames 2");
    // Compute intensity vaue based on time elapsed since last beat
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    // compute number of units flashing 
    int n_unit_on = density * n_unit;

    balise("Addr LED Ani1 New frames 3");
    // compute final RGB colors
    if (param_activate_flash && auto_activate_flash)
    {
         
        final_mix_RGB[R] = (1-pow(coef, 0.2)) * backgd_RGB[R] + coef * flash_RGB[R];
        final_mix_RGB[G] = (1-pow(coef, 0.2)) * backgd_RGB[G] + coef * flash_RGB[G];
        final_mix_RGB[B] = (1-pow(coef, 0.2)) * backgd_RGB[B] + coef * flash_RGB[B];
    }
    else
    {
        final_mix_RGB[R] = backgd_RGB[R];
        final_mix_RGB[G] = backgd_RGB[G];
        final_mix_RGB[B] = backgd_RGB[B];
    }

    balise("Addr LED Ani1 New frames 4");
    // set each units color
    for (int i=0; i<n_unit; i++){
        pixel unit_i_RGB;
        if (i<n_unit_on)
            unit_i_RGB = final_mix_RGB;
        else
            unit_i_RGB = backgd_RGB;
        switch (unit){
                case pix : this->fixture->pixels[units_index[i]] = unit_i_RGB;
                break;
                case seg : this->fixture->set_segment_color(units_index[i], unit_i_RGB);
                break;
                case bar : this->fixture->set_bar_color(units_index[i], unit_i_RGB);
                break;
                default :
                break;
            }
    }
}

/*
   #    #     # ### #     #    #    ####### ### ####### #     #             #####   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    #            #     #  
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   #                  #  
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #   #####     #####   
####### #   # #  #  #     # #######    #     #  #     # #   # #            #        
#     # #    ##  #  #     # #     #    #     #  #     # #    ##            #        
#     # #     # ### #     # #     #    #    ### ####### #     #            #######*/

void AddrLEDAnimation2::init(){
    BaseAnimation::init();
}

void AddrLEDAnimation2::new_frame(){
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size();

    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    // for each new beat, sort segments in random order
    if (sampler.new_beat)
        units_index = fcn::randomized_vector(units_index);

    // compute intensity value
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    //derive number of segments to turn on
    int n_unit_on = coef * n_unit;
    //chose which segments to turn on
    for (int i = 0; i<n_unit; i++){
        if (i<n_unit_on)
            switch (unit){
                case pix : this->fixture->pixels[units_index[i]] = flash_RGB;
                    break;
                case seg : this->fixture->set_segment_color(units_index[i], flash_RGB);
                    break;
                case bar : this->fixture->set_bar_color(units_index[i], flash_RGB);
                    break;
            }
            
        else
            switch (unit){
                case pix : this->fixture->pixels[units_index[i]] = backgd_RGB;
                    break;
                case seg : this->fixture->set_segment_color(units_index[i], backgd_RGB);
                    break;
                case bar : this->fixture->set_bar_color(units_index[i], backgd_RGB);
                    break;
            }
    }
}

/*
   #    #     # ### #     #    #    ####### ### ####### #     #             #####   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    #            #     #  
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   #                  #  
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #   #####     #####   
####### #   # #  #  #     # #######    #     #  #     # #   # #                  #  
#     # #    ##  #  #     # #     #    #     #  #     # #    ##            #     #  
#     # #     # ### #     # #     #    #    ### ####### #     #             ##### */

void AddrLEDAnimation3::init() {
    BaseAnimation::init();
}
void AddrLEDAnimation3::new_frame() {
    BaseAnimation::new_frame();
    
    // double f_weight = enable_filter*param_filter_weight*!is_first_frame();
    
    for (int i = 0; i<NUM_PIX; i++){
        pix_intensities[i] = min(255, max(0, fcn::random_walk((int)pix_intensities[i], 5, 0, 255) ));
        // if(f_weight != 0)
        //     pix_intensities[i] = min(255.0, max(0.0, pix_intensities[i] + f_weight * (atan_transfo[rand_min_max(0, 256)] - 127.0) ));
        // else
        //     pix_intensities[i] = atan_transfo[rand_min_max(0, 256)];

        this->fixture->pixels[i] = this->fixture->RGB(color, pix_intensities[i]);
    }
}

/*
#              ######                                            
#    #         #     # #    # #####  #####  #      ######  ####  
#    #         #     # #    # #    # #    # #      #      #      
#    #         ######  #    # #####  #####  #      #####   ####  
####### ###    #     # #    # #    # #    # #      #           # 
     #  ###    #     # #    # #    # #    # #      #      #    # 
     #  ###    ######   ####  #####  #####  ###### ######  ####  
*/
void AddrLEDAnimation4::init(){
    log(4, __FILE__, " ", __LINE__, " ",__func__, " ", this->fixture->name, " ", this->id);

    BaseAnimation::init();
    
    const int n_unit = unit==bar ? NUM_BAR : (unit==seg ? NUM_SEG : (unit==pix ? NUM_PIX : 0));

    this->flashes = vector<flash_vec>(n_unit, flash_vec(2));

    for (int i_unit=0; i_unit<n_unit; i_unit++){
        flashes[i_unit][i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2); 
        flashes[i_unit][i_prev].time = 0;
        flashes[i_unit][i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_unit][i_prev].color = black;
    }
}

void AddrLEDAnimation4::new_frame(){
    log(4, __FILE__, " ", __LINE__, " ",__func__);

    BaseAnimation::new_frame();

    long t = frame.t_current_ms;         // for readability
    int n_unit = this->flashes.size();   // for readability
    
   
    // for each spot "i" of the rack
    for (int i_unit=0; i_unit < n_unit; i_unit++){

        // auto current_spot = this->fixture->spots[i_unit];           // for readability
        auto &current_unit_flashes = flashes[i_unit];                  // for readability
        auto &current_unit_next_flash = flashes[i_unit][i_next];       // for readability
        auto &current_unit_prev_flash = flashes[i_unit][i_prev];       // for readability
        time_t &t_next = current_unit_next_flash.time;
        time_t &t_prev = current_unit_prev_flash.time;
        simpleColor &c_next = current_unit_next_flash.color;
        simpleColor &c_prev = current_unit_prev_flash.color;

        // log(4, __FILE__, " ", __LINE__, " ",__func__, " Mark2 , ", fcn::num_to_str(i_spot));

        const pixel     ani_backgd_RGB = fixture->RGB(back_color, SPOTRACK_ANI1_BkG_INTENSITY_LOW);
        
        // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
            double flash_intensity; // 0 by default
            if (flash_activation){
                // when the flash passes, compute the next flash timestamp and update prev flash
                if (t > t_next){
                    
                    t_prev = t_next;
                    t_next = t_next + rand_min_max(this->flash_len, 2*n_unit*this->rand_const_ms);
                    c_prev = c_next;
                    c_next = fcn::random_pick(this->flash_colors);
                    
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

            DMX_vec frame_flash_RGB = (t-t_prev > t_next-t) ? fixture->RGB(c_next) : this->fixture->RGB(c_prev);
            DMX_vec unit_final_RGB(3, 0);
            unit_final_RGB[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[R] + flash_intensity * frame_flash_RGB[R]  ),0),255); 
            unit_final_RGB[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[G] + flash_intensity * frame_flash_RGB[G]  ),0),255);
            unit_final_RGB[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[B] + flash_intensity * frame_flash_RGB[B]  ),0),255);

            switch (this->unit){
                case bar : this->fixture->set_bar_color(i_unit, unit_final_RGB);
                    break;
                case seg : this->fixture->set_segment_color(i_unit, unit_final_RGB);
                    break;
                case pix : this->fixture->pixels[i_unit] = unit_final_RGB;
                    break;
            }
    }
}