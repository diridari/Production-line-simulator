//
// Created by basti on 11.11.2020.
//

#include "ObjMapper.h"

GuiStation *ObjMapper::getGuiStation(BaseProductionStation *ps) {
    Log::log("get Obj Mapper for Station: " + ps->getStationName(),DebugL2);
    GuiStation *guiStation = nullptr;
    for(int i = 0; i<stationMapper->size();i++){
        StationMapper *m = stationMapper->at(i);
        if(m->station == ps){
            Log::log("mapped station to gui station. "+ ps->getStationName(),DebugL3);
            return m->gui;
        }
    }
    Log::log("failed to map station to gui station. Station Name: "+ ps->getStationName(),Error);
    return nullptr;
}


GuiBox *ObjMapper::getGuiBox(BaseWorkpiece *wp) {
    Log::log("search Obj Mapper for Box: " + wp->getName(),DebugL2);
    BaseWorkpiece *baseWorkpiece = nullptr;
    for(int i = 0; i<boxMapper->size();i++){
        BoxMapper *m = boxMapper->at(i);
        if(m->wp == wp){
            Log::log("mapped station to gui station. "+ wp->getName(),DebugL3);
            return m->gui;
        }
    }
    return nullptr;
}

ObjMapper::ObjMapper() {
    Log::log("generate new obj Mapper",Info)
    boxMapper = new  vector<BoxMapper*>();
    stationMapper = new vector<StationMapper*>();
}

void ObjMapper::addStation(BaseProductionStation *ps, GuiStation *gs) {
    Log::log("add Obj Mapper for Station: " + ps->getStationName(),DebugL2);
    stationMapper->push_back(new StationMapper(ps,gs));
}

void ObjMapper::addBox(BaseWorkpiece *wp, GuiBox *gb) {
    Log::log("add Obj Mapper for Box" + wp->getName(),DebugL2);
    boxMapper->push_back(new BoxMapper(wp,gb));
}

void ObjMapper::dropBox(BaseWorkpiece *wp) {
    for(int i = 0; i<boxMapper->size();i++){
        if(boxMapper->at(i)->wp == wp){
            boxMapper->erase(boxMapper->begin()+i);
            return;
        }
    }
}

