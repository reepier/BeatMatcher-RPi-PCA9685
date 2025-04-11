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
    SpotFixture(spot_type_t typ, int addr, int nch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, nch, nm, id, mast){
        this->type = typ;

        this->pixel = this->RGBW(black); // resize & initialise RGBWout vector

        // log(1, "Init. of ", this->name, " / Pixel size : ", this->pixel.size());
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

    SpotRack(spot_vec sp, std::string nm, int i, uint8_t mast=255): BaseFixture(-1, 0, nm, i, mast){
        this->id = i;
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

    DMX_vec RGBW(simpleColor, int intensity = 255) override;
};

extern SpotRack front_rack;
extern SpotRack rack_15;
extern SpotRack shehds_rack;
extern SpotRack rack_40;

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
};

/*
   #          ######                                            
  ##          #     # #    # #####  #####  #      ######  ####  
 # #          #     # #    # #    # #    # #      #      #      
   #          ######  #    # #####  #####  #      #####   ####  
   #   ###    #     # #    # #    # #    # #      #           # 
   #   ###    #     # #    # #    # #    # #      #      #    # 
 ##### ###    ######   ####  #####  #####  ###### ######  ####  
*/
// BUBBLES : background color with another color randomly apppearing
//TODO : whether in this animation or in a new one, add the possibility to chose a non-random sequence (traditional chaser)
// TODO add AUTOCOLOR
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
    int rand_const_ms;
    int flash_len;
    double fluct_int = 0.0;//0.4;
    double fluct_col = 0.0;

    // Internal variable (updated at every new_frame call)
    std::vector<int> p_ms;             // range of periods for various sine wvaes
    std::vector<flash_vec> flashes;     //for each spot, stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;

public :
    // fixture, color bckgd, color flash, oscil. period(ms)  max , min, mean time btwn flashes (ms), flash duration(ms), description, id
    // Multicolor flash constructor
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, color_vec f_cols, Shape fshape, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio){
        this->description = d;
        this->id = i;
        this->fixture = f;
        this->type = t;
        this->priority = prio;
        
        this->flash_colors = f_cols;
        this->back_color = b_col;
        this->flash_shape = fshape;
                // log(1, __func__, " ", this->id, " Palette : ", fcn::palette_to_string(this->flash_colors, '/'));

        this->rand_const_ms = prand;
        this->flash_len = flen;

        this->update_palette(color_vec{b_col});
        this->update_palette(f_cols);
    }
    // Base constructor
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, simpleColor f_col, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio){
        this->description = d;
        this->id = i;
        this->fixture = f;
        this->type = t;
        this->priority = prio;

        this->flash_colors.push_back(f_col);
        this->back_color = b_col;
        this->rand_const_ms = prand;
        this->flash_len = flen;


        this->update_palette(color_vec{b_col, f_col});
    }

    //overloaded constructors to add a master argument
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, color_vec f_cols, Shape fshape, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio, int mast)
        : SpotRackAnimation1(f, b_col, f_cols, fshape, prand, flen, d, i, t, prio)
    {
        this->master = mast;
    }
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, simpleColor f_col, Shape fshape, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio, int mast)
        : SpotRackAnimation1(f, b_col, f_col, fshape, prand, flen, d, i, t, prio)
    {
        this->master = mast;
    }

    //overloaded constructor to add a flash shape argument
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, simpleColor f_col, Shape fshape, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio) 
        : SpotRackAnimation1(f, b_col, f_col, prand, flen, d, i, t, prio){
        this->flash_shape = fshape;
    }
    // overloaded constructor to create the same animation without flash (everything else being equal)
    SpotRackAnimation1(SpotRack *f, simpleColor b_col, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio)
        : SpotRackAnimation1(f, b_col, b_col, prand, flen, d, i, t, prio){
        this->flash_activation = false;
    }

    //AUTOCOLOR Constructor
    SpotRackAnimation1(SpotRack *f, Shape fshape, int prand, int flen, std::string d, std::string i, AnimationType t, uint8_t prio){
        // Base parameters
        this->description = d, this->id = i, this->fixture = f, this->type = t, this->priority = prio;
        this->autocolor = true;             // animation relying on autocolor must be taggued as such
        // Cinematic Parameters
        this->rand_const_ms = prand;
        this->flash_shape = fshape;
        this->flash_len = flen;
    }
    
    
    void init() override;
    void init(const color_vec&) override;
    void new_frame();
};
/*
 #####          #####                                    
#     #        #     # ##### #####   ####  #####  ###### 
      #        #         #   #    # #    # #    # #      
 #####          #####    #   #    # #    # #####  #####  
#       ###          #   #   #####  #    # #    # #      
#       ###    #     #   #   #   #  #    # #    # #      
####### ###     #####    #   #    #  ####  #####  ###### 
*/
// STROBE : Random color flashes
// TODO add multicolor feature (change color at every new_frame)
// TODO add AUTOCOLOR
#define STRB_FASTEST 180
#define STRB_FAST 80
#define STRB_MED 30
#define STRB_SLOW 1
/*Strobe*/
class SpotRackAnimation2 : public SpotRackAnimation{
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
/*
 #####          #####                                     
#     #        #     # #    #   ##    ####  ###### #####  
      #        #       #    #  #  #  #      #      #    # 
 #####         #       ###### #    #  ####  #####  #    # 
      # ###    #       #    # ######      # #      #####  
#     # ###    #     # #    # #    # #    # #      #   #  
 #####  ###     #####  #    # #    #  ####  ###### #    # 
*/
// CHASER : each spots individually lights up and stays on for a user defined duration
class SpotRackAnimation3 : public SpotRackAnimation {
public:
    // Parameters
    color_vec colors;
    time_t chaser_period_ms; // duration between two turn-on
    time_t on_time;          // duration between turn-on and turn-off
    Shape decay;             //square, linear, exponential

