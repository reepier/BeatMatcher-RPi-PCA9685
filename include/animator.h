#pragma once

#include <wiringPi.h>
#include <string>

#include "music.h"
// #include "LED.h"

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
    bool flash = true;
    
    int animation_i = 0;            //index for the  animation being displayed currently

    unsigned long t_last_change_ms = millis();   //timestamp of last switch between aniamtions


    void update(unsigned int t_current, const SoundAnalyzer &music);
};

// Generic (core) description of an animation object
class BaseAnimation{
  public :
    std::string description;
    int id;
    unsigned long t_animation_start_ms;
};

class BaseFixture{

};

extern AnimationManager animator;