#pragma once
#include <string>
#include <platform.h>

#include "commonTypes.h"

// -- CONFIG ------------------------------------------------------------
#define FRATE   40          //Hz program main frame rate

// runtime flags for main functions -------------------------------------
extern bool b_BALISE;       //TRUE: console displays balise (without curses) 
extern bool b_NO_MUSIC;    //TRUE: music input & processing ; FALSE: music signal emulation 
extern bool b_NO_LED;      //TRUE: sends PCA9685 commands ; FALSE: ignores PCA9685 commands 
extern bool b_CURSES;       //TRUE : use curses HMI ; FALSE : use simple console output
extern bool b_EXT_CONTROL;

extern bool b_ANI_TEST;
extern std::vector<std::string> cli_anim_id;


// Music sampler
    #define BUF_LENGTH 128       // audio buffer length (number of individual samples)
    #define SAMPLING_FREQ 8000   // sampling frequency
    #define FREQ_BAND 2          // frequency band used to evaluate volume (low value for bass / high value for treble) //TODO calibrate

    #define VOL_BUFF_SIZE 128   // size of the volume buffer

    // state transition parameters
    #define THD_toBK 30             // Volume Threshold to go from state X to BREAK  mode
    #define THD_BTtoBS 3            // Threshold to go from BEAT TRACKING to BAD SIGNAL mode
    #define THD_BStoBT 5            // Threshold to go from  BAD SIGNAL to BEAT TRACKING mode
    #define TEMPO_BEAT_BREAK 1600   // duration after which state goes FROM to BREAK when no BEAT is detected  
    #define TEMPO_SUSTAINED_BREAK 4000  //[ms] Duration after which BREAK becomes SUSTAINED BREAK

// Music Emulator
#define BPM 100          // BPM
#define BREAKDuration 16  // beats
#define DROPDuration  16 // beats

// -- CONFIG ------------------------------------------------------------
#define     MAX_CONT_FLASH      120000          // 120000 
#define     TEMPO_ANIM_CHANGE   5000          // 240000
#define     MASTERDIMMER        1.0             //fraction --> must be decimal (literal float) !!!

#define     SPIDER_ANI_DURA     600000 
#define     STROBE_ANI_DURA     100000

#define      PAL_LIFESPAN_BICO  5
#define      PAL_LIFESPAN_MONO  3

#define     SPOTRACK_ANI1_BkG_INTENSITY_LOW   150
#define     SPOTRACK_ANI1_BkG_INTENSITY_HIGH  100

#define     ADDRLED_ANI4_BkG_INTENSITY_LOW   15
#define     DDRLED_ANI4_BkG_INTENSITY_HIGH  100

#define     SHOW_INTENSITY 0        // ranges from 1 to 3 (0 for all)

// -- CONFIG MAXIMUM --------------------------------------------------
#define     WAREH_TEMPO_ANI         5*60000      // average animation duration in the warehouse
#define     WAREH_TEMPO_PALETTE     20*60000     // average palette duration in the warehouse
#define     DANCEFL_TEMPO_ANI       60000      // average animation duration in the dancefloor
#define     DANCEFL_TEMPO_PALETTE   5000 //10*60000     // average palette duration in the dancefloor

#define     MAX_FASH_ANI
// External Controler SETTING
// #define SR1_DIMMER      0
// #define SR1_ANI_TYPE    1
// #define SR1_C1          2
// #define SR1_C2          3

// #define SR2_DIMMER      4
// #define SR2_ANI_TYPE    5
// #define SR2_C1          6
// #define SR2_C2          7

// #define WS_DIMMER      8
// #define WS_ANI_TYPE    9
// #define WS_ANI_UNIT    10
// #define WS_C1          11
// #define WS_C2          12
// #define WS_S1          13
// #define WS_S2          14
// #define WS_DENS        15
