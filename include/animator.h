#pragma once

#include <wiringPi.h>
#include <string>
#include <cmath>

#include "sysfcn.h"
#include "music.h"
// #include "LED.h"

// Common Datatypes
  // indexes for ease of reading --> write { color[R] = ... }  instead of { color[0] = ... } 
  #define R 0
  #define G 1
  #define B 2
  #define W 3

  enum SimpleColor{
    black=0,
    red,
    green,
    blue,
    yellow,
    orange,
    sodium,    //RGBW(255,10??,0,0)  --> deep orange, very red
    cyan,
    purple,
    magenta,
    pink,
    white,
    gold,     //RGBW(255,40,0,100 ) --> Orange + White
    last_color
  };
  const std::vector<std::string> colorName = {"Black", "Red", "Green", "Blue", 
                                      "Yellow", "Orange", "Sodium",
                                      "Cyan", "Purple", "Magenta", "Pink", "White",
                                      "Gold"};
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
class AnimationManager;   //TODO move this in a sceno.h and rename this module baseFixture.h & baseAnimation.h

class BaseFixture;        //TODO move this in baseFixture.h
class BaseAnimation;      //TODO move this in baseAnimation.h

typedef std::vector<BaseFixture*> fix_vec;
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
    const int nCH;

    // Animations
    BaseAnimation * active_animation = nullptr;
    std::vector<BaseAnimation*> animations;

    //constructor (adresse [0-511], number of channels, fixture's name)
    BaseFixture(int addr,int ch, std::string nm): address(addr), nCH(ch), name(nm){};
    virtual void init()=0;

    //animation management
    void blackout(bool);
    void activate_random();
    bool activate_by_ID(std::string);

    //DMX output
    virtual int get_address() = 0;
    virtual int get_nCH()     = 0;
    virtual DMX_vec buffer()  = 0;
};


// Generic (core) description of an animation object
class BaseAnimation{
  public :
    std::string name;                   
    std::string description;            // textual description
    std::string id;                     // unique id 
    unsigned long t_animation_start_ms; // times at which the animation was last activated
    unsigned long frame_cpt;            // number of frame computed since activation


    virtual void new_frame(){
      this->frame_cpt++;
    }
    virtual void init(){
      this->t_animation_start_ms = frame.t_current_ms;
      this->frame_cpt = 0;
    };

};


extern AnimationManager animator;


// -----------------------------------
// USEFULL FUNCTIONS
// -----------------------------------
// TODO --> tailor these functions specifically for each fixture ! in the <fixture>.cpp
namespace fcn{
  // returns a normalized 4 (or 3 for RGB) channel DMX vector based on color literal
  DMX_vec RGBW(SimpleColor, uint8_t intensity = 255);
  DMX_vec RGB(SimpleColor, uint8_t intensity = 255);
  #define RED(x) fcn::RGBW(red,x)
  #define GREEN(x) fcn::RGBW(green,x)
  #define BLUE(x) fcn::RGBW(blue,x)
  #define YELLOW(x) fcn::RGBW(yellow,x)
  #define ORANGE(x) fcn::RGBW(orange,x)
  #define SODIUM(x) fcn::RGBW(sodium,x)
  #define PURPLE(x) fcn::RGBW(purple,x)
  #define MAGENTA(x) fcn::RGBW(magenta,x)
  #define PINK(x) fcn::RGBW(pink,x)
  #define CYAN(x) fcn::RGBW(cyan,x)
  #define GOLD(x) fcn::RGBW(gold,x)
  #define WHITE(x) fcn::RGBW(white,x)
  #define BLACK fcn::RGBW(black)
  
  // returns a NORMALIZED 4 (or 3 for RGB) channel DMX vector based on a DMX_vector and a DMX vlue (0-255)
  DMX_vec RGBW_norm(DMX_vec, uint8_t intensity=255);
  DMX_vec RGB_norm(DMX_vec, uint8_t intensity=255);
  std::string DMXvec_to_str(DMX_vec, char);
  std::string num_to_str(int);
  std::string num_to_str(uint8_t);
  std::string num_to_str(double);
  int_vec convert_8_to_12bits(DMX_vec);
}