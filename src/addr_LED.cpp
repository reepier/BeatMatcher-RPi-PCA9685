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
}

DMX_vec AddressableLED::buffer(){
    // spits out an ordered vector containing every subpixel value (0-256)
    DMX_vec data(3*NUM_PIX);
    
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
        case white:
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





/*
   #    #     # ### #     #    #    ####### ### ####### #     #              #   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    #             ##   
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   #            # #   
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #   #####      #   
####### #   # #  #  #     # #######    #     #  #     # #   # #              #   
#     # #    ##  #  #     # #     #    #     #  #     # #    ##              #   
#     # #     # ### #     # #     #    #    ### ####### #     #            ####*/
