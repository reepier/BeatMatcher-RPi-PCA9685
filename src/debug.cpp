#include <iostream>
#include <ncurses.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <charconv>

#include "sysfcn.h"
#include "debug.h"
#include "animator.h"
#include "music.h"
#include "fixtures.h" 

using namespace std;

// extern SoundAnalyzer sampler;
// extern AnimationManager animator;
// extern LoopControler frame;

LogList log_list;

WINDOW *musicw;
WINDOW *animw;
WINDOW *outputw;
WINDOW *generalw;
WINDOW *consolew;
WINDOW *spectrumw;

#define WHITEred    3 // WHITE font / red background
#define WHITEgreen  4
#define WHITEblue   5
#define WHITEblack  1
#define BLACKwhite  2

#define C1 11
#define C2 74
#define C3 80

const int spectrumw_height = 48;
const int spectrumw_width = 40;

void init_display(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);


    initscr();
    // noecho();
    // refresh();
    // curs_set(0);
    musicw      = newwin(10,90, 0,0);
    animw       = newwin(5,90,10,0);
    outputw     = newwin(10,90,15,0);
    generalw    = newwin(3,90,25,0);
    consolew    = newwin(20,90,28,0);
    spectrumw   = newwin(spectrumw_height,spectrumw_width,0,90);


    if (!has_colors()){
        cout << "NO COLORS";
        exit(1);
    }
    start_color();
    init_pair(WHITEblack, COLOR_WHITE, COLOR_BLACK);
    init_pair(BLACKwhite, COLOR_BLACK, COLOR_WHITE);
    init_pair(WHITEred, COLOR_WHITE, COLOR_RED);
    init_pair(WHITEgreen, COLOR_WHITE, COLOR_GREEN);
    init_pair(WHITEblue, COLOR_WHITE, COLOR_BLUE);
}


