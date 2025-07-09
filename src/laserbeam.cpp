/** TEMPALTE FILE for a new fixture module*/
#include "laserbeam.h"


using namespace std;

LaserBeam laserbeam(13, 3, "BEAM", 1, 255);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */

void LaserBeam::init(){

}

DMX_vec LaserBeam::buffer(){
    return DMX_vec{ (uint8_t)(this->pixel[R] *this->master/255.0),
                    (uint8_t)(this->pixel[G] *this->master/255.0),
                    (uint8_t)(this->pixel[B] *this->master/255.0)};
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

DMX_vec LaserBeam::RGB(simpleColor c, int intensity){
    DMX_vec temp;
    // store in vector temp the color vector of norm 255
    switch (c){ //TODO : remove ref_int and simply pass base lumo in RGB_norm argument
        case black      :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        case red        :                   temp = fcn::RGB_norm(DMX_vec{255,0,0});     break;
        case green      :                   temp = fcn::RGB_norm(DMX_vec{0,255,0});     break;
        case blue       :                   temp = fcn::RGB_norm(DMX_vec{0,0,255});     break;
        case yellow     :                   temp = fcn::RGB_norm(DMX_vec{255,87,0});    break;
        case orange     :                   temp = fcn::RGB_norm(DMX_vec{255,35,0});    break;
        case sodium     :                   temp = fcn::RGB_norm(DMX_vec{255,16,0});    break;
        case cyan       :                   temp = fcn::RGB_norm(DMX_vec{0,184,255});   break;
        case purple     :                   temp = fcn::RGB_norm(DMX_vec{180,0,255});   break;    
        case magenta    :                   temp = fcn::RGB_norm(DMX_vec{255,0,197});   break;
        case pink       :                   temp = fcn::RGB_norm(DMX_vec{255,0,86});    break;
        case w_white    :                   temp = fcn::RGB_norm(DMX_vec{255,173,102}); break;
        case c_white    :                   temp = fcn::RGB_norm(DMX_vec{255,255,255}); break;
        case gold       :                   temp = fcn::RGB_norm(DMX_vec{255,50,3});    break;
        case light_red      :               temp = fcn::RGB_norm(DMX_vec{255,50,18});   break;
        case light_cyan     :               temp = fcn::RGB_norm(DMX_vec{70,200,255});   break;
        case light_blue     :               temp = fcn::RGB_norm(DMX_vec{52,74,255});   break;
        case light_purple   :               temp = fcn::RGB_norm(DMX_vec{206,89,255});   break;
        case light_magenta  :               temp = fcn::RGB_norm(DMX_vec{255,75,231});   break;
        case light_pink     :               temp = fcn::RGB_norm(DMX_vec{255,58,114});   break;
        case light_green    :               temp = fcn::RGB_norm(DMX_vec{50,255,50});   break;
        default         :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity==-1 ? -1 : intensity/255.0);

}


/*
   #                                                 
  # #   #    # # #    #   ##   ##### #  ####  #    # 
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
#     # # #  # # # ## # #    #   #   # #    # # #  # 
####### #  # # # #    # ######   #   # #    # #  # # 
#     # #   ## # #    # #    #   #   # #    # #   ## 
#     # #    # # #    # #    #   #   #  ####  #    # */

/*TODO proposition : for every animation that requires it, define functions such as get_flash_color(const color_vec& palette)
 and get_back_color(const color_vec& palette) that parse the palette (passed as argument) and compose it with internal
  parameters "(un)authorized_flash_color", (un)authorized_back_color. This could yield the perfect trade-off between the master palette 
  and each animation's own limitations (i.e. rendering complex colors at low intensity) */
void FixtureAnimation1::init(){
    BaseAnimation::init();
}

void FixtureAnimation1::init(const color_vec& palette){
    //AUTOCOLOR settings
    /* set animation colors based on color palette passed as argument*/
    
    // call standard init
    FixtureAnimation1::init();
}

void FixtureAnimation1::new_frame(){
    BaseAnimation::new_frame();
    // update fixture channels at every computational step
    
}