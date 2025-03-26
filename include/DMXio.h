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


// DMX Input interface
const unsigned int input_universe_id = 10;
extern ola::client::OlaClientWrapper wrapper;
extern ola::client::OlaClient *ola_input_client;

/* setupe ola library and start listening to input universe in dedicated thread*/
void setup_DMX_input();
