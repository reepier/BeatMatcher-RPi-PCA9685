#pragma once

#include <PCA9685.h>
#include <string>
#include <vector>


#define LEDCh0      1

// PCA9685 channel (0-15) for each color
#define LEDRed    15
#define LEDGreen  14
#define LEDBlue   13






/**class prototype*/
class LEDAnimation : public BaseAnimation{
  public: 
    // specific args and parameters
    int flash_RGB[3] = {0,0,0};                 // color components of the flash
    int backgd_RGB_minmax[6] = {0,0,0,0,0,0};           // min/max components for the background oscilltions {0 Rmin, 1 Rmax, 2 Gmin, 3 Gmax, 4 Bmin, 5 Bmax}
    int periods_ms[6] = {0,0,0};                  // periods of the background oscillations
    int fade_rate = 60;                 //ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)          

    // Constructor
    LEDAnimation(int, int, int, int, int, int ,int, int, int, std::string);

    void init();                // initializes/reset what needs to be (initial and/or random values, etc.)
    std::vector<int> new_frame(unsigned long, unsigned long, bool);   // computes the new frame's RGB values

    void display_anim();    // dipslay animation paramters and settings

    LEDAnimation* get_ptr();    // simply returns a pointer to the object

};


class LEDFixture : public BaseFixture{
  public :
    // Channels :
    uint8_t MASTER_DIMMER = 255;    // Master Dimmer from 0-255
    std::vector<int> RGB = {0,0,0};               // = {R,G,B} Values from 0-4095

    // Hardware interface (PCA9685)
    int fd;
    int addr = 0x40;
    unsigned int setOnVals[_PCA9685_CHANS] =
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    unsigned int setOffVals[_PCA9685_CHANS] =
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // Hardware interface (OLA) --> to be implemented


    // Animations
    LEDAnimation * active_animation = nullptr;  // points towards the animation currently running
    std::vector<LEDAnimation> animation;        // stores the parameters or every (manually) pre-defined animation 

    void LED_init();
    void send();
    void display_anim();
};

extern LEDFixture led;