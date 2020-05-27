#include "Elevator.h"

// adds a person to the carriage
void Elevator::addPerson(Person p)
{
    totalTime_+=2;          //It will take 2 seconds to load a perosn 
    carriage_.push_back(p);
    passengers_delivered_++;
    if (printing)    
        cout << "  Adding passenger " << p.getID() << " at floor " << current_floor_ << endl;
}

// removes a person from the carriage
void Elevator::removePerson(int i)
{    
    if (printing)
        cout << "  Removing passenger " << carriage_[i].getID() << " at floor " << current_floor_ << endl;
    totalTime_+=2;          //It will take 2 seconds to remove a person 
    time_carrying_ += carriage_[i].getTravelTime();
    //passengers_delivered_++; 
    carriage_.erase(carriage_.begin()+i);
}

// returns whether or not the carriage is empty
bool Elevator::isEmpty()
{
    if(carriage_.size() > 0)
        return false;
    return true;
}

// main method to move the elevator up or down
// unloads people who need to get off, and moves towards its new destination
void Elevator::moveFloor()
{       
    // unload anyone who needs to get off
    for ( int i = 0; i < carriage_.size(); i++ ) {
        if ( carriage_[i].getDesiredFloor() == current_floor_ )    
            removePerson(i);                                     
    }
    
    // if no one matches original destination, set destination to current furthest
    if ( !isEmpty() ) {
        bool no_matches = true;
        for ( int i = 0; i < carriage_.size(); i++ ) {
            if ( destination_ == carriage_[i].getDesiredFloor() ) {
                no_matches = false;
            }
        }
        if ( no_matches ) {
            int temp_high = 0;
                // find destination based on person who has the furthest destination
            for ( int i = 1; i < carriage_.size(); i++ ) {
                if ( abs( carriage_[i].getDesiredFloor() - current_floor_ ) > abs( carriage_[temp_high].getDesiredFloor() - current_floor_ ) ) 
                    temp_high = i;
            }
            setDestination(carriage_[temp_high].getDesiredFloor());  
        } 
    }

    // increment/decrement floor by one moving towards the destination
    if ( destination_ > current_floor_ )        //Need to go up 
    {
        //cout << "moving up";              // deubugger
        
        current_floor_++;
        floors_moved_++;                   //Move elevator up
        direction_ = true;
        if(carriage_.size() > 0)
            floors_moved_with_people++;
    }
    else if ( destination_ < current_floor_ && destination_ > 0 )      //Need to go down 
    {
        current_floor_--;
        floors_moved_++;                   //Move elevator down 
        direction_ = false;
        if(carriage_.size() > 0)
            floors_moved_with_people++;

    } else if ( destination_ != current_floor_) { 
        cout << "  Passenger's destination does not exist. " << endl; 
    }

    // add in the time it took to move
    totalTime_ += getSpeed();                  
    for ( int i = 0; i < carriage_.size(); i++ ) {
        carriage_[i].incrementTravelTime(getSpeed());
    }
}

// returns the speed of the elevator in seconds per floor based on the current load
int Elevator::getSpeed() {
    if ( getCurrentWeight() < 200 )     
        return 3;          //was 10         
    else if ( getCurrentWeight() < 500 )
        return 4;          //was 12          
    else if ( getCurrentWeight() < 800 )
        return 5;          //was 15    
    else 
        return 6;          //was 18
}

// returns the total weight of all passengers
int Elevator::getCurrentWeight() {
    int temp_weight = 0;
    for (int i = 0; i < carriage_.size(); i++) {
        temp_weight += carriage_[i].getWeight();
    }
    return temp_weight;
}

