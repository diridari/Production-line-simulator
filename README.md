# HiL_Taktstrasse
This application has the intension simulate the “Fischertechik Taktstraße” (https://www.fischertechnik.de/en/products/teaching/training-models/96790-edu-indexed-line-with-two-machining-stations-24v-education)
Since due to a corona crisis it is not (or only limitedly) possible to access the real cycle line, this project has the goal to simulate such a production line.

In this way it should be possible to keep the lecture "Embedded Systems" in the future.

However, the project does not have the goal to simulate the plant one to one, but only the basic idea.

The application does only simulate the actuators, sensors, boxes and Stations. The production logic (when to turn on/off the individual actuators) has to get defined by the user. For that there is a special API. 

## Features
* Define you own production station layout
* Extend existing actuators and sensors by abstracting the existing ones 
* View  the current simulation sate by an gui.
* Access each sensor and actuators by the api

# Usage

## Clone 

clone: git clone --recurse-submodules https://github.com/intel/Dependency-Reduction-Unit-Framework.git 
## API

## Gui 

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
