#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "music.h"
#include "LED.h"

// background sinewave periods parameters
#define MAX_T 30
#define MIN_T 2

class AnimationManager{
    public :
    // real time color
    int rval, gval, bval;
    // animation color storage & other parameters
    int color1[3];
    int color2[6];
    int color3[3];
    int back_color[3];
    float coef = 0;
    unsigned long period[6];

    const int n_animation = 10;   //total number of animations available
    int animation_i = 0;        //index for the  animation being displayed currently

    unsigned long t_last_change_ms;   //timestamp of last switch between aniamtions
    bool time_to_change;            //true when it time has come to switch between animation


    bool flash = true;

    void update(unsigned int t_current, const SoundAnalyzer &music);

    /** Function that checks whether or not it is time to switch from animation i to animation i+1
     *  @param  music_state_changed : true when the music state juste changed (i.e. from BEAT to BREAK)
     *  @param  t : current frame timestamp
    */
    bool is_time_to_change(bool music_state_changed, unsigned long t);


    /**
     * 
    */
    void increment();

    /**
     * 
    */
    void reset_period();
    void set_color(int rgb[], int c0=0, int c1=0, int c2=0, int c3=0, int c4=0, int c5=0);
    void reser_period();
    void flash_master(bool, unsigned long, bool, int);
    void flash_master_BS(int);

};

extern AnimationManager animator;

#endif // !ANIMATOR_H