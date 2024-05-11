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
#include "LED.h"
#include "fixtures.h" 

using namespace std;

extern SoundAnalyzer sampler;
extern AnimationManager animator;
extern LoopControler frame;

LogList log_list;

WINDOW *musicw;
WINDOW *animw;
WINDOW *outputw;
WINDOW *generalw;
WINDOW *consolew;

#define WHITEred    3 // WHITE font / red background
#define WHITEgreen  4
#define WHITEblue   5
#define WHITEblack  1
#define BLACKwhite  2

#define C1 11
#define C2 74
#define C3 80

void init_display(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);


    initscr();
    // noecho();
    // refresh();
    // curs_set(0);
    musicw      = newwin(10, 120, 0,0);
    animw       = newwin(5,120,10,0);
    outputw     = newwin(10,120,15,0);
    generalw    = newwin(3,120,25,0);
    consolew    = newwin(20,120,28,0);


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

    ostringstream volbuf, thrbuf, maxminbuf, clipbuf, beatbuf, statebuf ,nbt, nbk, ndrop;
    // Volume
    #define MAXVOL 400.0    //max volume value (approx.)   
    #define MAXVOLPX 60     //number of pixel allocated to volume bar
    // double vol_unit = max(min(100/MAXVOL, 1.0),0.0);    //unitary volume value [0;1]
    double vol_unit = max(min(sampler.volume/MAXVOL, 1.0),0.0);    //unitary volume value [0;1]
    
    int vol_px = pow(vol_unit, 0.5) * MAXVOLPX;
    volbuf << string(vol_px, 'o');
    
    mvwprintw(musicw, 1,1, "Volume");
    mvwprintw(musicw, 1,C1,"|");
    mvwprintw(musicw, 1,C1 + 1, volbuf.str().c_str());
    mvwprintw(musicw, 1,C2, "|");
    mvwprintw(musicw, 1,C2+1, to_string(sampler.recent_maximum(1000)).c_str());
    mvwprintw(musicw, 1,C3, "|");
    
    // Threshold
    // double thr_unit = max(min(100/MAXVOL, 1.0),0.0);  //unitary threshold value [0;1]
    double thr_unit = max(min(   sampler.beat_threshold/MAXVOL  ,1.0),0.0);  //unitary threshold value [0;1]
    int thr_px = pow(thr_unit, 0.5) * MAXVOLPX;
    thrbuf << "Threshold | " << string(thr_px-1, ' ') << '|' << string(MAXVOLPX-thr_px, ' ') << " | " << (int)sampler.beat_threshold;
    mvwprintw(musicw, 2,1, "Threshold");
    mvwprintw(musicw, 2,1, thrbuf.str().c_str());
    mvwprintw(musicw, 1,80, "|");
    mvwprintw(musicw, 2,80, "|");

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

    //TODO print a gauge bar with break indicator vs break threshold 
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
    for (auto fix : fix_vec{&addr_led, &led, &laser, &front_rack, &spider, &back_rack}){
        ostringstream animbuf, outbuf;
        animbuf << ((fix->active_animation->type == leader) ? "(L) ":"(b) ") << fix->name << " " << fix->active_animation->id << " - " << fix->active_animation->description;
        
        DMX_vec raw_buf = fix->buffer();
        outbuf << "| " <<fcn::vec_to_str(raw_buf, ',');

        if (fix == &back_rack)
            line++;

        mvwprintw(outputw, line, 1, animbuf.str().data());
        mvwprintw(outputw, line, 55, outbuf.str().size()<60? outbuf.str().data() : outbuf.str().substr(0, 60).data());
        
        line++;
    }


    wrefresh(outputw);
}

void disp_animation_window(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

//initialize
    curs_set(0);
    werase(animw);
    box(animw, ACS_VLINE, ACS_HLINE);
    wattron(animw, A_BOLD);
    mvwprintw(animw, 0,1, "ANIMATOR");
    wattroff(animw, A_BOLD);

    ostringstream anim_change_buf;
    long timer =  ((long)animator.t_last_change_ms + (long)TEMPO_ANIM_CHANGE - (long)frame.t_current_ms)/1000.0;

    anim_change_buf << "Animation switch : " << (timer>0 ? timer : 0);
    mvwprintw(animw, 2, 1, anim_change_buf.str().c_str());

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
    box(generalw, ACS_VLINE, ACS_HLINE);
    wattron(generalw, A_BOLD);
    mvwprintw(generalw, 0,1, "GENERAL");
    wattroff(generalw, A_BOLD);

    ostringstream cptbuf;
    cptbuf << "Frame counter : " << frame.cpt;
    mvwprintw(generalw, 1,1, cptbuf.str().c_str());

    ostringstream timbuf;
    timbuf << "Clock : " << frame.t_current_ms/1000.0 << "s";
    mvwprintw(generalw, 1, 35, timbuf.str().c_str());

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
            mvwprintw(consolew, i, 1, fcn::num_to_str((*log).timestamp/1000.0).c_str());
            mvwprintw(consolew, i--, 1+(*log).level-1+10, (*log).message.c_str());
            if (i==0){
                break;
            }
        }
    }

    wrefresh(consolew);
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
    
    // werase(animw);
    // box(animw, ACS_VLINE, ACS_HLINE);
    // wrefresh(animw);
    // werase(outputw);
    // box(outputw, ACS_VLINE, ACS_HLINE);
    // wrefresh(outputw);

    
    
    refresh();
}
/** Displays Critical variables in real time on the console */
void display(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    
    cout << "\x1B[2J\x1B[H";// << flush;
    cout << "//// MUSIQUE /////\n";
    cout << "Volume : " << string((int)(sampler.volume/1000.0*50), '█') << '\n'; //sampler.volume << endl;
    cout << "Threshold : " << sampler.beat_threshold << '\n';
    cout << "ratio V/T : " << (float)sampler.volume/sampler.beat_threshold << '\n';
    cout << "sample Max/Min : " << sampler.deb_max << "/" << sampler.deb_min << '\n';
    
    cout << "Clip : ";
        if (sampler.clipping) cout << "███"; 
        cout << '\n';
    cout << "Beat : ";
        if  (sampler.raw_beat) cout << "████";  
        cout << '\n';
    cout << "State: " << sampler.state  << '\n';

    #ifdef FAKEMUSIC
        cout << "Next beat : " << (sampler.t_next_beat_ms - millis())/1000.0  << "s\n";
        cout << "Next break : " << (sampler.t_next_break_ms - millis())/1000.0  << "s\n";
        cout << "Next drop : " << (sampler.t_next_drop_ms - millis())/1000.0  << "s\n";
    #endif 
    
    
    cout << '\n' << "//// ANIMATOR /////" << '\n';
    cout << "Animation : " << led.active_animation->id << " -> " << led.active_animation->description << '\n';
    cout << "Flash : " << animator.flash << '\n';
    cout << "Last change " << (frame.t_current_ms - animator.t_last_change_ms)/1000 << "s\n";

    cout << "\n//// OUTPUT /////" << '\n';
    cout << "R/G/B : " << led.RGBout[R] << " / " << led.RGBout[G] << " / " << led.RGBout[B] << endl;

    cout << "\n//// GENERAL /////" << '\n';
    cout << "FPS : " << 1.0/frame.loop_duration_ms*1000.0 << "Hz\n";
    cout << "Elapsed time : " << millis()/1000.0 << " s\n";

}

