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
enum spot_type_t{
    FunGen_RGBW_12x1W,
    Shehds_RGBWAU_10x8W,
    Shehds_RGBWAU_7x18W
};

/*
 #####  ######  ####### ####### 
#     # #     # #     #    #    
#       #     # #     #    #    
 #####  ######  #     #    #    
      # #       #     #    #    
#     # #       #     #    #    
 #####  #       #######    #    
*/



class SpotFixture : public BaseFixture{
public:
    // Channels :
    int nCH = 8;
    DMX_vec pixel;// = {0, 0, 0, 0}; // R G B W... values (0-255)
    uint8_t strobe = 0;                       // strobe speed (0 none - 1 slow - 255 fast)
    uint8_t color_wheel = 0;                  // fixture preset colors (unused)
    uint8_t prog = 0;                         // fixture preset program (unused)
    spot_type_t type;   // spot 

    SpotRack * rack;

    // Constructor & Initializer
    SpotFixture(spot_type_t typ, int addr, int nch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, nch, nm, id, mast, 0){
        this->type = typ;

        this->pixel = this->RGBW(black); // resize & initialise RGBWout vector
    };
    void init(){};

    // Get Functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;
    void reset_channels(){
        this->pixel = this->RGBW(black);
        this->strobe = 0;                       
        this->color_wheel = 0;                  
        this->prog = 0; 
        this->master = 255;
    };
    
    DMX_vec RGBW(simpleColor c, int intensity = 255) override;

};
extern SpotFixture spot_1, spot_2, spot_3, spot_4, spot_5, spot_6; 
extern SpotFixture spot_7, spot_8, spot_9, spot_10, spot_11, spot_12;
extern SpotFixture spot_13, spot_14, spot_15, spot_16, spot_17, spot_18, spot_19, spot_20;  // New Shehds spots
extern SpotFixture spot_21, spot_22, spot_23, spot_24, spot_25, spot_26; 

/* /!\ /!\ Bullshit class --> I don't plan on coding animation for individual spots */
class SpotAnimation : public BaseAnimation{
public:
    SpotFixture *fixture;
};



/* --------------------------------------------------------------------
 #####  ######  ####### #######    ######     #     #####  #    #  #####  
#     # #     # #     #    #       #     #   # #   #     # #   #  #     # 
#       #     # #     #    #       #     #  #   #  #       #  #   #       
 #####  ######  #     #    #       ######  #     # #       ###     #####  
      # #       #     #    #       #   #   ####### #       #  #         # 
#     # #       #     #    #       #    #  #     # #     # #   #  #     # 
 #####  #       #######    #       #     # #     #  #####  #    #  #####  

/ ----------------------------------------------------------------------- */
class SpotRack : public BaseFixture{
public:
    spot_vec spots;        // pointers to spotFixture object
    int rack_size;                           // number of spots (derived)
    //std::vector<BaseAnimation *> animations; // vector containing animations

    SpotRack(spot_vec sp, std::string nm, int addr, int i, uint8_t mast, int in_addr): BaseFixture(addr, 0, nm, i, mast, in_addr){
        // this->id = i;
        this->spots = sp;
        this->rack_size = sp.size();

        for (auto s : spots){
            s->rack = this;
            s->master = this->master;
        }
    };

    void init() override {};     // empty for now (no need)
    // void init_front(); // initialize a frontal rack of spots
    // void init_back();  // initialize a backgoround rack of spots
    
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override { return DMX_vec{}; }; // empty function (useless)
    void reset_spots(){
        for (spot_vec::iterator spot = spots.begin(); spot != spots.end(); spot++){
            (*spot)->reset_channels();
        }
    };
    void set_master(int mast){
        for(auto spot : spots){
            spot->master = mast;
        }
    }

    DMX_vec RGBW(simpleColor, int intensity = 255){return DMX_vec(0,0);};
};

extern SpotRack spot_rack_1;
extern SpotRack spot_rack_2;
extern SpotRack spot_rack_3;
extern SpotRack spot_rack_4;

void front_rack_init();
void rack_15_init();
void rack_40_init();
void shehds_rack_init();
void global_rack_init();

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####  
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     # 
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #       
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####  
####### #   # #  #  #     # #######    #     #  #     # #   # #       # 
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     # 
#     # #     # ### #     # #     #    #    ### ####### #     #  #####  
*/

class SpotRackAnimation : public BaseAnimation
{
public:
    SpotRack *fixture;
    SpotRackAnimation(std::string d, std::string i, AnimationType typ, uint8_t mast, int prio, int_vec intens) : BaseAnimation(d, i, typ, mast, prio, intens){};
};

/*
  ###          ######                             #####                              
 #   #         #     # #        ##   # #    #    #     #  ####  #       ####  #####  
#     #        #     # #       #  #  # ##   #    #       #    # #      #    # #    # 
#     #        ######  #      #    # # # #  #    #       #    # #      #    # #    # 
#     # ###    #       #      ###### # #  # #    #       #    # #      #    # #####  
 #   #  ###    #       #      #    # # #   ##    #     # #    # #      #    # #   #  
  ###   ###    #       ###### #    # # #    #     #####   ####  ######  ####  #    # 
*/
// PLAIN COLOR : display one color on all every spot of the rack
class SpotRackAnimation0 : public SpotRackAnimation{
   public:
    simpleColor color = black;
    int intensity = 255;
    
