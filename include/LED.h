#pragma once

#include <PCA9685.h>
#include <string>
#include <vector>

#include <ola/DmxBuffer.h>
#include <ola/client/StreamingClient.h>

#include "animator.h"


#define LEDCh0      1

// PCA9685 channel (0-15) for each color
#define LEDRed    15
#define LEDGreen  14
#define LEDBlue   13

// Declare all the classes before defining them
class LEDFixture;
class LEDAnimation;
class Flash_Back;

class LEDFixture : public BaseFixture{
  public :
    // Channels :
    std::vector<int> RGB = {0,0,0};               // = {R,G,B} Values from 0-4095

    // Hardware interface (PCA9685)
    int fd;
    int addr = 0x40;
    unsigned int setOnVals[_PCA9685_CHANS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    unsigned int setOffVals[_PCA9685_CHANS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // Hardware interface (OLA)
    ola::client::StreamingClient ola_client;
    ola::DmxBuffer ola_buffer;

    // Animations
    // Flash_Back * active_animation = nullptr;  // points towards the animation currently running
    // std::vector<Flash_Back> animations;        // stores the parameters or every (manually) pre-defined animation 

    void LED_init();
    void send();
    void display_anim();
};


class LEDAnimation : public BaseAnimation{
  // NOTHING specific here for now
};

/**Final animation class*/
class Flash_Back : public LEDAnimation{
  public: 
    // specific args and parameters
    int flash_RGB[3] = {0,0,0};                 // color components of the flash
    int backgd_RGB_minmax[6] = {0,0,0,0,0,0};           // min/max components for the background oscilltions {0 Rmin, 1 Rmax, 2 Gmin, 3 Gmax, 4 Bmin, 5 Bmax}
    int periods_ms[6] = {0,0,0,0,0,0};                  // periods of the background oscillations
    int fade_rate = 60;                 //ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)          

    // Constructor
    Flash_Back(int, int, int, int, int, int ,int, int, int, std::string);

    void init();                // initializes/reset what needs to be (initial and/or random values, etc.)
    std::vector<int> new_frame(unsigned long, unsigned long, bool);   // computes the new frame's RGB values

    void display_anim();    // dipslay animation paramters and settings

    Flash_Back* get_ptr();    // simply returns a pointer to the object

};

extern LEDFixture led;

