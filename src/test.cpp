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

fix_vec ll_fxtrs = {&led, &spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, &spot_d, &spot_g, &spider};
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

    // while(true){
    //   for(int c = SimpleColor::black; c != SimpleColor::last_color; c++){
        
    //     switch (c){
    //     case black:
    //         spot_1.RGBW = BLACK;
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(black) );
    //       break;
    //     case red:
    //         spot_1.RGBW = RED(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(red));
    //       break;
    //     case green:
    //         spot_1.RGBW = GREEN(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(green));
    //       break;
    //     case yellow:
    //         spot_1.RGBW = YELLOW(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(yellow));
    //       break;
    //     case blue:
    //         spot_1.RGBW = BLUE(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(blue));
    //       break;
    //     case orange:
    //         spot_1.RGBW = ORANGE(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(orange));
    //       break;
    //     case sodium:
    //         spot_1.RGBW = SODIUM(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(sodium));
    //       break;
    //     case cyan:
    //         spot_1.RGBW = CYAN(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(cyan));
    //       break;
    //     case purple:
    //         spot_1.RGBW = PURPLE(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(purple));
    //       break;
    //     case magenta:
    //         spot_1.RGBW = MAGENTA(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(magenta));
    //       break;
    //     case pink:
    //         spot_1.RGBW = PINK(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(pink));
    //       break;
    //     case gold:
    //         spot_1.RGBW = GOLD(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(gold));
    //       break;
    //     default:
    //         spot_1.RGBW = WHITE(255);
    //         led.RGB = fcn::convert_8_to_12bits( fcn::RGB(white));
    //       break;
    //     }      

    //     spot_2.RGBW = spot_1.RGBW;
    //     spot_3.RGBW = spot_1.RGBW;
        
    //     ola_buffer.SetRange(led.get_address(), led.buffer().data(), led.get_nCH());
    //     ola_buffer.SetRange(spot_1.address, spot_1.buffer().data(), spot_1.nCH);
    //     ola_buffer.SetRange(spot_2.address, spot_3.buffer().data(), spot_3.nCH);
    //     ola_buffer.SetRange(spot_3.address, spot_3.buffer().data(), spot_3.nCH);
        
    //     ola_client.SendDmx(1, ola_buffer);
    //     cout<<colorName[c]<<endl;
    //     cout<<colorName[c]<<endl;
        
    //   }
    // }

    // DMX_vec data = {0,8,255,17};
    // cout << fcn::DMXvec_to_str(data, ',');
    // cout << endl;
    
    // cout << fcn::num_to_str((int)127) << " " << fcn::num_to_str((uint8_t)128) << endl;

    // log(1, "Premiere entrée");
    // log(1, "Deuxième entrée");
    // log(1, "Troisième entrée");
    // log(1, "Quatrième entrée");

    // spit_log();

  // for (int i=0; i<255; i++){
  //   cout<< i <<"\t:\t" << min_max( map(i, 50,180,0,255), 0,255)<<endl;
  // }


  // led.RGB = fcn::RGB(white);
  // ola_buffer.SetRange(led.get_address(), led.buffer().data(), led.get_nCH());
  // ola_client.SendDmx(1, ola_buffer);

  // int_vec vals = {0,1};
  // int_vec proba = {5,5};

  // for (int i=0; i<30; i++){
  //   cout << fcn::random_pick(vals, proba) << endl;
  // }
  // time_ms start = millis();

  // while (true){
  //   time_ms t = millis();
  //   int y = (int)fcn::sin_wave(t, 1000, 0,50,0);
  //   // int y = (int)fcn::square_wave(t, 1000, 0,50,0.3, 0);
  //   // int y = (int)fcn::triangle_wave(t, 1000, 0,50,0.2, 0);


  //   cout << string((int)y, ' ') << '.' << endl;
  //   delay(50);
  // }

  // while (true){
  //   cout << rand_min_max(0,4) << endl;
  //   delay(200);
  // }

  // color_vec c = {};
  // while (true){
  //   cout << colorName[(int)fcn::random_pick(c, int_vec{})] << endl;
  //   delay(200);
  // }

  // Chat GPT Example :
    // std::vector<int> myVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // std::cout << "Original Vector: ";
    // for (const int& element : myVector) {
    //     std::cout << element << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Random Order: ";
    // readVectorInRandomOrder(myVector);


    #ifndef LINUX_PC // if compiling on raspberrypi
      _PCA9685_DEBUG = 0;
      _PCA9685_TEST = 0;

      fd = PCA9685_openI2C(1, addr);
      PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);
    #endif

    while (true){
      static uint8_t i=0;

      led.RGBout=fcn::convert_8_to_12bits(DMX_vec{i,i,i});
      send();
      i+=10;
      delay(100);
    }
}