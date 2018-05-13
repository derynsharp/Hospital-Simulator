//
//  Patients.hpp
//  Hospital Simulator
//

//DEVELOPER: Madison Oliver

#ifndef Patients_hpp
#define Patients_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include "Caregivers.hpp"
#include "Hospital.hpp"

using std::string;

/*Patients Class:
 
    Holds a lot of important stuff:
        1. Variables for patients that will be held in their records (name, number of visits to the ER, etc)
        2. The priority queue for all patients, based off their illness priority number
        3. The vector of queues for the doctors and nurses the patients can get treated by
 
    How it works:
        1. Lets the patient at the top of the priority queue (the one with the worst illness) into the ER
        2. Checks to see whether a nurse or doctor has to treat them (patients with illness priorities bellow 10 can get treated by either while patients with priorities above 10 can only be treated by doctors)
        3. Checks to see if there are any nurses or doctors that are available to treat the current patient and, if so, puts them with that doctor or nurse to be treated
        4. Checks whether doctors and nurses have finished treating their patients according to their arrival time and how long it took the caregiver to treat them, and if so, discharges the patients (no longer part of any queues)
 */
class Patients
{
private:
    //variables for a Patient object, including name, illness priority numbers, number of visits to the ER, amount of time it took to be treated, and total time in the ER from arrival to discharge
    string fname;
    string lname;
    std::stack<int> illnessP;
    int arrivalTime;
    int numOfVisits;
    int serviceTime;
    int totalWaitTime;
    
public:
    
    //default constructor
    Patients() {}
    
    //accessor and mutator functions
    
    string getFName() {return fname;}
    void setFName(string firstN) {fname = firstN;}
    
    string getLName() {return lname;}
    void setLName(string lastN) {lname = lastN;}
    
    std::stack<int> getIllnesses() {return illnessP;}
    void setIllnesses(std::stack<int> ill) {illnessP = ill;}
    
    int getArrivalTime() {return arrivalTime;}
    void setArrivalTime(int aTime) {arrivalTime = aTime;}
    
    int getVisits() {return numOfVisits;}
    void setVisits(int numV) {numOfVisits = numV;}
    
    int getServiceTime() {return serviceTime;}
    void setServiceTime (int sTime) {serviceTime = sTime;}
    
    int getTotalWaitTime() {return totalWaitTime;}
    void setTotalWaitTime(int tTime) {totalWaitTime = tTime;}
    
    
    //organizes Patients in the priority queue according to their priority illness level; highest numbers will go on top
    bool operator<(const Patients * &other) const
    {
        if (illnessP < other->illnessP)
            return true;
        else
            return false;
    }
    
    void createPatients()
    {
        
    }
};

#endif /* Patients_hpp */
