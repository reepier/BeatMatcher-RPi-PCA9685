#include <ctime>
#include <sys/time.h>
#include <sysfcn.h>
#include <stdlib.h>

// args : x, x1, x2, y1, y2 (from x1-x2 to  y1-y2)
int map(int x, int x1, int x2, int y1, int y2){
    float a = (float)(y2-y1)/(float)(x2-x1);
    float b = (float)y1 - a*x1;

    return (int)(a*x+b);
}

float map(float x, float x1, float x2, float y1, float y2){
    float a = (y2-y1)/(x2-x1);
    float b = y1 - a*x1;

    return a*x+b;
}


int rand_min_max(int min, int max){
    int x = rand() % (max-min) + min;
    return x;
}