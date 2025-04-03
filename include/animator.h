#pragma once

#include <wiringPi.h>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <random>
#include <unordered_set>

#include "commonTypes.h"
#include "debug.h" 
#include "sysfcn.h"
#include "music.h"


/** -----------------------------------
#######                                                   
#       #    # #    #  ####  ##### #  ####  #    #  ####  
#       #    # ##   # #    #   #   # #    # ##   # #     
#####   #    # # #  # #        #   # #    # # #  #  ####  
#       #    # #  # # #        #   # #    # #  # #      # 
#       #    # #   ## #    #   #   # #    # #   ## #    # 
#        ####  #    #  ####    #   #  ####  #    #  ####  
-----------------------------------                 */
namespace fcn{
  /* returns a normalized 4 (or 3 for RGB) channel DMX vector based on color literal 
  if intensity = -1, the normalization is disabled*/

  
  // returns a NORMALIZED 4 (or 3 for RGB) channel DMX vector based on a DMX_vector and a DMX vlue (0-255)
  template<typename T>
  std::vector<T> RGBW_norm(std::vector<T> rgbw, int intensity=255){
    const int size = rgbw.size();
    std::vector<T> ret(size);
    
    int max = 0;
    int sum = 0;
    for (int i=0; i<size; i++){
        sum += rgbw[i];
        max = rgbw[i]>max ? rgbw[i] : max;
    }

    double max_gain = max!=0 ? 255.0/max : 0;
    double gain = (intensity==-1) ? max_gain : (double)intensity/sum;
    gain = gain>max_gain? max_gain : gain;

    for (int i=0; i<size; i++){
        ret[i] = gain*rgbw[i];
    }
    return ret;
  }

  template<typename T>
  std::vector<T> RGB_norm(std::vector<T> rgb, int intensity=255){
    return fcn::RGBW_norm(rgb, intensity);
  }
  
  std::string vec_to_str(DMX_vec, char);
  std::string vec_to_str(int_vec, char);
  std::string vec_to_str(str_vec, char);

  std::string palette_to_string(color_vec, char sep='/');

  std::string num_to_str(int);
  std::string num_to_str(time_t);
  std::string num_to_str(uint8_t);
  std::string num_to_str(double);
  std::string ms_to_hhmmss(time_ms);
  std::string ms_to_hhmmssms(time_ms);

  
  int_vec convert_8_to_12bits(DMX_vec);

  /*shape functions*/

  // SINGLE BURSTS
  //exponential decay
  inline double exp_decay(time_ms t, time_ms t0, time_ms period, double min, double max){
    return min + (max-min)*std::exp((t0-t)/(double)period);
  }

  // pure gaussian shape -> exp(-x²/2)
  inline double gaussian(time_ms t, time_ms t0, time_ms period, double min, double max){
      double sigma = period/3.0;
      // return min + (max-min)*std::exp( -std::pow((t-t0)/sigma, 2)/2 );

      double x = ((int)t-(int)t0)/sigma;
      return min + (max-min)*std::exp( -std::pow(x, 2)/2 ); 
  }

  // squared gaussian shape -> exp(-x⁴/4) (longer plateau, steeper slopes)
  inline double gaussian2(time_ms t, time_ms t0, time_ms period, double min, double max){ 
    double sigma = period/3.0;
    double x = ((int)t-(int)t0)/sigma;
    // return min + (max-min)*std::exp( -std::pow((t-t0)/sigma, 4)/4 );
    return min + (max-min)*std::exp( -std::pow(x, 4)/4 );
  }

  inline double square(time_ms t, time_ms t0, time_ms period, double min, double max, double alpha=0.5){
    if ( t > t0-alpha*period  &&  t < t0+(1-alpha)*period ) {return max;}
    else {return min;}
  }
  
  inline double triangle(time_ms t, time_ms t0, time_ms period, double min, double max, double alpha=0.5){
    double x = ( (int)t-(int)t0 ) / (double)period;
    // cout << "\tt:"<<(int)t<< "\tt0:"<<(int)t0<< "\tT:"<<(int)period<< "\ta:"<<alpha<< "\tx:"<<x<<endl;

    if ( -alpha <= x  &&  x <= 0  ){
    //   std::cout<<"mark1: " << -alpha << " "<< x << " "<< 0 << " " << endl; 
        return map(x, -alpha, 0.0, (double)min, (double)max);
    }
    else if (0 < x  &&  x <= 1-alpha ){
    //   std::cout<<"mark2: " << 0 << " "<< x << " "<< 1-alpha << " " << endl;
        return map(x, 0.0, 1.0-alpha, (double)max, (double)min);
    }
    else {
    //   std::cout<<"mark3: " << endl;
        return min;
    }
  }

