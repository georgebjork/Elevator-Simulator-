# Elevator-Simulator-

This is an elevator simulator that is co authored with Adam Cassidy 

This simulator was created for our final project in our data strucutres class. The purpose of this simulator was to build the most efficent  
elevator algorithim, and stress test it given different distributions of people throughout a building. The program will execute 1000 runs of each 
distribution and collect 5 different data sets 

  1. Total Time (How long on average did the elevator run for)
  2. Passengers Delivered (How many passengers were delived on each run 
  3. Total Floors Traveled (On average how many floors would the elevator travel per run)
  4. Total Floors Traveled with Passengers (On average how many floors did the elevator travel with people in it)
  5. Ride Time Per Passenger(What was the average time a person was in an elevator for)
  
The algorithm of the elevator will always start on floor 1 and be emtpy. It will then move up a floor and pick 
up people as long as they dont exceed the total weight constraint of the elevator. It will then move the elevator up to the highest floor
out of all the people in the elevator. It will move up one floor at a time. If there is a person it can drop off or pick up along the way it 
will do so. It will continue this until all people are removed from the elevator 

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*IMPORTANT\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\* <br />
If you would like to see and example of one run being displayed,
      Comment Out:
          main.cpp: lines 282-285
     Uncomment:
         main.cpp: whichever of lines 289-292 you would like to see
         
To mix things up, try changing the numFloors in line 30, or the numPersons in line 31, adjust the RUNS_PER in line 280 accordingly 

