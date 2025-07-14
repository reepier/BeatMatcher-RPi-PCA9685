/** TEMPALTE FILE for a new fixture module*/
#include "laserbeam.h"


using namespace std;

LaserBeam laserbeam(12, 3, "BEAM", 1, 255);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */

void LaserBeam::init(){
    this->animations.push_back(new LaserBeamAnimation0(this, black,  "", "LB.0", backer, 1, 0));
    this->animations.push_back(new LaserBeamAnimation0(this, "Couleur", "LB.0.1", backer, 1, 255));


    this->animations.push_back(new LaserBeamAnimation1(this, gaussian,  3000, 800, "Test Bubbles", "LB.1", any, 1, 255));
    this->animations.push_back(new LaserBeamAnimation1(this, square,    3000, 800, "Test Square", "LB.1", any, 1, 255));
    this->animations.push_back(new LaserBeamAnimation1(this, expdecay,  3000, 800, "Test Flash", "LB.1", any, 1, 255));

    this->animations.push_back(new LaserBeamAnimation1(this, square,    1000, 1000/FRATE, "Slow Strobe", "LB.1", any, 1, 255));


    this->animations.push_back(new LaserBeamAnimation2(this, "Beat",    "LB.2", leader, true, 255));

    this->activate_none();
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
        case yellow     :                   temp = fcn::RGB_norm(DMX_vec{255,230,0});    break;
        case orange     :                   temp = fcn::RGB_norm(DMX_vec{255,50,0});    break;
        case sodium     :                   temp = fcn::RGB_norm(DMX_vec{255,25,0});    break;
        case cyan       :                   temp = fcn::RGB_norm(DMX_vec{0,255,100});   break;
        case purple     :                   temp = fcn::RGB_norm(DMX_vec{100,0,255});   break;    
        case magenta    :                   temp = fcn::RGB_norm(DMX_vec{180,0,255});   break;
        case pink       :                   temp = fcn::RGB_norm(DMX_vec{255,0,40});    break;
        case w_white    :                   temp = fcn::RGB_norm(DMX_vec{140,255,6}); break;
        case c_white    :                   temp = fcn::RGB_norm(DMX_vec{74,255,36}); break;
        case gold       :                   temp = fcn::RGB_norm(DMX_vec{255,100,0});    break;
        case light_red      :               temp = fcn::RGB_norm(DMX_vec{255,155,4});   break;
        case light_cyan     :               temp = fcn::RGB_norm(DMX_vec{40,255,50});   break;
        case light_blue     :               temp = fcn::RGB_norm(DMX_vec{30,255,255});   break;
        case light_purple   :               temp = fcn::RGB_norm(DMX_vec{135,255,255});   break;
        case light_magenta  :               temp = fcn::RGB_norm(DMX_vec{255,255,206});   break;
        case light_pink     :               temp = fcn::RGB_norm(DMX_vec{255,200,60});   break;
        case light_green    :               temp = fcn::RGB_norm(DMX_vec{40,255,10});   break;
        default         :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity);

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
  ###          #######                 
 #   #         #       # #    # ###### 
#     #        #       #  #  #  #      
#     #        #####   #   ##   #####  
#     # ###    #       #   ##   #      
 #   #  ###    #       #  #  #  #      
  ###   ###    #       # #    # ##### */

void LaserBeamAnimation0::init() {
    BaseAnimation::init();
}
void LaserBeamAnimation0::init(const color_vec& palette) {
    if (this->autocolor){
        switch (palette.size())
        {
        case 0:     this->color = black;        break;
        case 1:     this->color = palette[0];   break;
        default:    this->color = *(palette.end()-1);   break;
        }
    }

    //Standard init()
    LaserBeamAnimation0::init();
}

void LaserBeamAnimation0::new_frame() {
    this->fixture->pixel = this->fixture->RGB(this->color, -1);
}


/*
  #          ######                          ######                             
 ##          #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
# #          #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
  #          ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
  #   ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
  #   ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
##### ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
*/

