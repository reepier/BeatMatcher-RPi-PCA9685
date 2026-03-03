/** TEMPALTE FILE for a new fixture module*/
#include "laserbeam.h"

#define FILL this->animations.push_back(new LaserBeamAnimation0(this, black,  " - ", "LB.0", backer, 0, 0, int_vec{}));
using namespace std;

LaserBeam laserbeam(RGB_500_Fat,2,    19, 6, "BEAM", 7, 255, 140);
// LaserBeam laserbeam(RGB_1W,         19, 3, "BEAM", 7, 255, 140);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */

void LaserBeam::init(){
    this->animations.push_back(new LaserBeamAnimation0(this, black,  " - ", "LB.0", backer, 0, 0, int_vec{}));
    this->animations.push_back(new LaserBeamAnimation0(this, "Couleur", "LB.0.1",   backer, 0, 255, int_vec{}));
    FILL
    FILL

    this->animations.push_back(new LaserBeamAnimation1(this, gaussian,  3000, 800, "Bulles lent", "LB.1",       any, 1, 255, int_vec{1,2,3}));
    this->animations.push_back(new LaserBeamAnimation1(this, gaussian,  1000, 400, "Bulles rapide", "LB.1",     any, 1, 255, int_vec{1,2,3}));
    FILL
    FILL
    this->animations.push_back(new LaserBeamAnimation1(this, square,  3000, 800, "Chaser lent", "LB.1",       any, 1, 255, int_vec{1,2,3}));
    this->animations.push_back(new LaserBeamAnimation1(this, square,  1000, 400, "Chaser rapide", "LB.1",     any, 1, 255, int_vec{1,2,3}));

    this->animations.push_back(new LaserBeamAnimation1(this, expdecay,  3000, 800, "Décharge lent", "LB.1",     any, 1, 255, int_vec{1,2,3}));
    this->animations.push_back(new LaserBeamAnimation1(this, expdecay,  800, 200, "Décharge rapide", "LB.1",    any, 1, 255, int_vec{1,2,3}));
    FILL
    FILL
    FILL
    FILL


    this->animations.push_back(new LaserBeamAnimation1(this, square,    1500, 1000/FRATE,   "Strobe lent", "LB.1",      any,   1, 255, int_vec{1,2,3}));
    this->animations.push_back(new LaserBeamAnimation1(this, square,    500, 1000/FRATE,    "Strobe rapide", "LB.1",    any, 1, 255, int_vec{1,2,3}));
    FILL
    FILL
    FILL
    FILL

    this->animations.push_back(new LaserBeamAnimation2(this, 0.5, "Beat",    "LB.2", leader, 255, 1, int_vec{3}));
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL

    this->activate_none();

    this->dump_animations("LaserBeam");
}

