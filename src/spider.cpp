#include "spider.h"
#include "sysfcn.h"
#include "debug.h"
#include "sysfcn.h"

using namespace std;

/*
####### ### #     # ####### #     # ######  ####### 
#        #   #   #     #    #     # #     # #       
#        #    # #      #    #     # #     # #       
#####    #     #       #    #     # ######  #####   
#        #    # #      #    #     # #   #   #       
#        #   #   #     #    #     # #    #  #       
#       ### #     #    #     #####  #     # ####### 
*/
SpiderFixture spider(29, 44, "AFX-9-Beam", 1);

void SpiderFixture::init(){
        log(4, __FILE__, " ", __LINE__, " ",__func__);

    this->animations.push_back(new SpiderAnimation1(this, black,  0, 0, int_vec{tiltMAX,tiltMAX,tiltMAX},    " ", "SPI.0.0"));
    this->animations.push_back(new SpiderAnimation1(this, white,     0, 30,    int_vec{0, 0, 0},    "Horizontality check",       "SPI.0.1"));
    this->animations.push_back(new SpiderAnimation1(this, white,     0, 30,    int_vec{90, 90, 90}, "Orthogonality check",       "SPI.0.2"));

    // push the animations:
    // Animation TYPE 1 --> fixed position for chill zone @OMERTA IX
    int high_pos = 100, low_pos = -10;
    this->animations.push_back(new SpiderAnimation1(this, red,     0, 0,    int_vec{low_pos, high_pos, high_pos},  "Red static (coin chill)",       "SPI.1"));
    // this->animations.push_back(new SpiderAnimation1(this, sodium,  120, 0,  int_vec{high_pos,low_pos,high_pos},  "Sodium static (coin chill)",    "SPI.2"));
    // this->animations.push_back(new SpiderAnimation1(this, orange,  240, 0,  int_vec{high_pos,high_pos,low_pos},  "Orange static (coin chill)",    "SPI.3"));
    this->animations.push_back(new SpiderAnimation1(this, yellow,  0, 0,    int_vec{low_pos,high_pos,high_pos},  "Yellow static (coin chill)",    "SPI.4"));
    // this->animations.push_back(new SpiderAnimation1(this, gold,    120, 0,  int_vec{high_pos,low_pos,high_pos},  "Gold static (coin chill)",      "SPI.5"));
    this->animations.push_back(new SpiderAnimation1(this, white,   240, 0,  int_vec{high_pos,high_pos,low_pos},  "White static (coin chill)",     "SPI.6"));
    // this->animations.push_back(new SpiderAnimation1(this, cyan,    0, 0,    int_vec{low_pos,high_pos,high_pos},  "Cyan static (coin chill)",      "SPI.7"));
    // this->animations.push_back(new SpiderAnimation1(this, blue,    120, 0,  int_vec{high_pos,low_pos,high_pos},  "Blue static (coin chill)",      "SPI.8"));
    this->animations.push_back(new SpiderAnimation1(this, purple,  240, 0,  int_vec{high_pos,high_pos,low_pos},  "Purple static (coin chill)",    "SPI.9"));
    // this->animations.push_back(new SpiderAnimation1(this, magenta, 0, 0,    int_vec{low_pos,high_pos,high_pos},  "Magenta static (coin chill)",   "SPI.10"));
    // this->animations.push_back(new SpiderAnimation1(this, pink,    120, 0,  int_vec{high_pos,low_pos,high_pos},  "Pink static (coin chill)",      "SPI.11"));
    // this->animations.push_back(new SpiderAnimation1(this, green,   240, 0,  int_vec{high_pos,high_pos,low_pos},  "Green static (coin chill)",     "SPI.12"));
    // this->animations.push_back(new SpiderAnimation1(this, white,    0, 20, int_vec{20,20,20},  "White, 20°, slow", "SPI.1.2"));
    // this->animations.push_back(new SpiderAnimation1(this, blue,    0, -20, int_vec{130,130,130},  "Blue, 130°, slow", "SPI.1.3"));

    // Animation TYPE 2
    // SpiderAnimation2(SpiderFixture *f, SimpleColor b_col, SimpleColor f_col, Shape f_shp, unsigned long f_len, unsigned long f_dt,int p_pos, int p_speed, int_vec t_pos, int t_per, Shape t_shp, std::string d, std::string i){
    // Slow beams
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red},      gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, red",      "SPI.3.1.1"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{sodium},   gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, sodium",   "SPI.3.1.2"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{orange},   gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, orange",   "SPI.3.1.3"));
 // this->animations.push_back(new SpiderAnimation2(this, black, color_vec{yellow},   gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, yellow",   "SPI.3.1.4"));
 // this->animations.push_back(new SpiderAnimation2(this, black, color_vec{gold},     gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, gold",     "SPI.3.1.5"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white},    gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, white",    "SPI.3.1.6"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{cyan},     gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, cyan",     "SPI.3.1.7"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{blue},     gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, blue",     "SPI.3.1.8"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{purple},   gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, purple",   "SPI.3.1.9"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{magenta},  gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, magenta",  "SPI.3.1.10"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{pink},     gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, pink",     "SPI.3.1.11"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{green},    gaussian, 2000, 3, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, green",    "SPI.3.1.12"));
    
    //medium speed beams    
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red, red, red, white},     gaussian2, 1000, 3, 0, 20,  int_vec{70,120}, 8000,  "Slow rotating beams, Red White",   "SPI.3.4"));

    // Quick beams
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red},     square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,    "Quick moving beams, Red",     "SPI.3.3.1"));              
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{sodium},  square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000, "Quick moving beams, Sodium",  "SPI.3.3.2"));                
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{orange},  square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000, "Quick moving beams, Orange",  "SPI.3.3.3"));                
 // this->animations.push_back(new SpiderAnimation2(this, black, color_vec{yellow},  square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000, "Quick moving beams, Yellow",  "SPI.3.3.4"));                
 // this->animations.push_back(new SpiderAnimation2(this, black, color_vec{gold},    square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,   "Quick moving beams, Gold",    "SPI.3.3.5"));                
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white},   square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,  "Quick moving beams, White",   "SPI.3.3.6"));              
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{cyan},    square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,   "Quick moving beams, Cyan",    "SPI.3.3.7"));                
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{blue},    square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,   "Quick moving beams, Blue",    "SPI.3.3.8"));                
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{purple},  square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000, "Quick moving beams, Purple",  "SPI.3.3.9"));                
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{magenta}, square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,"Quick moving beams, Magenta", "SPI.3.3.0"));              
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{pink},    square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,   "Quick moving beams, Pink",    "SPI.3.3.1"));                
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{green},   square,    100, 0.5, 0, 20,   int_vec{80,110}, 7000,  "Quick moving beams, Green",   "SPI.3.3.2"));              

    // Animation TYPE 3
    // Beating array of beams
    // Monochrome
    this->animations.push_back(new SpiderAnimation3(this, color_vec{red},"Beating beams Red", "SPI.4.1.1"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{sodium},"Beating beams Sodium", "SPI.4.1.2"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{orange},"Beating beams Orange", "SPI.4.1.3"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{yellow},"Beating beams Yellow", "SPI.4.1.4"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{gold},"Beating beams Gold", "SPI.4.1.5"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{white},"Beating beams White", "SPI.4.1.6"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{cyan},"Beating beams Cyan", "SPI.4.1.7"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{blue},"Beating beams Blue", "SPI.4.1.8"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{purple},"Beating beams Purple", "SPI.4.1.9"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{magenta},"Beating beams Magenta", "SPI.4.1.10"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{pink},"Beating beams Pink", "SPI.4.1.11"));
    this->animations.push_back(new SpiderAnimation3(this, color_vec{green},"Beating beams Green", "SPI.4.1.12"));

    
    this->animations.push_back(new SpiderAnimation3(this, color_vec{},"Beating beams ", "SPI.4.1.")); 
    this->animations.push_back(new SpiderAnimation3(this, color_vec{red,sodium,orange,yellow,gold,white,cyan,blue,purple,magenta,pink,green},"animtion spider beat", "SPI.4.1")); 

    this->activate_by_index(0);
}