/**
#     #                        
##   ## #    #  ####  #  ####  
# # # # #    # #      # #    # 
#  #  # #    #  ####  # #      
#     # #    #      # # #      
#     # #    # #    # # #    # 
#     #  ####   ####  #  ####  
*/
void disp_music_window(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    
    //initialize
    curs_set(0);
    werase(musicw);
    box(musicw, ACS_VLINE, ACS_HLINE);
    wattron(musicw, A_BOLD);
    mvwprintw(musicw, 0,1, "MUSIC");
    wattroff(musicw, A_BOLD);

    ostringstream volbuf, lagvolbuf, thrbuf, maxminbuf, clipbuf, beatbuf, statebuf ,nbt, nbk, ndrop;
    // print Volume vumeter
    #define MAXVOL 400.0    //max volume value (approx.)   
    #define MAXVOLPX 60     //number of pixel allocated to volume bar
    // double vol_unit = max(min(100/MAXVOL, 1.0),0.0);    //unitary volume value [0;1]
    double vol_unit     = max(min(sampler.volume/MAXVOL, 1.0),0.0);    //unitary volume value [0;1]
    double lagvol_unit  = max(min(sampler.lagging_volume/MAXVOL, 1.0),0.0);
    int vol_px = pow(vol_unit, 0.5) * MAXVOLPX;
    int lagvolpix = pow(lagvol_unit, 0.5) * MAXVOLPX;
    volbuf << string(vol_px, 'o');
    lagvolbuf << 
    
    mvwprintw(musicw, 1,1, "Volume");
    mvwprintw(musicw, 1,C1,"|");
    mvwprintw(musicw, 1,C1 + 1, volbuf.str().c_str());
    mvwprintw(musicw, 1,C1 + 1 + lagvolpix, "0");
    mvwprintw(musicw, 1,C2, "|");
    mvwprintw(musicw, 1,C2+1, to_string(sampler.recent_maximum(1000)).c_str());
    mvwprintw(musicw, 1,C3, "|");
    
    // Threshold
    // double thr_unit = max(min(100/MAXVOL, 1.0),0.0);  //unitary threshold value [0;1]
    double thr_unit = max(min(   sampler.beat_threshold/MAXVOL  ,1.0),0.0);  //unitary threshold value [0;1]
    int thr_px = pow(thr_unit, 0.5) * MAXVOLPX;
    thrbuf << "Threshold | " << string(thr_px-1, ' ') << '|' << string(MAXVOLPX-thr_px, ' ') << " | " << (int)sampler.beat_threshold;
    // mvwprintw(musicw, 2,1, "Threshold");
    // mvwprintw(musicw, 2,1, thrbuf.str().c_str());
    // mvwprintw(musicw, 1,80, "|");
    // mvwprintw(musicw, 2,80, "|");

    mvwprintw(musicw, 1, C1 + thr_px, "|");    //test

    maxminbuf << "Max/Min : " << sampler.deb_max << "/" << sampler.deb_min;
    // mvwprintw(musicw, 3,1, maxminbuf.str().c_str());
    
    // CLIPPING warnig
    clipbuf << (sampler.clipping?"CLIP":"");
    wattron(musicw, A_BOLD);
    mvwprintw(musicw, 1,83, clipbuf.str().c_str());
    wattroff(musicw, A_BOLD);

    // BEAT signal 
    beatbuf << (sampler.raw_beat?"BEAT":"");
    wattron(musicw, A_BOLD);
    mvwprintw(musicw, 2,83, beatbuf.str().c_str());
    wattroff(musicw, A_BOLD);

    switch(sampler.state){
        case BEAT :
            statebuf << "BEAT";
            break;
        case BREAK :
            statebuf << "        BREAK";
            break;
        case SUSTAINED_BREAK :
            statebuf << "        BREAK +";
            break;

        case BAD_SIGNAL :
            statebuf << "                   BAD_SIGNAL";
            break;
        default :
            break;
    }
    mvwprintw(musicw, 4,1, statebuf.str().c_str());


    nbt     << "Nxt beat : " << (sampler.t_next_beat_ms - millis())/1000.0 << "s";
    nbk     << "| Nxt break : " << (sampler.t_next_break_ms - millis())/1000.0  << "s";
    ndrop   << "| Nxt drop : " << (sampler.t_next_drop_ms - millis())/1000.0  << "s";
    


    #ifdef LINUX_PC
        // mvwprintw(musicw, 6,1, nbt.str().c_str());
        mvwprintw(musicw, 6,31, nbk.str().c_str());
        mvwprintw(musicw, 6,51, ndrop.str().c_str());
    #else
    if(b_NO_MUSIC){
        mvwprintw(musicw, 6,1, nbt.str().c_str());
        mvwprintw(musicw, 6,31, nbk.str().c_str());
        mvwprintw(musicw, 6,51, ndrop.str().c_str());
    }
    #endif
    // mvwprintw(...

    wrefresh(musicw);
}

//TODO : Fill animator window with with timer to animation change

/**
#######                                  
#     # #    # ##### #####  #    # ##### 
#     # #    #   #   #    # #    #   #   
#     # #    #   #   #    # #    #   #   
#     # #    #   #   #####  #    #   #   
#     # #    #   #   #      #    #   #   
#######  ####    #   #       ####    #   
*/
void disp_output_window(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

//initialize
    curs_set(0);
    werase(outputw);
    box(outputw, ACS_VLINE, ACS_HLINE);
    wattron(outputw, A_BOLD);
    mvwprintw(outputw, 0,1, "OUTPUT");
    wattroff(outputw, A_BOLD);

    int line=1;
    for (auto fix : fix_vec{&addr_led, /*&led,*/ &laser, &front_rack, &spider, &rack_15, &rack_40, &shehds_rack, &redrayz}){
        if (fix->active_animation != nullptr){
            ostringstream animbuf, outbuf;
            
            animbuf << ((fix->active_animation->type == leader) ? "(L) ":((fix->active_animation->type == backer) ? "(b) " : "(a) ")) << fix->name << " " << fix->active_animation->id << " - " << fix->active_animation->description;
            
            DMX_vec raw_buf = fix->buffer();
            outbuf << "| " <<fcn::vec_to_str(raw_buf, ',');

            int max_length = 40;
            mvwprintw(outputw, line, 1, animbuf.str().data());
            mvwprintw(outputw, line, 45, outbuf.str().size()<max_length? outbuf.str().data() : outbuf.str().substr(0, max_length).data());
            
            if((fix == &front_rack) || fix == &shehds_rack)  line+=2;
            else line += 1;
        }


    }


    wrefresh(outputw);
}

