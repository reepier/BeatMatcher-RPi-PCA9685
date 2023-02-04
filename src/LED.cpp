#include <iostream>
#include "constant.h"
#include "LED.h"
#include "sysfcn.h"
#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/client/StreamingClient.h>
#include <cmath>
#include <wiringPi.h>

#include <PCA9685.h>

// TODO: move to an animator class/module
// color storage
int color1[3];
int color2[6];
int color3[3];
int back_color[3];
float coef = 0;

// TODO: move to an animator class/module
// background sinewave periods parameters
unsigned long period[6];
#define MAX_T 30
#define MIN_T 2

// TODO: move to a classe mimicking a DMX fixtures --> for the sake of homogeneity with the future architecture
// libPCA9685 specific variables
int fd;
int addr = 0x40;
unsigned int setOnVals[_PCA9685_CHANS] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  unsigned int setOffVals[_PCA9685_CHANS] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
void LED_init(){
    _PCA9685_DEBUG = 0;
    _PCA9685_TEST = 0;

    fd = PCA9685_openI2C(1, addr);
    PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);

    reset_period();
}


void set_color(int rgb[], int c0, int c1, int c2, int c3, int c4, int c5){
  rgb[0]=c0;
  rgb[1]=c1;
  rgb[2]=c2;
  rgb[3]=c3;
  rgb[4]=c4;
  rgb[5]=c5;
}

/** 
* This function takes R G B values in and sends them to the LED controler via I2C
* r : 12 bits red intensity value (0-4095)
* g : 12 bits green intensity value (0-4095)
* b : 12 bits red intensity value (0-4095)
*/
void rgb_color(int r, int g, int b){



  // Send frame to the PCA9685 module  
  setOffVals[LEDRed] = r;
  setOffVals[LEDGreen] = g;
  setOffVals[LEDBlue] = b;

  PCA9685_setPWMVals(fd, addr, setOnVals, setOffVals);
}


//TODO : raw_beat argument is useless --> remove it...  the beat_t timer is enough to compute the exponential decay
void flash_master(bool raw_beat, unsigned long beat_t, bool flash, int fade_rate){
    unsigned long t = millis();

    //TODO : use more explicit naming (rgb instead of color)
    // color2[] stores [redmin, redmax, greenmin, green max...]
    back_color[0] = (color2[0]+color2[1])/2 
                    + (color2[1]-color2[0])/4
                            *(sin(2*3.14*t/period[0])+sin(2*3.14*t/period[1]));
    back_color[1] = (color2[2]+color2[3])/2 
                    + (color2[3]-color2[2])/4
                            *(sin(2*3.14*t/period[2])-sin(2*3.14*t/period[3]));
    back_color[2] = (color2[4]+color2[5])/2 
                    + (color2[5]-color2[4])/4
                            *(sin(2*3.14*t/period[4])-sin(2*3.14*t/period[5]));
                                
    if (raw_beat && flash){
        rgb_color(color1[1], color1[2], color1[2]);
    }
    else{
        if (flash){
        coef = exp(-(float)(t-beat_t)/fade_rate);
        }
        else{
        coef = 0;  
        }
        rgb_color(back_color[0]+coef*(color1[0]-back_color[0]), back_color[1]+coef*(color1[1]-back_color[1]), back_color[2]+coef*(color1[2]-back_color[2]));
    }
}

void flash_master_BS(int vol){
  // secondary flashing mode
  // the LED display the color contained in color1 array but with an intensity following the volume
  float intensity = sqrt((float)map(vol, 0, 180, 5, 255)/255);
  
  rgb_color(intensity*(float)color1[0], intensity*(float)color1[1], intensity*(float)color1[2]);
}

//TODO move to animator class/module
void reset_period(){
  // randomSeed(analogRead(musicpin));

  period[0] = 1000*rand_min_max(MIN_T, MAX_T);
  period[1] = 1000*rand_min_max(MIN_T, MAX_T);
  period[2] = 1000*rand_min_max(MIN_T, MAX_T);
  period[3] = 1000*rand_min_max(MIN_T, MAX_T);
  period[4] = 1000*rand_min_max(MIN_T, MAX_T);
  period[5] = 1000*rand_min_max(MIN_T, MAX_T); 
}



void animator(int i){
        switch (i){
          case 0:
            // Warm Flashes
            set_color(color1, 255<<4, 150<<4, 80<<4);   // flash RGB color
            set_color(color2, 30<<4,100<<4, 1<<4,7<<4, 0<<4,0<<4);  // back color wave settings (Rmax, Rmin, Gmax,...)
          break;
          case 1:
            // Sodium Flashes
            set_color(color1, 255<<4, 30<<4, 0<<4);
            set_color(color2, 15<<4,50<<4, 0<<4,5<<4, 0<<4,0<<4);
          break;
          case 2:
            // Sodium Flashes
            set_color(color1, 255<<4, 50<<4, 10<<4);
            set_color(color2, 15<<4,50<<4, 0<<4,5<<4, 0<<4,0<<4);      
          break;
          case 3:
          // Very Warm
            set_color(color1, 255<<4, 150<<4, 80<<4);
            set_color(color2, 30<<4,100<<4, 1<<4,7<<4, 0<<4,0<<4);      
          break;
          case 4:
            // Slide to pink palette introducing blue
            set_color(color1, 255<<4, 150<<4, 80<<4);
            set_color(color2, 30<<4,100<<4, 1<<4,7<<4, 0<<4,10<<4);   
          break;
          case 5:
            // reduce red, increase blue
            set_color(color1, 255<<4, 100<<4, 80<<4);
            set_color(color2, 0<<4,80<<4, 0<<4,0<<4, 0<<4,20<<4);
          break;
          case 6:
            // reduce red, increase blue
            set_color(color1, 255<<4, 100<<4, 80<<4);
            set_color(color2, 0<<4,50<<4, 0<<4,0<<4, 0<<4,80<<4);     
          break;
          case 7:
            // Mostly blue
            set_color(color1, 255<<4, 100<<4, 80<<4);
            set_color(color2, 0<<4,20<<4, 0<<4,5<<4, 0<<4,100<<4);      
          break;
          case 8:
            // Introduce green to slide towards cyan - yellow palette
            set_color(color1, 255<<4, 100<<4, 80<<4);
            set_color(color2, 0<<4,10<<4, 0<<4,10<<4, 0<<4,100<<4);    
          break;
          case 9:
            //BLACK BACKGROUND with WHITE FLASHES
            set_color(color1, 255<<4, 100<<4, 80<<4);
            set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);     
          break;
          case 10:
            // pure pink flashes
            set_color(color1, 255<<4, 0<<4, 25<<4);
            set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);
          break;
          case 11:
            // pure blue flashes
            set_color(color1, 0<<4, 0<<4, 255<<4);
            set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);
          break;
          case 12:
            // pure red flashes
            set_color(color1, 255<<4, 0<<4, 0<<4);
            set_color(color2, 0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4);     

          break;
        }
}