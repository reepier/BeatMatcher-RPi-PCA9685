#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "wiringPi.h"
using namespace std;

#include <ola/DmxBuffer.h>
#include <ola/client/StreamingClient.h>

#include "constant.h"
#include "config.h"
#include "sysfcn.h"
#include "music.h"
#include "animator.h"
#include "fixtures.h"

// DMX output interface (OLA)
  ola::client::StreamingClient ola_client;
  ola::DmxBuffer ola_buffer;

fix_vec ll_fxtrs = {&led, &spot_1, &spot_2, &spot_3, &spot_d, &spot_g, &spider};
fix_vec fixtures = {&front_rack, &led, &spider};

LoopControler frame;

void build_buffer(){
    
}

void send_buffer(){

}

void spit_colors(){
  for(int c = simpleColor::black; c != simpleColor::last_color; c++){
    cout << colorName[c] << "\t: RGBW{" << fcn::DMXvec_to_str(fcn::RGBW((simpleColor)c), ',') << "} \t RGB{" << fcn::DMXvec_to_str(fcn::RGB((simpleColor)c), ',') << "}" << endl;
  }
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

  int_vec vals = {0,1};
  int_vec proba = {5,5};

  for (int i=0; i<30; i++){
    cout << fcn::random_pick(vals, proba) << endl;
  }
}