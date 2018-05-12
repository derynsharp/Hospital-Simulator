//
//  Hospital.cpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#include "Hospital.hpp"

void Hospital::runSim()
{
    for (clock = 0; clock < totalTime; clock++)
    {
        allPatients->enter(clock);
    }
}
