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


    // Monochrome background
    animations.push_back(new AddrLEDAnimation1(this, black,       red,  "Red background",      "PIX.1",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    sodium,  "Sodium background",   "PIX.2",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    orange,  "Orange background",   "PIX.3",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    yellow,  "Yellow background",   "PIX.4",   backer,   false));
 // animations.push_back(new AddrLEDAnimation1(this, black,      gold,  "Gold background",     "PIX.5",   backer,   false));
 // animations.push_back(new AddrLEDAnimation1(this, black,     white,  "White background",    "PIX.6",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,      cyan,  "Cyan background",     "PIX.7",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,      blue,  "Blue background",     "PIX.8",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,    purple,  "Purple background",   "PIX.9",   backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,   magenta,  "Magenta background",  "PIX.10",  backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,      pink,  "Pink background",     "PIX.11",  backer,   false));
    animations.push_back(new AddrLEDAnimation1(this, black,     green,  "Green background",    "PIX.12",  backer,   false));
    
    // Monochrome Flash
    animations.push_back(new AddrLEDAnimation1(this, red,       black,  "Red Flashes",      "PIX.1.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    black,  "Sodium Flashes",   "PIX.1.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    black,  "Orange Flashes",   "PIX.1.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    black,  "Yellow Flashes",   "PIX.1.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,      black,  "Gold Flashes",     "PIX.1.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     black,  "White Flashes",    "PIX.1.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      black,  "Cyan Flashes",     "PIX.1.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      black,  "Blue Flashes",     "PIX.1.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    black,  "Purple Flashes",   "PIX.1.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   black,  "Magenta Flashes",  "PIX.1.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      black,  "Pink Flashes",     "PIX.1.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     black,  "Green Flashes",    "PIX.1.12", leader));

    animations.push_back(new AddrLEDAnimation1(this, red,       red,       "Red Flashes, Red Background",          "PIX.2.1" , leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,    sodium,    "Sodium Flashes, Sodium Background",    "PIX.2.2" , leader));
    animations.push_back(new AddrLEDAnimation1(this, orange,    orange,    "Orange Flashes, Orange Background",    "PIX.2.3" , leader));
    animations.push_back(new AddrLEDAnimation1(this, yellow,    yellow,    "Yellow Flashes, Yellow Background",    "PIX.2.4" , leader));
 // animations.push_back(new AddrLEDAnimation1(this, gold,      gold,      "Gold Flashes, Gold Background",        "PIX.2.5" , leader));
 // animations.push_back(new AddrLEDAnimation1(this, white,     white,     "White Flashes, White Background",      "PIX.2.6" , leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,      cyan,      "Cyan Flashes, Cyan Background",        "PIX.2.7" , leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,      blue,      "Blue Flashes, Blue Background",        "PIX.2.8" , leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,    purple,    "Purple Flashes, Purple Background",    "PIX.2.9" , leader));
    animations.push_back(new AddrLEDAnimation1(this, magenta,   magenta,   "Magenta Flashes, Magenta Background",  "PIX.2.10" , leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,      pink,      "Pink Flashes, Pink Background",        "PIX.2.11" , leader));
    animations.push_back(new AddrLEDAnimation1(this, green,     green,     "Green Flashes, Green Background",      "PIX.2.12" , leader));

    // White Flash with monochrome background
    animations.push_back(new AddrLEDAnimation1(this, white,     red,     "White Flashes, Red background",      "PIX.3.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     sodium,  "White Flashes, Sodium background",   "PIX.3.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     orange,  "White Flashes, Orange background",   "PIX.3.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     yellow,  "White Flashes, Yellow background",   "PIX.3.4", leader));
 // animations.push_back(new AddrLEDAnimation1(this, white,     gold,    "White Flashes, Gold background",     "PIX.3.5", leader));
 // animations.push_back(new AddrLEDAnimation1(this, white,     white,   "White Flashes, White background",    "PIX.3.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     cyan,    "White Flashes, Cyan background",     "PIX.3.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     blue,    "White Flashes, Blue background",     "PIX.3.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     purple,  "White Flashes, Purple background",   "PIX.3.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     magenta, "White Flashes, Magenta background",  "PIX.3.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     pink,    "White Flashes, Pink background",     "PIX.3.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, white,     green,   "White Flashes, Green background",    "PIX.3.12", leader));
    
    // Monochrome Flashes with white background --> Low intensity white looks like SHIT !!
    // animations.push_back(new AddrLEDAnimation1(this, red,     white,    " Red Flashes, White background",      "PIX.4.1"));
    // animations.push_back(new AddrLEDAnimation1(this, sodium,  white,    " Sodium Flashes, White background",   "PIX.4.2"));
    // animations.push_back(new AddrLEDAnimation1(this, orange,  white,    " Orange Flashes, White background",   "PIX.4.3"));
    // animations.push_back(new AddrLEDAnimation1(this, yellow,  white,    " Yellow Flashes, White background",   "PIX.4.4"));
    // animations.push_back(new AddrLEDAnimation1(this, gold,    white,    " Gold Flashes, White background",     "PIX.4.5"));
    // animations.push_back(new AddrLEDAnimation1(this, white,   white,    " White Flashes, White background",    "PIX.4.6"));
    // animations.push_back(new AddrLEDAnimation1(this, cyan,    white,    " Cyan Flashes, White background",     "PIX.4.7"));
    // animations.push_back(new AddrLEDAnimation1(this, blue,    white,    " Blue Flashes, White background",     "PIX.4.8"));
    // animations.push_back(new AddrLEDAnimation1(this, purple,  white,    " Purple Flashes, White background",   "PIX.4.9"));
    // animations.push_back(new AddrLEDAnimation1(this, magenta, white,    " Magenta Flashes, White background",  "PIX.4.10"));
    // animations.push_back(new AddrLEDAnimation1(this, pink,    white,    " Pink Flashes, White background",     "PIX.4.11"));
    // animations.push_back(new AddrLEDAnimation1(this, green,   white,    " Green Flashes, White background",    "PIX.4.12"));

    // Bicolor animation based on color palettes
    animations.push_back(new AddrLEDAnimation1(this, cyan,     red,       "cyan Flashes, red background",         "PIX.6.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     magenta,   "cyan Flashes, magenta background",     "PIX.6.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     purple,    "gold Flashes, purple background",      "PIX.6.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     red,       "gold Flashes, red background",         "PIX.6.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     orange,    "gold Flashes, orange background",      "PIX.6.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     sodium,    "gold Flashes, sodium background",      "PIX.6.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     purple,    "cyan Flashes, purple background",      "PIX.6.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, pink,     purple,    "pink Flashes, purple background",      "PIX.6.8", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     pink,      "cyan Flashes, pink background",        "PIX.6.9", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     green,     "cyan Flashes, pink background",        "PIX.6.10", leader));
    animations.push_back(new AddrLEDAnimation1(this, green,    cyan,      "cyan Flashes, pink background",        "PIX.6.11", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     orange,    "cyan Flashes, pink background",        "PIX.6.12", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     sodium,    "cyan Flashes, pink background",        "PIX.6.13", leader));
    
    this->activate_none();
}

// spits out an ordered vector containing every subpixel value (0-256)
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
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    pixel backgd_RGB = this->fixture->RGB(back_color, 40);
    pixel flash_RGB = this->fixture->RGB(flash_color);
    pixel final_RGB(3);

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
    this->fixture->set_allpix_color(final_RGB);
}