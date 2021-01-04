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


By calling the application with the argument:

    --currentSetup

the application generates an inforamtion about the current setup. Here it is also possible to see the api for the current setup.


