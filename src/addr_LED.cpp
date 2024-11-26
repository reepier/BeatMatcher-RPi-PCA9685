#include <algorithm>

using namespace std;

#include "addr_LED.h"

AddressableLED addr_led(1, 0, 3*NUM_PIX, "LEDs", 1, 180);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */


void AddressableLED::init(){
    // declare animations here
    animations.push_back(new AddrLEDAnimation1(this, black,  black,  " ",    "PIX.0.0", backer));

// ---MAXIMUM CONFIGURATION------------------

// 0. Constant background color
#if SHOW_INTENSITY==0 or SHOW_INTENSITY==1
    animations.push_back(new AddrLEDAnimation1(this, red,    red,     "red background",    "PIX.0.1", backer, false));
    animations.push_back(new AddrLEDAnimation1(this, blue,   blue,    "blue background",   "PIX.0.2", backer, false));
    animations.push_back(new AddrLEDAnimation1(this, purple, purple,  "purple background", "PIX.0.3", backer, false));
    animations.push_back(new AddrLEDAnimation1(this, cyan,   cyan,    "cyan background",   "PIX.0.4", backer, false));
#endif
// 1. FLASH ON BEAT
    // Original BEATMATCHER Flashes (all bar flashing)
#if SHOW_INTENSITY==0 or SHOW_INTENSITY==1
    animations.push_back(new AddrLEDAnimation1(this, red,      black, "red flashes",      "PIX.1.0.1", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, blue,     black, "blue flashes",     "PIX.1.0.2", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, purple,   black, "purple flashes",   "PIX.1.0.3", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, gold,     black, "gold flashes",     "PIX.1.0.4", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, sodium,   black, "sodium flashes",   "PIX.1.0.5", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     black, "cyan flashes",     "PIX.1.0.6", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, w_white,  black, "w_white flashes",  "PIX.1.0.7", leader, 1));
    animations.push_back(new AddrLEDAnimation1(this, c_white,  black, "c_white flashes",  "PIX.1.0.8", leader, 1));
#endif

    // Randomized Analog flashes (exponential decay), 75% of bars
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 2
    // Flashes, no backgound
    animations.push_back(new AddrLEDAnimation1(this, red,     black,  bar, 0.6,   "red Flashes",     "PIX.1.1.1", leader));
    animations.push_back(new AddrLEDAnimation1(this, blue,    black,  bar, 0.6,   "blue Flashes",    "PIX.1.1.2", leader));
    animations.push_back(new AddrLEDAnimation1(this, purple,  black,  bar, 0.6,   "purple Flashes",  "PIX.1.1.3", leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,    black,  bar, 0.6,   "gold Flashes",    "PIX.1.1.4", leader));
    animations.push_back(new AddrLEDAnimation1(this, sodium,  black,  bar, 0.6,   "sodium Flashes",  "PIX.1.1.5", leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,    black,  bar, 0.6,   "cyan Flashes",    "PIX.1.1.6", leader));
    animations.push_back(new AddrLEDAnimation1(this, w_white, black,  bar, 0.6,   "w_white Flashes", "PIX.1.1.7", leader));
    animations.push_back(new AddrLEDAnimation1(this, c_white, black,  bar, 0.6,   "c_white Flashes", "PIX.1.1.8", leader));
    //Flashes with backgd
    animations.push_back(new AddrLEDAnimation1(this, gold,     red,     bar, 0.6,   "gold Flashes, red backgd",         "PIX.1.1.9",   leader));
    animations.push_back(new AddrLEDAnimation1(this, w_white,  red,     bar, 0.6,   "w_white Flashes, red backgd",      "PIX.1.1.10",  leader));
    animations.push_back(new AddrLEDAnimation1(this, c_white,  red,     bar, 0.6,   "c_white Flashes, red backgd",      "PIX.1.1.11",  leader));
    animations.push_back(new AddrLEDAnimation1(this, gold,     purple,  bar, 0.6,   "gold Flashes, purple backgd",      "PIX.1.1.12",  leader));
    animations.push_back(new AddrLEDAnimation1(this, w_white,  purple,  bar, 0.6,   "w_white Flashes, purple backgd",   "PIX.1.1.13",  leader));
    animations.push_back(new AddrLEDAnimation1(this, c_white,  purple,  bar, 0.6,   "c_white Flashes, purple backgd",   "PIX.1.1.14",  leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     red,     bar, 0.6,   "cyan Flashes, red backgd",         "PIX.1.1.15",  leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     purple,  bar, 0.6,   "cyan Flashes, purple backgd",      "PIX.1.1.16",  leader));
    animations.push_back(new AddrLEDAnimation1(this, w_white,  blue,    bar, 0.6,   "w_white Flashes, blue backgd",     "PIX.1.1.17",  leader));
    animations.push_back(new AddrLEDAnimation1(this, c_white,  blue,    bar, 0.6,   "c_chite Flashes, blue backgd",     "PIX.1.1.18",  leader));
    animations.push_back(new AddrLEDAnimation1(this, cyan,     blue,    bar, 0.6,   "cyan Flashes, blue backgd",        "PIX.1.1.19",  leader));
    animations.push_back(new AddrLEDAnimation1(this, red,      blue,    bar, 0.6,   "red Flashes, blue backgd",         "PIX.1.1.20",  leader));    
    animations.push_back(new AddrLEDAnimation1(this, blue,     red,     bar, 0.6,   "blue Flashes, red backgd",         "PIX.1.1.21",  leader));    
#endif

    // Randomized Digital Beat with led bars
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 3
    // Flashes, no backgound
    animations.push_back(new AddrLEDAnimation2(this, red,     black,  bar,   "red Flashes",     "PIX.1.2.1", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, blue,    black,  bar,   "blue Flashes",    "PIX.1.2.2", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, purple,  black,  bar,   "purple Flashes",  "PIX.1.2.3", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, gold,    black,  bar,   "gold Flashes",    "PIX.1.2.4", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, sodium,  black,  bar,   "sodium Flashes",  "PIX.1.2.5", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,    black,  bar,   "cyan Flashes",    "PIX.1.2.6", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white, black,  bar,   "w_white Flashes", "PIX.1.2.7", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white, black,  bar,   "c_white Flashes", "PIX.1.2.8", leader, 1));
    //Flashes with backgd
    animations.push_back(new AddrLEDAnimation2(this, gold,     red,      bar,   "gold Flashes, red backgd",       "PIX.1.2.9", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white,  red,      bar,   "w_white Flashes, red backgd",    "PIX.1.2.10", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white,  red,      bar,   "c_white Flashes, red backgd",    "PIX.1.2.11", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, gold,     purple,   bar,   "gold Flashes, purple backgd",    "PIX.1.2.12", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white,  purple,   bar,   "w_white Flashes, purple backgd", "PIX.1.2.13", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white,  purple,   bar,   "c_white Flashes, purple backgd", "PIX.1.2.14", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,     red,      bar,   "cyan Flashes, red backgd",       "PIX.1.2.15", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,     purple,   bar,   "cyan Flashes, purple backgd",    "PIX.1.2.16", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white,  blue,     bar,   "w_white Flashes, blue backgd",   "PIX.1.2.17", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white,  blue,     bar,   "c_white Flashes, blue backgd",   "PIX.1.2.18", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,     blue,     bar,   "cyan Flashes, blue backgd",      "PIX.1.2.19", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, red,      blue,     bar,   "red Flashes, blue backgd",       "PIX.1.2.20", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, blue,     red,      bar,   "blue Flashes, red backgd",       "PIX.1.2.21", leader, 1));
#endif

    // Digital Beat with led pixels
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 3
    // Flashes, no backgound
    animations.push_back(new AddrLEDAnimation2(this, red,     black,  pix,   "red Flashes",     "PIX.1.3.1", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, blue,    black,  pix,   "blue Flashes",    "PIX.1.3.2", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, purple,  black,  pix,   "purple Flashes",  "PIX.1.3.3", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, gold,    black,  pix,   "gold Flashes",    "PIX.1.3.4", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, sodium,  black,  pix,   "sodium Flashes",  "PIX.1.3.5", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,    black,  pix,   "cyan Flashes",    "PIX.1.3.6", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white, black,  pix,   "w_white Flashes", "PIX.1.3.7", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white, black,  pix,   "c_white Flashes", "PIX.1.3.8", leader, 1));
    //Flashes with backgd
    animations.push_back(new AddrLEDAnimation2(this, gold,     red,      pix,   "gold Flashes, red backgd",       "PIX.1.3.9", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white,  red,      pix,   "w_white Flashes, red backgd",    "PIX.1.3.10", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white,  red,      pix,   "c_white Flashes, red backgd",    "PIX.1.3.11", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, gold,     purple,   pix,   "gold Flashes, purple backgd",    "PIX.1.3.12", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white,  purple,   pix,   "w_white Flashes, purple backgd", "PIX.1.3.13", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white,  purple,   pix,   "c_white Flashes, purple backgd", "PIX.1.3.14", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,     red,      pix,   "cyan Flashes, red backgd",       "PIX.1.3.15", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,     purple,   pix,   "cyan Flashes, purple backgd",    "PIX.1.3.16", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, w_white,  blue,     pix,   "w_white Flashes, blue backgd",   "PIX.1.3.17", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, c_white,  blue,     pix,   "c_white Flashes, blue backgd",   "PIX.1.3.18", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, cyan,     blue,     pix,   "cyan Flashes, blue backgd",      "PIX.1.3.19", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, red,      blue,     pix,   "red Flashes, blue backgd",       "PIX.1.3.20", leader, 1));
    animations.push_back(new AddrLEDAnimation2(this, blue,     red,      pix,   "blue Flashes, red backgd",       "PIX.1.3.21", leader, 1));
#endif


// 2. BUBBLES
    // Slow & long Bubbles
#if SHOW_INTENSITY==0 or SHOW_INTENSITY <= 2
    // Dark background
    int flash_length = 1500, burst_period = 400;
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red},       gaussian, bar, burst_period, flash_length, "slow red bubbles",      "PIX.2.1.1", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{blue},      gaussian, bar, burst_period, flash_length, "slow blue bubbles",     "PIX.2.1.2", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{purple},    gaussian, bar, burst_period, flash_length, "slow purple bubbles",   "PIX.2.1.3", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{gold},      gaussian, bar, burst_period, flash_length, "slow gold bubbles",     "PIX.2.1.4", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{sodium},    gaussian, bar, burst_period, flash_length, "slow sodium bubbles",   "PIX.2.1.5", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{cyan},      gaussian, bar, burst_period, flash_length, "slow cyan bubbles",     "PIX.2.1.6", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{w_white},   gaussian, bar, burst_period, flash_length, "slow w_white bubbles",  "PIX.2.1.7", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{c_white},   gaussian, bar, burst_period, flash_length, "slow c_white bubbles",  "PIX.2.1.8", backer, 1, 255));
    // color Background
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{gold},    gaussian, bar, burst_period, flash_length, "S gold bubbles, red backgd",       "PIX.2.1.9",  backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{w_white}, gaussian, bar, burst_period, flash_length, "S w_white bubbles, red backgd",    "PIX.2.1.10", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{c_white}, gaussian, bar, burst_period, flash_length, "S c_white bubbles, red backgd",    "PIX.2.1.11", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{gold},    gaussian, bar, burst_period, flash_length, "S gold bubbles, purple backgd",    "PIX.2.1.12", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{w_white}, gaussian, bar, burst_period, flash_length, "S w_white bubbles, purple backgd", "PIX.2.1.13", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{c_white}, gaussian, bar, burst_period, flash_length, "S c_white bubbles, purple backgd", "PIX.2.1.14", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{cyan},    gaussian, bar, burst_period, flash_length, "S cyan bubbles, red backgd",       "PIX.2.1.15", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{cyan},    gaussian, bar, burst_period, flash_length, "S cyan bubbles, purple backgd",    "PIX.2.1.16", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{w_white}, gaussian, bar, burst_period, flash_length, "S w_white bubbles, blue backgd",   "PIX.2.1.17", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{c_white}, gaussian, bar, burst_period, flash_length, "S c_white bubbles, blue backgd",   "PIX.2.1.18", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{cyan},    gaussian, bar, burst_period, flash_length, "S cyan bubbles, blue backgd",      "PIX.2.1.19", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{red},     gaussian, bar, burst_period, flash_length, "S red bubbles, blue backgd",       "PIX.2.1.20", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{blue},    gaussian, bar, burst_period, flash_length, "S blue bubbles, red backgd",       "PIX.2.1.21", backer, 1, 255));
#endif

    // Fast & short Bubbles
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 2
    flash_length = 600, burst_period = 200;
    // Dark background
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red},       gaussian, bar, burst_period, flash_length, "fast red bubbles",      "PIX.2.2.1", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{blue},      gaussian, bar, burst_period, flash_length, "fast blue bubbles",     "PIX.2.2.2", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{purple},    gaussian, bar, burst_period, flash_length, "fast purple bubbles",   "PIX.2.2.3", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{gold},      gaussian, bar, burst_period, flash_length, "fast gold bubbles",     "PIX.2.2.4", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{sodium},    gaussian, bar, burst_period, flash_length, "fast sodium bubbles",   "PIX.2.2.5", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{cyan},      gaussian, bar, burst_period, flash_length, "fast cyan bubbles",     "PIX.2.2.6", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{w_white},   gaussian, bar, burst_period, flash_length, "fast w_white bubbles",  "PIX.2.2.7", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{c_white},   gaussian, bar, burst_period, flash_length, "fast c_white bubbles",  "PIX.2.2.8", any, 1, 255));
    // color Background
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{gold},    gaussian, bar, burst_period, flash_length, "F gold bubbles, red backgd",       "PIX.2.1.9",  any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{w_white}, gaussian, bar, burst_period, flash_length, "F w_white bubbles, red backgd",    "PIX.2.1.10", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{c_white}, gaussian, bar, burst_period, flash_length, "F c_white bubbles, red backgd",    "PIX.2.1.11", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{gold},    gaussian, bar, burst_period, flash_length, "F gold bubbles, purple backgd",    "PIX.2.1.12", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{w_white}, gaussian, bar, burst_period, flash_length, "F w_white bubbles, purple backgd", "PIX.2.1.13", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{c_white}, gaussian, bar, burst_period, flash_length, "F c_white bubbles, purple backgd", "PIX.2.1.14", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{cyan},    gaussian, bar, burst_period, flash_length, "F cyan bubbles, red backgd",       "PIX.2.1.15", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{cyan},    gaussian, bar, burst_period, flash_length, "F cyan bubbles, purple backgd",    "PIX.2.1.16", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{w_white}, gaussian, bar, burst_period, flash_length, "F w_white bubbles, blue backgd",   "PIX.2.1.17", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{c_white}, gaussian, bar, burst_period, flash_length, "F c_white bubbles, blue backgd",   "PIX.2.1.18", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{cyan},    gaussian, bar, burst_period, flash_length, "F cyan bubbles, blue backgd",      "PIX.2.1.19", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{red},     gaussian, bar, burst_period, flash_length, "F red bubbles, blue backgd",       "PIX.2.1.20", any, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{blue},    gaussian, bar, burst_period, flash_length, "F blue bubbles, red backgd",       "PIX.2.1.21", any, 1, 255));
#endif

