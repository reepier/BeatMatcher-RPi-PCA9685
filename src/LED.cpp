#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include <wiringPi.h>

#include "LED.h"
#include "sysfcn.h"

LEDFixture led(0, 13, "Led Bars", 1, 255);

// ------------------------------------------------------------
// LED FIXTURE CLASS Function definition

// Fixture initalizer
void LEDFixture::init(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    animations.push_back(new LEDAnimation1(this, black,  black,  " ",    "LED.0.0", backer));

    // Monochrome background
    animations.push_back(new LEDAnimation1(this, black, red,      "Red background",      "LED.1",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, sodium,   "Sodium background",   "LED.2",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, orange,   "Orange background",   "LED.3",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, yellow,   "Yellow background",   "LED.4",   backer,   false));
 // animations.push_back(new LEDAnimation1(this, black, gold,     "Gold background",     "LED.5",   backer,   false));
 // animations.push_back(new LEDAnimation1(this, black, w_white," White background",    "LED.6",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, cyan,     "Cyan background",     "LED.7",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, blue,     "Blue background",     "LED.8",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, purple,   "Purple background",   "LED.9",   backer,   false));
    animations.push_back(new LEDAnimation1(this, black, magenta,  "Magenta background",  "LED.10",  backer,   false));
    animations.push_back(new LEDAnimation1(this, black, pink,     "Pink background",     "LED.11",  backer,   false));
    animations.push_back(new LEDAnimation1(this, black, green,    "Green background",    "LED.12",  backer,   false));
    
    // Monochrome Flash
    animations.push_back(new LEDAnimation1(this, red,       black,  "Red Flashes",      "LED.1.1", leader));
    animations.push_back(new LEDAnimation1(this, sodium,    black,  "Sodium Flashes",   "LED.1.2", leader));
    animations.push_back(new LEDAnimation1(this, orange,    black,  "Orange Flashes",   "LED.1.3", leader));
    animations.push_back(new LEDAnimation1(this, yellow,    black,  "Yellow Flashes",   "LED.1.4", leader));
    animations.push_back(new LEDAnimation1(this, gold,      black,  "Gold Flashes",     "LED.1.5", leader));
    animations.push_back(new LEDAnimation1(this, w_white,   black,  "WWhite Flashes",    "LED.1.6", leader));
    animations.push_back(new LEDAnimation1(this, cyan,      black,  "Cyan Flashes",     "LED.1.7", leader));
    animations.push_back(new LEDAnimation1(this, blue,      black,  "Blue Flashes",     "LED.1.8", leader));
    animations.push_back(new LEDAnimation1(this, purple,    black,  "Purple Flashes",   "LED.1.9", leader));
    animations.push_back(new LEDAnimation1(this, magenta,   black,  "Magenta Flashes",  "LED.1.10", leader));
    animations.push_back(new LEDAnimation1(this, pink,      black,  "Pink Flashes",     "LED.1.11", leader));
    animations.push_back(new LEDAnimation1(this, green,     black,  "Green Flashes",    "LED.1.12", leader));

    animations.push_back(new LEDAnimation1(this, red,       red,       "Red Flashes, Red Background",          "LED.2.1" , leader));
    animations.push_back(new LEDAnimation1(this, sodium,    sodium,    "Sodium Flashes, Sodium Background",    "LED.2.2" , leader));
    animations.push_back(new LEDAnimation1(this, orange,    orange,    "Orange Flashes, Orange Background",    "LED.2.3" , leader));
    animations.push_back(new LEDAnimation1(this, yellow,    yellow,    "Yellow Flashes, Yellow Background",    "LED.2.4" , leader));
 // animations.push_back(new LEDAnimation1(this, gold,      gold,      "Gold Flashes, Gold Background",        "LED.2.5" , leader));
 // animations.push_back(new LEDAnimation1(this, w_white,     white,   "WWhite Flashes, WWhite Background",      "LED.2.6" , leader));
    animations.push_back(new LEDAnimation1(this, cyan,      cyan,      "Cyan Flashes, Cyan Background",        "LED.2.7" , leader));
    animations.push_back(new LEDAnimation1(this, blue,      blue,      "Blue Flashes, Blue Background",        "LED.2.8" , leader));
    animations.push_back(new LEDAnimation1(this, purple,    purple,    "Purple Flashes, Purple Background",    "LED.2.9" , leader));
    animations.push_back(new LEDAnimation1(this, magenta,   magenta,   "Magenta Flashes, Magenta Background",  "LED.2.10" , leader));
    animations.push_back(new LEDAnimation1(this, pink,      pink,      "Pink Flashes, Pink Background",        "LED.2.11" , leader));
    animations.push_back(new LEDAnimation1(this, green,     green,     "Green Flashes, Green Background",      "LED.2.12" , leader));

    // White Flash with monochrome background
    animations.push_back(new LEDAnimation1(this, w_white,     red,     "WWhite Flashes, Red background",      "LED.3.1", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     sodium,  "WWhite Flashes, Sodium background",   "LED.3.2", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     orange,  "WWhite Flashes, Orange background",   "LED.3.3", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     yellow,  "WWhite Flashes, Yellow background",   "LED.3.4", leader));
 // animations.push_back(new LEDAnimation1(this, w_white,     gold,    "WWhite Flashes, Gold background",     "LED.3.5", leader));
 // animations.push_back(new LEDAnimation1(this, w_white,     Wwhite,   "WWhite Flashes, WWhite background",    "LED.3.6", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     cyan,    "WWhite Flashes, Cyan background",     "LED.3.7", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     blue,    "WWhite Flashes, Blue background",     "LED.3.8", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     purple,  "WWhite Flashes, Purple background",   "LED.3.9", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     magenta, "WWhite Flashes, Magenta background",  "LED.3.10", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     pink,    "WWhite Flashes, Pink background",     "LED.3.11", leader));
    animations.push_back(new LEDAnimation1(this, w_white,     green,   "WWhite Flashes, Green background",    "LED.3.12", leader));
    
    // Monochrome Flashes with white background --> Low intensity white looks like SHIT !!
    // animations.push_back(new LEDAnimation1(this, red,     white,    " Red Flashes, White background",      "LED.4.1"));
    // animations.push_back(new LEDAnimation1(this, sodium,  white,    " Sodium Flashes, White background",   "LED.4.2"));
    // animations.push_back(new LEDAnimation1(this, orange,  white,    " Orange Flashes, White background",   "LED.4.3"));
    // animations.push_back(new LEDAnimation1(this, yellow,  white,    " Yellow Flashes, White background",   "LED.4.4"));
    // animations.push_back(new LEDAnimation1(this, gold,    white,    " Gold Flashes, White background",     "LED.4.5"));
    // animations.push_back(new LEDAnimation1(this, white,   white,    " White Flashes, White background",    "LED.4.6"));
    // animations.push_back(new LEDAnimation1(this, cyan,    white,    " Cyan Flashes, White background",     "LED.4.7"));
    // animations.push_back(new LEDAnimation1(this, blue,    white,    " Blue Flashes, White background",     "LED.4.8"));
    // animations.push_back(new LEDAnimation1(this, purple,  white,    " Purple Flashes, White background",   "LED.4.9"));
    // animations.push_back(new LEDAnimation1(this, magenta, white,    " Magenta Flashes, White background",  "LED.4.10"));
    // animations.push_back(new LEDAnimation1(this, pink,    white,    " Pink Flashes, White background",     "LED.4.11"));
    // animations.push_back(new LEDAnimation1(this, green,   white,    " Green Flashes, White background",    "LED.4.12"));

    // Bicolor animation based on color palettes
    animations.push_back(new LEDAnimation1(this, cyan,     red,       "cyan Flashes, red background",         "LED.6.1", leader));
    animations.push_back(new LEDAnimation1(this, cyan,     magenta,   "cyan Flashes, magenta background",     "LED.6.2", leader));
    animations.push_back(new LEDAnimation1(this, gold,     purple,    "gold Flashes, purple background",      "LED.6.3", leader));
    animations.push_back(new LEDAnimation1(this, gold,     red,       "gold Flashes, red background",         "LED.6.4", leader));
    animations.push_back(new LEDAnimation1(this, gold,     orange,    "gold Flashes, orange background",      "LED.6.5", leader));
    animations.push_back(new LEDAnimation1(this, gold,     sodium,    "gold Flashes, sodium background",      "LED.6.6", leader));
    animations.push_back(new LEDAnimation1(this, cyan,     purple,    "cyan Flashes, purple background",      "LED.6.7", leader));
    animations.push_back(new LEDAnimation1(this, pink,     purple,    "pink Flashes, purple background",      "LED.6.8", leader));
    animations.push_back(new LEDAnimation1(this, cyan,     pink,      "cyan Flashes, pink background",        "LED.6.9", leader));
    animations.push_back(new LEDAnimation1(this, cyan,     green,     "cyan Flashes, pink background",        "LED.6.10", leader));
    animations.push_back(new LEDAnimation1(this, green,    cyan,      "cyan Flashes, pink background",        "LED.6.11", leader));
    animations.push_back(new LEDAnimation1(this, cyan,     orange,    "cyan Flashes, pink background",        "LED.6.12", leader));
    animations.push_back(new LEDAnimation1(this, cyan,     sodium,    "cyan Flashes, pink background",        "LED.6.13", leader));
    
    
    this->activate_by_index(0);
    balise("LED animations created");
}

