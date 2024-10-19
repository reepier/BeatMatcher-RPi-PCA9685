using namespace std;

#include "redrayz.h"

RedrayLaser redrayz(1, 6, "Redray laser", 1);

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */

void RedrayLaser::init(){
    // black, OFF animation
    animations.push_back(new RedrayzAnimation1(this, 0, " ", "RED.0", any));

    // All laser switched on
    animations.push_back(new RedrayzAnimation1(this, 255, "FULL ON", "RED.1.1", any));
    // define animations 

    this->activate_none();
}

DMX_vec RedrayLaser::buffer(){
    DMX_vec data(this->nCH);
    data = this->output_channels;
    return data;
}
/*
   #          #######                 
  ##          #       # #    # ###### 
 # #          #       #  #  #  #      
   #          #####   #   ##   #####  
   #   ###    #       #   ##   #      
   #   ###    #       #  #  #  #      
 ##### ###    #       # #    # #####*/
 void RedrayzAnimation1::init(){
    BaseAnimation::init();
    this->fixture->output_channels = this->values;
 }


  void RedrayzAnimation1::new_frame(){
    BaseAnimation::new_frame();
 }



/*
  #####         ######                          ######                             
 #     #        #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
       #        #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
  #####         ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
 #       ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
 #       ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
 ####### ###    #     # #    # #    # #####     ######   ####  #    #  ####    #  */

//  void RedrayzAnimation2::init(){

//  }


//   void RedrayzAnimation2::new_frame(){
    
//  }