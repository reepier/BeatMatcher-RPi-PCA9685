#include <cmath>

#include "spot.h"
#include "constant.h"
#include "sysfcn.h"

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

std::vector<uint8_t> SpotFixture::buffer(){
    return std::vector<uint8_t>{this->MASTER_DIMMER, this->RGBW[R], this->RGBW[G],this->RGBW[B],this->RGBW[W], this->prog, this->color_wheel, this->strobe};
}

/* /!\ /!\ Bullshit contructor --> I don't plan on coding animation for individual spots */
SpotAnimation1::SpotAnimation1(SpotFixture* fix, uint8_t r,uint8_t g,uint8_t b, uint8_t w, std::string d, std::string i){
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
    this->animations.push_back(new SpotFrontAnimation1(this, std::vector<uint8_t>{25,0,60,0}, std::vector<uint8_t>{255,40,0,0}));
    this->animations.push_back(new SpotFrontAnimation1(this, std::vector<uint8_t>{50,5,0,0}, std::vector<uint8_t>{0,0,0,255}));
}

void SpotRack::init_back(){
    this->rack_size = this->spots.size();
    //this->animations.push_back();
}

// -----------------------------------
// FRONTAL RACK of SPOT Animations
// -----------------------------------
void SpotFrontAnimation1::init(){
    const int sin_max_p_ms = 15000;
    const int sin_min_p_ms = 5000;
    const int rand_const_ms= 5000;
    
    this->frame_cpt = 0;
    this->t_animation_start_ms;
    this->p_ms = std::vector<int>{rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms)};
    
    const int n_spot = this->fixture->spots.size();
    this->t_next.resize(n_spot);
    for (int i=0; i<n_spot; i++){
        t_next[i] = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2);
    }
}

void SpotFrontAnimation1::new_frame(){
    unsigned long t = frame.t_current_ms;
    int n_spot = this->fixture->spots.size();

    // update 4 sinewaves of different period
    std::vector<double> s = {sin(2*M_PI*t/p_ms[0]), sin(2*M_PI*t/p_ms[1]), sin(2*M_PI*t/p_ms[2]), sin(2*M_PI*t/p_ms[3]), sin(2*M_PI*t/p_ms[4]) };
    
    // for each spot "i" of the rack
    for (int i=0; i < this->fixture->rack_size; i++){
        // compute the background color values : 
        this->fixture->spots[i]->RGBW[R] = std::min(std::max(    (int) (  (1+0.4*s[(i+4)%5]) * this->color1[R] * (1 + 0.4*s[(i+0)%5]))  ,0),255);
        this->fixture->spots[i]->RGBW[G] = std::min(std::max(    (int) (  (1+0.4*s[(i+4)%5]) * this->color1[G] * (1 + 0.4*s[(i+1)%5]))  ,0),255);
        this->fixture->spots[i]->RGBW[B] = std::min(std::max(    (int) (  (1+0.4*s[(i+4)%5]) * this->color1[B] * (1 + 0.4*s[(i+2)%5]))  ,0),255);
        this->fixture->spots[i]->RGBW[W] = std::min(std::max(    (int) (  (1+0.4*s[(i+4)%5]) * this->color1[W] * (1 + 0.4*s[(i+3)%5]))  ,0),255);
        // ------------------------------- limit to 0-255 ---------------- Spot Intensity    *  RGBW pixel intensity                            ;
        
    }
}
