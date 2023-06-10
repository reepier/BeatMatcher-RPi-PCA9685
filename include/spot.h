#include <vector>
#include <string>

#include "animator.h"


class SpotFixture;     
class SpotAnimation;
class SpotAnimation1;

class SpotRack;
class SpotBack;


class SpotFixture : public BaseFixture{
public:
    // Channels :
    std::vector<uint8_t> RGBW = {0,0,0,0}; // R G B W values (0-255)
    uint8_t strobe;                     // strobe speed (0 none - 1 slow - 255 fast)
    uint8_t color_wheel;                // fixture preset colors (unused)
    uint8_t prog;                       // fixture preset program (unused)

    // constructor
    SpotFixture(int addr): BaseFixture(addr){};
    void init();
};
extern SpotFixture spot;


class SpotAnimation : public BaseAnimation{
public:
    SpotFixture * fixture;
};


// simple constant RGBW scene
class SpotAnimation1 : public SpotAnimation{
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;

    SpotAnimation1(SpotFixture*,uint8_t,uint8_t,uint8_t,uint8_t, std::string, std::string);
    void init();
    void new_frame();
};





