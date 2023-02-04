#include <iostream>
#include <math.h>
#include <sysfcn.h>

using namespace std;

void test_map(){
    for (int i=0; i<10; i+=2){
        std::cout << i << " -> " << map(i, 0, 10, 3, 5) << std::endl;
    }
}

void test_millis(){
    sysfcn_init();

    while (millis()<5000){
        std::cout << "t = " << millis()/1000.0 << "s" << std::endl;
    }
}

void test_rand_min_max(){
    for (int i=0; i<20; i++){
        std::cout << rand_min_max(0,100) << std::endl;
    }
}

int static_cpt(){
    static int i = 5;
    ++i;
    return i;
}

void test_static_cpt(){
    for (int i=0; i<20; i++){
        int cpt = static_cpt();
        std::cout << cpt << std::endl;
    }
}

void test_unary_operator(){
    double x;
    for (int i=0; i<10; i++){
        x += 0.5;
        std::cout << x << std::endl;
    }
}


void test_dmx_framerate(){
    int r,g,b;
    int T = 5000;

    r = 255 * (1.0+sin(2*M_PI*millis()/T)) / 2;
    g = 255 * (1.0+sin(2*M_PI*millis()/T + 2*M_PI/3)) / 2;
    b = 255 * (1.0+sin(2*M_PI*millis()/T + 4*M_PI/3)) / 2;
}









int main(){
// MANDATORY ------------------------
// initialize the sysfcn lib    
    sysfcn_init();

// TESTS ----------------------------

// sysfcn.h :
    // test de map()
    // test_map();
    // test de milis()
    // test_millis();
    // test de rand_min_max()
    // test_rand_min_max();


// other
    //test_static_cpt();
    test_unary_operator();
}

