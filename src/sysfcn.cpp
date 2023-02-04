#include <ctime>
#include <sys/time.h>
#include <sysfcn.h>
#include <stdlib.h>

unsigned long prog_start_us = 0;
void sysfcn_init(){
    // store the time (s since epoch) at which the program starts
    timeval t;
    gettimeofday(&t, nullptr);
    prog_start_us = t.tv_sec*1000000 + t.tv_usec;

    // seed the PRNG
    std::srand(time(NULL));
}

unsigned long millis(){
    return micros()/1000;
}

unsigned long micros(){
    timeval t;
    gettimeofday(&t, nullptr);
    return t.tv_sec*1000000 + t.tv_usec - prog_start_us;
}


int map(int x, int x1, int x2, int y1, int y2){
    float a = (float)(y2-y1)/(float)(x2-x1);
    float b = (float)y1 - a*x1;

    return (int)(a*x+b);
}

int rand_min_max(int min, int max){
    int x = rand() % (max-min) + min;
    return x;
}


/* TODO BETTER
     - replace gettimeofday() par time()

*/