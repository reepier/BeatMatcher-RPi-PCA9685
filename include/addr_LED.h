#pragma once

#include "animator.h"

//
#define MAX_PIX_PER_UNI     170 //
#define MAX_SUBPIX_PER_UNI  510 // maximum number of subpixels arried over 1 universe (1 universe can only carry complete pixels (BC-204 limitation))
// WS2815 led strip config
  // Config paramters
  constexpr int NUM_BAR = 18;                       // Total Number of bars
  constexpr int NUM_SEG = 3*NUM_BAR;             // Total number of segments (across all bars)
  // Quasi constants
  constexpr int NUM_PIX_BAR = 58;        // number of pixels per bar
  // Derivatives
  constexpr int NUM_PIX = NUM_BAR*NUM_PIX_BAR;           // Total number of pixels
  constexpr int NUM_SUBPIX = 3*NUM_PIX;  // Total number of artnet dmx datas
  
  /* Artnet Controler configuraiton : 
  Channel 1 : 
    Start Universe : 2 (corresponds to ola universe 1 while Start uni 2 correspond to ola universe 0)
    CHannel start : 1 
    Num pixel : 680 (MAX)
  Channel 2 : 
    Start Universe : 2 (corresponds to ola universe 1 while Start uni 2 correspond to ola universe 0)
    CHannel start : 1 
    Num pixel : 680 (MAX)*/

enum strip_subdiv_t{
  group,// Group of bars
  bar,  // Led bar
  seg,  // Led segment (fraction of a bar)
  pix   // Individual pixel
};


// bars configuration
typedef std::vector<int_vec> LED_bar_config ;
inline LED_bar_config bar_config = {/*bar1*/  {0,  58},    //  {start pixel, end pixel}
                                    /*bar2*/  {58, 116},
                                    /*bar3*/  {116, 174},
                                    /*bar4*/  {174, 232},
                                    /*bar5*/  {232+1, 290},
                                    /*bar6*/  {290+1, 348},
                                    /*bar7*/  {348, 406},
                                    /*bar8*/  {406, 464},
                                    /*bar9*/  {464, 522},
                                    /*bar10*/ {522, 580},
                                    /*bar11*/ {580, 638},
                                    /*bar12*/ {638, 696},
                                    /*bar13*/ {696, 754},
                                    /*bar14*/ {754, 812},
                                    /*bar15*/ {812, 870},
                                    /*bar16*/ {870, 928},
                                    /*bar17*/ {928, 986},
                                    /*bar18*/ {986, 1044}
                                  };
                                  
typedef std::vector<int_vec> LED_group_config ;
  //groups of bar
inline LED_group_config group_conf = {{0,1,2}, {3,4,5}, {6,7,8}, {9,10,11}, {12,13,14}, {15,16,17}};

// fixture class declaration
class AddressableLED;

/*
#######                                     
#       # #    # ##### #    # #####  ###### 
#       #  #  #    #   #    # #    # #      
#####   #   ##     #   #    # #    # #####  
#       #   ##     #   #    # #####  #      
#       #  #  #    #   #    # #   #  #      
#       # #    #   #    ####  #    # ###### */


// fixture class definition
class AddressableLED : public BaseFixture{
  public:
    //each individual led pixel RGB value is stored in this vector
    pixel_vec pixels;

    // Fixture Controler :


    //custom constructor (also calls base constructor)
    AddressableLED(int uni, int addr, int ch, std::string nm, int id, uint8_t mast, int in_addr) : BaseFixture(addr, ch, nm, id, mast, in_addr){
      this->pixels.resize(NUM_PIX, DMX_vec(3)); // resize the vector : NUM_PIX pixels, each pixel has 3 subpixels (RGB)
    };

    // custom initializer declaration
    void init() override;

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;

    // Fixture Specific Color Macro
    DMX_vec RGB(simpleColor, int intensity = 255) override;
    
