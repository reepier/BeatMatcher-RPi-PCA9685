#include <iostream>
#include "constant.h"
#include "LED.h"
#include "sysfcn.h"
#include "animator.h"

#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/client/StreamingClient.h>
#include <wiringPi.h>

#include <PCA9685.h>


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

    animator.reset_period();
}



/** 
* This function takes R G B values in and sends them to the LED controler via I2C
* r : 12 bits red intensity value (0-4095)
* g : 12 bits green intensity value (0-4095)
* b : 12 bits red intensity value (0-4095)
*/
void rgb_color(int r, int g, int b){
  animator.rval = r;
  animator.gval = g;
  animator.bval = b;
  // Send frame to the PCA9685 module  
  setOffVals[LEDRed] = r;
  setOffVals[LEDGreen] = g;
  setOffVals[LEDBlue] = b;

  PCA9685_setPWMVals(fd, addr, setOnVals, setOffVals);
}
