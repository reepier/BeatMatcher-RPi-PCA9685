#include <cmath>

#include "spot.h"
#include "sysfcn.h"
#include "debug.h"

using namespace std;

SpotFixture spot_1(73,  8, "Spot 1");     //spot frontal 1
SpotFixture spot_2(81,  8, "Spot 2");     //spot frontal 2
SpotFixture spot_3(89,  8, "Spot 3");     //spot frontal 3
SpotFixture spot_4(97,  8, "Spot_4");     //spot frontal 4
SpotFixture spot_5(105, 8, "Spot_5");     //spot frontal 5
SpotFixture spot_6(113, 8, "Spot_6");     //spot frontal 6



SpotFixture spot_g(122, 8, "Spot g");     //spot d'ambiance gauche
SpotFixture spot_d(130, 8, "Spot d");     //spot d'ambiance droite

/* --------------------------------------------------------------------
   _____ _____   ____ _______ 
  / ____|  __ \ / __ \__   __|
 | (___ | |__) | |  | | | |   
  \___ \|  ___/| |  | | | |   
  ____) | |    | |__| | | |   
 |_____/|_|     \____/  |_|   

/ ----------------------------------------------------------------------- */
/* /!\ /!\ Bullshit initializer --> I don't plan on coding animation for individual spots */
// void SpotFixture::init(){
//     this->animations.push_back(new SpotAnimation1(this, 0,0,0,0,    " ", "SPOT.0.0"));
//     // this->animations.push_back(new SpotAnimation1(this, 0,0,0,255,  "White", "SPOT.1.2"));
//     // this->animations.push_back(new SpotAnimation1(this, 255,0,0,0,  "Red", "SPOT.1.3"));
//     // this->animations.push_back(new SpotAnimation1(this, 0,255,0,0,  "Green", "SPOT.1.4"));
//     // this->animations.push_back(new SpotAnimation1(this, 0,0,255,0,  "Blue", "SPOT.1.5"));
//     // this->animations.push_back(new SpotAnimation1(this, 255,255,0,0,"Yellow", "SPOT.1.6"));
//     // this->animations.push_back(new SpotAnimation1(this, 255,0,255,0,"Magenta", "SPOT.1.7"));
//     // this->animations.push_back(new SpotAnimation1(this, 0,255,255,0,"Cyan", "SPOT.1.8"));

//     this->activate_by_ID("SPOT.0.0");
//     /*
//     this->active_animation = this->animations[ rand() % this->animations.size() ];
//     this->active_animation->init();
//     */
// }

// DMX_vec SpotFixture::buffer(){
    
// }

// DMX_vec SpotFixture::RGBW(simpleColor c, uint8_t intensity){
//     switch (c)
//     {
//     case black:
//         return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
//         break;
//     case red:
//         return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);
//         break;
//     case green:
//         return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 160.0/255*intensity);
//         break;
//     case blue:
//         return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);
//         break;
//     case yellow:
//         return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);
//         break;
//     case orange:
//         return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);
//         break;
//     case sodium:
//         return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);
//         break;
//     case cyan:
//         return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);
//         break;
//     case purple:
//         return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);
//         break;    
//     case magenta:
//         return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);
//         break;
//     case pink:
//         return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);
//         break;
//     case white:
//         return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
//         break;
//     case gold:
//         return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
//         break;
//     default:
//         break;
//     }
// }


/* /!\ /!\ Bullshit contructor --> I don't plan on coding animation for individual spots */
// SpotAnimation1::SpotAnimation1(SpotFixture* fix, uint8_t r,uint8_t g,uint8_t b, uint8_t w, string d, string i){
//     this->fixture = fix;
//     this->name  = "Fixed RGB color";
//     this->description = d;
//     this->id    = i;
//     this->red   = r;
//     this->green = g;
//     this->blue  = b;
//     this->white = w;
// }

// void SpotAnimation1::init(){
//     this->t_animation_start_ms = millis();
//     this->frame_cpt = 0;
// }