// 3. ChASER
    //Slow Chaser
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 2
    flash_length = 1500, burst_period = 300;
    // Dark background
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red},       square, bar, burst_period, flash_length, "Slow red chaser",      "PIX.3.1.1", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{blue},      square, bar, burst_period, flash_length, "Slow blue chaser",     "PIX.3.1.2", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{purple},    square, bar, burst_period, flash_length, "Slow purple chaser",   "PIX.3.1.3", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{gold},      square, bar, burst_period, flash_length, "Slow gold chaser",     "PIX.3.1.4", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{sodium},    square, bar, burst_period, flash_length, "Slow sodium chaser",   "PIX.3.1.5", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{cyan},      square, bar, burst_period, flash_length, "Slow cyan chaser",     "PIX.3.1.6", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{w_white},   square, bar, burst_period, flash_length, "Slow w_white chaser",  "PIX.3.1.7", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{c_white},   square, bar, burst_period, flash_length, "Slow c_white chaser",  "PIX.3.1.8", backer, 1, 255));
    // color Background
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{gold},    square, bar, burst_period, flash_length, "S gold chaser, red backgd",       "PIX.3.1.9",  backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{w_white}, square, bar, burst_period, flash_length, "S w_white chaser, red backgd",    "PIX.3.1.10", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{c_white}, square, bar, burst_period, flash_length, "S c_white chaser, red backgd",    "PIX.3.1.11", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{gold},    square, bar, burst_period, flash_length, "S gold chaser, purple backgd",    "PIX.3.1.12", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{w_white}, square, bar, burst_period, flash_length, "S w_white chaser, purple backgd", "PIX.3.1.13", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{c_white}, square, bar, burst_period, flash_length, "S c_white chaser, purple backgd", "PIX.3.1.14", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{cyan},    square, bar, burst_period, flash_length, "S cyan chaser, red backgd",       "PIX.3.1.15", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{cyan},    square, bar, burst_period, flash_length, "S cyan chaser, purple backgd",    "PIX.3.1.16", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{w_white}, square, bar, burst_period, flash_length, "S w_white chaser, blue backgd",   "PIX.3.1.17", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{c_white}, square, bar, burst_period, flash_length, "S c_white chaser, blue backgd",   "PIX.3.1.18", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{cyan},    square, bar, burst_period, flash_length, "S cyan chaser, blue backgd",      "PIX.3.1.19", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{red},     square, bar, burst_period, flash_length, "S red chaser, blue backgd",       "PIX.3.1.20", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{blue},    square, bar, burst_period, flash_length, "S blue chaser, red backgd",       "PIX.3.1.21", backer, 1, 255));    
#endif
    // Fast Chaser
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 3
    flash_length = 600, burst_period = 200;
    // Dark background
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red},       square, bar, burst_period, flash_length, "Fast red chaser",      "PIX.3.2.1", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{blue},      square, bar, burst_period, flash_length, "Fast blue chaser",     "PIX.3.2.2", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{purple},    square, bar, burst_period, flash_length, "Fast purple chaser",   "PIX.3.2.3", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{gold},      square, bar, burst_period, flash_length, "Fast gold chaser",     "PIX.3.2.4", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{sodium},    square, bar, burst_period, flash_length, "Fast sodium chaser",   "PIX.3.2.5", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{cyan},      square, bar, burst_period, flash_length, "Fast cyan chaser",     "PIX.3.2.6", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{w_white},   square, bar, burst_period, flash_length, "Fast w_white chaser",  "PIX.3.2.7", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{c_white},   square, bar, burst_period, flash_length, "Fast c_white chaser",  "PIX.3.2.8", backer, 1, 255));
    // color Background
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{gold},    square, bar, burst_period, flash_length, "F gold chaser, red backgd",       "PIX.3.2.9",  backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{w_white}, square, bar, burst_period, flash_length, "F w_white chaser, red backgd",    "PIX.3.2.10", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{c_white}, square, bar, burst_period, flash_length, "F c_white chaser, red backgd",    "PIX.3.2.11", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{gold},    square, bar, burst_period, flash_length, "F gold chaser, purple backgd",    "PIX.3.2.12", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{w_white}, square, bar, burst_period, flash_length, "F w_white chaser, purple backgd", "PIX.3.2.13", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{c_white}, square, bar, burst_period, flash_length, "F c_white chaser, purple backgd", "PIX.3.2.14", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{cyan},    square, bar, burst_period, flash_length, "F cyan chaser, red backgd",       "PIX.3.2.15", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, purple,  color_vec{cyan},    square, bar, burst_period, flash_length, "F cyan chaser, purple backgd",    "PIX.3.2.16", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{w_white}, square, bar, burst_period, flash_length, "F w_white chaser, blue backgd",   "PIX.3.2.17", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{c_white}, square, bar, burst_period, flash_length, "F c_white chaser, blue backgd",   "PIX.3.2.18", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{cyan},    square, bar, burst_period, flash_length, "F cyan chaser, blue backgd",      "PIX.3.2.19", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, blue,    color_vec{red},     square, bar, burst_period, flash_length, "F red chaser, blue backgd",       "PIX.3.2.20", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, red,     color_vec{blue},    square, bar, burst_period, flash_length, "F blue chaser, red backgd",       "PIX.3.2.21", backer, 1, 255));   
#endif