/*
    #     #     #  ###  #     #     #     #######  #######  ######  
   # #    ##    #   #   ##   ##    # #       #     #     #  #     # 
  #   #   # #   #   #   # # # #   #   #      #     #     #  #     # 
 #     #  #  #  #   #   #  #  #  #     #     #     #     #  ######  
 #######  #   # #   #   #     #  #######     #     #     #  #   #   
 #     #  #    ##   #   #     #  #     #     #     #     #  #    #  
 #     #  #     #  ###  #     #  #     #     #     #######  #     # 
*/
void disp_animation_window(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

//initialize
    curs_set(0);
    werase(animw);
    // box(animw, ACS_VLINE, ACS_HLINE);
    wattron(animw, A_BOLD);
    mvwprintw(animw, 0,1, "ANIMATOR");
    wattroff(animw, A_BOLD);

    ostringstream anim_change_buf, show_int_buf;
    long timer =  ((long)animator.t_last_change_ms + (long)TEMPO_ANIM_CHANGE - (long)frame.t_current_ms)/1000.0;

    anim_change_buf << "Animation switch : " << (timer>0 ? timer : 0);
    mvwprintw(animw, 2, 1, anim_change_buf.str().c_str());

    show_int_buf << "Show intensity : " << SHOW_INTENSITY;
    mvwprintw(animw, 2, 35, show_int_buf.str().c_str());

    wrefresh(animw);
}
/**
 #####                                            
#     # ###### #    # ###### #####    ##   #      
#       #      ##   # #      #    #  #  #  #      
#  #### #####  # #  # #####  #    # #    # #      
#     # #      #  # # #      #####  ###### #      
#     # #      #   ## #      #   #  #    # #      
 #####  ###### #    # ###### #    # #    # ###### 
*/
void disp_general_window(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

//initialize
    curs_set(0);
    werase(generalw);
    // box(generalw, ACS_VLINE, ACS_HLINE);
    wattron(generalw, A_BOLD);
    mvwprintw(generalw, 0,1, "GENERAL");
    wattroff(generalw, A_BOLD);

    ostringstream cptbuf;
    cptbuf << "Frame counter : " << frame.cpt;
    mvwprintw(generalw, 1,1, cptbuf.str().c_str());

    ostringstream timbuf;
    timbuf << "Clock : " << frame.t_current_ms/1000.0 << "s";
    mvwprintw(generalw, 1, 25, timbuf.str().c_str());

    ostringstream oheadbuf;
    char * statement;
    if (frame.loop_overhead) statement = "YES";
    else statement = "FALSE";
    oheadbuf << "Calc Overhead : " << statement << " " << frame.loop_overhead_us/1000 << "ms";
    mvwprintw(generalw, 1, 50, oheadbuf.str().c_str());


    wrefresh(generalw);
}

/**
 #####                                            
#     #  ####  #    #  ####   ####  #      ###### 
#       #    # ##   # #      #    # #      #      
#       #    # # #  #  ####  #    # #      #####  
#       #    # #  # #      # #    # #      #      
#     # #    # #   ## #    # #    # #      #      
 #####   ####  #    #  ####   ####  ###### ###### 
*/

void disp_console_window(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    curs_set(0);
    werase(consolew);
    box(consolew, ACS_VLINE, ACS_HLINE);
    wattron(consolew, A_BOLD);
    mvwprintw(consolew, 0,1, "CONSOLE");
    wattroff(consolew, A_BOLD);

    if (log_list.size() == 0){

    }else{
        int i = 19;
        for (LogList::reverse_iterator log = log_list.rbegin(); log != log_list.rend(); log++){
            mvwprintw(consolew, i, 1, fcn::ms_to_hhmmssms((*log).timestamp).c_str());
            mvwprintw(consolew, i--, 1+(*log).level-1+15, (*log).message.c_str());
            if (i==0){
                break;
            }
        }
    }

    wrefresh(consolew);
}