  // PERIODIC FUNCTIONS
  //sine wave
  inline double sin_wave(time_ms t, time_ms period, double min, double max, double phase = 0){
    return (max+min)/2 + (max-min)/2*std::sin(2*M_PI*t/period + phase);
  }
  //triangular wave
  inline double triangle_wave(time_ms t, time_ms period, double min, double max, double alpha = 0.5, double phase = 0){
    if (alpha>1.0){alpha = 1.0;}
    else if (alpha < 0.0){alpha = 0.0;}

    double t_prime = (t+phase/2.0/M_PI*period) / period;
    t_prime = t_prime - (int)t_prime;

    if (t_prime<alpha)  {return (double)map(t_prime, 0.0, alpha, min, max);}
    else                {return (double)map(t_prime, alpha, 1.0, max, min);}
  }
  //square wave
  inline double square_wave(time_ms t, time_ms period, double min, double max, double alpha = 0.5, double phase = 0){
    if (alpha>1.0){alpha = 1.0;}
    else if (alpha < 0.0){alpha = 0.0;}

    double t_prime = (t+phase/2.0/M_PI*period) / period;
    t_prime = t_prime - (int)t_prime;

    if (t_prime<alpha)  {return min;}
    else                {return max;}
  }

  // RANDOM generation functions
  template<class T>
  T random_pick(std::vector<T> vals, int_vec proba_vec = {}){
    int n = vals.size();

    if (n == 0){
      // log(1, "Empty list of values");
      return (T)0;
    }
    else if (n==1) {
      // log(1, "Single value passed");
      return vals[0];
    }

    if (proba_vec.size() == 0){
      // log(1, "No probability passed --> equipr.");
      proba_vec.resize(n, 1); // if proba is not passed as an argument, default to equiprobability
    }else if (proba_vec.size() != n){ // if proba vector does not match value vector in size, return & log.
      // log(1, "Proba size differs from vals size !!");
      return (T)0;
    }

    int proba_sum = 0;
    for (int i=0; i<proba_vec.size(); i++){
      proba_sum += proba_vec[i];
    }
    
    int_vec proba_scale = {proba_vec[0]};
    for (int i=1; i<n; i++){
      proba_scale.push_back(proba_scale[i-1] + proba_vec[i]);
    }
    int pick = rand_min_max(0, proba_sum);

    for (int i=0; i<n; i++){
      if (pick < proba_scale[i]){
        // log(2, "proba_sum:", proba_sum," pick:", pick, " clor:", colorName[(int)vals[i]]);
        return vals[i];
      }
    }

    return (T)0;    //TODO bellec ce cast est bancale AF
  }

  template<class T>
  std::vector<T> randomized_vector(std::vector<T> v){
    std::vector<T> out_vec = v;
    std::random_device rd;
    std::mt19937 rng(rd());

    shuffle(v.begin(), v.end(), rng);
    return v;
  }

  template<typename T>
  T random_walk(T input, T max_incr, T floor, T roof){
    T output = std::min(roof, std::max(floor, input + rand_min_max(-max_incr, max_incr)));
    return output;
  }
 

  // Color functions
  // check wether color palettes cp1 and cp2 have at least n color in common
  inline bool are_consistent(color_vec cp1, color_vec cp2, int n = 1){
    int common_col = 0;
    for (auto c1 : cp1){
      for (auto c2 : cp2){
        if (c1 == c2)
          common_col++;
      }
    }

    return common_col>=n;
  }



  //TODO define function that takes in 2 vectors and combine them using different rules (intersection, exclusion, etc.)
  /* returns a vector containing only the common elements between v1 and v2 */
template<class T>
std::vector<T> get_vector_intersection(const std::vector<T>& v1, const std::vector<T>& v2) {
    // Special case: If v2 is empty, return an empty vector
    if (v2.empty()) {
        return v1;
    }

    // Use an unordered_set for fast lookup (O(1) average time complexity)
    std::unordered_set<T> v2_set(v2.begin(), v2.end());
    std::vector<T> vres;

    // Find common elements
    for (const auto& item : v1) {
        if (v2_set.count(item)) {
            vres.push_back(item);
            v2_set.erase(item); // Ensure uniqueness in the output
        }
    }

    return vres;
}

