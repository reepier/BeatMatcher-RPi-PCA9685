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
  int_vec RGB = {0, 0, 0}; // = {R,G,B} Values from 0-4095 (12 bits PWM thanks to PCA9685)
  int nCH = 4;


  LEDFixture(int addr, int ch, std::string nm) : BaseFixture(addr, ch, nm){};
  void init();

  int get_nCH() override { return this->nCH; };
  int get_address() override { return this->address; };
  std::vector<uint8_t> buffer() override;
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
  int_vec backgd_RGB_minmax = {0, 0, 0, 0, 0, 0}; // min/max components for the background oscilltions {0 Rmin, 1 Rmax, 2 Gmin, 3 Gmax, 4 Bmin, 5 Bmax}
  int_vec periods_ms = {0, 0, 0, 0, 0, 0};        // periods of the background oscillations
  int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

  // Constructor
  LEDAnimation1(LEDFixture*, int, int, int, int, int, int, int, int, int, std::string, std::string);
  LEDAnimation1(LEDFixture* fix, DMX_vec flash_rgb, DMX_vec bkgd_rgb_min_max, std::string d, std::string i);

  void init() override;      // initializes/reset what needs to be (initial and/or random values, etc.)
  void new_frame(); // computes the new frame's RGB values
};
