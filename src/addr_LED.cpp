#include <algorithm>

using namespace std;

#include "addr_LED.h"

AddressableLED addr_led(1, 0, 3*NUM_PIX, "LEDs", 1, 180);

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

    //AUTOCOLOR with Animation type 1 : Analog Beat all pixels ()Beatmatcher original animation)------------------------------
    animations.push_back(new AddrLEDAnimation1(this, bar, 1, "Analog Beat", "PIX.6.1", leader, true, 255));     

    //AUTOCOLOR with Animation type 1 : Analog Beat with random fragments ----------------------------------------------------
    animations.push_back(new AddrLEDAnimation1(this, bar, 0.7,  "Bar Analog Beat",      "PIX.6.2.1", leader, true, 255));     
    animations.push_back(new AddrLEDAnimation1(this, seg, 0.7,  "Segments Analog Beat", "PIX.6.2.2", leader, true, 255));    //TODO Fix this one 
    animations.push_back(new AddrLEDAnimation1(this, pix, 0.7,  "Pixels Analog Beat",   "PIX.6.2.3", leader, true, 255));     
    
    //AUTOCOLOR with Animation type 2 : Digital Beat -------------------------------------------------------------------------
    animations.push_back(new AddrLEDAnimation2(this, bar, "Bar Digital Beat (autocolor)",       "PIX.7.1", leader, true, 255));     
    animations.push_back(new AddrLEDAnimation2(this, seg, "Segments Digital Beat (autocolor)",  "PIX.7.2", leader, true, 255));     
    animations.push_back(new AddrLEDAnimation2(this, pix, "Pixel Digital Beat (autocolor)",     "PIX.7.3", leader, true, 255));     
    
    //AUTOCOLOR with Animation type 4 : Random Bursts----------------------------------------------------------------------------------------
    //Slow & long bubbles
    animations.push_back(new AddrLEDAnimation4(this, gaussian, bar, 400, 1500, "Slow Bubbles", "PIX.8.1", backer, 1, 255));
    // Fast & short Bubbles
    animations.push_back(new AddrLEDAnimation4(this, gaussian, bar, 200, 600, "Fast Bubbles ", "PIX.8.2", any, 1, 255));
    // Slow Random Chaser
    animations.push_back(new AddrLEDAnimation4(this, square,   bar, 300, 1500, "Slow Chaser",  "PIX.8.3", backer, 1, 255));
    // Fast Random Chaser 
    animations.push_back(new AddrLEDAnimation4(this, square,   bar, 200, 600, "Fast Chaser",  "PIX.8.4", any, 1, 255));
    // Fast Random Strobe
    animations.push_back(new AddrLEDAnimation4(this, square, bar, 50, 1000/FRATE, "Fast Random Strobe", "PIX.8.5", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, square, bar, 50, 1000/FRATE, "Mid  Random Strobe", "PIX.8.5", any, 1, 255));
    // Decaying Flash
    animations.push_back(new AddrLEDAnimation4(this, square, bar, 150, 1000/FRATE, "Slow Strobe", "PIX.8.6", any, 1, 255));


    this->activate_none();
}