  /*returns a vetor containings every elements from v1 except those present in v2 (purges v1 from elements of v2)*/
template<class T>
std::vector<T> get_vector_exclusion(const std::vector<T>& v1, const std::vector<T>& v2) {
    std::unordered_set<T> v2_set(v2.begin(), v2.end()); // Store v2 for fast lookup
    std::vector<T> vres = v1;

    std::erase_if(vres, [&v2_set](const T& item) {
        return v2_set.contains(item); // Remove if item is in v2
    });

    return vres;
}


} /*End of namespace fcn*/

class ColorPaletteMagazine{
  public:
    std::vector<color_vec>   color_palettes;
    int_vec     probas;

    void push_back(color_vec palette, int proba){
        color_palettes.push_back(palette);
        probas.push_back(proba);
    }

    int size(){return color_palettes.size();}
    
    //returns a random palette within the magasine (weighed by proba)
    color_vec get_random_palette(){return fcn::random_pick(color_palettes, probas);}
    
    // returns a palette with at least 1 common color with the palette passed as argument (wweighed by prba if several candidates exist)
    color_vec get_similar_palette(color_vec current_palette){
      
      if (current_palette.size()==0){
        return this->get_random_palette();
      }else{

        //list candidates
        ColorPaletteMagazine candidates;
        for (int i = 0; i<this->size(); i++){
          if (fcn::are_consistent(this->color_palettes[i], current_palette)){
            candidates.push_back(this->color_palettes[i], this->probas[i]);
          }
        }
        // choses randomly taking proba into account
        if (candidates.size() !=0 ){
          return candidates.get_random_palette();
        }else{
          log(1, "No similar color palette exist... ", fcn::palette_to_string(current_palette, '/'));
          return this->get_random_palette();
        }
      }
    }

    color_vec get_similar_palette(){
      return this->get_random_palette();
    }

    // TODO do not return the same colorpalette as the one passed as argument
    //    -> worst case, return a random animation to get out of the color well
};


/**-------------------------------------------------------------------------------------------
   #                                                    #     #               
  # #   #    # # #    #   ##   ##### #  ####  #    #    ##   ##  ####  #####  
 #   #  ##   # # ##  ##  #  #    #   # #    # ##   #    # # # # #    # #    # 
#     # # #  # # # ## # #    #   #   # #    # # #  #    #  #  # #      #    # 
####### #  # # # #    # ######   #   # #    # #  # #    #     # #  ### #####  
#     # #   ## # #    # #    #   #   # #    # #   ##    #     # #    # #   #  
#     # #    # # #    # #    #   #   #  ####  #    #    #     #  ####  #    # 

------------------------------------------------------------------------------- */
/**
 * class AnimationManager is the entity responsible for determining which animation every 
 * fixture should run, based on the musical analysis
*/
class AnimationManager{
  public :
    bool flash = true;
    time_t timer_start_ms = 0, timer_end_ms=0, timer_duration_ms = 0;
    unsigned long t_last_change_ms = millis();   //timestamp of last switch between aniamtions
    ColorPaletteMagazine palette_magasine, palette_magasine_2, test_palette;
    color_vec controler_main_palette = color_vec{}; 

    void init();

    void random_update();
    void palette_update();
    void autocolor_update();
    void show_update();
    void nov30_maximum_update();
    bool test_animation();
    bool controled_update();
  
    void set_timer(time_t);
    void reset_timer();
    bool timer_elapsed();
};

extern AnimationManager animator;


/** ----------------------------------------------------------
######                          #######                                     
#     #   ##    ####  ######    #       # #    # ##### #    # #####  ###### 
#     #  #  #  #      #         #       #  #  #    #   #    # #    # #      
######  #    #  ####  #####     #####   #   ##     #   #    # #    # #####  
#     # ######      # #         #       #   ##     #   #    # #####  #      
#     # #    # #    # #         #       #  #  #    #   #    # #   #  #      
######  #    #  ####  ######    #       # #    #   #    ####  #    # ###### 
 --------------------------------------------------------------- */
