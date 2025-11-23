#include <algorithm>

using namespace std;

#include "addr_LED.h"

// reserve animation for future use --> without it, QLC config would need to be rebuilt for every added animation
#define FILL animations.push_back(new AddrLEDAnimation0(this, black, " - ",    "PIX.0.0", any, 0, 0, int_vec{}));

AddressableLED addr_led(1, 0, 3*NUM_PIX, "LEDs", 1, 255, 20);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */

//TODO WABISABI2 configure intensity vecror, priorities, and animation type 

void AddressableLED::init(){
    // declare animations here
    animations.push_back(new AddrLEDAnimation0(this, black, " - ",    "PIX.0.0", any, 0, 0, int_vec{1,2,3}));
    
    animations.push_back(new AddrLEDAnimation0(this, "Couleur fixe",    "PIX.0.1", any, 0, 255, int_vec{1,2,3}));

    FILL    
    FILL
    //AUTOCOLOR with Animation type 1 : Analog Beat all pixels ()Beatmatcher original animation)------------------------------
    animations.push_back(new AddrLEDAnimation1(this, bar, 1, "Beat (Original)", "PIX.6.1", leader, 255, 1, int_vec{2,3}));     

    //AUTOCOLOR with Animation type 1 : Analog Beat with random fragments ----------------------------------------------------
    animations.push_back(new AddrLEDAnimation1(this, group, 0.7,  "Beat (Group)",   "PIX.6.2.1", leader, 255, 1, int_vec{2,3}));     
    animations.push_back(new AddrLEDAnimation1(this, bar,   0.7,  "Beat (Barre)",   "PIX.6.2.1", leader, 255, 1, int_vec{2,3}));     
    animations.push_back(new AddrLEDAnimation1(this, seg,   0.7,  "Beat (Segm.)",   "PIX.6.2.1", leader, 255, 0, int_vec{2,3}));     
    animations.push_back(new AddrLEDAnimation1(this, pix,   0.7,  "Beat (Pixel)",   "PIX.6.2.3", leader, 255, 1, int_vec{3}));     
    FILL

    //AUTOCOLOR with Animation type 2 : Digital Beat -------------------------------------------------------------------------
    animations.push_back(new AddrLEDAnimation2(this, group,   "Beat digital (Group)",  "PIX.7.1", leader, 1, 255, int_vec{2,3}));     
    animations.push_back(new AddrLEDAnimation2(this, bar,     "Beat digital (Barre)",  "PIX.7.1", leader, 1, 255, int_vec{2,3}));     
    animations.push_back(new AddrLEDAnimation2(this, seg,     "Beat digital (Segm.)",  "PIX.7.2", leader, 0, 255, int_vec{2,3}));     
    animations.push_back(new AddrLEDAnimation2(this, pix,     "Beat digital (Pixel)",  "PIX.7.3", leader, 1, 255, int_vec{3}));     
    FILL
    FILL

    //AUTOCOLOR with Animation type 4 : Random Bursts----------------------------------------------------------------------------------------
    animations.push_back(new AddrLEDAnimation4(this, gaussian, bar, 7000,   30000, "Bulles statique", "PIX.8.1",  backer,  1, 255, int_vec{1}));
    animations.push_back(new AddrLEDAnimation4(this, gaussian, bar, 3000,   3000,  "Bulles très lentes", "PIX.8.1",  backer,  1, 255, int_vec{1}));
    animations.push_back(new AddrLEDAnimation4(this, gaussian, bar, 1800,   1500,  "Bulles lentes ",     "PIX.8.2",  backer,  1, 255, int_vec{1,2}));
    animations.push_back(new AddrLEDAnimation4(this, gaussian, bar, 200,    600,   "Bulles rapides ",    "PIX.8.2",  any,     1, 255, int_vec{1,2,3}));
    animations.push_back(new AddrLEDAnimation4(this, gaussian, group, 1500,   2000,  "Bulles lentes (group)",     "PIX.8.2",  any,     1, 255, int_vec{1,2}));
    animations.push_back(new AddrLEDAnimation4(this, gaussian, group, 200,    600,   "Bulles rapides (group)",    "PIX.8.2",  any,     1, 255, int_vec{2,3}));
    FILL
    FILL
    animations.push_back(new AddrLEDAnimation4(this, gaussian,  pix, 100, 1500,        "Scintillement lent",         "PIX.8.1", backer, 1, 255, int_vec{1}));
    animations.push_back(new AddrLEDAnimation4(this, gaussian,  pix, 10,  800,         "Scintillement rapide",       "PIX.8.1", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new AddrLEDAnimation4(this, square,    pix, 10,  1000/FRATE,  "Scintillement frénétique",  "PIX.8.1", backer, 1, 255, int_vec{2,3}));
    FILL
    FILL
    FILL

    animations.push_back(new AddrLEDAnimation4(this, square,   bar, 7000,   30000,   "Néon quasi-stat.",   "PIX.8.3",  backer,  1, 255, int_vec{1}));
    animations.push_back(new AddrLEDAnimation4(this, square,   bar, 3000,   3000,    "Néon très lent",     "PIX.8.3",  backer,  1, 255, int_vec{1,2}));
    animations.push_back(new AddrLEDAnimation4(this, square,   bar, 1800,   1500,    "Néon lent",          "PIX.8.3",  backer,  1, 255, int_vec{1,2}));
    animations.push_back(new AddrLEDAnimation4(this, square,   bar, 200,    600,     "Néon rapide",        "PIX.8.4",  any,     1, 255, int_vec{1,2,3}));
    FILL
    FILL

    animations.push_back(new AddrLEDAnimation4(this, expdecay,   bar, 1800,   1500,    "Décharge lent",        "PIX.8.3",  backer,  1, 255, int_vec{1,2}));
    animations.push_back(new AddrLEDAnimation4(this, expdecay,   bar, 200,    600,     "Décharge rapide",      "PIX.8.4",  any,     1, 255, int_vec{3}));
    FILL
    FILL
    FILL
    FILL

    animations.push_back(new AddrLEDAnimation4(this, square, bar,    150,   1000/FRATE, "Strobe lent", "PIX.8.6",            any,     1, 255, int_vec{2,3}));
    animations.push_back(new AddrLEDAnimation4(this, square, group,  150,   1000/FRATE, "Strobe lent (groupe)", "PIX.8.6",   any,     1, 255, int_vec{2,3}));
    animations.push_back(new AddrLEDAnimation4(this, square, bar,    50,    1000/FRATE, "Strobe rapide", "PIX.8.5",          leader,  1, 255, int_vec{3}));
    animations.push_back(new AddrLEDAnimation4(this, square, group,  50,    1000/FRATE, "Strobe rapide (groupe)", "PIX.8.5", leader,  1, 255, int_vec{3}));
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
    FILL
    FILL

    this->activate_none();
    this->dump_animations("AddressableLED");
}

// spits out an ordered vector containing every subpixel value (0-256)
DMX_vec AddressableLED::buffer(){
    DMX_vec data(NUM_SUBPIX);
    
    double final_master =  this->active_animation!=nullptr ? 
                                    animator.master/255.0 * this->master/255.0 * this->active_animation->master/255.0
                                    : animator.master/255.0;  // from 0.0 to 1.0

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
        case yellow     :ref_int = 200,     temp = fcn::RGB_norm(DMX_vec{255,105,0});    break;
        case orange     :                   temp = fcn::RGB_norm(DMX_vec{255,35,0});    break;
        case sodium     :                   temp = fcn::RGB_norm(DMX_vec{255,16,0});    break;
        case cyan       :ref_int = 150;     temp = fcn::RGB_norm(DMX_vec{0,160,255});   break;
        case purple     :                   temp = fcn::RGB_norm(DMX_vec{160,0,255});   break;    
        case magenta    :                   temp = fcn::RGB_norm(DMX_vec{255,0,255});   break;
        case pink       :                   temp = fcn::RGB_norm(DMX_vec{255,0,86});    break;
        case w_white    :                   temp = fcn::RGB_norm(DMX_vec{255,130,65}); break;
        case c_white    :                   temp = fcn::RGB_norm(DMX_vec{255,200,180}); break;
        case gold       :                   temp = fcn::RGB_norm(DMX_vec{255,80,10});    break;
        case light_red      :               temp = fcn::RGB_norm(DMX_vec{255,40,15});   break;
        case light_cyan     :ref_int = 220; temp = fcn::RGB_norm(DMX_vec{120,235,255});   break;
        case light_blue     :               temp = fcn::RGB_norm(DMX_vec{70,80,255});   break;
        case light_purple   :               temp = fcn::RGB_norm(DMX_vec{206,89,255});   break;
        case light_magenta  :               temp = fcn::RGB_norm(DMX_vec{255,75,231});   break;
        case light_pink     :               temp = fcn::RGB_norm(DMX_vec{255,58,114});   break;
        case light_green    :ref_int = 180, temp = fcn::RGB_norm(DMX_vec{50,255,40});   break;
        default         :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity==-1 ? -1 : (int)ref_int * intensity/255.0);
}


