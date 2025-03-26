#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <wiringPi.h>
#include <algorithm>
#include <thread>


#include "debug.h"
#include "fixtures.h"
#include "music.h"
#include "animator.h"
#include "DMXio.h"
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

    

fix_vec ll_fxtrs = {    /*&led,*/ &spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, 
                        &spot_7, &spot_8, &spot_9, &spot_10, &spot_11, &spot_12, 
                        &spot_13, &spot_14, &spot_15, &spot_16, &spot_17, &spot_18, &spot_19, &spot_20,
                        &spider, &laser, &redrayz};

fix_vec fixtures = {&addr_led, &led, &laser, &front_rack, &rack_15, &rack_40, &shehds_rack, &spider, &redrayz};

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
            b_ANI_TEST = true;
            while ( (i<n-1) && (string(args[++i]).find('-') != 0) ) {
                cli_anim_id.push_back(string(args[i]));
                balise( (*(cli_anim_id.end()-1)).data() );
            }
        }
        else if(strcmp(arg, "--controled") == 0){
            b_EXT_CONTROL = true;
        }
        else{
            return false;
        }
    }


    #ifdef LINUX_PC //if compiling on PC, force NO_MUSIC and NO_LED since PCA9685 and MCP3008 are not compatible
        // b_NO_MUSIC = true;
        b_NO_LED = true;
    #endif

    return true;
}

void initialize() {
    srand((unsigned)time(nullptr));

    #ifndef LINUX_PC // if compiling on raspberrypi
    if (!b_NO_LED){
        balise("Init. PCA...");
        _PCA9685_DEBUG = 0;
        _PCA9685_TEST = 0;

        fd = PCA9685_openI2C(1, addr);
        PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);
    }
    #endif

    balise("Init. ola...");
    ola_output_client.Setup();
    ola_buffer.Blackout();
    for(auto pix_uni : ola_pix_unis){
        pix_uni.buf.Blackout();
    }
    

    balise("Init. Sampler...");
    sampler.init();   // initialize Music lib
    
    balise("Init Animator...");
    animator.init();
    
    balise("Init. fixtures...");
    for (fix_vec::iterator fixture = fixtures.begin(); fixture != fixtures.end(); fixture++){
        balise("Initializing ", (*fixture)->name);
        (*fixture)->init();
        (*fixture)->activate_none();
    }

    if (b_EXT_CONTROL) // very important to start DMX input code AFTER initializing Fixtures
        setup_DMX_input();

    if (!b_BALISE){
        balise("Init. Debug...");
        init_display();
    }
}

LoopControler frame;

int main(int argc, char* argv[]){
    log(4, __FILE__, " ",__LINE__, " ", __func__);


    balise("Initialization...");
    if(!process_arguments(argc, argv)){
        cout << "Initialization failed : unknown argument(s) passed" << endl;
        return -1;
    }
    initialize();
    balise("Initalisation terminated with success !");

    while (true){
        log(4, __FILE__, " ",__LINE__, " ", __func__);

        // Update general counters and timers
        balise("----------------------------Start new frame...");
        frame.start_new_frame();
        
        // Record and process music sample 
        balise("Record & process sample...");   
        sampler.update();

        // Run animator
        balise("Run animator...");
        if(!b_ANI_TEST && !b_EXT_CONTROL){    // if nominal case
            balise("Run animator normal update");
            // animator.random_update();
            // animator.palette_update();
            // // animator.show_update();
            //animator.nov30_maximum_update();
            animator.autocolor_update();
        }
        else if (!b_EXT_CONTROL && b_ANI_TEST && frame.cpt == 0){   // else activate once and for all the animations to test
            balise("Run animator test fcn");
            if(!animator.test_animation()){
                // return -1;
            }
        }

        balise("Compute new frames...");
        for (fix_vec::iterator fixture = fixtures.begin(); fixture != fixtures.end(); fixture++){
            if((*fixture)->active_animation != nullptr){
                log(4, (*fixture)->name, " : new frame for ", (*fixture)->active_animation->id.data());
                (*fixture)->active_animation->new_frame();
            }
        }

        // led.active_animation->new_frame();
        // //spot_g.active_animation->new_frame();
        // front_rack.active_animation->new_frame();
        // spider.active_animation->new_frame();
        
        balise("Send frame...");
        send();

        if (true || !b_BALISE){
            balise("Debug...");
            if (!b_CURSES){
                display();
            }else{
                display_curse();
            }
        }

        balise("Wait next frame...");
        frame.wait_for_next();
    }
}