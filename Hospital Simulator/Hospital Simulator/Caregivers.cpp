//
//  Caregivers.cpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <map>
#include "Caregivers.hpp"
#include "Random.h"

Random randTime;

//randomize between 1 and 20 minutes
int Caregivers::getTreatTime()
{
    return randTime.next_int(19) + 1;
}

//randomize between 1 and 10 minutes for Nurses
int Nurses::getTreatTime()
{
    return randTime.next_int(9) + 1;
}
