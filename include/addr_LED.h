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
    AddressableLED(int uni, int addr, int ch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, ch, nm, id, mast){
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

      AddrLEDAnimation0(AddressableLED* f, simpleColor c, std::string d, std::string i, AnimationType t=any, int prio=1, int mast=255){
        //set BAse parameters
        this->description = d, this->id = i, this->fixture = f, this->type=t, this->priority=prio, this->master=mast;
        //set cinematic parameters
        this->color = c;
        this->autocolor = false;
      }
      AddrLEDAnimation0(AddressableLED* f, std::string d, std::string i, AnimationType t=any, int prio=1, int mast=255){
        //set BAse parameters
        this->description = d, this->id = i, this->fixture = f, this->type=t, this->priority=prio, this->master=mast;
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
  bool param_activate_flash;
  simpleColor flash_color = black;            // flash color
  simpleColor back_color = black;             // background color
  double density = 1.0;               // proportion of LED's flashing (0-100%) 
  strip_subdiv_t unit = bar;          // flash pattern subdivision (bar, segment, pixel)
  
  int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

    // Dynamic variables (updated internally at each frame)
    int_vec units_index;

  // ORIGINAL Constructor
  AddrLEDAnimation1(AddressableLED* f, simpleColor f_col, simpleColor b_col, std::string d, std::string i, AnimationType typ, bool flash = true){
    this->fixture = f;
    this->description = d;
    this->id = i;

    this->type = typ;
    this->param_activate_flash = flash;

    this->flash_color = f_col;
    this->back_color = b_col;
    units_index.resize(NUM_BAR);
    for(int i=0; i<units_index.size(); i++){
      units_index[i] = i;
    }


    this->update_palette(color_vec{f_col, b_col});
  }
  // overload to include fragmentation
  AddrLEDAnimation1(AddressableLED* f, simpleColor f_col, simpleColor b_col, strip_subdiv_t subdiv, double dens, std::string d, std::string i, AnimationType typ, bool flash = true)
  : AddrLEDAnimation1(f, f_col, b_col, d, i, typ, flash)
  {
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
  //AUTOCOLOR constructor 
  AddrLEDAnimation1(AddressableLED* f, strip_subdiv_t subdiv, double dens, std::string d, std::string i, AnimationType typ, bool flash = true, uint8_t mast = 255){
    //set Base params 
    this->fixture = f,this->description = d,this->id = i, this->type = typ;
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
    AddrLEDAnimation2(AddressableLED *f, simpleColor f_col, simpleColor b_col, strip_subdiv_t u, std::string d, std::string i, AnimationType typ=any, int prio=1, int mast=255)
    {
      //set BAse params
      this->description = d,this->id = i,this->fixture = f,this->type = typ,this->master = mast,this->priority=prio;
      //set cinematic params
      this->flash_color = f_col;
      this->back_color = b_col;
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

      this->update_palette(color_vec{f_col, b_col});
    }
    // AUTOCOLOR Constructor
    AddrLEDAnimation2(AddressableLED *f, strip_subdiv_t u, std::string d, std::string i, AnimationType typ=any, int prio=1, int mast=255){
      //set BAse params
      this->description = d,this->id = i,this->fixture = f,this->type = typ,this->master = mast,this->priority=prio;
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

/*     
       #####          #     #                        
      #     #         ##    #  ####  #  ####  ###### 
            #         # #   # #    # # #      #      
       #####          #  #  # #    # #  ####  #####  
            # ###     #   # # #    # #      # #      
      #     # ###     #    ## #    # # #    # #      
       #####  ###     #     #  ####  #  ####  ###### 

  Noise function
  Asynchronous animation (no Beat)
*/
class AddrLEDAnimation3 : public AddrLEDAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    simpleColor color;
    bool enable_filter = false;
    float param_filter_weight = 0.1;
    // Dynamic variables (updated internally at each frame)
    uint8_vec pix_intensities = uint8_vec(NUM_PIX, 0);
    // Precomputed values
    uint8_vec atan_transfo = uint8_vec(NUM_PIX);
    float Q = 0.03; // greater Q = more distortion
    float A = 255.0/2;
    float K = A/atan(Q*A);
    void compute_atan_transfo(){
      for (int i = 0; i<NUM_PIX; i++){
        float x = i;
        atan_transfo[i] = A+K*atan(Q*(x-A));
      }
      // log(1, fcn::vec_to_str(atan_transfo, ','));
    }
    
    // Constructor 1 : 1 color, random intensity on each pixel
    AddrLEDAnimation3(AddressableLED *f, simpleColor col, bool enable_filter, std::string d, std::string i)
    {
        this->description = d;
        this->id = i; 
        this->fixture = f;

        this->color = col;
        this->enable_filter = enable_filter;

        this->update_palette(col);
        this->compute_atan_transfo();
    }
    AddrLEDAnimation3(AddressableLED *f, simpleColor col, std::string d, std::string i)
    {
        this->description = d;
        this->id = i; 
        this->fixture = f;

        this->color = col;

        this->update_palette(col);
        this->compute_atan_transfo();
    }

    void init() override;
    void new_frame() override;

    //plot (A + K * atan(Q*(x-A))) with Q = 0.05, A=255/2, K =A/atan(Q*A), x from 0 to 255
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
    // DMX_vec back_color;
    simpleColor back_color;
    // DMX_vec flash_color;
    color_vec flash_colors;

    Shape flash_shape = gaussian; // default setting leads to gaussian flashes (of bubbles)
    strip_subdiv_t unit = bar;
    // int sin_max_p_ms = 15000;
    // int sin_min_p_ms = 5000;
    int rand_const_ms;
    int flash_len;
    // double fluct_int = 0.4;
    // double fluct_col = 0.25;

    // Internal variable (updated at every new_frame call)
    int_vec p_ms;             // range of periods for various sine wvaes
    // std::vector<unsigned long> t_next; // timestamp of the next rise ()
    // std::vector<unsigned long> t_prev; // timestamp of the prev rise () (memory)
    std::vector<flash_vec> flashes;     //for each spot, stores previous & next flash data (color & time) --> flashes[spot_ind][prev/next].color/time

    // Internal helpful & hidden stuff (for readability)
    const int i_prev = 0, i_next = 1;
  public:
    //CONSTUCTORS
    // Base constructor
    AddrLEDAnimation4(AddressableLED *f, simpleColor b_col, color_vec f_cols, Shape fshape, strip_subdiv_t u, int prand, int flen, std::string d, std::string i, AnimationType t, int prio, int mast=255){
      //set Base parameters
      this->description = d,this->id = i,this->fixture = f,this->type = t,this->priority = prio,this->master = mast;
      //set cinematic parameters
      this->flash_colors = f_cols;
      this->back_color = b_col;
      this->rand_const_ms = prand;
      this->flash_len = flen;
      this->flash_shape = fshape;        

      this->update_palette(color_vec{b_col});
      this->update_palette(f_cols);
    }
    // AUTOCOLOR constructor
    AddrLEDAnimation4(AddressableLED *f, Shape fshape, strip_subdiv_t u, int prand, int flen, std::string d, std::string i, AnimationType t, int prio, int mast=255){
      //set Base paramters
      this->description = d,this->id = i,this->fixture = f,this->type = t,this->priority = prio,this->master = mast;
      this->autocolor = true;
      //set cinematic parameters
      this->flash_shape = fshape;
      this->unit = u;
      this->rand_const_ms=prand;
      this->flash_len = flen;
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

*/


