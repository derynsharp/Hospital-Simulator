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
#include <iostream>
#include <queue>
#include <vector>
#include "Patients.hpp"

/*Hospital Class:
 
    Holds a lot of important stuff:
        1. The priority queue for all patients, based off their illness priority number
        2. The vector of queues for the doctors and nurses the patients can get treated by
        3. Clock and the total time the simulation will run for
 */

class Hospital
{
private:
    int clock;
    int totalTime;
	int arrivalRate;
    int numOfDoctors;
    int numOfNurses;
    
    //this class also holds a priority queue of all the patients based on illness priority as well as queues for however many Doctors and Nurses the user puts in
    std::priority_queue<Patients *> allPatients;
    std::vector <std::queue<Patients *>> allDoctors;
    std::vector <std::queue<Patients *>> allNurses;
    
public:
    void enterData();
    void runSim();
    void displayMenu();
    
    void setUpDocs(int numDocs);
    void setUpNurses(int numNurses);
    
    void enter(int clock);
};

#endif /* Hospital_hpp */
