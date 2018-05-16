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
#include <fstream>
#include <map>
#include "Caregivers.hpp"

using std::string;

/*Patients Class:
    
    Variables:
        fname = first name of patient
        lname = last name of patient
        illnessP = a stack that holds all of the patient's illness priority numbers (1-20)
        arrivalTime = when the patient arrived at the ER
        numOfVisits = number of times the patient has entered the ER
        serviceTime = how long it took for the patient to be treated
        totalWaitTime = how long the patient was in the ER, from arrival to discharge
 
    Functions:
        mutator and accessor functions
        bool operator function -- used to set patients in priority queue based of their most recent illness priority number
        createPatients function -- streams in names from text files and pushes them onto the priority queue and a map of all patients
 */
class Patients
{
private:
    //variables for a Patient object, including name, illness priority numbers, number of visits to the ER, amount of time it took to be treated, and total time in the ER from arrival to discharge
    string fname;
    string lname;
    std::stack<int> illnessP;
    int arrivalTime;
    unsigned long int numOfVisits;
    int serviceTime;
    int totalWaitTime;
    
public:
    
    //default constructor
    Patients() {}
	Patients(string first, string last) { fname = first; lname = last; }
    
    //accessor and mutator functions
    
    string getFName() {return fname;}
    void setFName(string firstN) {fname = firstN;}
    
    string getLName() {return lname;}
    void setLName(string lastN) {lname = lastN;}
    
    std::stack<int> getIllnesses() {return illnessP;}
    void setIllnesses(std::stack<int> ill) {illnessP = ill;}
    
    int getArrivalTime() {return arrivalTime;}
    void setArrivalTime(int aTime) {arrivalTime = aTime;}
    
    unsigned long int getVisits() {return numOfVisits;}
    void setVisits(unsigned long int numV) {numOfVisits = numV;}
    
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

			//read from 'residents' text file to create a directory of first names
			std::ifstream fin;
			fin.open("residents_of_273ville.txt");

			if (fin.fail()) 
			{
				std::cout << "can't open 'residents_of_273ville.txt'\n";
			}
			const int population = 2000;
			string DirectoryFirst[population];

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
		
			string DirectoryLast[population];

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

			std::map <string, Patients*> PatientDirectory;

			for (int i = 0; i < population; i++)
			{
				PatientDirectory[DirectoryFirst[i]] = new Patients(DirectoryFirst[i], DirectoryLast[i]);
			}

		}


};

#endif /* Patients_hpp */
