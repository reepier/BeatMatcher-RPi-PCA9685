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

    // RANDOM BURST
    //
    animations.push_back(new RedrayzAnimation2(this, gaussian, 600,   400,      "Fast gaussian bursts",        "RED.2.1.1", any, 1));
    animations.push_back(new RedrayzAnimation2(this, gaussian, 1500,  800,      "Slow gaussian bursts",        "RED.2.1.2", any, 1));
    animations.push_back(new RedrayzAnimation2(this, gaussian2, 8000,  2500,    "Very slow gaussian bursts",   "RED.2.1.3", any, 1));
    animations.push_back(new RedrayzAnimation2(this, gaussian2, 1500,  4000,    "Scarce gaussian bursts",      "RED.2.1.4", any, 1));
    
    animations.push_back(new RedrayzAnimation2(this, square, 600,   400,      "Fast square bursts",          "RED.2.2.1", any, 1));
    animations.push_back(new RedrayzAnimation2(this, square, 1500,  500,      "Slow square bursts",          "RED.2.2.2", any, 1));
    animations.push_back(new RedrayzAnimation2(this, square, 5000,  1000,     "Very slow square bursts",     "RED.2.2.3", any, 1));

    animations.push_back(new RedrayzAnimation2(this, square, 50,   100,   "VF Strob square bursts",   "RED.2.3.1", any, 1));
    animations.push_back(new RedrayzAnimation2(this, square, 50,   500,   "F strobe square bursts",   "RED.2.3.2", any, 1));
    animations.push_back(new RedrayzAnimation2(this, square, 50,   1000,  "S strobe bursts",          "RED.2.3.3", any, 1));
    animations.push_back(new RedrayzAnimation2(this, square, 50,   2000,  "VS strobe bursts",          "RED.2.3.4", any, 1));


    animations.push_back(new RedrayzAnimation2(this, expdecay, 1500, 1500,  "Vslow exponential burst",   "RED.2.4.1", any, 1));
    animations.push_back(new RedrayzAnimation2(this, expdecay, 600, 700,   "Slow exponential burst",    "RED.2.4.2", any, 1));
    animations.push_back(new RedrayzAnimation2(this, expdecay, 200, 300,   "Fast exponential burst",    "RED.2.4.3", any, 1));
    animations.push_back(new RedrayzAnimation2(this, expdecay, 700, 4000,  "Scarce slow exponential burst",  "RED.2.4.4", any, 1));
    animations.push_back(new RedrayzAnimation2(this, expdecay, 200, 2000,  "Scarce fast exponential burst",  "RED.2.4.5", any, 1));

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

void RedrayzAnimation2::init(){BaseAnimation::init();
  const int n_unit = NUM_LAS; //set the nuber of laser pixels to control
  this->flashes = vector<flash_vec>(n_unit, flash_vec(2));
  for (int i_unit=0; i_unit<n_unit; i_unit++){
    flashes[i_unit][i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2*n_unit); 
    flashes[i_unit][i_prev].time = 0;
  }
}


void RedrayzAnimation2::new_frame(){
  BaseAnimation::new_frame();
  
  long t = frame.t_current_ms;         // for readability
  const int n_unit = this->flashes.size();   // for readability

  // for each laser "i" of the module
  for (int i_unit=0; i_unit < n_unit; i_unit++){
    // auto current_spot = this->fixture->spots[i_unit];           // for readability
    auto &current_unit_flashes = flashes[i_unit];                  // for readability
    auto &current_unit_next_flash = flashes[i_unit][i_next];       // for readability
    auto &current_unit_prev_flash = flashes[i_unit][i_prev];       // for readability
    time_t &t_next = current_unit_next_flash.time;
    time_t &t_prev = current_unit_prev_flash.time;

    // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
    double flash_intensity; // 0 by default
    if (flash_activation){
      // when the flash passes, compute the next flash timestamp and update prev flash
      if (t > t_next){
          
        t_prev = t_next;
        t_next = t_next + rand_min_max(this->flash_len, 2*n_unit*this->rand_const_ms);
      }

      // Compute pixel intensity
      switch (this->flash_shape){
        case square :
          flash_intensity = fcn::square(t, t_prev, flash_len, 0.0,1.0) + fcn::square(t, t_next, flash_len, 0.0,1.0);
          break;
        case gaussian2 :
          flash_intensity = fcn::gaussian2(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian2(t, t_next, flash_len, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
          break;
        case expdecay : // with an exponent of 3 instead of 1 to compensate for the diode non linearity
          flash_intensity = pow(fcn::exp_decay(t, t_prev, flash_len, 0.0, 1.0), 3.0);
          break;
        default :
          flash_intensity = fcn::gaussian(t, t_prev, flash_len, 0.0,1.0) + fcn::gaussian(t, t_next, flash_len, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
          break;
      }
    }else{
      flash_intensity = 0.0;
    }

    this->fixture->output_channels[i_unit] = flash_intensity*this->master;
  }
  balise("fausse balise");
}