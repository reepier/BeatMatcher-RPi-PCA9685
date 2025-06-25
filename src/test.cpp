#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <wiringPi.h>
#include <algorithm>
#include <thread>
#include <csignal>
#include <cstdlib>

#include "debug.h"
#include "fixtures.h"
#include "music.h"
#include "animator.h"
#include "DMXio.h"
#include "sysfcn.h"
#include "config.h"

using namespace std;
    

fix_vec ll_fxtrs = {    /*&led,*/ &spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, 
                        &spot_7, &spot_8, &spot_9, &spot_10, &spot_11, &spot_12, 
                        &spot_13, &spot_14, &spot_15, &spot_16, &spot_17, &spot_18, &spot_19, &spot_20,
                        &spider, &laser, &laserbox1};

fix_vec fixtures = {&addr_led, &laser, &spot_rack_1, &spot_rack_2, &spot_rack_4, &spot_rack_3, &spider, &lasergroup1/*, &lasergroup1*/};

bool process_arguments(int n, char* args[]){
    for (int i=1; i<n; i++){
        char* arg = args[i];

        if (strcmp(arg, "--help") == 0){
            cout << "Arguments :\n--noled\n--nomusic\n--nocurses\n--animation <anim_id>" << endl;
            exit(0);
        }else if(strcmp(arg, "--balise") == 0){
            b_BALISE = true;
        }
        else if (strcmp(arg, "--nomusic") == 0){
            b_NO_MUSIC = true;
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



    return true;
}

void on_exit(int signal) {
    std::cout << "\nCaught Ctrl+C (SIGINT), restoring terminal settings...\n";
    std::system("stty sane");  // restore terminal settings
    std::exit(0);              // exit cleanly
}

void initialize() {

    // Register signal handler
    std::signal(SIGINT, on_exit);

    srand((unsigned)time(nullptr));


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
        //  int val = fcn::heartbeat(millis(), 20, 0.0, 180.0);
        //  spot_6.pixel = spot_6.RGBW(red, val);
        //  spot_9.pixel = spot_9.RGBW(red, val);
         
        vector<double> vals = fcn::heartbeat_vec(millis(), 20, 0.0, 180.0);
        spot_6.pixel = spot_6.RGBW(red, vals[0]);
        spot_9.pixel = spot_9.RGBW(red, vals[1]);
        
        
        send();
        delay(20);
    }

}