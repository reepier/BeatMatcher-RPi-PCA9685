#include <vector>

#include "animator.h"


class LaserFixture;     
class LaserAnimation;
class LaserAnimation1;

/**
####### ### #     # ####### #     # ######  ####### 
#        #   #   #     #    #     # #     # #       
#        #    # #      #    #     # #     # #       
#####    #     #       #    #     # ######  #####   
#        #    # #      #    #     # #   #   #       
#        #   #   #     #    #     # #    #  #       
#       ### #     #    #     #####  #     # ####### 
*/
class LaserFixture : public BaseFixture{
public:    
    // Channels
    uint8_t motor1;                     // motor 1 speed (0-255)
    uint8_t motor2;                     // motor 2 speed (0-255)
    DMX_vec RGB = {0,0,0};      // RGB diod command (0 or 255) 
    uint8_t prog;
    uint8_t motor_sync, freq_sync;      // motor speed and flickering freq calibration coefficient 
    int nCH = 8;

    // constructor
    LaserFixture(int addr, int ch, std::string nm): BaseFixture(addr, ch, nm, 1,255){};
    void init() override;

    int get_nCH() override {return this->nCH;};
    int get_address() override {return this->address;};
    DMX_vec buffer() override;

};
extern LaserFixture laser;


class LaserAnimation : public BaseAnimation{
  public:
    LaserFixture* fixture;
};

/**
   #    #     # ### #     #    #    ####### ### ####### #     #  #####  
  # #   ##    #  #  ##   ##   # #      #     #  #     # ##    # #     # 
 #   #  # #   #  #  # # # #  #   #     #     #  #     # # #   # #       
#     # #  #  #  #  #  #  # #     #    #     #  #     # #  #  #  #####  
####### #   # #  #  #     # #######    #     #  #     # #   # #       # 
#     # #    ##  #  #     # #     #    #     #  #     # #    ## #     # 
#     # #     # ### #     # #     #    #    ### ####### #     #  #####  
*/
/**Prebuilt animation*/
class LaserAnimation1 : public LaserAnimation{
public:
    uint8_t indice;

    LaserAnimation1(LaserFixture* fix, uint8_t ind, color_vec c, std::string d, std::string i){
        this->fixture = fix;
        this->description = d;
        this->id = i;
        this->indice = ind;

        for (auto col : c){
            this->update_palette(col);
            if (col == magenta)
                  this->update_palette(pink);
        }
        
        str_vec palette_literal;
        for (auto col : this->color_palette){
            palette_literal.push_back(colorName[(int)col]);
        }
        // log(1, this->id, " ", fcn::vec_to_str(palette_literal, '/'));
    }
    
    void init() override {this->fixture->prog = this->indice;};
    void new_frame() override;

    
};