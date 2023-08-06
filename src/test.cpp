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

    DMX_vec rgbw(4);
    while(true){
      for(int c = SimpleColor::black; c != SimpleColor::last_color; c++){
        
        spot_1.RGBW = fcn::RGBW((SimpleColor)c);
        spot_2.RGBW = fcn::RGBW((SimpleColor)c);
        spot_3.RGBW = fcn::RGBW((SimpleColor)c);
      
        
        ola_buffer.SetRange(spot_1.address, spot_1.buffer().data(), spot_1.nCH);
        ola_buffer.SetRange(spot_2.address, spot_3.buffer().data(), spot_3.nCH);
        ola_buffer.SetRange(spot_3.address, spot_3.buffer().data(), spot_3.nCH);
        
        cout<<colorName[c]<<endl;
        ola_client.SendDmx(1, ola_buffer);
        delay(1000);
      }
    }

    // DMX_vec data = {0,8,255,17};
    // cout << fcn::DMXvec_to_str(data, ',');
    // cout << endl;
    
    // cout << fcn::num_to_str((int)127) << " " << fcn::num_to_str((uint8_t)128) << endl;
}