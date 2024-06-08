#pragma once

#include "animator.h"

//
#define MAX_PIX_PER_UNI     170 //
#define MAX_SUBPIX_PER_UNI  510 // maximum number of subpixels arried over 1 universe (1 universe can only carry complete pixels (BC-204 limitation))
// WS2815 led strip config
  // Config paramters
  #define NUM_BAR 12             // Total Number of bars
  #define NUM_SEG 48            // Total number of segments (across all bars)
  // Quasi constants
  #define NUM_PIX_BAR 58        // number of pixels per bar
  // Derivatives
  #define NUM_PIX NUM_BAR*NUM_PIX_BAR           // Total number of pixels
  #define NUM_SUBPIX 3*NUM_PIX  // Total number of artnet dmx datas

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
    pixel_vec pixels;


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
    void set_bar_color(int bar_num, simpleColor color){};
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
      auto first_pix = this->pixels.begin() + bar*NUM_PIX/NUM_BAR;
      auto last_pix = first_pix + NUM_PIX/NUM_BAR;
      for (auto pix = first_pix; pix != last_pix; pix++){
        (*pix) = color;
      }
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
         #       
        ##       
       # #       
         #       
         #   ### 
         #   ### 
       ##### #*/

// Makeover of the ORIGINAL Beatmatcher animation --> all pixels flash at the same time, on beat
class AddrLEDAnimation1 : public AddrLEDAnimation{
  public:
    // specific parameters
  bool param_activate_flash;
  simpleColor flash_color;
  simpleColor back_color;
  
  int fade_rate = 60;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

  // Constructor
  AddrLEDAnimation1(AddressableLED* f, simpleColor f_col, simpleColor b_col, std::string d, std::string i, AnimationType typ, bool flash = true){
    this->fixture = f;
    this->description = d;
    this->id = i;

    this->type = typ;
    this->param_activate_flash = flash;

    this->flash_color = f_col;
    this->back_color = b_col;

    this->update_palette(color_vec{f_col, b_col});
  }

    void init() override;
    void new_frame() override;
};

/*
       #####      
      #     #     
            #     
       #####      
      #       ### 
      #       ### 
      ####### ### 
      
 Variant of the original beat matching animation : 
  - The strip is ivided into segments
  - The flash turns on all segments
  - The flash Decay turns of segments one by one as intensity decreases */

enum strip_subdiv_t{
  bar,  // Led bar
  seg,  // Led segment (fraction of a bar)
  pix   // Individual pixel
};

class AddrLEDAnimation2 : public AddrLEDAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    pixel backgd_RGB;
    pixel flash_RGB;
    strip_subdiv_t unit;
    int fade_rate = 80;                            // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)

    // Dynamic variables (updated internally at each frame)
    int_vec units_index;
    // Constructor
    AddrLEDAnimation2(AddressableLED *f, simpleColor f_col, simpleColor b_col, strip_subdiv_t u, std::string d, std::string i)
    {
        this->description = d;
        this->id = i;
        this->fixture = f;

        this->flash_RGB = this->fixture->RGB(f_col);
        this->backgd_RGB = this->fixture->RGB(b_col, 20);
        this->unit = u;

        switch (u){
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

    void init() override;
    void new_frame() override;
};

/*     
       #####      
      #     #     
            #     
       #####      
            # ### 
      #     # ### 
       #####  ##

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
