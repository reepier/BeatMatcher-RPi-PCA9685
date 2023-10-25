#pragma once

#include <string>
#include <vector>

#include "debug.h"
#include "config.h"

#ifndef LINUX_PC
#include <PCA9685.h>
#endif

#include "animator.h"

#define LEDCh0 1

// PCA9685 channel (0-15) for each color
#define LEDRed 15
#define LEDGreen 14
#define LEDBlue 13

// background sinewave periods parameters
#define MAX_T 30
#define MIN_T 2

// Declare all the classes before defining them
class LEDFixture;
class LEDAnimation;
class LEDAnimation1;

// ------------------------------------
// LED Fixture ------------------------
// ------------------------------------

class LEDFixture : public BaseFixture
{
public:
  // Channels :
  int_vec RGBout = {0, 0, 0}; // = {R,G,B} Values from 0-4095 (12 bits PWM thanks to PCA9685)
  int nCH = 4;

  // Constructor & Initializer
  LEDFixture(int addr, int ch, std::string nm) : BaseFixture(addr, ch, nm){};
  void init();

  // Get functions
  int get_nCH() override { return this->nCH; };
  int get_address() override { return this->address; };
  std::vector<uint8_t> buffer() override;

  // Fixture specific Color Macros
  DMX_vec RGB(simpleColor, int intensity = 255) override;
};
extern LEDFixture led;

// ------------------------------------
// LED Animation ----------------------
// ------------------------------------

class LEDAnimation : public BaseAnimation
{
public:
  // NOTHING specific here for now
  LEDFixture *fixture;
};

/*Flash on beat and wavy background*/
class LEDAnimation1 : public LEDAnimation
{
public:
  // specific parameters
  int_vec flash_RGB = {0, 0, 0};                  // color components of the flash
  int_vec backgd_RGB_minmax = {0, 0, 0, 0, 0, 0}; // min/max components for the background oscilltions {Rmin, Rmax, Gmin, Gmax, Bmin, Bmax}
  int_vec periods_ms = {0, 0, 0, 0, 0, 0};        // periods of the background oscillations
  int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

  // Constructor
  LEDAnimation1(LEDFixture* f, simpleColor f_col, simpleColor b_col, std::string d, std::string i){
    this->fixture = f;
    this->description = d;
    this->id = i;

    this->flash_RGB = fcn::convert_8_to_12bits(this->fixture->RGB(f_col, -1));
    int_vec back_RGB = fcn::convert_8_to_12bits(this->fixture->RGB(b_col, 35));
    double c_min = 0.7, c_max = 1.3;
    this->backgd_RGB_minmax = {(int)(c_min*back_RGB[R]), (int)(c_max*back_RGB[R]), (int)(c_min*back_RGB[G]), (int)(c_max*back_RGB[G]), (int)(c_min*back_RGB[B]), (int)(c_max*back_RGB[B])};

    this->update_colors_used(color_vec{f_col, b_col});
  }

  void init() override;      // initializes/reset what needs to be (initial and/or random values, etc.)
  void new_frame(); // computes the new frame's RGB values
};
