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

#include "config.h"
#include "sysfcn.h"
#include "music.h"
#include "animator.h"
#include "fixtures.h"

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

fix_vec ll_fxtrs = {&led, &spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, &spot_8, &spot_7, &spider};
fix_vec fixtures = {&front_rack, &led, &spider};

LoopControler frame;

void build_buffer(){
    
}

void send(){
    #ifndef LINUX_PC // if compiling on raspberrypi
    // Send frame to the PCA9685 module
    // Take into account the MASTER DIMMER value !! --> as late as possible, right before data is sent
    setOffVals[LEDRed] = led.RGBout[R] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDGreen] = led.RGBout[G] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDBlue] = led.RGBout[B] * led.MASTER_DIMMER / 255.0;

    PCA9685_setPWMVals(fd, addr, setOnVals, setOffVals);
#endif // DEBUG

    // send DMX frame to OLA server.
    balise("Construct buffer");
    for (fix_vec::iterator fx = ll_fxtrs.begin(); fx != ll_fxtrs.end(); fx++){
        ola_buffer.SetRange((*fx)->get_address(), (*fx)->buffer().data(), (*fx)->get_nCH());
    }
    // ola_buffer.SetRange(ll_fxtrs[0]->address, ll_fxtrs[0]->buffer().data(), ll_fxtrs[0]->nCH);
    // ola_buffer.SetRange(led.address, led.buffer().data(), led.nCH);
    // ola_buffer.SetRange(spot_g.address, spot_g.buffer().data(), spot_g.nCH);
    // ola_buffer.SetRange(spot_d.address, spot_d.buffer().data(), spot_d.nCH);
    // ola_buffer.SetRange(spot_1.address, spot_1.buffer().data(), spot_1.nCH);
    // ola_buffer.SetRange(spot_2.address, spot_2.buffer().data(), spot_2.nCH);
    // ola_buffer.SetRange(spot_3.address, spot_3.buffer().data(), spot_3.nCH);
    // ola_buffer.SetRange(spider.address, spider.buffer().data(), spider.nCH);

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

  // Chat GPT Example :
    // std::vector<int> myVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // std::cout << "Original Vector: ";
    // for (const int& element : myVector) {
    //     std::cout << element << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Random Order: ";
    // readVectorInRandomOrder(myVector);


    // #ifndef LINUX_PC // if compiling on raspberrypi
    //   _PCA9685_DEBUG = 0;
    //   _PCA9685_TEST = 0;

    //   fd = PCA9685_openI2C(1, addr);
    //   PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);
    // #endif

    // while (true){
    //   static uint8_t i=0;

    //   led.RGBout=fcn::convert_8_to_12bits(DMX_vec{i,i,i});
    //   send();
    //   i+=10;
    //   delay(100);
    // }

    while (true){
        for (simpleColor c = red; c<last_color; c = (simpleColor)(int)(c+1)){
          // spot_1.RGBWout = front_rack.RGBW(c);
          // spot_2.RGBWout = front_rack.RGBW(c);
          // spot_3.RGBWout = front_rack.RGBW(c);
          cout << colorName[(int)c] << endl;
          for (auto gain : int_vec{255}){
            led.RGBout = fcn::convert_8_to_12bits( led.RGB(c, gain) );
            send();
            delay(500);
          }
        }
    }
}