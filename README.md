# HiL_Taktstrasse
This application has the intension simulate the “Fischertechik Taktstraße” (https://www.fischertechnik.de/en/products/teaching/training-models/96790-edu-indexed-line-with-two-machining-stations-24v-education).

Since due to a corona crisis it is not (or only limitedly) possible to access the real cycle line, this project has the goal to simulate such a production line.

In this way it should be possible to keep the lecture "Embedded Systems" in the future.

However, the project does not have the goal to simulate the plant one to one, but only the basic idea.

The application does only simulate the actuators, sensors, boxes and Stations. The production logic (when to turn on/off the individual actuators) has to get defined by the user. For that there is a special API. 

clone:
	git clone --recurse-submodules https://github.com/intel/Dependency-Reduction-Unit-Framework.git 
	
## Features
* Define you own production station layout
* Extend existing actuators and sensors by abstracting the existing ones 
* View  the current simulation state.
* Access each sensor and actuators by the api

# Usage
* See 'Simulation/Usage.md'

# API Documentation
## Idea
Each station shout have a defined unique name (e.g. pusher1, miller. driller) and a defined set of actuators and sensors. 
This can be used to access each sensor and actuator by addressing the station followed by the sensor/actuator. 
Sensors can only be read and actuators can only be written. 

## Protocol structure
Each call has the same structure:

      [get/set] [stationName] [Sensor/ActuatorID] [opt. Data]
      
A get request for the second sensor in the “pushStation1” would be:

     get pushStation1 2
A set request for the second  actuator on the Milling station to the value “1” would be

      set Milling 2 1 


# Trouble Shouting

## Compile Error

#### Reason

* Submodules not present

### Appearance

    find: ‘../../lib/SimpleLogging/src’: No such file or directory
    find: ‘../../lib/CPP-Argument-Parser/src’: No such file or directory
#### Solution
This error results by not initialized submodules. To update those sub modules call:

    git submodule init
    git submodule update