DMX_vec SpiderFixture::buffer(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    DMX_vec ret(this->nCH);
    // ret.resize(this->nCH);
    
    ret[0] = min(max( map( this->pan_position%360 , 0, 359, 0, 255)  ,0),255);
    ret[1] = (this->pan_speed == 0) ? 0 : 
                    (this->pan_speed<0) ? max(min( map(this->pan_speed, -128, -1, 10, 127), 255),10) :
                        max(min( map(this->pan_speed, 1, 127, 128, 255), 255),10);

    // Theoretical Calibration 
    // ret[2]= min(max(    map(this->tilt[0], tiltMIN, tiltMAX, 0, 255)    ,0),255);
    // ret[3]= min(max(    map(this->tilt[1], tiltMIN, tiltMAX, 0, 255)    ,0),255);
    // ret[4]= min(max(    map(this->tilt[2], tiltMIN, tiltMAX, 0, 255)    ,0),255);
    // Empirical channel by channel calibration
    ret[2]= min(max(    map(this->tilt[0], 0, 90, 52, 215)    ,0),255);
    ret[3]= min(max(    map(this->tilt[1], 0, 90, 41, 207)    ,0),255);
    ret[4]= min(max(    map(this->tilt[2], 0, 90, 39, 204)    ,0),255);
    
    ret[5]=this->MASTER_DIMMER;
    ret[6]=this->strobe;

    for (int led=0; led<NLED; led++){
        for (int pix=0; pix<NCOL; pix++){
            ret[7+led*NCOL+pix] = this->pixels[led][pix];
        }
    }
    ret[nCH-1] = prog;

    return ret;
}

