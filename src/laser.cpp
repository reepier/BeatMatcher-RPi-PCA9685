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
    this->animations.push_back(new LaserAnimation1(this, 7,  color_vec{white},     "Circle Dance white",     "LAS.1.1.7", any));
    // Circle dance Bicolor
    this->animations.push_back(new LaserAnimation1(this, 8,  color_vec{white, red},             "Circle Dance white, red",      "LAS.1.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 9,  color_vec{white, green},           "Circle Dance white, green",    "LAS.1.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 10,  color_vec{white, blue},           "Circle Dance white, blue",     "LAS.1.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 11, color_vec{white, yellow, gold},    "Circle Dance white, yellow",   "LAS.1.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 12, color_vec{white, cyan},            "Circle Dance white, cyan",     "LAS.1.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 13, color_vec{white, magenta, pink},   "Circle Dance white, magenta",  "LAS.1.2.6", any));

    // Glitch Bicolor
    this->animations.push_back(new LaserAnimation1(this, 20,    color_vec{white, red},           "Glitch white, red",      "LAS.2.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 21,    color_vec{white, green},         "Glitch white, green",    "LAS.2.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 22,    color_vec{white, blue},          "Glitch white, blue",     "LAS.2.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 23,    color_vec{white, yellow},        "Glitch white, yellow",   "LAS.2.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 24,    color_vec{white, cyan},          "Glitch white, cyan",     "LAS.2.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 25,    color_vec{white, magenta},       "Glitch white, magenta",  "LAS.2.1.6", any));
    // Glitch Monochrome
    this->animations.push_back(new LaserAnimation1(this, 26,    color_vec{red},        "Glitch red",        "LAS.2.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 27,    color_vec{green},      "Glitch green",      "LAS.2.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 28,    color_vec{blue},       "Glitch blue",       "LAS.2.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 29,    color_vec{yellow},     "Glitch yellow",     "LAS.2.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 30,    color_vec{cyan},       "Glitch cyan",       "LAS.2.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 31,    color_vec{magenta},    "Glitch magenta",    "LAS.2.2.6", any));
    this->animations.push_back(new LaserAnimation1(this, 32,    color_vec{white},      "Glitch white",      "LAS.2.2.7", any));

    // Palm Dance Bichrome
    this->animations.push_back(new LaserAnimation1(this, 50,    color_vec{white, red},     "Palm Dance white red",     "LAS.3.1.1", any));
    this->animations.push_back(new LaserAnimation1(this, 51,    color_vec{white, green},   "Palm Dance white green",   "LAS.3.1.2", any));
    this->animations.push_back(new LaserAnimation1(this, 52,    color_vec{white, blue},    "Palm Dance white blue",    "LAS.3.1.3", any));
    this->animations.push_back(new LaserAnimation1(this, 53,    color_vec{white, yellow},  "Palm Dance white yellow",  "LAS.3.1.4", any));
    this->animations.push_back(new LaserAnimation1(this, 54,    color_vec{white, cyan},    "Palm Dance white cyan",    "LAS.3.1.5", any));
    this->animations.push_back(new LaserAnimation1(this, 55,    color_vec{white, magenta}, "Palm Dance white magenta", "LAS.3.1.6", any));
    // Palm Dance Monochrome
    this->animations.push_back(new LaserAnimation1(this, 56,    color_vec{red},     "Palm Dance red",       "LAS.3.2.1", any));
    this->animations.push_back(new LaserAnimation1(this, 57,    color_vec{green},   "Palm Dance green",     "LAS.3.2.2", any));
    this->animations.push_back(new LaserAnimation1(this, 58,    color_vec{blue},    "Palm Dance blue",      "LAS.3.2.3", any));
    this->animations.push_back(new LaserAnimation1(this, 59,    color_vec{yellow},  "Palm Dance yellow",    "LAS.3.2.4", any));
    this->animations.push_back(new LaserAnimation1(this, 60,    color_vec{cyan},    "Palm Dance cyan",      "LAS.3.2.5", any));
    this->animations.push_back(new LaserAnimation1(this, 61,    color_vec{magenta}, "Palm Dance magenta",   "LAS.3.2.6", any));
    this->animations.push_back(new LaserAnimation1(this, 62,    color_vec{white},   "Palm Dance white",     "LAS.3.2.7", any));


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