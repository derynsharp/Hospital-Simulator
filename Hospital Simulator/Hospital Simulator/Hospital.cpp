//
//  Hospital.cpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#include "Hospital.hpp"
#include "Patients.hpp"

void Hospital::enterData()
{
	int inputNum;
	std::cout << "Welcome to 273Ville Hospital.How many patients are arriving per hour ? Enter an integer from 1 - 60. \n";
	std::cin >> inputNum;
	if (inputNum >= 1 && inputNum <= 60)
	{
		arrivalRate = inputNum;
	}
	else if (inputNum <= 0 || inputNum >= 61)
	{
		std::cout << "Invalid Number. \n";
	}

	int inputNum2;
	std::cout << "The patient arrival rate is now " << arrivalRate << ".How many Nurses are on call this week? Please enter an integer from 1 - 10. \n";
	std::cin >> inputNum2;

	if (inputNum2 >= 1 && inputNum2 <= 10)
	{
		setUpNurses(inputNum2);
	}
	else if (inputNum2 <= 0 || inputNum2 >= 11)
	{
		std::cout << "Invalid Number.\n";
	}
	
	int inputNum3;
	std::cout << "The patient arrival rate is now " << arrivalRate << " and the number of Nurses is " << numOfNurses << ".How many Doctors are on call this week ? Please enter an integer from 1 - 10.\n";
	std::cin >> inputNum3;
	if (inputNum3 >= 1 && inputNum3 <= 10)
	{
		numOfDoctors = inputNum3;
	}
	else if (inputNum3 <= 0 || inputNum3 >= 11)
	{
		std::cout << "Invalid Number.\n";
	}
	
	std::cout << "The patient arrival rate is now " << arrivalRate << ", the number of Nurses is " << numOfNurses << " and the number of Doctors is " << numOfDoctors << ".\n";

}

void Hospital::runSim()
{
    for (clock = 0; clock < totalTime; clock++)
    {
    }
}

void Hospital::setUpDocs(int numDocs)
{
    allDoctors.resize(numDocs);
}

void Hospital::setUpNurses(int numNurses)
{
    allNurses.resize(numNurses);
}

void Hospital::enter(int clock)
{
    Doctors * genDoc = new Doctors; //generic doctor object
    Nurses * genNurse = new Nurses; //generic nurse object
    
    //set up how many doctors and nurses there are
    setUpDocs(numOfDoctors);
    setUpNurses(numOfNurses);
    
    
    if (!allPatients.empty())
    {
        //bring in patient with highest illness priority and set their arrival time to now
        Patients * currentPatient = allPatients.top();
        currentPatient->setArrivalTime(clock);
        
        //look to see if any Nurses or Doctors are available if their illness priority is beneath or equal to 10
        if (currentPatient->getIllnesses().top() <= 10)
        {
            //check all the Nurse queues
            for (int i = 0; i < allNurses.size(); i++)
            {
                //in the case that the Nurse queue is full
                if (!allNurses[i].empty())
                {
                    //check if Patient in Nurse queue is done being treated and pop them off the queue if they are(discharged for good yay!)
                    Patients * thisPatient = allNurses[i].front();
                    if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                    {
                        thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
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
                            if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                            {
                                thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                                allDoctors[y].pop();
                            }
                        }
                        //in the case that the Doctor queue is empty, push currentPatient into the doctor's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                        else
                        {
                            allDoctors[y].push(currentPatient);
                            currentPatient->setServiceTime(genDoc->getTreatTime());
                            allPatients.pop();
                        }
                    }
                }
                //in the case that the Nurse queue is empty, push currentPatient into the nurses's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                else
                {
                    allNurses[i].push(currentPatient);
                    currentPatient->setServiceTime(genNurse->getTreatTime());
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
                    if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                    {
                        thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                        allDoctors[i].pop();
                    }
                }
                //in the case that the Doctor queue is empty, push currentPatient into the doctor's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                else
                {
                    allDoctors[i].push(currentPatient);
                    currentPatient->setServiceTime(genDoc->getTreatTime());
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
                if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                {
                    thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                    allNurses[i].pop();
                }
            }
            
            if (!allDoctors[i].empty())
            {
                //check if Patient in Doctor queue is done being treated and pop them off if so (discharged for good yay!)
                Patients * thisPatient = allDoctors[i].front();
                if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                {
                    thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                    allDoctors[i].pop();
                }
            }
        }
    }
}
