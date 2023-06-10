#include "spot.h"
#include "constant.h"


SpotFixture spot(73);

void SpotFixture::init(){
    this->animations.push_back(new SpotAnimation1(this, 0,0,0,0,    "Black", "SPOT.1.1"));
    this->animations.push_back(new SpotAnimation1(this, 0,0,0,255,  "White", "SPOT.1.2"));
    this->animations.push_back(new SpotAnimation1(this, 255,0,0,0,  "Red", "SPOT.1.3"));
    this->animations.push_back(new SpotAnimation1(this, 0,255,0,0,  "Green", "SPOT.1.4"));
    this->animations.push_back(new SpotAnimation1(this, 0,0,255,0,  "Blue", "SPOT.1.5"));
    this->animations.push_back(new SpotAnimation1(this, 255,255,0,0,"Yellow", "SPOT.1.6"));
    this->animations.push_back(new SpotAnimation1(this, 255,0,255,0,"Magenta", "SPOT.1.7"));
    this->animations.push_back(new SpotAnimation1(this, 0,255,255,0,"Cyan", "SPOT.1.8"));

    this->active_animation = this->animations[ rand() % this->animations.size() ];
    this->active_animation->init();
}


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
