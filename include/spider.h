#include <vector>

#include "animator.h"

#define NLED 9
#define NCOL 4




class SpiderFixture;
class SpiderAnimation;

typedef std::vector<DMX_vec> pixel_vec; 
// --------------------------------------
// SPIDER FIXTURE definition
// --------------------------------------

class SpiderFixture : public BaseFixture
{
public:
    const int nCH = 44;
    int pan_position;                   // pan position (°)
    int  pan_speed;                     // pan speed    [-128 - 127]
    int_vec tilt;                       // tilt axes [tilt 1, tilt 2...] [0-255] -> -30, +120°
    pixel_vec pixels; // LED Pixels [ [R,G,B,W] , [R,G,B,W] , ... [R,G,B,W] ]
    uint8_t strobe;
    uint8_t prog;
    
    SpiderFixture(int addr) : BaseFixture(addr)
    {  
        this->tilt.resize(3);
        this->pixels.resize(NLED, DMX_vec(NCOL));
    };

    void init() override;

    DMX_vec buffer() override;
};
extern SpiderFixture spider;

// --------------------------------------
// SPIDER ANIMATION definition
// --------------------------------------

class SpiderAnimation : public BaseAnimation{
public:
    SpiderFixture *fixture;
};

// Static Monochrome Animation
class SpiderAnimation1 : public SpiderAnimation{
  public:
    int pan_pos;  //pan position °
    int pan_spd;  //pan speed (-128 ; +127)
    int_vec tilt; //tilt position x3 ()
    pixel_vec pix = pixel_vec(9, fcn::RGBW(black)); // stores RGB values as follow RGBW[Led_i][Pix_i]

    SpiderAnimation1(SpiderFixture *f, SimpleColor c,  int pos, int spd, int_vec til, std::string d, std::string i){
        this->description = d;
        this->id = i; 
        this->fixture = f;

        if (til.size()==1){
            this->tilt = int_vec(3, til[0]);
        }else if (til.size()!=3){
            this->tilt.resize(0);
        }else{
            this->tilt = til;
        }
        this->pan_pos = pos;
        this->pan_spd = spd;

        this->pix = pixel_vec(9, fcn::RGBW(c));
    };
    SpiderAnimation1(SpiderFixture *f);
    void init() override;
    void new_frame() override;
};
