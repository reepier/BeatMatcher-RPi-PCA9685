#include "spider.h"
#include "sysfcn.h"
#include "debug.h"
#include "sysfcn.h"

using namespace std;

// --------------------------------------
// SPIDER FIXTURE definition
// --------------------------------------
SpiderFixture spider(29, 44, "AFX-9-Beam");

void SpiderFixture::init(){
    // push the animations:
    // Animation TYPE 1
    this->animations.push_back(new SpiderAnimation1(this, black,  0, 0, int_vec{tiltMIN,tiltMIN,tiltMIN},    "BLACK", "SPI.0.0"));
    
    this->animations.push_back(new SpiderAnimation1(this, red,    0, 20, int_vec{90,90,90},    "Red, 90°, static", "SPI.1.1"));
    this->animations.push_back(new SpiderAnimation1(this, white,    0, 20, int_vec{20,20,20},  "White, 20°, slow", "SPI.1.2"));
    this->animations.push_back(new SpiderAnimation1(this, blue,    0, -20, int_vec{130,130,130},  "Blue, 130°, slow", "SPI.1.3"));
    // Animation TYPE 2
    // SpiderAnimation2(SpiderFixture *f, SimpleColor b_col, SimpleColor f_col, Shape f_shp, unsigned long f_len, unsigned long f_dt,int p_pos, int p_speed, int_vec t_pos, int t_per, Shape t_shp, std::string d, std::string i){
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, gaussian,   400, 300,   0, 20,    int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.1"));
    this->animations.push_back(new SpiderAnimation2(this, red,   color_vec{white}, gaussian,   800, 300,   0, 20,    int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.2"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{red, blue}, gaussian,   500, 700,   0, 20,    int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.3"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, gaussian,   700, 1000,  0, 20,   int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.4"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, gaussian,   1000,2000,  0, 20,  int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.5"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, gaussian,   1500,3000,  0, 20,  int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.6"));
    this->animations.push_back(new SpiderAnimation2(this, black, color_vec{white}, gaussian,   1500,500,  0, 20,  int_vec{0,0,0}, 10000, sinus, "Developpement animation",   "SPI.2.7"));
    
    this->activate_by_ID("SPI.0.0");
}

DMX_vec SpiderFixture::buffer(){
    DMX_vec ret(this->nCH);
    // ret.resize(this->nCH);
    
    ret[0] = min(max( map( this->pan_position%360 , 0, 359, 0, 255)  ,0),255);
    ret[1] = (this->pan_speed == 0) ? 0 : 
                    (this->pan_speed<0) ? max(min( map(this->pan_speed, -128, -1, 10, 127), 255),10) :
                        max(min( map(this->pan_speed, 1, 127, 128, 255), 255),10);

    ret[2]= min(max(    map(this->tilt[0], -30, 120, 0, 255)    ,0),255);
    ret[3]= min(max(    map(this->tilt[1], -30, 120, 0, 255)    ,0),255);
    ret[4]= min(max(    map(this->tilt[2], -30, 120, 0, 255)    ,0),255);
    
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

// ---------------------------------------------
// SPIDER ANIMATION definition
// ---------------------------------------------
// ---------------------------------------------

// ---------------------------------------------
// Animtion TYPE 1
void SpiderAnimation1::new_frame(){
    balise("Compute new spider1 frame");
    // do onothin, simply set the fixture's colors & motor settings
    this->fixture->pan_position = this->pan_pos;
    this->fixture->pan_speed = this->pan_spd;
    this->fixture->tilt = this->tilt;
    this->fixture->pixels = this->pix;
}

// ---------------------------------------------
// Animtion TYPE 2
void SpiderAnimation2::update_flash_time(){
    unsigned long t = frame.t_current_ms;   //for readability
    static int cpt = 0;
    for(int pix = 0; pix < flash_time.size(); pix++){   //pour chaque pixel
        
        unsigned long t_next = flash_time[pix][1];
        if (t>t_next){    // si t a depassé t_next
            
            flash_time[pix][0] = t_next;
            flash_time[pix][1] = t_next + rand_min_max(flash_length*2, 2*9*flash_dt);   // flash interval : [0+eps ; 2*flash_dt] --> average flash_dt between flashes
            
            flashes[pix][0].time = flashes[pix][1].time;
            flashes[pix][1].time = flashes[pix][0].time + rand_min_max(flash_length*2, 2*9*flash_dt);
            flashes[pix][0].color = flashes[pix][1].color;
            flashes[pix][1].color = fcn::random_pick(flash_colors, flash_color_proba);
            // log(1, );
            cpt++;
                        // log(1, "now:", t/1000.0, "\tnext:", (flash_time[pix][1]-t)/1000.0);
        }
    }
}

void SpiderAnimation2::new_frame(){
    // TODO finish the transition to a multi color flash capability

    this->fixture->pixels       = pixel_vec(9, BLACK);
    this->fixture->pan_position = this->pan_position;
    this->fixture->pan_speed    = this->pan_speed;
    this->fixture->tilt         = int_vec{0,0,0};

    update_flash_time();

    unsigned long t = frame.t_current_ms;
    double sigma = this->flash_length/3.0;
    DMX_vec background_color_RGBW = fcn::RGBW(this->background_color, 50);
    DMX_vec flash_color_RGBW = fcn::RGBW(this->flash_colors[0]);   //temporary
    
    // Tilt
    if (this->tilt_period == 0){
        this->fixture->tilt = this->tilt_position;
    }else{
        double rad = 2*M_PI*t/this->tilt_period;
        this->fixture->tilt     = int_vec{(int)sin_min_max(rad, tiltMIN, tiltMAX), (int)sin_min_max(rad+M_PI/3, tiltMIN, tiltMAX), (int)sin_min_max(rad+2*M_PI/3, tiltMIN, tiltMAX)};
    }

    // Colors
    for (int pix = 0; pix < this->fixture->pixels.size(); pix++){
        unsigned long t_prev = flash_time[pix][0];
        unsigned long t_next = flash_time[pix][1];

        double flash_coef = exp( -pow(pow(t-t_prev ,2)/2/pow(sigma,2), 2)) + exp( -pow(pow(t_next-t ,2)/2/pow(sigma,2),2)); //TODO implement more differnt shapes

        this->fixture->pixels[pix][R] = background_color_RGBW[R] * (1-flash_coef) + flash_coef * flash_color_RGBW[R];
        this->fixture->pixels[pix][G] = background_color_RGBW[G] * (1-flash_coef) + flash_coef * flash_color_RGBW[G];
        this->fixture->pixels[pix][B] = background_color_RGBW[B] * (1-flash_coef) + flash_coef * flash_color_RGBW[B];
        this->fixture->pixels[pix][W] = background_color_RGBW[W] * (1-flash_coef) + flash_coef * flash_color_RGBW[W];
    }
    
}