void LaserBeamAnimation1::init(){
    log(4, __FILE__, " ", __LINE__, " ",__func__, " ", this->fixture->name, " ", this->id);

    BaseAnimation::init();

    this->flashes = flash_vec(2);

        flashes[i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2); 
        flashes[i_prev].time = 0;
        flashes[i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_prev].color = black;
}
void LaserBeamAnimation1::init(const color_vec& palette){
    // AUTOCOLOR init : assign flash colors & back color based on passed color palette :
    const int palette_size = palette.size();
    switch (palette_size)
    {
    case 0:
        this->flash_colors = color_vec{black}, this->back_color = black;            break;
    case 1:
        this->flash_colors = color_vec{palette[0]}, this->back_color = palette[0];  break;
    case 2: 
        this->flash_colors = color_vec{palette[0]}, this->back_color = palette[1];  break;
    default:
        flash_colors = color_vec{fcn::random_pick(palette)},    back_color = fcn::random_pick(palette);     break;
    }

    //call STANDARD init()
    LaserBeamAnimation1::init();
}

void LaserBeamAnimation1::new_frame(){
    log(4, __FILE__, " ", __LINE__, " ",__func__);

    BaseAnimation::new_frame();

    long t = frame.t_current_ms;         // for readability
    int n_unit = this->flashes.size();   // for readability
    
   

        // auto current_spot = this->fixture->spots[i_unit];           // for readability
        auto &next_flash = flashes[i_next];       // for readability
        auto &prev_flash = flashes[i_prev];       // for readability
        time_t &t_next = next_flash.time;
        time_t &t_prev = prev_flash.time;
        simpleColor &c_next = next_flash.color;
        simpleColor &c_prev = prev_flash.color;

        // log(4, __FILE__, " ", __LINE__, " ",__func__, " Mark2 , ", fcn::num_to_str(i_spot));

        const pixel ani_backgd_RGB = fixture->RGB(back_color, 50);
        
        // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
            double flash_intensity; // 0 by default
            if (flash_activation){
                // when the flash passes, compute the next flash timestamp and update prev flash
                if (t > t_next){
                    
                    t_prev = t_next;
                    t_next = t_next + rand_min_max(this->flash_len, 2*this->rand_const_ms);
                    c_prev = c_next;
                    c_next = fcn::random_pick(this->flash_colors);
                    
                }
                
                // flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                switch (this->flash_shape){
                    case square :
                        flash_intensity = fcn::square(t, t_prev, flash_len, 0.0,1.0) + fcn::square(t, t_next, flash_len, 0.0,1.0);
                        break;
                    case gaussian :
                        flash_intensity = fcn::gaussian(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian(t, t_next, flash_len, 0.0,1.0);
                        break;
                    case gaussian2 :
                        flash_intensity = fcn::gaussian2(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian2(t, t_next, flash_len, 0.0,1.0);
                        break;
                    case expdecay :
                        flash_intensity = fcn::exp_decay(t, t_prev, flash_len, 0.0,1.0);
                        break;
                    default :
                        flash_intensity = fcn::gaussian(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian(t, t_next, flash_len, 0.0,1.0);
                        break;
                }

            }else{
                flash_intensity = 0.0;
            }

            DMX_vec frame_flash_RGB = (t-t_prev > t_next-t) ? fixture->RGB(c_next, -1) : this->fixture->RGB(c_prev, -1);
            DMX_vec final_RGB(3, 0);
            final_RGB[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[R] + flash_intensity * frame_flash_RGB[R]  ),0),255); 
            final_RGB[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[G] + flash_intensity * frame_flash_RGB[G]  ),0),255);
            final_RGB[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[B] + flash_intensity * frame_flash_RGB[B]  ),0),255);

            //masterization
            for (auto subpix : final_RGB){
                subpix = subpix * this->master/255.0;
            }

            this->fixture->pixel = final_RGB;
}

/*
 #####            #                                          ######  #######    #    #######
#     #          # #   #    #   ##   #       ####   ####     #     # #         # #      #   
      #         #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #   
 #####         #     # # #  # #    # #      #    # #         ######  #####   #     #    #   
#       ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #   
#       ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #   
####### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #   
*/


void LaserBeamAnimation2::init(){
    BaseAnimation::init();
}
void LaserBeamAnimation2::init(const color_vec& palette){
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
    LaserBeamAnimation2::init();
}

void LaserBeamAnimation2::new_frame(){
    BaseAnimation::new_frame();
    
    // local variables for readability
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    // enable / disable based on music status
    bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/;
    

    // precompute pixel values
    pixel backgd_RGB = this->fixture->RGB(back_color, 20);
    pixel flash_RGB = this->fixture->RGB(flash_color, -1);
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

    // masterization (animation->master)
    for (auto subpix : final_mix_RGB){
        subpix = subpix * this->master/255.0;
    }

    
    // set each units color
    this->fixture->pixel = final_mix_RGB;

}
