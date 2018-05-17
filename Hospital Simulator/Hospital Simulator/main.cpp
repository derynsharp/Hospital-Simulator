//
//  main.cpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#include <iostream>
#include "Caregivers.hpp"
#include "Patients.hpp"
#include "Hospital.hpp"


int main()
{
    Hospital * MyHospital = new Hospital (0,0.5,1,1);
    MyHospital->enterData();
    MyHospital->createPatients();
    MyHospital->runSim();
    MyHospital->displayMenu();
    
}
