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

int main(){
    ola_client.Setup();

    // while(true){
    //   for(int c = SimpleColor::black; c != SimpleColor::last_color; c++){
        
    //     switch (c)
    //     {
    //     case black:
    //         spot_1.RGBW = BLACK;
    //       break;
    //     case red:
    //         spot_1.RGBW = RED(255);
    //       break;
    //     case green:
    //         spot_1.RGBW = GREEN(255);
    //       break;
    //     case blue:
    //         spot_1.RGBW = BLUE(255);
    //       break;
    //     case orange:
    //         spot_1.RGBW = ORANGE(255);
    //       break;
    //     case purple:
    //         spot_1.RGBW = PURPLE(255);
    //       break;
    //     case gold:
    //         spot_1.RGBW = GOLD(255);
    //       break;
    //     default:
    //         spot_1.RGBW = WHITE(255);
    //       break;
    //     }      

    //     spot_2.RGBW = spot_1.RGBW;
    //     spot_3.RGBW = spot_1.RGBW;
        
    //     ola_buffer.SetRange(spot_1.address, spot_1.buffer().data(), spot_1.nCH);
    //     ola_buffer.SetRange(spot_2.address, spot_3.buffer().data(), spot_3.nCH);
    //     ola_buffer.SetRange(spot_3.address, spot_3.buffer().data(), spot_3.nCH);
        
    //     cout<<colorName[c]<<endl;
    //     ola_client.SendDmx(1, ola_buffer);
    //     delay(1000);
    //   }
    // }

    // DMX_vec data = {0,8,255,17};
    // cout << fcn::DMXvec_to_str(data, ',');
    // cout << endl;
    
    // cout << fcn::num_to_str((int)127) << " " << fcn::num_to_str((uint8_t)128) << endl;

    log(1, "Premiere entrée");
    log(1, "Deuxième entrée");
    log(1, "Troisième entrée");
    log(1, "Quatrième entrée");

    spit_log();
}