// 4. Strobe (Short pulses, no background)
    //Very Fast
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 3
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red},     square, bar, 50, 1000/FRATE, "red VF strobe, Black bg",     "PIX.4.1.1", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{blue},    square, bar, 50, 1000/FRATE, "blue VF strobe, Black bg",    "PIX.4.1.2", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{purple},  square, bar, 50, 1000/FRATE, "purple VF strobe, Black bg",  "PIX.4.1.3", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{gold},    square, bar, 50, 1000/FRATE, "gold VF strobe, Black bg",    "PIX.4.1.4", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{sodium},  square, bar, 50, 1000/FRATE, "sodium VF strobe, Black bg",  "PIX.4.1.5", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{cyan},    square, bar, 50, 1000/FRATE, "cyan VF strobe, Black bg",    "PIX.4.1.6", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{w_white}, square, bar, 50, 1000/FRATE, "w_white VF strobe, Black bg", "PIX.4.1.7", leader, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{c_white}, square, bar, 50, 1000/FRATE, "c_white VF strobe, Black bg", "PIX.4.1.8", leader, 1, 255));
#endif
#if SHOW_INTENSITY==0 or SHOW_INTENSITY >= 2
    // Scarce
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{red},      square, bar, 1000, 1000/FRATE,  "red slow strobe, Black bg",      "PIX.4.2.1", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{blue},     square, bar, 1000, 1000/FRATE,  "blue slow strobe, Black bg",     "PIX.4.2.2", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{purple},   square, bar, 1000, 1000/FRATE,  "purple slow strobe, Black bg",   "PIX.4.2.3", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{gold},     square, bar, 1000, 1000/FRATE,  "gold slow strobe, Black bg",     "PIX.4.2.4", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{sodium},   square, bar, 1000, 1000/FRATE,  "sodium slow strobe, Black bg",   "PIX.4.2.5", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{cyan},     square, bar, 1000, 1000/FRATE,  "cyan slow strobe, Black bg",     "PIX.4.2.6", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{w_white},  square, bar, 1000, 1000/FRATE,  "w_white slow strobe, Black bg",  "PIX.4.2.7", backer, 1, 255));
    animations.push_back(new AddrLEDAnimation4(this, black, color_vec{c_white},  square, bar, 1000, 1000/FRATE,  "c_white slow strobe, Black bg",  "PIX.4.2.8", backer, 1, 255));
