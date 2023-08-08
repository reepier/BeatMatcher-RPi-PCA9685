#include <cmath>

#include "spot.h"
#include "constant.h"
#include "sysfcn.h"
#include "debug.h"

using namespace std;

SpotFixture spot_1(73, 8, "Spot 1");     //spot frontal 1
SpotFixture spot_2(81, 8, "Spot 2");     //spot frontal 2
SpotFixture spot_3(89, 8, "Spot 3");    //spot frontal 3

SpotFixture spot_g(97, 8, "Spot g");     //spot d'ambiance gauche
SpotFixture spot_d(105, 8, "Spot d");     //spot d'ambiance droite

// -----------------------------------
// INDIVIDUAL SPOT
// -----------------------------------
/* /!\ /!\ Bullshit initializer --> I don't plan on coding animation for individual spots */
void SpotFixture::init(){
    this->animations.push_back(new SpotAnimation1(this, 0,0,0,0,    "Black", "SPOT.0.0"));
    // this->animations.push_back(new SpotAnimation1(this, 0,0,0,255,  "White", "SPOT.1.2"));
    // this->animations.push_back(new SpotAnimation1(this, 255,0,0,0,  "Red", "SPOT.1.3"));
    // this->animations.push_back(new SpotAnimation1(this, 0,255,0,0,  "Green", "SPOT.1.4"));
    // this->animations.push_back(new SpotAnimation1(this, 0,0,255,0,  "Blue", "SPOT.1.5"));
    // this->animations.push_back(new SpotAnimation1(this, 255,255,0,0,"Yellow", "SPOT.1.6"));
    // this->animations.push_back(new SpotAnimation1(this, 255,0,255,0,"Magenta", "SPOT.1.7"));
    // this->animations.push_back(new SpotAnimation1(this, 0,255,255,0,"Cyan", "SPOT.1.8"));

    this->activate_by_ID("SPOT.0.0");
    /*
    this->active_animation = this->animations[ rand() % this->animations.size() ];
    this->active_animation->init();
    */
}

DMX_vec SpotFixture::buffer(){
    return DMX_vec{this->MASTER_DIMMER, this->RGBW[R], this->RGBW[G],this->RGBW[B],this->RGBW[W], this->prog, this->color_wheel, this->strobe};
}

/* /!\ /!\ Bullshit contructor --> I don't plan on coding animation for individual spots */
SpotAnimation1::SpotAnimation1(SpotFixture* fix, uint8_t r,uint8_t g,uint8_t b, uint8_t w, string d, string i){
    this->fixture = fix;
    this->name  = "Fixed RGB color";
    this->description = d;
    this->id    = i;
    this->red   = r;
    this->green = g;
    this->blue  = b;
    this->white = w;
}

void SpotAnimation1::init(){
    this->t_animation_start_ms = millis();
    this->frame_cpt = 0;
}

void SpotAnimation1::new_frame(){
    balise("compute new spot1 frame");
    // nothing to do for this animation
    this->fixture->RGBW[R] = this->red;
    this->fixture->RGBW[G] = this->green;
    this->fixture->RGBW[B] = this->blue;
    this->fixture->RGBW[W] = this->white;
}


// -----------------------------------
// RACKs of SPOTS
// -----------------------------------
SpotRack front_rack(&spot_1, &spot_2, &spot_3, "Front Rack");
SpotRack back_rack(&spot_g, &spot_d, "Back Rack");

