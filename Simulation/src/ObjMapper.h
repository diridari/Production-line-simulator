//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_OBJMAPPER_H
#define PRODUCTION_LINE_SIMULATOR_OBJMAPPER_H

#include <src/productionStation/BaseProductionStation.h>
#include "src/gui/GuiStation.h"
#include "src/gui/GuiBox.h"
#include "src/gui/MainWindow.h"
typedef struct StationMapper{
    BaseProductionStation *station;
    GuiStation * gui;
}StationMapper;

typedef struct BoxMapper{
    BaseWorkpiece *wp;
    GuiBox * gui;
}BoxMapper;


/**
 * Map Simulation Obj to Gui Obj
 */
class ObjMapper {
    vector<BoxMapper*> *boxMapper;
    vector<StationMapper*> *stationMapper;
    MainWindow *mainWindow;

public:
    ObjMapper( MainWindow *mainWindow_);

    GuiStation * getGuiStation(BaseProductionStation *ps);
    GuiBox * getGuiBox(BaseWorkpiece *wp);

    void insertBox(BaseWorkpiece *wp,BaseProductionStation * newStation);
    void deleteBox(BaseWorkpiece *wp){
        //TODO
    };
    void changeBoxStation(BaseWorkpiece *wp,BaseProductionStation * newStation);
    void addStatin(BaseProductionStation *ps);

};


#endif //PRODUCTION_LINE_SIMULATOR_OBJMAPPER_H
