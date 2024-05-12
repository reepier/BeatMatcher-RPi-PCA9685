#pragma once
#include <string>
#include <platform.h>

#include "commonTypes.h"

// -- CONFIG ------------------------------------------------------------
#define FRATE   30          //Hz program main frame rate

// runtime flags for main functions -------------------------------------
extern bool b_BALISE;       //TRUE: console displays balise (without curses) 
extern bool b_NO_MUSIC;    //TRUE: music input & processing ; FALSE: music signal emulation 
extern bool b_NO_LED;      //TRUE: sends PCA9685 commands ; FALSE: ignores PCA9685 commands 
extern bool b_CURSES;       //TRUE : use curses HMI ; FALSE : use simple console output

extern bool b_test;
extern std::vector<std::string> vec_anim_id;


// Music sampler
    #define SAMPLE_SIZE 128      // record length (number of individual samples)
    #define SAMPLING_FREQ 8000     // sampling frequency
    #define FREQ_BAND 2     // frequency band used to evaluate volume (low value for bass / high value for treble)

    #define VOL_BUFF_SIZE 128   // size of the volume buffer

    // state transition parameters
    #define THD_toBK 30             // Volume Threshold to go from state X to BREAK  mode
    #define THD_BTtoBS 3            // Threshold to go from BEAT TRACKING to BAD SIGNAL mode
    #define THD_BStoBT 5            // Threshold to go from  BAD SIGNAL to BEAT TRACKING mode
    #define TEMPO_BEAT_BREAK 1000   // duration after which state goes FROM to BREAK when no BEAT is detected  

// Music Emulator
#define BPM 120          // BPM
#define BREAKDuration 4  // beats
#define DROPDuration  8 // beats

// -- CONFIG ------------------------------------------------------------
#define     MAX_CONT_FLASH      120000          // 120000
#define     TEMPO_ANIM_CHANGE   60000          // 240000
#define     MASTERDIMMER        1.0             //fraction --> must be decimal (literal float) !!!

#define     SPIDER_ANI_DURA     600000 
#define     STROBE_ANI_DURA     45000

#define      PAL_LIFESPAN_BICO  4
#define      PAL_LIFESPAN_MONO  2

#define     SPOTRACK_ANI1_BkG_INTENSITY_LOW   40
#define     SPOTRACK_ANI1_BkG_INTENSITY_HIGH  100

