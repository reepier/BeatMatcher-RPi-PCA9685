#include <iostream>
#include <math.h>
#include <vector>

#include "sysfcn.h"

using namespace std;

void test_map(){
    for (int i=0; i<10; i+=2){
        std::cout << i << " -> " << map(i, 0, 10, 3, 5) << std::endl;
    }
}

// void test_millis(){
//     sysfcn_init();

//     while (millis()<5000){
//         std::cout << "t = " << millis()/1000.0 << "s" << std::endl;
//     }
// }

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


// void test_dmx_framerate(){
//     int r,g,b;
//     int T = 5000;

//     r = 255 * (1.0+sin(2*M_PI*millis()/T)) / 2;
//     g = 255 * (1.0+sin(2*M_PI*millis()/T + 2*M_PI/3)) / 2;
//     b = 255 * (1.0+sin(2*M_PI*millis()/T + 4*M_PI/3)) / 2;
// }





int * return_array(){
    int out[3] = {10, 20, 30};
    return out;
}


class Animation{
  public:
    Animation();
    vector<int> frame();
    Animation * get_ptr();
};

Animation::Animation(){

}

vector<int> Animation::frame(){
    vector<int> out = {40,50,60};
    return out;
}

Animation * Animation::get_ptr(){
    return this;
}

class Fixture{
  public:
    vector<int> RGB;
    Animation * active_animation;
    vector<Animation> animations;
    void display_data();
};

void Fixture::display_data(){
    for(vector<int>::const_iterator it = RGB.begin(); it != RGB.end(); it++ ){
        cout << *it << " " ; 
    }
    cout << endl;
}



int main(){
// MANDATORY ------------------------
// initialize the sysfcn lib    
    // sysfcn_init();

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
    // test_unary_operator();

// vector
    // cout << "TEST VECTORS" << endl;
    // vector<int> v1 = {1,2,3};
    // vector<int> v2 = {0,0,0}; 
    // vector<int> v3;

    // cout<< v1[0] << " " << v1[1] << " " << v1[2] <<endl;
    // cout<< v2[0] << " " << v2[1] << " " << v2[2] <<endl;
    // // cout<< v3[0] << " " << v3[1] << " " << v3[2] <<endl;

    // v2 = v1;                // OK
    // v3 = return_vector();   // OK
    // v2 = {7,8,9};           // OK

    // cout<< v1[0] << " " << v1[1] << " " << v1[2] <<endl;
    // cout<< v2[0] << " " << v2[1] << " " << v2[2] <<endl;
    // cout<< v3[0] << " " << v3[1] << " " << v3[2] <<endl;

    // cout << "TEST ARRAYS" << endl;
    // int a1[3] = {1,2,3};
    // int a2[3] = {0};
    // int a3[3] = {0};

    // cout << a1[0] << " " << a1[1] << " " << a1[2] << endl;
    // cout << a2[0] << " " << a2[1] << " " << a2[2] << endl;
    // cout << a3[0] << " " << a3[1] << " " << a3[2] << endl;
    
    // int *a4;
    // a4 = return_array();
    // cout << a4 ;// << " " << *(a4+1) << " " << *(a4+2) << endl;

    Fixture obj;
    obj.animations.push_back(Animation());
    obj.animations.push_back(Animation());
    obj.animations.push_back(Animation());

    obj.active_animation = obj.animations[2].get_ptr();

    obj.RGB = obj.active_animation->frame();
    obj.display_data();
}

