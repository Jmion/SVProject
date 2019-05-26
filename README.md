# README
The purpose of this application is to run a simulation with multiple animals. We want to simulate and environment where food can grow, and different species can eat, hunt, and fornicate. To monitor the progress of our simulation statistics are available of the bottom of the screen which show interesting statistics about the specific environment.

## Requirements

To be able to compile and run you must have:

* Scons
* SFML library

Scons is not as well know as make but it has similar functionality. It allows programs to be compiled and linked easily and without any hassle. 

SFML is a cross platform library which should allow this program to be ported to any OS that SFML supports Windows, Linux, macOS and soon Android & iOS. 
Porting this program to mobile is expected to be a bit of work but SFML will help use reduce the amount of work required.

## How to run the software

This software is expected to be able to run without any hassle across GNU/Linux, MacOS, and Windows. The current release version has only been tested on **GNU/Linux** Debian based OS using kernel version 4.15.0-50-generic.

* To run the main software simply run *scons application-run*
* To run the environment where the user can place obstacles that will interfere with the propagation of waves simply run *scons NeuronalTest-run*


## User interface

### Predator Prey Simulation

| Behavior                | Key           |
|-------------------------|---------------|
| Reset simulation        | R             |
| End of program          |  Esc          |
| Reload config file      | C             |
| Add a Gerbil at MP      | G             |
| Add a Dragon at MP      | Q             |
| Dracarys (dragon fire)  | A             |
| Add a Scorpion at MP    | S             |
| Add a food at MP        | F             |
| Toggle debug mode       | D             |
| Switch macro/micro view | Tab           |
| Zoom                    | Z             |
| Move view to the right  | $\rightarrow$ |
| Move view to the left   | $\leftarrow$  |
| Move view up            | $\uparrow$    |
| Move view down          | $\downarrow$  |
| Pause                   | Space         |

### Neuronal Simulation

| Behavior                              | Key           |
|---------------------------------------|---------------|
| Mouse position will be revered to as  | MP            |
| Reset the simulation                  | R             |
| End the program                       | Esc           |
| Reload the configuration file         | C             |
| Add a neuronal scorpion at MP         | N             |
| Add a wave gerbil at MP               | W             |
| Toggle debug mode                     | D             |
| Switch macro/micro view               | Tab           |
| Zoom                                  | Z             |
| Move view to the right                | $\rightarrow$ |
| Move view to the left                 | $\leftarrow$  |
| Move view up                          | $\uparrow$    |
| Move view down                        | $\downarrow$  |
| Pause                                 | Space         |


## Configuration files

Most of the behavior of the animals in the simulation is defined in JSON files that are located in the ./res directory. To launch any of the programs mentioned above with a custom configuration file add *--cfg=myCustomConfigFile.json* at the end of the command. This allows users to configure and change the parameters of there simulation without having to modify any code. Changes made in the configuration file can immediately be accessible within the application without requiring a restart or recompile of the app. To refresh running application use the **C** key.