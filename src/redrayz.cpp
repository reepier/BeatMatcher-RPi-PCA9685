using namespace std;

#include "redrayz.h"
#include "DMXio.h"

#define FILL animations.push_back(new RedrayzAnimation0(this, black, " - ", "RED.0", any, 0, 0, int_vec{}));

RedLaserBox laserbox1(1, 6, "Grada Laser 1", 1);
RedLaserBox laserbox2(7, 6, "Grada Laser 2", 2);
RedLaserBox laserbox3(13, 6, "Grada Laser 3", 2);

RedLaserGroup lasergroup1(vector<DMX_channel*>{&laserbox1.lasers[0], &laserbox1.lasers[1], &laserbox1.lasers[2], &laserbox1.lasers[3], &laserbox1.lasers[4], &laserbox1.lasers[5],
                                               &laserbox2.lasers[0], &laserbox2.lasers[1], &laserbox2.lasers[2], &laserbox2.lasers[3], &laserbox2.lasers[4], &laserbox2.lasers[5],
                                               &laserbox3.lasers[0], &laserbox3.lasers[1], &laserbox3.lasers[2], &laserbox3.lasers[3], &laserbox3.lasers[4], &laserbox3.lasers[5]}, 
                          "RedRayz 1", RED_CTRL_ADR, 6, 255, 40);
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
    animations.push_back(new RedrayzAnimation0(this, black, " - ", "RED.0", any, 0, 0, int_vec{}));
    // All laser switched on
    animations.push_back(new RedrayzAnimation0(this, "FULL ON", "RED.1.1", any, 255, 0, int_vec{}));
    // define animations
    FILL
    FILL

    // RANDOM BURST
    animations.push_back(new RedrayzAnimation1(this, gaussian,  8000,    1800, "Bulles Très lent",      "RED.2.1.3", backer, 1, 255, int_vec{1}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,   10000,   2000, "Bulles Très lent (+)",  "RED.2.1.5", backer, 1, 255, int_vec{1}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,   1500,    500,  "Bulles Lent",           "RED.2.1.2", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,  1500,    2500, "Bulles Lent (-)",       "RED.2.1.4", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, gaussian,   600,     300,  "Bulles Rapides",        "RED.2.1.1", any, 1, 255, int_vec{1,2,3}));
    FILL
    FILL

    animations.push_back(new RedrayzAnimation1(this, square, 5000,  1000,     "Chaser Très lent",         "RED.2.2.3", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, square, 10000, 3000,     "Chaser Très lent +",   "RED.2.2.4", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, square, 1500,  500,      "Chaser Lent",              "RED.2.2.2", backer, 1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation1(this, square, 600,   400,      "Chaser Rapide",              "RED.2.2.1", any, 1, 255, int_vec{2,3}));
    FILL
    FILL

    animations.push_back(new RedrayzAnimation1(this, square, 50,   2000,  "Strobe Très lent",   "RED.2.3.4", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, square, 50,   1000,  "Strobe Lent",        "RED.2.3.3", backer, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, square, 50,   500,   "Strobe Rapide",      "RED.2.3.2", any,    1, 255, int_vec{3}));
    animations.push_back(new RedrayzAnimation1(this, square, 50,   100,   "Strobe Très rapide", "RED.2.3.1", leader, 1, 255, int_vec{3}));
    FILL
    FILL

    animations.push_back(new RedrayzAnimation1(this, expdecay, 1500,  1500,  "Décharge très lent",     "RED.2.4.1", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 1500,  1000,  "Décharge très lent (+)", "RED.2.4.6", backer, 1, 255, int_vec{1,2}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 600,   700,   "Décharge lent",          "RED.2.4.2", any,    1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 700,   4000,  "Décharge lent (-)",      "RED.2.4.4", any,    1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 200,   300,   "Décharge rapide",        "RED.2.4.3", leader, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation1(this, expdecay, 200,   2000,  "Décharge rapide (-)",    "RED.2.4.5", leader, 1, 255, int_vec{2,3}));
    FILL
    FILL

    animations.push_back(new RedrayzAnimation2(this, 1.0, "Beat",       "RED.2.1", leader, 1, 255, int_vec{1,2,3}));
    animations.push_back(new RedrayzAnimation2(this, 0.7, "Beat 70%",   "RED.2.2", leader, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation2(this, 0.4, "Beat 40%",   "RED.2.3", leader, 1, 255, int_vec{2,3}));
    animations.push_back(new RedrayzAnimation2(this, 0.2, "Beat 20%",   "RED.2.4", leader, 0, 255, int_vec{2,3}));
    FILL
    FILL

    animations.push_back(new RedrayzAnimation3(this, "Digital Beat", "RED.3.1", leader, 1, 255, int_vec{2,3}));
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL
    FILL

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





/**
######   #####  ######  #     #    #######               
#     # #     # #     # #  #  #    #        ####  #    # 
#     # #       #     # #  #  #    #       #    # ##   # 
######  #  #### ######  #  #  #    #####   #      # #  # 
#   #   #     # #     # #  #  #    #       #      #  # # 
#    #  #     # #     # #  #  #    #       #    # #   ## 
#     #  #####  ######   ## ##     #        ####  #    # 
*/

DMX_vec RedLaserGroup::RGB(simpleColor c, int intensity){
    DMX_vec temp;
    // store in vector temp the color vector of norm 255
    switch (c){ //TODO : remove ref_int and simply pass base lumo in RGB_norm argument
        case black      :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        case red        :                   temp = fcn::RGB_norm(DMX_vec{255,0,0});     break;
        // case green      :                   temp = fcn::RGB_norm(DMX_vec{0,255,0});     break;
        // case blue       :                   temp = fcn::RGB_norm(DMX_vec{0,0,255});     break;
        // case yellow     :                   temp = fcn::RGB_norm(DMX_vec{255,230,0});    break;
        // case orange     :                   temp = fcn::RGB_norm(DMX_vec{255,50,0});    break;
        // case sodium     :                   temp = fcn::RGB_norm(DMX_vec{255,25,0});    break;
        // case cyan       :                   temp = fcn::RGB_norm(DMX_vec{0,255,100});   break;
        // case purple     :                   temp = fcn::RGB_norm(DMX_vec{100,0,255});   break;    
        // case magenta    :                   temp = fcn::RGB_norm(DMX_vec{180,0,255});   break;
        // case pink       :                   temp = fcn::RGB_norm(DMX_vec{255,0,40});    break;
        // case w_white    :                   temp = fcn::RGB_norm(DMX_vec{140,255,6}); break;
        // case c_white    :                   temp = fcn::RGB_norm(DMX_vec{74,255,36}); break;
        // case gold       :                   temp = fcn::RGB_norm(DMX_vec{255,100,0});    break;
        // case light_red      :               temp = fcn::RGB_norm(DMX_vec{255,155,4});   break;
        // case light_cyan     :               temp = fcn::RGB_norm(DMX_vec{40,255,50});   break;
        // case light_blue     :               temp = fcn::RGB_norm(DMX_vec{30,255,255});   break;
        // case light_purple   :               temp = fcn::RGB_norm(DMX_vec{135,255,255});   break;
        // case light_magenta  :               temp = fcn::RGB_norm(DMX_vec{255,255,206});   break;
        // case light_pink     :               temp = fcn::RGB_norm(DMX_vec{255,200,60});   break;
        // case light_green    :               temp = fcn::RGB_norm(DMX_vec{40,255,10});   break;
        default         :                   temp = fcn::RGB_norm(DMX_vec{0,0,0});       break;
        }

        /* return a color vector with the same tint as temp but normalized according to a color specific 
        coefficient (to account for the fixtures's color by color response)*/
        return fcn::RGB_norm(temp, intensity);

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
    if (this->autocolor){
        switch (palette.size())
        {
        case 0:     this->color = black;        break;
        // case 1:     this->color = palette[0];   break;
        default:    this->color = *(palette.end()-1);   break;
        }
    }

  // STANDARD init()
  RedrayzAnimation0::init();
}

void RedrayzAnimation0::new_frame(){
  BaseAnimation::new_frame();

  for (int i=0; i<this->fixture->group_size; i++){
    DMX_vec       DMX_values = this->fixture->RGB(this->color);
    *(this->fixture->lasers[i]) = DMX_values[R] * this->fixture->master/255.0 * this->master/255.0;
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
        flashes[i_unit][i_next].time = rand_min_max(0.0, (double)n_unit);
        flashes[i_unit][i_prev].time = -1*rand_min_max(0.0, (double)n_unit);
        flashes[i_unit][i_next].color = fcn::random_pick(this->flash_colors);
        flashes[i_unit][i_prev].color = black;
  }
}
void RedrayzAnimation1::init(const color_vec& palette){
  // AUTOCOLOR init : assign flash colors & back color based on passed color palette :
  const int palette_size = palette.size();
  switch (palette_size)
  {
  case 0:
      this->flash_colors = color_vec{black}, this->back_color = black;            break;
  case 1:
      this->flash_colors = color_vec{palette[0]}, this->back_color = black;  break;
  case 2: 
      this->flash_colors = color_vec{palette[0]}, this->back_color = palette[1];  break;
  default:
      flash_colors = color_vec{fcn::random_pick(palette)},    back_color = fcn::random_pick(palette);     break;
  }

  //call STANDARD init()
  RedrayzAnimation1::init();
}

void RedrayzAnimation1::new_frame(){
  BaseAnimation::new_frame();

  //update external parameters :
    // Burst length (param Duration)
    const int current_duration      = clamp(
                                                map3_param(this->fixture->param1, (double)this->flash_length/5, (double)this->flash_length, 5*(double)this->flash_length),
                                                1000.0/FRATE,
                                                30000.0);
    // Burst Interval 
    const int current_interval    = clamp(
                                                map3_param(this->fixture->param2, (double)this->flash_interval/5, (double)this->flash_interval, 5*(double)this->flash_interval),
                                                1000.0/FRATE,
                                                30000.0);
    // Bakground Intensity 
    const int current_bkg_intensity = map3_param(this->fixture->param3, 0.0, (double)ADDRLED_BKG_INTENSITY_REF, 255.0);


  // long t = frame.t_current_ms;                // for readability
  const int n_unit = this->flashes.size();   // for readability

  // update internal timescale ("dt" in inversely proportionnal);
  this->t_unit += 1000.0/FRATE/current_interval;

  // for each laser "i" of the module
  for (int i_unit=0; i_unit < n_unit; i_unit++){
    // auto current_spot = this->fixture->spots[i_unit];           // for readability
    auto &current_unit_flashes = flashes[i_unit];                  // for readability
    auto &current_unit_next_flash = flashes[i_unit][i_next];       // for readability
    auto &current_unit_prev_flash = flashes[i_unit][i_prev];       // for readability
    double &t_next = current_unit_next_flash.time;
    double &t_prev = current_unit_prev_flash.time;
    simpleColor &c_next = current_unit_next_flash.color;
    simpleColor &c_prev = current_unit_prev_flash.color;

    const pixel ani_backgd_RGB = fixture->RGB(back_color, current_bkg_intensity);


    // if flash is actviated, compute the flash --> exp( -(spd.(t-t0))²)
    double flash_intensity; // 0 by default
    if (flash_activation){ //TODO remove activation booleans
      // when the flash passes, compute the next flash timestamp and update prev flash
      if (t_unit > t_next){
          
        t_prev = t_next;
        t_next = t_next + rand_min_max(0.0, 2.0*n_unit);
        c_prev = c_next;
        c_next = fcn::random_pick(this->flash_colors);
      }

      // Compute pixel intensity
      switch (this->flash_shape){
          case square : flash_intensity = fcn::square((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::square((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
              break;
          case gaussian : flash_intensity = fcn::gaussian((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::gaussian((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
              break;
          case gaussian2 : flash_intensity = fcn::gaussian2((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::gaussian2((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
              break;
          case expdecay : flash_intensity = fcn::exp_decay((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0);
              break;
          default : flash_intensity = fcn::gaussian((t_unit-t_prev)*current_interval, 0, current_duration, 0.0,1.0) + fcn::gaussian((t_next-t_unit)*current_interval, 0, current_duration, 0.0,1.0);
              break;
      }
    }else{
      flash_intensity = 0.0;
    }

    DMX_vec frame_flash_RGB = (t_unit-t_prev > t_next-t_unit) ? fixture->RGB(c_next) : this->fixture->RGB(c_prev);
    DMX_vec unit_final_RGB(3, 0);
    unit_final_RGB[R] = clamp( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[R] + flash_intensity * frame_flash_RGB[R]  ),0,255); 
    unit_final_RGB[G] = clamp( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[G] + flash_intensity * frame_flash_RGB[G]  ),0,255);
    unit_final_RGB[B] = clamp( (int)( (1.0-pow(flash_intensity, 0.2)) * ani_backgd_RGB[B] + flash_intensity * frame_flash_RGB[B]  ),0,255);


    *(this->fixture->lasers[i_unit]) = unit_final_RGB[R] * this->fixture->master/255.0 * this->master/255.0;
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
    // AUTOCOLOR init
    switch (palette.size())
    {
    case 0:     this->flash_color=black,        this->back_color=black;
        break;
    case 1:     this->flash_color=palette[0];   this->back_color=black;
        break;
    case 2:     this->flash_color=palette[0],   this->back_color=palette[1];
        break;
    default:    this->flash_color=black,        this->back_color=black;
        break;
    }

  // call standard init
  RedrayzAnimation2::init();
}

void RedrayzAnimation2::new_frame(){
  BaseAnimation::new_frame();

  //update external parameters :
    // fade rate (param Duration)
    const int current_fade_rate_ms    = map3_param(this->fixture->param1, 1000.0/FRATE, (double)this->fade_rate, 1000.0);
    // Bakground Intensity 
    const int current_bkg_intensity   = map3_param(this->fixture->param3, 0.0, 50.0, 255.0);
    // Ratio 
    const double current_ratio        = map3_param(this->fixture->param4, 0.1, this->density, 1.0);

    
  // local variables for readability
  const unsigned long t_ms = frame.t_current_ms;
  const unsigned long t_last_beat_ms = sampler.t_last_new_beat;
  int_vec::size_type n_unit = units_index.size(); 
  int n_unit_on = current_ratio * n_unit;


  // for each new beat, sort segments in random order
  if (sampler.new_beat){
      units_index = fcn::randomized_vector(units_index);
  }

  // Compute intensity value based on time elapsed since last beat
  double coef = fcn::exp_decay(t_ms, t_last_beat_ms, current_fade_rate_ms, 0.0, 1.0);

  // set each laser intensity
  for (int i_unit=0; i_unit<n_unit; i_unit++){

        pixel backgd_RGB    = this->fixture->RGB(back_color, current_bkg_intensity);
        pixel flash_RGB     = this->fixture->RGB(flash_color);
        pixel final_RGB     = this->fixture->RGB(black); //initialization before calculations

    if (i_unit<n_unit_on){
      for(auto i_subpix = 0; i_subpix<final_RGB.size(); i_subpix++){
          final_RGB[i_subpix] = coef * flash_RGB[i_subpix] + (1-pow(coef, 0.2)) * backgd_RGB[i_subpix];
      }
    }else{
      final_RGB = backgd_RGB;
    }

    *(this->fixture->lasers[units_index[i_unit]]) = final_RGB[R] * this->fixture->master/255.0 * this->master/255.0;
    
  }

    log(2, fcn::num_to_str(this->fixture->param4), " : ", fcn::num_to_str(current_ratio), ", ",n_unit, ", ",fcn::num_to_str(n_unit_on));
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
  
  // fade rate (param Duration)
  const int current_fade_rate_ms    = map3_param(this->fixture->param1, 1000.0/FRATE, (double)this->fade_rate, 1000.0);
  // Bakground Intensity 
  // const int current_bkg_intensity   = map3_param(this->fixture->param3, 0.0, (double)ADDRLED_BKG_INTENSITY_REF, 255.0);
  // Ratio 
  const double current_ratio        = map3_param(this->fixture->param4, 0.1, 0.7, 1.0);

  // for readability
  unsigned long t_ms = frame.t_current_ms;
  unsigned long t_last_beat_ms = sampler.t_last_new_beat;
  int_vec::size_type n_unit = units_index.size();

//TODO remove activation booleans (param_activate_flash & auto_activate_flash)
  bool auto_activate_flash = (sampler.state == BEAT) /*&& (t_ms-sampler.t_beat_tracking_start < MAX_CONT_FLASH)*/;

  // for each new beat, sort segments in random order
  if (sampler.new_beat)
      units_index = fcn::randomized_vector(units_index);

  // compute intensity value
  float coef = fcn::exp_decay(t_ms, t_last_beat_ms, current_fade_rate_ms, 0.0, 1.0);
  //derive number of segments to turn on
  int n_unit_on = coef * n_unit * current_ratio;
  //chose which segments to turn on
  for (int i = 0; i<n_unit; i++){ //TODO leave one unit on ?
      if (i<n_unit_on)
        *(this->fixture->lasers[units_index[i]]) = 1.0 *this->fixture->master*this->master/255.0;
      else
        *(this->fixture->lasers[units_index[i]]) = 0;
  }
}
