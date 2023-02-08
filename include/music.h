#include <fftw3.h>
#include <vector>

#include <MCP3008/MCP3008.h>

#define SAMPLE_SIZE 128      // record length (number of individual samples)
#define SAMPLING_FREQ 8000     // sampling frequency
#define FREQ_BAND 2     // frequency band used to evaluate volume (low value for bass / high value for treble)

#define VOL_BUFF_SIZE 128   // size of the volume buffer

// MCP3008
#define MCP3008_MAX 1023
#define MCP3008_MIN 0
#define MCP_CHAN 5

// thresholds
#define THD_toBK 45     // Volume Threshold to go from state X to BREAK  mode
#define THD_BTtoBS 3    // Threshold to go from BEAT TRACKING to BAD SIGNAL mode
#define THD_BStoBT 5    // Threshold to go from  BAD SIGNAL to BEAT TRACKING mode

// FFTW
#define REAL 0
#define IMAG 1
#define FREQ 0
#define AMPL 1

enum states{
    BEAT_TRACKING   = 1,    // volume is high and beat is clear
    BREAK           = 2,    // volume is low (indicates a break)
    BAD_SIGNAL      = 3     // volume is high but the beat is not perceptible
};

class SoundAnalyzer{

    MCP3008Lib::MCP3008 adc;    // MCP3008 object
    // record storage
    // private :   double record_real[SAMPLE_SIZE];
    // private :   double record_imag[SAMPLE_SIZE];
    // FFTW structures
    public : fftw_complex *signal;
    private : fftw_complex *fft_out;
    private : fftw_plan my_plan;

    // FFT results storage structure
    public  : float spectrum[SAMPLE_SIZE][2];    // stores AMPL x FREQ array;

    public :    bool clip; // true if record() detects ADC saturation
    public :    int volume;
    // FFT library
    // private :   arduinoFFT FFT = arduinoFFT();
    // phrase storage
        //private :   int v_memory[VOL_BUFF_SIZE];
        //private :   int v_memory_sorted[VOL_BUFF_SIZE];
    std::vector<int> v_memory;
    std::vector<int> v_memory_sorted;

    // phrase analysis variables
    private :   int i_record = 0;                   // number of volume samples recorded
    private :   bool tab_is_full=false;
    public :    bool enable_analysis;
    public :    float v_max, v_mean, v_quarter[3], v_95, v_XX;
    public :    float ratio_95_q1, ratio_95_q2, ratio_95_q3;

    // Beat tracking variables
    public :    float beat_threshold = 60;
    public :    bool raw_beat=false, new_beat=false, filtered_beat=false;
    public :    unsigned long last_beat = 0;         // Stores timestamp of the last raw_beat=true event
    public :    unsigned long last_new_beat = 0;
    public :    unsigned long beat_tracking_start = 0;

    // state machine variables
    private :   int BS_cpt = 0, BT_cpt = 0;
    public :    states state = BEAT_TRACKING, old_sys_state = BEAT_TRACKING;
    public :    bool state_changed = false;    

    // Main functions (entry points)
    public :    void init();
    public :    void update();
    public :    void record();          
    public :    void process_record();

    // hidden functions (called by the main functions)
    private :   void _copy_memory();
    private :   void _compute_stats();
    private :   void _update_beat_threshold();
    private :   void _update_state();
    private :   void _remove_DC_value();
    private :   void _compute_FFT();
    private :   void _sort_memory();

    // fake analysis function (for animation developpement purpose)
    public :    void fake_analysis(); 

    // debug intermediary variables
    public :    int deb_max, deb_min;

};

extern SoundAnalyzer sampler;