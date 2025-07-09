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

/* 1 : Random bursts*/
/* 2 : Analog Beat*/

class LaserBeamAnimation : public BaseAnimation{
  public:
    LaserBeam *fixture;
};



class LaserBeamAnimation1 : public LaserBeamAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    int param1, param2;
    // Dynamic variables (updated internally at each frame)
    int var1, var2;
    
    //AUTOCOLOR Constructor
    LaserBeamAnimation1(LaserBeam *f, /* ..args...,*/ std::string d, std::string i, AnimationType t, int prio, int mast=255)
    {
        //set BAse parameters
        this->description = d, this->id = i, this->fixture = f, this->type=t, this->priority=prio, this->master=mast;
        this->autocolor = true;
        //Set cinematic parameters
        this->param1 /* = arg1 */;
        this->param2 /* = arg2 */;
    }

    void init() override; //Standard init fcn
    void init(const color_vec&) override; //AUTOCOLOR init fcn
    void new_frame() override;
};