// void SpotAnimation1::new_frame(){
//     balise("compute new spot1 frame");
//     // nothing to do for this animation
//     this->fixture->RGBWout[R] = this->red;
//     this->fixture->RGBWout[G] = this->green;
//     this->fixture->RGBWout[B] = this->blue;
//     this->fixture->RGBWout[W] = this->white;
// }


/* --------------------------------------------------------------------
   _____ _____   ____ _______    _____            _____ _  __ _____ 
  / ____|  __ \ / __ \__   __|  |  __ \     /\   / ____| |/ // ____|
 | (___ | |__) | |  | | | |     | |__) |   /  \ | |    | ' /| (___  
  \___ \|  ___/| |  | | | |     |  _  /   / /\ \| |    |  <  \___ \ 
  ____) | |    | |__| | | |     | | \ \  / ____ \ |____| . \ ____) |
 |_____/|_|     \____/  |_|     |_|  \_\/_/    \_\_____|_|\_\_____/ 

/ ----------------------------------------------------------------------- */
SpotRack front_rack(spot_vec{&spot_1, &spot_2, &spot_3, &spot_4, &spot_5, &spot_6}, "Front Rack");
SpotRack back_rack(&spot_g, &spot_d, "Back Rack");

void SpotRack::init(){
    this->rack_size = this->spots.size();
    // log(1, "Rack initialized with ", fcn::num_to_str(this->rack_size).data(), " spots !");

    //this->animations.push_back();
    // Animation 1 : Backgrnd color + random soft flashes
    this->animations.push_back(new SpotFrontAnimation1(this, black,         black,       8000, 1000,   " ", "FR.0.0"));

    // SpotFrontAnimation1(SpotRack *f, DMX_vec c1, DMX_vec c2, int pmax, int pmin, int prand, int flen, std::string d, std::string i)
    this->animations.push_back(new SpotFrontAnimation1(this, purple,    gold,   2500, 1000,   "Purple background / gold flashes",    "FR.1.1.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, sodium,    white,  2500, 1000,   "Orange background, white flashes",    "FR.1.1.2"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,       blue,   2500, 1000,   "Red background, Blue flashes",        "FR.1.1.3"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,       red,    2500, 1000,   "Red background, RED flashes",         "FR.1.1.4"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,       gold,   2500, 1000,   "Red background gold flashes",         "FR.1.1.5"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,       gold,   1000, 1000,   "Red background fast gold flashes",         "FR.1.1.5.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,       white,  2500, 1000,   "Red background, white flashes",       "FR.1.1.6"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,       white,  1000, 1000,   "Red background, fast white flashes",  "FR.1.1.6.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, pink,      cyan,   2500, 1000,   "Purple background, Cyan flashes",     "FR.1.1.7"));

    this->animations.push_back(new SpotFrontAnimation1(this, black,         white,  2500, 1000,   "Black background, White flashes",      "FR.1.2.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, black,         white,  1000, 600,    "Black background, fast White flashes", "FR.1.2.1.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, black,         red,    2500, 1000,   "Black background, Red flashes",        "FR.1.2.2"));
    this->animations.push_back(new SpotFrontAnimation1(this, black,         blue,   2500, 1000,   "Black background, Blue flashes",       "FR.1.2.3"));
    this->animations.push_back(new SpotFrontAnimation1(this, black,         orange, 2500, 1000,   "Black background, Orange flashes",     "FR.1.2.4"));
    this->animations.push_back(new SpotFrontAnimation1(this, black,         gold,   2500, 1000,   "Black background, GOLD flashes",       "FR.1.2.5"));
    this->animations.push_back(new SpotFrontAnimation1(this, black,         gold,   1000, 600,    "Black background, fast GOLD flashes",  "FR.1.2.5.1"));

    this->animations.push_back(new SpotFrontAnimation1(this, sodium,   black,  2500, 2000,   "Sodium background, Black holes",  "FR.1.3.1"));
    this->animations.push_back(new SpotFrontAnimation1(this, red,      black,  2500, 2000,   "Red background, Black holes",     "FR.1.3.2"));
    this->animations.push_back(new SpotFrontAnimation1(this, purple,   black,  2500, 2000,   "Purple background, Black holes",  "FR.1.3.3"));

    // Animation 2: Monochrome Stroboscope
    // this->animations.push_back(new SpotFrontAnimation2(this, WHITE(255),  255,          "white, max strobe",   "FR.2.1.00"));
    this->animations.push_back(new SpotFrontAnimation2(this, white,  STRB_FASTEST, "white, very fast strobe",   "FR.2.1.0"));
    this->animations.push_back(new SpotFrontAnimation2(this, white,  STRB_FAST,    "white, fast strobe",   "FR.2.1.1"));
    this->animations.push_back(new SpotFrontAnimation2(this, white,  STRB_MED,     "white, medium strobe", "FR.2.1.2"));
    this->animations.push_back(new SpotFrontAnimation2(this, white,  STRB_SLOW,    "white, slow strobe",   "FR.2.1.3"));

    this->animations.push_back(new SpotFrontAnimation2(this, red,    STRB_FAST,    "red, fast strobe",     "FR.2.2.1"));
    this->animations.push_back(new SpotFrontAnimation2(this, red,    STRB_MED,     "red, medium strobe",   "FR.2.2.2"));
    this->animations.push_back(new SpotFrontAnimation2(this, red,    STRB_SLOW,    "red, slow strobe",     "FR.2.2.3"));
    this->animations.push_back(new SpotFrontAnimation2(this, gold,   STRB_FAST,    "gold, fast strobe",    "FR.2.3.1"));
    this->animations.push_back(new SpotFrontAnimation2(this, gold,   STRB_MED,     "gold, medium strobe",  "FR.2.3.2"));
    this->animations.push_back(new SpotFrontAnimation2(this, gold,   STRB_SLOW,    "gold, slow strobe",    "FR.2.3.3"));
    
    this->activate_by_ID("FR.0.0");
}

void SpotRack::init_back(){
    this->rack_size = this->spots.size();
    //this->animations.push_back();
}

DMX_vec SpotRack::RGBW(simpleColor c, int intensity){
    switch (c)
    {
    case black:
        return fcn::RGBW_norm(DMX_vec{0,0,0,0}, intensity);
        break;
    case red:
        return fcn::RGBW_norm(DMX_vec{255,0,0,0}, intensity);
        break;
    case green:
        return fcn::RGBW_norm(DMX_vec{0,255,0,0}, 161.0/255*intensity);
        break;
    case blue:
        return fcn::RGBW_norm(DMX_vec{0,0,255,0}, 190.0/255*intensity);
        break;
    case yellow:
        return fcn::RGBW_norm(DMX_vec{255,90,0,0}, intensity);
        break;
    case orange:
        return fcn::RGBW_norm(DMX_vec{255,40,0,0}, intensity);
        break;
    case sodium:
        return fcn::RGBW_norm(DMX_vec{255,20,0,0}, intensity);
        break;
    case cyan:
        return fcn::RGBW_norm(DMX_vec{0,219,255,0}, 180.0/255*intensity);
        break;
    case purple:
        return fcn::RGBW_norm(DMX_vec{150,0,255,0}, intensity);
        break;    
    case magenta:
        return fcn::RGBW_norm(DMX_vec{255,0,240,0}, intensity);
        break;
    case pink:
        return fcn::RGBW_norm(DMX_vec{255,0,100,0}, intensity);
        break;
    case white:
        return fcn::RGBW_norm(DMX_vec{0,0,0,255}, 200.0/255*intensity);
        break;
    case gold:
        return fcn::RGBW_norm(DMX_vec{255,40,0,100}, intensity);
        break;
    default:
        break;
    }
}

// -----------------------------------
// FRONTAL RACK of SPOT Animations
// -----------------------------------
// 1 ---------------------------------
void SpotFrontAnimation1::init(){
    BaseAnimation::init();
    this->fixture->reset_spots();

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
    BaseAnimation::new_frame();

    long t = frame.t_current_ms;       // for readability
    int n_spot = this->fixture->rack_size;   // for readability
    
    // update 5 sinewaves of different period
    vector<double> s = {sin(2*M_PI*t/p_ms[0]), sin(2*M_PI*t/p_ms[1]), sin(2*M_PI*t/p_ms[2]), sin(2*M_PI*t/p_ms[3]), sin(2*M_PI*t/p_ms[4]) };
    
    // for each spot "i" of the rack
    for (int i_spot=0; i_spot < n_spot; i_spot++){
        DMX_vec backgd_RGBW(4);        
        // compute the background color values : 
            backgd_RGBW[R] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[R] * (1 + fluct_col*s[(i_spot+0)%5]))  ,0),255);
            backgd_RGBW[G] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[G] * (1 + fluct_col*s[(i_spot+1)%5]))  ,0),255);
            backgd_RGBW[B] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[B] * (1 + fluct_col*s[(i_spot+2)%5]))  ,0),255);
            backgd_RGBW[W] = min(max(    (int) (  (1 + fluct_int*s[(i_spot+4)%5]) * this->back_color[W] * (1 + fluct_col*s[(i_spot+3)%5]))  ,0),255);
        // ------------------------------- limit to 0-255 ---------------- Spot Intensity    *  RGBW pixel intensity                            ;
        
        // compute the flash = exp( -(spd.(t-t0))²)
            // when the flash passes, compute the next flash timestamp and update prev flash

            if (t > this->t_next[i_spot]){

                this->t_prev[i_spot] = this->t_next[i_spot];
                this->t_next[i_spot] = this->t_next[i_spot] + rand_min_max(this->flash_len, 2*n_spot*this->rand_const_ms);
            }

            int t_next = this->t_next[i_spot];        // for readability
            int t_prev = this->t_prev[i_spot];        // for readability  
            
            double flash_intensity = exp( -pow(2.5/this->flash_len*(t - t_prev), 2)) + exp( -pow(2.5/this->flash_len*(t - t_next), 2));

            this->fixture->spots[i_spot]->RGBWout[R] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[R] + flash_intensity * this->flash_color[R]  ),0),255); 
            this->fixture->spots[i_spot]->RGBWout[G] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[G] + flash_intensity * this->flash_color[G]  ),0),255);
            this->fixture->spots[i_spot]->RGBWout[B] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[B] + flash_intensity * this->flash_color[B]  ),0),255);
            this->fixture->spots[i_spot]->RGBWout[W] = min(max( (int)( (1.0-flash_intensity) * backgd_RGBW[W] + flash_intensity * this->flash_color[W]  ),0),255);
    }
}

