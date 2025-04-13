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


// DMX output interface (OLA)
    ola::client::StreamingClient ola_output_client;
    ola::DmxBuffer ola_buffer;
    vector<ola::DmxBuffer> ola_pix_buffers(NUM_SUBPIX/MAX_SUBPIX_PER_UNI + ((NUM_SUBPIX%MAX_SUBPIX_PER_UNI)==0 ? 0 : 1));

fix_vec ll_fxtrs = {&spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6, &spot_7,&spot_8, &spot_9, &spider, &laser};
fix_vec fixtures = {&addr_led, &laser, &front_rack, &rack_15, &spider};

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
        else{
            return false;
        }
    }



    return true;
}

void initialize() {
    srand((unsigned)time(nullptr));


    balise("Init. ola...");
    ola_output_client.Setup();
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

    // construct & send DMX frame for old school fixtures (COTS DMX fixtures)
    balise("Construct & send buffer for classical fixtures");
    for (fix_vec::iterator fx = ll_fxtrs.begin(); fx != ll_fxtrs.end(); fx++){
        ola_buffer.SetRange((*fx)->get_address(), (*fx)->buffer().data(), (*fx)->get_nCH());
    }
    ola_output_client.SendDmx(0, ola_buffer);

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
        ola_output_client.SendDmx(universe_cpt++, pix_buf);
    }

}

LoopControler frame;

int main(int argc, char* argv[]){
    log(4, __FILE__, " ",__LINE__, " ", __func__);


    // MAIN PROGRAM (take what is needed and comment out the rest    
    // initialize();
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



    // while (true){
    //     for(auto int_c = 0; int_c < colorName.size(); int_c++){
    //         auto c = (simpleColor)int_c;
    //         addr_led.set_allpix_color(c);
    //         send();
    //         delay(1000);
    //     }
    // }



    // while(true){
    //     auto start = millis();
    //     auto t=start;
    //     while(t<(start+2000)){
    //         int val = min(255, max(0, (int)fcn::exp_decay(t, start, 1000, 0, 100) ));
            
    //         cout<<string(val, '-')<<endl;
    //         // cout<<(t-start)/1000.0<< " : " << val <<endl;
            
    //         delay(50);
    //         t=millis();
    //     }
    // }

    // while(true){
    //     auto t = millis();
    //     cout << t << " -> " << fcn::ms_to_hhmmss(t) << " or " << fcn::ms_to_hhmmssms(t) << endl;;
    //     delay(100);
    // }

    color_vec palette = {red, green, blue};
    color_vec authorized = {red, blue, orange, gold};
    color_vec unauthorized = {green, cyan};
    cout << "palette : " << fcn::palette_to_string(palette) <<endl;
    cout << "auth. : " << fcn::palette_to_string(authorized) <<endl<<endl;
    cout << "unauth. : " << fcn::palette_to_string(unauthorized) <<endl;
    cout << "palette <Inter.> authrozed : " << fcn::palette_to_string( fcn::get_vector_intersection(palette, authorized) , '/') << endl;
    cout << "palette - unauthorized : " << fcn::palette_to_string( fcn::get_vector_exclusion(palette, unauthorized) , '/') << endl;

}