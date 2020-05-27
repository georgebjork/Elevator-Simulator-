#include "Building.h"

// loads a specific scenarin into the building
void Building::setFloors(vector<list<Person>> d)
{
    num_floors_ = d.size();
    floors_ = d;
}

// processes the elevator
// loads passengers from current floor onto elevator (if doesnt pass weight restriction)
// or sends elevator to someone else that is waiting
bool Building::directElevator() {
    it = floors_[elevator_.getCurrentFloor() - 1].begin();
    // if elevator is empty, add first person at floor and set elevator destination
    if ( elevator_.isEmpty() && !floors_[elevator_.getCurrentFloor() - 1].empty() ) {
        elevator_.addPerson(*it);
        it = floors_[elevator_.getCurrentFloor() - 1].erase(it);
        if ( (*it).getDesiredFloor() > elevator_.getCurrentFloor() )
            elevator_.setDirection(true);
        else 
            elevator_.setDirection(false);
    }
    // load elevator with as many more passengers possible by weight limit and if the passenger's direction matches the current direction
    while ( it != floors_[elevator_.getCurrentFloor() - 1].end() ) {   // scan throught the whole floor
        // see if the person at the iterator can be loaded by weight limit and direction
        if ( elevator_.getCurrentWeight() + (*it).getWeight() <= elevator_.getMaxWeight() ) {
            // load next person on floor if their direction is the same 
            bool pas_dir = false; // figure out the passenger's direction 
            if ( (*it).getDesiredFloor() > elevator_.getCurrentFloor() )
                pas_dir = true;
            // if direction matches, add them to the elevator
            //cout << pas_dir << ", " << elevator_.getDirection();
            if ( pas_dir == elevator_.getDirection() ) {
                // add to elevator carriage
                elevator_.addPerson(*it);
                // remove from floor
                floors_[elevator_.getCurrentFloor() - 1].erase(it);
            } 
        }
        ++it;
    }

    //cout << "passengers loaded" << endl; // debugger

    // if car is empty, scan for closest passenger to go pick up
    if ( elevator_.isEmpty() ) {
        int go_to = scanFloors();
        // if there are no passengers waiting anywhere, return false and end simulation
        if ( go_to == -1 ) {
            return false;
        } else {
            // send the elevator to the closest floor
            elevator_.setDestination( go_to );
        }
    }
    //cout << "running move_floor()" << endl; // debugger

    // send elevator to next person's floor - this priority will be handled within the different elevator types
    
    elevator_.moveFloor(); 
    if (printing)
        cout << *this;
    return true;
}

// scans to see what floors have passengers
int Building::scanFloors() {
    vector<int> temp;
    // fill vector to represent what floors have people waiting
    for ( int i = 0; i < num_floors_; i++ ) {
        
        if ( !floors_[i].empty() )
            temp.push_back(i + 1);
    }
    
    // find which floor is closest to the elevator's current position and return it
    int closest;
    if(temp.size() > 0)
        closest = temp[0];
    else
        return -1;

    for(int i = 1; i < temp.size(); i++)
    {
        if(temp[i] - elevator_.getCurrentFloor() < closest - elevator_.getCurrentFloor())
            closest = temp[i];
    }

    return closest;
}
// converts an integer of seconds and prints it as a readable time
void Building::printTime( int seconds ) {
    if ( seconds / 3600 < 10 ) 
        cout << 0;
    cout << seconds / 3600 << ":";
    if ( (seconds % 3600) / 60 < 10 ) 
        cout << 0;
    cout << (seconds % 3600) / 60 << ":"; 
    if ( seconds % 60 < 10 )
        cout << 0;
    cout << (seconds % 60) << endl;
}

// prints all analytics gathered by the elevator
void Building::printAnalyticalData() {
    cout << "************************************************************************" << endl;
    cout << "************************************************************************" << endl;
    cout << "************************************************************************" << endl;
    cout << "Elevator Analytics:" << endl;
    //cout << "  Number of People Originally Created: " << numPeople << endl; // debugger
    cout << "  Total Time: ";
    printTime(getRunTime());
    cout << "  Total Passengers Delivered: " << getPassengersDelivered() << endl;
    cout << "  Total Floors Traveled: " << getFloorsTravelled() << endl;
    cout << "  Floors Moved With Passengers: " << getFloorsTravelledWithPeople() << endl;
    cout << "  Average Ride Time per Passenger: ";
    printTime(getAverageRideTime());
    cout << "************************************************************************" << endl;
    cout << "************************************************************************" << endl;
    cout << "************************************************************************" << endl;
}

// overloaded ostream operator for the elevator's current state
std::ostream &operator<<(std::ostream &os, Building b)
{
    cout << "Elevator passengers [ " ;
    //Print out all of the passengers in elevator
    for(int i = 0; i < b.elevator_.getCarriageSize(); i++)
    {   
        Person p = b.elevator_.getPerson(i);
        cout << p.getID();
        if ( i < b.elevator_.getCarriageSize() - 1 )
            cout << ", ";
    }
    cout << " ] ";
    
    //Print out how much weight is in the elevator 
    cout << "Weight: " << b.elevator_.getCurrentWeight();

    //Print out current floor
    cout << " Floor: " << b.elevator_.getCurrentFloor(); 
    
    // Print out destination
    cout << " Destination: " << b.elevator_.getDestination();
    
    //Print out total time
    cout << " Time: ";
    b.printTime(b.elevator_.getTotalTime());
    
    return os;
}   