//
//  main.cpp
//  Hospital Simulator
//
//  Created by Madison Oliver on 5/12/18.
//  Copyright © 2018 Madison Oliver. All rights reserved.
//

#include <iostream>
#include "Caregivers.hpp"
#include "Patients.hpp"
#include "Hospital.hpp"


int main()
{
    Hospital * MyHospital = new Hospital (0,0.5,1,1);
    std::priority_queue<Patients *> allPatientstest;
    
    
    Patients * Lucy = new Patients;
    Lucy->setFName("Lucy");
    Lucy->setLName("MAY");
    Lucy->setIllnesses(6);
    Lucy->setArrivalTime(0);
    Lucy->setVisits(0);
    Lucy->setTotalWaitTime(0);
    Lucy->setServiceTime(0);
    

    allPatientstest.push(Lucy);
    
    
    MyHospital->runSim(allPatientstest);
    
    std::cout << "Name: " << Lucy->getFName() << std::endl;
    std::cout << "Recent Illness Level: " << Lucy->getIllnesses() << std::endl;
    std::cout << "Arrival Time: " << Lucy->getArrivalTime() << std::endl;
    std::cout << "Number of Visits: " << Lucy->getVisits() << std::endl;
    std::cout << "Total Wait Time: " << Lucy->getTotalWaitTime() << std::endl;
    std::cout << "Service Time: " << Lucy->getServiceTime() << std::endl;
    
}
