#include <thread>

#include "debug.h"
#include "DMXio.h"
#include "fixtures.h"

using namespace std;

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
ola::client::StreamingClient ola_output_client;
ola::DmxBuffer ola_buffer;
vector<ola_universe> ola_pix_unis(NUM_SUBPIX/MAX_SUBPIX_PER_UNI + ((NUM_SUBPIX%MAX_SUBPIX_PER_UNI)==0 ? 0 : 1));


void send(){

    // construct & send DMX frame for old school fixtures (COTS DMX fixtures)
    balise("Construct & send buffer for classical fixtures");
    for (fix_vec::iterator fx = ll_fxtrs.begin(); fx != ll_fxtrs.end(); fx++){
        ola_buffer.SetRange((*fx)->get_address(), (*fx)->buffer().data(), (*fx)->get_nCH());
    }
    ola_output_client.SendDmx(0, ola_buffer);

    // construct & send DMX frames for addressable leds pixels values (sent through artnet)
    balise("Construct & send buffer for artnet pixels");
    DMX_vec sub_buffer, long_buffer = addr_led.buffer();
    auto start = long_buffer.begin();
    int universe_cpt = 1;
    for(auto& pix_uni : ola_pix_unis){
        unsigned int length;
        if (long_buffer.end() > start + MAX_SUBPIX_PER_UNI){
            sub_buffer.assign(start, start + MAX_SUBPIX_PER_UNI);
            length = MAX_SUBPIX_PER_UNI;
            start += MAX_SUBPIX_PER_UNI;
        }else{ 
            sub_buffer.assign(start, long_buffer.end());
            length = distance(start, long_buffer.end());
        }

        pix_uni.buf.SetRange(0, sub_buffer.data(), length);
        pix_uni.uni = universe_cpt++;
    }

    //send pixel buffers in random sequence (to avoid showing regular patterns when some frames are lost)
    vector<ola_universe> ola_pix_uni_rand = fcn::randomized_vector(ola_pix_unis);
    ola::client::StreamingClientInterface::SendArgs args;
    for(auto& pix_uni : ola_pix_uni_rand){
        ola_output_client.SendDMX(pix_uni.uni, pix_uni.buf, args);
    }
}


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
ola::client::OlaClientWrapper wrapper;
ola::client::OlaClient *ola_input_client;


/** Control logic & code structure :
 * - data from TRIG_CH is processed in the following manner
 *          if =255 --> the controler cmds are processed in real time (colors & animations updated at every frame)
 *          if <255 --> the controler cmds are processed only when a RISING front is detected on TRIG_CH data (Rising fronts 
 *                      are filtered 1 second to avoid cascades of triggers when the input channel continuously increases)
 *   
 * - data from channel MAIN_COL1 & MAIN_COL1, if not both equal to 0 are converted into a color palette :
 *           animator.controler_main_palette
 * - data from channel LED_COL1_CH & LED_COL2_CH, if not both equal to 0 are converted into a color palette : addr_led.controler_palette
    */