// Generic (core) description of a fixture (later derived into specific classes)
class BaseFixture{
  public:
    // Generic attributes
    std::string name;                   // 
    std::string description;            // textual description
    int id;                             // unique id to differentiate between vseveral fixtres of the same type (i.e. COTS PAR spots & racks)

    // DMX related parameters
    uint8_t master = 255;           // Master Dimmer from 0-255
    int address;                    // DMX address
    bool b_blackout;
    const int nCH;

    // DMX Controler parameters
    color_vec external_palette;     // this color palette is defined (or not) by the external controler 
    int       external_animation;   // stores external animation commands
    
    // Animations catalog
    BaseAnimation * active_animation = nullptr;

    anim_vec animations;

    //constructor (adresse [0-511], number of channels, fixture's name)
    BaseFixture(int addr,int ch, std::string nm, int i, uint8_t mast): address(addr), nCH(ch), name(nm), id(i), master(mast){};
    virtual void init()=0;

    //animation activation & management
    void blackout(bool);
    bool activate_none();
    bool activate_by_index(int), activate_by_index(int, const color_vec&);
    bool activate_random(bool include_black = true), activate_random(const color_vec&, bool include_black = true);
    bool activate_by_ID(std::string);
    bool activate_autocolor(color_vec&);
    virtual bool activate_by_color(color_vec, AnimationType arg_type = any); //additionnal argument to orient the activation toward a leading or backing aniation
    bool activate_by_ptr(BaseAnimation*), activate_by_ptr(BaseAnimation*, const color_vec&);
    
    //DMX output
    virtual int get_address() = 0;
    virtual int get_nCH()     = 0;
    virtual DMX_vec buffer()  = 0;

    virtual DMX_vec RGBW(simpleColor, int){}; // common (but overriden) function that returns a 4 RGBW vector based on standrad color input
    virtual DMX_vec RGB(simpleColor, int){};
};
/** Font : Old Banner
######                             #                                                 
#     #   ##    ####  ######      # #   #    # # #    #   ##   ##### #  ####  #    # 
#     #  #  #  #      #          #   #  ##   # # ##  ##  #  #    #   # #    # ##   # 
######  #    #  ####  #####     #     # # #  # # # ## # #    #   #   # #    # # #  # 
#     # ######      # #         ####### #  # # # #    # ######   #   # #    # #  # # 
#     # #    # #    # #         #     # #   ## # #    # #    #   #   # #    # #   ## 
######  #    #  ####  ######    #     # #    # # #    # #    #   #   #  ####  #    # 
*/

// Generic (core) description of an animation object
class BaseAnimation{
  public :
    std::string name;                   
    std::string description;            // textual description
    std::string id;                     // unique id
    AnimationType type = any;
    unsigned long t_animation_start_ms; // times at which the animation was last activated
    unsigned long frame_cpt;            // number of frame computed since activation
    color_vec color_palette;            // lists the colors used in the animation (initialized by constructor)
    int priority = 1;                  // weight on the priority list (animations with higher priority will be have higher chance of activation)
    uint8_t master = 255;

    bool autocolor = false;                       // defines wether the animation has predefiend color or autocolor
    color_vec authorized_color = {};              // list of authorized colors for autocolor (empty means all color OK==authorized)
    color_vec unauthorized_color = {};            // list of unauthorized colors for autocolor (empty means al color OK==authorized)
    color_vec* auto_color_palette = nullptr;      //pointer to the color palette used for automatic color definition (allows the use of multiple color palettes in the program) 

    //Base constructor
    BaseAnimation(){};
    BaseAnimation(std::string d, std::string i, AnimationType typ, uint8_t mast) : description(d),  id(i), type(typ), master(mast) {};

    bool is_monochrome(){return (color_palette.size() == 1);};
    bool is_first_frame(){return frame_cpt==0;};

    /*Determines whether or not the animation is compatible with autocolor & a specific color palette
    The criteria shall be simple / generic enough to be applicable to every fixture / animations :
      - is autocolor true ? 
      - do authorized color include all? some? of the passed color palette
      - are there any? too many? unauthorized color in the palette
      --> to start simple, only use the first criteria, //TODO improve later
      
    virtual function override might allow to refine this function for each individual animation*/
    virtual bool is_autocolor_compatible(const color_vec& palette){return this->autocolor;} 
    