void SpotRack::init(){
    this->rack_size = this->spots.size();

    //this->animations.push_back();
    // Animation 1
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      BLACK,       15000, 5000, 8000, 1000,   "Black", "FR.0.0"));

    this->animations.push_back(new SpotFrontAnimation1(this, PURPLE(50), GOLD(255),   15000, 5000, 8000, 1000,   "Purple background / gold flashes",    "FR.1.1.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, SODIUM(50), WHITE(255),  15000, 5000, 8000, 1000,   "Orange background, white flashes",    "FR.1.1.2"));
    this->animations.push_back(new SpotFrontAnimation1(this, RED(50),    BLUE(255),   15000, 5000, 8000, 1000,   "Red background, Blue flashes",        "FR.1.1.3"));
    this->animations.push_back(new SpotFrontAnimation1(this, RED(50),    RED(255),    15000, 5000, 8000, 1000,   "Red background, RED flashes",         "FR.1.1.4"));
    this->animations.push_back(new SpotFrontAnimation1(this, RED(50),    GOLD(255),   15000, 5000, 8000, 1000,   "Red background gold flashes",         "FR.1.1.5"));
    this->animations.push_back(new SpotFrontAnimation1(this, RED(50),    WHITE(255),  15000, 5000, 8000, 1000,   "Red background, white flashes",       "FR.1.1.6"));
    this->animations.push_back(new SpotFrontAnimation1(this, RED(50),    WHITE(255),  15000, 5000, 3000, 600,    "Red background, fast white flashes",  "FR.1.1.6.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, PINK(50),   CYAN(255),   15000, 5000, 7000, 1000,   "Purple background, Cyan flashes",     "FR.1.1.7"));

    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      WHITE(255),  15000, 5000, 8000, 1000,   "Black background, White flashes",     "FR.1.2.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      WHITE(255),  15000, 5000, 3000, 600,    "Black background, fast White flashes","FR.1.2.1.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      RED(255),    15000, 5000, 8000, 1000,    "Black background, Red flashes",       "FR.1.2.2"));
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      BLUE(255),   15000, 5000, 8000, 1000,    "Black background, Blue flashes",      "FR.1.2.3"));
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      ORANGE(255), 15000, 5000, 8000, 1000,    "Black background, Orange flashes",    "FR.1.2.4"));
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      GOLD(255),   15000, 5000, 8000, 1000,    "Black background, GOLD flashes",      "FR.1.2.5"));
    this->animations.push_back(new SpotFrontAnimation1(this, BLACK,      GOLD(255),   15000, 5000, 3000, 600,    "Black background, fast GOLD flashes",  "FR.1.2.5.1"));

    this->animations.push_back(new SpotFrontAnimation1(this, SODIUM(100),   BLACK,   15000, 5000, 7000, 2000,   "Sodium background, Black holes",   "FR.1.3.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, RED(100),      BLACK,   15000, 5000, 7000, 2000,   "Red background, Black flashes",    "FR.1.3.2"));
    this->animations.push_back(new SpotFrontAnimation1(this, PURPLE(100),   BLACK,   15000, 5000, 7000, 2000,   "Purple background, Black flashes", "FR.1.3.3"));

    // Animation 2:
    this->animations.push_back(new SpotFrontAnimation2(this, WHITE(255),  STRB_FAST,    "white, fast strobe",   "FR.2.1.1"));
    this->animations.push_back(new SpotFrontAnimation2(this, WHITE(255),  STRB_MED,     "white, medium strobe", "FR.2.1.2"));
    this->animations.push_back(new SpotFrontAnimation2(this, WHITE(255),  STRB_SLOW,    "white, slow strobe",   "FR.2.1.3"));
    this->animations.push_back(new SpotFrontAnimation2(this, RED(255),    STRB_FAST,    "red, fast strobe",     "FR.2.2.1"));
    this->animations.push_back(new SpotFrontAnimation2(this, RED(255),    STRB_MED,     "red, medium strobe",   "FR.2.2.2"));
    this->animations.push_back(new SpotFrontAnimation2(this, RED(255),    STRB_SLOW,    "red, slow strobe",     "FR.2.2.3"));
    this->animations.push_back(new SpotFrontAnimation2(this, GOLD(255),   STRB_FAST,    "gold, fast strobe",    "FR.2.3.1"));
    this->animations.push_back(new SpotFrontAnimation2(this, GOLD(255),   STRB_MED,     "gold, medium strobe",  "FR.2.3.2"));
    this->animations.push_back(new SpotFrontAnimation2(this, GOLD(255),   STRB_SLOW,    "gold, slow strobe",    "FR.2.3.3"));
    

    
    this->activate_by_ID("FR.0.0");
}

void SpotRack::init_back(){
    this->rack_size = this->spots.size();
    //this->animations.push_back();
}

// -----------------------------------
// FRONTAL RACK of SPOT Animations
// -----------------------------------
// 1 ---------------------------------
void SpotFrontAnimation1::init(){
    this->frame_cpt = 0;
    this->t_animation_start_ms;

    this->p_ms = vector<int>{rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms),rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms), rand_min_max(sin_min_p_ms, sin_max_p_ms)};
    
    const int n_spot = this->fixture->spots.size();
    this->t_next.resize(n_spot);
    this->t_prev.resize(n_spot);
    for (int i=0; i<n_spot; i++){
        t_next[i] = frame.t_current_ms + rand_min_max(rand_const_ms/5, rand_const_ms*2);
        t_prev[i] = 0;
    }
}

