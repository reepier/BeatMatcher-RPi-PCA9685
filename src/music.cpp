/**
 * This Module contains all the code required to :
 * - Record a music sample using MCP3008 ADC chip and the I2C bus
 * - Process the sample (FFT & custom phrase analysis)
 * - Update outputs ()
 * 
*/

#include <algorithm>
#include <cmath>
#include <climits>

#include "rtaudio/RtAudio.h"

#include "config.h"
#include "debug.h"
#include "music.h"
#include "sysfcn.h"
#include <wiringPi.h>


SoundAnalyzer sampler;

#ifdef LINUX_PC // RT Audio -----------------------------------------------------------------
typedef double SAMPLE_TYPE;
#define FORMAT RTAUDIO_FLOAT64

RtAudio adc;

/** This function is called automatically every time rtaudio records a new sample buffer (the frequency depends on sample 
 * size and sampling frequency). It is asynchronous with the rest of the program that runs on a constant 40Hz "main loop". if the sampling
 * runs at a higher rate, some samples will get lost in between executions of the "main loop" but every time the "main loop" executes, it
 * will access the newest sample buffer. 
 */
int rtaudio_callback_fcn(void * /*outputBuffer*/, void *inputBuffer, unsigned int nBufferFrames,
                        double /*streamTime*/, RtAudioStreamStatus /*status*/, void * /*data*/){
    
    // recast rtaudio std arguments :
    SAMPLE_TYPE *iBuffer = (SAMPLE_TYPE *) inputBuffer;

    
    // extract the buffer & format it like the old one (double from 0 to 1023)
    // store the N newest sample in a data structure accessible to the rest of the program
    for (int i=0; i<BUF_LENGTH; i++){
        double sample_i =  map(iBuffer[i], -1.0, 1.0, 0.0, 1023.0); // use only 1 channel --> TODO use averaged Left & Right
        sampler.fft_signal[i][REAL] = sample_i;
        sampler.fft_signal[i][IMAG] = 0;
    }

    //TODO mix together high sampling frequency with longer total buffer : each callback appends a small "subbuffer"
    //  to the head of the total buffer (while removing a tail of the same length). Gaol is to have both a fast refresh rate + a better low frequency resolution (longer total sample)
    // the higher bass resolution will comm with an induced delay though... to be tried & tetsed
    
    //TODO execute FFT here ??
    sampler._process_record();  //else use analog recording

}
#endif


/**
 * This function initializes the music-input module of this project :
 * - allocates memory for the music samples
 * - connects to the external ADCs (rasperrypi configuration)
 * - connects to the intenal audio interface (PC configuration) & set it up
 * - adapts its behavior to the platform & hardware configuration
 * */
void SoundAnalyzer::init(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

     // allocate memory fot the fft_signal & fft out storage structures (arrays of doubles)
    fft_signal = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*BUF_LENGTH);
    fft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*BUF_LENGTH);
    
    // initializa connection with MCP3008 ADC
    #ifndef LINUX_PC
        adc.connect();
    // initialise connection to Audio interface on PC (RtAudio Library)
    #else
    if (b_NO_MUSIC == false){
        std::vector<unsigned int> deviceIds = adc.getDeviceIds();
        if ( deviceIds.size() < 1 ) {
            
        }
        
        unsigned int channels = 2, fs = SAMPLING_FREQ, bufferFrames = BUF_LENGTH, device = 0, offset = 0;
        RtAudio::StreamParameters iParams;
        iParams.nChannels = 2;
        iParams.firstChannel = 0;
        iParams.deviceId = adc.getDefaultInputDevice(); // default device is used //TODO implemnt choixe if required

        // adc.setErrorCallback( define a callback function to handle error ) // TODO integrate errors to the program's log console

        //open Stream
        if ( adc.openStream( NULL, &iParams, RTAUDIO_FLOAT64, fs, &bufferFrames, &rtaudio_callback_fcn/*, (void *)&data*/) ){
            balise("\nRtAudio : Failed to open Stream!\n");
            exit( 1 );
        }
        balise("Rt Audio Stream open!");
        // check stream is open
        if ( adc.isStreamOpen() == false ){
            balise("RtAudio : Stream not open!");
            exit( 1 );
        }
        balise("Rt Audio Stream confirmed open !");

        //Start Stream
        if ( adc.startStream() ){
            balise("RtAudio : Failed to start Stream!");
            exit(1);
        }
        balise("Rt Audio Stream started!");
    }
    #endif
}

/**
 * This function is the sequencer all the major subtasks of real time sound-analysis 
 */
void SoundAnalyzer::update(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    time_t t = frame.t_current_ms;
    #ifndef LINUX_PC
    if(!b_NO_MUSIC){
        this->_record();
        this->_process_record();
    }else{
        sampler.process_record_fake();
    }
    #else
        if(b_NO_MUSIC){
            sampler.process_record_fake(); // If NOMUSIC flag is true use fake music signal
        }else{
        }
    #endif // LINUX_PC
    this->_filter_volume();

    this->_update_beats();
    this->_update_state();
    this->_update_beat_threshold();
}

