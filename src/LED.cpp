#include <iostream>
#include <cmath>
#include <fstream>

#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/client/StreamingClient.h>
#include <wiringPi.h>

#include "constant.h"
#include "LED.h"
#include "sysfcn.h"

LEDFixture led(0, 4, "Led Bars");

// ------------------------------------------------------------
// LED FIXTURE CLASS Function definition

// Fixture initalizer
void LEDFixture::init(){
    animations.push_back(new LEDAnimation1(this, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Black", "LED.0.0"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 150 << 4, 80 << 4, 30 << 4, 100 << 4, 1 << 4, 7 << 4, 0 << 4, 0 << 4, "Warm White Flashes, Red/orange background", "LED.1.1"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 50 << 4, 10 << 4, 15 << 4, 50 << 4, 0 << 4, 5 << 4, 0 << 4, 0 << 4, "Sodium Flashes, Red/orange background", "LED.1.2"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, "Red flashes, Black background", "LED.1.3"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 150 << 4, 80 << 4, 30 << 4, 100 << 4, 0 << 4, 0 << 4, 0 << 4, 10 << 4, "Warm White flashes, Red/Pink background", "LED.1.4"));
    animations.push_back(new LEDAnimation1(this, 0 << 4, 0 << 4, 255 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, "Blue flashes, Black background", "LED.1.5"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 100 << 4, 80 << 4, 0 << 4, 80 << 4, 0 << 4, 0 << 4, 0 << 4, 20 << 4, "Warm White flashes, Pink background", "LED.1.6"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 100 << 4, 80 << 4, 0 << 4, 50 << 4, 0 << 4, 0 << 4, 0 << 4, 80 << 4, "Warm White flashes, Purple background", "LED.1.7"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 100 << 4, 80 << 4, 0 << 4, 20 << 4, 0 << 4, 0 << 4, 0 << 4, 100 << 4, "Warm White flashes, Blue/Purple backgroud", "LED.1.8"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 100 << 4, 80 << 4, 0 << 4, 10 << 4, 0 << 4, 10 << 4, 0 << 4, 100 << 4, "Warm White flashes, cyan background", "LED.1.9"));
    animations.push_back(new LEDAnimation1(this, 255 << 4, 100 << 4, 80 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, 0 << 4, "White flashes, Black background", "LED.1.10"));

    this->activate_by_ID("LED.0.0");

    
}

DMX_vec LEDFixture::buffer(){
    // balise(fcn::DMXvec_to_str({this->MASTER_DIMMER, (uint8_t)(this->RGB[R] >> 4), (uint8_t)(this->RGB[G] >> 4), (uint8_t)(this->RGB[B] >> 4)}).data());
    return DMX_vec{this->MASTER_DIMMER, (uint8_t)(this->RGB[R] >> 4), (uint8_t)(this->RGB[G] >> 4), (uint8_t)(this->RGB[B] >> 4)};
}



// ----------------------------------------------------------
// ANIMATION CLASS Function definition
// Animation constructor
LEDAnimation1::LEDAnimation1(LEDFixture* fix, int flash_r, int flash_g, int flash_b, int back_rmin, int back_rmax, int back_gmin, int back_gmax, int back_bmin, int back_bmax, std::string d, std::string i){
    this->fixture = fix;
    this->name = "Flash / Wavy Backgd";
    this->description = d;
    this->id = i;
    this->flash_RGB[R] = flash_r;
    this->flash_RGB[G] = flash_g;
    this->flash_RGB[B] = flash_b;

    this->backgd_RGB_minmax[0] = back_rmin;
    this->backgd_RGB_minmax[1] = back_rmax;
    this->backgd_RGB_minmax[2] = back_gmin;
    this->backgd_RGB_minmax[3] = back_gmax;
    this->backgd_RGB_minmax[4] = back_bmin;
    this->backgd_RGB_minmax[5] = back_bmax;
}

// Animation initializer
void LEDAnimation1::init(){
    this->frame_cpt = 0;
    this->t_animation_start_ms = millis();

    periods_ms[0] = 1000 * rand_min_max(MIN_T, MAX_T);
    periods_ms[1] = 1000 * rand_min_max(MIN_T, MAX_T);
    periods_ms[2] = 1000 * rand_min_max(MIN_T, MAX_T);
    periods_ms[3] = 1000 * rand_min_max(MIN_T, MAX_T);
    periods_ms[4] = 1000 * rand_min_max(MIN_T, MAX_T);
    periods_ms[5] = 1000 * rand_min_max(MIN_T, MAX_T);
}

/** Computes the RGB values to send to the led display based on : */
void LEDAnimation1::new_frame(){
    balise("compute new Led1 frame");
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;

    //bool flash = animator.flash; //TOO remove variable flash --> not necessary
    bool flash = (sampler.state == BEAT) && (frame.t_current_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    int backgd_color[3];

    backgd_color[R] = (backgd_RGB_minmax[0] + backgd_RGB_minmax[1]) / 2 + (backgd_RGB_minmax[1] - backgd_RGB_minmax[0]) / 4 * (sin(2 * 3.14 * t_ms / periods_ms[0]) + sin(2 * 3.14 * t_ms / periods_ms[1]));
    backgd_color[G] = (backgd_RGB_minmax[2] + backgd_RGB_minmax[3]) / 2 + (backgd_RGB_minmax[3] - backgd_RGB_minmax[2]) / 4 * (sin(2 * 3.14 * t_ms / periods_ms[2]) - sin(2 * 3.14 * t_ms / periods_ms[3]));
    backgd_color[B] = (backgd_RGB_minmax[4] + backgd_RGB_minmax[5]) / 2 + (backgd_RGB_minmax[5] - backgd_RGB_minmax[4]) / 4 * (sin(2 * 3.14 * t_ms / periods_ms[4]) - sin(2 * 3.14 * t_ms / periods_ms[5]));

    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    if (flash)
    {

        fixture->RGB[R] = backgd_color[R] + coef * (flash_RGB[R] - backgd_color[R]);
        fixture->RGB[G] = backgd_color[G] + coef * (flash_RGB[G] - backgd_color[G]);
        fixture->RGB[B] = backgd_color[B] + coef * (flash_RGB[B] - backgd_color[B]);
    }
    else
    {
        fixture->RGB[R] = backgd_color[R];
        fixture->RGB[G] = backgd_color[G];
        fixture->RGB[B] = backgd_color[B];
    }
}