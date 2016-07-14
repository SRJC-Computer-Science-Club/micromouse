# MicroMouse #

## Branches
* master : code that has been successfully tested on mouse and in sim
* sim : code that has been successfully tested in dev
* dev : code that successfully compiles and has been self tested

![alt branches](https://github.com/SRJC-Computer-Science-Club/micromouse/blob/master/workflow.png)

*the general workflow*

#### Git tutorials

(*if you're new to git watch this first:* https://www.youtube.com/watch?v=0fKg7e37bQE)

basic example of this workflow: https://www.youtube.com/watch?v=oFYyTZwMyAg

## Program Structure
![alt program structure](https://github.com/SRJC-Computer-Science-Club/micromouse/blob/dev/Charts/Hierarchy_Dev2.PNG)


###Classes

#### Controller

Controls the states of the micromouse.
The states are:
1. Do Nothing
2. Map Maze
3. Run Maze (requires that mapping was performed first)
4. Cycle Speed (partially implemented)
5. Debug Mode
6. Calibrate Sensors (Disabled, calibrates IR sensors)
7. Calibrate Motor (Not implemented)
8. Reset Maze (clears any memory of the mapped maze)

States are controlled via the three switches on the micromouse body.
Internally the states may change automatically.

### MouseBot

This class represents all the higher level information needed as a micromouse.
The Maze, the position in the maze, and the direction are all stored in this class.
It performs the two main functions of a micromouse, mapping the maze and running the maze.
MouseBot does not access any sensors directly, instead it uses RobotIO as an interface.


### RobotIO

This class deals with all the sensors and interacting with the real world.
All the pins on the Teensy are defined here.
All movement and positioning is handled by this class. 
All IRsensor and encoder data is interpreted by this class.


Other classes are more self-explanatory, read the individual header files for more detail


## Program flow

![alt Program Flow](https://github.com/SRJC-Computer-Science-Club/micromouse/blob/dev/Charts/flow%20v02.png)

## Project Divisions

### Pathfinding

* find shortest path

* talk with mapping

* talk with motion control

### mapping

* track position

* locate walls

* explore maze

* detect finish cell

* talk with motion control

* talk with pathfinding

* talk with hardware

### motion control

* moving

* turning

* speed control

* collision avoidance

* talk with mapping

* talk with pathfinding

* talk with hardware

### hardware


* microcontroller (likely teensy or micro arduino): https://www.pjrc.com/store/teensy32.html

* sensors
 * proximity/range finder : https://www.pololu.com/category/79/sharp-distance-sensors

* body

* wheels - https://www.pololu.com/  

* motors -  
 * dual-shaft : https://www.pololu.com/category/60/micro-metal-gearmotors
 * hall-effect quadrature encoders: https://www.pololu.com/product/3081
 * H-bridge: https://www.sparkfun.com/products/315
   * http://itp.nyu.edu/physcomp/labs/motors-and-transistors/dc-motor-control-using-an-h-bridge/
 * current sensor for stalls: https://www.pololu.com/product/1185

* batteries
