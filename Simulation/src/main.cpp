

#include <lib/SimpleLogging/include/logging.h>
#include <thread>
#include <src/gui/MainWindow.h>
#include <zconf.h>
#include <src/productionStation/conveyorbeltStation.h>
#include <QtWidgets/QApplication>
#include "version.h"
#include "src/gui/ObjMapper.h"
ObjMapper *objectMapper;


int main(int argc, char *argv[])
{

    Log::advancedConf()->setCliHighLight(false);
    Log::setLogLevel(Info,DebugL3);
    Log::log("run event Loop",Info);
    Log:log("start simulation version: " + to_string(VERSION_MAJOR) + "."+ to_string(VERSION_MINOR) + "."+ to_string(VERSION_REVISION) +"\r\n",Message);

    conveyorbeltStation *c5 = new conveyorbeltStation(nullptr,"band5");
    conveyorbeltStation *c4 = new conveyorbeltStation(c5,"band4");
    conveyorbeltStation *c3 = new conveyorbeltStation(c4,"band3");
    conveyorbeltStation *c2 = new conveyorbeltStation(c3,"band2");
    conveyorbeltStation *c1 = new conveyorbeltStation(c2,"band1");


    c1->setConveyorbeltState(ACTUATOR_ON);
    c2->setConveyorbeltState(ACTUATOR_ON);
    c3->setConveyorbeltState(ACTUATOR_ON);
    c4->setConveyorbeltState(ACTUATOR_ON);
    c5->setConveyorbeltState(ACTUATOR_ON);

    c1->setDirection(directionUp,directionDown);
    c2->setDirection(directionUp,directionLeft);
    c3->setDirection(directionRight,directionDown);
    c4->setDirection(directionUp,directionLeft);
    c5->setDirection(directionRight,directionLeft);

/*
       c1->setDirection(directionUp,directionDown);
       c2->setDirection(directionUp,directionRight);
       c3->setDirection(directionLeft,directionRight);
       c4->setDirection(directionLeft,directionUp);
       c5->setDirection(directionDown,directionUp);
*/

    BaseWorkpiece *wp1 = new BaseWorkpiece(0,"test-workpiece1");
    BaseWorkpiece *wp2 = new BaseWorkpiece(31,"test-workpiece1");
    BaseWorkpiece *wp3 = new BaseWorkpiece(62,"test-workpiece2");
    BaseWorkpiece *wp4 = new BaseWorkpiece(95,"test-workpiece3");


    c1->insertBox(wp1, wp1->getPosition());
    c1->insertBox(wp2, wp2->getPosition());
    c1->insertBox(wp3, wp3->getPosition());
    c1->insertBox(wp4, wp4->getPosition());
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

    w.show();
    return app.exec();
}
