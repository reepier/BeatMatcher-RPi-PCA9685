#pragma once

#include <wiringPi.h>
#include <string>
#include <cmath>

#include "music.h"
// #include "LED.h"

// Common Datatypes
  // indexes for ease of reading --> write { color[R] = ... }  instead of { color[0] = ... } 
  #define R 0
  #define G 1
  #define B 2
  #define W 3

  enum SimpleColor{
    black   =0,
    red     =1,
    green   =2,
    blue    =3,
    yellow  =4,
    cyan    =5,
    magenta =6,
    white   =7
  };
  enum Shape{
      square,
      sinus,
      triangle,
      gaussian,
      saw
  };
  
  typedef std::vector<uint8_t>  DMX_vec;  //a vector of 8bit int with values ranging from 0 to 255
  typedef std::vector<int>      int_vec;  //a vector of standard int 

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
    virtual DMX_vec buffer() = 0;
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
// TODO --> tailor these functions specifically for each fixture ! in the <fixture>.cpp
namespace fcn{
  // returns a 4 (or 3 for RGB) channel DMX vector based on color literal (unnormalized --> full 255)
  DMX_vec RGBW(SimpleColor);
  DMX_vec RGB(SimpleColor);


  // returns a NORMALIZED 4 (or 3 for RGB) channel DMX vector based on a DMX_vector and a DMX vlue (0-255)
  DMX_vec RGBW_norm(DMX_vec, uint8_t);
  DMX_vec RGB_norm(DMX_vec, uint8_t);
}