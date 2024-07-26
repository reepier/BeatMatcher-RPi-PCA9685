#include "laser.h"
#include "debug.h"

LaserFixture laser(13, 8, "Laser");

/**
####### ### #     # ####### #     # ######  ####### 
#        #   #   #     #    #     # #     # #       
#        #    # #      #    #     # #     # #       
#####    #     #       #    #     # ######  #####   
#        #    # #      #    #     # #   #   #       
#        #   #   #     #    #     # #    #  #       
#       ### #     #    #     #####  #     # ####### 
*/
DMX_vec LaserFixture::buffer(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    return DMX_vec{motor1, motor2, RGB[R], RGB[G], RGB[B], prog, motor_sync, freq_sync};
}

void LaserFixture::init(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    // BLACK
    this->animations.push_back(new LaserAnimation1(this, 0,     color_vec{black},   " ",     "LAS.0", backer));

    // Circle dance Monochrome
    this->animations.push_back(new LaserAnimation1(this, 1,  color_vec{red},       "Circle Dance red",       "LAS.1.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 2,  color_vec{green},     "Circle Dance green",     "LAS.1.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 3,  color_vec{blue},      "Circle Dance blue",      "LAS.1.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 4,  color_vec{yellow},    "Circle Dance yellow",    "LAS.1.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 5,  color_vec{cyan},      "Circle Dance cyan",      "LAS.1.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 6,  color_vec{magenta},   "Circle Dance magenta",   "LAS.1.1.6", any));
    this->animations.push_back(new LaserAnimation1(this, 7,  color_vec{c_white},     "Circle Dance white",     "LAS.1.1.7", any));
    // Circle dance Bicolor
    this->animations.push_back(new LaserAnimation1(this, 8,  color_vec{c_white, red},       "Circle Dance white, red",      "LAS.1.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 9,  color_vec{c_white, green},     "Circle Dance white, green",    "LAS.1.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 10,  color_vec{c_white, blue},     "Circle Dance white, blue",     "LAS.1.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 11, color_vec{c_white, yellow},    "Circle Dance white, yellow",   "LAS.1.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 12, color_vec{c_white, cyan},      "Circle Dance white, cyan",     "LAS.1.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 13, color_vec{c_white, magenta},   "Circle Dance white, magenta",  "LAS.1.2.6", any));
    this->animations.push_back(new LaserAnimation1(this, 14, color_vec{red, cyan},        "Circle Dance red, cyan",       "LAS.1.2.7", any));
    this->animations.push_back(new LaserAnimation1(this, 15, color_vec{red, blue},        "Circle Dance red, blue",       "LAS.1.2.8", any));
    this->animations.push_back(new LaserAnimation1(this, 16, color_vec{red, magenta},     "Circle Dance red, blue",       "LAS.1.2.9", any));

    // Glitch Monochrome
    this->animations.push_back(new LaserAnimation1(this, 26,    color_vec{red},        "Glitch red",        "LAS.2.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 27,    color_vec{green},      "Glitch green",      "LAS.2.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 28,    color_vec{blue},       "Glitch blue",       "LAS.2.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 29,    color_vec{yellow},     "Glitch yellow",     "LAS.2.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 30,    color_vec{cyan},       "Glitch cyan",       "LAS.2.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 31,    color_vec{magenta},    "Glitch magenta",    "LAS.2.2.6", any));
    this->animations.push_back(new LaserAnimation1(this, 32,    color_vec{c_white},      "Glitch white",      "LAS.2.2.7", any));
    // Glitch Bicolor
    this->animations.push_back(new LaserAnimation1(this, 20,    color_vec{c_white, red},          "Glitch white, red",      "LAS.2.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 21,    color_vec{c_white, green},        "Glitch white, green",    "LAS.2.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 22,    color_vec{c_white, blue},         "Glitch white, blue",     "LAS.2.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 23,    color_vec{c_white, yellow},       "Glitch white, yellow",   "LAS.2.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 24,    color_vec{c_white, cyan},         "Glitch white, cyan",     "LAS.2.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 25,    color_vec{c_white, magenta},      "Glitch white, magenta",  "LAS.2.1.6", any));
    this->animations.push_back(new LaserAnimation1(this, 33,    color_vec{red, cyan},           "Glitch white, magenta",  "LAS.2.1.7", any));
    this->animations.push_back(new LaserAnimation1(this, 34,    color_vec{red, blue},           "Glitch white, magenta",  "LAS.2.1.8", any));
    
    // Palm Dance Bichrome
    this->animations.push_back(new LaserAnimation1(this, 50,    color_vec{c_white, red},     "Palm Dance white red",     "LAS.3.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 51,    color_vec{c_white, green},   "Palm Dance white green",   "LAS.3.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 52,    color_vec{c_white, blue},    "Palm Dance white blue",    "LAS.3.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 53,    color_vec{c_white, yellow},  "Palm Dance white yellow",  "LAS.3.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 54,    color_vec{c_white, cyan},    "Palm Dance white cyan",    "LAS.3.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 55,    color_vec{c_white, magenta}, "Palm Dance white magenta", "LAS.3.1.6", any));
    // Palm Dance Monochrome
    this->animations.push_back(new LaserAnimation1(this, 56,    color_vec{red},     "Palm Dance red",       "LAS.3.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 57,    color_vec{green},   "Palm Dance green",     "LAS.3.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 58,    color_vec{blue},    "Palm Dance blue",      "LAS.3.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 59,    color_vec{yellow},  "Palm Dance yellow",    "LAS.3.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 60,    color_vec{cyan},    "Palm Dance cyan",      "LAS.3.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 61,    color_vec{magenta}, "Palm Dance magenta",   "LAS.3.2.6", any));
    this->animations.push_back(new LaserAnimation1(this, 62,    color_vec{c_white},   "Palm Dance white",     "LAS.3.2.7", any));

    // Glitter Monochrome
    this->animations.push_back(new LaserAnimation1(this, 110,    color_vec{red},     "Glitter red",      "LAS.4.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 111,    color_vec{green},   "Glitter green",    "LAS.4.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 112,    color_vec{blue},    "Glitter blue",     "LAS.4.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 113,    color_vec{yellow},  "Glitter yellow",   "LAS.4.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 114,    color_vec{cyan},    "Glitter cyan",     "LAS.4.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 115,    color_vec{magenta}, "Glitter magenta",  "LAS.4.1.6", any));
    this->animations.push_back(new LaserAnimation1(this, 116,    color_vec{c_white},   "Glitter white",    "LAS.4.1.7", any));
    // Glitter Bichrom4
    this->animations.push_back(new LaserAnimation1(this, 117,    color_vec{red, c_white},     "Glitter red white",     "LAS.4.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 118,    color_vec{green, c_white},   "Glitter green white",   "LAS.4.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 119,    color_vec{blue, c_white},    "Glitter blue white",    "LAS.4.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 120,    color_vec{yellow, c_white},  "Glitter yellow white",  "LAS.4.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 121,    color_vec{cyan, c_white},    "Glitter cyan white",    "LAS.4.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 122,    color_vec{magenta, c_white}, "Glitter magenta white", "LAS.4.2.6", any));
    this->animations.push_back(new LaserAnimation1(this, 123,    color_vec{cyan, magenta},  "Glitter cyan magenta",  "LAS.4.2.7", any));
    this->animations.push_back(new LaserAnimation1(this, 124,    color_vec{red, blue},      "Glitter red blue",      "LAS.4.2.8", any));
    this->animations.push_back(new LaserAnimation1(this, 125,    color_vec{red, cyan},      "Glitter red cyan",      "LAS.4.2.9", any));

    // Smooth Broken
    this->animations.push_back(new LaserAnimation1(this, 140,    color_vec{red},      "SmoothB black & red",      "LAS.5.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 141,    color_vec{green},    "SmoothB black & green",    "LAS.5.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 142,    color_vec{blue},     "SmoothB black & blue",     "LAS.5.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 143,    color_vec{yellow},   "SmoothB black & yellow",   "LAS.5.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 144,    color_vec{cyan},     "SmoothB black & cyan",     "LAS.5.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 145,    color_vec{magenta},  "SmoothB black & magenta",  "LAS.5.1.6", any));
    this->animations.push_back(new LaserAnimation1(this, 146,    color_vec{c_white},    "SmoothB black & white",    "LAS.5.1.7", any));
    // Smooth Broken
    this->animations.push_back(new LaserAnimation1(this, 147,    color_vec{red, c_white},      "SmoothB red & white",     "LAS.5.2.1",  any));
    this->animations.push_back(new LaserAnimation1(this, 148,    color_vec{green, c_white},    "SmoothB green & white",   "LAS.5.2.2",  any));
    this->animations.push_back(new LaserAnimation1(this, 149,    color_vec{blue, c_white},     "SmoothB blue & white",    "LAS.5.2.3",  any));
    this->animations.push_back(new LaserAnimation1(this, 150,    color_vec{blue, cyan},      "SmoothB blue & cyan",     "LAS.5.2.7",  any));
    this->animations.push_back(new LaserAnimation1(this, 151,    color_vec{red, cyan},       "SmoothB red & cyan",      "LAS.5.2.8",  any));
    this->animations.push_back(new LaserAnimation1(this, 152,    color_vec{red, magenta},    "SmoothB red & magenta",   "LAS.5.2.9",  any));
    this->animations.push_back(new LaserAnimation1(this, 153,    color_vec{blue, magenta},   "SmoothB blue & magenta",  "LAS.5.2.10", any));
    


    this->activate_by_index(0);
}

// laser specific function to activate magenta animations when current palette contains pink
bool LaserFixture::activate_by_color(color_vec arg_palette, AnimationType arg_type){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    for (auto col : arg_palette){
        if (col==pink)
            arg_palette.push_back(magenta);
    }
    return BaseFixture::activate_by_color(arg_palette, arg_type);
}




/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####  
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     # 
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #       
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####  
####### #   # #  #  #     # #######    #     #  #     # #   # #       # 
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     # 
#     # #     # ### #     # #     #    #    ### ####### #     #  #####  
*/
void LaserAnimation1::new_frame(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);
   
}