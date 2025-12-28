#include "animator.h"

// LaserBeam class declaration
class LaserBeam;

enum laserbeam_type_t{
    RGB_500_Fat,
    RGB_1W
};


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
    laserbeam_type_t type;

    //custom constructor (also calls base constructor)
    LaserBeam(laserbeam_type_t typ, int addr, int ch, std::string nm, int id, uint8_t mast, int in_addr) : BaseFixture(addr, ch, nm, id, mast, in_addr)
    {
      this->type = typ;  
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
      LaserBeamAnimation(std::string d, std::string i, AnimationType typ, uint8_t mast, int prio, int_vec intens) : BaseAnimation(d, i, typ, mast, prio, intens){};
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
    LaserBeamAnimation0(LaserBeam* f, simpleColor c, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :LaserBeamAnimation(d, i, t, mast, prio, intens){
      //set BAse parameters
      this->fixture = f;
      //set cinematic parameters
      this->color = c;
      this->autocolor = false;
    }
    //  AUTOCOLOR Constructor
    LaserBeamAnimation0(LaserBeam* f, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :LaserBeamAnimation(d, i, t, mast, prio, intens){
        //set BAse parameters
      this->fixture = f;
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
    int flash_interval;
    int flash_length;
    // double fluct_int = 0.4;
    // double fluct_col = 0.25;

    // Internal variable (updated at every new_frame call)
    flash_vec flashes;     // stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time
    double t_unit;                    // internal, dynamic timescale. This timescale is artificially shrinked/elongated so that the average interval between bursts is 1

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;

    //CONSTUCTORS
    // AUTOCOLOR constructor
    LaserBeamAnimation1(LaserBeam *f, Shape fshape, int finterv, int flen, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :LaserBeamAnimation(d, i, t, mast, prio, intens){
      //set Base paramters
      this->fixture = f;
      this->autocolor = true;
      //set cinematic parameters
      this->flash_shape = fshape;
      this->flash_interval=finterv;
      this->flash_length = flen;
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
    bool param_activate_flash = true;;
    simpleColor flash_color = black;            // flash color
    simpleColor back_color = black;             // background color
    
    int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
  
      // Dynamic variables (updated internally at each frame)
  
    //AUTOCOLOR constructor 
    LaserBeamAnimation2(LaserBeam* f, std::string d, std::string i, AnimationType t, uint8_t mast, int prio, int_vec intens)
    :LaserBeamAnimation(d, i, t, mast, prio, intens){
        //set Base params 
      this->fixture = f;
      this->autocolor=true;
      //set cinematic params
    }
  
      void init() override;
      void init(const color_vec&) override;
      void new_frame() override;
      
  };


/*3 Heart Beat*/