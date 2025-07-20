using namespace std;

#include "redrayz.h"
#include "DMXio.h"

RedLaserBox laserbox1(0, 6, "Grada Laser 1", 1);
RedLaserBox laserbox2(6, 6, "Grada Laser 2", 2);

RedLaserGroup lasergroup1(vector<DMX_channel*>{&laserbox1.lasers[0], &laserbox1.lasers[1], &laserbox1.lasers[2], &laserbox1.lasers[3], &laserbox1.lasers[4], &laserbox1.lasers[5],
                                               &laserbox2.lasers[0], &laserbox2.lasers[1], &laserbox2.lasers[2], &laserbox2.lasers[3], &laserbox2.lasers[4], &laserbox2.lasers[5]}, 
                          "RedRayz 1", RED_CTRL_ADR, 6);
/*RedLaserGroup lasergroup2(vector<DMX_channel*>{}, 
                           "Groupe Laser 2", 0, 2);*/


/*
#                                       #####                              
#         ##    ####  ###### #####     #     # #####   ####  #    # #####  
#        #  #  #      #      #    #    #       #    # #    # #    # #    # 
#       #    #  ####  #####  #    #    #  #### #    # #    # #    # #    # 
#       ######      # #      #####     #     # #####  #    # #    # #####  
#       #    # #    # #      #   #     #     # #   #  #    # #    # #      
####### #    #  ####  ###### #    #     #####  #    #  ####   ####  #      */

