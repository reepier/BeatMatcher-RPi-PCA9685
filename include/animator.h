#pragma once

#include <wiringPi.h>
#include <string>
#include <cmath>

#include "music.h"
// #include "LED.h"





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
    
    unsigned long t_last_change_ms = millis();   //timestamp of last switch between aniamtions
    
    void update();
    bool test_animation();
};

// Generic (core) description of a fixture (later derived into specific classes)
class BaseFixture{
  public:
    // Generic attributes
    std::string name;                   // 
    std::string description;            // textual description
    std::string id;                     // unique id 

    // DMX related parameters
    uint8_t MASTER_DIMMER = 255;    // Master Dimmer from 0-255
    int address;                    // DMX address
    bool b_blackout;
    int nCH;

    // Animations
    BaseAnimation * active_animation = nullptr;
    std::vector<BaseAnimation*> animations;

    //constructor
    BaseFixture(int addr): address(addr){};
    virtual void init()=0;

    //animation management
    void blackout(bool);
    void activate_random();
    bool activate_by_ID(std::string);

    //DMX output
    virtual std::vector<uint8_t> buffer() = 0;
};


// Generic (core) description of an animation object
class BaseAnimation{
  public :
    std::string name;                   
    std::string description;            // textual description
    std::string id;                     // unique id 
    unsigned long t_animation_start_ms; // times at which the animation was last activated
    unsigned long frame_cpt;            // number of frame computed since activation


    virtual void new_frame() = 0;
    virtual void init() = 0;

};


extern AnimationManager animator;


// -----------------------------------
// USEFULL FUNCTIONS
// -----------------------------------
// TODO
