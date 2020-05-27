#pragma once 

#include <iostream> 

class Person{
    private:
        int current_floor = -1;                                                                 //Persons current floor
        int desired_floor = -1;                                                                 //Floor where elevator wants to go 
        int person_id_;                                                                         //Each person will have a unique id 
        int board_time_;                                                                        //This will calculate wait time until picked up by elevator 
        int travel_time_ = 0;                                                                   //This will calculate the total travel time in elevator
        int weight_;                                                                            //Stores the weight in pounds of the passenger

    public:
        Person() {};                                                                            //Default const
        Person(int current, int desiredFloor, int weight, int id) : current_floor(current),     // Argument const
            desired_floor(desiredFloor), weight_(weight), person_id_(person_id_ = id) {}    

        void setDesiredFloor(int desiredFloor) { desired_floor = desiredFloor; }                //Set the floor the person wants to go to 
        void setCurrentFloor(int currentFloor) { current_floor = currentFloor; }                //Set the current floor 

        int getCurrentFloor() { return current_floor; }                                         //Return their current floor
        int getDesiredFloor() { return desired_floor; }                                         //Return their desired floor 
        int getWeight() { return weight_; }                                                     //Return their weight
        int getID() { return person_id_; }                                                      //Returns person id                 
        int getTravelTime() { return travel_time_; }                                            // returns passenger's travel time
        void incrementTravelTime( int time ) { travel_time_ += time; }                          // Increments travel time by entered amount
        
        bool operator==(const Person& p)                                                        //Operator overload
        {
            //If the ids and the desired floor are the same, then they are the same person 
            if(this->person_id_ == p.person_id_ && this->desired_floor == p.desired_floor)
                return true;
            return false; 
        }
};      