void SpotFrontAnimation1::new_frame(){
    balise("compute new front rack1 frame");
    long t = frame.t_current_ms;       // for readability
    int n_spot = this->fixture->spots.size();   // for readability
    
    // update 4 sinewaves of different period
    vector<double> s = {sin(2*M_PI*t/p_ms[0]), sin(2*M_PI*t/p_ms[1]), sin(2*M_PI*t/p_ms[2]), sin(2*M_PI*t/p_ms[3]), sin(2*M_PI*t/p_ms[4]) };
    
    // for each spot "i" of the rack
    for (int i_spot=0; i_spot < n_spot; i_spot++){
        DMX_vec backgd_RGBW(4);        
        // compute the background color values : 
            backgd_RGBW[R] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[R] * (1 + 0.4*s[(i_spot+0)%5]))  ,0),255);
            backgd_RGBW[G] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[G] * (1 + 0.4*s[(i_spot+1)%5]))  ,0),255);
            backgd_RGBW[B] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[B] * (1 + 0.4*s[(i_spot+2)%5]))  ,0),255);
            backgd_RGBW[W] = min(max(    (int) (  (1+0.4*s[(i_spot+4)%5]) * this->color1[W] * (1 + 0.4*s[(i_spot+3)%5]))  ,0),255);
        // ------------------------------- limit to 0-255 ---------------- Spot Intensity    *  RGBW pixel intensity                            ;
        
        // compute the flash = exp( -(spd.(t-t0))²)
            // when the flash passes, compute the next flash timestamp and update prev flash

            if (t > this->t_next[i_spot]){

                this->t_prev[i_spot] = this->t_next[i_spot];
                this->t_next[i_spot] = this->t_next[i_spot] + rand_min_max(this->rand_const_ms/5, this->rand_const_ms*2);
            }

            int t_next_flash = this->t_next[i_spot];        // for readability
            int t_prev_flash = this->t_prev[i_spot];        // for readability  
            
            double flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev_flash), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next_flash), 2));

            this->fixture->spots[i_spot]->RGBW[R] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[R] + flash_intensity * this->color2[R]  ),0),255); 
            this->fixture->spots[i_spot]->RGBW[G] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[G] + flash_intensity * this->color2[G]  ),0),255);
            this->fixture->spots[i_spot]->RGBW[B] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[B] + flash_intensity * this->color2[B]  ),0),255);
            this->fixture->spots[i_spot]->RGBW[W] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[W] + flash_intensity * this->color2[W]  ),0),255);
    }
}

// -----------------------------------
// 2 ---------------------------------
void SpotFrontAnimation2::shake(){  //randomizes the strob speeds on request
    for (DMX_vec::iterator spd = this->strobe_spds.begin(); spd != this->strobe_spds.end(); spd++){
        float delta =  map((float)this->strobe_spd, 0.0, 255.0, var_max, var_min);          
        
        (*spd) = rand_min_max( this->strobe_spd*(1-delta) , this->strobe_spd*(1+delta) ); // initialize each strobe with a slightly different frequency
    }
}

void SpotFrontAnimation2::init(){
    this->frame_cpt = 0;
    this->t_animation_start_ms = frame.t_current_ms;
    this->t_next_shake = frame.t_current_ms + 2000;

    this->shake();
}

void SpotFrontAnimation2::new_frame(){
    // for readability
    spot_vec spots = this->fixture->spots;
    int n_spots = spots.size();
    unsigned long t = frame.t_current_ms;

    if (((long)frame.t_current_ms - (long)this->t_next_shake) > 0){
        this->shake();
        this->t_next_shake += 2000; 
    }
    for (int i = 0; i<n_spots; i++){
        spots[i]->RGBW   = this->color;

        float delta = map((float)this->strobe_spds[i], 0.0,255.0, var_max, var_min) / 2;
        spots[i]->strobe = min(max( (int)(this->strobe_spds[i] * (1 + delta*sin(i*M_PI/3 + 2*M_PI*t/3000)))  ,0),255);
        // spots[i]->strobe = min(max( rand_min_max(this->strobe_spds[i] * (1-delta) , this->strobe_spds[i] * (1+delta))  ,0),255);
    }
}