/*
 #####  ######  #######  #####  ####### ######  #     # #     # 
#     # #     # #       #     #    #    #     # #     # ##   ## 
#       #     # #       #          #    #     # #     # # # # # 
 #####  ######  #####   #          #    ######  #     # #  #  # 
      # #       #       #          #    #   #   #     # #     # 
#     # #       #       #     #    #    #    #  #     # #     # 
 #####  #       #######  #####     #    #     #  #####  #     # 
 */

 
void disp_spectrum_window(){
    curs_set(0);
    werase(spectrumw);
    box(spectrumw, ACS_VLINE, ACS_HLINE);
    wattron(spectrumw, A_BOLD);
    mvwprintw(spectrumw, 0,1, "SPECTRUM");
    wattroff(spectrumw, A_BOLD);

    for (int i=0 ; i<BUF_LENGTH && i<spectrumw_height-2; i++){
        mvwprintw(spectrumw, i+1, 1, fcn::num_to_str(sampler.sample_spectrum[i][FREQ]).c_str());
        double val_log = max(0.0, (double)20*log10(sampler.sample_spectrum[i][AMPL]));
        double val_unit = val_log/100;
        int val_pix = min((double)(spectrumw_width-7), val_unit * (spectrumw_width-7));
        mvwprintw(spectrumw, i+1, 1+4+1, string(val_pix, '|').c_str());
    }

/* DO stuff */

    wrefresh(spectrumw);
}

void display_curse(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    
    // balise("*********music window");
    disp_music_window();
    // balise("*********animation window");
    disp_animation_window();
    // balise("*********output window");
    disp_output_window();
    // balise("*********general window");
    disp_general_window();
    // balise("*********console window");
    disp_console_window();

    disp_spectrum_window();
    
    // werase(animw);
    // box(animw, ACS_VLINE, ACS_HLINE);
    // wrefresh(animw);
    // werase(outputw);
    // box(outputw, ACS_VLINE, ACS_HLINE);
    // wrefresh(outputw);

    
    
    refresh();
}

/* The main program interface looks as follows : 

┌MUSIC─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│Volume    |ooooooooooo0                                  |               |399  |  CLIP                                │
│                                                                                  BEAT                                │
│                                                                                                                      │
│ BEAT   BREAK +  BAD_SIGNAL                                                                                           │
│                                                                                                                      │
│                              | Nxt break : 12.287| Nxt drop : 2.687s                                                 │
│                                                                                                                      │
│                                                                                                                      │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
┌ANIMATOR──────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                                                                                      │
│Animation switch : 0              Show intensity : 0                                                                  │
│                                                                                                                      │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
┌OUTPUT────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│(a) LEDs PIX.6.2.3 - Pixels Analog Beat               |   5,  0,  7,  5,  0,  7,  5,  0,  7,  5,  0,  7,  5,  0,      │
│(b) Laser LAS.0 -                                     |   0,  0,  0,  0,  0,  0,  0,  0                               │
│(a) Front Rack FR.0.0.1 - Flash animation with Autocol|                                                               │
│                                                                                                                      │
│(a) Spider SPI.0.0 -                                  |   0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,      │
│(b) Vert. Beams R15.0 -                               |                                                               │
│(b) Rack 2 R40.0 -                                    |                                                               │
│(b) SHEHDS Rack BR2.0 -                               |                                                               │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
┌GENERAL───────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│Frame counter : 656     Clock : 8806.85s         Calc Overhead : YES 22ms                                             │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
┌CONSOLE───────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│                                                                                                                      │
│2:26:30:216    Activating LED.0.0:                                                                                    │
│2:26:30:216    Activating LAS.0:                                                                                      │
│2:26:30:216    Activating SPI.0.0:                                                                                    │
└2:26:30:337────src/animator.cpp autocolor_update Sodium/Purple────────────────────────────────────────────────────────┘



*/