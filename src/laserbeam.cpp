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

/*
  #          ######                          ######                             
 ##          #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
# #          #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
  #          ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
  #   ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
  #   ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
##### ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
*/

  

/*
 #####            #                                          ######  #######    #    #######
#     #          # #   #    #   ##   #       ####   ####     #     # #         # #      #   
      #         #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #   
 #####         #     # # #  # #    # #      #    # #         ######  #####   #     #    #   
#       ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #   
#       ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #   
####### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #   
*/


void LaserBeamAnimation1::init(){
    BaseAnimation::init();
}
void LaserBeamAnimation1::init(const color_vec& palette){
    // AUTOCOLOR init
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
    //STANDARD init
    LaserBeamAnimation1::init();
}

void LaserBeamAnimation1::new_frame(){
    BaseAnimation::new_frame();
    
    // local variables for readability
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    // enable / disable based on music status
    bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/;
    

    // precompute pixel values
    pixel backgd_RGB = this->fixture->RGB(back_color, 20 * this->master/255.0);
    pixel flash_RGB = this->fixture->RGB(flash_color, this->master);
    pixel final_mix_RGB = this->fixture->RGB(black);

    // Compute intensity vaue based on time elapsed since last beat
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);

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

    // set each units color
    this->fixture->pixel = final_mix_RGB;
}