DMX_vec SpiderFixture::RGBW(simpleColor c, int intensity){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    switch (c)
    {
    case black:
        return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
        break;
    case red:
        return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);
        break;
    case green:
        return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 160.0/255*intensity);
        break;
    case blue:
        return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);
        break;
    case yellow:
        return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);
        break;
    case orange:
        return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);
        break;
    case sodium:
        return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);
        break;
    case cyan:
        return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);
        break;
    case purple:
        return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);
        break;    
    case magenta:
        return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);
        break;
    case pink:
        return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);
        break;
    case white:
        return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
        break;
    case gold:
        return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
        break;
    default:
        break;
    }
}

/*
   #    #     # ### #     #    #    ####### ### ####### #     #              #   
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    #             ##   
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   #            # #   
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #   #####      #   
####### #   # #  #  #     # #######    #     #  #     # #   # #              #   
#     # #    ##  #  #     # #     #    #     #  #     # #    ##              #   
#     # #     # ### #     # #     #    #    ### ####### #     #            ##### 
*/

void SpiderAnimation1::new_frame(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    BaseAnimation::new_frame();

    balise("Compute new spider1 frame");
    // do onothin, simply set the fixture's colors & motor settings
    this->fixture->pan_position = this->pan_pos;
    this->fixture->pan_speed = this->pan_spd;
    this->fixture->tilt = this->tilt;
    this->fixture->pixels = this->pix;
}


/*
   #           #####  
  # #         #     # 
 #   #              # 
#     # #####  #####  
#######       #       
#     #       #       
#     #       ####### 
*/
void SpiderAnimation2::update_next_flash(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    unsigned long t = frame.t_current_ms;   //for readability

    static int cpt = 0;
    for(int pix = 0; pix < flashes.size(); pix++){   //pour chaque pixel
        
        unsigned long t_next = flashes[pix][i_next].time;
        if (t>t_next){    // si t a depassé t_next
            
            // flash_time[pix][0] = t_next;
            // flash_time[pix][1] = t_next + rand_min_max(flash_length*2, 2*9*flash_dt);   // flash interval : [0+eps ; 2*flash_dt] --> average flash_dt between flashes
            
            this->flashes[pix][i_prev].time  = this->flashes[pix][i_next].time;
            this->flashes[pix][i_next].time  = this->flashes[pix][i_prev].time + rand_min_max(flash_length, 2*9*flash_dt);
            this->flashes[pix][i_prev].color = this->flashes[pix][i_next].color;
            this->flashes[pix][i_next].color = fcn::random_pick(flash_colors, flash_color_proba);
            // log(1, );
            cpt++;
            // log(1, "now:", t/1000.0, "\tnext:", (flash_time[pix][1]-t)/1000.0);
        }
    }
}

