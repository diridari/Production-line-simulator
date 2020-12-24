//
// Created by basti on 19.12.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_ARGUMENTCALLBACKFUNCTIONS_H
#define PRODUCTION_LINE_SIMULATOR_ARGUMENTCALLBACKFUNCTIONS_H
#include <argvParser.h>
#include "productionStation/conveyorbeltStation.h"
#include "productionStation/BaseProductionStation.h"
#include "productionStation/MillAndDrillStation.h"
#include "productionStation/PushStation.h"
extern int port;
extern bool generateAPI;
extern bool cliHighlighting;
extern BaseProductionStation *newStartStation;


argvParser *initProgramArguments();
void logArgumentStatus();
#endif //PRODUCTION_LINE_SIMULATOR_ARGUMENTCALLBACKFUNCTIONS_H