void processDMXinput(const ola::client::DMXMetadata &metadata, const ola::DmxBuffer &data) {
    static ola::DmxBuffer memorized_buffer; // contains the last DMX buffer received

    //Check if new data is available (if input data has changed)
    bool new_data_available = false;
    if (memorized_buffer.Size()==0 || !(data == memorized_buffer)){
        new_data_available = true;
        // log(1, "New control data available");
    }

    // Process trigger
    bool trigger = false;
    static time_t last_trigger_ms;
    if ( data.Get(MAIN_TRIG_CH) == 255    ||   (data.Get(MAIN_TRIG_CH) > memorized_buffer.Get(MAIN_TRIG_CH) && millis()-last_trigger_ms > 1000) ){
        trigger = true;
        last_trigger_ms = millis();
    }else{
        trigger = false;
    }
    if (trigger){
        // log(1, "Trigger activated, processing new commands");
    }

    // PROCESS MAIN COLORS (only when the trigger is active) //TODO even in case of trigger, if nothing change wt regards to the previous settinfs, do nothing.
    if (trigger){
        // get & rewrap raw data
        int main_col1_val = min(max((uint8_t)0,  data.Get(MAIN_COL1_CH)) , (uint8_t)(simpleColor::last_color));
        int main_col2_val = min(max((uint8_t)0,  data.Get(MAIN_COL2_CH)) , (uint8_t)(simpleColor::last_color));
        //create output structrue
        color_vec main_palette;
        // if input data are not in DEFAULT positions (automatic mode)
        if ( main_col1_val!=0 || main_col2_val!=0 ) { 
            // create a palette based on input data
            if (main_col1_val > 0)  main_palette.push_back((simpleColor)(main_col1_val-1));
            if (main_col2_val > 0)  main_palette.push_back((simpleColor)(main_col2_val-1));
            // update animator main palette if there is a change
            if (animator.external_palette != main_palette){
                animator.external_palette = main_palette;
                animator.new_external_palette = true;
                // log(1, "New main palette : ", fcn::palette_to_string(animator.external_palette));
            }else{
                
            }
        // if input data are in DEFAULT position
        }else{
            if ( !animator.external_palette.empty()){       //if not already empty 
                animator.external_palette.clear();    //reset to empty palette (meaning auto palette or fixture palette will apply to leds)
                animator.new_external_palette = true;
                log(1, "Back to automatic main palette");
            }else{
                
            }
        }
    }else{
        
    }

    // PROCESS ADRESSABLE LED DIMMER
    if (new_data_available){ // process dimmer input as a continuous stream (& not only on trigger)
        // get & rewrap raw data
        addr_led.master = data.Get(LED_DIM_CH); // already a 0-255 dmx data, no conversion/rewrap needed
    }

    //PROCESS ADDRESSABLE LEDs Animation
    if (trigger){
        //get & rewrap raw data
        int led_ani_val = data.Get(LED_ANI_CH);
        // if input data is not in DEFAULT positions (automatic mode)
        if ( led_ani_val!=0) { 
            // update led animation if there is a change
            if (addr_led.external_animation != led_ani_val){
                addr_led.external_animation = led_ani_val;
                addr_led.new_external_animation = true;
                // log(2, "New led animation : ", fcn::num_to_str(addr_led.external_animation));
            }else{
                
            }
        // if input data is DEFAULT (0) 
        }else{
            if (addr_led.external_animation != 0){  //if not already reset to 0
                addr_led.external_animation = 0;    //reset to 0
                addr_led.new_external_animation = true;
                log(2, "Back to automatic led animation");
            }else{
                
            }
        }
    }else{
        
    }

    //PROCESS ADDRESSABLE LEDs COLORS
    if (trigger){
        // get & rewrap raw data //TODO use "clamp" instead of min(max())
        int led_col1_val = min(max((uint8_t)0,  data.Get(LED_COL1_CH)) , (uint8_t)(simpleColor::last_color));
        int led_col2_val = min(max((uint8_t)0,  data.Get(LED_COL2_CH)) , (uint8_t)(simpleColor::last_color));
        //create output structrue
        color_vec led_palette;   //start with empty palette
        // if input data are not in DEFAULT positions (automatic mode)
        if ( led_col1_val!=0 || led_col2_val!=0 ) {
            // create a palette based on (non zero) input data
            if (led_col1_val > 0)  led_palette.push_back((simpleColor)(led_col1_val-1));
            if (led_col2_val > 0)  led_palette.push_back((simpleColor)(led_col2_val-1));
            // update led palette if there is a change
            if (addr_led.external_palette != led_palette){
                addr_led.new_external_palette = true;
                addr_led.external_palette = led_palette;
                // log(2, "New led palette : ", fcn::palette_to_string(addr_led.external_palette));
            }else{
                
            }
        }else{
            if ( !addr_led.external_palette.empty()){  //if not already empty 
                addr_led.new_external_palette = true;
                addr_led.external_palette.clear();    //reset to empty palette (meaning main palette or auto palette will apply to leds)
                log(2, "Back to automatic led palette");
            }else{
                
            }
        }
    }else{
        
    }//TODO clean this if / elseif structure --> it has way to many ramifications


    SpotRack* spot_rack_1 = &front_rack;  //allows for more fexibility when using more than 1 rack
    //PROCESS SPOT RACK 1 DIMMER
    if (new_data_available){ // process dimmer input as a continuous stream (& not only on trigger)
        // get & rewrap raw data
        spot_rack_1->master = data.Get(SR1_DIM_CH); // already a 0-255 dmx data, no conversion/rewrap needed
    }

    //PROCESS SPOT RACK 1 Animation
    if (trigger){
        //get & rewrap raw data
        int sr1_ani_val = data.Get(SR1_ANI_CH);
        // if input data is not in DEFAULT positions (automatic mode)
        if ( sr1_ani_val!=0) { 
            // update Rack animation if there is a change
            if (spot_rack_1->external_animation != sr1_ani_val){
                spot_rack_1->external_animation = sr1_ani_val;
                spot_rack_1->new_external_animation = true;
                // log(2, "New SR1 animation : ", fcn::num_to_str(spot_rack_1->external_animation));
            }else{
                
            }
        // if input data is DEFAULT (0) 
        }else{
            if (spot_rack_1->external_animation != 0){  //if not already reset to 0
                spot_rack_1->external_animation = 0;    //reset to 0
                spot_rack_1->new_external_animation = true;
                log(2, "Back to automatic SR1 animation");  //TODO choose where to put log instructions (cannot be both in DMXio and Animator)
            }else{
                
            }
        }
    }else{
        
    }

    //PROCESS SPOT RACK 1 LEDs COLORS
    if (trigger){
        // get & rewrap raw data
        int sr1_col1_val = min(max((uint8_t)0,  data.Get(SR1_COL1_CH)) , (uint8_t)(simpleColor::last_color));
        int sr1_col2_val = min(max((uint8_t)0,  data.Get(SR1_COL2_CH)) , (uint8_t)(simpleColor::last_color));
        //create output structrue
        color_vec sr1_palette;   //start with empty palette
        // if input data are not in DEFAULT positions (automatic mode)
        if ( sr1_col1_val!=0 || sr1_col2_val!=0 ) {
            // create a palette based on (non zero) input data
            if (sr1_col1_val > 0)  sr1_palette.push_back((simpleColor)(sr1_col1_val-1));
            if (sr1_col2_val > 0)  sr1_palette.push_back((simpleColor)(sr1_col2_val-1));
            // update Rack palette if there is a change
            if (spot_rack_1->external_palette != sr1_palette){
                spot_rack_1->external_palette = sr1_palette;
                spot_rack_1->new_external_palette = true;
                // log(2, "New SR1 palette : ", fcn::palette_to_string(spot_rack_1->external_palette));
            }else{
                
            }
        }else{
            if ( !spot_rack_1->external_palette.empty()){  //if not already empty 
                spot_rack_1->external_palette.clear();    //reset to empty palette (meaning main palette or auto palette will apply to leds)
                spot_rack_1->new_external_palette = true;
                log(2, "Back to automatic SR1 palette");
            }else{
                
            }
        }
    }else{
        
    }

    //PROCESS RED RAYZ DIMMER
    if (new_data_available){ // process dimmer input as a continuous stream (& not only on trigger)
        // get & rewrap raw data
        redrayz.master = data.Get(RED_DIM_CH); // already a 0-255 dmx data, no conversion/rewrap needed
        redrayz.address = redrayz.get_address();
    }

    //PROCESS RED RAYZ Animation
    if (trigger){
        //get & rewrap raw data
        int red_ani_val = data.Get(RED_ANI_CH);
        // if input data is not in DEFAULT positions (automatic mode)
        if ( red_ani_val!=0) { 
            // update Rack animation if there is a change
            if (redrayz.external_animation != red_ani_val){
                redrayz.external_animation = red_ani_val;
                redrayz.new_external_animation = true;
            }else{
                
            }
        // if input data is DEFAULT (0) 
        }else{
            if (redrayz.external_animation != 0){  //if not already reset to 0
                redrayz.external_animation = 0;    //reset to 0
                redrayz.new_external_animation = true;
                log(2, "Back to automatic RED animation");  //TODO choose where to put log instructions (cannot be both in DMXio and Animator)
            }else{
                
            }
        }
    }else{
        
    }

    //PROCESS RED RAYZ COLORS
    if (trigger){
        // get & rewrap raw data
        int red_col1_val = min(max((uint8_t)0,  data.Get(RED_COL1_CH)) , (uint8_t)(simpleColor::last_color));
        int red_col2_val = min(max((uint8_t)0,  data.Get(RED_COL2_CH)) , (uint8_t)(simpleColor::last_color));
        //create output structrue
        color_vec red_palette;   //start with empty palette
        // if input data are not in DEFAULT positions (automatic mode)
        if ( red_col1_val!=0 || red_col2_val!=0 ) {
            // create a palette based on (non zero) input data
            if (red_col1_val > 0)  red_palette.push_back((simpleColor)(red_col1_val-1));
            if (red_col2_val > 0)  red_palette.push_back((simpleColor)(red_col2_val-1));
            // update Rack palette if there is a change
            if (redrayz.external_palette != red_palette){
                redrayz.external_palette = red_palette;
                redrayz.new_external_palette = true;
                // log(2, "New SR1 palette : ", fcn::palette_to_string(spot_rack_1->external_palette));
            }else{
                
            }
        }else{
            if ( !redrayz.external_palette.empty()){  //if not already empty 
                redrayz.external_palette.clear();    //reset to empty palette (meaning main palette or auto palette will apply to leds)
                redrayz.new_external_palette = true;
                log(2, "Back to automatic RED palette");
            }else{
                
            }
        }
    }else{
        
    }

    //TODO to improve genericity, put all these repeating code blocks in BaseFixture class (with overrides if needed in SpecificFixture class)


    memorized_buffer = data;    // memorize current buffer for the next function call
}


