#include <vector>
#include <string>

#include "animator.h"

class SpotFixture;
class SpotAnimation;
class SpotAnimation1;

class SpotRack;
class SpotBack;

// TODO Remove the individual spot class --> I will never need (for now) to control 1 spot individually.
// -----------------------------------
// INDIVIDUAL SPOT
// -----------------------------------

class SpotFixture : public BaseFixture{
public:
    // Channels :
    int nCH = 8;
    std::vector<uint8_t> RGBW = {0, 0, 0, 0}; // R G B W values (0-255)
    uint8_t strobe = 0;                       // strobe speed (0 none - 1 slow - 255 fast)
    uint8_t color_wheel = 0;                  // fixture preset colors (unused)
    uint8_t prog = 0;                         // fixture preset program (unused)

    // constructor
    SpotFixture(int addr) : BaseFixture(addr){};
    void init();

    // dmx output
    std::vector<uint8_t> buffer();
};
extern SpotFixture spot_g, spot_d, spot_1, spot_2, spot_3;

/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
class SpotAnimation : public BaseAnimation{
public:
    SpotFixture *fixture;
};

/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
class SpotAnimation1 : public SpotAnimation{
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;

    SpotAnimation1(SpotFixture *, uint8_t, uint8_t, uint8_t, uint8_t, std::string, std::string);
    void init();
    void new_frame();
};

// -----------------------------------
// RACK of SPOTS
// -----------------------------------
/* frontal rack*/
class SpotRack : public BaseFixture{
public:
    std::vector<SpotFixture *> spots;        // pointers to spotFixture object
    int rack_size;                           // number of spots (derived)
    //std::vector<BaseAnimation *> animations; // vector containing animations

    /* Hard coded with 2 or 3 spots (temporarily?) */
    SpotRack(SpotFixture* s1, SpotFixture* s2, SpotFixture* s3) : BaseFixture(512){ 
        this->spots.push_back(s1);
        this->spots.push_back(s2);
        this->spots.push_back(s3);};
    SpotRack(SpotFixture* s1, SpotFixture* s2) : BaseFixture(512){
        this->spots.push_back(s1);
        this->spots.push_back(s2);};

    void init(){};     // empty function (useless)
    void init_front(); // initialize a frontal rack of spots
    void init_back();  // initialize a backgoround rack of spots

    std::vector<uint8_t> buffer(){return std::vector<uint8_t>{};}; // empty function (useless)
};

extern SpotRack front_rack;
extern SpotRack back_rack;

class SpotRackAnimtion : public BaseAnimation
{
public:
    SpotRack *fixture;
};

/*2 Oscillating colors, with one flashing randomly and another one as fluctuating background*/
class SpotFrontAnimation1 : public SpotRackAnimtion
{
public:
    // aniation parameters (set by user)
    std::vector<uint8_t> color1;
    std::vector<uint8_t> color2;
    int sin_max_p_ms;
    int sin_min_p_ms;
    int rand_const_ms;
    int flash_len;

    // Internal variable (for storage between frames)
    std::vector<int> p_ms;             // range of periods for various sine wvaes
    std::vector<unsigned long> t_next; // timestamp of the next rise ()
    std::vector<unsigned long> t_prev; // timestamp of the prev rise () (memory)

    // fixture, color bckgd, color flash, oscil. period(ms)  max , min, mean time btwn flashes (ms), flash duration(ms), description, id
    SpotFrontAnimation1(SpotRack *f, std::vector<uint8_t> c1, std::vector<uint8_t> c2, int pmax, int pmin, int prand, int flen, std::string d, std::string i)
    {
        this->description = d;
        this->id = i;
        this->fixture = f;
        this->color1 = c1;
        this->color2 = c2;
        this->sin_max_p_ms = pmax;
        this->sin_min_p_ms = pmin;
        this->rand_const_ms = prand;
        this->flash_len = flen;
    }
    void init();
    void new_frame();
};

/*Strobe*/
class SpotFrontAnimation2
{
};