/*
  ###          #######                 
 #   #         #       # #    # ###### 
#     #        #       #  #  #  #      
#     #        #####   #   ##   #####  
#     # ###    #       #   ##   #      
 #   #  ###    #       #  #  #  #      
  ###   ###    #       # #    # ##### */


void AddrLEDAnimation0::init() {
    BaseAnimation::init();
}
void AddrLEDAnimation0::init(const color_vec& palette) {
    if (this->autocolor){
        switch (palette.size())
        {
        case 0:     this->color = black;        break;
        case 1:     this->color = palette[0];   break;
        default:    this->color = *(palette.end()-1);   break;
        }
    }

    //Standard init()
    AddrLEDAnimation0::init();
}

void AddrLEDAnimation0::new_frame() {
    this->fixture->set_allpix_color(this->color);
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
    case 1:     this->flash_color=palette[0];   this->back_color=black;
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
    // enable / disable based on music status
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
                case group:this->fixture->set_group_color(units_index[i], unit_i_RGB);
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
    case 1:     this->flash_color=palette[0];   this->back_color=black;
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
                case group:this->fixture->set_group_color(units_index[i], flash_RGB);
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
                case group : this->fixture->set_group_color(units_index[i], backgd_RGB);
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
// void AddrLEDAnimation3::init() {
//     BaseAnimation::init();
// }
// void AddrLEDAnimation3::new_frame() {
//     BaseAnimation::new_frame();
    
//     // double f_weight = enable_filter*param_filter_weight*!is_first_frame();
    
//     for (int i = 0; i<NUM_PIX; i++){
//         pix_intensities[i] = min(255, max(0, fcn::random_walk((int)pix_intensities[i], 5, 0, 255) ));
//         // if(f_weight != 0)
//         //     pix_intensities[i] = min(255.0, max(0.0, pix_intensities[i] + f_weight * (atan_transfo[rand_min_max(0, 256)] - 127.0) ));
//         // else
//         //     pix_intensities[i] = atan_transfo[rand_min_max(0, 256)];

//         this->fixture->pixels[i] = this->fixture->RGB(color, pix_intensities[i]);
//     }
// }

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
    
    const int n_unit = unit==group ? group_conf.size() : (unit==bar ? NUM_BAR : (unit==seg ? NUM_SEG : (unit==pix ? NUM_PIX : 0)));

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
        this->flash_colors = color_vec{palette[0]}, this->back_color = black;  break;
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

        const pixel ani_backgd_RGB = fixture->RGB(back_color, 30);
        
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
                case group:this->fixture->set_group_color(i_unit, unit_final_RGB);
                    break;
                case bar : this->fixture->set_bar_color(i_unit, unit_final_RGB);
                    break;
                case seg : this->fixture->set_segment_color(i_unit, unit_final_RGB);
                    break;
                case pix : this->fixture->pixels[i_unit] = unit_final_RGB;
                    break;
            }
    }
}


