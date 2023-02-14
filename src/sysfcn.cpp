#include <ctime>
#include <sys/time.h>
#include <sysfcn.h>
#include <stdlib.h>

int map(int x, int x1, int x2, int y1, int y2){
    float a = (float)(y2-y1)/(float)(x2-x1);
    float b = (float)y1 - a*x1;

    return (int)(a*x+b);
}

int rand_min_max(int min, int max){
    int x = rand() % (max-min) + min;
    return x;
}