void RedLaserGroup::init(){
    // black, OFF animation
    animations.push_back(new RedrayzAnimation0(this, 0, " - ", "RED.0", any, 0, 0, int_vec{}));

    // All laser switched on
    animations.push_back(new RedrayzAnimation0(this, 255, "FULL ON", "RED.1.1", any, 255, 0, int_vec{}));
    // define animations

    // RANDOM BURST
    //
    animations.push_back(new RedrayzAnimation1(this, gaussian2,  8000,    2500, "Bulles très lent",      "RED.2.1.3", backer, 1, 255, int_vec{1}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,   10000,   3000, "Bulles très lent (+)",  "RED.2.1.5", backer, 1, 255, int_vec{1}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,   1500,    800,  "Bulles lent",           "RED.2.1.2", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, gaussian2,  1500,    4000, "Bulles lent (-)",       "RED.2.1.4", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,   600,     400,  "Bulles rapides",        "RED.2.1.1", any, 1, 255, int_vec{1,2,3}));
    
    animations.push_back(new RedrayzAnimation1(this, square, 5000,  1000,     "Very slow chaser",         "RED.2.2.3", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, square, 10000, 3000,     "VS, overlapping chaser",   "RED.2.2.4", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, square, 1500,  500,      "Slow chaser",              "RED.2.2.2", backer, 1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation1(this, square, 600,   400,      "Fast chaser",              "RED.2.2.1", any, 1, 255, int_vec{2,3}));

    animations.push_back(new RedrayzAnimation1(this, square, 50,   2000,  "Strobe très lent",   "RED.2.3.4", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, square, 50,   1000,  "Strobe lent",        "RED.2.3.3", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, square, 50,   500,   "Strobe rapide",      "RED.2.3.2", any,    1, 255, int_vec{3}));
    animations.push_back(new RedrayzAnimation1(this, square, 50,   100,   "Strobe très rapide", "RED.2.3.1", leader, 1, 255, int_vec{3}));

    animations.push_back(new RedrayzAnimation1(this, expdecay, 1500,  1500,  "Décharge très lent",     "RED.2.4.1", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 1500,  1000,  "Décharge très lent (+)", "RED.2.4.6", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 600,   700,   "Décharge lent",          "RED.2.4.2", any,    1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 700,   4000,  "décharge lent (-)",      "RED.2.4.4", any,    1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 200,   300,   "Décharge rapide",        "RED.2.4.3", leader, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 200,   2000,  "Décharge rapide (-)",    "RED.2.4.5", leader, 1, 255, int_vec{2,3}));

    animations.push_back(new RedrayzAnimation2(this, 1.0, "Beat",       "RED.2.1", leader, 1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation2(this, 0.7, "Beat 70%",   "RED.2.2", leader, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation2(this, 0.4, "Beat 40%",   "RED.2.3", leader, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation2(this, 0.2, "Beat 20%",   "RED.2.4", leader, 0, 255, int_vec{2,3}));

    animations.push_back(new RedrayzAnimation3(this, "Digital Beat", "RED.3.1", leader, 1, 255, int_vec{2,3}));

    this->activate_none();

    this->dump_animations("RedRayz");
}

/*
#                                      ######                
#         ##    ####  ###### #####     #     #  ####  #    # 
#        #  #  #      #      #    #    #     # #    #  #  #  
#       #    #  ####  #####  #    #    ######  #    #   ##   
#       ######      # #      #####     #     # #    #   ##   
#       #    # #    # #      #   #     #     # #    #  #  #  
####### #    #  ####  ###### #    #    ######   ####  #    #  */

DMX_vec RedLaserBox::buffer(){
    DMX_vec data(this->nCH);

    for (int i=0; i<this->nCH; i++){  // adjust intensity with fixture master dimmer
      data[i] = animator.master/255.0 * this->master/255.0 * this->lasers[i];
    }

    return data;
}



/*
  ###          #######                 
 #   #         #       # #    # ###### 
#     #        #       #  #  #  #      
#     #        #####   #   ##   #####  
#     # ###    #       #   ##   #      
 #   #  ###    #       #  #  #  #      
  ###   ###    #       # #    # ##### */

void RedrayzAnimation0::init(){
  BaseAnimation::init();
}
void RedrayzAnimation0::init(const color_vec& palette){
//TODO turn laser of if palette does not contain red

  /* Pas d'argument couleur défini pour le laser rouge --> il est toujours rouge*/
  // STANDARD init()
  RedrayzAnimation0::init();
}

void RedrayzAnimation0::new_frame(){
  BaseAnimation::new_frame();

  for (int i=0; i<this->fixture->group_size; i++){
    *(this->fixture->lasers[i]) = this->values[i] * this->fixture->master/255.0 * this->master/255.0;
  }
}



/*
    #           ######                          ######                             
   ##           #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
  # #           #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
    #           ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
    #   ###     #   #   ###### #  # # #    #    #     # #    # #####       #   #   
    #   ###     #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
  ##### ###     #     # #    # #    # #####     ######   ####  #    #  ####    */

void RedrayzAnimation1::init(){
  BaseAnimation::init();

  const int n_unit = this->fixture->group_size; //set the nuber of laser pixels to control
  this->flashes = vector<flash_vec>(n_unit, flash_vec(2));
  for (int i_unit=0; i_unit<n_unit; i_unit++){
    flashes[i_unit][i_next].time = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2*n_unit); 
    flashes[i_unit][i_prev].time = 0;
  }
}
void RedrayzAnimation1::init(const color_vec& palette){
  /* Pas d'argument couleur défini pour le laser rouge --> il est toujours rouge*/
  //STANDARD init()
  RedrayzAnimation1::init();
}

void RedrayzAnimation1::new_frame(){
  BaseAnimation::new_frame();
  
  long t = frame.t_current_ms;                // for readability
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
        t_next = t_next + rand_min_max(0, 2*n_unit*this->rand_const_ms);
      }

      // Compute pixel intensity
      switch (this->flash_shape){
        case square :
          flash_intensity = fcn::square(t, t_prev, burst_length, 0.0,1.0) + fcn::square(t, t_next, burst_length, 0.0,1.0);
          break;
        case gaussian2 :
          flash_intensity = fcn::gaussian2(t, t_prev, burst_length, 0.0,1.0) + fcn::gaussian2(t, t_next, burst_length, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
          break;
        case expdecay : // with an exponent of 3 instead of 1 to compensate for the diode non linearity
          flash_intensity = pow(fcn::exp_decay(t, t_prev, burst_length, 0.0, 1.0), 3.0);
          break;
        default :
          flash_intensity = fcn::gaussian(t, t_prev, burst_length, 0.0,1.0) + fcn::gaussian(t, t_next, burst_length, 0.0,1.0); //exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));
          break;
      }
    }else{
      flash_intensity = 0.0;
    }

    *(this->fixture->lasers[i_unit]) = flash_intensity * this->fixture->master * this->master/255.0;
  }
  balise("fausse balise");
}

/*
 #####            #                                          ######                      
#     #          # #   #    #   ##   #       ####   ####     #     # ######   ##   ##### 
      #         #   #  ##   #  #  #  #      #    # #    #    #     # #       #  #    #   
 #####         #     # # #  # #    # #      #    # #         ######  #####  #    #   #   
#       ###    ####### #  # # ###### #      #    # #  ###    #     # #      ######   #   
#       ###    #     # #   ## #    # #      #    # #    #    #     # #      #    #   #   
####### ###    #     # #    # #    # ######  ####   ####     ######  ###### #    #   #   



*/
void RedrayzAnimation2::init(){
  BaseAnimation::init();
}
void RedrayzAnimation2::init(const color_vec& palette){
  //AUTOCOLOR settings
  /* set animation colors based on color palette passed as argument*/
  /* since the laser boxes can only display red colo, just check wehter palette contains red, and
      activate flash param if it does*/
  if (std::find(palette.begin(), palette.end(), red) != palette.end()){
    this->param_activate_flash = true;
  }else{
    this->param_activate_flash = false;
  }

  // call standard init
  RedrayzAnimation2::init();
}

void RedrayzAnimation2::new_frame(){
  BaseAnimation::new_frame();

  // local variables for readability
  unsigned long t_ms = frame.t_current_ms;
  unsigned long t_last_beat_ms = sampler.t_last_new_beat;
  int_vec::size_type n_unit = units_index.size(); 
  int n_unit_on = density * n_unit;

  // enable / disable based on music status
  bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/;

  // for each new beat, sort segments in random order
  if (sampler.new_beat){
      units_index = fcn::randomized_vector(units_index);
      // log(1, fcn::num_to_str(n_unit_on), "/", fcn::num_to_str((int)n_unit), " : ",  fcn::vec_to_str(units_index, ','));
      // int_vec on_las = int_vec(units_index.begin(), units_index.begin()+n_unit_on);
      // log(1, fcn::vec_to_str(on_las, ','));
  }

  // Compute intensity value based on time elapsed since last beat
  float coef;
  if (param_activate_flash && auto_activate_flash)
    coef = fcn::exp_decay(t_ms, t_last_beat_ms, this->fade_rate, 0.0, 1.0);
  else
    coef = 0;
  
  // set each laser intensity
  for (int i=0; i<n_unit; i++){
    if (i<n_unit_on)
      *(this->fixture->lasers[units_index[i]]) = coef * this->fixture->master * this->master/255.0;
    else
      *(this->fixture->lasers[units_index[i]]) = 0;
  }
}

/*
 #####         ######                                    ######                      
#     #        #     # #  ####  # #####   ##   #         #     # ######   ##   ##### 
      #        #     # # #    # #   #    #  #  #         #     # #       #  #    #   
 #####         #     # # #      #   #   #    # #         ######  #####  #    #   #   
      # ###    #     # # #  ### #   #   ###### #         #     # #      ######   #   
#     # ###    #     # # #    # #   #   #    # #         #     # #      #    #   #   
 #####  ###    ######  #  ####  #   #   #    # ######    ######  ###### #    #   #   
 

 */

 void RedrayzAnimation3::init(){
  BaseAnimation::init();
}

void RedrayzAnimation3::init(const color_vec& palette){
  //AUTOCOLOR init
  /* set animation colors based on color palette passed as argument*/
  /* since the laser boxes can only display red colo, just check wehter palette contains red, and
      activate flash param if it does*/
      if (std::find(palette.begin(), palette.end(), red) != palette.end()){
        this->param_activate_flash = true;
      }else{
        this->param_activate_flash = false;
      }
    
  //Standard init
  RedrayzAnimation3::init();
}

void RedrayzAnimation3::new_frame(){
  BaseAnimation::new_frame();
  
  // for readability
  unsigned long t_ms = frame.t_current_ms;
  unsigned long t_last_beat_ms = sampler.t_last_new_beat;
  int_vec::size_type n_unit = units_index.size();

  bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/; //TODO useless ?

  // for each new beat, sort segments in random order
  if (sampler.new_beat)
      units_index = fcn::randomized_vector(units_index);

  // compute intensity value
  float coef = fcn::exp_decay(t_ms, t_last_beat_ms, this->fade_rate, 0.0, 1.0);
  //derive number of segments to turn on
  int n_unit_on = coef * n_unit;
  //chose which segments to turn on
  for (int i = 0; i<n_unit; i++){
      if (i<n_unit_on)
        *(this->fixture->lasers[units_index[i]]) = 1.0 *this->fixture->master*this->master/255.0;
      else
        *(this->fixture->lasers[units_index[i]]) = 0;
  }
}