    // Dynamic variables (updated internally at each frame)

    // Constructor
    SpotRackAnimation3(color_vec c, time_t spd, time_t dur, SpotRack *f, std::string d, std::string i)
    {
        this->description = d;
        this->id = i; 
        this->fixture = f;

        this->colors = c;

        this->update_palette(c);
    }

    void init() override;
    void new_frame() override;
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
// TODO update to something similar to AdressableLED::AnalogBeat
// Flashes on beat with background color --> similar to the original LED animation
class SpotRackAnimation4 : public SpotRackAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    bool param_activate_flash;
    simpleColor flash_color = black;            // color used for flashes
    simpleColor back_color = black;             // background color displayed inbetween flashes
    double density = 1.0;               // proportion of spots flashing (0-100%) 
    int fade_rate = 60;                 //[ms] rate of exponential flash decay



    /* TODO The following parameters are only accessible at SpotRackAnimation4 level, they must have 
    a (simplified) counterpart at BaseAnimation level. Autocolor constructor shall convert these into
    BaseAnimation member paramters. might even be worth it to set the followong params at construction ? 
    (easier maintenance if everything is set at construction rather than in many different code modules & blocks) */
    color_vec auth_flash_colors = {};   //list of authorized colors for flash_color parameter (empty == all colors authorized)
    color_vec auth_back_colors = {};    //list of authorized colors for back_color parameter (empty == all colors authorized)
    color_vec unauth_flash_colors = {}; //list of unauthorized colors for flash_color parameter (empty == no colors unauthorized)
    color_vec unauth_back_colors = {};  //list of unauthorized colors for flash_color parameter (empty == no colors unauthorized)
    
    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

    // Constructor
    SpotRackAnimation4(SpotRack *f, simpleColor f_col, simpleColor b_col, std::string d, std::string i, AnimationType typ, bool flash = true)
    {
        this->description = d;
        this->id = i; 
        this->fixture = f;

        this->type = typ;
        this->param_activate_flash = flash;

        this->flash_color = f_col;
        this->back_color = b_col;
        units_index.resize(this->fixture->spots.size());
        for(int i=0; i<units_index.size(); i++){
            units_index[i] = i;
        }
      
        this->update_palette(color_vec{f_col, b_col});
    }
    
    /*overloaded constructor autocolor
    TODO add a parameter to set at construction the number of colors ? or assign this parameter (random pick) at init()*/
    SpotRackAnimation4(SpotRack *f, double dens, std::string d, std::string i, AnimationType typ, bool flash = true){
        this->description = d, this->id = i, this->fixture = f; // set base parameters
        this->autocolor = true;             // animation relying on autocolor must be taggued as such
        
        this->param_activate_flash = flash;
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



// TODO add something similar to AdressableLED::DigitalBeat
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
    
    /* TODO The following parameters are only accessible at SpotRackAnimation5 level, they must have 
    a (simplified) counterpart at BaseAnimation level. Autocolor constructor shall convert these into
    BaseAnimation member paramters. might even be worth it to set the followong params at construction ? 
    (easier maintenance if everything is set at construction rather than in many different code modules & blocks) */
    color_vec auth_flash_colors = {};   //list of authorized colors for flash_color parameter (empty == all colors authorized)
    color_vec auth_back_colors = {};    //list of authorized colors for back_color parameter (empty == all colors authorized)
    color_vec unauth_flash_colors = {}; //list of unauthorized colors for flash_color parameter (empty == no colors unauthorized)
    color_vec unauth_back_colors = {};  //list of unauthorized colors for flash_color parameter (empty == no colors unauthorized)

    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

    // AUTOCOLOR Constructor
    SpotRackAnimation5(SpotRack *f, std::string d, std::string i, AnimationType typ=any, int prio=1, int mast=255){
        //set BAse params
        this->description = d,this->id = i,this->fixture = f,this->type = typ,this->master = mast,this->priority=prio;
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