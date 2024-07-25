#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <wiringPi.h>
#include <algorithm>

#include <ola/DmxBuffer.h>
#include <ola/client/StreamingClient.h>

#include "debug.h"
#include "fixtures.h"
#include "music.h"
#include "sysfcn.h"
#include "config.h"

using namespace std;

#ifndef LINUX_PC // if compiling on raspberrypi
    // I2C Hardware interface (PCA9685)
    int fd;
    int addr = 0x40;
    unsigned int setOnVals[_PCA9685_CHANS]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int setOffVals[_PCA9685_CHANS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

// DMX output interface (OLA)
    ola::client::StreamingClient ola_client;
    ola::DmxBuffer ola_buffer;
    vector<ola::DmxBuffer> ola_pix_buffers(NUM_SUBPIX/MAX_SUBPIX_PER_UNI + ((NUM_SUBPIX%MAX_SUBPIX_PER_UNI)==0 ? 0 : 1));

fix_vec ll_fxtrs = {&led, &spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, &spot_7,&spot_8, &spot_9, &spider, &laser};
fix_vec fixtures = {&addr_led, &led, &laser, &front_rack, &back_rack, &spider};

bool process_arguments(int n, char* args[]){
    for (int i=1; i<n; i++){
        char* arg = args[i];

        if (strcmp(arg, "--help") == 0){
            cout << "Arguments :\n--noled\n--nomusic\n--nocurses\n--animation <anim_id>" << endl;
            exit(0);
        }else if(strcmp(arg, "--balise") == 0){
            b_BALISE = true;
            // b_CURSES = false;
        }
        else if (strcmp(arg, "--noled") == 0){
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
            while ( (i<n-1) && (string(args[++i]).find('-') != 0) ) {
                vec_anim_id.push_back(string(args[i]));
                balise( (*(vec_anim_id.end()-1)).data() );
            }
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
    for(auto buf : ola_pix_buffers){
        buf.Blackout();
    }

    balise("Init. Sampler...");
    sampler.init();   // initialize Music lib
    
    balise("Init Animator...");
    animator.init();
    
    balise("Init. fixtures...");
    for (fix_vec::iterator fixture = fixtures.begin(); fixture != fixtures.end(); fixture++){
        balise("Initializing ", (*fixture)->name);
        (*fixture)->init();
    }

    
    if (!b_BALISE){
        balise("Init. Debug...");
        init_display();
    }
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

    // construct & send DMX frame for old school fixtures (COTS DMX fixtures)
    balise("Construct & send buffer for classical fixtures");
    for (fix_vec::iterator fx = ll_fxtrs.begin(); fx != ll_fxtrs.end(); fx++){
        ola_buffer.SetRange((*fx)->get_address(), (*fx)->buffer().data(), (*fx)->get_nCH());
    }
    ola_client.SendDmx(0, ola_buffer);

    // construct & send DMX frames for addressable leds pixels values (sent through artnet)
    balise("Construct & send buffer for artnet pixels");
    DMX_vec sub_buffer, long_buffer = addr_led.buffer();
    auto start = long_buffer.begin();
    int universe_cpt = 1;
    for(auto& pix_buf : ola_pix_buffers){
        unsigned int length;
        if (long_buffer.end() > start + MAX_SUBPIX_PER_UNI){
            sub_buffer.assign(start, start + MAX_SUBPIX_PER_UNI);
            length = MAX_SUBPIX_PER_UNI;
            start += MAX_SUBPIX_PER_UNI;
        }else{ 
            sub_buffer.assign(start, long_buffer.end());
            length = distance(start, long_buffer.end());
        }

        pix_buf.SetRange(0, sub_buffer.data(), length);
        ola_client.SendDmx(universe_cpt++, pix_buf);
    }

}

LoopControler frame;

int main(int argc, char* argv[]){
    log(4, __FILE__, " ",__LINE__, " ", __func__);


    // MAIN PROGRAM (take what is needed and comment out the rest    
    initialize();
    // balise("Initalisation terminated with success !");

    // while (true){
    //     log(4, __FILE__, " ",__LINE__, " ", __func__);

    //     // Update general counters and timers
    //     balise("----------------------------Start new frame...");
    //     frame.start_new_frame();
        
    //     // Record and process music sample 
    //     balise("Record & process sample...");   
    //     sampler.update();

    //     balise("Run animator...");
    //     if(!b_test){    // if nominal case
    //         balise("Run animator normal update");
    //         // animator.random_update();
    //         // animator.palette_update();
    //         animator.test_update();
    //     }
    //     else if (frame.cpt == 0){   // else activate once and for all the animations to test
    //         balise("Run animator test fcn");
    //         if(!animator.test_animation()){
    //             // return -1;
    //         }
    //     }

    //     balise("Compute new frames...");
    //     for (fix_vec::iterator fixture = fixtures.begin(); fixture != fixtures.end(); fixture++){
    //         log(4, (*fixture)->name, " : new frame for ", (*fixture)->active_animation->id.data());
    //         (*fixture)->active_animation->new_frame();
    //     }
    //     // led.active_animation->new_frame();
    //     // //spot_g.active_animation->new_frame();
    //     // front_rack.active_animation->new_frame();
    //     // spider.active_animation->new_frame();
        
    //     balise("Send frame...");
    //     send();

    //     if (true || !b_BALISE){
    //         balise("Debug...");
    //         if (!b_CURSES){
    //             display();
    //         }else{
    //             display_curse();
    //         }
    //     }

    //     balise("Wait next frame...");
    //     frame.wait_for_next();
    // }



    while (true){
        for(auto int_c = 0; int_c < colorName.size(); int_c++){
            auto c = (simpleColor)int_c;
            addr_led.set_allpix_color(c);
            send();
            delay(1000);
        }
    }
}