// Function Called when universe registration completes.
void RegisterComplete(const ola::client::Result& result) {
    if (!result.Success()) {
        //  OLA_WARN << "Failed to register universe: " << result.Error();
    }
}

void setup_DMX_input(){
    if (!wrapper.Setup())
        exit(1);
    ola_input_client = wrapper.GetClient();
    // Set the callback and register our interest in this universe
    ola_input_client->SetDMXCallback(ola::NewCallback(&processDMXinput));
    ola_input_client->RegisterUniverse(input_universe_id, ola::client::REGISTER, ola::NewSingleCallback(&RegisterComplete));
    
    // // option 1 : without thread --> halts the rest of the application execution !!! NOPE !!!
    // wrapper.GetSelectServer()->Run();

    //option 2 : with thread --> allows the rest of the application to execute in parallel !! YUP !!!
    // Create a new thread to run the select server
    std::thread select_server_thread([]() {
        wrapper.GetSelectServer()->Run();
    });
    // Detach the thread to let it run independently
    select_server_thread.detach();
}



/*TODO DMX Commande interface
Pour faciliter l'integration du systeme Beatmatcher avec d'autre éléments, la necessité d'une IHM de pilotage en temps réel
s'impose.
Afin de maximiser les cas d'usage possible, les exigences sont les suivantes : 

Lorsqu'il est exécuté et sans interruption d'exécution / recompilation :
    - le programme doit etre capable de fonctionner en automatisme intégral lorsque l'opérateur le souhaite ou lorsqu'il
     n'y a pas d'opérateur (c'est la seule capacité du Beatmatcher aujourd'hui)
    - le programme doit etre capable de receptionner des ordres de commande via DMX sur 1 univers(Artnet) permettant de piloter
    au choix un ou plusieurs des éléments suivants :
        - la palette de couleur général (2 ou 3 couleurs)
        - la palette de couleur de chaque fixture (1 à 3 couleurs)
        - l'animation jouée par chaque fixture (choisie dans une liste prédéfinie et préconfigurée)
        - le dimmer de chaque fixture
        L'opérateur peut ainsi prendre ou rendre la main sur chacun de ces paramètres individuellement permettant une grande
        flexibilité dans le degré d'automatisme. Par exemple, il est possible à partir d'une configuration tout automatique de 
        simplement forcer l'animation et/ou la couleur d'un seul fixture parmi l'ensemble
        
    - Afin de faciliter la gestion de l'ensemble et d'éviter les changements d'animation / couleur intempestifs et donc 
    (disgracieux), l'opérateur doit pouvoir toucher aux commandes pour préparer la scene suivante SANS que le Beatmatcher
    ne prenne en compte les commandes immédiatement. On introduira donc un système de déclencheur (1 canal DMX) qui par un
    front montant, commande au beatmatcher la prise en compte des nouveaux réglages. Ce déclencheur peut n'agir que sur 
    quelques canaux de commmande particulièrement dangereux (choix animation, choix couleur) et pas sur d'autres (Dimmers).
    Ce déclencheur doit pouvoir etre inhibé en le positionnant à sa valeur MAX (les changemets de paramétrages sont alors
    prise en compte en continu) 
    - pour rendre la main sur un canal de type choix animation ou choix couleur, l'opérateur le positionne à la valeur minimum
    soit ZERO. Dans cette configuration, c'est le beatmatcher qui fait automatiquement les choix d'animation et de couleur. 
         */
