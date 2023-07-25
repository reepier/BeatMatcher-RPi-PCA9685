#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <wiringPi.h>

#include "debug.h"
#include "constant.h"
#include "LED.h"
#include "spot.h"
#include "music.h"
#include "animator.h"
#include "sysfcn.h"
#include "config.h"

using namespace std;

#ifndef LINUX_PC // if compiling on raspberrypi
  // I2C Hardware interface (PCA9685)
  int fd;
  int addr = 0x40;
  unsigned int setOnVals[_PCA9685_CHANS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned int setOffVals[_PCA9685_CHANS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

// DMX output interface (OLA)
  ola::client::StreamingClient ola_client;
  ola::DmxBuffer ola_buffer;


bool process_arguments(int n, char* args[]){
    for (int i=1; i<=n-1; i++){
        char* arg = args[i];

        if (strcmp(arg, "--noled") == 0){
            b_NO_LED = true;
        }
        else if (strcmp(arg, "--nomusic") == 0){
            b_NO_MUSIC = true;
        }
        else if(strcmp(arg, "--nocurses") == 0){
            b_CURSES == false;
        }
        else if(strcmp(arg, "--animation") == 0){
            b_test = true;
            ++i; // get the following argument
            arg = args[i];  
            s_anim_id = arg;
        }
        else{
            return false;
        }
    }

    #ifdef LINUX_PC //if compiling on PC, force NO_MUSIC and NO_LED since PCA9685 and MCP3008 are not compatible
        b_NO_MUSIC = true;
        b_NO_LED = true;
    #endif

    return true;
}

void initialize() {
    srand((unsigned)time(nullptr));
    

    #ifndef LINUX_PC // if compiling on raspberrypi
        balise("Init. PCA...");
        _PCA9685_DEBUG = 0;
        _PCA9685_TEST = 0;

        fd = PCA9685_openI2C(1, addr);
        PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);
    #endif

    balise("Init. ola...");
    ola_client.Setup();
    ola_buffer.Blackout();

    balise("Init. Sampler...");
    sampler.init();   // initialize Music lib
    
    balise("Init. fixtures...");
    led.init();   // initialize OLA & shit
    front_rack.init_front();
    //spot_g.init();
    

    balise("Init. Debug...");
    init_display();
}

void send(){
    #ifndef LINUX_PC // if compiling on raspberrypi
    // Send frame to the PCA9685 module
    // Take into account the MASTER DIMMER value !! --> as late as possible, right before data is sent
    setOffVals[LEDRed] = led.RGB[R] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDGreen] = led.RGB[G] * led.MASTER_DIMMER / 255.0;
    setOffVals[LEDBlue] = led.RGB[B] * led.MASTER_DIMMER / 255.0;

    PCA9685_setPWMVals(fd, addr, setOnVals, setOffVals);
#endif // DEBUG

    // send DMX frame to OLA server.
    ola_buffer.SetRange(led.address, led.buffer().data(), led.nCH);
    ola_buffer.SetRange(spot_g.address, spot_g.buffer().data(), spot_g.nCH);
    ola_buffer.SetRange(spot_d.address, spot_d.buffer().data(), spot_d.nCH);
    ola_buffer.SetRange(spot_1.address, spot_1.buffer().data(), spot_1.nCH);
    ola_buffer.SetRange(spot_2.address, spot_2.buffer().data(), spot_2.nCH);
    ola_buffer.SetRange(spot_3.address, spot_3.buffer().data(), spot_3.nCH);

    ola_client.SendDmx(1, ola_buffer);
}

LoopControler frame;

int main(int argc, char* argv[]){

    balise("Initialization...");
    if(!process_arguments(argc, argv)){
        cout << "Initialization failed : unknown argument(s) passed" << endl;
        return -1;
    }
    initialize();
    
    while (true){
        // Update general counters and timers
        balise("Start new frame...");
        frame.start_new_frame();
        
        // Record and process music sample 
        balise("Record & process sample...");   
        sampler.update(frame.t_current_ms);

        balise("Run animator...");
        if(!b_test){    // if nominal case
            animator.update();
        }
        else if (frame.cpt == 0){   // else activate once and for all the animations to test
            animator.test();
        }

        balise("Compute new frame...");
        led.active_animation->new_frame();
        //spot_g.active_animation->new_frame();
        front_rack.active_animation->new_frame();
        
        balise("Send frame...");
        send();

        balise("Debug...");
        if (!b_CURSES){
            display();
        }else{
            display_curse();
        }

        balise("Wait next frame...");
        frame.wait_for_next();
    }
}