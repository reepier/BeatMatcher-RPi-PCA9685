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
#       #    # #    # #      #   #     #     q# #   #  #    # #    # #      
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
    RedLaserGroup(std::vector<DMX_channel*> channels, std::string nm, int addr, int i, uint8_t mast, int in_addr) : BaseFixture(addr, channels.size(), nm, i,mast, in_addr){
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
extern RedLaserGroup lasergroup1/*, lasergroup2*/;


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
    RedLaserBox(int addr, int nch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, nch, nm, id, mast, 0){
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
extern RedLaserBox laserbox1, laserbox2, laserbox3;



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
    RedrayzAnimation(std::string d, std::string i, AnimationType typ, uint8_t mast, int prio, int_vec intens) : BaseAnimation(d, i, typ, mast, prio, intens){};
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

    RedrayzAnimation0(RedLaserGroup *f, uint8_t val, std::string d, std::string i, AnimationType t, int mast, int prio, int_vec intens)
    :RedrayzAnimation(d, i, t, mast, prio, intens){
      this->fixture = f;
            
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
    int flash_interval;
    int flash_length;

    // Dynamic variables (updated internally at each frame)
    std::vector<flash_vec> flashes;     //for each spot, stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time
    double t_unit;                    // internal, dynamic timescale. This timescale is artificially shrinked/elongated so that the average interval between bursts is 1

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;

    // Constructor
    RedrayzAnimation1(RedLaserGroup *f, Shape fshape,  time_t flen, time_t prand, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :RedrayzAnimation(d, i, t, mast, prio, intens){
      this->fixture = f;
      this->autocolor = true;

      this->flash_shape = fshape;
      this->flash_length = flen;
      this->flash_interval = prand;

      this->update_palette(red);
    }

    void init() override;
    void init(const color_vec&) override;
    void new_frame() override;
};


/*
 #####            #                                          ######                      
#     #          # #   #    #   ##   #       ####   ####     #     # ######   ##   ##### 
      #         #   #  ##   #  #  #  #      #    # #    #    #     # #       #  #    #   
 #####         #     # # #  # #    # #      #    # #         ######  #####  #    #   #   
#       ###    ####### #  # # ###### #      #    # #  ###    #     # #      ######   #   
#       ###    #     # #   ## #    # #      #    # #    #    #     # #      #    #   #   
####### ###    #     # #    # #    # ######  ####   ####     ######  ###### #    #   #   



*/
class RedrayzAnimation2 : public RedrayzAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    bool param_activate_flash;
    double density = 1.0;               // proportion of LED's flashing (0-100%) 
    
    int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
  
    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

    //AUTOCOLOR Constructor
    RedrayzAnimation2(RedLaserGroup *f, double dens, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :RedrayzAnimation(d, i, t, mast, prio, intens){
      //set BAse parameters
      this->fixture = f;
      this->autocolor = true;
      //Set cinematic parameters
      this->density = dens;
      units_index.resize(f->group_size);
      for(int i=0; i<units_index.size(); i++){
        units_index[i] = i;
      }
    }
    
    void init() override; //Standard init fcn
    void init(const color_vec&) override; //AUTOCOLOR init fcn
    void new_frame() override;
};


/*
 #####         ######                                    ######                      
#     #        #     # #  ####  # #####   ##   #         #     # ######   ##   ##### 
      #        #     # # #    # #   #    #  #  #         #     # #       #  #    #   
 #####         #     # # #      #   #   #    # #         ######  #####  #    #   #   
      # ###    #     # # #  ### #   #   ###### #         #     # #      ######   #   
#     # ###    #     # # #    # #   #   #    # #         #     # #      #    #   #   
 #####  ###    ######  #  ####  #   #   #    # ######    ######  ###### #    #   #   
 
Variant of the original beat matching animation : 
  - The strip is ivided into segments
  - The flash turns on all segments
  - The flash Decay turns of segments one by one as intensity decreases */

  class RedrayzAnimation3 : public RedrayzAnimation{
    public:
      // Animation parameters (constant or set by animation constructor)
      bool param_activate_flash;
      int fade_rate = 80;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)
  
      // Dynamic variables (updated internally at each frame)
      int_vec units_index;
      // AUTOCOLOR Constructor
      RedrayzAnimation3(RedLaserGroup *f, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
      :RedrayzAnimation(d, i, t, mast, prio, intens){
        //set BAse params
        this->description = d,this->id = i,this->fixture = f,this->type = t,this->master = mast,this->priority=prio;
        this->autocolor=true;
        //set cinematic params
        units_index.resize(f->group_size);

        for(int i=0; i<units_index.size(); i++){
          units_index[i] = i;
        }
      }

      void init() override;
      void init(const color_vec&) override;
      void new_frame() override;
  };
  