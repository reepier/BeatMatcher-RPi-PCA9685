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

    // Dynamic variables (updated internally at each frame)

    // Constructor
    FixtureAnimation1(Fixture *f, std::string d, std::string i)
    {
        this->description = d;
        this->id = i; 
        this->fixture = f;

        this->update_palette(...);
    }

    void init() override{BaseAnimation::init();};
    void new_frame() override{BaseAnimation::new_frame();};
};


