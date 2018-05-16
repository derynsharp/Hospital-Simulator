//
//  Random.h
//  Hospital Simulator
//
#ifndef Random_h
#define Random_h

#include <cstdlib>
#include <ctime>

//used to randomize the amount of time it takes for Doctors and Nurses to treat a patient
class Random {
    
public:
    Random()
    {
        srand((unsigned int)std::time(0));
    }
    Random(int seed)
    {
        srand(seed);
    }
  
    int next_int(int n)
    {
        return int(next_double() * n);
    }
    
    double next_double()
    {
        return double(rand()) / RAND_MAX;
    }
    
};


#endif /* Random_h */
