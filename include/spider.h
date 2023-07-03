#include <vector>

#include "animator.h"

#define NLED 9
#define NCOL 4
#define PAN_POS 0
#define PAN_SPD 1
#define R 0
#define G 0
#define B 0
#define W 0

class SpiderFixture;
class SpiderAnimation;

// --------------------------------------
// SPIDER FIXTURE definition
// --------------------------------------

class SpiderFixture : public BaseFixture{
public :
    std::vector<uint8_t> pan;                // pan axis [posiiton, Speed]
    std::vector<uint8_t> tilt;               // tilt axes [tilt 1, tilt 2...]
    std::vector<std::vector<uint8_t>> RGBW;     // LED Pixels [ [R,G,B,W] , [R,G,B,W] , ... [R,G,B,W] ]
    uint8_t strobe;
    const int nCH = 43;

    SpiderFixture(int addr) : BaseFixture(addr){
        this->pan.resize(2);
        this->tilt.resize(3);
        this->RGBW.resize(NLED, std::vector<uint8_t>(NCOL));
    };

    void init() override;

    std::vector<uint8_t> buffer() override;
};
extern SpiderFixture spider(31);


// --------------------------------------
// SPIDER ANIMATION definition
// --------------------------------------

class SpiderAnimation : public BaseAnimation{
public :
    SpiderFixture * fixture;
    

};


// Static Monochrome Animation
class SpiderAnimation1 : public SpiderAnimation{
public :
    uint8_t RGBW[9][4];

    SpiderAnimation1();

    void init() override;
    void new_frame() override;
};
