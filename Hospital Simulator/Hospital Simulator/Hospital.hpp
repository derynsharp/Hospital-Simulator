//
//  Hospital.hpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#ifndef Hospital_hpp
#define Hospital_hpp

#include <stdio.h>
#include "Patients.hpp"

class Hospital
{
private:
    int clock;
    int totalTime;
	int arrivalRate;
    Patients * allPatients;
    
public:
    void enterData();
    void runSim();
    void displayMenu();
};

#endif /* Hospital_hpp */
