#include "spot.h"
#include "constant.h"


SpotFixture spot_g(73);     //spot d'ambiance gauche
SpotFixture spot_d(81);     //spot d'ambiance droite

SpotFixture spot_1(89);     //spot frontal 1
SpotFixture spot_2(97);     //spot frontal 2
SpotFixture spot_3(105);    //spot frontal 3

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
SpotFront::SpotFront(SpotFixture* s1, SpotFixture* s2, SpotFixture* s3){
    this->spots.push_back(s1);
    this->spots.push_back(s2);
    this->spots.push_back(s3);
};

SpotFront rack(&spot_1, &spot_2, &spot_3);


void SpotFront::init(){
    //this->animations.push_back();
}
