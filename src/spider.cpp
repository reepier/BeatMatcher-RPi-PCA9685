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
    // Animation TYPE 1
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
    // monochrome
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, gaussian,   500,  3,   0, 20,  int_vec{50,120}, 10000, "Fast & short white flashes, tilt motion",   "SPI.2.1.1"));
    this->animations.push_back(new SpiderAnimation2(this, black,   color_vec{white}, gaussian, 2000, 2,   0, 20,  int_vec{50,120}, 10000, "Fast white flashes, red back, tilt motion", "SPI.2.1.2"));
    // bichrome
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red, red, red, white}, gaussian, 1000, 1, 0, 20,    int_vec{70, 120}, 10000, "Red & White flashes",              "SPI.2.2.1"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red, purple},          gaussian,   1500, 4,  0, 20, int_vec{70, 120}, 10000, "Red & Blue flashes, tilt motion",  "SPI.2.2.2"));
    this->animations.push_back(new SpiderAnimation2(this, white, color_vec{red, blue, green},     gaussian,   1500, 4,  0, 20, int_vec{70, 120}, 10000, "white bg, red,green,blue flashes", "SPI.2.2.3"));

    // Slow beams
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red, red, red, white},    gaussian2, 2000, 5, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, Red White",  "SPI.3.1"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{blue, blue, blue, white}, gaussian2, 2000, 5, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, Blue White", "SPI.3.2"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red, red, red, blue},     gaussian2, 2000, 5, 0, 20,  int_vec{70,120}, 10000,  "Slow rotating beams, Red Blue",   "SPI.3.3"));
    
    // Quick beams
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, square,    100, 1, 0, 0,   int_vec{90,90,90},     "Quick static beams, White",   "SPI.3.4"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, square,    100, 1, 0, 20,  int_vec{70,120}, 5000, "Quick rotating beams, White", "SPI.3.5"));


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

    // TODO finish the transition to a multi color flash capability
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
        double sigma = this->flash_length/3.0;
        switch (this->flash_shape){
            case gaussian2 :
            // flash_coef = exp( -pow(pow(t-t_prev ,2)/2/pow(sigma,2), 2)) + exp( -pow(pow(t_next-t ,2)/2/pow(sigma,2),2)); //TODO implement more differnt shapes
            flash_coef = fcn::gaussian2(t, t_prev, sigma, 0.0, 1.0) + fcn::gaussian2(t, t_next, sigma, 0.0, 1.0);
            break;
            
            case gaussian :
            // flash_coef = exp( - pow(t-t_prev ,2)/2/pow(sigma,2)) + exp( -pow(pow(t_next-t ,2)/2/pow(sigma,2),2)); //TODO implement more differnt shapes
            flash_coef = fcn::gaussian(t, t_prev, sigma, 0.0, 1.0) + fcn::gaussian(t, t_next, sigma, 0.0, 1.0);            
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
