//
//  Caregivers.hpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#ifndef Caregivers_hpp
#define Caregivers_hpp

#include <stdio.h>
#include "Random.h"

//parent class for Doctors and Nurses
class Caregivers
{
public:
    Caregivers() {}
    int getTreatTime();
};

//Nurses class, use polymorphism to get the correct time to treat a patient for Nurses
class Nurses : public Caregivers
{
public:
    Nurses():Caregivers() {}
    int getTreatTime();
};

//Doctors class, uses Caregivers' function to get correct time to treat a patient for Doctors
class Doctors : public Caregivers
{
public:
    Doctors() : Caregivers() {}
};

#endif /* Caregivers_hpp */
