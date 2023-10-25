/**
 * This Module contains all the code required to :
 * - Record a music sample using MCP3008 ADC chip and the I2C bus
 * - Process the sample (FFT & custom phrase analysis)
 * - Update outputs ()
 * 
*/

#include <algorithm>
#include <cmath>

#include "config.h"
#include "debug.h"
#include "music.h"
#include "sysfcn.h"
#include <wiringPi.h>

SoundAnalyzer sampler;

void SoundAnalyzer::init(){
    // initializa connection with MCP3008 ADC
    #ifndef LINUX_PC
        adc.connect();
    #endif
    // allocate memory fot the fft_signal & fft out storage structures (arrays of doubles)
    fft_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*SAMPLE_SIZE);
    fft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*SAMPLE_SIZE);
}

void SoundAnalyzer::update(){
    time_t t = frame.t_current_ms;
    #ifndef LINUX_PC
    if(!b_NO_MUSIC){
        this->_record();
        this->_process_record();
    }else{
        sampler.process_record_fake();
    }
    #else
        sampler.process_record_fake();
    #endif // LINUX_PC
    
    this->_update_beats();
    this->_update_state();
    this->_update_beat_threshold();
}

#ifndef LINUX_PC
void SoundAnalyzer::_record(){
    unsigned long next_us = micros();
    clipping = false;
    deb_max=MCP3008_MIN, deb_min=MCP3008_MAX;
     
    for (int i=0; i<SAMPLE_SIZE; i++){
      next_us = next_us + 1000000.0/SAMPLING_FREQ;
      fft_signal[i][REAL] = adc.read(MCP_CHAN);
      fft_signal[i][IMAG] = 0;
      if (fft_signal[i][REAL] > (MCP3008_MAX-CLIP_MARGIN) || fft_signal[i][REAL] < (MCP3008_MIN+CLIP_MARGIN))
        clipping = true;
      if (fft_signal[i][REAL] > deb_max)
        deb_max = fft_signal[i][REAL];
      if (fft_signal[i][REAL] < deb_min)
        deb_min = fft_signal[i][REAL];

      while(micros() < next_us){}    // wait until the end of the samplign period
    }
}
#endif

void SoundAnalyzer::_process_record(){
    _remove_DC_value();
    _compute_FFT();
      
    // extract current volume (measure in FFT frequency band "FREQ_BAND")
    volume = sample_spectrum[FREQ_BAND][AMPL]*2/SAMPLE_SIZE;
    
    // save the current volume sample in moving memory
    // when the memory is full, overwrite the first records
    v_memory.push_back(volume);
    cpt ++;
    if(_memory_overflow()) v_memory.erase(v_memory.begin());    //when max size is reached, erase oldest values

    if (_condition_for_analyis()){
        this->_sort_memory();  
    }
}

void SoundAnalyzer::_update_beats(){
    // check for raw_beat
    // Compare current level to threshold and control LED
    if (volume >= beat_threshold){
        if (!raw_beat){
            new_beat = true;
            t_last_new_beat = frame.t_current_ms;
        }
        else{
            new_beat = false;
        }
        
        raw_beat = true;
        t_last_beat = frame.t_current_ms;
    }
    else{
        raw_beat = false;
        filtered_beat = false;
        new_beat = false;
    }
}

    // activate phrase analyis enable flag every 32 samples (VOL_BUFF_SIZE/4) 

    // if phrase analysis enable flag is TRUE, analyze & compute statistics

