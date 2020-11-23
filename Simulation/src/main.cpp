

#include <lib/SimpleLogging/include/logging.h>
#include <thread>
#include <src/gui/MainWindow.h>
#include <zconf.h>
#include <src/productionStation/conveyorbeltStation.h>
#include <QtWidgets/QApplication>
#include <src/productionStation/PushStation.h>
#include <src/productionStation/MillAndDrillStation.h>
#include "version.h"
#include "src/gui/ObjMapper.h"
ObjMapper *objectMapper;
conveyorbeltStation *c6 = new conveyorbeltStation(nullptr,"band5");
PushStation *c5 = new PushStation(c6,"band4");
MillAndDrillStation *c4 = new MillAndDrillStation(c5,"band3");
MillAndDrillStation *c3 = new MillAndDrillStation(c4,"band3");
PushStation *c2 = new PushStation(c3,"band3");
conveyorbeltStation *c1 = new conveyorbeltStation(c2,"band1");

int main(int argc, char *argv[])
{

    Log::advancedConf()->setCliHighLight(false);
    Log::setLogLevel(Info,DebugL3);
    Log::log("run event Loop",Info);
    Log:log("start simulation version: " + to_string(VERSION_MAJOR) + "."+ to_string(VERSION_MINOR) + "."+ to_string(VERSION_REVISION) +"\r\n",Message);



    c1->setDirection(directionDown,directionUp);
    c2->setDirection(directionDown,directionRight);
    c3->setDirection(directionLeft,directionRight);
    c4->setDirection(directionLeft,directionRight);
    c5->setDirection(directionLeft,directionDown);
    c6->setDirection(directionUp,directionDown);
    
    // simulation steps
    /**
     * 1. Operate all Workpieces
     * 1.1 each station has a set of boxes that are on that stage
     * 1.2 a box can move to the next station if
     *          a) the next station is movable
     *          b) there are no blocking elements
     *        then it is changing the current station
     * 1.3 a box can move inside the same station if
     *          a) the station is moving
     *          b) there is no blocking box on the left hand side
     *
     * 2. Depending of the new box positions the sensor states gets calculated
     * 3.
     */
    objectMapper = new ObjMapper;
    QApplication app(argc,argv);
    MainWindow w(c1);
    void userLoop();
    new thread(userLoop);
    w.show();
    return app.exec();
}

void runOnTime(){
    sleep(2);
    bool detectBox = false;
    c1->setConveyorbeltState(actuatorState::ACTUATOR_ON);
    for(int i = 0; i<70;i++){
        usleep(100000);
        if(c1->getSensors()->at(0)->getSensorState() == sensorState::SENSOR_ON)
            detectBox = true;
    }
    if(!detectBox)
        return;
    sleep(1);
    c1->setConveyorbeltState(actuatorState::ACTUATOR_OFF);

    // Push 1
    c2->getActuators()->at(0)->toogleState(); // Push on
    sleep(7);
    c2->getActuators()->at(0)->toogleState(); // Push back
    sleep(7);
    c2->getActuators()->at(0)->toogleState(); // Push off

    // Mill
    detectBox = false;
    c3->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_ON);
    for(int i = 0; i<60;i++){
        usleep(100000);
        if(c3->getSensors()->at(0)->getSensorState() == sensorState::SENSOR_ON && !detectBox){
            detectBox = true;
            c3->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_OFF);
            c3->getActuators()->at(1)->setActuatorState(actuatorState::ACTUATOR_ON);

            sleep(1);
            c3->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_ON);
            c3->getActuators()->at(1)->setActuatorState(actuatorState::ACTUATOR_OFF);

        }
    }
    c3->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_OFF);
    if(!detectBox)
        return;
    // Drill
    detectBox = false;
    c4->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_ON);
    for(int i = 0; i<60;i++){
        usleep(100000);
        if(c4->getSensors()->at(0)->getSensorState() == sensorState::SENSOR_ON && !detectBox){
            detectBox = true;
            c4->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_OFF);
            c4->getActuators()->at(1)->setActuatorState(actuatorState::ACTUATOR_ON);

            sleep(1);
            c4->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_ON);
            c4->getActuators()->at(1)->setActuatorState(actuatorState::ACTUATOR_OFF);

        }

    }
    c4->getActuators()->at(0)->setActuatorState(actuatorState::ACTUATOR_OFF);
    if(!detectBox)
        return;

}
void userLoop(){
    while(1){
       runOnTime();
    }
}