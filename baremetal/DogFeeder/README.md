# DogFeeder Repo

In a not so far future, our dog will be home alone for +8 hours.
Some of the residense fear that our dog will be lonely and therefor the need for some active toys which can be fully automated to start at given periods throughout the day.


## The dogfeeder project
This project is ment to be a solution to a lonly and starving dog. The dogfeeder is required to automatically open up a door to deliever delicious dog food at specific periodes through out the day.

## Use Cases

### User wants to give the dog a treat
<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/baremetal/DogFeeder/Docs/diagrams/UseCase_TreatDog.bmp" width="700" height="600">
</p>


## Software achitecture

### ServoController

The servo controller is a class-container used for encapsulating the functionallity of activating the servo motors. 
In this project, two servo motors and two current sesnors will be used, however the ServoController will make it look like they are a single unit, for the end user.



<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/baremetal/DogFeeder/Docs/diagrams/DogFeeder diagrams.bmp" width="500" height="600">
</p>

## PCB board
The PCB board developed is ment to support a esp32-dev board with up to 3 actuators powered by an external power source. The board is a 4-layer board and is created through the opensource project https://www.kicad.org/

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/baremetal/DogFeeder/Images/pcb_board.png" width="600" height="500">
</p>

