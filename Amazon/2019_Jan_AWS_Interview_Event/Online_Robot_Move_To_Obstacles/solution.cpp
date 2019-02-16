/*
 * 2. Move robot to the obstacles.
a. For every <x, y> position in the area, it could be of value 0, 1 or 9.
    0: means trench
    1: flag ground
	9: obstacles
b. Robot can only move to flat areas. 
c. Return the closest number of steps to obstacles if there is a route to obstacles.
d. Return -1 if there is no route to obstacles

Solution:
1. A 2-D array of bools which indicates whther a position has been visited 
2.a By "visited", it means from the min steps from this point to obstacles has been calculated. Initially each value is false.
3. Do it in a recusive way. 
4. The robot can move to each valid positions as long as this posistion has not been visited yet.
*/
