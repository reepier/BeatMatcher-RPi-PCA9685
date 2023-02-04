#include <fftw3.h>
#include <vector>

#define SAMP_N 128      // record length (number of individual samples)
#define SAMP_F 8000     // sampling frequency
#define FREQ_BAND 2     // frequency band used to measure volume

#define PHRASE_LEN 128   // number of volume samples in 1 phrase

// MCP3008
#define ADC_MAX 1023
#define ADC_MIN 0
#define MCP_CHAN 5

// thresholds
#define THD_toBK 45
#define THD_BTtoBS 3
#define THD_BStoBT 5

// FFTW
#define REAL 0
#define IMAG 1
#define FREQ 0
#define AMPL 1

class SoundAnalyzer{
            
    // record storage
    // private :   double record_real[SAMP_N];
    // private :   double record_imag[SAMP_N];
    // FFTW structures
    public : fftw_complex *signal;
    private : fftw_complex *fft_out;
    private : fftw_plan my_plan;

    // FFT results storage structure
    public  : float spectrum[SAMP_N][2];    // stores AMPL x FREQ array;

    public :    bool clip; // true if record() detects ADC saturation
    public :    int volume;
    // FFT library
    // private :   arduinoFFT FFT = arduinoFFT();
    // phrase storage
        //private :   int v_memory[PHRASE_LEN];
        //private :   int v_memory_sorted[PHRASE_LEN];
    std::vector<int> v_memory;
    std::vector<int> v_memory_sorted;

    // phrase analysis variables
    private :   int i_record = 0;                   // number of volume samples recorded
    private :   bool tab_is_full=false;
    public :    bool enable_analysis;
    public :    float v_max, v_mean, v_quarter[3], v_95, v_XX;
    public :    float ratio_95_q1, ratio_95_q2, ratio_95_q3;

    // Beat tracking variables
    public :    float beat_thresh = 60;
    public :    bool beat=false, new_beat=false, filtered_beat=false;
    public :    unsigned long last_beat = 0;         // Stores timestamp of the last beat=true event
    public :    unsigned long last_new_beat = 0;
    public :    unsigned long beat_tracking_start = 0;

    // state machine variables
    private :   int BS_cpt = 0, BT_cpt = 0;
    public :    int system_state = 1, old_sys_state = 1;
    public :    bool state_change = false;    

    // Main functions
    public :    void init();
    public :    void record();          
    public :    void process_record();

    // hidden functions
    private :   void copy_memory();
    private :   void compute_stats();
    private :   void update_beat_threshold();
    private :   void update_state();
    private :   void DCRemoval();
    private :   void ComputeFFT();
    private :   void sort_memory();

    // fake analysis (for animation developpement purpose)
    public :    void fake_analysis(); 


    // debug intermediary variables
    public :    int deb_max, deb_min;

};

extern SoundAnalyzer sampler;