    // Useful color setters
      // set bar color 
    void set_bars_color(int_vec bar_nums, simpleColor color){};

    void set_allpix_color(DMX_vec color){
      for (auto& pix : this->pixels){
        pix = color;
      }
    }
    void set_allpix_color(simpleColor color, uint8_t intensity = 255){
      set_allpix_color(this->RGB(color, intensity));
    }

    
    void set_segment_color(int seg, DMX_vec color){
      //DO something
      auto first_pix = this->pixels.begin() + seg*NUM_PIX/NUM_SEG;
      auto last_pix = first_pix + NUM_PIX/NUM_SEG;
      for (auto pix = first_pix; pix != last_pix; pix++){
        (*pix) = color;
      }
    }
    void set_segment_color(int seg, simpleColor color, uint8_t intensity = 255){
      set_segment_color(seg, this->RGB(color, intensity));
    }

    void set_bar_color(int bar, DMX_vec color){
      // auto first_pix = this->pixels.begin() + bar*NUM_PIX/NUM_BAR;
      auto first_pix = this->pixels.begin() + bar_config[bar][0];
      auto last_pix = this->pixels.begin() + bar_config[bar][1];

      for (auto pix = first_pix; pix != last_pix; pix++){
        (*pix) = color;
      }
    }
    void set_bar_color(int bar_num, simpleColor color, uint8_t intensity = 255){
      set_bar_color(bar_num, this->RGB(color, intensity));
    };

    void set_group_color(int i_group, DMX_vec color){
      int_vec bars = group_conf[i_group];
      for (auto i_bar : bars){
        this->set_bar_color(i_bar, color);
      }
    }
    void set_group_color(int i_group, simpleColor color, uint8_t intensity = 255){
      set_group_color(i_group, this->RGB(color, intensity));
    }

};
extern AddressableLED addr_led;




/*
   #                                                 
  # #   #    # # #    #   ##   ##### #  ####  #    # 
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
#     # # #  # # # ## # #    #   #   # #    # # #  # 
####### #  # # # #    # ######   #   # #    # #  # # 
#     # #   ## # #    # #    #   #   # #    # #   ## 
#     # #    # # #    # #    #   #   #  ####  #    # */
class AddrLEDAnimation : public BaseAnimation{
  public:
    AddressableLED *fixture;
    AddrLEDAnimation(std::string d, std::string i, AnimationType typ, uint8_t mast, int prio, int_vec intens) : BaseAnimation(d, i, typ, mast, prio, intens){};
};

