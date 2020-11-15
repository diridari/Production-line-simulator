//
// Created by basti on 11.11.2020.
//

#include "ObjMapper.h"

GuiStation *ObjMapper::getGuiStation(BaseProductionStation *ps) {
    GuiStation *guiStation = nullptr;
    for(int i = 0; i<stationMapper->size();i++){
        StationMapper *m = stationMapper->at(i);
        if(m->station == ps){
            return m->gui;
        }
    }
    Log::log("failed to map station to gui station",Error);
    return nullptr;
}


GuiBox *ObjMapper::getGuiBox(BaseWorkpiece *wp) {
    BaseWorkpiece *baseWorkpiece = nullptr;
    for(int i = 0; i<boxMapper->size();i++){
        BoxMapper *m = boxMapper->at(i);
        if(m->wp == wp){
            return m->gui;
        }
    }
    return nullptr;
}

ObjMapper::ObjMapper() {
    boxMapper = new  vector<BoxMapper*>();
    stationMapper = new vector<StationMapper*>();
}

void ObjMapper::addStation(BaseProductionStation *ps, GuiStation *gs) {
    stationMapper->push_back(new StationMapper(ps,gs));
}

void ObjMapper::addBox(BaseWorkpiece *wp, GuiBox *gb) {
    boxMapper->push_back(new BoxMapper(wp,gb));
}

