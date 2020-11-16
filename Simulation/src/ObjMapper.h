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
    StationMapper(BaseProductionStation *wp_,GuiStation * gui_):station(wp_),gui(gui_){ };

}StationMapper;

typedef struct BoxMapper{
    BaseWorkpiece *wp;
    GuiBox * gui;
    BoxMapper(BaseWorkpiece *wp_,GuiBox * gui_):wp(wp_),gui(gui_){ };
}BoxMapper;


/**
 * Map Simulation Obj to Gui Obj
 */
class ObjMapper {
    vector<BoxMapper*> *boxMapper;
    vector<StationMapper*> *stationMapper;

public:
    ObjMapper();

    GuiStation * getGuiStation(BaseProductionStation *ps);
    GuiBox * getGuiBox(BaseWorkpiece *wp);

    void addStation(BaseProductionStation *ps, GuiStation *gs);
    void addBox(BaseWorkpiece *wp, GuiBox *gb);

};


#endif //PRODUCTION_LINE_SIMULATOR_OBJMAPPER_H
