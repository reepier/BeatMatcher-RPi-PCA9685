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

double tri(time_ms t, time_ms t0, time_ms period, double min, double max, double alpha=0.5){
    double x = ( (int)t-(int)t0 )/ (double)period;
    // cout << "\tt:"<<(int)t<< "\tt0:"<<(int)t0<< "\tT:"<<(int)period<< "\ta:"<<alpha<< "\tx:"<<x<<endl;

    if ( -alpha <= x  &&  x <= 0  ){
    //   std::cout<<"mark1: " << -alpha << " "<< x << " "<< 0 << " " << endl; 
        return map(x, -alpha, 0.0, (double)min, (double)max);
    }
    else if (0 < x  &&  x <= 1-alpha ){
    //   std::cout<<"mark2: " << 0 << " "<< x << " "<< 1-alpha << " " << endl;
        return map(x, 0.0, 1.0-alpha, (double)max, (double)min);
    }
    else {
    //   std::cout<<"mark3: " << endl;
        return min;
    }
}


int main(){
    cout << "ola_setup "<<endl;
    ola_client.Setup();
    srand(millis());
    #ifndef LINUX_PC // if compiling on raspberrypi
        balise("Init. PCA...");
        _PCA9685_DEBUG = 0;
        _PCA9685_TEST = 0;

        fd = PCA9685_openI2C(1, addr);
        PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);
    #endif

    // color_vec cp1 = {black, white};
    // color_vec cp2 = {red, black};
    // color_vec cp3 = {purple, orange};
    // color_vec cp4 = {white, black};

    // cout << (fcn::are_consistent(cp1, cp2) ? 1 : 0) << endl;
    // cout << (fcn::are_consistent(cp1, cp2, 2) ? 1 : 0) << endl;

    // cout << (fcn::are_consistent(cp1, cp3) ? 1 : 0) << endl;
    // cout << (fcn::are_consistent(cp1, cp4, 2) ? 1 : 0) << endl;
    // cout << (fcn::are_consistent(cp1, cp4, 1) ? 1 : 0) << endl;

    // while (true) {
    //     for (int i=0; i<40; i++){
    //         // cout << i << ":\t" << string((int)fcn::gaussian(i, 20, 15, 1, 80)-1, '-')<<'o' << endl;
    //         // cout << i << ":\t" << string((int)fcn::gaussian2(i, 20, 15, 1, 80)-1, '-')<<'o' << endl;
    //         // cout << i << ":\t" << string((int)tri(i, 20, 20, 1, 80, 0.2)-1, '-')<<'o'<< endl;
    //         // cout << i << ":\t" << string((int)fcn::triangle(i, 20, 20, 1, 80, 0.8)-1, '-')<<'o'<< endl;
    //         // cout << i << ":\t" << string((int)fcn::square(i, 20, 15, 1, 80, 0.2)-1, '-')<<'o'<< endl;
    //         delay(100);
    //     }
    // }

    // double y = tri(8,10,20, 0,15, 0.2);
    // cout << y << endl;

    // y = tri(10,10,20, 0,15, 0.2);
    // cout << y << endl;

    // y = tri(12,10,20, 0,15, 0.2);
    // cout << y << endl;

    // y = tri(30,10,20, 0,15, 0.2);
    // cout << y << endl;

    // cout << "start"<<endl;
    // int_vec vec = {1,2,3,4,5,6};
    // cout << "base vec created"<<endl;
    // while(true){
    //     int_vec out_vec = fcn::randomized_vector(vec);
    //     cout << fcn::vec_to_str(  vec, ',') << "  -->  ";
    //     cout << fcn::vec_to_str(  out_vec, ',') <<endl;
    //     delay(1000); 
    // }

    animator.init();
    spider.init();

    // cout << "Animations : " << endl;
    // for (auto anim : spider.animations){
    //     cout << anim->id << " : " << fcn::palette_to_string(anim->color_palette, '/') << endl;
    // }

    // for (auto pal : animator.palette_magasine.color_palettes){
    //     cout << "Palette " << fcn::palette_to_string(pal, '/') << endl;
    //     for (int i=0; i<5; i++){
    //         spider.activate_by_color(pal);
    //         cout << "Tirage : " << spider.active_animation->id << "\t" << fcn::palette_to_string(spider.active_animation->color_palette, '/') << endl;
    //     }
    // }

    spider.activate_by_color(color_vec{blue, purple}, leader);
    spider.activate_by_color(color_vec{blue, purple}, backer);
    spider.activate_by_color(color_vec{blue, purple}, any);
    

}