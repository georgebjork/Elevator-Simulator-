#pragma once

#include <iostream>
#include <deque>
#include <algorithm>
#include "Person.h"
#include "Building.h"

using std::deque;
using std::cout;
using std::endl;
using std::sort;

class Elevator {
    private:
        int current_floor_ = 1;                                 //Current floor of the elevator                         
        const int max_weight_ = 1000;                           // Max amount of weight the elevator can hold the elevator can hold
        int totalTime_ = 0;                                     //This will be the total time for taking all passengers 
        int time_carrying_ = 0;                                 // time spent carrying people
        int destination_ = 2;                                   // Current destination
        bool direction_ = true;                                 // true is upwards, false is downwards
        bool printing = false;                                  // print out sim data as it runs
        
        // analytic data
        int passengers_delivered_ = 0;                          // stores the current number of people this elevator has delivered to their destinations
        int floors_moved_ = 0;                                  // stores the current number of floors this elevator had traveled
        int floors_moved_with_people = 0;                       // stores the current number of floors travelled while carrying people
        deque<Person> carriage_;                                //Deque of people in elevator  
                                     
    public:
        Elevator() {};                                          //Default 

        void addPerson(Person p);                               // adds a person to the carriage
        void removePerson(int i);                               // removes a person from the carriage
        void moveFloor();                                       // moves elevator
        void setDestination( int dest ) { destination_ = dest; }// sets the elevators destination
        void setDirection( bool dir ) { direction_ = dir; }     // sets the current direction elevator is travelling
        void setPrinting(bool print) { printing = print; }      // sets sim info to print while running

        bool isEmpty();                                       //Checks to see if the elevator is empty
        
        int getPassengersDelivered() { return passengers_delivered_; }          // returns passengers_delivered_
        int getFloorsMoved() { return floors_moved_; }                          // returns floors_moved
                         
        int getSpeed();                                                         // Returns the time elapsed to move a floot based on the current weight of the elevator
        int getCurrentWeight();                                                 // returns current weight of all passengers combined
        int getCurrentFloor() { return current_floor_; }                        // returns the floor that the elevator is currently positioned
        int getMaxWeight() { return max_weight_; }                              // returns the max weight capacity of this elevator
        int getCarriageSize() { return carriage_.size(); }                      //Return the amount of people in carriage
        int getTotalTime() { return totalTime_; }                               //Return total time
        int getTimeCarrying() { return time_carrying_; }                        // returns the current time spent carrying people
        int getDestination() { return destination_; }                           // returns the current destination
        bool getDirection() { return direction_; }                              // returns the current direction the elevator is traveling
        int getFloorsMovedWithPeople() { return floors_moved_with_people;}      // returns the number of floors moved while carrying people

        Person getPerson(int i) { return carriage_[i]; }                        //Will return a person from the carriage     
};      

#include "Elevator.cpp"