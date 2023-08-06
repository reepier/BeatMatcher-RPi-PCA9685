#include "spider.h"
#include "sysfcn.h"
#include "debug.h"

using namespace std;

// --------------------------------------
// SPIDER FIXTURE definition
// --------------------------------------
SpiderFixture spider(29, 44, "AFX-9-Beam");

void SpiderFixture::init(){
    // push the animations:
    this->animations.push_back(new SpiderAnimation1(this, black,  0, 0, int_vec{0,0,0},    "BLACK", "SPI.0.0"));
    this->animations.push_back(new SpiderAnimation1(this, red,    0, 20, int_vec{90,90,90},    "Red, 90°, static", "SPI.1.1"));
    this->animations.push_back(new SpiderAnimation1(this, white,    0, 20, int_vec{20,20,20},  "White, 20°, slow", "SPI.1.2"));
    this->animations.push_back(new SpiderAnimation1(this, blue,    0, -20, int_vec{130,130,130},  "Blue, 130°, slow", "SPI.1.3"));
    
    this->activate_by_ID("SPI.0.0");
}

DMX_vec SpiderFixture::buffer(){
    DMX_vec ret(this->nCH);
    // ret.resize(this->nCH);
    
    ret[0] = min(max( map( this->pan_position%360 , 0, 359, 0, 255)  ,0),255);
    ret[1] = (this->pan_speed == 0) ? 0 : 
                    (this->pan_speed<0) ? max(min( map(this->pan_speed, -128, -1, 10, 127), 255),10) :
                        max(min( map(this->pan_speed, 1, 127, 128, 255), 255),10);

    ret[2]= min(max(    map(this->tilt[0], -30, 120, 0, 255)    ,0),255);
    ret[3]= min(max(    map(this->tilt[1], -30, 120, 0, 255)    ,0),255);
    ret[4]= min(max(    map(this->tilt[2], -30, 120, 0, 255)    ,0),255);
    
    ret[5]=this->MASTER_DIMMER;
    ret[6]=this->strobe;

    for (int led=0; led<NLED; led++){
        for (int pix=0; pix<NCOL; pix++){
            ret[7+led*NCOL+pix] = this->pixels[led][pix];
        }
    }
    ret[nCH-1] = prog;

    return ret;
}

// ---------------------------------------------
// SPIDER ANIMATION definition
// ---------------------------------------------
void SpiderAnimation1::init(){
    this->frame_cpt = 0;
    this->t_animation_start_ms = millis();
}

void SpiderAnimation1::new_frame(){
    balise("Compute new spider1 frame");
    // do onothin, simply set the fixture's colors & motor settings
    this->fixture->pan_position = this->pan_pos;
    this->fixture->pan_speed = this->pan_spd;
    this->fixture->tilt = this->tilt;
    this->fixture->pixels = this->pix;
}