void SoundAnalyzer::_update_state(){
    // update system state 
    switch (state){     
        // If Beat Tracking
        case BEAT:
            if (_condition_for_analyis()){
                
                // If volume drops below threshold, go to BREAK
                if (volume_percentile(95) < THD_toBK){
                  state = BREAK;
                }

                // If no beat is discernible 
                else if (volume_ratio(95, 25) < THD_BTtoBS){
                    BS_buff += 1;
                    if (BS_buff == 4){
                        _switch_to_state(BAD_SIGNAL);
                    }
                }

                else{BS_buff=0;}
            }
            break;

        // If Break
        case BREAK:
            if(raw_beat){
                state = BEAT;
                t_beat_tracking_start = millis();
            }
        break;

        // If Beat Lost
        case BAD_SIGNAL:
            if (_condition_for_analyis()){
                if (volume_percentile(95) < THD_toBK){
                    state = BREAK;
                }
            }
        break;

        default:
        break;
        }

        // update state change flag
        if (state != previous_state){
            state_changed = true;
            previous_state = state;
        }
        else{
            state_changed = false;
        }
}

void SoundAnalyzer::_update_beat_threshold(){
    if (_condition_for_analyis() && state != BREAK){
          beat_threshold = volume_percentile(90) * (float)1/10 + beat_threshold*(float)9/10;
        }
}

/**Function that returns the volume value for the given percentile
 * @param percentile : integer from 0-100 (%)
 * @return 
*/
float SoundAnalyzer::volume_percentile(int percentile){
    if (percentile > 100) percentile = 100;
    else if (percentile < 0) percentile = 0;

    int i =  percentile/100.0 * (VOL_BUFF_SIZE-1);

    return (float)v_memory_sorted[i];
}

/**Function that computes the ratio between 2 volume samples chosen from their percentile*/
float SoundAnalyzer::volume_ratio(int num_percentile, int denom_percentile){
    return volume_percentile(num_percentile) / volume_percentile(denom_percentile);
}
/**Funciton that extract the maximum volume reached within the last <period> ms*/
int SoundAnalyzer::recent_maximum(int period){
    static const float max = VOL_BUFF_SIZE*1000.0/FRATE;    // memory is finit in size
    static const float min = 0;                             // cannot accept negative duration
    if (period > max ) period = max;                        
    else if (period < min) period = min;

    int i_min = v_memory.size() - period / FRATE * 1000;    
    if (i_min < 0) i_min = 0;                                           // cannot hav negative indexes
    else if (i_min > (v_memory.size()-1)) i_min = v_memory.size()-1;    // cannot read past the last vector element

    int vmax = 0;
    for (int i=v_memory.size()-1; i>= i_min; i--){
        if (v_memory[i] > vmax) vmax = v_memory[i];
    }
    return vmax;
}

void SoundAnalyzer::_remove_DC_value(){
    double sum = 0.0;
    for (int i=0; i<SAMPLE_SIZE; i++){
        sum += fft_signal[i][REAL];
    }
    double mean = sum/SAMPLE_SIZE;
    for (int i=0; i<SAMPLE_SIZE; i++){
        fft_signal[i][REAL] -= mean;
    }
}

