/**
 * This Module contains all the code required to :
 * - Record a music sample using MCP3008 ADC chip and the I2C bus
 * - Process the sample (FFT & custom phrase analysis)
 * - Update outputs ()
 * 
*/


/** TODO :
 * - put the MCP3008 object inside the SoundANalyzer class
 * - enumerate everything that can support it (states, variables, etc.)
 * 
*/

#include <algorithm>
#include <cmath>

#include "debug.h"
#include "music.h"
#include "constant.h"
#include "sysfcn.h"
#include <wiringPi.h>

SoundAnalyzer sampler;

void SoundAnalyzer::update(){
    this->record();
    this->process_record();

}

void SoundAnalyzer::record(){
    unsigned long next = micros();
    clip = false;

    deb_max=MCP3008_MIN, deb_min=MCP3008_MAX;
     
    for (int i=0; i<SAMPLE_SIZE; i++){
      next = next + 1000000.0/SAMPLING_FREQ;
      signal[i][REAL] = adc.read(MCP_CHAN);
      signal[i][IMAG] = 0;
      if (signal[i][REAL] > (MCP3008_MAX-10) || signal[i][REAL] < (MCP3008_MIN+10))
        clip = true;
      if (signal[i][REAL] > deb_max)
        deb_max = signal[i][REAL];
      if (signal[i][REAL] < deb_min)
        deb_min = signal[i][REAL];

      while(micros() < next){}    // wait until the end of the samplign period
    }
}

// rewrite using FFTW instead of ArduinoFFT
void SoundAnalyzer::process_record(){
    this->_remove_DC_value();
    //FFT.Windowing(value_r, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    this->_compute_FFT();
    //FFT.ComplexToMagnitude(record_real, record_imag, SAMPLE_SIZE);  --> incuded into computeFFT
      
    // extract current volume (measure in FFT frequency band "FREQ_BAND")
    volume = spectrum[FREQ_BAND][AMPL]*2/SAMPLE_SIZE;
    
    // save the current volume sample in moving memory
    // when the memory is full, overwrite the first records.
    
    // new version
    v_memory.push_back(volume);
    i_record ++;
    if(v_memory.size() > VOL_BUFF_SIZE){
        if (!tab_is_full){
            tab_is_full = true;
        } 
        v_memory.erase(v_memory.begin());
    } // new version

    // check for raw_beat 
    // Compare current level to threshold and control LED 
    if (volume >= beat_threshold){
    if (!raw_beat){
        new_beat = true;
        t_last_new_beat = millis();
    }
    else{
        new_beat = false;
    }
    
    raw_beat = true;
    t_last_beat = millis();
    }
    else{
    raw_beat = false;
    filtered_beat = false;
    new_beat = false;
    }

    // activate phrase analyis enable flag every 32 samples (VOL_BUFF_SIZE/4) 
    if (tab_is_full && (i_record%(VOL_BUFF_SIZE/4) == 0))
        enable_analysis = true;
    else
        enable_analysis = false;

    // if phrase analysis enable flag is TRUE, analyze & compute statistics
    if (enable_analysis){
        this->_sort_memory();
        
        //_copy_memory();      // copy v_memory
        //KickSort<int>::quickSort(v_memory_sorted, VOL_BUFF_SIZE);  // sort volume record by value (ascending) for statistical analysis
        
        this->_compute_stats();    // compute the statistics
      }

    // in any case, update system state
    this->_update_state();
    this->_update_beat_threshold();
}

void SoundAnalyzer::_update_state(){
    // update system state 
    switch (state){     
        // If Beat Tracking
        case BEAT:
            if (enable_analysis){
                
                // If volume drops below threshold, go to BREAK
                if (v_95 < THD_toBK){
                  state = BREAK;
                }

                // If beat signal is weak 
                else if (ratio_95_q1 < THD_BTtoBS){
                BS_cpt += 1;
                if (BS_cpt == 4){
                    state = BAD_SIGNAL;
                    BS_cpt = 0;
                }
                }
                else{BS_cpt=0;}
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
            if (enable_analysis){
                if (v_95 < THD_toBK){
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
    if (enable_analysis == 1 && state != 2){
          beat_threshold = v_XX*(float)1/10 + beat_threshold*(float)9/10;
        }
}

void SoundAnalyzer::_copy_memory(){
    for (int i=0;i<VOL_BUFF_SIZE;i++)
        v_memory_sorted[i] = v_memory[i];
}

void SoundAnalyzer::_compute_stats(){
  unsigned long sum=0;
  for (int i=0; i<VOL_BUFF_SIZE; i++){
    sum = sum + v_memory_sorted[i];
  }
  v_mean = sum/VOL_BUFF_SIZE;
  
  v_max = v_memory_sorted[VOL_BUFF_SIZE-1];
  v_quarter[0] = v_memory_sorted[VOL_BUFF_SIZE/4];
  v_quarter[1] = v_memory_sorted[VOL_BUFF_SIZE/2];
  v_quarter[2] = v_memory_sorted[3*VOL_BUFF_SIZE/4];
  v_95 = v_memory_sorted[95*VOL_BUFF_SIZE/100];
  
  v_XX = v_memory_sorted[90*VOL_BUFF_SIZE/100];
  
  if (v_quarter[0]>0){ratio_95_q1 = (float)v_95/v_quarter[0];}
  else {ratio_95_q1 = 1;}
  
  if (v_quarter[1]>0){ratio_95_q2 = (float)v_95/v_quarter[1];}
  else {ratio_95_q2 = 1;}
  
  if (v_quarter[2]>0){ratio_95_q3 = (float)v_95/v_quarter[2];}
  else {ratio_95_q3 = 1;}

}

void SoundAnalyzer::_remove_DC_value(){
    double sum = 0.0;
    for (int i=0; i<SAMPLE_SIZE; i++){
        sum += signal[i][REAL];
    }
    double mean = sum/SAMPLE_SIZE;
    for (int i=0; i<SAMPLE_SIZE; i++){
        signal[i][REAL] -= mean;
    }
}

void SoundAnalyzer::_compute_FFT(){
  // Compute FFT
  my_plan = fftw_plan_dft_1d(SAMPLE_SIZE, signal, fft_out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(my_plan);

  // Reshape results 
  for (int i=0; i<SAMPLE_SIZE; i++){
      spectrum[i][FREQ] = i * SAMPLING_FREQ/SAMPLE_SIZE;
      spectrum[i][AMPL] = (pow(fft_out[i][REAL], 2) + pow(fft_out[i][IMAG],2)) * 7E-5; // compute magnitude + normalize (empirical)
  }  
}

void SoundAnalyzer::init(){
  // initializa connection with MCP3008 ADC
  adc.connect();

  // allocate memory fot the signal & fft out storage structures (arrays of doubles)
  signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*SAMPLE_SIZE);
  fft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*SAMPLE_SIZE);
}

void SoundAnalyzer::_sort_memory(){
  v_memory_sorted.assign(v_memory.begin(), v_memory.end());
  std::sort(v_memory_sorted.begin(), v_memory_sorted.end());
}

#ifdef FAKEMUSIC

#define BPM 130          // BPM
#define BREAKDuration 8  // beats
#define DROPDuration  16 // beats

const int beat_duration_ms = 60000/BPM;
const int break_duration_ms = BREAKDuration * beat_duration_ms;
const int drop_duration_ms = DROPDuration * beat_duration_ms;


void SoundAnalyzer::fake_analysis(unsigned long t){
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

    // delay(30);

}

#endif // FAKEMUSIC

/* TODO BETTER
- wrap the FFT & read process to work with VECTORS !!!
-
*/
