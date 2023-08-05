#include <cmath>

#include "spot.h"
#include "constant.h"
#include "sysfcn.h"

using namespace std;

SpotFixture spot_1(73);     //spot frontal 1
SpotFixture spot_2(81);     //spot frontal 2
SpotFixture spot_3(89);    //spot frontal 3

SpotFixture spot_g(97);     //spot d'ambiance gauche
SpotFixture spot_d(105);     //spot d'ambiance droite

// -----------------------------------
// INDIVIDUAL SPOT
// -----------------------------------
/* /!\ /!\ Bullshit initializer --> I don't plan on coding animation for individual spots */
void SpotFixture::init(){
    this->animations.push_back(new SpotAnimation1(this, 0,0,0,0,    "Black", "SPOT.0.0"));
    this->animations.push_back(new SpotAnimation1(this, 0,0,0,255,  "White", "SPOT.1.2"));
    this->animations.push_back(new SpotAnimation1(this, 255,0,0,0,  "Red", "SPOT.1.3"));
    this->animations.push_back(new SpotAnimation1(this, 0,255,0,0,  "Green", "SPOT.1.4"));
    this->animations.push_back(new SpotAnimation1(this, 0,0,255,0,  "Blue", "SPOT.1.5"));
    this->animations.push_back(new SpotAnimation1(this, 255,255,0,0,"Yellow", "SPOT.1.6"));
    this->animations.push_back(new SpotAnimation1(this, 255,0,255,0,"Magenta", "SPOT.1.7"));
    this->animations.push_back(new SpotAnimation1(this, 0,255,255,0,"Cyan", "SPOT.1.8"));

    this->activate_by_ID("SPOT.0.0");
    /*
    this->active_animation = this->animations[ rand() % this->animations.size() ];
    this->active_animation->init();
    */
}

DMX_vec SpotFixture::buffer(){
    return DMX_vec{this->MASTER_DIMMER, this->RGBW[R], this->RGBW[G],this->RGBW[B],this->RGBW[W], this->prog, this->color_wheel, this->strobe};
}

/* /!\ /!\ Bullshit contructor --> I don't plan on coding animation for individual spots */
SpotAnimation1::SpotAnimation1(SpotFixture* fix, uint8_t r,uint8_t g,uint8_t b, uint8_t w, string d, string i){
    this->fixture = fix;
    this->name  = "Fixed RGB color";
    this->description = d;
    this->id    = i;
    this->red   = r;
    this->green = g;
    this->blue  = b;
    this->white = w;
}

void SpotAnimation1::init(){
    this->t_animation_start_ms = millis();
    this->frame_cpt = 0;
}

void SpotAnimation1::new_frame(){
    // nothing to do for this animation
    this->fixture->RGBW[R] = this->red;
    this->fixture->RGBW[G] = this->green;
    this->fixture->RGBW[B] = this->blue;
    this->fixture->RGBW[W] = this->white;
}


// -----------------------------------
// RACKs of SPOTS
// -----------------------------------
SpotRack front_rack(&spot_1, &spot_2, &spot_3);
SpotRack back_rack(&spot_g, &spot_d);

