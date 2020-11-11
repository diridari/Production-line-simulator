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
}

void ObjMapper::insertBox(BaseWorkpiece *wp, BaseProductionStation *newStation) {
    GuiBox *b = mainWindow->addBox(wp,getGuiStation(newStation));
    if(b != nullptr) {
        BoxMapper *m = new BoxMapper;
        m->gui = b;
        m->wp = wp;
    }
}

void ObjMapper::changeBoxStation(BaseWorkpiece *wp, BaseProductionStation *newStation) {
    GuiBox *g =getGuiBox(wp);
    if(g == nullptr){
        Log::log("no gui box for box" + (wp->getName()),Error);
        return;
    }
    g->setStation(getGuiStation(newStation));
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

ObjMapper::ObjMapper(MainWindow *mainWindow_) {
    boxMapper = new  vector<BoxMapper*>();
    stationMapper = new vector<StationMapper*>();
    mainWindow = mainWindow_;
}

void ObjMapper::addStatin(BaseProductionStation *ps) {
    GuiStation *g = mainWindow->addStation(ps);
    if(g != nullptr){
        StationMapper *m = new StationMapper;
        m->station = ps;
        m->gui = g;
        stationMapper->push_back(m);
    }
}
