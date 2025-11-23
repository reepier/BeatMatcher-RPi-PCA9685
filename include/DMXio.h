#include <vector>

#include <ola/DmxBuffer.h>
#include <ola/client/ClientWrapper.h>
#include <ola/client/StreamingClient.h>

/* objects declared as "extern" are defined in DMXio.cpp */

struct ola_universe{
    int uni;                // universe ID ()
    ola::DmxBuffer buf;     // data content
};

/*
####### #     # ####### ######  #     # ####### 
#     # #     #    #    #     # #     #    #    
#     # #     #    #    #     # #     #    #    
#     # #     #    #    ######  #     #    #    
#     # #     #    #    #       #     #    #    
#     # #     #    #    #       #     #    #    
#######  #####     #    #        #####     #    
*/


// DMX output interface (OLA)
extern ola::client::StreamingClient ola_output_client;
extern ola::DmxBuffer ola_buffer;
extern std::vector<ola_universe> ola_pix_unis;

void send();

/*
### #     # ######  #     # ####### 
 #  ##    # #     # #     #    #    
 #  # #   # #     # #     #    #    
 #  #  #  # ######  #     #    #    
 #  #   # # #       #     #    #    
 #  #    ## #       #     #    #    
### #     # #        #####     #            
*/
#define OLA_ADR_OFFSET  -1

#define MAIN_CTRL_ADR      1+OLA_ADR_OFFSET
    #define MAIN_TRIG_CH       1 +OLA_ADR_OFFSET+MAIN_CTRL_ADR
    #define MAIN_DIM_CH        2 +OLA_ADR_OFFSET+MAIN_CTRL_ADR
    #define MAIN_COL1_CH       3 +OLA_ADR_OFFSET+MAIN_CTRL_ADR
    #define MAIN_COL2_CH       4 +OLA_ADR_OFFSET+MAIN_CTRL_ADR
    #define MAIN_INT_CH        5 +OLA_ADR_OFFSET+MAIN_CTRL_ADR
    #define MAIN_BEAT_CH       6 +OLA_ADR_OFFSET+MAIN_CTRL_ADR

#define LED_CTRL_ADR    15+OLA_ADR_OFFSET
    #define LED_DIM_CH      1+OLA_ADR_OFFSET+LED_CTRL_ADR
    #define LED_ANI_CH      2+OLA_ADR_OFFSET+LED_CTRL_ADR
    #define LED_COL1_CH     3+OLA_ADR_OFFSET+LED_CTRL_ADR
    #define LED_COL2_CH     4+OLA_ADR_OFFSET+LED_CTRL_ADR


#define RED_CTRL_ADR    20+OLA_ADR_OFFSET
    #define RED_DIM_CH      1+OLA_ADR_OFFSET+RED_CTRL_ADR
    #define RED_ANI_CH      2+OLA_ADR_OFFSET+RED_CTRL_ADR
    #define RED_COL1_CH     3+OLA_ADR_OFFSET+RED_CTRL_ADR 
    #define RED_COL2_CH     4+OLA_ADR_OFFSET+RED_CTRL_ADR



#define SR1_CTRL_ADR    25+OLA_ADR_OFFSET
#define SR2_CTRL_ADR    30+OLA_ADR_OFFSET
#define SR3_CTRL_ADR    35+OLA_ADR_OFFSET
#define SR4_CTRL_ADR    40+OLA_ADR_OFFSET
    #define SR_DIM_CH      1+OLA_ADR_OFFSET
    #define SR_ANI_CH      2+OLA_ADR_OFFSET
    #define SR_COL1_CH     3+OLA_ADR_OFFSET
    #define SR_COL2_CH     4+OLA_ADR_OFFSET

#define BEAM_CTRL_ADR   45+OLA_ADR_OFFSET
    #define BEAM_DIM_CH      1+OLA_ADR_OFFSET+BEAM_CTRL_ADR
    #define BEAM_ANI_CH      2+OLA_ADR_OFFSET+BEAM_CTRL_ADR
    #define BEAM_COL1_CH     3+OLA_ADR_OFFSET+BEAM_CTRL_ADR
    #define BEAM_COL2_CH     4+OLA_ADR_OFFSET+BEAM_CTRL_ADR


// NEW definition
#define FIX_DIM_CH       1  +OLA_ADR_OFFSET
#define FIX_ANI_CH       2  +OLA_ADR_OFFSET
#define FIX_COL1_CH      3  +OLA_ADR_OFFSET
#define FIX_COL2_CH      4  +OLA_ADR_OFFSET
#define FIX_PARM1_CH     5  +OLA_ADR_OFFSET
#define FIX_PARM2_CH     6  +OLA_ADR_OFFSET
#define FIX_PARM3_CH     7  +OLA_ADR_OFFSET
#define FIX_PARM4_CH     8  +OLA_ADR_OFFSET
#define FIX_PARM5_CH     9  +OLA_ADR_OFFSET
#define FIX_PARM6_CH     10 +OLA_ADR_OFFSET
#define FIX_PARM7_CH     11 +OLA_ADR_OFFSET
#define FIX_PARM8_CH     12 +OLA_ADR_OFFSET




// DMX Input interface
const unsigned int input_universe_id = 10;
extern ola::client::OlaClientWrapper wrapper;
extern ola::client::OlaClient *ola_input_client;

/* setupe ola library and start listening to input universe in dedicated thread*/
void setup_DMX_input();