void SpotRack::init_front(){
    this->rack_size = this->spots.size();

    //this->animations.push_back();
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{0,0,0,0},       15000, 5000, 8000, 1000, "Black", "FR.0.0"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{25,0,60,0},    DMX_vec{255,40,0,110},   15000, 5000, 8000, 1000, "Purple background / orange flashes", "FR.1.01"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{50,5,0,0},     DMX_vec{0,0,0,255},     15000, 5000, 8000, 1000, "Orange background, white flashes", "FR.1.2"));  
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{50,0,0,0},     DMX_vec{0,0,255,0},     15000, 5000, 8000, 1000, "Red background, Blue flashes", "FR.1.3"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{50,0,0,0},     DMX_vec{255,0,0,0},     15000, 5000, 8000, 1000, "red background, RED flashes", "FR.1.4"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{50,0,0,0},     DMX_vec{255,40,0,40},   15000, 5000, 8000, 1000, "red background orange flashes", "FR.1.5"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{50,0,0,0},     DMX_vec{0,0,0,255},     15000, 5000, 8000, 1000, "red background, white flashes", "FR.1.6"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{50,0,0,0},     DMX_vec{0,0,0,255},     15000, 5000, 3000, 600, "red background, white flashes", "FR.1.61"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{0,0,0,255},       15000, 5000, 5000, 700, "Black background, White flashes", "FR.1.7"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{0,0,0,255},       15000, 5000, 3000, 600, "Black background, White flashes", "FR.1.71"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{255,0,0,0},       15000, 5000, 5000, 700, "Black background, Red flashes", "FR.1.8"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{0,0,150,0},       15000, 5000, 5000, 700, "Black background, Blue flashes", "FR.1.9"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{255,40,0,0},       15000, 5000, 5000, 700, "Black background, Orange flashes", "FR.1.10"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{200,35,0,80},       15000, 5000, 5000, 700, "Black background, Orange/White flashes", "FR.1.11"));
    this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{60,0,30,0},    DMX_vec{0,150,150,80},       15000, 5000, 7000, 1000, "Purple background, Cyan flashes", "FR.1.12"));


    //this->animations.push_back(new SpotFrontAnimation1(this, DMX_vec{0,0,0,0},      DMX_vec{0,0,0,0},       15000, 5000, 8000, 1000, "...", "FR.1."));

}

void SpotRack::init_back(){
    this->rack_size = this->spots.size();
    //this->animations.push_back();
}

// -----------------------------------
// FRONTAL RACK of SPOT Animations
// -----------------------------------
void SpotFrontAnimation1::init(){
    
    
    this->frame_cpt = 0;
    this->t_animation_start_ms;
    this->p_ms = vector<int>{rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms)};
    
    const int n_spot = this->fixture->spots.size();
    this->t_next.resize(n_spot);
    this->t_prev.resize(n_spot);
    for (int i=0; i<n_spot; i++){
        t_next[i] = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2);
        t_prev[i] = 0;
    }
}

void SpotFrontAnimation1::new_frame(){
    long t = frame.t_current_ms;       // for readability
    int n_spot = this->fixture->spots.size();   // for readability

    // update 4 sinewaves of different period
    vector<double> s = {sin(2*M_PI*t/p_ms[0]), sin(2*M_PI*t/p_ms[1]), sin(2*M_PI*t/p_ms[2]), sin(2*M_PI*t/p_ms[3]), sin(2*M_PI*t/p_ms[4]) };
    
    // for each spot "i" of the rack
    for (int i_spot=0; i_spot < n_spot; i_spot++){
        DMX_vec backgd_RGBW(4);        
        // compute the background color values : 
            backgd_RGBW[R] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[R] * (1 + 0.4*s[(i_spot+0)%5]))  ,0),255);
            backgd_RGBW[G] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[G] * (1 + 0.4*s[(i_spot+1)%5]))  ,0),255);
            backgd_RGBW[B] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[B] * (1 + 0.4*s[(i_spot+2)%5]))  ,0),255);
            backgd_RGBW[W] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[W] * (1 + 0.4*s[(i_spot+3)%5]))  ,0),255);
        // ------------------------------- limit to 0-255 ---------------- Spot Intensity    *  RGBW pixel intensity                            ;
        
        // compute the flash = exp( -(spd.(t-t0))²)
            // when the flash passes, compute the next flash timestamp and update prev flash
            if (t > this->t_next[i_spot]){
                this->t_prev[i_spot] = this->t_next[i_spot];
                this->t_next[i_spot] = this->t_next[i_spot] + rand_min_max(this->rand_const_ms/5, this->rand_const_ms*2);
            }

            int t_next_flash = this->t_next[i_spot];        // for readability
            int t_prev_flash = this->t_prev[i_spot];        // for readability  
            
            double flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev_flash), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next_flash), 2));

            this->fixture->spots[i_spot]->RGBW[R] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[R] + flash_intensity * this->color2[R]  ),0),255); 
            this->fixture->spots[i_spot]->RGBW[G] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[G] + flash_intensity * this->color2[G]  ),0),255);
            this->fixture->spots[i_spot]->RGBW[B] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[B] + flash_intensity * this->color2[B]  ),0),255);
            this->fixture->spots[i_spot]->RGBW[W] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[W] + flash_intensity * this->color2[W]  ),0),255);
    }
}