// -----------------------------------
// 2 ---------------------------------
void SpotFrontAnimation2::shake(){  //randomizes the strob speeds on request
    for (DMX_vec::iterator spd = this->strobe_spds.begin(); spd != this->strobe_spds.end(); spd++){
        (*spd) = (strobe_min<strobe_max)? rand_min_max( this->strobe_min , this->strobe_max ) : this->strobe_max; // initialize each strobe with a slightly different frequency
        log(1, "Min:", fcn::num_to_str(strobe_min), " Max:", fcn::num_to_str(strobe_max), " picked", fcn::num_to_str((*spd)));

    }
}

void SpotFrontAnimation2::init(){
    BaseAnimation::init();

    this->t_next_shake = frame.t_current_ms + 2000;
    this->shake();

    log(1, "Min:", fcn::num_to_str(strobe_min), " Max:", fcn::num_to_str(strobe_max));

}

void SpotFrontAnimation2::new_frame(){
    BaseAnimation::new_frame();
    
    // for readability
    spot_vec spots = this->fixture->spots;
    int n_spots = spots.size();
    unsigned long t = frame.t_current_ms;

    if (((long)frame.t_current_ms - (long)this->t_next_shake) > 0){
        this->shake();
        this->t_next_shake += 2000; 
    }
    for (int i = 0; i<n_spots; i++){
        spots[i]->RGBWout  = this->fixture->RGBW(this->color);

        spots[i]->strobe = (int)(this->strobe_spds[i]); // min(max( (int)(this->strobe_spds[i] * (1 + delta*sin(i*M_PI/3 + 2*M_PI*t/3000)))  ,0),255);
        // spots[i]->strobe = min(max( rand_min_max(this->strobe_spds[i] * (1-delta) , this->strobe_spds[i] * (1+delta))  ,0),255);
    }
}