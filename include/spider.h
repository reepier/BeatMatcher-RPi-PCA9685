#pragma once

#include <vector>

#include "animator.h"

#define NLED 9
#define NCOL 4

class SpiderFixture;
class SpiderAnimation;

typedef std::vector<DMX_vec> pixel_vec;

/**
####### ### #     # ####### #     # ######  ####### 
#        #   #   #     #    #     # #     # #       
#        #    # #      #    #     # #     # #       
#####    #     #       #    #     # ######  #####   
#        #    # #      #    #     # #   #   #       
#        #   #   #     #    #     # #    #  #       
#       ### #     #    #     #####  #     # ####### 
*/
#define tiltMIN -30 //tilt min angle (°)
#define tiltMAX 120 //tilt max angle (°)
class SpiderFixture : public BaseFixture
{
public:
    int pan_position;                   // pan position [-inf ; inf]
    int pan_speed;                     // pan speed    [-128 ; 127]
    int_vec tilt;                       // tilt axes {tilt 1, 2, 3} -> [tiltMIN; tiltMAX]°
    pixel_vec pixels; // LED Pixels [ [R,G,B,W] , [R,G,B,W] , ... [R,G,B,W] ]
    uint8_t strobe;
    uint8_t prog;
    
    SpiderFixture(int addr, int ch, std::string nm, int id, uint8_t mast=255) : BaseFixture(addr, ch, nm, id, mast)
    {  
        this->tilt.resize(3);
        this->pixels.resize(NLED, DMX_vec(NCOL));
    };
    void init() override;

    // Get functions
    int get_nCH() override { return this->nCH; };
    int get_address() override { return this->address; };
    DMX_vec buffer() override;

    // Spider Specific Color Macro
    DMX_vec RGBW(simpleColor, int intensity = 255) override;
};
extern SpiderFixture spider;

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####  
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     # 
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #       
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####  
####### #   # #  #  #     # #######    #     #  #     # #   # #       # 
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     # 
#     # #     # ### #     # #     #    #    ### ####### #     #  #####  
*/
class SpiderAnimation : public BaseAnimation{
public:
    SpiderFixture *fixture;
};

/*
   #             #   
  # #           ##   
 #   #         # #   
#     # #####    #   
#######          #   
#     #          #   
#     #        ##### 
*/
// Static Monochrome
class SpiderAnimation1 : public SpiderAnimation{
  public:
    int pan_pos;  //pan position °
    int pan_spd;  //pan speed (-128 ; +127)
    int_vec tilt; //tilt position x3 ()
    pixel_vec pix = pixel_vec(9, DMX_vec{0,0,0,0}); // stores RGB values as follow RGBW[Led_i][Pix_i]

    SpiderAnimation1(SpiderFixture *f, simpleColor c,  int pos, int spd, int_vec til, std::string d, std::string i){
        this->description = d;
        this->id = i; 
        this->fixture = f;

        if (til.size()==1){
            this->tilt = int_vec(3, til[0]);
        }else if (til.size()!=3){
            this->tilt.resize(0);
        }else{
            this->tilt = til;
        }
        this->pan_pos = pos;
        this->pan_spd = spd;

        this->pix = pixel_vec(9, this->fixture->RGBW(c));

        this->update_palette(c);
    };
    void init() override{BaseAnimation::init();};
    void new_frame() override;
};

/*
   #           #####  
  # #         #     # 
 #   #              # 
#     # #####  #####  
#######       #       
#     #       #       
#     #       ####### 
*/
// Random beams

class SpiderAnimation2 : public SpiderAnimation{
  public:
    // constant parameters (defining the animation)
    simpleColor background_color;
    color_vec flash_colors;                 // stores the different fkash colors
    int_vec flash_color_proba = {};              // stores each flash color's probability of occurence
    unsigned long flash_dt;
    Shape flash_shape;
    int flash_length;
    int pan_position;
    int pan_speed;
    int_vec tilt_position;
    int tilt_period;

    // dynamic variables (to compute each frame)
    std::vector<t_vec>      flash_time; //for each of the 9 pixels, stores {time of previous flash, time of next flash} --> needs update at every frame
    
