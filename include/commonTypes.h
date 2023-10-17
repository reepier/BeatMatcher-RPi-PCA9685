#pragma once

#include <vector>
#include <string>

// indexes for ease of reading --> write { color[R] = ... }  instead of { color[0] = ... } 
#define R 0
#define G 1
#define B 2
#define W 3

// Common Datatypes
typedef unsigned long time_ms;

enum simpleColor{
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
    sinus2,
    triangle,
    gaussian,
    gaussian2,
    saw       
};

typedef std::vector<simpleColor>    color_vec;
typedef std::vector<uint8_t>        DMX_vec;  //a vector of 8bit int with values ranging from 0 to 255
typedef std::vector<int>            int_vec;  //a vector of standard int
typedef std::vector<unsigned long>  t_vec;
typedef std::vector<std::string>    str_vec;

  // Declare all the classes before defining them
class AnimationManager;   //TODO move this in a sceno.h and rename this module baseFixture.h & baseAnimation.h
class BaseFixture;        //TODO move this in baseFixture.h
class BaseAnimation;      //TODO move this in baseAnimation.h

typedef std::vector<BaseFixture*> fix_vec;
typedef std::vector<BaseAnimation*> anim_vec;