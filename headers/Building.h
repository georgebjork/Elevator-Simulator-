#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <stdlib.h>  

#include "Person.h"
#include "Elevator.h"
#include "Math.h"

using std::vector;
using std::list;

class Building{
    private:
        int num_floors_;                                                            //Amount of floors in buidling                                                      
        std::string dataName = "";                                                  // signifies the type of scenario loaded
        vector<list<Person>> floors_;                                               //This will be the same size of the num_floors and hold all the persons on the floor. Each index in the vector will be a floor and the list will hold all the person objects on the floor
        Elevator elevator_;                                                         //This will be the building elevator 
        list<Person>::iterator it;                                                  // iterator needed for accessing people on each floor
        bool printing = false;                                                      // print out sim data as it runs

    public:
        Building() {};                                                              //Default 
        bool directElevator();                                                      //Argument constructor 
        int scanFloors();                                                           // scans building to find closest person waiting

        void setFloors(vector<list<Person>> d);                                     // sets floors to match entered example
        void printAnalyticalData();                                                 // Print out anaytics from this buildings elevator(s)
        void printTime(int seconds);                                                // Prints an int seconds as a readable hour, miinute, and second format
        void setDataName(std::string s) { dataName = s; };                          // sets the name of type of scenario
        void setToPrint() { printing = true; elevator_.setPrinting(true); }         // sets the sim to print out steps as it runs

        // used for analytics
        int getRunTime() { return elevator_.getTotalTime(); };                      // returns total runtime                                    
        int getPassengersDelivered() { return elevator_.getPassengersDelivered(); } // returns total passengeres delivered
        int getFloorsTravelled() { return elevator_.getFloorsMoved(); }             // returns total floors travelled
        int getFloorsTravelledWithPeople() { return elevator_.getFloorsMovedWithPeople(); }  // returns total floors travelled while carrying people
        double getAverageRideTime() { return (static_cast<double>(elevator_.getTimeCarrying()) / static_cast<double>(elevator_.getPassengersDelivered())); }  // returns the average ride time of passengers

        friend std::ostream &operator<<(std::ostream &os, Building b);               //This will print out all the current the data of the elevator
};

#include "Building.cpp"