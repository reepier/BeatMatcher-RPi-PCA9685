#include "spider.h"



// --------------------------------------
// SPIDER FIXTURE definition
// --------------------------------------

void SpiderFixture::init(){
    

    // push the animations:
    // this->animations.push_back(...)
}

std::vector<uint8_t> SpiderFixture::buffer(){
    std::vector<uint8_t> ret(this->nCH);
    
    ret[0] = this->pan[0];
    ret[1] = this->pan[1];

    ret[2]=this->tilt[0];
    ret[3]=this->tilt[1];
    ret[4]=this->tilt[2];
    
    ret[5]=this->MASTER_DIMMER;
    ret[6]=this->strobe;

    int ch=7;
    for (int i=0; i<NLED; i++){
        for (int j=0; i<NCOL; j++){
            ret[ch] = this->RGBW[i][j];
        }
    }
}

// ---------------------------------------------
// SPIDER ANIMATION definition
// ---------------------------------------------