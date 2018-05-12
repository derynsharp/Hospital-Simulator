//
//  Hospital.cpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#include "Hospital.hpp"

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
		= inputNum2;
	}
	else if (inputNum2 <= 0 || inputNum2 >= 11)
	{
		std::cout << "Invalid Number.\n";
	}
	
	int inputNum3;
	std::cout << "The patient arrival rate is now " << arrivalRate << " and the number of Nurses is " << numofNurses << ".How many Doctors are on call this week ? Please enter an integer from 1 - 10.\n";
	std::cin >> inputNum3;
	if (inputNum3 >= 1 && inputNum3 <= 10)
	{
		NumofDoctors = inputNum3;
	}
	else if (inputNum3 <= 0 || inputNum3 >= 11)
	{
		std::cout << "Invalid Number.\n";
	}
	
	std::cout << "The patient arrival rate is now " << arrivalRate << ", the number of Nurses is " << numofNurses << " and the number of Doctors is " << NumofDoctors << ".\n";

}

void Hospital::runSim()
{
    for (clock = 0; clock < totalTime; clock++)
    {
        allPatients->enter(clock);
    }
}