void SpiderAnimation2::new_frame(){
        log(4, __FILE__, " ", __LINE__, " ",__func__);

    BaseAnimation::new_frame();

    this->fixture->pixels       = pixel_vec(9, DMX_vec{0,0,0,0});
    this->fixture->pan_position = this->pan_position;
    this->fixture->pan_speed    = this->pan_speed;
    this->fixture->tilt         = int_vec{0,0,0};

    update_next_flash();

    unsigned long t = frame.t_current_ms;
    DMX_vec background_color_RGBW = this->fixture->RGBW(this->background_color, 50);
    
    // Tilt
    if (this->tilt_period == 0){
        this->fixture->tilt = this->tilt_position;
    }else{
        double rad = 2*M_PI*t/this->tilt_period;
        int t_min = min(max(this->tilt_position[0], tiltMIN),tiltMAX);
        int t_max = min(max(this->tilt_position[1], tiltMIN),tiltMAX);

        this->fixture->tilt     = int_vec{(int)sin_min_max(rad, t_min, t_max), (int)sin_min_max(rad+M_PI/3, t_min, t_max), (int)sin_min_max(rad+2*M_PI/3, t_min, t_max)};
    }

    // Colors
    for (int pix_i = 0; pix_i < this->fixture->pixels.size(); pix_i++){
        unsigned long t_prev = this->flashes[pix_i][i_prev].time;
        unsigned long t_next = this->flashes[pix_i][i_next].time;
        DMX_vec flash_color_RGBW = (t-t_prev > t_next-t) ? this->fixture->RGBW(this->flashes[pix_i][i_next].color) : this->fixture->RGBW(this->flashes[pix_i][i_prev].color);

        double flash_coef;
        switch (this->flash_shape){
            case gaussian2 :
            // flash_coef = exp( -pow(pow(t-t_prev ,2)/2/pow(sigma,2), 2)) + exp( -pow(pow(t_next-t ,2)/2/pow(sigma,2),2)); //TODO implement more differnt shapes
            flash_coef = fcn::gaussian2(t, t_prev, flash_length, 0.0, 1.0) + fcn::gaussian2(t, t_next, flash_length, 0.0, 1.0);
            break;
            
            case gaussian :
            // flash_coef = exp( - pow(t-t_prev ,2)/2/pow(sigma,2)) + exp( -pow(pow(t_next-t ,2)/2/pow(sigma,2),2)); //TODO implement more differnt shapes
            flash_coef = fcn::gaussian(t, t_prev, flash_length, 0.0, 1.0) + fcn::gaussian(t, t_next, flash_length, 0.0, 1.0);            
            break;
            
            case triangle :
            flash_coef = fcn::triangle(t,t_prev, this->flash_length, 0.0,1.0) + fcn::triangle(t,t_next, this->flash_length, 0.0,1.0);
            break;
            
            case square :
            flash_coef = fcn::square(t,t_prev, this->flash_length, 0.0,1.0) + fcn::square(t,t_next, this->flash_length, 0.0,1.0);
            break;
            
            default :
            break;
        }
        

        this->fixture->pixels[pix_i][R] = background_color_RGBW[R] * (1-flash_coef) + flash_coef * flash_color_RGBW[R];
        this->fixture->pixels[pix_i][G] = background_color_RGBW[G] * (1-flash_coef) + flash_coef * flash_color_RGBW[G];
        this->fixture->pixels[pix_i][B] = background_color_RGBW[B] * (1-flash_coef) + flash_coef * flash_color_RGBW[B];
        this->fixture->pixels[pix_i][W] = background_color_RGBW[W] * (1-flash_coef) + flash_coef * flash_color_RGBW[W];
    }
    
}

/*
   #           #####  
  # #         #     # 
 #   #              # 
#     # #####  #####  
#######             # 
#     #       #     # 
#     #        #####  
*/


void SpiderAnimation3::new_frame(){
    BaseAnimation::new_frame();
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    // copy global variables for readability
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    bool new_beat = sampler.new_beat;
    auto fix = this->fixture;

    // beat fade coefficient --> decreases exponentially from 1 to 0 after every beat (in ~ x10^-2 s) 
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    int n_beams = coef*NLED; // the number of beams to display depends on the exponential coef

    // update the random vector at every beat;
    if(new_beat || this->is_first_frame()){
        this->rand_index_vector = fcn::randomized_vector(this->index_vector);
        for(color_vec::iterator c = rand_col_vector.begin(); c != rand_col_vector.end(); ++c){
            (*c) = fcn::random_pick(this->flash_colors);
        }

        // log(1, fcn::vec_to_str(rand_index_vector, ','));
        // log(2, fcn::palette_to_string(rand_col_vector, ','));
    }

    // Set pixel colors
    for(auto i : index_vector){
        if (i<n_beams){
            fix->pixels[ rand_index_vector[i] ] = fix->RGBW(rand_col_vector[i], pow(coef, 0.25)*255);
        }else{
            fix->pixels[ rand_index_vector[i] ] = fix->RGBW(black);
        }
    }
    
    // Set tilt & pan
    fix->tilt = param_anim_tilt;
    fix->pan_position = param_anim_pan;
    fix->pan_speed = param_anim_pan_spd;

    fix->pan_position = this->param_anim_pan;
    fix->pan_speed    = this->param_anim_pan_spd;

    // Tilt
    if (param_anim_tilt_period == 0){
        fix->tilt = param_anim_tilt;
    }else{
        double rad = 2*M_PI*t_ms/param_anim_tilt_period;
        int t_min = min(max(param_anim_tilt[0], tiltMIN),tiltMAX);
        int t_max = min(max(param_anim_tilt[1], tiltMIN),tiltMAX);

        this->fixture->tilt     = int_vec{(int)sin_min_max(rad, t_min, t_max), (int)sin_min_max(rad+M_PI/3, t_min, t_max), (int)sin_min_max(rad+2*M_PI/3, t_min, t_max)};
    }
}