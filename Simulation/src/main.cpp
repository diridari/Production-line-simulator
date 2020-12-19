

#include <zmq.h>
#include <lib/SimpleLogging/include/logging.h>
#include <thread>
#include <src/gui/MainWindow.h>
#include <zconf.h>
#include <src/productionStation/conveyorbeltStation.h>
#include <QtWidgets/QApplication>
#include <src/productionStation/PushStation.h>
#include <src/productionStation/MillAndDrillStation.h>
#include <src/api/api.h>
#include "version.h"
#include "ArgumentCallbackFunctions.h"
#include "src/gui/ObjMapper.h"
ObjMapper *objectMapper;
conveyorbeltStation *c6 = new conveyorbeltStation(nullptr,"End");
PushStation *c5 = new PushStation(c6,"Pusher2");
MillAndDrillStation *c4 = new MillAndDrillStation(c5,"Drill");
MillAndDrillStation *c3 = new MillAndDrillStation(c4,"Mill");
PushStation *c2 = new PushStation(c3,"Pusher1");
conveyorbeltStation *c1 = new conveyorbeltStation(c2,"Start");

int main(int argc, char *argv[])
{



    Log::setLogLevel(Info,DebugL3);
    argvParser *p = initProgramArguments();
    // analyze the given parameters
    if (!p->analyseArgv(argc, argv)) {
        p->printHelpMessage(cliHighlighting);
        return -5;
    }
    logArgumentStatus();
    Log:log("start simulation version: " + to_string(VERSION_MAJOR) + "."+ to_string(VERSION_MINOR) + "."+ to_string(VERSION_REVISION) +"\r\n",Message);



    c1->setDirection(directionDown,directionUp);
    c2->setDirection(directionDown,directionRight);
    c3->setDirection(directionLeft,directionRight);
    c4->setDirection(directionLeft,directionRight);
    c5->setDirection(directionLeft,directionDown);
    c6->setDirection(directionUp,directionDown);

    // init api
    api * api_ = new api(c1);

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
