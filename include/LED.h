#ifndef LED_H
#define LED_H


#define LEDCh0          1

// PCA9685 channel (0-15) for each color
#define LEDRed    15
#define LEDGreen  14
#define LEDBlue   13

class LEDFixture{
    // Channels :
    uint8_t MASTER_DIMMER = 255;      // Master Dimmer from 0-255
    int RGB[3];                 // ={R,G,B} Values from 0-4095
};

void LED_init();
void rgb_color(int, int, int);


#endif // !LED_H
