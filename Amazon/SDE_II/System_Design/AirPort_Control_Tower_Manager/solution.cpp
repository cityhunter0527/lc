/*
 *  Design an airport control tow management system
 *  1. Fly out and Landing airplain management
 *  2. Ability to track which plain is delayed, how many hours are delayed to prioritize
 *  3. Ability to cancel some flight due to remote city weather condition.
 *
 *
 *  Solution:
 *  1. one queue for fly out
 *  2. one queue for landing 
 *  3. each airplain is an object which will request:
 *     3.1 fly in or land
 *     3.2 class members include start time (calculate delay hours), target city, etc.
 *  4. Each runway whould have one waiting way there should a limited number of airplanes on this waiting way. 
 *     other plains should be still connected to bridge before waiting way has room to be queued.
 *  5. Each plane in the air waiting for landing should have left fuel to calculate the flight hours.
 *     Need to handle urgent flight which has limited fuels left (top priority).  
 *
 * */