    // helpful & hidden stuff
    const int i_next = 1, i_prev = 0;           //indices for readability

    // constant parameters (defining the animation)
    std::vector<flash_vec>  flashes; //for each of the 9 pixels, one vector containing prev_flash and next_flash data (color & timing).

    SpiderAnimation2(SpiderFixture *f, simpleColor b_col, color_vec f_col, Shape f_shp, unsigned long f_len, double f_n,int p_pos, int p_speed, int_vec t_pos, std::string d, std::string i, AnimationType typ=any){
        this->fixture           = f;
        this->description       = d;
        this->id                = i;
        this->type              = typ;

        this->background_color  = b_col;
        this->flash_colors      = f_col;
        this->flash_length      = f_len;
        this->flash_shape       = f_shp;
        this->flash_dt          = this->flash_length / f_n;
        this->pan_position      = p_pos;
        this->pan_speed         = p_speed;
        this->tilt_position     = t_pos;
        this->tilt_period = 0;

        this->update_palette(b_col);
        this->update_palette(f_col);
    };
    SpiderAnimation2(SpiderFixture *f, simpleColor b_col, color_vec f_col, Shape f_shp, unsigned long f_len, double f_n,int p_pos, int p_speed, int_vec t_minmax, int t_per, std::string d, std::string i, AnimationType typ=any){
        this->fixture     = f;
        this->description       = d;
        this->id                = i;
        this->type              = typ;

        this->background_color  = b_col;
        this->flash_colors      = f_col;
        this->flash_length      = f_len;
        this->flash_shape       = f_shp;
        this->flash_dt          = this->flash_length / f_n;
        this->pan_position      = p_pos;
        this->pan_speed         = p_speed;
        this->tilt_position     = t_minmax;
        this->tilt_period       = t_per;

        this->update_palette(b_col);
        this->update_palette(f_col);
    };

    void init() override{
        BaseAnimation::init();
        this->flashes.resize(NLED, flash_vec(2));
        this->flash_time.resize(NLED, t_vec(2));

        for(int pix = 0; pix < this->flash_time.size(); pix++){
            flash_time[pix][0] = t_animation_start_ms - 3*flash_length ;                          // initialize previous flash far enough in the past to not create a visible flash
            flash_time[pix][1] = t_animation_start_ms + rand_min_max(flash_length,  flash_dt*9);  // set next flash far enough in the future to not create a step in lighting
            
            flashes[pix][0].time = t_animation_start_ms - 3*flash_length;
            flashes[pix][1].time = t_animation_start_ms + rand_min_max(flash_length,  flash_dt*9);
            flashes[pix][0].color = black;
            flashes[pix][1].color = fcn::random_pick(flash_colors, flash_color_proba);
        }

        if (flash_length<200){animator.set_timer(STROBE_ANI_DURA);}

    };

    void new_frame() override;

  private:
    void update_next_flash();
};

/*
   #           #####  
  # #         #     # 
 #   #              # 
#     # #####  #####  
#######             # 
#     #       #     # 
#     #        #####  

Beams flashing & disappearing on beat */

class SpiderAnimation3 : public SpiderAnimation{
  public:
    // Animation parameters (constant or set by animation constructor)
    const int_vec param_anim_tilt = {70,100};
    const int param_anim_tilt_period = 5000;
    const int param_anim_pan = 0;
    const int param_anim_pan_spd = 20;

    color_vec flash_colors;      // beam colors
    const int fade_rate = 60;          // ms flash fade rate (time constant of an exponential decay : intensity = exp(-(t-t0)/fade_rate)


    const int_vec index_vector = {0,1,2,3,4,5,6,7,8}; // vectr storing the idex of every spider pixel [0-8]

    // Dynamic variables (updated internally at each frame)
    int_vec rand_index_vector = index_vector;
    color_vec rand_col_vector = color_vec(NLED, black);

    // Constructor
    SpiderAnimation3(SpiderFixture *f, color_vec f_col, std::string d, std::string i, AnimationType typ = any){
        this->description = d;
        this->id = i; 
        this->fixture = f;
        this->type = typ;

        this->flash_colors = f_col;

        this->update_palette(f_col);
    }

    void init() override{BaseAnimation::init();};
    void new_frame() override;
};