

class Animator{
    public :
    
    int n_animation = 10;   //total number of animations available
    int animation_i;        //index for the  animation being displayed currently

    unsigned long t_last_change_ms;   //timestamp of last switch between aniamtions
    bool time_to_change;            //true when it time has come to switch


void update(unsigned int t_current, const SoundAnal);


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