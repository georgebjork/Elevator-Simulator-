// Elevator Sim: Adam Cassidy and George Bjork
// This runs a simulation of an elevator in a ten story building. People will be spread out in different ways among the floors, and 
// we will be showing the differences in average ride time per person, total time elevator was running, total floors travelled,
// and average floors travelled per person for each scenario. (for example, having all 100 people at the first floor vs. having them
// all spread out among the building).
// **************************IMPORTANT********************************
// If you would like to see and example of one run being displayed,
//      Comment Out:
//          main.cpp: lines 282-285
//      Uncomment:
//          main.cpp: whichever of lines 289-292 you would like to see
//
// To mix things up, try changing the numFloors in line 30, or the numPersons in line 31, adjust the RUNS_PER in line 280 accordingly 

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <algorithm>

#include "../headers/Building.h"
#include "../headers/Person.h"

using std::cout;
using std::endl;
using std::list;
using std::vector;

int numFloor = 10;
int numPersons = 100;

vector<Building> sim;

// Distributes people in a building's container evenly among all floors
vector<list<Person>> evenlyDistributed()
{
    vector<list<Person>> data;
    //Create list of persons
    list<Person> l;
    for (int i = 0; i < numFloor; i++)
    {
        //Push list of person to vector index
        data.push_back(l);
    }

    int floor;
    int desired_floor;
    int id;
    int weight;
    int num = 0;
    for (int i = 1; i <= numFloor; i++)
    {
        //Create ten people for that floor
        for (int j = 0; j < numPersons / numFloor; j++)
        {
            //Random floor
            desired_floor = (rand() % numFloor) + 1;
            while (desired_floor == i)
            {
                desired_floor = (rand() % numFloor) + 1;
            }

            //Weight will only be between 350 and 100
            weight = rand() % 250 + 100;
            //Push to the list on that floor
            data[i - 1].push_back(Person(i, desired_floor, weight, num++));
        }
    }

    return data;
}

// Distributes people in a building's container randomly among all floors
vector<list<Person>> randomDistribution()
{
    vector<list<Person>> data;
    //Create list of persons
    list<Person> l;
    for (int i = 0; i < numFloor; i++)
    {
        //Push list of person to vector index
        data.push_back(l);
    }

    int floor;
    int desired_floor;
    int id;
    int weight;
    int num = 0;

    for (int i = 0; i < numPersons; i++)
    {
        desired_floor = (rand() % numFloor) + 1;
        while (desired_floor == i)
        {
            desired_floor = (rand() % numFloor) + 1;
        }

        //Weight will only be between 350 and 100
        weight = rand() % 250 + 100;
        //Push to the list on that floor
        data[rand() % numFloor + 0].push_back(Person(0, desired_floor, weight, num++));
    }
    return data;
}

// Distributes people in a building's container all at the bottom
vector<list<Person>> allBottom()
{
    vector<list<Person>> data;
    //Create list of persons
    list<Person> l;
    for (int i = 0; i < numFloor; i++)
    {
        //Push list of person to vector index
        data.push_back(l);
    }

    int floor;
    int desired_floor;
    int id;
    int weight;
    int num = 0;

    for (int i = 0; i < numPersons; i++)
    {
        desired_floor = (rand() % numFloor) + 1;
        while (desired_floor == i)
        {
            desired_floor = (rand() % numFloor) + 1;
        }

        //Weight will only be between 350 and 100
        weight = rand() % 250 + 100;
        //Push to the list on that floor
        data[0].push_back(Person(0, desired_floor, weight, num++));
    }
    return data;
}

// Distributes people in a building's container with half at the top and half at the bottom
vector<list<Person>> halfTopHalfBottom()
{
    vector<list<Person>> data;
    //Create list of persons
    list<Person> l;
    for (int i = 0; i < numFloor; i++)
    {
        //Push list of person to vector index
        data.push_back(l);
    }

    int floor;
    int desired_floor;
    int id;
    int weight;
    int num = 0;

    for (int i = 1; i <= 2; i++)
    {
        //Create ten people for that floor
        for (int j = 0; j < numPersons / 2; j++)
        {
            //Random floor
            desired_floor = (rand() % numFloor) + 1;
            while (desired_floor == i)
            {
                desired_floor = (rand() % numFloor) + 1;
            }

            //Weight will only be between 350 and 100
            weight = rand() % 250 + 100;
            //Push to the list on that floor
            if (i == 1)
                data[i - 1].push_back(Person(i, desired_floor, weight, num++));
            else
                data[data.size() - 1].push_back(Person(data.size(), desired_floor, weight, num++));
        }
    }
    return data;
}