DMX_vec LaserBeam::buffer(){
    DMX_vec data(this->nCH);

    double final_master = animator.master/255.0 * this->master/255.0;

    int i_data=0;
    for (int i_pix=0; i_pix<this->pixels.size(); i_pix++){
        for (int j_subpix=0; j_subpix<this->pixels[i_pix].size(); j_subpix++){
            data[i_data++] = 255 - final_master * this->pixels[i_pix][j_subpix]; 
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

DMX_vec RGB_1W_RGB(simpleColor c, int intensity){
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

DMX_vec RGB_500_Fat_RGBW(simpleColor c, int intensity){
    DMX_vec temp;
    // store in vector temp the color vector of norm 255
    switch (c){ //TODO : remove ref_int and simply pass base lumo in RGB_norm argument
        case black      :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        case red        :                   temp = fcn::RGB_norm(DMX_vec{255,0,0});     break;
        case green      :                   temp = fcn::RGB_norm(DMX_vec{0,255,0});     break;
        case blue       :                   temp = fcn::RGB_norm(DMX_vec{0,0,255});     break;
        case yellow     :                   temp = fcn::RGB_norm(DMX_vec{255,105,0});    break;
        case orange     :                   temp = fcn::RGB_norm(DMX_vec{255,35,0});    break;
        case sodium     :                   temp = fcn::RGB_norm(DMX_vec{255,16,0});    break;
        case cyan       :                   temp = fcn::RGB_norm(DMX_vec{0,160,255});   break;
        case purple     :                   temp = fcn::RGB_norm(DMX_vec{160,0,255});   break;    
        case magenta    :                   temp = fcn::RGB_norm(DMX_vec{255,0,255});   break;
        case pink       :                   temp = fcn::RGB_norm(DMX_vec{255,0,86});    break;
        case w_white    :                   temp = fcn::RGB_norm(DMX_vec{255,130,65}); break;
        case c_white    :                   temp = fcn::RGB_norm(DMX_vec{255,200,180}); break;
        case gold       :                   temp = fcn::RGB_norm(DMX_vec{255,80,10});    break;
        case light_red      :               temp = fcn::RGB_norm(DMX_vec{255,40,15});   break;
        case light_cyan     :               temp = fcn::RGB_norm(DMX_vec{120,235,255});   break;
        case light_blue     :               temp = fcn::RGB_norm(DMX_vec{70,80,255});   break;
        case light_purple   :               temp = fcn::RGB_norm(DMX_vec{206,89,255});   break;
        case light_magenta  :               temp = fcn::RGB_norm(DMX_vec{255,75,231});   break;
        case light_pink     :               temp = fcn::RGB_norm(DMX_vec{255,58,114});   break;
        case light_green    :               temp = fcn::RGB_norm(DMX_vec{50,255,40});   break;
        default         :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity);

}


DMX_vec LaserBeam::RGB(simpleColor c, int intensity){
    switch (this->type){
        case RGB_1W :       return RGB_1W_RGB(c, intensity);break;
        case RGB_500_Fat :  return RGB_500_Fat_RGBW(c, intensity);break;
        
        default :    break;
    }

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
        default:    this->color = *(palette.begin());   break;
        }
    }

    //Standard init()
    LaserBeamAnimation0::init();
}

void LaserBeamAnimation0::new_frame() {
    // Col1 Intensity 
    int current_c1_intensity = map3_param(this->fixture->param8, 0.0, 255.0, 255.0);
    if (this->fixture->param8==1.0) current_c1_intensity = -1; // -1 means maxxing out fixture's RGB values

    for(pixel_vec::iterator pix = this->fixture->pixels.begin(); pix!=this->fixture->pixels.end(); pix++){
        *(pix) = this->fixture->RGB(this->color, current_c1_intensity);
    }
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

    const int n_unit = this->fixture->pixels.size();             // set the number of laser pixels to control
    this->flashes = vector<flash_vec>(n_unit, flash_vec(2));  // resize pixel vector

    // initialize flash vector
    for (int i_unit=0; i_unit<n_unit; i_unit++){
        flashes[i_unit][i_next].time = rand_min_max(0.0, (double)n_unit);
        flashes[i_unit][i_prev].time = -1*rand_min_max(0.0, (double)n_unit);
        flashes[i_unit][i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_unit][i_prev].color = black;
    }
}
void LaserBeamAnimation1::init(const color_vec& palette){
    // AUTOCOLOR init : assign flash colors & back color based on passed color palette :
    const int palette_size = palette.size();
    switch (palette_size)
    {
    case 0:
        this->flash_colors = color_vec{black}, this->back_color = black;            break;
    case 1:
        this->flash_colors = color_vec{palette[0]}, this->back_color = black;  break;
    case 2: 
        this->flash_colors = color_vec{palette[0]}, this->back_color = palette[1];  break;
    default:
        flash_colors = color_vec{fcn::random_pick(palette)},    back_color = fcn::random_pick(palette);     break;
    }

    //call STANDARD init()
    LaserBeamAnimation1::init();
}

void LaserBeamAnimation1::new_frame(){
    BaseAnimation::new_frame();

//update external parameters :
    // Shape
    const vector<Shape> shapes = {gaussian, gaussian2, square, expdecay};
    this->current_param_shape_i       = clamp(  map_param(this->fixture->param5,  0, (int)shapes.size()),
                                                0,
                                                (int)shapes.size()-1);
    this->current_param_shape       = shapes[current_param_shape_i];

    if (this->frame_cpt==1){    // If animation just started 
      this->current_shape = this->preset_shape; // use preset shape
      /*do nothing*/
    }else if(this->previous_param_shape != this->current_param_shape){  //else if external shape changes
      this->current_shape = this->current_param_shape;                          // use external shape
    }
    this->previous_param_shape = this->current_param_shape;               // update param_shape memory

    // Overall Speed : mean interval between two bursts
    const int current_interval    = clamp(      map3_param(this->fixture->param2, 5*(double)this->preset_interval, (double)this->preset_interval, (double)this->preset_interval/5 ),
                                                1000.0/FRATE,
                                                30000.0);
    const double speed_ratio = (double)preset_interval/current_interval;  // speed multiplicator --> =1 means using preset speed, > 1 means faster, < 1 means slower
    // Burst length (param Duration)
    // speed_ratio multiplicator maintains constant luminosity when speeding up animtion (buy reducing burst duration by as much as overall speed increased)
    const double speed_adjusted_duration = preset_duration/speed_ratio;
    const int current_duration      = clamp(    map3_param(this->fixture->param1, speed_adjusted_duration/5, speed_adjusted_duration, 5*speed_adjusted_duration),
                                                1000.0/FRATE,
                                                30000.0);

    // Col1 Intensity 
    int current_c1_intensity = map3_param(this->fixture->param8, 0.0, 255.0, 255.0);
    if (this->fixture->param8==1.0) current_c1_intensity = -1; // -1 means maxxing out fixture's RGB values
    // Col2 Intensity 
    const int current_bkg_intensity = map3_param(this->fixture->param3, 0.0, (double)RED_BKG_INTENSITY_REF, 255.0);


    int n_unit = this->flashes.size();   // for readability
    
    // update internal timescale ("dt" in inversely proportionnal);
    this->t_unit += 1000.0/FRATE/current_interval;

  // for each laser "i" of the module
  for (int i_unit=0; i_unit < n_unit; i_unit++){
        // auto current_spot = this->fixture->spots[i_unit];           // for readability
        auto &current_unit_next_flash = flashes[i_unit][i_next];       // for readability
        auto &current_unit_prev_flash = flashes[i_unit][i_prev];       // for readability
        double &t_next = current_unit_next_flash.time;
        double &t_prev = current_unit_prev_flash.time;
        simpleColor &c_next = current_unit_next_flash.color;
        simpleColor &c_prev = current_unit_prev_flash.color;

        // log(4, __FILE__, " ", __LINE__, " ",__func__, " Mark2 , ", fcn::num_to_str(i_spot));

        const pixel ani_backgd_RGB = fixture->RGB(back_color, current_bkg_intensity);
        
        // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
        double flash_intensity; // 0 by default
        // when the flash passes, compute the next flash timestamp and update prev flash
        if (t_unit > t_next){
            
            t_prev = t_next;
            t_next = t_next + rand_min_max(0.0, 2.0);
            c_prev = c_next;
            c_next = fcn::random_pick(this->flash_colors);
            
        }
        
        switch (this->preset_shape){
            case square : flash_intensity = fcn::square((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::square((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
                break;
            case gaussian : flash_intensity = fcn::gaussian((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::gaussian((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
                break;
            case gaussian2 : flash_intensity = fcn::gaussian2((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::gaussian2((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
                break;
            case expdecay : flash_intensity = fcn::exp_decay((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0);
                break;
            default : flash_intensity = fcn::gaussian((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::gaussian((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
                break;
        }

        DMX_vec frame_flash_RGB = (t_unit-t_prev > t_next-t_unit) ? fixture->RGB(c_next, current_c1_intensity) : this->fixture->RGB(c_prev, current_c1_intensity);
        DMX_vec final_RGB(3, 0);
        final_RGB[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[R] + flash_intensity * frame_flash_RGB[R]  ),0),255); 
        final_RGB[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[G] + flash_intensity * frame_flash_RGB[G]  ),0),255);
        final_RGB[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[B] + flash_intensity * frame_flash_RGB[B]  ),0),255);

        //masterization
        for (auto subpix : final_RGB){
            subpix = subpix * this->master/255.0;
        }

        this->fixture->pixels[i_unit] = final_RGB;
    }
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
    case 1:     this->flash_color=palette[0];   this->back_color=black;
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

    //update external parameters :
    // flash duration (param Duration)
    const int current_fade_rate_ms    = map3_param(this->fixture->param1, 1000.0/FRATE, (double)this->preset_duration, 1000.0);
    // Col1 Intensity 
    int current_c1_intensity = map3_param(this->fixture->param8, 0.0, 255.0, 255.0);
    if (this->fixture->param8==1.0) current_c1_intensity = -1; // -1 means maxxing out fixture's RGB values
    // Col2 Intensity 
    const int current_bkg_intensity = map3_param(this->fixture->param3, 0.0, (double)RED_BKG_INTENSITY_REF, 255.0);
    // Ratio 
    const double current_ratio        = clamp(  map3_param(this->fixture->param4, 0.0, this->preset_density, 1.5),
                                                0.0,
                                                1.0);

    // local variables for readability
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size(); 
    int n_unit_on = max(1, (int)(current_ratio * n_unit));

      // for each new beat, sort segments in random order
    if (sampler.new_beat){
        units_index = fcn::randomized_vector(units_index);
    }

    // enable / disable based on music status
    bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/;
    
    // Compute intensity value based on time elapsed since last beat
    double coef = fcn::exp_decay(t_ms, t_last_beat_ms, current_fade_rate_ms, 0.0, 1.0);

    // set each laser intensity
    for (int i_unit=0; i_unit<n_unit; i_unit++){

        pixel backgd_RGB    = this->fixture->RGB(back_color, current_bkg_intensity);
        pixel flash_RGB     = this->fixture->RGB(flash_color, current_c1_intensity);
        pixel final_RGB     = this->fixture->RGB(black); //initialization before calculations

        if (i_unit<n_unit_on){
            for(auto i_subpix = 0; i_subpix<final_RGB.size(); i_subpix++){
                final_RGB[i_subpix] = coef * flash_RGB[i_subpix] + (1-pow(coef, 0.2)) * backgd_RGB[i_subpix];
                final_RGB[i_subpix] = final_RGB[i_subpix] * this->master/255.0;
            }
        }else{
            final_RGB = backgd_RGB;
        }

        this->fixture->pixels[units_index[i_unit]] = final_RGB;
        
    }
}
