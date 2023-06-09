#include <vector>

#include "animator.h"


class SpotFixture;     
class SpotAnimation;
class SpotAnimation1;

class SpotRack;


class SpotFixture : public BaseFixture{
    
    // Channels :
    std::vector<uint8_t> RGB = {0,0,0}; // R G B values from 0 to 
    uint8_t strobe, color_wheel, prog;
    int addr;

};


class SpotAnimation : public BaseAnimation{
    SpotFixture * fixture
};


// simple constant RGB scene
class SpotAnimation1 : public SpotAnimation{

};





