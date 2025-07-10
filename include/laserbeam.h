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



/*
  #          ######                          ######                             
 ##          #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
# #          #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
  #          ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
  #   ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
  #   ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
##### ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
*/

  

/*
 #####            #                                          ######  #######    #    #######
#     #          # #   #    #   ##   #       ####   ####     #     # #         # #      #   
      #         #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #   
 #####         #     # # #  # #    # #      #    # #         ######  #####   #     #    #   
#       ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #   
#       ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #   
####### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #   
*/





class LaserBeamAnimation1 : public LaserBeamAnimation{
    public:
      // specific parameters
    bool param_activate_flash;
    simpleColor flash_color = black;            // flash color
    simpleColor back_color = black;             // background color
    
    int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
  
      // Dynamic variables (updated internally at each frame)
  
    //AUTOCOLOR constructor 
    LaserBeamAnimation1(LaserBeam* f, std::string d, std::string i, AnimationType typ, bool flash = true, uint8_t mast = 255){
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