#ifndef LINUX_PC
void SoundAnalyzer::_record(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    if (micros() > (ULLONG_MAX - SAMPLE_SIZE*1000000/SAMPLING_FREQ)){ // if micros() is about to overflow
        log(4, micros(), " ",ULLONG_MAX," ", SAMPLE_SIZE*1000000/SAMPLING_FREQ);
        delayMicroseconds(SAMPLE_SIZE*1000000/SAMPLING_FREQ*2); // wait for the overflow to complete & resume
    }

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

/**
 * This function : 
 * - Removes DC component
 * - Computes FFT
 * - Extract the current volume for the desired frequency band
 * - Update volume history 
 */
void SoundAnalyzer::_process_record(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    _remove_DC_value();
    _compute_FFT();
      
    // extract current volume (measure in FFT frequency band "FREQ_BAND") and
    volume = sample_spectrum[FREQ_BAND][AMPL]*2/BUF_LENGTH;
    
    // save the current volume sample in moving memory
    // when the memory is full, overwrite the first records
    v_memory.push_back(volume);
    cpt ++;
    if(_memory_overflow()) v_memory.erase(v_memory.begin());    //when max size is reached, erase oldest values

    if (_condition_for_analyis()){
        this->_sort_memory();  
    }
}

/**
 * This function :
 * - uses the updated & processed audio record to detect Beats
 */
void SoundAnalyzer::_update_beats(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

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

/** 
 * This function detects phrasing (Beat, Break...)
*/
void SoundAnalyzer::_update_state(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    // update system state 
    previous_state = state; //save current state as "previous" value
    switch (state){     
        // If Beat Tracking
        case BEAT:
            if (_condition_for_analyis()){ //TODO : update the analysis at every frame 
                
                // switch to break when last beat since 1000 ms
                if (frame.t_current_ms - t_last_beat > TEMPO_BEAT_BREAK){
                  _switch_to_state(BREAK);
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
                _switch_to_state(BEAT);
            }else if(frame.t_current_ms - t_last_state_change > TEMPO_SUSTAINED_BREAK){
                _switch_to_state(SUSTAINED_BREAK);
            }
        break;

        case SUSTAINED_BREAK:
            if(raw_beat){
                _switch_to_state(BEAT);
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

        // update state change flag & previous state
        if (state != previous_state){
            state_changed = true;
        }
        else{
            state_changed = false;
        }
}

/**
 * This function changes the beat threshold based on current averaged volume in order
 * to adapt to a changing volume or frequency structure 
 */
void SoundAnalyzer::_update_beat_threshold(){
    log(4, __FILE__, " ",__LINE__, " ", __func__);

    if (_condition_for_analyis() && state == BEAT){
          beat_threshold = volume_percentile(90) * (float)1/10 + beat_threshold*(float)9/10;
        }
}

/**
 * This funciton derivates a filtered volume (introduces a lag).
 * The filter is asymetrical, when volume goes up, the filter is more responsive than when volue goes down. 
 * It is designed to reduce the random noise in volume signal & create a decaying effect after each beat
 * Without introducing to much delay delay in beat detection
 * */ 
void SoundAnalyzer::_filter_volume(){
    const double filter_weight_up = 0.02;
    const double filter_weight_down = 0.6;
    if (volume>lagging_volume){
        lagging_volume = filter_weight_up*lagging_volume + (1.0-filter_weight_up)*volume;
    }else{
        lagging_volume = filter_weight_down*lagging_volume + (1.0-filter_weight_down)*volume;
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
/**Function that extract the maximum volume reached within the last <period> ms*/
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
    for (int i=0; i<BUF_LENGTH; i++){
        sum += fft_signal[i][REAL];
    }
    double mean = sum/BUF_LENGTH;
    for (int i=0; i<BUF_LENGTH; i++){
        fft_signal[i][REAL] -= mean;
    }
}

void SoundAnalyzer::_compute_FFT(){
  // Compute FFT
  fft_plan = fftw_plan_dft_1d(BUF_LENGTH, fft_signal, fft_out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(fft_plan);

  // Reshape results 
  for (int i=0; i<BUF_LENGTH; i++){
      sample_spectrum[i][FREQ] = i * SAMPLING_FREQ/BUF_LENGTH;
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

// TODO Analyze data at each frame rather than when thesse condiutions are met
bool SoundAnalyzer::_condition_for_analyis(){
    return (_memory_full() && (cpt%(VOL_BUFF_SIZE/4) == 0));
}

void SoundAnalyzer::_switch_to_state(states s){
    // Common actions
    t_last_state_change = frame.t_current_ms;
    // Transition specifi
    switch(s){
        case BEAT:
            state = BEAT;
            t_beat_tracking_start = frame.t_current_ms;
        break;

        case BREAK:
            state = BREAK;
        break;

        case BAD_SIGNAL:
            state = BAD_SIGNAL;
            BS_buff = 0;    // reset buffer
        break;

        case SUSTAINED_BREAK:
            state = SUSTAINED_BREAK;
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


