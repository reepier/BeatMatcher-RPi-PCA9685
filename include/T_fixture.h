#include "animator.h"

// fixture class declaration
class Fixture;

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */


// fixture class definition
class Fixture : public BaseFixture{
  public:
    
    //custom constructor (also calls base constructor)
    Fixture(int addr, int ch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, ch, nm, id, mast)
    {

    };
    // custom initializer declaration
    void init() override;

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;

    // Fixture Specific Color Macro
    DMX_vec RGBW(simpleColor, int intensity = 255) override;

};
extern Fixture name_of_the_fixture_object;



/*
   #                                                 
  # #   #    # # #    #   ##   ##### #  ####  #    # 
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
#     # # #  # # # ## # #    #   #   # #    # # #  # 
####### #  # # # #    # ######   #   # #    # #  # # 
#     # #   ## # #    # #    #   #   # #    # #   ## 
#     # #    # # #    # #    #   #   #  ####  #    # */
class FixtureAnimation : public BaseAnimation{
  public:
    Fixture *fixture;
};



class FixtureAnimation1 : public FixtureAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    int param1, param2;
    // Dynamic variables (updated internally at each frame)
    int var1, var2;
    
    // Constructor
    FixtureAnimation1(Fixture *f, /* specific args */ std::string d, std::string i, AnimationType t, int prio, int mast=255)
    {
        //set BAse parameters
        this->description = d, this->id = i, this->fixture = f, this->type=typ, this->priority=prio, this->master=mast;
        //Set cinematic parameters
        this->param1 /* = arg1 */;
        this->param2 /* = arg2 */;
        this->update_palette(/*argx*/);
    }
    //AUTOCOLOR Constructor
    FixtureAnimation1(Fixture *f, /* ..args...,*/ std::string d, std::string i, AnimationType t, int prio, int mast=255)
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


