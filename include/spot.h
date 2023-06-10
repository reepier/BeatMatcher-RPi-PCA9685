#include <vector>

#include "animator.h"


class SpotFixture;     
class SpotAnimation;
class SpotAnimation1;

class SpotRack;
class SpotBack;


class SpotFixture : public BaseFixture{
public:
    // Channels :
    std::vector<uint8_t> RGB = {0,0,0}; // R G B values (0-255)
    uint8_t strobe;                     // strobe speed (0 none - 1 slow - 255 fast)
    uint8_t color_wheel;                // fixture preset colors (unused)
    uint8_t prog;                       // fixture preset program (unused)

    // constructor
    SpotFixture(int addr): BaseFixture(addr){};
};


class SpotAnimation : public BaseAnimation{
    SpotFixture * fixture;
};


// simple constant RGB scene
class SpotAnimation1 : public SpotAnimation{

};





