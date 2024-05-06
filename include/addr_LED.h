#pragma once

#include "animator.h"

//
#define MAX_PIX_PER_UNI     170 //
#define MAX_SUBPIX_PER_UNI  510 // maximum number of subpixels arried over 1 universe (1 universe can only carry complete pixels (BC-204 limitation))
// WS2815 led strip config
#define NUM_PIX 174         // Total number of pixels
#define NUM_SUBPIX 3*NUM_PIX
#define NUM_PIX_BAR 58      // number of pixels per bar
#define NUM_BAR 3           // Number of bars
#define NUM_SEG 9           // Number of segments (fraction of a bar)

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

    void set_all_color(DMX_vec color){
      for (auto pix : this->pixels){
        pix = color;
      }
    }
    void set_all_color(simpleColor color, uint8_t intensity = 255){
      set_all_color(this->RGB(color, intensity));
    };

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

// Makeover of the ORIGINAL Beatmatcher animation
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

    void init() override{BaseAnimation::init();};
    void new_frame() override{BaseAnimation::new_frame();};
};