#endif

    this->activate_none();
}

// spits out an ordered vector containing every subpixel value (0-256)
//TODO Add support for fixture Master & Animation Master
DMX_vec AddressableLED::buffer(){
    DMX_vec data(NUM_SUBPIX);
    
    int i_data = 0;
    for (auto pix : this->pixels){        
        for (auto sub_pix : pix){
            data[i_data++] = (uint8_t) (this->master/255.0 * this->active_animation->master/255.0 * sub_pix);
        }
    }
    return data;
}   





/**
######   #####  ######  #     #    #######               
#     # #     # #     # #  #  #    #        ####  #    # 
#     # #       #     # #  #  #    #       #    # ##   # 
######  #  #### ######  #  #  #    #####   #      # #  # 
#   #   #     # #     # #  #  #    #       #      #  # # 
#    #  #     # #     # #  #  #    #       #    # #   ## 
#     #  #####  ######   ## ##     #        ####  #    # 
*/
//TODO calibrate colors
DMX_vec AddressableLED::RGB(simpleColor c, int intensity){
    // log(4, __FILE__, " ",__LINE__, " ", __func__);

    DMX_vec temp;
    int ref_int = 255;          // reference intensity, set for each color to get a constnat luminosity trhoughtou the palette
    // store in vector temp the color vector of norm 255
    switch (c){
        case black:
            temp = fcn::RGB_norm(DMX_vec{0,0,0});
            break;
        case red:
            temp = fcn::RGB_norm(DMX_vec{255,0,0});
            break;
        case green:
            ref_int = 100; 
            temp = fcn::RGB_norm(DMX_vec{0,255,0});
            break;
        case blue:
            ref_int = 220;
            temp = fcn::RGB_norm(DMX_vec{0,0,255});
            break;
        case yellow:
            ref_int = 200;
            temp = fcn::RGB_norm(DMX_vec{255,87,0});
            break;
        case orange:
            temp = fcn::RGB_norm(DMX_vec{255,35,0});
            break;
        case sodium:
            temp = fcn::RGB_norm(DMX_vec{255,16,0});
            break;
        case cyan:
            ref_int = 150;
            temp = fcn::RGB_norm(DMX_vec{0,184,255});
            break;
        case purple:
            ref_int = 255;
            temp = fcn::RGB_norm(DMX_vec{180,0,255});
            break;    
        case magenta:
            ref_int = 255;
            temp = fcn::RGB_norm(DMX_vec{255,0,197});
            break;
        case pink:
            ref_int = 255;
            temp = fcn::RGB_norm(DMX_vec{255,0,86});
            break;
        case w_white:
            temp = fcn::RGB_norm(DMX_vec{255,173,102});
            break;
        case c_white:
            ref_int = 255; 
            temp = fcn::RGB_norm(DMX_vec{255,255,255});
            break;
        case gold:
            temp = fcn::RGB_norm(DMX_vec{255,50,3});
            break;
        default:
            temp = fcn::RGB_norm(DMX_vec{0,0,0});
            break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity==-1 ? -1 : (int)ref_int * intensity/255.0);
}





