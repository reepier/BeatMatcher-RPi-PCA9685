#include "animator.h"

#define NUM_LAS 6

// fixture class declaration
class RedrayLaser;

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */


// fixture class definition
class RedrayLaser : public BaseFixture{
  public:
    //Channels :
    DMX_vec output_channels;

    //custom constructor (also calls base constructor)
    RedrayLaser(int addr, int ch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, ch, nm, id, mast){
        output_channels = DMX_vec(NUM_LAS, 0);
    };
    // custom initializer declaration
    void init() override;

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;

    // Fixture Specific Color Macro
};
extern RedrayLaser redrayz;



/*
   #                                                 
  # #   #    # # #    #   ##   ##### #  ####  #    # 
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
#     # # #  # # # ## # #    #   #   # #    # # #  # 
####### #  # # # #    # ######   #   # #    # #  # # 
#     # #   ## # #    # #    #   #   # #    # #   ## 
#     # #    # # #    # #    #   #   #  ####  #    # */
class RedrayzAnimation : public BaseAnimation{
  public:
    RedrayLaser *fixture;
};



/*
   #          #######                 
  ##          #       # #    # ###### 
 # #          #       #  #  #  #      
   #          #####   #   ##   #####  
   #   ###    #       #   ##   #      
   #   ###    #       #  #  #  #      
 ##### ###    #       # #    # #####
 
 predefined, constant output, channel by channel*/

 class RedrayzAnimation1 : public RedrayzAnimation{
  public:
    DMX_vec values;

    RedrayzAnimation1(RedrayLaser *f, uint8_t val, std::string d, std::string i, AnimationType t){
        this->fixture = f;
        this->description = d;
        this->id = i;
        this->type = t;
        
        this->values = DMX_vec(NUM_LAS, val);
        
        if (val!= 0) this->update_palette(red);
    }
    
    void init() override;
    void new_frame() override;
 };
/*
  #####         ######                          ######                             
 #     #        #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
       #        #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
  #####         ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
 #       ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
 #       ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
 ####### ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   


Makeover of Bubbles Animation for red ray lasers
    - random burst of each laser
    - burst shape, length & period can be set
*/


class RedrayzAnimation2 : public RedrayzAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    bool flash_activation = true;
    Shape flash_shape = gaussian; // default setting leads to gaussian flashes (of bubbles)
    int rand_const_ms;
    int burst_length;

    // Dynamic variables (updated internally at each frame)
    std::vector<flash_vec> flashes;     //for each spot, stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;

    // Constructor
    RedrayzAnimation2(RedrayLaser *f, Shape fshape,  time_t flen, time_t prand, std::string d, std::string i, AnimationType t, int prio, int mast=255)
    {
      this->description = d;
      this->id = i; 
      this->fixture = f;
      this->type = t;
      this->priority = prio;
      this->master = mast;

      this->flash_shape = fshape;
      this->burst_length = flen;
      this->rand_const_ms = prand;

      this->update_palette(red);
    }

    void init() override;
    void new_frame() override;
};


