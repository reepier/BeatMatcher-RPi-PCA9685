#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "music.h"

class AnimationManager{
    public :
    const int n_animation = 10;   //total number of animations available
    int animation_i = 2;        //index for the  animation being displayed currently

    unsigned long t_last_change_ms;   //timestamp of last switch between aniamtions
    bool time_to_change;            //true when it time has come to switch between animation


    bool flash = true;

    void update(unsigned int t_current, const SoundAnalyzer &music);

    /** Function that checks whether or not it is time to switch from animation i to animation i+1
     *  @param  music_state_changed : true when the music state juste changed (i.e. from BEAT_TRACKING to BREAK)
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

};

extern AnimationManager animator;


#endif // !ANIMATOR_H

