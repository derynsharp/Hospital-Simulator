//
//  Hospital.cpp
//  Hospital Simulator
//



#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <map>
#include "Hospital.hpp"
#include "Patients.hpp"

Random thisRand;

void Hospital::enterData()
{
	double inputNum;
	std::cout << "Welcome to 273Ville Hospital.How many patients are arriving per hour ? Enter an integer from 1 - 60. \n";
	do
	{
		std::cin >> inputNum;
		if (inputNum >= 1 && inputNum <= 60)
		{
			arrivalRate = inputNum / 60.0;
		}
		else if (inputNum <= 0 || inputNum >= 61)
		{
			std::cout << "Invalid Number. \nEnter an integer from 1 - 60. \n";
		}
	} while (inputNum <= 0 || inputNum >= 61);

	int inputNum2;
	std::cout << "The patient arrival rate is now " << arrivalRate << ".\nHow many Nurses are on call this week? Please enter an integer from 1 - 10. \n";
	do
	{
		std::cin >> inputNum2;

		if (inputNum2 >= 1 && inputNum2 <= 10)
		{
			numOfNurses = inputNum2;
		}
		else if (inputNum2 <= 0 || inputNum2 >= 11)
		{
			std::cout << "Invalid Number.\nPlease enter an integer from 1 - 10. \n";
		}
	} while (inputNum2 <= 0 || inputNum2 >= 11);
	
	int inputNum3;
	std::cout << "The patient arrival rate is now " << arrivalRate << " and the number of Nurses is " << numOfNurses << ".\nHow many Doctors are on call this week ? Please enter an integer from 1 - 10.\n";
	
	do 
	{
		std::cin >> inputNum3;
		if (inputNum3 >= 1 && inputNum3 <= 10)
		{
			numOfDoctors = inputNum3;
		}
		else if (inputNum3 <= 0 || inputNum3 >= 11)
		{
			std::cout << "Invalid Number.\nPlease enter an integer from 1 - 10.\n";
		}
	} while (inputNum3 <= 0 || inputNum3 >= 11);
	
	std::cout << "The patient arrival rate is now " << arrivalRate << ", the number of nurses is " << numOfNurses << " and the number of doctors is " << numOfDoctors << ".\n";
    
    std::cout << "Simulation commencing." << std::endl;

}

void Hospital::createPatients()
{
		//read from 'residents' text file to create a directory of first names
		std::ifstream fin;
		fin.open("residents_of_273ville.txt");

		if (fin.fail())
		{
			std::cout << "can't open 'residents_of_273ville.txt'\n";
		}

		int i = 0; 
		string line;

		while (getline(fin, line) && i<= population)
		{
			DirectoryFirst[i] = line;
			i++;
		}
		
		fin.close(); //created array of first names

		//read from 'surnames' text file to create a directory of last names
		fin.open("surnames_of_273ville.txt");

		if (fin.fail())
		{
			std::cout << "can't open 'surnames_of_273ville.txt'\n";
		}


		i = 0;
		string line2;

		while (getline(fin, line2) && i<= population)
		{
			DirectoryLast[i] = line2;
			i++;
		}
		fin.close(); //created array of surnames. 
					 //These arrays should make creating a map of patient objects much easier.


		for (i = 0; i < population; i++)
		{
			PatientDirectory[DirectoryFirst[i]] = new Patients(DirectoryFirst[i], DirectoryLast[i]);
		}
}

Patients * Hospital::getPatient()
{
    int x;
    x = thisRand.next_int(2000); // randomizes an index number to use to find a patient in the map

	auto itr = PatientDirectory.find(DirectoryFirst[x]); //finds said patient in the map

	int y;
	y = thisRand.next_int(10); //randomizes illness PROBABILITY

	if (y >= 0 && y <= 6) // 70% probability
	{
		int a;
		a = thisRand.next_int(10) + 1; //illness priority between 1 and 10
        (*itr).second->setIllnesses(a);
	}

	else if (y >= 7 && y <= 8) // 20% probability
	{
		int b;
		b = thisRand.next_int(5) + 11; //illness priority between 11 and 15
        (*itr).second->setIllnesses(b);
	}

	else if (y == 9) // 10% probability
	{
		int c;
		c = thisRand.next_int(5) + 16; //illness priority between 16 and 20
        (*itr).second->setIllnesses(c);
	}
    
    (*itr).second->setVisits((*itr).second->getAllIllnesses().size());
    
    return (*itr).second;
}

void Hospital::setPatients()
{
    double d = thisRand.next_double();
    if (d < arrivalRate)
        {
            Patients* p = getPatient();
            allPatients.push(p);
        }
}