/*
  #             #                                          ######  #######    #    #######
 ##            # #   #    #   ##   #       ####   ####     #     # #         # #      #   
# #           #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #   
  #          #     # # #  # #    # #      #    # #         ######  #####   #     #    #   
  #   ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #   
  #   ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #   
##### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #   
*/
void AddrLEDAnimation1::init(){
    BaseAnimation::init();
}

void AddrLEDAnimation1::new_frame(){
    balise("Addr LED Ani1 New frames...");
    BaseAnimation::new_frame();
    
    // local variables for readability
    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size();

    balise("Addr LED Ani1 New frames 1");
    // enable / disable
    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);
    
    // for each new beat, sort segments in random order
    if (sampler.new_beat)
        units_index = fcn::randomized_vector(units_index);

    // precompute pixel values
    pixel backgd_RGB = this->fixture->RGB(back_color, 20);
    pixel flash_RGB = this->fixture->RGB(flash_color);
    pixel final_mix_RGB(3);

    // Compute intensity vaue based on time elapsed since last beat
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    // compute number of units flashing 
    int n_unit_on = density * n_unit;

    // compute final RGB colors
    if (param_activate_flash && auto_activate_flash)
    {
         
        final_mix_RGB[R] = (1-pow(coef, 0.2)) * backgd_RGB[R] + coef * flash_RGB[R];
        final_mix_RGB[G] = (1-pow(coef, 0.2)) * backgd_RGB[G] + coef * flash_RGB[G];
        final_mix_RGB[B] = (1-pow(coef, 0.2)) * backgd_RGB[B] + coef * flash_RGB[B];
    }
    else
    {
        final_mix_RGB[R] = backgd_RGB[R];
        final_mix_RGB[G] = backgd_RGB[G];
        final_mix_RGB[B] = backgd_RGB[B];
    }

    // set each units color
    for (int i=0; i<n_unit; i++){
        pixel unit_i_RGB;
        if (i<n_unit_on)
            unit_i_RGB = final_mix_RGB;
        else
            unit_i_RGB = backgd_RGB;
        switch (unit){
                case pix : this->fixture->pixels[units_index[i]] = unit_i_RGB;
                break;
                case seg : this->fixture->set_segment_color(units_index[i], unit_i_RGB);
                break;
                case bar : this->fixture->set_bar_color(units_index[i], unit_i_RGB);
                break;
                default :
                break;
            }
    }
}

