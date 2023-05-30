#include <iostream>
#include <cmath>
#include <fstream>

#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/client/StreamingClient.h>
#include <wiringPi.h>

#include "constant.h"
#include "LED.h"
#include "sysfcn.h"
#include "animator.h"

#include <PCA9685.h>


LEDFixture led;


// ------------------------------------------------------------
// LED FIXTURE CLASS Function definition

// Fixture initalizer
void LEDFixture::LED_init(){

    #ifndef PINAKED
    // intialize hardware output
    _PCA9685_DEBUG = 0;
    _PCA9685_TEST = 0;

    fd = PCA9685_openI2C(1, addr);
    PCA9685_initPWM(fd, addr, _PCA9685_MAXFREQ);

    #endif // DEBUG

    ola_client.Setup();
    ola_buffer.Blackout();


    animations.push_back(Flash_Back(255<<4, 150<<4, 80<<4,     30<<4,100<<4, 1<<4,7<<4, 0<<4,0<<4,"Warm White Flashes, Red/orange background"));
    animations.push_back(Flash_Back(255<<4, 50<<4, 10<<4,      15<<4,50<<4, 0<<4,5<<4, 0<<4,0<<4, "Sodium Flashes, Red/orange background"));
    animations.push_back(Flash_Back(255<<4, 0<<4, 0<<4,        0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4, "Red flashes, Black background"));
    animations.push_back(Flash_Back(255<<4, 150<<4, 80<<4,     30<<4,100<<4, 0<<4, 0<<4, 0<<4,10<<4, "Warm White flashes, Red/Pink background"));
    animations.push_back(Flash_Back(0<<4, 0<<4, 255<<4,        0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4, "Blue flashes, Black background"));
    animations.push_back(Flash_Back(255<<4, 100<<4, 80<<4,     0<<4,80<<4, 0<<4,0<<4, 0<<4,20<<4, "Warm White flashes, Pink background"));
    animations.push_back(Flash_Back(255<<4, 100<<4, 80<<4,     0<<4,50<<4, 0<<4,0<<4, 0<<4,80<<4, "Warm White flashes, Purple background"));
    animations.push_back(Flash_Back(255<<4, 100<<4, 80<<4,     0<<4,20<<4, 0<<4, 0<<4, 0<<4,100<<4, "Warm White flashes, Blue/Purple backgroud"));
    animations.push_back(Flash_Back(255<<4, 100<<4, 80<<4,     0<<4,10<<4, 0<<4,10<<4, 0<<4,100<<4, "Warm White flashes, cyan background"));    
    animations.push_back(Flash_Back(255<<4, 100<<4, 80<<4,     0<<4,0<<4, 0<<4,0<<4, 0<<4,0<<4, "White flashes, Black background"));

    active_animation = animations[animator.animation_i].get_ptr();
}

 
// This function sends RGB values to the LED controler via I2C
void LEDFixture::send(){
    
    // Send frame to the PCA9685 module
    // Take into account the MASTER DIMMER value !! --> as late as possible, right before data is sent
    setOffVals[LEDRed] = RGB[R] * MASTER_DIMMER/255.0;
    setOffVals[LEDGreen] = RGB[G] * MASTER_DIMMER/255.0;
    setOffVals[LEDBlue] = RGB[B] * MASTER_DIMMER/255.0;

    #ifndef PINAKED
    PCA9685_setPWMVals(fd, addr, setOnVals, setOffVals);
    #endif // DEBUG

    // send DMX frame to OLA server.
    uint8_t data[] = {MASTER_DIMMER, RGB[R]>>4, RGB[G]>>4, RGB[B]>>4};
    // ola_buffer.SetChannel(0, 255);
    ola_buffer.SetRange(0, data, 4);
    ola_client.SendDmx(1, ola_buffer);
}




// ----------------------------------------------------------
// ANIMATION CLASS Function definition
// Animation constructor
Flash_Back::Flash_Back(int flash_r, int flash_g, int flash_b, int back_rmin, int back_rmax, int back_gmin, int back_gmax, int back_bmin, int back_bmax, std::string descr){
    
    this->flash_RGB[R] = flash_r;
    this->flash_RGB[G] = flash_g;
    this->flash_RGB[B] = flash_b;

    this->backgd_RGB_minmax[0] = back_rmin;
    this->backgd_RGB_minmax[1] = back_rmax;
    this->backgd_RGB_minmax[2] = back_gmin;
    this->backgd_RGB_minmax[3] = back_gmax;
    this->backgd_RGB_minmax[4] = back_bmin;
    this->backgd_RGB_minmax[5] = back_bmax;

    this->description = descr;
}

// Animation initializer
void Flash_Back::init(){

    periods_ms[0] = 1000*rand_min_max(MIN_T, MAX_T);
    periods_ms[1] = 1000*rand_min_max(MIN_T, MAX_T);
    periods_ms[2] = 1000*rand_min_max(MIN_T, MAX_T);
    periods_ms[3] = 1000*rand_min_max(MIN_T, MAX_T);
    periods_ms[4] = 1000*rand_min_max(MIN_T, MAX_T);
    periods_ms[5] = 1000*rand_min_max(MIN_T, MAX_T); 
}


// Animation main function --> returns the color to display
/** Computes the RGB values to send to the led display based on :
 * @param t : t current time 
 * @param t_last_beat_ms : timestamp of the last beat detected 
 * @param flash : if true, the function will display a bright flash for every beat
 * @param fade_rate_ms : duration of the flash's exponential decay */
std::vector<int> Flash_Back::new_frame(unsigned long t, unsigned long t_last_beat_ms, bool flash){
    std::vector<int> frame;//(3);
    frame.reserve(3);

    int backgd_color[3];

    backgd_color[R] = (backgd_RGB_minmax[0]+backgd_RGB_minmax[1])/2 
                        + (backgd_RGB_minmax[1]-backgd_RGB_minmax[0])/4 * (sin(2*3.14*t/periods_ms[0])+sin(2*3.14*t/periods_ms[1]));
    backgd_color[G] = (backgd_RGB_minmax[2]+backgd_RGB_minmax[3])/2 
                        + (backgd_RGB_minmax[3]-backgd_RGB_minmax[2])/4 * (sin(2*3.14*t/periods_ms[2])-sin(2*3.14*t/periods_ms[3]));
    backgd_color[B] = (backgd_RGB_minmax[4]+backgd_RGB_minmax[5])/2 
                        + (backgd_RGB_minmax[5]-backgd_RGB_minmax[4])/4 * (sin(2*3.14*t/periods_ms[4])-sin(2*3.14*t/periods_ms[5]));          

    float coef = exp(-(double)(t-t_last_beat_ms)/fade_rate);
    if (flash){
        frame[R] = backgd_color[R] + coef*(flash_RGB[R]-backgd_color[R]); 
        frame[G] = backgd_color[G] + coef*(flash_RGB[G]-backgd_color[G]); 
        frame[B] = backgd_color[B] + coef*(flash_RGB[B]-backgd_color[B]);
    }
    else{
        frame[R] = backgd_color[R];
        frame[G] = backgd_color[G];
        frame[B] = backgd_color[B];
    }

    return frame;
}

void Flash_Back::display_anim(){
    std::cout << this->description << std::endl; 
    std::cout << "Flash color (R,G,B) : " << this->flash_RGB[R] << " / " << this->flash_RGB[R] << " / " << this->flash_RGB[R] << std::endl;

}

Flash_Back* Flash_Back::get_ptr(){
    return this;
}