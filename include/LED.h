#ifndef LED_H
#define LED_H


#define LyreCh0         31

#define LyrePan         1
#define LyreTilt1       2
#define LyreTilt2       3
#define LyreTilt3       4
#define LyreMaster      5
#define LyreStrobe      6
#define LyreRed         7
#define LyreGreen       8
#define LyreBlue        9
#define LyreWhite       10

#define LaserCh0        11

#define LEDCh0          1

// PCA9685 channel (0-15) for each color
#define LEDRed    15
#define LEDGreen  14
#define LEDBlue   13

// extern int color1[3];
// extern int color2[6];
// extern int color3[3];

void LED_init();
// void set_color(int rgb[], int c0=0, int c1=0, int c2=0, int c3=0, int c4=0, int c5=0);
void rgb_color(int, int, int);

// void flash_master(bool, unsigned long, bool, int fade_rate = 80);
// void flash_master_BS(int);

// void reset_period();

#endif // !LED_H