/*
 #####         ######                                    ######  #######    #    #######
#     #        #     # #  ####  # #####   ##   #         #     # #         # #      #   
      #        #     # # #    # #   #    #  #  #         #     # #        #   #     #   
 #####         #     # # #      #   #   #    # #         ######  #####   #     #    #   
#       ###    #     # # #  ### #   #   ###### #         #     # #       #######    #   
#       ###    #     # # #    # #   #   #    # #         #     # #       #     #    #   
####### ###    ######  #  ####  #   #   #    # ######    ######  ####### #     #    #   
*/
void AddrLEDAnimation2::init(){
    BaseAnimation::init();
}

void AddrLEDAnimation2::new_frame(){
    BaseAnimation::new_frame();

    unsigned long t_ms = frame.t_current_ms;
    unsigned long t_last_beat_ms = sampler.t_last_new_beat;
    int_vec::size_type n_unit = units_index.size();

    bool auto_activate_flash = (sampler.state == BEAT) && (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH);

    // for each new beat, sort segments in random order
    if (sampler.new_beat)
        units_index = fcn::randomized_vector(units_index);

    // compute intensity value
    float coef = exp(-(double)(t_ms - t_last_beat_ms) / fade_rate);
    //derive number of segments to turn on
    int n_unit_on = coef * n_unit;
    //chose which segments to turn on
    for (int i = 0; i<n_unit; i++){
        if (i<n_unit_on)
            switch (unit){
                case pix : this->fixture->pixels[units_index[i]] = flash_RGB;
                    break;
                case seg : this->fixture->set_segment_color(units_index[i], flash_RGB);
                    break;
                case bar : this->fixture->set_bar_color(units_index[i], flash_RGB);
                    break;
            }
            
        else
            switch (unit){
                case pix : this->fixture->pixels[units_index[i]] = backgd_RGB;
                    break;
                case seg : this->fixture->set_segment_color(units_index[i], backgd_RGB);
                    break;
                case bar : this->fixture->set_bar_color(units_index[i], backgd_RGB);
                    break;
            }
    }
}

