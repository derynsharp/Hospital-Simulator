//
//  Patients.hpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

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
    
    //this class also holds a priority queue of all the patients based on illness priority as well as queues for however many Doctors and Nurses the user puts in
    std::priority_queue<Patients *> allPatients;
    std::vector <std::queue<Patients *>> allDoctors;
    std::vector <std::queue<Patients *>> allNurses;
    
public:
    
    Doctors * genDoc; //generic doctor object
    Nurses * genNurse; //generic nurse object
    
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
    
    void enter(int clock)
    {
        if (!allPatients.empty())
        {
            //bring in patient with highest illness priority and set their arrival time to now
            Patients * currentPatient = allPatients.top();
            currentPatient->arrivalTime = clock;
            
            //look to see if any Nurses or Doctors are available if their illness priority is beneath or equal to 10
            if (currentPatient->illnessP.top() <= 10)
            {
                //check all the Nurse queues
                for (int i = 0; i < allNurses.size(); i++)
                {
                    //in the case that the Nurse queue is full
                    if (!allNurses[i].empty())
                    {
                        //check if Patient in Nurse queue is done being treated and pop them off the queue if they are(discharged for good yay!)
                        Patients * thisPatient = allNurses[i].front();
                        if (clock - thisPatient->arrivalTime > thisPatient->serviceTime)
                        {
                            allNurses[i].pop();
                        }
                        //check all the Doctor queues (since people with these illness priorities can also be treated by Doctors if the Nurses are not available)
                        for (int y = 0; y < allDoctors.size(); y++)
                        {
                            //in the case that the Doctor queue is full
                            if (!allDoctors.empty())
                            {
                                //check if Patient in Doctor queue is done being treated and pop them off if so(discharged for good yay!)
                                Patients * thisPatient = allDoctors[y].front();
                                if (clock - thisPatient->arrivalTime > thisPatient->serviceTime)
                                {
                                    allDoctors[y].pop();
                                }
                            }
                            //in the case that the Doctor queue is empty, push currentPatient into the doctor's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                            else
                            {
                                allDoctors[y].push(currentPatient);
                                currentPatient->serviceTime = genDoc->getTreatTime();
                                allPatients.pop();
                            }
                        }
                    }
                     //in the case that the Nurse queue is empty, push currentPatient into the nurses's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                    else
                    {
                        allNurses[i].push(currentPatient);
                        currentPatient->serviceTime = genNurse->getTreatTime();
                        allPatients.pop();
                    }
                }
            }
            //look to see if any Doctors are available if their illness priority above 10
            else
            {
                //check all Doctor queues
                for (int i = 0; i < allDoctors.size(); i++)
                {
                    //in the case that the Doctor queue is full
                    if (!allDoctors[i].empty())
                    {
                        //check if Patient in Doctor queue is done being treated and pop them off if so (discharged for good yay!)
                        Patients * thisPatient = allDoctors[i].front();
                        if (clock - thisPatient->arrivalTime > thisPatient->serviceTime)
                        {
                            allDoctors[i].pop();
                        }
                    }
                    //in the case that the Doctor queue is empty, push currentPatient into the doctor's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                    else
                    {
                        allDoctors[i].push(currentPatient);
                        currentPatient->serviceTime = genDoc->getTreatTime();
                        allPatients.pop();
                    }
                }
            }
        }
        else
        {
            //check all the Nurse and Doctor queues
            for (int i = 0; i < allNurses.size(); i++)
            {
                //in the case that the Nurse queue is full
                if (!allNurses[i].empty())
                {
                    //check if Patient in Nurse queue is done being treated and pop them off the queue if they are(discharged for good yay!)
                    Patients * thisPatient = allNurses[i].front();
                    if (clock - thisPatient->arrivalTime > thisPatient->serviceTime)
                    {
                        allNurses[i].pop();
                    }
                }
                
                if (!allDoctors[i].empty())
                {
                    //check if Patient in Doctor queue is done being treated and pop them off if so (discharged for good yay!)
                    Patients * thisPatient = allDoctors[i].front();
                    if (clock - thisPatient->arrivalTime > thisPatient->serviceTime)
                    {
                        allDoctors[i].pop();
                    }
                }
            }
        }
    }
};

#endif /* Patients_hpp */