/*
  ###          #######                 
 #   #         #       # #    # ###### 
#     #        #       #  #  #  #      
#     #        #####   #   ##   #####  
#     # ###    #       #   ##   #      
 #   #  ###    #       #  #  #  #      
  ###   ###    #       # #    # ##### */

  class AddrLEDAnimation0 : public AddrLEDAnimation{
    public:
      simpleColor color = black;

      AddrLEDAnimation0(AddressableLED* f, simpleColor c, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
      :AddrLEDAnimation(d, i, t, mast, prio, intens){
        //set BAse parameters
        this->fixture = f;
        //set cinematic parameters
        this->color = c;
        this->autocolor = false;
      }
      AddrLEDAnimation0(AddressableLED* f, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
      :AddrLEDAnimation(d, i, t, mast, prio, intens){
        //set BAse parameters
        this->fixture = f;
        //set cinematic parameters
        this->autocolor = true;
      }

      void init() override; //Standard init fcn
      void init(const color_vec&) override; //AUTOCOLOR init fcn
      void new_frame() override;
  
  };




/*
         #             #                                          ######  #######    #    #######  
        ##            # #   #    #   ##   #       ####   ####     #     # #         # #      #     
       # #           #   #  ##   #  #  #  #      #    # #    #    #     # #        #   #     #     
         #          #     # # #  # #    # #      #    # #         ######  #####   #     #    #     
         #   ###    ####### #  # # ###### #      #    # #  ###    #     # #       #######    #     
         #   ###    #     # #   ## #    # #      #    # #    #    #     # #       #     #    #     
       ##### ###    #     # #    # #    # ######  ####   ####     ######  ####### #     #    #    */

// Makeover of the ORIGINAL Beatmatcher animation --> all pixels flash at the same time, on beat
class AddrLEDAnimation1 : public AddrLEDAnimation{
  public:
    // specific parameters
  bool param_activate_flash = true;
  simpleColor flash_color = black;            // flash color
  simpleColor back_color = black;             // background color
  double density = 1.0;               // proportion of LED's flashing (0-100%) 
  strip_subdiv_t unit = bar;          // flash pattern subdivision (bar, segment, pixel)
  
  int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

  // Dynamic variables (updated internally at each frame)
  int_vec units_index;

  //AUTOCOLOR constructor 
  AddrLEDAnimation1(AddressableLED* f, strip_subdiv_t subdiv, double dens, std::string d, std::string i, AnimationType t, uint8_t mast, int prio, int_vec intens)
  :AddrLEDAnimation(d, i, t, mast, prio, intens){
      //set Base params 
    this->fixture = f,this->description = d,this->id = i, this->type = t;
    this->autocolor=true;
    //set cinematic params
    this->density = dens;
    this->unit = subdiv;
    switch (subdiv){
      case group: units_index.resize(group_conf.size());
            break;
      case bar : units_index.resize(NUM_BAR);
        break;
      case seg : units_index.resize(NUM_SEG);
        break;
      case pix : units_index.resize(NUM_PIX);
        break;
      }
    for(int i=0; i<units_index.size(); i++){
      units_index[i] = i;
    }

  }

    void init() override;
    void init(const color_vec&) override;
    void new_frame() override;
    
};

/*
       #####         ######                                    ######  #######    #    ####### 
      #     #        #     # #  ####  # #####   ##   #         #     # #         # #      #    
            #        #     # # #    # #   #    #  #  #         #     # #        #   #     #    
       #####         #     # # #      #   #   #    # #         ######  #####   #     #    #    
      #       ###    #     # # #  ### #   #   ###### #         #     # #       #######    #    
      #       ###    #     # # #    # #   #   #    # #         #     # #       #     #    #    
      ####### ###    ######  #  ####  #   #   #    # ######    ######  ####### #     #    #    
      
 Variant of the original beat matching animation : 
  - The strip is ivided into segments
  - The flash turns on all segments
  - The flash Decay turns of segments one by one as intensity decreases */



class AddrLEDAnimation2 : public AddrLEDAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    simpleColor back_color;
    simpleColor flash_color;
    strip_subdiv_t unit;
    int fade_rate = 80;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

    // Dynamic variables (updated internally at each frame)
    int_vec units_index;
    // Constructor
    // AUTOCOLOR Constructor
    AddrLEDAnimation2(AddressableLED *f, strip_subdiv_t u, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :AddrLEDAnimation(d, i, t, mast, prio, intens){

      //set BAse params
      this->description = d,this->id = i,this->fixture = f,this->type = t,this->master = mast,this->priority=prio;
      this->autocolor=true;
      //set cinematic params
      this->unit = u;
      switch (u){
        case group: units_index.resize(group_conf.size());
          break;
        case bar : units_index.resize(NUM_BAR);
          break;
        case seg : units_index.resize(NUM_SEG);
          break;
        case pix : units_index.resize(NUM_PIX);
          break;
      }
      for(int i=0; i<units_index.size(); i++){
        units_index[i] = i;
      }
    }
    
    void init() override;
    void init(const color_vec&) override;
    void new_frame() override;
};



/*TODO major add a choice between random & sequential bursts : sequential mode allows for clean, standard, chasers
      sequential mode setting shall include time constraints (burst length & period) AND spatial constraint (pixel 
      or pixel group sequencing : {1,2,3,4,5,6}, {6,5,4,3,2,1}, {{1,2,3}{6,5,4}}, etc.);
/*
#              ######                          ######                             
#    #         #     #   ##   #    # #####     #     # #    # #####   ####  ##### 
#    #         #     #  #  #  ##   # #    #    #     # #    # #    # #        #   
#    #         ######  #    # # #  # #    #    ######  #    # #    #  ####    #   
####### ###    #   #   ###### #  # # #    #    #     # #    # #####       #   #   
     #  ###    #    #  #    # #   ## #    #    #     # #    # #   #  #    #   #   
     #  ###    #     # #    # #    # #####     ######   ####  #    #  ####    #   
     
Makeover of spotracks Bubblles function :
- random bursts of colors on inidividual pixel units
- pixel units can be LED bars, BAr segemnts or inidividual pixels.
- bursts have different shapes (gaussian, square...).
*/
class AddrLEDAnimation4 : public AddrLEDAnimation
{
private :
    // animation parameters (constant, set at construction)
    bool flash_activation = true;
    simpleColor back_color;
    color_vec flash_colors;

    Shape flash_shape = gaussian; // default setting leads to gaussian flashes (of bubbles)
    strip_subdiv_t unit = bar;
    int flash_interval;
    int flash_length;

    // Internal variable (updated at every new_frame call)
    int_vec p_ms;                     // range of periods for various sine wvaes
    std::vector<flash_vec> flashes;   //for each spot, stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time
    double t_unit;                    // internal, dynamic timescale. This timescale is artificially shrinked/elongated so that the average interval between bursts is 1

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;
  public:
    // AUTOCOLOR constructor
    AddrLEDAnimation4(AddressableLED *f, Shape fshape, strip_subdiv_t u, int prand, int flen, std::string d, std::string i, AnimationType t, int prio, int mast, int_vec intens)
    :AddrLEDAnimation(d, i, t, mast, prio, intens){
      //set Base paramters
      this->description = d,this->id = i,this->fixture = f,this->type = t,this->priority = prio,this->master = mast;
      this->autocolor = true;
      //set cinematic parameters
      this->flash_shape = fshape;
      this->unit = u;
      this->flash_interval=prand;
      this->flash_length = flen;
    }


    void init() override;
    void init(const color_vec&) override;
    void new_frame();
};

/** LED driver configuration :
 *    3 SERIES CONFIGURATION (use driver output channel 1,2,3)
 *        6 bars bars per series configuration :
 *          OUT 1 :  
 *              Start Universe  : 2
 *              Start Channel   : 1 (first)
 *              Pixels          : 6*58 = 348
 * 
 *              OUT 1 sends 348 pixels, 1044 dmx channels, 2 full universe (uni 2+3) + 24 channels in universe 4
 * 
 *          OUT 2 :
 *              Start Universe  : 4
 *              Start Channel   : 25 (24 + 1 since OUT 1 ends at Uni 4 - CH 24)
 *              Pixels          : 348
 * 
 *              OUT 2 sends 348 pixels, 1044 dmx channels :
 *                                - 486 (510-24) in Uni 4 (558 left)
 *                                - 510 (N max subpixels per universe) in Uni 5 (558-510)
 *                                - 48 (1044-486-510) in Uni 6      
 *                      
 * 
 *          OUT 3 :
 *              Start Universe  : 6
 *              Start Channel   : 49
 *              
 * 
 *    2 SERIES CONFIGURATION
 *  *       9 bars per series configuration :
 *          OUT 1 :  
 *              Start Universe  : 2
 *              Start Channel   : 1 (first)
 *              Pixels          : 9*58 = 522
 * 
 *              OUT 1 sends 522 pixels, 1566 dmx channels, 3 full universe (uni 2+3+4) + 36 channels in universe 5


*/