/*
 #####          #     #                        
#     #         ##    #  ####  #  ####  ###### 
      #         # #   # #    # # #      #      
 #####          #  #  # #    # #  ####  #####  
      # ###     #   # # #    # #      # #      
#     # ###     #    ## #    # # #    # #      
 #####  ###     #     #  ####  #  ####  ###### 
*/
void AddrLEDAnimation3::init() {
    BaseAnimation::init();
}
void AddrLEDAnimation3::new_frame() {
    BaseAnimation::new_frame();
    
    // double f_weight = enable_filter*param_filter_weight*!is_first_frame();
    
    for (int i = 0; i<NUM_PIX; i++){
        pix_intensities[i] = min(255, max(0, fcn::random_walk((int)pix_intensities[i], 5, 0, 255) ));
        // if(f_weight != 0)
        //     pix_intensities[i] = min(255.0, max(0.0, pix_intensities[i] + f_weight * (atan_transfo[rand_min_max(0, 256)] - 127.0) ));
        // else
        //     pix_intensities[i] = atan_transfo[rand_min_max(0, 256)];

        this->fixture->pixels[i] = this->fixture->RGB(color, pix_intensities[i]);
    }
}

/*
#              ######                          ######                             
#    #         #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
#    #         #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
#    #         ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
####### ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
     #  ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
     #  ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
*/
void AddrLEDAnimation4::init(){
    log(4, __FILE__, " ", __LINE__, " ",__func__, " ", this->fixture->name, " ", this->id);

    BaseAnimation::init();
    
    const int n_unit = unit==bar ? NUM_BAR : (unit==seg ? NUM_SEG : (unit==pix ? NUM_PIX : 0));

    this->flashes = vector<flash_vec>(n_unit, flash_vec(2));

    for (int i_unit=0; i_unit<n_unit; i_unit++){
        flashes[i_unit][i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2*n_unit); 
        flashes[i_unit][i_prev].time = 0;
        flashes[i_unit][i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_unit][i_prev].color = black;
    }
}

