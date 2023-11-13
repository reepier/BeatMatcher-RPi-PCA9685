#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

#include "wiringPi.h"
using namespace std;

#include <ola/DmxBuffer.h>
#include <ola/client/StreamingClient.h>

#include "../include/config.h"
#include "../include/sysfcn.h"
#include "../include/music.h"
#include "../include/animator.h"
#include "../include/fixtures.h"

// DMX output interface (OLA)
  ola::client::StreamingClient ola_client;
  ola::DmxBuffer ola_buffer;

#ifndef LINUX_PC // if compiling on raspberrypi
    // I2C Hardware interface (PCA9685)
    int fd;
    int addr = 0x40;
    unsigned int setOnVals[_PCA9685_CHANS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int setOffVals[_PCA9685_CHANS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

fix_vec ll_fxtrs = {&led, &spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, &spot_7, &spider, &laser};
fix_vec fixtures = {&front_rack, &back_rack, &led, &spider, &laser};

LoopControler frame;

void build_buffer(){
    
}

void send(){
    #ifndef LINUX_PC // if compiling on raspberrypi
    // Send frame to the PCA9685 module
    // Take into account the MASTER DIMMER value !! --> as late as possible, right before data is sent
    setOffVals[LEDRed1] = led.RGBout[R] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDGreen1] = led.RGBout[G] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDBlue1] = led.RGBout[B] * led.MASTER_DIMMER / 255.0;
    
    setOffVals[LEDRed2] = led.RGBout[R] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDGreen2] = led.RGBout[G] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDBlue2] = led.RGBout[B] * led.MASTER_DIMMER / 255.0;

    PCA9685_setPWMVals(fd, addr, setOnVals, setOffVals);
#endif // DEBUG

    // send DMX frame to OLA server.
    balise("Construct buffer");
    for (fix_vec::iterator fx = ll_fxtrs.begin(); fx != ll_fxtrs.end(); fx++){
        ola_buffer.SetRange((*fx)->get_address(), (*fx)->buffer().data(), (*fx)->get_nCH());
    }

    balise("OLAclient.send()");
    ola_client.SendDmx(1, ola_buffer);
}

void spit_colors(){
  for(int c = simpleColor::black; c != simpleColor::last_color; c++){
    // cout << colorName[c] << "\t: RGBW{" << fcn::vec_to_str(fcn::RGBW((simpleColor)c), ',') << "} \t RGB{" << fcn::vec_to_str(fcn::RGB((simpleColor)c), ',') << "}" << endl;
  }
}

// Function to read vector elements in random order
void readVectorInRandomOrder(std::vector<int>& vec) {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 rng(rd());

    // Shuffle the vector using the random number generator
    std::shuffle(vec.begin(), vec.end(), rng);

    // Iterate through the shuffled vector and read its elements
    for (const int& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main(){
    ola_client.Setup();
    srand(millis());
    #ifndef LINUX_PC // if compiling on raspberrypi
        balise("Init. PCA...");
        _PCA9685_DEBUG = 0;
        _PCA9685_TEST = 0;

        fd = PCA9685_openI2C(1, addr);
        PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);
    #endif

    color_vec cp1 = {black, white};
    color_vec cp2 = {red, black};
    color_vec cp3 = {purple, orange};
    color_vec cp4 = {white, black};

    cout << (fcn::are_consistent(cp1, cp2) ? 1 : 0) << endl;
    cout << (fcn::are_consistent(cp1, cp2, 2) ? 1 : 0) << endl;

    cout << (fcn::are_consistent(cp1, cp3) ? 1 : 0) << endl;
    cout << (fcn::are_consistent(cp1, cp4, 2) ? 1 : 0) << endl;
    cout << (fcn::are_consistent(cp1, cp4, 1) ? 1 : 0) << endl;
  }