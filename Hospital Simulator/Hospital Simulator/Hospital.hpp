//
//  Hospital.hpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#ifndef Hospital_hpp
#define Hospital_hpp

#include <iostream>
#include <queue>
#include <vector>
#include "Patients.hpp"

/*Hospital Class:
 
    Holds a lot of important stuff:
        1. The priority queue for all patients, based off their illness priority number
        2. The vector of queues for the doctors and nurses the patients can get treated by
        3. Clock and the total time the simulation will run for
        4. The arrival rate of patients/min
 */

class Hospital
{
private:
    int clock;
    const int totalTime = 10080; //number of minutes in a week
	int arrivalRate;
    int numOfDoctors;
    int numOfNurses;

	static const int population = 2000;
	string DirectoryFirst[population];
	string DirectoryLast[population];
	std::map <string, Patients*> PatientDirectory;
    
   
    std::priority_queue<Patients *> allPatients;
    std::vector <std::queue<Patients *>> allDoctors;
    std::vector <std::queue<Patients *>> allNurses;
    
public:
    Hospital() {}
    Hospital(int clock, int arrivalRate, int numOfDoctors, int numOfNurses) {this->clock = clock; this->arrivalRate = arrivalRate; this->numOfDoctors = numOfDoctors; this->numOfNurses = numOfNurses;}
    void enterData();
	void createPatients();
	Patients * getPatient();
    void runSim();
    int displayMenu();
    
    void setUpDocs(int numDocs);
    void setUpNurses(int numNurses);
    
    void enter(int clock);
};

#endif /* Hospital_hpp */
