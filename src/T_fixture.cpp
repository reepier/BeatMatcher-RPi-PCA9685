/** TEMPALTE FILE for a new fixture module*/
#include "T_fixture.h"

using namespace std;


Fixture fixturename;

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */

void Fixture::init(){
    /*declare animations*/
}

DMX_vec Fixture::buffer(){
    /*build DMX sub-frame*/
    return DMX_vec{ /*...*/};
}

/**
######   #####  ######  #     #    #######               
#     # #     # #     # #  #  #    #        ####  #    # 
#     # #       #     # #  #  #    #       #    # ##   # 
######  #  #### ######  #  #  #    #####   #      # #  # 
#   #   #     # #     # #  #  #    #       #      #  # # 
#    #  #     # #     # #  #  #    #       #    # #   ## 
#     #  #####  ######   ## ##     #        ####  #    # 
*/

DMX_vec Fixture::RGBW(simpleColor c, int intensity){
    /*define color catalog as DMX_vec*/
}

/*
   #                                                 
  # #   #    # # #    #   ##   ##### #  ####  #    # 
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
#     # # #  # # # ## # #    #   #   # #    # # #  # 
####### #  # # # #    # ######   #   # #    # #  # # 
#     # #   ## # #    # #    #   #   # #    # #   ## 
#     # #    # # #    # #    #   #   #  ####  #    # */

/*TODO proposition : for every animation that requires it, define functions such as get_flash_color(const color_vec& palette)
 and get_back_color(const color_vec& palette) that parse the palette (passed as argument) and compose it with internal
  parameters "(un)authorized_flash_color", (un)authorized_back_color. This could yield the perfect trade-off between the master palette 
  and each animation's own limitations (i.e. rendering complex colors at low intensity) */
color_vec FixtureAnimation1::get_flash_color(const color_vec& palette){

}
color_vec FixtureAnimation1::get_flash_color(const color_vec& palette){
    
}

void FixtureAnimation1::init(){
    BaseAnimation::init();
}
void FixtureAnimation1::init(const color_vec& palette){
    //AUTOCOLOR settings
    /* set animation colors based on color palette passed as argument*/
    
    // call standard init
    FixtureAnimation1::init();
}

void FixtureAnimation1::new_frame(){
    BaseAnimation::new_frame();
    // update fixture channels at every computational step
    
}