DMX_vec LEDFixture::buffer(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    int_vec RGBcoarse = {0,0,0};
    int_vec RGBfine = {0,0,0};
    for(auto i : int_vec{R,G,B}){
        RGBcoarse[i]   = ( this->RGBout[i] ) >> 4;
        RGBfine[i]     = ( (this->RGBout[i] - (RGBcoarse[i]<<4) ) << 4 );
    }

    // log(1, fcn::num_to_str(this->RGBout[G]), " c:", fcn::num_to_str(RGBcoarse[G])," f:", fcn::num_to_str(RGBfine[G]>>4 )," synt:", fcn::num_to_str( ((RGBcoarse[G]) << 4) + ((RGBfine[G]) >> 4) ));

    return DMX_vec{master, 
        (uint8_t)(RGBcoarse[R]), (uint8_t)(RGBcoarse[G]), (uint8_t)(RGBcoarse[B]),
        (uint8_t)(RGBcoarse[R]), (uint8_t)(RGBcoarse[G]), (uint8_t)(RGBcoarse[B]),
        (uint8_t)(RGBfine[R]),(uint8_t)(RGBfine[G]),(uint8_t)(RGBfine[B]),
        (uint8_t)(RGBfine[R]),(uint8_t)(RGBfine[G]),(uint8_t)(RGBfine[B]) };

}

