//
//  Hospital.cpp
//  Hospital Simulator
//


#include "Hospital.hpp"
#include "Patients.hpp"

void Hospital::enterData()
{
	int inputNum;
	std::cout << "Welcome to 273Ville Hospital.How many patients are arriving per hour ? Enter an integer from 1 - 60. \n";
	do
	{
		std::cin >> inputNum;
		if (inputNum >= 1 && inputNum <= 60)
		{
			arrivalRate = inputNum / 60;
		}
		else if (inputNum <= 0 || inputNum >= 61)
		{
			std::cout << "Invalid Number. \nEnter an integer from 1 - 60. \n";
		}
	} while (inputNum <= 0 || inputNum >= 61);

	int inputNum2;
	std::cout << "The patient arrival rate is now " << arrivalRate << ".How many Nurses are on call this week? Please enter an integer from 1 - 10. \n";
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
	std::cout << "The patient arrival rate is now " << arrivalRate << " and the number of Nurses is " << numOfNurses << ".How many Doctors are on call this week ? Please enter an integer from 1 - 10.\n";
	
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

		for (int i = 0; i < population; i++)
		{
			string line;
			while (getline(fin, line))
			{
				DirectoryFirst[i] = line;
			}
		}
		fin.close(); //created array of first names

					 //read from 'surnames' text file to create a directory of last names

		fin.open("surnames_of_273ville.txt");

		if (fin.fail())
		{
			std::cout << "can't open 'surnames_of_273ville.txt'\n";
		}


		for (int i = 0; i < population; i++)
		{
			string line;
			while (getline(fin, line))
			{
				DirectoryLast[i] = line;
			}
		}
		fin.close(); //created array of surnames. 
					 //These arrays should make creating a map of patient objects much easier.


		for (int i = 0; i < population; i++)
		{
			PatientDirectory[DirectoryFirst[i]] = new Patients(DirectoryFirst[i], DirectoryLast[i]);

		
	}
}

void Hospital::getPatient()
{
	srand(time(NULL));
	int x;
	x = rand() % 2000; // randomizes an index number to use to find a patient in the map

	PatientDirectory.find(DirectoryFirst[x]); //finds said patient in the map

	srand(time(NULL));
	int y;
	y = rand() % 10; //randomizes illness PROBABILITY

	if (y >= 0 && y <= 6) // 70% probability
	{
		srand(time(NULL));
		int a;
		a = rand() % 10 + 1; //illness priority between 1 and 10
	}

	else if (y >= 7 && y <= 8) // 20% probability
	{
		srand(time(NULL));
		int b;
		b = rand() % 5 + 11; //illness priority between 11 and 15
	}

	else if (y == 9) // 10% probability
	{
		srand(time(NULL));
		int c;
		c = rand() % 5 + 16; //illness priority between 16 and 20
	}
}

void Hospital::runSim()
{
    for (clock = 0; clock < totalTime; clock++)
    {
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
        
        //look to see if any Nurses or Doctors are available if their illness priority is beneath or equal to 10
        if (currentPatient->getIllnesses().top() <= 10)
        {
            //check all the Nurse queues
            for (unsigned int i = 0; i < allNurses.size(); i++)
            {
                //in the case that the Nurse queue is full
                if (!allNurses[i].empty())
                {
                    //check if Patient in Nurse queue is done being treated and pop them off the queue if they are(discharged for good yay!)
                    Patients * thisPatient = allNurses[i].front();
                    if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                    {
                        thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime()); //update total time
                        thisPatient->setVisits(thisPatient->getIllnesses().size()); //set number of visits to how many illnesses they've had
                        allNurses[i].pop();
                    }
                    //check all the Doctor queues (since people with these illness priorities can also be treated by Doctors if the Nurses are not available)
                    for (unsigned int y = 0; y < allDoctors.size(); y++)
                    {
                        //in the case that the Doctor queue is full
                        if (!allDoctors.empty())
                        {
                            //check if Patient in Doctor queue is done being treated and pop them off if so(discharged for good yay!)
                            Patients * thisPatient = allDoctors[y].front();
                            if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                            {
                                thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                                 thisPatient->setVisits(thisPatient->getIllnesses().size()); //set number of visits to how many illnesses they've had
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
            for (unsigned int i = 0; i < allDoctors.size(); i++)
            {
                //in the case that the Doctor queue is full
                if (!allDoctors[i].empty())
                {
                    //check if Patient in Doctor queue is done being treated and pop them off if so (discharged for good yay!)
                    Patients * thisPatient = allDoctors[i].front();
                    if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                    {
                        thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                         thisPatient->setVisits(thisPatient->getIllnesses().size()); //set number of visits to how many illnesses they've had
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
        for (unsigned int i = 0; i < allNurses.size(); i++)
        {
            //in the case that the Nurse queue is full
            if (!allNurses[i].empty())
            {
                //check if Patient in Nurse queue is done being treated and pop them off the queue if they are(discharged for good yay!)
                Patients * thisPatient = allNurses[i].front();
                if (clock - thisPatient->getArrivalTime() > thisPatient->getServiceTime())
                {
                    thisPatient->setTotalWaitTime(clock - thisPatient->getArrivalTime());
                     thisPatient->setVisits(thisPatient->getIllnesses().size()); //set number of visits to how many illnesses they've had
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
                    thisPatient->setVisits(thisPatient->getIllnesses().size()); //set number of visits to how many illnesses they've had
                    allDoctors[i].pop();
                }
            }
        }
    }
}