    virtual void new_frame(){
      this->frame_cpt++;
    }
    virtual void init(){
      this->t_animation_start_ms = frame.t_current_ms;
      this->frame_cpt = 0;
    }
    virtual void init(const color_vec&){}; //special init() for AUTOCOLOR feature
     
     
    /** //TODO :
     * until now, every animation must be defined with a (very) specific set of (color, shape, time...) arguments. 
     * Basically every (interesting) parameter of the animation must be defined at construction. This is very time
     * consuming & inefficient since color are also defined in the color palette...
     * 
     * GOAL : use the current color palette (a selection of 1,2 or 3 matching colors) to set the animation colors at initialization.
     * This way,  the animation declaration only sets the cinematic & dynamic parameters (speed, shape, periods...), which will drastically 
     * reduce the volume of objects to declare
     * The main goal here is to simplify the configuraiton process. Indeed the current solution presents drawbacks :
     * - Show configuration is lengthy (creating new color means adding many lines to every fixture ini fcn)
     * - Multicolor animations are even more time consuming (more color combinations available)
     * -  
     * 
     * Limits :
     * The correct color finding algorithm must be found to avoid undiesrable effects :
     * - Bad color rendering when using complex colors for low intensity (i.e. Gold color for PAR LED background illumination)
     * 
     * Functionalities :
     * - the color definition happens in the Animation::init() function
     * - the color definition is based on a color palette 
     * - authorized & unauthorized colors can be defined manually (or not) 
     * - the color palette will then be defined with the following rules in mind :
     *    - color order matters : the first color will be used for dynamic/flash/bursts elements while the next for background/fix/slow elements
     * 
     * - display the palette (for each fixture ? globally ?) in the output console
     * 
     * Options :
     * - The nummber of color (1, 2 more?) or a range of color number could be set at animation construction (to allow or restrict
     *  multicolor mode animation per animation)
     * - Could be an opportunity to upgrade the color palette : instead of just declaring an array of colors, colors could be assigned for $
     * particular roles (flash, background, both, or else...)   
     *
     * 
     * */
    void update_palette(color_vec colors){
      for (color_vec::iterator new_c = colors.begin(); new_c != colors.end(); new_c++){
        // check if new color is not already stored in color_palette
        bool duplicate = false;
        for (color_vec::iterator stored_c = color_palette.begin(); stored_c != color_palette.end(); stored_c++){
          if ((*new_c) == (*stored_c)){
            duplicate = true;
          }
        }
        if ( (*new_c) != black && !duplicate){
          this -> color_palette.push_back((*new_c));
        }
      }
    }
    void update_palette(simpleColor color){
      update_palette(color_vec{color});
    }
};







/** Font : ANSI regular ---------------------------------------------------------
██████   █████  ███████ ███████      █████  ███    ██ ██ ███    ███  █████  ████████ ██  ██████  ███    ██ 
██   ██ ██   ██ ██      ██          ██   ██ ████   ██ ██ ████  ████ ██   ██    ██    ██ ██    ██ ████   ██ 
██████  ███████ ███████ █████       ███████ ██ ██  ██ ██ ██ ████ ██ ███████    ██    ██ ██    ██ ██ ██  ██ 
██   ██ ██   ██      ██ ██          ██   ██ ██  ██ ██ ██ ██  ██  ██ ██   ██    ██    ██ ██    ██ ██  ██ ██ 
██████  ██   ██ ███████ ███████     ██   ██ ██   ████ ██ ██      ██ ██   ██    ██    ██  ██████  ██   ████                                                                                               
*/

/** Font : BIG ---------------------------------------------------------
  ____                                  _                 _   _             
 |  _ \                     /\         (_)               | | (_)            
 | |_) | __ _ ___  ___     /  \   _ __  _ _ __ ___   __ _| |_ _  ___  _ __  
 |  _ < / _` / __|/ _ \   / /\ \ | '_ \| | '_ ` _ \ / _` | __| |/ _ \| '_ \ 
 | |_) | (_| \__ \  __/  / ____ \| | | | | | | | | | (_| | |_| | (_) | | | |
 |____/ \__,_|___/\___| /_/    \_\_| |_|_|_| |_| |_|\__,_|\__|_|\___/|_| |_|
                                                                            
--------------------------------------------------------------- */