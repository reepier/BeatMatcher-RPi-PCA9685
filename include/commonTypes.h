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
    sodium,    //RGBW(255,10??,0,0)  --> deep orange, very red
    orange,
    yellow,
    gold,
    w_white,      // warmish white (defined by the spots)
    c_white,     // cold flat white
    cyan,       
    blue,
    purple,
    magenta,
    pink,
    green,
    sevika_pink,
    hextech_cyan,
    shimmer_purple,
    last_color
};
const std::vector<std::string> colorName = {
    "Black",
    "Red",
    "Sodium",
    "Orange",
    "Yellow",
    "Gold",
    "White",
    "Cyan",
    "Blue",
    "Purple",
    "Magenta",
    "Pink",
    "Green",
    "Sevika Pink",
    "Hextech Cyan",
    "Shimmer Purple"};

enum Shape{
    square,
    sinus,
    sinus2,
    triangle,
    gaussian,
    gaussian2,
    saw       
};

enum AnimationType{
    leader,
    backer,
    any
};

struct Flash{   // stores : color (simpleColor) and the timestamp (time_ms) of a flash (or any resembling event)
    simpleColor color;
    time_t time;
};

// different types of commonly used vectors
typedef std::vector<simpleColor>    color_vec;
typedef std::vector<uint8_t>        DMX_vec;  //a vector of 8bit int with values ranging from 0 to 255
typedef std::vector<int>            int_vec;  //a vector of standard int
typedef std::vector<uint8_t>        uint8_vec;
typedef std::vector<unsigned long>  t_vec;
typedef std::vector<std::string>    str_vec;
typedef std::vector<Flash>          flash_vec;      //a vector of n Flash
typedef std::vector<DMX_vec>        pixel_vec;
typedef DMX_vec                     pixel;


  // Declare all the classes before defining them
class AnimationManager;   //TODO move this in a sceno.h and rename this module baseFixture.h & baseAnimation.h
class BaseFixture;        //TODO move this in baseFixture.h
class BaseAnimation;      //TODO move this in baseAnimation.h

typedef std::vector<BaseFixture*> fix_vec;
typedef std::vector<BaseAnimation*> anim_vec;
