#include <vector>

#include "animator.h"

using namespace std;

class LaserFixture;     
class LaserAnimation;
class LaserAnimation1;


class LaserFixture : public BaseFixture{
public:    
    // Channels
    uint8_t motor1;                     // motor 1 speed (0-255)
    uint8_t motor2;                     // motor 2 speed (0-255)
    vector<uint8_t> RGB = {0,0,0};      // RGB diod command (0 or 255) 
    uint8_t prog;
    uint8_t motor_sync, freq_sync;      // motor speed and flickering freq calibration coefficient 

    // constructor
    LaserFixture(int addr): BaseFixture(addr){};

    // color macros;
    void red(){        
        this->RGB[R] = 255;
        this->RGB[G] = 0;
        this->RGB[B] = 0;
    }
    void green(){        
        this->RGB[R] = 0;
        this->RGB[G] = 255;
        this->RGB[B] = 0;
    }
    void blue(){        
        this->RGB[R] = 0;
        this->RGB[G] = 0;
        this->RGB[B] = 255;
    } 
    void yellow(){        
        this->RGB[R] = 255;
        this->RGB[G] = 255;
        this->RGB[B] = 0;
    } 
    void magenta(){        
        this->RGB[R] = 255;
        this->RGB[G] = 0;
        this->RGB[B] = 255;
    } 
    void cyan(){        
        this->RGB[R] = 0;
        this->RGB[G] = 255;
        this->RGB[B] = 255;
    } 
    void black(){        
        this->RGB[R] = 0;
        this->RGB[G] = 0;
        this->RGB[B] = 0;
    }
    void white(){        
        this->RGB[R] = 255;
        this->RGB[G] = 255;
        this->RGB[B] = 255;
    }
    void digital_color(uint8_t c){
        switch (c)
        {
        case 0:
            this->black();
            break;
        case 1:
            this->red();
            break;
        case 2:
            this->green();
            break;
        case 3:
            this->blue();
            break;
        case 4:
            this->yellow();
            break;
        case 5:
            this->cyan();
            break;
        case 6:
            this->magenta();
            break;
        case 7:
            this->white();
            break;
        
        default:
            break;
        }
    }
};


class LaserAnimation : public BaseAnimation{

};


class LaserAnimation1 : public LaserAnimation{

};