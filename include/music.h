#pragma once


#include <fftw3.h>
#include <vector>
#include <wiringPi.h>
// #include "debug.h"

#ifndef LINUX_PC //if compiling on raspberrypi
    #include "MCP3008/MCP3008.h"
#endif




// MCP3008
#define MCP3008_MAX 1023
#define MCP3008_MIN 0
#define MCP_CHAN 5
#define CLIP_MARGIN 80

// thresholds
#define THD_toBK 30     // Volume Threshold to go from state X to BREAK  mode
#define THD_BTtoBS 3    // Threshold to go from BEAT TRACKING to BAD SIGNAL mode
#define THD_BStoBT 5    // Threshold to go from  BAD SIGNAL to BEAT TRACKING mode

// FFTW
#define REAL 0
#define IMAG 1
#define FREQ 0
#define AMPL 1

enum states{
    BEAT        = 1,    // volume is high and beat is clear
    BREAK       = 2,    // volume is low (indicates a break)
    BAD_SIGNAL  = 3     // volume is high but the beat is not perceptible
};

class SoundAnalyzer{

    #ifndef LINUX_PC //if compiling on raspberrypi
        MCP3008Lib::MCP3008 adc;    // MCP3008 object
    #endif

    // FFTW lib structures
    public : fftw_complex *fft_signal;
    private : fftw_complex *fft_out;
    private : fftw_plan fft_plan;

    // FFT results storage structure
    public  : float sample_spectrum[BUF_LENGTH][2];    // stores AMPL x FREQ array;

    public :    bool clipping; // true if _record() detects ADC saturation
    public :    int volume;
    public :    double lagging_volume;
    
    public :    std::vector<int> v_memory;          // time serie of the measured volume
    public :    std::vector<int> v_memory_sorted;   // sorted serie of the measured volume

    // phrase analysis variables
    private :   int cpt = 0;                        // number of samples recorded
    
    // Beat tracking variables
    public :    float beat_threshold = 60;
    public :    bool raw_beat=false, new_beat=false, filtered_beat=false;
    public :    unsigned long t_last_beat = 0;         // Stores timestamp of the last raw_beat=true event
    public :    unsigned long t_last_new_beat = 0;
    public :    unsigned long t_beat_tracking_start = millis();

    // state machine
    private :   int BS_buff = 0, BT_buff = 0;     // counters used to filter out transents in states estimation
    public :    states state = BEAT, previous_state = BEAT;
    public :    bool state_changed = false;    

    // Main functions (entry points)
    public :    void init();
    public :    void update();


    // statistics computation
    public :    float volume_percentile(int);
    public :    float volume_ratio(int, int);
    public :    int recent_maximum(int);

    // hidden functions (called by the main functions)
    // private :   void _copy_memory();
    // private :   void _compute_stats();
    #ifndef LINUX_PC //if compiling on raspberrypi
        public :    void _record();
    #endif          
    public :    void _process_record();
    public:     void _update_beats();
    private :   void _update_beat_threshold();
    private :   void _update_state();
    private :   void _remove_DC_value();
    private :   void _compute_FFT();
    private :   void _sort_memory();
    private :   bool _memory_overflow();
    private :   bool _memory_full();
    private :   bool _condition_for_analyis();
    private :   void _filter_volume();

    private :   void _switch_to_state(states);

    // fake analysis function (for animation developpement purpose)
    public :    void fake_analysis(); 

    public:     void process_record_fake();
    private :   void _update_beat_threshold_fake();
    public:     void record_sample_fake();

    // debug intermediary variables
    public :    int deb_max, deb_min;
    
    //fake beat
    unsigned long t_next_break_ms, t_next_drop_ms, t_next_beat_ms;
    
};

extern SoundAnalyzer sampler;