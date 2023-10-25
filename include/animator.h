#pragma once

#include <wiringPi.h>
#include <string>
#include <sstream>
#include <cmath>

#include "commonTypes.h"
#include "debug.h"
#include "sysfcn.h"
#include "music.h"
// #include "LED.h"


/**
 * class AnimationManager is the entity responsible for determining which animation every 
 * fixture should run, based on the musical analysis
*/
class AnimationManager{
    public :
    bool flash = true;
    
    unsigned long t_last_change_ms = millis();   //timestamp of last switch between aniamtions
    
    void random_update();
    void palette_update();
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
    anim_vec animations;

    //constructor (adresse [0-511], number of channels, fixture's name)
    BaseFixture(int addr,int ch, std::string nm): address(addr), nCH(ch), name(nm){};
    virtual void init()=0;

    //animation management
    void blackout(bool);
    bool activate_none();
    bool activate_by_index(int);
    bool activate_random();
    bool activate_by_ID(std::string);
    bool activate_by_color(color_vec);

    //DMX output
    virtual int get_address() = 0;
    virtual int get_nCH()     = 0;
    virtual DMX_vec buffer()  = 0;

    virtual DMX_vec RGBW(simpleColor, int){}; // common (but overriden) function that returns a 4 RGBW vector based on standrad color input
    virtual DMX_vec RGB(simpleColor, int){};
};


// Generic (core) description of an animation object
class BaseAnimation{
  public :
    std::string name;                   
    std::string description;            // textual description
    std::string id;                     // unique id 
    unsigned long t_animation_start_ms; // times at which the animation was last activated
    unsigned long frame_cpt;            // number of frame computed since activation
    color_vec color_palette;              // lists the colors used in the animation (initialized by constructor)
    
    bool      is_monochrome(){return (color_palette.size() == 1);};
    
    virtual void new_frame(){
      this->frame_cpt++;
    }
    virtual void init(){
      this->t_animation_start_ms = frame.t_current_ms;
      this->frame_cpt = 0;
    };
    void update_colors_used(color_vec colors){
      for (color_vec::iterator new_c = colors.begin(); new_c != colors.end(); new_c++){
        // check if new color is not already stored in color_palette
        bool duplicate = false;
        for (color_vec::iterator stored_c = color_palette.begin(); stored_c != color_palette.end(); stored_c++){
          if ((*new_c) == (*stored_c)){
            duplicate = true;
          }
        }
        if ( (*new_c) != black && !duplicate){
          this -> color_palette.push_back((*new_c));
        }
      }
    }
    void update_colors_used(simpleColor color){
      update_colors_used(color_vec{color});
    }
};

extern AnimationManager animator;


/** -----------------------------------
  ______                _   _                 
 |  ____|              | | (_)                
 | |__ _   _ _ __   ___| |_ _  ___  _ __  ___ 
 |  __| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 | |  | |_| | | | | (__| |_| | (_) | | | \__ \
 |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
-----------------------------------                 */
// TODO --> tailor these functions specifically for each fixture ! in the <fixture>.cpp
namespace fcn{
  /* returns a normalized 4 (or 3 for RGB) channel DMX vector based on color literal 
  if intensity = -1, the normalization is disabled*/
  // DMX_vec RGBW(simpleColor, uint8_t intensity = 255);
  // DMX_vec RGB(simpleColor, uint8_t intensity = 255);
  // #define RED(x) fcn::RGBW(red,x)
  // #define GREEN(x) fcn::RGBW(green,x)
  // #define BLUE(x) fcn::RGBW(blue,x)
  // #define YELLOW(x) fcn::RGBW(yellow,x)
  // #define ORANGE(x) fcn::RGBW(orange,x)
  // #define SODIUM(x) fcn::RGBW(sodium,x)
  // #define PURPLE(x) fcn::RGBW(purple,x)
  // #define MAGENTA(x) fcn::RGBW(magenta,x)
  // #define PINK(x) fcn::RGBW(pink,x)
  // #define CYAN(x) fcn::RGBW(cyan,x)
  // #define GOLD(x) fcn::RGBW(gold,x)
  // #define WHITE(x) fcn::RGBW(white,x)
  // #define BLACK fcn::RGBW(black)
  
  // returns a NORMALIZED 4 (or 3 for RGB) channel DMX vector based on a DMX_vector and a DMX vlue (0-255)
  DMX_vec RGBW_norm(DMX_vec, int intensity=255);
  DMX_vec RGB_norm(DMX_vec, int intensity=255);
  