// spits out an ordered vector containing every subpixel value (0-256)
DMX_vec AddressableLED::buffer(){
    DMX_vec data(NUM_SUBPIX);
    
    double final_master =  this->active_animation!=nullptr ? 
                                    this->master/255.0 * this->active_animation->master/255.0
                                    : 1.0;  // from 0.0 to 1.0

    int i_data = 0;
    for (auto pix : this->pixels){        
        for (auto sub_pix : pix){
            data[i_data++] = (uint8_t) (final_master * sub_pix);
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
    switch (c){ //TODO : remove ref_int and simply pass base lumo in RGB_norm argument
        case black      :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        case red        :                   temp = fcn::RGB_norm(DMX_vec{255,0,0});     break;
        case green      :ref_int = 100,     temp = fcn::RGB_norm(DMX_vec{0,255,0});     break;
        case blue       :ref_int = 220,     temp = fcn::RGB_norm(DMX_vec{0,0,255});     break;
        case yellow     :ref_int = 200,     temp = fcn::RGB_norm(DMX_vec{255,87,0});    break;
        case orange     :                   temp = fcn::RGB_norm(DMX_vec{255,35,0});    break;
        case sodium     :                   temp = fcn::RGB_norm(DMX_vec{255,16,0});    break;
        case cyan       :ref_int = 150;     temp = fcn::RGB_norm(DMX_vec{0,184,255});   break;
        case purple     :                   temp = fcn::RGB_norm(DMX_vec{180,0,255});   break;    
        case magenta    :                   temp = fcn::RGB_norm(DMX_vec{255,0,197});   break;
        case pink       :                   temp = fcn::RGB_norm(DMX_vec{255,0,86});    break;
        case w_white    :                   temp = fcn::RGB_norm(DMX_vec{255,173,102}); break;
        case c_white    :                   temp = fcn::RGB_norm(DMX_vec{255,255,255}); break;
        case gold       :                   temp = fcn::RGB_norm(DMX_vec{255,50,3});    break;
        case light_red      :               temp = fcn::RGB_norm(DMX_vec{255,50,18});   break;
        case light_cyan     :ref_int = 220; temp = fcn::RGB_norm(DMX_vec{70,200,255});   break;
        case light_blue     :               temp = fcn::RGB_norm(DMX_vec{52,74,255});   break;
        case light_purple   :               temp = fcn::RGB_norm(DMX_vec{206,89,255});   break;
        case light_magenta  :               temp = fcn::RGB_norm(DMX_vec{255,75,231});   break;
        case light_pink     :               temp = fcn::RGB_norm(DMX_vec{255,58,114});   break;
        case light_green    :ref_int = 180, temp = fcn::RGB_norm(DMX_vec{50,255,50});   break;
        default         :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity==-1 ? -1 : (int)ref_int * intensity/255.0);
}





/*
  #             #                                          ######  #######    #    #######
 ##            # #   #    #   ##   #       ####   ####     #     # #         # #      #   
# #           #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #   
  #          #     # # #  # #    # #      #    # #         ######  #####   #     #    #   
  #   ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #   
  #   ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #   
##### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #   
*/
void AddrLEDAnimation1::init(){
    BaseAnimation::init();
}
void AddrLEDAnimation1::init(const color_vec& palette){
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
    AddrLEDAnimation1::init();
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
    bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/;
    
    // for each new beat, sort segments in random order
    if (sampler.new_beat)
        units_index = fcn::randomized_vector(units_index);

    // precompute pixel values
    pixel backgd_RGB = this->fixture->RGB(back_color, 20);
    pixel flash_RGB = this->fixture->RGB(flash_color);
    pixel final_mix_RGB(3);

    // Compute intensity vaue based on time elapsed since last beat
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    // compute number of units flashing 
    int n_unit_on = density * n_unit;

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
 #####         ######                                    ######  #######    #    #######
#     #        #     # #  ####  # #####   ##   #         #     # #         # #      #   
      #        #     # # #    # #   #    #  #  #         #     # #        #   #     #   
 #####         #     # # #      #   #   #    # #         ######  #####   #     #    #   
#       ###    #     # # #  ### #   #   ###### #         #     # #       #######    #   
#       ###    #     # # #    # #   #   #    # #         #     # #       #     #    #   
####### ###    ######  #  ####  #   #   #    # ######    ######  ####### #     #    #   
*/
void AddrLEDAnimation2::init(){
    BaseAnimation::init();
}
void AddrLEDAnimation2::init(const color_vec& palette){
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
    AddrLEDAnimation2::init();
}

void AddrLEDAnimation2::new_frame(){
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size();
    pixel flash_RGB = this->fixture->RGB(this->flash_color);
    pixel backgd_RGB = this->fixture->RGB(this->back_color, 20);

    bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/; //TODO useless ?

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
 #####          #     #                        
#     #         ##    #  ####  #  ####  ###### 
      #         # #   # #    # # #      #      
 #####          #  #  # #    # #  ####  #####  
      # ###     #   # # #    # #      # #      
#     # ###     #    ## #    # # #    # #      
 #####  ###     #     #  ####  #  ####  ###### 
*/
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
#              ######                          ######                             
#    #         #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
#    #         #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
#    #         ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
####### ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
     #  ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
     #  ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
*/
void AddrLEDAnimation4::init(){
    log(4, __FILE__, " ", __LINE__, " ",__func__, " ", this->fixture->name, " ", this->id);

    BaseAnimation::init();
    
    const int n_unit = unit==bar ? NUM_BAR : (unit==seg ? NUM_SEG : (unit==pix ? NUM_PIX : 0));

    this->flashes = vector<flash_vec>(n_unit, flash_vec(2));

    for (int i_unit=0; i_unit<n_unit; i_unit++){
        flashes[i_unit][i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2*n_unit); 
        flashes[i_unit][i_prev].time = 0;
        flashes[i_unit][i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_unit][i_prev].color = black;
    }
}
void AddrLEDAnimation4::init(const color_vec& palette){
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
    AddrLEDAnimation4::init();
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

        const pixel ani_backgd_RGB = fixture->RGB(back_color, ADDRLED_ANI4_BkG_INTENSITY_LOW);
        
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


// /* 4 - HiVE*/
// void AddrLEDAnimation5::init() {BaseAnimation::init();
//     const auto num_group = groups_size.size();
    
//     for (int i_grp = 0; i_grp<num_group; i_grp++){
//         const auto group_size = groups_size[i_grp];
//         // for each group of led bar, initialize a vector of blots with a number of elements proportional to the number of bars in the group
//         this->blot_groups[i_grp] = blot_vec(    (int)(this->density_factor * group_size * 6)    );

//         // for each of the group's blot, initialize its widthn, position, speed & intensity 
//         for (auto blot : blot_groups[i_grp]) {
//             // position (pixels as a uint) is randomly picked along the length of the bars' group 
//             blot.position = rand_min_max(0, group_size * NUM_PIX_BAR);
//             //nothing else for now, all blots are created equal (see class definition)
//         }
//     }
// };

// void AddrLEDAnimation5::new_frame() {BaseAnimation::new_frame();
//     //update blot kinematics (position)

//     //compute each pixel's value :
//     //for each group of bars :
//     auto pix_parser = this->fixture->pixels.begin();

//     for (auto i_grp = 0; i_grp < groups_size.size(); i_grp++){
//         const int num_bar_group = groups_size[i_grp];
//         const int num_pix_group = num_bar_group * NUM_PIX_BAR;
//         auto blots = this->blot_groups[i_grp];
        
//         //for each pixel in the group
//         int pix_position = 0;
//         for (auto pix = pix_parser; pix != pix_parser + num_pix_group; pix ++){
//             // find the closest blot (in terms of position)
//             auto closest_blot = blots[0];
//             for (auto blot : blots){
//                 if (abs(blot.position-pix_position) < abs(closest_blot.position-pix_position)){
//                     closest_blot.position = blot.position;
//                     closest_blot.luminosity = blot.luminosity;
//                     closest_blot.color = blot.color;
//                     closest_blot.width = blot.width;
//                 }
//             }

//             // compute the pixel's color (from closest blot's width, color & intensity);
//             auto blot_dist = closest_blot.position - pix_position;
//             (*pix) = blot_dist > closest_blot.width/2 ? this->fixture->RGBW(closest_blot.color, closest_blot.luminosity*255) : this->fixture->RGBW(black, 0);
//         }
//         pix_parser += num_pix_group;

//     }
  

// };