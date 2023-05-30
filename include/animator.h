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

// Declare all the classes before defining them
class AnimationManager;
class BaseFixture;
class BaseAnimation;



/**
 * class AnimationManager is the entity responsible for determining which animation every 
 * fixture should run, based on the musical analysis
*/
class AnimationManager{
    public :
    bool flash = true;
    
    int animation_i = 0;                          //index for the  animation being displayed currently

    unsigned long t_last_change_ms = millis();   //timestamp of last switch between aniamtions


    void update(unsigned int t_current, const SoundAnalyzer &music);
};

// Generic (core) description of a fixture (later derived into specific classes)
class BaseFixture{
  public:
    // Generic attributes
    std::string name;
    std::string description;            //textual description
    int id;                             //unique id 

    // Output channels
    uint8_t MASTER_DIMMER = 255;    // Master Dimmer from 0-255

    // Animations
    BaseAnimation * active_animation = nullptr;
    std::vector<BaseAnimation> animations;
};


// Generic (core) description of an animation object
class BaseAnimation{
  public :
    std::string name;
    std::string description;            //textual description
    int id;                             //unique id 
    unsigned long t_animation_start_ms; //times at which the animation was last activated
    unsigned long frame_cpt;            //number of frame computed since activation

    BaseFixture * parent_fixture = nullptr;

    BaseAnimation * get_ptr(){return this;}

    // virtual void activate();
    // virtual void new_frame();

};


extern AnimationManager animator;