void SoundAnalyzer::_compute_FFT(){
  // Compute FFT
  fft_plan = fftw_plan_dft_1d(SAMPLE_SIZE, fft_signal, fft_out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(fft_plan);

  // Reshape results 
  for (int i=0; i<SAMPLE_SIZE; i++){
      sample_spectrum[i][FREQ] = i * SAMPLING_FREQ/SAMPLE_SIZE;
      sample_spectrum[i][AMPL] = (pow(fft_out[i][REAL], 2) + pow(fft_out[i][IMAG],2)) * 7E-5; // compute magnitude + normalize (empirical)
  }  
}

void SoundAnalyzer::_sort_memory(){
  v_memory_sorted.assign(v_memory.begin(), v_memory.end());
  std::sort(v_memory_sorted.begin(), v_memory_sorted.end());
}


// true if number of volume sample stored exceed (>) MAX value
bool SoundAnalyzer::_memory_overflow(){
    return (v_memory.size() > VOL_BUFF_SIZE);
}
// true if number of volume sample stored equals (=) MAX value
bool SoundAnalyzer::_memory_full(){
    return (v_memory.size() == VOL_BUFF_SIZE);
}
bool SoundAnalyzer::_condition_for_analyis(){
    return (_memory_full() && (cpt%(VOL_BUFF_SIZE/4) == 0));
}

void SoundAnalyzer::_switch_to_state(states s){
    switch(s){
        case BEAT:
            state = BEAT;
            t_beat_tracking_start = millis();
        break;

        case BREAK:
            state = BREAK;
        break;

        case BAD_SIGNAL:
            state = BAD_SIGNAL;
            BS_buff = 0;    // reset buffer
        break;

        default:
        break; 
    }
}


/**---------------------------------------------------------------
 * FAKE FUNCTIONS to emulate the music input
   ---------------------------------------------------------------*/




const int beat_duration_ms = 60000/BPM;
const int break_duration_ms = BREAKDuration * beat_duration_ms;
const int drop_duration_ms = DROPDuration * beat_duration_ms;

const int min_volume = 20, max_volume = 400;

inline int fake_volume1(){
    return min_volume + (max_volume-min_volume)*pow(((sin(2*M_PI*millis()/beat_duration_ms)+1)/2), 5);
}
inline int fake_volume2(){
    return min_volume + 0.25*min_volume*sin(2*M_PI*millis()/1000);
}

void SoundAnalyzer::process_record_fake(){
    time_t t = frame.t_current_ms;
    // initialize
    static bool init = true;
    if (init){
        t_beat_tracking_start = t;
        t_next_drop_ms = t  + drop_duration_ms + break_duration_ms;
        t_next_beat_ms = t;
        t_next_break_ms = t + drop_duration_ms;
        init = false;
    }

    static states pseudo_state = BEAT, previous_pseudo_state = pseudo_state;
    switch(pseudo_state){
        case BEAT:
            if (t >= t_next_break_ms){
                t_next_break_ms += (break_duration_ms + drop_duration_ms);
                previous_pseudo_state = pseudo_state;
                pseudo_state = BREAK; 
            }
        break;
        case BREAK:
            if (t >= t_next_drop_ms){
                t_next_drop_ms += (drop_duration_ms + break_duration_ms);
                previous_pseudo_state = pseudo_state;
                pseudo_state = BEAT;
            }
        break;
        default:
        break;
    }
    // volume
    switch(pseudo_state){
        case BEAT:
            volume = fake_volume1();
        break;
        case BREAK:
            volume = fake_volume2();
        break;
    }

    // v_memory
    v_memory.push_back(volume);
    cpt ++;
    if(_memory_overflow()) v_memory.erase(v_memory.begin());    //when max size is reached, erase oldest values

    if (_condition_for_analyis()){
        this->_sort_memory();  
    }
}

/** DEPRECATED */
void SoundAnalyzer::fake_analysis(){
    time_t t = frame.t_current_ms;
    // initialize
    static bool init = true;
    if (init){
        t_beat_tracking_start = t;
        t_next_drop_ms = t  + drop_duration_ms + break_duration_ms;
        t_next_beat_ms = t;
        t_next_break_ms = t + drop_duration_ms;
        init = false;
    }
    
    // update state machine
    switch (state){
        case BEAT:
            if (t >= t_next_break_ms){
                t_next_break_ms += (break_duration_ms + drop_duration_ms);
                previous_state = state;
                state = BREAK; 
                state_changed = true;
            }
            else{
                state_changed = false;
            }
            break;
        case BREAK:
            if (t >= t_next_drop_ms){
                t_next_drop_ms += (drop_duration_ms + break_duration_ms);

                state_changed = true;
                previous_state = state;
                state = BEAT;
                t_beat_tracking_start = t;
            }
            else{
                state_changed = false;
            }
            break;
        default:
            break;
    }

    // generate fake raw_beat
    if (t >= t_next_beat_ms){
        raw_beat = true;
        new_beat = true;
        t_last_beat = t;
        t_last_new_beat = t;

        t_next_beat_ms += beat_duration_ms;
    }
    else{
        raw_beat = false;
        new_beat = false;
    }
}

/* TODO BETTER
- wrap the FFT & read process to work with VECTORS !!!
*/
