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
#include "spider.h"
#include "spot.h"
#include "LED.h"

// DMX output interface (OLA)
  ola::client::StreamingClient ola_client;
  ola::DmxBuffer ola_buffer;

LoopControler frame;

void build_buffer(){
    
}

void send_buffer(){

}

int main(){
    ola_client.Setup();

    DMX_vec rgbw(4);
    while(true){
        rgbw[R] = 255*(1+sin(2*M_PI*millis()/5000))/2;
        rgbw[B] = 255*(1+sin(2*M_PI*millis()/5000 + M_PI))/2;
        spot_1.RGBW = rgbw;
        ola_buffer.SetRange(spot_1.address, spot_1.buffer().data(), spot_1.nCH);
        ola_client.SendDmx(1, ola_buffer);
        delay(10);
    }
}