    //BASE Constructor
    SpotRackAnimation0(SpotRack *f,  simpleColor c, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    : SpotRackAnimation(d, i, t, mast, prio, intens){
        //set BAse parameters
        this->fixture = f;
        // Cinematic params
        this->color = c;
    }

    //AUTOCOLOR Constructor
    SpotRackAnimation0(SpotRack *f,  std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    : SpotRackAnimation(d, i, t, mast, prio, intens){
        //set BAse parameters
        this->fixture = f;
        this->autocolor = true;
    }

    void init() override; //Standard init fcn
    void init(const color_vec&) override; //AUTOCOLOR init fcn
    void new_frame() override;

};
 
/*
   #          ######                          ######                             
  ##          #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
 # #          #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
   #          ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
   #   ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
   #   ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
 ##### ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
*/
// BUBBLES : background color with another color randomly apppearing on a randomly chosen spot
//TODO : whether in this animation or in a new one, add the possibility to chose a non-random sequence (traditional chaser)
class SpotRackAnimation1 : public SpotRackAnimation
{
private :
    // animation parameters (constant, set at construction)
    bool flash_activation = true;
    simpleColor back_color;
    color_vec flash_colors;

    Shape flash_shape = gaussian; // default setting leads to gaussian flashes (of bubbles)
    int sin_max_p_ms = 15000;
    int sin_min_p_ms = 5000;
    int flash_interval;
    int flash_length;
    double fluct_int = 0.0;//0.4;
    double fluct_col = 0.0;

    // Internal variable (updated at every new_frame call)
    std::vector<int> p_ms;              // range of periods for various sine wvaes //TODO remove 
    std::vector<flash_vec> flashes;     // for each spot, stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time
    double t_unit;                      // internal, dynamic timescale. This timescale is artificially shrinked/elongated so that the average interval between bursts is 1 (regardless of the real interval value (set externally and at construction))

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;

public :

    //AUTOCOLOR Constructor
    SpotRackAnimation1(SpotRack *f, Shape fshape, int finterv, int flen, std::string d, std::string i, AnimationType t, uint8_t prio,int mast, int_vec intens)
    : SpotRackAnimation(d, i, t, mast, prio, intens){
        // Base parameters
        this->fixture = f;
        this->autocolor = true;             // animation relying on autocolor must be taggued as such
        // Cinematic Parameters
        this->flash_interval = finterv;
        this->flash_shape = fshape;
        this->flash_length = flen;
    }
    
    
    void init() override;
    void init(const color_vec&) override;
    void new_frame();
};

/*
#                 #                                          ######                      
#    #           # #   #    #   ##   #       ####   ####     #     # ######   ##   ##### 
#    #          #   #  ##   #  #  #  #      #    # #    #    #     # #       #  #    #   
#    #         #     # # #  # #    # #      #    # #         ######  #####  #    #   #   
####### ###    ####### #  # # ###### #      #    # #  ###    #     # #      ######   #   
     #  ###    #     # #   ## #    # #      #    # #    #    #     # #      #    #   #   
     #  ###    #     # #    # #    # ######  ####   ####     ######  ###### #    #   #
*/
// Flashes on beat with background color --> similar to the original LED animation
class SpotRackAnimation4 : public SpotRackAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    bool param_activate_flash = true;           //old relic
    simpleColor flash_color = black;            // color used for flashes
    simpleColor back_color = black;             // background color displayed inbetween flashes
    double density = 1.0;               // proportion of spots flashing (0-100%) 
    int fade_rate = 60;                 //[ms] rate of exponential flash decay



    
    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

    
    /*overloaded constructor autocolor
    TODO add a parameter to set at construction the number of colors ? or assign this parameter (random pick) at init()*/
    SpotRackAnimation4(SpotRack *f, double dens, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    : SpotRackAnimation(d, i, t, mast, prio, intens){
        this->fixture = f; // set base parameters
        this->autocolor = true;             // animation relying on autocolor must be taggued as such
        
        this->density = dens;
        units_index.resize(this->fixture->spots.size());
        for(int i=0; i<units_index.size(); i++){
            units_index[i] = i;
        }
        /*The real color assignement is done at animation initialisation / activation (baseanimation.init()) 
        for safety purpose, at construction (or class definition), colors are set to black*/
    }


    void init() override;                   // does not much
    void init(const color_vec&) override;   // does same as init() + assigns color automatically
    void new_frame() override;
};



/*
#######        ######                                    ######                      
#              #     # #  ####  # #####   ##   #         #     # ######   ##   ##### 
#              #     # # #    # #   #    #  #  #         #     # #       #  #    #   
######         #     # # #      #   #   #    # #         ######  #####  #    #   #   
      # ###    #     # # #  ### #   #   ###### #         #     # #      ######   #   
#     # ###    #     # # #    # #   #   #    # #         #     # #      #    #   #   
 #####  ###    ######  #  ####  #   #   #    # ######    ######  ###### #    #   #   
*/
class SpotRackAnimation5 : public SpotRackAnimation{
  public:
    // Animation parameters (constant or set by animation constructor, init)
    simpleColor back_color;
    simpleColor flash_color;
    int fade_rate = 110;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
    

    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

    // AUTOCOLOR Constructor
    SpotRackAnimation5(SpotRack *f, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    : SpotRackAnimation(d, i, t, mast, prio, intens){
        //set BAse params
        this->fixture = f;
        this->autocolor=true;
        //set cinematic params
        units_index.resize(this->fixture->spots.size());
        
        for(int i=0; i<units_index.size(); i++){
          units_index[i] = i;
        }
    }

    void init() override;
    void init(const color_vec&) override;
    void new_frame() override;
  
};