#include "animator.h"

// LaserBeam class declaration
class LaserBeam;

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */


// LaserBeam class definition
class LaserBeam : public BaseFixture{
  public:
    //channels
    DMX_vec pixel;

    //custom constructor (also calls base constructor)
    LaserBeam(int addr, int ch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, ch, nm, id, mast)
    {
        this->pixel = this->RGB(black);
    };
    // custom initializer declaration
    void init() override;

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;

    // LaserBeam Specific Color Macro
    DMX_vec RGB(simpleColor, int intensity = 255) override;

};
extern LaserBeam laserbeam;



/*
   #                                                 
  # #   #    # # #    #   ##   ##### #  ####  #    # 
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
#     # # #  # # # ## # #    #   #   # #    # # #  # 
####### #  # # # #    # ######   #   # #    # #  # # 
#     # #   ## # #    # #    #   #   # #    # #   ## 
#     # #    # # #    # #    #   #   #  ####  #    # */

class LaserBeamAnimation : public BaseAnimation{
    public:
      LaserBeam *fixture;
  };
  
/*
  ###          #######                 
 #   #         #       # #    # ###### 
#     #        #       #  #  #  #      
#     #        #####   #   ##   #####  
#     # ###    #       #   ##   #      
 #   #  ###    #       #  #  #  #      
  ###   ###    #       # #    # ##### */

class LaserBeamAnimation0 : public LaserBeamAnimation{
  public:
    simpleColor color = black;
  
    //  Constructor 
    LaserBeamAnimation0(LaserBeam* f, simpleColor c, std::string d, std::string i, AnimationType t=any, int prio=1, int mast=255){
      //set BAse parameters
      this->description = d, this->id = i, this->fixture = f, this->type=t, this->priority=prio, this->master=mast;
      //set cinematic parameters
      this->color = c;
      this->autocolor = false;
    }
    //  AUTOCOLOR Constructor
    LaserBeamAnimation0(LaserBeam* f, std::string d, std::string i, AnimationType t=any, int prio=1, int mast=255){
      //set BAse parameters
      this->description = d, this->id = i, this->fixture = f, this->type=t, this->priority=prio, this->master=mast;
      //set cinematic parameters
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

class LaserBeamAnimation1 : public LaserBeamAnimation
{
  public :
    // animation parameters (constant, set at construction)
    bool flash_activation = true;
    // DMX_vec back_color;
    simpleColor back_color;
    // DMX_vec flash_color;
    color_vec flash_colors;

    Shape flash_shape = gaussian; // default setting leads to gaussian flashes (of bubbles)
    // int sin_max_p_ms = 15000;
    // int sin_min_p_ms = 5000;
    int rand_const_ms;
    int flash_len;
    // double fluct_int = 0.4;
    // double fluct_col = 0.25;

    // Internal variable (updated at every new_frame call)
    flash_vec flashes;     // stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;

    //CONSTUCTORS
    // AUTOCOLOR constructor
    LaserBeamAnimation1(LaserBeam *f, Shape fshape, int prand, int flen, std::string d, std::string i, AnimationType t, int prio, int mast=255){
      //set Base paramters
      this->description = d,this->id = i,this->fixture = f,this->type = t,this->priority = prio,this->master = mast;
      this->autocolor = true;
      //set cinematic parameters
      this->flash_shape = fshape;
      this->rand_const_ms=prand;
      this->flash_len = flen;
    }


    void init() override;
    void init(const color_vec&) override;
    void new_frame();
};


/*
 #####            #                                          ######  #######    #    #######
#     #          # #   #    #   ##   #       ####   ####     #     # #         # #      #   
      #         #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #   
 #####         #     # # #  # #    # #      #    # #         ######  #####   #     #    #   
#       ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #   
#       ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #   
####### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #   
*/





class LaserBeamAnimation2 : public LaserBeamAnimation{
    public:
      // specific parameters
    bool param_activate_flash;
    simpleColor flash_color = black;            // flash color
    simpleColor back_color = black;             // background color
    
    int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
  
      // Dynamic variables (updated internally at each frame)
  
    //AUTOCOLOR constructor 
    LaserBeamAnimation2(LaserBeam* f, std::string d, std::string i, AnimationType typ, bool flash = true, uint8_t mast = 255){
      //set Base params 
      this->fixture = f,this->description = d,this->id = i, this->type = typ;
      this->autocolor=true;
      //set cinematic params
      this->param_activate_flash = flash;
    }
  
      void init() override;
      void init(const color_vec&) override;
      void new_frame() override;
      
  };


/*3 Heart Beat*/