  std::string vec_to_str(DMX_vec, char);
  std::string vec_to_str(int_vec, char);
  std::string vec_to_str(str_vec, char);

  std::string num_to_str(int);
  std::string num_to_str(uint8_t);
  std::string num_to_str(double);
  int_vec convert_8_to_12bits(DMX_vec);

  /*shape functions*/
  // TODO maybe just implement a function for each shape (gaussian(), square(), saw()...)

  // SINGLE BURSTS
  // pure gaussian shape -> exp(-x²/2)
  inline double gaussian(time_ms t, time_ms t0, time_ms period, double min, double max){
      double sigma = period/3.0;
      return min + (max-min)*std::exp( -std::pow((t-t0)/sigma, 2)/2 );
  }
  // squared gaussian shape -> exp(-x⁴/4) (longer plateau, steeper slopes)
  inline double gaussian2(time_ms t, time_ms t0, time_ms period, double min, double max){ 
    double sigma = period/3.0;
    return min + (max-min)*std::exp( -std::pow((t-t0)/sigma, 4)/4 );
  }
  inline double square(time_ms t, time_ms t0, time_ms period, double min, double max, double alpha=0.5){
    if ( t > t0-alpha*period  &&  t < t0+(1-alpha)*period ) {return max;}
    else {return min;}
  }
  inline double triangle(time_ms t, time_ms t0, time_ms period, double min, double max, double alpha=0.5){
    if ( t0-alpha*period < t  &&  t < t0  )         {return (double)map((double)t, t0-alpha*period, (double)t0,           min, max);}  
    else if (t0 < t  &&  t < t0+(1-alpha)*period )  {return (double)map((double)t, (double)t0,      t0+(1-alpha)*period,  max, min);}
    else {return min;}
  }

  // PERIODIC FUNCTIONS
  //sine wave
  inline double sin_wave(time_ms t, time_ms period, double min, double max, double phase = 0){
    return (max+min)/2 + (max-min)/2*std::sin(2*M_PI*t/period + phase);
  }
  //triangular wave
  inline double triangle_wave(time_ms t, time_ms period, double min, double max, double alpha = 0.5, double phase = 0){
    if (alpha>1.0){alpha = 1.0;}
    else if (alpha < 0.0){alpha = 0.0;}

    double t_prime = (t+phase/2.0/M_PI*period) / period;
    t_prime = t_prime - (int)t_prime;

    if (t_prime<alpha)  {return (double)map(t_prime, 0.0, alpha, min, max);}
    else                {return (double)map(t_prime, alpha, 1.0, max, min);}
  }
  //square wave
  inline double square_wave(time_ms t, time_ms period, double min, double max, double alpha = 0.5, double phase = 0){
    if (alpha>1.0){alpha = 1.0;}
    else if (alpha < 0.0){alpha = 0.0;}

    double t_prime = (t+phase/2.0/M_PI*period) / period;
    t_prime = t_prime - (int)t_prime;

    if (t_prime<alpha)  {return min;}
    else                {return max;}
  }

  // random generation functions
  template<class T>
  T random_pick(std::vector<T> vals, int_vec proba_vec = {}){
    int n = vals.size();

    if (n == 0){
      // log(1, "Empty list of values");
      return (T)0;
    }
    else if (n==1) {
      // log(1, "Single value passed");
      return vals[0];
    }

    if (proba_vec.size() == 0){
      // log(1, "No probability passed --> equipr.");
      proba_vec.resize(n, 1); // if proba is not passed as an argument, default to equiprobability
    }else if (proba_vec.size() != n){ // if proba vector does not match value vector in size, return & log.
      // log(1, "Proba size differs from vals size !!");
      return (T)0;
    }

    int proba_sum = 0;
    for (int i=0; i<proba_vec.size(); i++){
      proba_sum += proba_vec[i];
    }
    
    int_vec proba_scale = {proba_vec[0]};
    for (int i=1; i<n; i++){
      proba_scale.push_back(proba_scale[i-1] + proba_vec[i]);
    }
    int pick = rand_min_max(0, proba_sum);

    for (int i=0; i<n; i++){
      if (pick < proba_scale[i]){
        // log(2, "proba_sum:", proba_sum," pick:", pick, " clor:", colorName[(int)vals[i]]);
        return vals[i];
      }
    }

    return (T)0;    //TODO bellec ce casting est bancale AF
  }
}