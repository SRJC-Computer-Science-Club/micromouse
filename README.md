# MicroMouse #

## Branches
* master : code that has been successfully tested on mouse and in sim
* sim : code that has been successfully tested in dev
* dev : code that successfully compiles and has been self tested
* master-2 : master does not matter :P it's all about dev :)

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


