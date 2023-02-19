#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "music.h"
#include "LED.h"

// background sinewave periods parameters
#define MAX_T 30
#define MIN_T 2

// indexes for ease of reading --> write { color[R] = ... }  instead of { color[0] = ... } 
#define R 0
#define G 1
#define B 2


/**
 * class AnimationManager is the entity responsible for determining which animation every 
 * fixture should run, based on the musical analysis
*/
class AnimationManager{
    public :
    // TODO remove
    // real time color
    // int rval, Gval, Bval;

    //TODO remove
    // animation color storage & other parameters
    // int flash_RGB[3];     
    // int backgd_RGB_minmax[6];          // {0 Rmin, 1 Rmax, 2 Gmin, 3 Gmax, 4 Bmin, 5 Bmax}
    // int backgd_color[3];
    bool flash = true;

    // float coef = 0;
    // unsigned long periods[6];    // // random frequencis (periods) for color sine wave: {0 Rf1, 1 Rf2, 2 Gf1, 3 Gf2, 4 Bf1, 5 Bf2}

    const int n_animation = 10;     //total number of animations available
    int animation_i = 0;            //index for the  animation being displayed currently

    unsigned long t_last_change_ms;   //timestamp of last switch between aniamtions


    void update(unsigned int t_current, const SoundAnalyzer &music);


    // void reset_period();    // todo move to LEDanimtion::init()
    void set_color(int rgb[], int c0=0, int c1=0, int c2=0, int c3=0, int c4=0, int c5=0);  //todo move to LEDFixture::ainmation data structure
    void reser_period();
    void flash_master(unsigned long, unsigned long, bool, int);
    void flash_master_BS(int);

};

extern AnimationManager animator;

#endif // !ANIMATOR_H