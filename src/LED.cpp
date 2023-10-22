#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/client/StreamingClient.h>
#include <wiringPi.h>

#include "LED.h"
#include "sysfcn.h"

LEDFixture led(0, 4, "Led Bars");

// ------------------------------------------------------------
// LED FIXTURE CLASS Function definition

// Fixture initalizer
void LEDFixture::init(){
    // animations.push_back(new LEDAnimation1(this, black,  black,           " ", "LED.0.0"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 150, 80} ,DMX_vec{30, 100, 1, 7, 0, 0},   "Warm White Flashes, Red/orange background", "LED.1.1.1"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 50, 10},  DMX_vec{15, 50, 0, 5, 0, 0},    "Sodium Flashes, Red/orange background", "LED.1.2"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 0, 0},    DMX_vec{0, 0, 0, 0, 0, 0},      "Red flashes, Black background", "LED.1.3"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 150, 80}, DMX_vec{30, 100, 0, 0, 0, 10},  "Warm White flashes, Red/Pink background", "LED.1.4"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{0, 0, 255},    DMX_vec{0, 0, 0, 0, 0, 0},      "Blue flashes, Black background", "LED.1.5"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 100, 80}, DMX_vec{0, 80, 0, 0, 0, 20},    "Warm White flashes, Pink background", "LED.1.6"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 100, 80}, DMX_vec{0, 50, 0, 0, 0, 80},    "Warm White flashes, Purple background", "LED.1.7"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 100, 80}, DMX_vec{0, 20, 0, 0, 0, 100},   "Warm White flashes, Blue/Purple backgroud", "LED.1.8"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 100, 80}, DMX_vec{0, 10, 0, 10, 0, 100},  "Warm White flashes, cyan background", "LED.1.9"));
    // animations.push_back(new LEDAnimation1(this, DMX_vec{255, 100, 80}, DMX_vec{0, 0, 0, 0, 0, 0},      "White flashes, Black background", "LED.1.10"));
    animations.push_back(new LEDAnimation1(this, black,  black,  " ",                                 "LED.0.0"));
    
    animations.push_back(new LEDAnimation1(this, white, orange,  "White Flashes, orange background",  "LED.1.1"));
    animations.push_back(new LEDAnimation1(this, gold,  orange,  "Gold Flashes, orange background",   "LED.1.2"));
    animations.push_back(new LEDAnimation1(this, red,   black,   "Red flashes, Black background",     "LED.1.3"));
    animations.push_back(new LEDAnimation1(this, blue,  black,   "Blue flashes, Black background",    "LED.1.4"));
    animations.push_back(new LEDAnimation1(this, white, pink,    "White flashes, Pink background",    "LED.1.5"));
    animations.push_back(new LEDAnimation1(this, white, magenta, "White flashes, magenta background", "LED.1.6"));
    animations.push_back(new LEDAnimation1(this, white, cyan,    "White flashes, cyan background",    "LED.1.7"));
    animations.push_back(new LEDAnimation1(this, white, black,   "White flashes, Black background",   "LED.1.8"));
    animations.push_back(new LEDAnimation1(this, gold,  black,   "Gold Flashes, black background",    "LED.1.9"));

    this->activate_by_ID("LED.0.0");
}

DMX_vec LEDFixture::buffer(){
    return DMX_vec{this->MASTER_DIMMER, (uint8_t)(this->RGBout[R] >> 4), (uint8_t)(this->RGBout[G] >> 4), (uint8_t)(this->RGBout[B] >> 4)};
}

// Animation initializer
void LEDAnimation1::init(){
    BaseAnimation::init();
    for (int_vec::iterator per_it=periods_ms.begin(); per_it!=periods_ms.end(); per_it++){
        (*per_it) = 1000 * rand_min_max(MIN_T, MAX_T);
    }
}

/** Computes the RGB values to send to the led display based on : */
void LEDAnimation1::new_frame(){
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    //bool flash = animator.flash; //TOO remove variable flash --> not necessary
    bool flash_on = (sampler.state == BEAT) && (frame.t_current_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    int backgd_color[3];

    backgd_color[R] = (backgd_RGB_minmax[0] + backgd_RGB_minmax[1]) / 2 + (backgd_RGB_minmax[1] - backgd_RGB_minmax[0]) / 4 * (sin(2*M_PI*t_ms / periods_ms[0]) + sin(2*M_PI*t_ms / periods_ms[1]));
    backgd_color[G] = (backgd_RGB_minmax[2] + backgd_RGB_minmax[3]) / 2 + (backgd_RGB_minmax[3] - backgd_RGB_minmax[2]) / 4 * (sin(2*M_PI*t_ms / periods_ms[2]) - sin(2*M_PI*t_ms / periods_ms[3]));
    backgd_color[B] = (backgd_RGB_minmax[4] + backgd_RGB_minmax[5]) / 2 + (backgd_RGB_minmax[5] - backgd_RGB_minmax[4]) / 4 * (sin(2*M_PI*t_ms / periods_ms[4]) - sin(2*M_PI*t_ms / periods_ms[5]));

    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    if (flash_on)
    {
        fixture->RGBout[R] = backgd_color[R] + coef * (flash_RGB[R] - backgd_color[R]);
        fixture->RGBout[G] = backgd_color[G] + coef * (flash_RGB[G] - backgd_color[G]);
        fixture->RGBout[B] = backgd_color[B] + coef * (flash_RGB[B] - backgd_color[B]);
    }
    else
    {
        fixture->RGBout[R] = backgd_color[R];
        fixture->RGBout[G] = backgd_color[G];
        fixture->RGBout[B] = backgd_color[B];
    }
}

// TODO --> move into the LEDFixtureClass o that each Fixtures has its own override of the color function
DMX_vec LEDFixture::RGB(simpleColor c, uint8_t intensity){
    switch (c)
    {
    case black:
        return fcn::RGB_norm(DMX_vec{0,0,0}, intensity);
        break;
    case red:
        return fcn::RGB_norm(DMX_vec{255,0,0}, intensity);
        break;
    case green:
        return fcn::RGB_norm(DMX_vec{0,255,0}, intensity);
        break;
    case blue:
        return fcn::RGB_norm(DMX_vec{0,0,255}, intensity);
        break;
    case yellow:
        return fcn::RGB_norm(DMX_vec{255,63,0}, intensity);
        break;
    case orange:
        return fcn::RGB_norm(DMX_vec{255,20,0}, intensity);
        break;
    case sodium:
        return fcn::RGB_norm(DMX_vec{255,9,0}, intensity);
        break;
    case cyan:
        return fcn::RGB_norm(DMX_vec{0,153,255}, intensity);
        break;
    case purple:
        return fcn::RGB_norm(DMX_vec{139,0,255}, intensity);
        break;    
    case magenta:
        return fcn::RGB_norm(DMX_vec{255,0,186}, intensity);
        break;
    case pink:
        return fcn::RGB_norm(DMX_vec{255,0,71}, intensity);
        break;
    case white:
        return fcn::RGB_norm(DMX_vec{255,78,26}, intensity);
        break;
    case gold:
        return fcn::RGB_norm(DMX_vec{255,37,4}, intensity);
        break;
    default:
        break;
    }
}