# Elevator-Simulator-

This is an elevator simulator that is co authored with Adam Cassidy 

This simulator was created for our final project in our data strucutres class. The purpose of this simulator was to build the most effiecnt 
algorithim we could and stress test it given different distributions of people throughout a building. The program will execute 1000 runs of each 
distribution and collect 5 different data sets 

  a. Total Time (How long on average did the elevator run for)
  b. Passengers Delivered (How many passengers were delived on each run 
  c. Total Floors Traveled (On average how many floors would the elevator travel per run)
  d. Total Floors Traveled with Passengers (On average how many floors did the elevator travel with people in it)
  e. Ride Time Per Passenger(What was the average time a person was in an elevator for)
  
The alogorithm of the elevator works like this. The elevator will always start on floor 1 and be emtpy. It will then move up a floor and pick 
up people as long as they dont exceed the total weight constraint of the elevator. It will then move the elevator up to the highest floor
out of all the people in the elevator. It will move up on floor at a time. If there is a person it can drop off or pick up along the way it 
will do so. It will continue this until all people are removed from the elevator 
