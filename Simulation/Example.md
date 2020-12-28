# Simple Example
to run a simple example the application can be called with the arguments:
    
    ./Production_line_simulator -s conveyorbeltStation c1 Left Right -s MillAndDrillStation m1 Left Right

keep in mind that the stations are in reverse order.

This command will create a simulation with to stations. 

To view the current setup the argument "--currentSetup" can be attached.

     ./Production_line_simulator -s conveyorbeltStation c1 Left Right -s MillAndDrillStation m1 Left Right --currentSetup

This will show the current setup (until the argument gets added). Now it is possible to view each station with the connected sensors and actuators and there positions.
Also the api accesses are getting displayed. 

e.g.

    The current setup is:
    1:   Station: m1
        Actuators:
                * Conveyorbelt. If activated this actuator moves all boxes.
                    position: 50
                    Api access: "set m1 0 <0/1>"
                * Miller and Driller. This Actuator has no real effect
                    position: 50
                    Api access: "set m1 1 <0/1>"
        Sensors:
                * Light Barrier. When a box passes through the sensor, an active signal is sent by the sensor.
                    position: 50
                    Api access: "get m1 0"

         
    2:   Station: c1
        Actuators:
                * Conveyorbelt. If activated this actuator moves all boxes.
                    position: 50
                    Api access: "set c1 0 <0/1>"
        Sensors:
                * Light Barrier. When a box passes through the sensor, an active signal is sent by the sensor.
                    position: 80
                    Api access: "get c1 0"

To access those sensors and actuators by the api it just has to send the string after "Api access".
With the argument --port


    