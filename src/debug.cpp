#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <cmath>

#include "debug.h"
#include "animator.h"
#include "music.h"
#include "LED.h"

using namespace std;

extern SoundAnalyzer sampler;
extern AnimationManager animator;
extern LoopControler frame;

WINDOW *musicw;
WINDOW *animw;
WINDOW *outputw;
WINDOW *generalw;

void init_display(){
    initscr();
    noecho();
    curs_set(0);
    musicw = newwin(10, 100, 0,0);
    animw = newwin(3,100,10,0);
    outputw = newwin(3,100,20,0);
    generalw = newwin(3,100,30,0);
}


void display_curse(){
    ostringstream volbuf, thrbuf, maxminbuf, clipbuf, beatbuf, statebuf ,nbt, nbk, ndrop;

    volbuf << "Volume    : " << string((int)( pow(sampler.volume/200.0, 0.33)*60    ), 'o');
    thrbuf << "Threshold : " << string((int)( pow(sampler.recent_maximum(1000)/200.0, 0.33)*60 -1 ), ' ') << '|';
    maxminbuf << "Max/Min : " << sampler.deb_max << "/" << sampler.deb_min;
    clipbuf << (sampler.clipping?"CLIP":"");
    beatbuf << (sampler.raw_beat?"BEAT":"");
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
    #ifdef FAKEMUSIC
        nbt     << "Nxt beat : " << (sampler.t_next_beat_ms - millis())/1000.0;
        nbk     << "Nxt break : " << (sampler.t_next_break_ms - millis())/1000.0  << "s\n";
        ndrop   << "Nxt drop : " << (sampler.t_next_drop_ms - millis())/1000.0  << "s\n";
    #endif
    

    
    werase(musicw);
    box(musicw, ACS_VLINE, ACS_HLINE);
    mvwprintw(musicw, 0,1, "MUSIC");

    mvwprintw(musicw, 1,1, volbuf.str().c_str());
    mvwprintw(musicw, 2,1, thrbuf.str().c_str());
    mvwprintw(musicw, 3,1, maxminbuf.str().c_str());
    mvwprintw(musicw, 4,1, beatbuf.str().c_str());
    mvwprintw(musicw, 4,10, clipbuf.str().c_str());
    mvwprintw(musicw, 5,1, statebuf.str().c_str());
    #ifdef FAKEMUSIC
        mvwprintw(musicw, 6,1, nbt.str().c_str());
        mvwprintw(musicw, 6,21, nbk.str().c_str());
        mvwprintw(musicw, 6,41, ndrop.str().c_str());
    #endif
    wrefresh(musicw);

    

    werase(animw);
    box(animw, ACS_VLINE, ACS_HLINE);
    wrefresh(animw);
    werase(outputw);
    box(outputw, ACS_VLINE, ACS_HLINE);
    wrefresh(outputw);
    werase(generalw);
    box(generalw, ACS_VLINE, ACS_HLINE);
    wrefresh(generalw);
    
    refresh();
}
/** Displays Critical variables in real time on the console */
void display(){
    
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
    cout << "Animation : " << animator.animation_i << " -> " << led.active_animation->description << '\n';
    cout << "Flash : " << animator.flash << '\n';
    cout << "Last change " << (frame.t_current_ms - animator.t_last_change_ms)/1000 << "s\n";

    cout << "\n//// OUTPUT /////" << '\n';
    cout << "R/G/B : " << led.RGB[R] << " / " << led.RGB[G] << " / " << led.RGB[B] << endl;

    cout << "\n//// GENERAL /////" << '\n';
    cout << "FPS : " << 1.0/frame.loop_duration_ms*1000.0 << "Hz\n";
    cout << "Elapsed time : " << millis()/1000.0 << " s\n";

}