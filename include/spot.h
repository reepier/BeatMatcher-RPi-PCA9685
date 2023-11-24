#pragma once

#include <vector>
#include <string>

#include "config.h"
#include "debug.h"
#include "animator.h"

class SpotFixture;
class SpotAnimation;
class SpotAnimation1;

class SpotRack;
class SpotBack;

typedef std::vector<SpotFixture*> spot_vec;
// TODO Remove the individual spot class --> I will never need (for now) to control 1 spot individually.
/* --------------------------------------------------------------------

 #####  ######  ####### ####### 
#     # #     # #     #    #    
#       #     # #     #    #    
 #####  ######  #     #    #    
      # #       #     #    #    
#     # #       #     #    #    
 #####  #       #######    #    

/ ----------------------------------------------------------------------- */

class SpotFixture : public BaseFixture{
public:
    // Channels :
    int nCH = 8;
    uint8_t MASTER_DIMMER = 255;
    DMX_vec RGBWout = {0, 0, 0, 0}; // R G B W values (0-255)
    uint8_t strobe = 0;                       // strobe speed (0 none - 1 slow - 255 fast)
    uint8_t color_wheel = 0;                  // fixture preset colors (unused)
    uint8_t prog = 0;                         // fixture preset program (unused)

    // Constructor & Initializer
    SpotFixture(int addr, int ch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, ch, nm, id, mast){};
    void init(){};

    // Get Functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override {return DMX_vec{this->MASTER_DIMMER, this->RGBWout[R], this->RGBWout[G],this->RGBWout[B],this->RGBWout[W], this->prog, this->color_wheel, this->strobe};};
    void reset_channels(){
        this->RGBWout = {0, 0, 0, 0};
        this->strobe = 0;                       
        this->color_wheel = 0;                  
        this->prog = 0; 
    };

    // DMX_vec RGBW(simpleColor, uint8_t intensity = 255) override {};

};
extern SpotFixture spot_7, spot_8, spot_1, spot_2, spot_3, spot_4, spot_5, spot_6;

/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
class SpotAnimation : public BaseAnimation{
public:
    SpotFixture *fixture;
};

/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
// class SpotAnimation1 : public SpotAnimation{
// public:
//     uint8_t red;
//     uint8_t green;
//     uint8_t blue;
//     uint8_t white;

//     SpotAnimation1(SpotFixture *, uint8_t, uint8_t, uint8_t, uint8_t, std::string, std::string);
//     void init() override {BaseAnimation::init();};
//     void new_frame();
// };

/* --------------------------------------------------------------------
 #####  ######  ####### #######    ######     #     #####  #    #  #####  
#     # #     # #     #    #       #     #   # #   #     # #   #  #     # 
#       #     # #     #    #       #     #  #   #  #       #  #   #       
 #####  ######  #     #    #       ######  #     # #       ###     #####  
      # #       #     #    #       #   #   ####### #       #  #         # 
#     # #       #     #    #       #    #  #     # #     # #   #  #     # 
 #####  #       #######    #       #     # #     #  #####  #    #  #####  

/ ----------------------------------------------------------------------- */
/* frontal rack*/
class SpotRack : public BaseFixture{
public:
    spot_vec spots;        // pointers to spotFixture object
    int rack_size;                           // number of spots (derived)
    //std::vector<BaseAnimation *> animations; // vector containing animations

    SpotRack(spot_vec sp, std::string nm, int i, uint8_t mast=255): BaseFixture(-1, 0, nm, i, mast){
        this->id = i;
        this->spots = sp;
        this->rack_size = sp.size();

        for (auto s : spots){
            s->MASTER_DIMMER = this->MASTER_DIMMER;
        }
    };

    void init() override;     // empty function (useless)
    void init_front(); // initialize a frontal rack of spots
    void init_back();  // initialize a backgoround rack of spots
    
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override { return DMX_vec{}; }; // empty function (useless)
    void reset_spots(){
        for (spot_vec::iterator spot = spots.begin(); spot != spots.end(); spot++){
            (*spot)->reset_channels();
        }
    };