// DMX_vec LEDFixture::buffer_pix(){
//     vector<uint8_t> data;
//     data.resize(3*NUM_PIX); // resize the vector to hold every subpixel data
    
//     for (int i = 0; i<3*NUM_PIX; i+=3){
//         data[i] =   this->RGBout[R] >> 4;
//         data[i+1] = this->RGBout[G] >> 4;
//         data[i+2] = this->RGBout[B] >> 4;
//     }

//     return data;
// }

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####                 #   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     #               ##   
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #                    # #   
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####     #####       #   
####### #   # #  #  #     # #######    #     #  #     # #   # #       #                #   
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     #                #   
#     # #     # ### #     # #     #    #    ### ####### #     #  #####               ##### 
*/
// Animation initializer
void LEDAnimation1::init(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    BaseAnimation::init();
    for (int_vec::iterator per_it=periods_ms.begin(); per_it!=periods_ms.end(); per_it++){
        (*per_it) = 1000 * rand_min_max(MIN_T, MAX_T);
    }
}
// does nothing
/** Computes the RGB values to send to the led display based on : */
void LEDAnimation1::new_frame(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    int backgd_color[3];

    backgd_color[R] = (backgd_RGB_minmax[0] + backgd_RGB_minmax[1]) / 2 + (backgd_RGB_minmax[1] - backgd_RGB_minmax[0]) / 4 * (sin(2*M_PI*t_ms / periods_ms[0]) + sin(2*M_PI*t_ms / periods_ms[1]));
    backgd_color[G] = (backgd_RGB_minmax[2] + backgd_RGB_minmax[3]) / 2 + (backgd_RGB_minmax[3] - backgd_RGB_minmax[2]) / 4 * (sin(2*M_PI*t_ms / periods_ms[2]) - sin(2*M_PI*t_ms / periods_ms[3]));
    backgd_color[B] = (backgd_RGB_minmax[4] + backgd_RGB_minmax[5]) / 2 + (backgd_RGB_minmax[5] - backgd_RGB_minmax[4]) / 4 * (sin(2*M_PI*t_ms / periods_ms[4]) - sin(2*M_PI*t_ms / periods_ms[5]));

    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    if (param_activate_flash && auto_activate_flash)
    {
        fixture->RGBout[R] = (1-pow(coef, 0.2)) * backgd_color[R] + coef * flash_RGB[R];
        fixture->RGBout[G] = (1-pow(coef, 0.2)) * backgd_color[G] + coef * flash_RGB[G];
        fixture->RGBout[B] = (1-pow(coef, 0.2)) * backgd_color[B] + coef * flash_RGB[B];
    }
    else
    {
        fixture->RGBout[R] = backgd_color[R];
        fixture->RGBout[G] = backgd_color[G];
        fixture->RGBout[B] = backgd_color[B];
    }
    // log(1, fcn::vec_to_str(this->fixture->RGBout, '\t'));
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
DMX_vec LEDFixture::RGB(simpleColor c, int intensity){
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
            temp = fcn::RGB_norm(DMX_vec{255,63,0});
            break;
        case orange:
            temp = fcn::RGB_norm(DMX_vec{255,20,0});
            break;
        case sodium:
            temp = fcn::RGB_norm(DMX_vec{255,9,0});
            break;
        case cyan:
            ref_int = 90;
            temp = fcn::RGB_norm(DMX_vec{0,153,255});
            break;
        case purple:
            ref_int = 200;
            temp = fcn::RGB_norm(DMX_vec{139,0,255});
            break;    
        case magenta:
            ref_int = 220;
            temp = fcn::RGB_norm(DMX_vec{255,0,186});
            break;
        case pink:
            ref_int = 240;
            temp = fcn::RGB_norm(DMX_vec{255,0,71});
            break;
        case w_white:
            temp = fcn::RGB_norm(DMX_vec{255,78,26});
            break;
        case gold:
            temp = fcn::RGB_norm(DMX_vec{255,37,4});
            break;
        default:
            temp = fcn::RGB_norm(DMX_vec{0,0,0});
            break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity==-1 ? -1 : (int)ref_int * intensity/255.0);
}