void AddrLEDAnimation4::new_frame(){
    log(4, __FILE__, " ", __LINE__, " ",__func__);

    BaseAnimation::new_frame();

    long t = frame.t_current_ms;         // for readability
    int n_unit = this->flashes.size();   // for readability
    
   
    // for each spot "i" of the rack
    for (int i_unit=0; i_unit < n_unit; i_unit++){

        // auto current_spot = this->fixture->spots[i_unit];           // for readability
        auto &current_unit_flashes = flashes[i_unit];                  // for readability
        auto &current_unit_next_flash = flashes[i_unit][i_next];       // for readability
        auto &current_unit_prev_flash = flashes[i_unit][i_prev];       // for readability
        time_t &t_next = current_unit_next_flash.time;
        time_t &t_prev = current_unit_prev_flash.time;
        simpleColor &c_next = current_unit_next_flash.color;
        simpleColor &c_prev = current_unit_prev_flash.color;

        // log(4, __FILE__, " ", __LINE__, " ",__func__, " Mark2 , ", fcn::num_to_str(i_spot));

        const pixel ani_backgd_RGB = fixture->RGB(back_color, ADDRLED_ANI4_BkG_INTENSITY_LOW);
        
        // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
            double flash_intensity; // 0 by default
            if (flash_activation){
                // when the flash passes, compute the next flash timestamp and update prev flash
                if (t > t_next){
                    
                    t_prev = t_next;
                    t_next = t_next + rand_min_max(this->flash_len, 2*n_unit*this->rand_const_ms);
                    c_prev = c_next;
                    c_next = fcn::random_pick(this->flash_colors);
                    
                }

                // flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                switch (this->flash_shape){
                    case square :
                        flash_intensity = fcn::square(t, t_prev, flash_len, 0.0,1.0) + fcn::square(t, t_next, flash_len, 0.0,1.0);
                        break;
                    case gaussian2 :
                        flash_intensity = fcn::gaussian2(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian2(t, t_next, flash_len, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                        break;
                    default :
                        flash_intensity = fcn::gaussian(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian(t, t_next, flash_len, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
                        break;
                }

            }else{
                flash_intensity = 0.0;
            }

            DMX_vec frame_flash_RGB = (t-t_prev > t_next-t) ? fixture->RGB(c_next) : this->fixture->RGB(c_prev);
            DMX_vec unit_final_RGB(3, 0);
            unit_final_RGB[R] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[R] + flash_intensity * frame_flash_RGB[R]  ),0),255); 
            unit_final_RGB[G] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[G] + flash_intensity * frame_flash_RGB[G]  ),0),255);
            unit_final_RGB[B] = min(max( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[B] + flash_intensity * frame_flash_RGB[B]  ),0),255);

            switch (this->unit){
                case bar : this->fixture->set_bar_color(i_unit, unit_final_RGB);
                    break;
                case seg : this->fixture->set_segment_color(i_unit, unit_final_RGB);
                    break;
                case pix : this->fixture->pixels[i_unit] = unit_final_RGB;
                    break;
            }
    }
}


// /* 4 - HiVE*/
// void AddrLEDAnimation5::init() {BaseAnimation::init();
//     const auto num_group = groups_size.size();
    
//     for (int i_grp = 0; i_grp<num_group; i_grp++){
//         const auto group_size = groups_size[i_grp];
//         // for each group of led bar, initialize a vector of blots with a number of elements proportional to the number of bars in the group
//         this->blot_groups[i_grp] = blot_vec(    (int)(this->density_factor * group_size * 6)    );

//         // for each of the group's blot, initialize its widthn, position, speed & intensity 
//         for (auto blot : blot_groups[i_grp]) {
//             // position (pixels as a uint) is randomly picked along the length of the bars' group 
//             blot.position = rand_min_max(0, group_size * NUM_PIX_BAR);
//             //nothing else for now, all blots are created equal (see class definition)
//             // TODO update
//         }
//     }
// };

// void AddrLEDAnimation5::new_frame() {BaseAnimation::new_frame();
//     //update blot kinematics (position)

//     //compute each pixel's value :
//     //for each group of bars :
//     auto pix_parser = this->fixture->pixels.begin();

//     for (auto i_grp = 0; i_grp < groups_size.size(); i_grp++){
//         const int num_bar_group = groups_size[i_grp];
//         const int num_pix_group = num_bar_group * NUM_PIX_BAR;
//         auto blots = this->blot_groups[i_grp];
        
//         //for each pixel in the group
//         int pix_position = 0;
//         for (auto pix = pix_parser; pix != pix_parser + num_pix_group; pix ++){
//             // find the closest blot (in terms of position)
//             auto closest_blot = blots[0];
//             for (auto blot : blots){
//                 if (abs(blot.position-pix_position) < abs(closest_blot.position-pix_position)){
//                     //TODO replace with a operator= overload
//                     closest_blot.position = blot.position;
//                     closest_blot.luminosity = blot.luminosity;
//                     closest_blot.color = blot.color;
//                     closest_blot.width = blot.width;
//                 }
//             }

//             // compute the pixel's color (from closest blot's width, color & intensity);
//             auto blot_dist = closest_blot.position - pix_position;
//             (*pix) = blot_dist > closest_blot.width/2 ? this->fixture->RGBW(closest_blot.color, closest_blot.luminosity*255) : this->fixture->RGBW(black, 0);
//         }
//         pix_parser += num_pix_group;

//     }
  

// };