void Hospital::runSim()
{
    for (clock = 0; clock < totalTime; clock++)
    {
        setPatients();
        enter(clock);
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


/* enter(int clock) function
    
    How it works:
        1. Lets the patient at the top of the priority queue (the one with the worst illness) into the ER
        2. Checks to see whether a nurse or doctor has to treat them (patients with illness priorities bellow 10 can get treated by either while patients with priorities above 10 can only be treated by doctors)
        3. Checks to see if there are any nurses or doctors that are available to treat the current patient and, if so, puts them with that doctor or nurse to be treated
        4. Checks whether doctors and nurses have finished treating their patients according to their arrival time and how long it took the caregiver to treat them, and if so, discharges the patients (no longer part of any queues)
 */
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
        currentPatient->setVisits(currentPatient->getAllIllnesses().size()); //set number of visits to how many illnesses they've had
        
        //look to see if any Nurses or Doctors are available if their illness priority is beneath or equal to 10
        if (currentPatient->getIllnesses() <= 10)
        {
            //check all the Nurse queues
            for (int i = 0; i < allNurses.size(); i++)
            {
                //in the case that the Nurse queue is full
                if (!allNurses[i].empty())
                {
                    //check if Patient in Nurse queue is done being treated and pop them off the queue if they are(discharged for good yay!)
                    Patients * thisPatient = allNurses[i].front();
                    if (thisPatient!= NULL && clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                    {
                        thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime()); //update total time
                        allNurses[i].pop();
                    }
                    //check all the Doctor queues (since people with these illness priorities can also be treated by Doctors if the Nurses are not available)
                    for (int y = 0; y < allDoctors.size(); y++)
                    {
                        //in the case that the Doctor queue is full
                        if (!allDoctors[y].empty())
                        {
                            //check if Patient in Doctor queue is done being treated and pop them off if so(discharged for good yay!)
                            Patients * thisPatient = allDoctors[y].front();
                            if (thisPatient!= NULL && clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
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
                            break;
                        }
                    }
                }
                //in the case that the Nurse queue is empty, push currentPatient into the nurses's room, set the amount of time it will take for them to get treated, and pop them off the priority queue
                else
                {
                    allNurses[i].push(currentPatient);
                    currentPatient->setServiceTime(genNurse->getTreatTime());
                    allPatients.pop();
                    break;
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
                    if (thisPatient!= NULL && clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
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
                    break;
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
                if (thisPatient!= NULL && clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                {
                    thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                    allNurses[i].pop();
                }
            }
            
            if (!allDoctors[i].empty())
            {
                //check if Patient in Doctor queue is done being treated and pop them off if so (discharged for good yay!)
                Patients * thisPatient = allDoctors[i].front();
                if (thisPatient!= NULL && clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                {
                    thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                    allDoctors[i].pop();
                }
            }
        }
    }
}

int Hospital::displayMenu()
{
    int answer = 0;
    
    while (answer != 3)
    {
    std::cout << "1) Display all patients" << std::endl;
    std::cout << "2) Search for a specific patient record" << std::endl;
    std::cout << "3) Exit" << std::endl;
    std::cout << "Please enter 1, 2, or 3: ";
    std::cin >> answer;
        
        int validAnswer = 1;
        
        while (validAnswer != 0)
        {
    
		switch (answer)
        {
            case 1:
            {
                std::cout << "Names of all treated patients: " << std::endl;
                for (int i = 0; i < PatientDirectory.size(); i++)
                {
                    if (!PatientDirectory[DirectoryFirst[i]]->getAllIllnesses().empty())
                    {
                    std::cout << PatientDirectory[DirectoryFirst[i]]->getFName() << " " << PatientDirectory[DirectoryFirst[i]]->getLName() << std::endl;
                    }
                }

                validAnswer = 0;
                break;
            }
                
            case 2:
			{
				//search map by first name
				std::string name;
				std::cout << "Enter a first name to find that patient record: ";
				std::cin >> name;
				auto itr = PatientDirectory.find(name);
                std::cout << "Name: " << (*itr).second->getFName() << " " << (*itr).second->getLName() << std::endl;
                std::cout << "Recent Illness Level: " << (*itr).second->getIllnesses() << std::endl;
                std::cout << "Number of Visits: " << (*itr).second->getVisits() << std::endl;
				validAnswer = 0;
				break;
            }
            case 3:
            {
                //exit program
                validAnswer = 0;
                continue;
                break;
            }
            default:
            {
                std::cout << "Invalid option, please try again: ";
                std::cin >> answer;
                break;
            }
        }
    }
    }
    return 0;
}
