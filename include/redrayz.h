#include "animator.h"

#define NUM_LAS_PER_BOX 6

// fixture class declaration
class RedLaserBox;
class RedLaserGroup;


/* 
#                                       #####                              
#         ##    ####  ###### #####     #     # #####   ####  #    # #####  
#        #  #  #      #      #    #    #       #    # #    # #    # #    # 
#       #    #  ####  #####  #    #    #  #### #    # #    # #    # #    # 
#       ######      # #      #####     #     # #####  #    # #    # #####  
#       #    # #    # #      #   #     #     # #   #  #    # #    # #      
####### #    #  ####  ###### #    #     #####  #    #  ####   ####  #      */

/* This fixture represents a group individual laser channels that do not necessarily
 belong to the same gradation box.
 Every output channel from this "abstract" fixture points to a "real" channel from one 
 of the physical fixture represented by RedLaserBox class */

class RedLaserGroup : public BaseFixture{
  public :
    // Channels
    std::vector<DMX_channel*> lasers; // each element from this vector points to a RedLaserBox::output_channel element.
    int group_size;
    
    // Constructor
    RedLaserGroup(std::vector<DMX_channel*> channels, std::string nm, int addr, int i, uint8_t mast=255) : BaseFixture(addr, channels.size(), nm, i,mast){
      this->lasers = channels;
      this->group_size = channels.size();
    };

    // custom initializer declaration
    void init() override;

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override {return DMX_vec(0);};
    

    
};
extern RedLaserGroup lasergroup1, lasergroup2;


/*
#                                      ######                
#         ##    ####  ###### #####     #     #  ####  #    # 
#        #  #  #      #      #    #    #     # #    #  #  #  
#       #    #  ####  #####  #    #    ######  #    #   ##   
#       ######      # #      #####     #     # #    #   ##   
#       #    # #    # #      #   #     #     # #    #  #  #  
####### #    #  ####  ###### #    #    ######   ####  #    #  */

/* This class represents a pĥysical laser gradation box */

// fixture class definition
class RedLaserBox : public BaseFixture{
  public:
    //Channels :
    DMX_vec lasers;

    //custom constructor (also calls base constructor)
    RedLaserBox(int addr, int nch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, nch, nm, id, mast){
        lasers = DMX_vec{10, 20, 30, 40, 50, 60};//(nch, 0);
    };

    // custom initializer declaration
    void init() override {};

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;
    

    // Fixture Specific Color Macro
};
extern RedLaserBox laserbox1;



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
    RedLaserGroup *fixture;
};



/*
  ###          #######                 
 #   #         #       # #    # ###### 
#     #        #       #  #  #  #      
#     #        #####   #   ##   #####  
#     # ###    #       #   ##   #      
 #   #  ###    #       #  #  #  #      
  ###   ###    #       # #    # ###### 
  
 predefined, constant output, channel by channel*/

 class RedrayzAnimation0 : public RedrayzAnimation{
  public:
    DMX_vec values;

    RedrayzAnimation0(RedLaserGroup *f, uint8_t val, std::string d, std::string i, AnimationType t){
        this->fixture = f;
        this->description = d;
        this->id = i;
        this->type = t;
        
        this->values = DMX_vec(f->lasers.size(), val);
        this->autocolor = true;
        
        if (val!= 0) this->update_palette(red);
    }
  
    void init() override;
    void init(const color_vec&) override;
    void new_frame() override;
 };
/*
    #           ######                          ######                             
   ##           #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
  # #           #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
    #           ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
    #   ###     #   #   ###### #  # # #    #    #     # #    # #####       #   #   
    #   ###     #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
  ##### ###     #     # #    # #    # #####     ######   ####  #    #  ####    #   


Makeover of Bubbles Animation for red ray lasers
    - random burst of each laser
    - burst shape, length & period can be set
*/


class RedrayzAnimation1 : public RedrayzAnimation{
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
    RedrayzAnimation1(RedLaserGroup *f, Shape fshape,  time_t flen, time_t prand, std::string d, std::string i, AnimationType t, int prio, int mast=255)
    {
      this->description = d,this->id = i,this->fixture = f,this->type = t,this->priority = prio,this->master = mast;
      this->autocolor = true;

      this->flash_shape = fshape;
      this->burst_length = flen;
      this->rand_const_ms = prand;

      this->update_palette(red);
    }

    void init() override;
    void init(const color_vec&) override;
    void new_frame() override;
};