// runs one iteration of the simulation
Building run(Building b, vector<list<Person>> data, std::string name, bool prnt )
{
    b.setDataName(name);
    b.setFloors(data);
    if (prnt)
        b.setToPrint();

    // while loop to keep directing the
    //cout << "reached here." << endl;
    while (b.directElevator())
    {
        int i; // Do nothing! What we need to run is in the header of the while loop;
        //cout << "stuck here";  // debugger
    }
   
    if (prnt) {
        cout << "Final Elevator State:" << endl << b << endl << endl;      // Had to add this, our analytics get shifted to negatives and zeros without it
        // print out analytical data
        b.printAnalyticalData();
    }
    return b;
}

// tests the entered scenario NUM_RUNS times
void test_scenario( std::string type, int NUM_RUNS ) {
    Building b;

    const int RUNS = NUM_RUNS;

    int total_time = 0;
    int total_pass_del = 0;
    int total_floors_trav = 0;
    int total_floors_trav_pass = 0;
    int total_avg_ride_time = 0;
    // based on the type of scenario, run the test NUM_RUNS times and display averages
    if ( type == "Evenly Distributed" ) {
        cout << "Testing: Evenly Distributed People.\nRuns: " << RUNS << endl; 
        
        for (int i = 0; i < RUNS; i++) {
            Building test = run(b, evenlyDistributed(), "Evenly Distributed", false);
            total_time += test.getRunTime();
            total_pass_del += test.getPassengersDelivered();
            total_floors_trav += test.getFloorsTravelled();
            total_floors_trav_pass += test.getFloorsTravelledWithPeople();
            total_avg_ride_time += test.getAverageRideTime();
        }
    } else if ( type == "All Bottom" ) {
        cout << "Testing: All People at Bottom.\nRuns: " << RUNS << endl; 
        
        for (int i = 0; i < RUNS; i++) {
            Building test = run(b, allBottom(), "All Bottom", false);
            total_time += test.getRunTime();
            total_pass_del += test.getPassengersDelivered();
            total_floors_trav += test.getFloorsTravelled();
            total_floors_trav_pass += test.getFloorsTravelledWithPeople();
            total_avg_ride_time += test.getAverageRideTime();
        }
    } else if ( type == "Half Top Half Bottom" ) {
        cout << "Testing: Half at Top Half at Bottom.\nRuns: " << RUNS << endl; 
        
        for (int i = 0; i < RUNS; i++) {
            Building test = run(b, halfTopHalfBottom(), "Half Top Half Bottom", false);
            total_time += test.getRunTime();
            total_pass_del += test.getPassengersDelivered();
            total_floors_trav += test.getFloorsTravelled();
            total_floors_trav_pass += test.getFloorsTravelledWithPeople();
            total_avg_ride_time += test.getAverageRideTime();
        }
    } else if ( type == "Random" ) {
        cout << "Testing: Randomly Distributed People.\nRuns: " << RUNS << endl; 
        
        for (int i = 0; i < RUNS; i++) {
            Building test = run(b, randomDistribution(), "Random", false);
            total_time += test.getRunTime();
            total_pass_del += test.getPassengersDelivered();
            total_floors_trav += test.getFloorsTravelled();
            total_floors_trav_pass += test.getFloorsTravelledWithPeople();
            total_avg_ride_time += test.getAverageRideTime();
        }
    } else {
        cout << "Invalid scenario type." << endl;
    }
    cout << "  Average Total Time: ";
    b.printTime(total_time / RUNS);
    cout << "  Passengers Delivered Each Simulation: " << total_pass_del / RUNS << endl;
    cout << "  Average Total Floors Traveled: " << total_floors_trav / RUNS << endl;
    cout << "  Average Floors Moved With Passengers: " << total_floors_trav_pass / RUNS << endl;
    cout << "  Average Average Ride Time per Passenger: ";
    b.printTime(total_avg_ride_time / RUNS);
    cout << endl;
}

int main()
{
    srand(time(0));
    const int RUNS_PER = 1000;

    test_scenario( "Evenly Distributed", RUNS_PER );
    test_scenario( "All Bottom", RUNS_PER );
    test_scenario( "Half Top Half Bottom", RUNS_PER );
    test_scenario( "Random", RUNS_PER );

    Building b;

    //run(b, evenlyDistributed(), "Evenly Distributed", true);
    //run(b, allBottom(), "All Bottom", true);
    //run(b, halfTopHalfBottom(), "Half Top Half Bottom", true);
    //run(b, randomDistribution(), "Random", true);

    return 0;
}