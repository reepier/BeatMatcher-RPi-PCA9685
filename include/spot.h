#include <vector>
#include <string>

#include "animator.h"


class SpotFixture;     
class SpotAnimation;
class SpotAnimation1;

class SpotFront;
class SpotBack;



// TODO Remove the individual spot class --> I will never need (for now) to control 1 spot individually.
// -----------------------------------
// INDIVIDUAL SPOT
// -----------------------------------

class SpotFixture : public BaseFixture{
public:
    // Channels :
    int nCH = 8;
    std::vector<uint8_t> RGBW = {0,0,0,0}; // R G B W values (0-255)
    uint8_t strobe  =0;                     // strobe speed (0 none - 1 slow - 255 fast)
    uint8_t color_wheel =0;                // fixture preset colors (unused)
    uint8_t prog =0;                       // fixture preset program (unused)

    // constructor
    SpotFixture(int addr): BaseFixture(addr){};
    void init();

    //dmx output
    std::vector<uint8_t> buffer();
};
extern SpotFixture spot_g, spot_d, spot_1, spot_2, spot_3;


/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
class SpotAnimation : public BaseAnimation{
public:
    SpotFixture * fixture;
};


/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
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

// -----------------------------------
// RACK of SPOTS
// -----------------------------------
/* frontal rack*/
class SpotFront{
public:
    std::vector<SpotFixture*> spots;
    std::vector<BaseAnimation*> animations;

    /* Hard coded with 3 spots (temporarily?) */
    SpotFront(SpotFixture*,SpotFixture*,SpotFixture*);
    void init();
};


/*2 Oscillating colors, with one main and one */
class SpotFrontAnimation1{

};

/*Strobe*/
class SpotFrontAnimation2{

};



/* background rack*/
class SpotBack{
};