    DMX_vec RGBW(simpleColor, int intensity = 255) override;
};

extern SpotRack front_rack;
extern SpotRack back_rack;

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####  
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     # 
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #       
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####  
####### #   # #  #  #     # #######    #     #  #     # #   # #       # 
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     # 
#     # #     # ### #     # #     #    #    ### ####### #     #  #####  
*/

class SpotRackAnimtion : public BaseAnimation
{
public:
    SpotRack *fixture;
};

/*2 Oscillating colors, with one flashing randomly and another one as fluctuating background*/
class SpotRackAnimation1 : public SpotRackAnimtion
{
public:
    // animation parameters (set by user)
    bool flash_activation = true;
    DMX_vec back_color;
    DMX_vec flash_color;
    int sin_max_p_ms = 15000;
    int sin_min_p_ms = 5000;
    int rand_const_ms;
    int flash_len;
    double fluct_int = 0.4;
    double fluct_col = 0.25;

    // Internal variable (for storage between frames)
    std::vector<int> p_ms;             // range of periods for various sine wvaes
    std::vector<unsigned long> t_next; // timestamp of the next rise ()
    std::vector<unsigned long> t_prev; // timestamp of the prev rise () (memory)

    // fixture, color bckgd, color flash, oscil. period(ms)  max , min, mean time btwn flashes (ms), flash duration(ms), description, id
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, simpleColor f_col, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio){
        this->description = d;
        this->id = i;
        this->fixture = f;
        this->type = t;
        this->priority = prio;
    
        this->flash_color = this->fixture->RGBW(f_col);
        if (f_col==black)
            this->back_color = this->fixture->RGBW(b_col, 100);     // more intensity if there is no flash
        else
            this->back_color = this->fixture->RGBW(b_col, SPOTRACK_BG_INTENSITY);     // less intensity if there is a flash

        // this->sin_max_p_ms = pmax;
        // this->sin_min_p_ms = pmin;
        this->rand_const_ms = prand;
        this->flash_len = flen;

        this->update_palette(color_vec{b_col, f_col});
    }
    // overloaded constructor to create the same animation without flash (everything else being equal)
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio) : SpotRackAnimation1(f, b_col, b_col, prand, flen, d, i, t, prio){
        this->flash_activation = false;
    }

    void init() override;
    void new_frame();
};

#define STRB_FASTEST 180
#define STRB_FAST 80
#define STRB_MED 30
#define STRB_SLOW 1
/*Strobe*/
class SpotRackAnimation2 : public SpotRackAnimtion{
  public:
    simpleColor color;
    uint8_t strobe_spd;
    uint8_t strobe_max;
    uint8_t strobe_min;

    DMX_vec strobe_spds;

    double delta;
    const double DMX_min = 0;
    const double DMX_max = 240;
    const double deltaDmin = 60;  // absolute random variation of speed @DMX_min
    const double deltaDmax = 0;  // absolute random variation of speed @DMX_max
    

    SpotRackAnimation2(SpotRack *f, simpleColor c, uint8_t speed, std::string d, std::string i, AnimationType t, uint8_t prio){
        this->description = d;
        this->id = i;
        this->fixture = f;
        this->type = t;
        this->priority = prio;

        this->color =  c;
        this->strobe_spd = speed;
        this->strobe_spds.resize(this->fixture->rack_size);
        
        double delta = std::min(std::max( map((double)this->strobe_spd, DMX_min, DMX_max, deltaDmin, deltaDmax) ,deltaDmax),deltaDmin);          
        // this->delta = map((double)this->strobe_spd, DMX_min, DMX_max, deltaDmin, deltaDmax);
        this->strobe_max = std::min(std::max( (int)(strobe_spd +delta), 1),255);
        this->strobe_min = std::min(std::max( (int)(strobe_spd -delta), 1),255);

        this->update_palette(c);
    }
    
    void init() override;
    void new_frame() override;
private :
    void shake();
    unsigned long t_next_shake;
};