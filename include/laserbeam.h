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
    std::vector<DMX_vec> pixels;
    laserbeam_type_t type;

    //custom constructor (also calls base constructor)
    LaserBeam(laserbeam_type_t typ, int n_laser, int addr, int ch, std::string nm, int id, uint8_t mast, int in_addr) : BaseFixture(addr, ch, nm, id, mast, in_addr)
    {
      this->type = typ;  
      this->pixels = std::vector<DMX_vec>(n_laser, this->RGB(black));
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
    // Animation parameters (constant or set by animation constructor)
    // bool flash_activation = true;
    simpleColor back_color;
    color_vec flash_colors;

    Shape preset_shape = gaussian; // default setting leads to gaussian flashes (of bubbles)
    int preset_interval;
    int preset_duration;

    // Internal variable (updated at every new_frame call)
    std::vector<flash_vec> flashes;     // stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time
    double t_unit;                    // internal, dynamic timescale. This timescale is artificially shrinked/elongated so that the average interval between bursts is 1
    int current_param_shape_i;
    Shape current_param_shape, previous_param_shape, current_shape;

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
      this->preset_shape = fshape;
      this->preset_interval=finterv;
      this->preset_duration = flen;
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
    double preset_density = 1.0;               // proportion of LED's flashing (0-100%) 
    
    int preset_duration = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
  
    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

    //AUTOCOLOR constructor 
    LaserBeamAnimation2(LaserBeam* f, double dens, std::string d, std::string i, AnimationType t, uint8_t mast, int prio, int_vec intens)
    :LaserBeamAnimation(d, i, t, mast, prio, intens){
      //set Base params 
      this->fixture = f;
      this->autocolor=true;
      //set cinematic params
      this->preset_density = dens;
      units_index.resize(this->fixture->pixels.size());
      for(int i=0; i<units_index.size(); i++){
        units_index[i] = i;
      }
    }
  
      void init() override;
      void init(const color_vec&) override;
      void new_frame() override;
      
  };


/*3 Heart Beat*/