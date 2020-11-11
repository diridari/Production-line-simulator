

#include <lib/SimpleLogging/include/logging.h>
#include <thread>
#include <src/gui/MainWindow.h>
#include <zconf.h>
#include <src/productionStation/conveyorbeltStation.h>
#include <QtWidgets/QApplication>
#include "version.h"
#include "ObjMapper.h"
#include "main.h"
int main(int argc, char *argv[])
{

    Log::advancedConf()->setCliHighLight(false);
    Log::setLogLevel(Message,DebugL3);
    Log::log("run event Loop",Info);
    Log:log("start simulation version: " + to_string(VERSION_MAJOR) + "."+ to_string(VERSION_MINOR) + "."+ to_string(VERSION_REVISION) +"\r\n",Message);

    conveyorbeltStation *c3 = new conveyorbeltStation(nullptr,"band 3");
    conveyorbeltStation *c2 = new conveyorbeltStation(c3,"band 2");
    conveyorbeltStation *c1 = new conveyorbeltStation(c2,"band 1");
    c3->setConveyorbeltState(ACTUATOR_ON);
    c2->setConveyorbeltState(ACTUATOR_ON);
    c1->setConveyorbeltState(ACTUATOR_ON);
    BaseWorkpiece *wp1 = new BaseWorkpiece;
    c1->insertBox(wp1);
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

    QApplication app(argc,argv);
    MainWindow w;
    void run (BaseProductionStation *c1,MainWindow *w);
    new thread(run,c1,&w);
    usleep(10000);
    objMapper = new ObjMapper(&w);
    objMapper->addStatin(c1);
    objMapper->addStatin(c2);
    objMapper->insertBox(wp1,c1);
    return app.exec();
}

void run (BaseProductionStation *c1,MainWindow *w) {
    while (1) {
        usleep(100000);
        Log::log("run simulation step", Info);
        c1->runSimulationStep();
        w->update(); // update gui

    }

}