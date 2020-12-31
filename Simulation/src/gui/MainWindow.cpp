//
// Created by basti on 11.11.2020.
//

#include "MainWindow.h"
#include <QTimer>

#include <QtWidgets/QApplication>
#include <src/main.h>
#include <QMenuBar>
#include "GuiPlacing.h"

MainWindow::MainWindow(BaseProductionStation *startStation, QWidget *parent) : startStation(startStation), QWidget(parent){
    Log::log("generate Main window",Message);
    stationSet = new vector<GuiStation*>;
    BaseProductionStation *station = startStation;

    Direction     lastDir =  noDirection;
    GuiPlacing p;
    while(station != nullptr){
        GuiStation *guiStation = new  GuiStation(station,station->getInputDirection(),station->getOutputDirection(),this);
        GridPosition gp = p.addStation(station);
        objectMapper->addStation(station,guiStation);
        guiStation->setGridPosition(gp.x, gp.y); // add the minimum size to the position to get the total position
        Log::log("pre place station at grid pos:"+to_string(gp.x)+","+to_string(gp.y),Message);
        station = station->getNextStationInChain();
        stationSet->push_back(guiStation);
    }

    //
    setMinimumSize(MinStationSize*p.getGridSize().x,MinStationSize*p.getGridSize().y);
    GridPosition offset = p.getCurrentOffset();
    for(int i = 0; i<stationSet->size();i++ ){
        GuiStation * station = stationSet->at(i);
        station->setGridPosition(station->getGridPositionX()-offset.x,station->getGridPositionY()-offset.y);
        Log::log("place station at:"+to_string(station->getGridPositionX())+","+to_string(station->getGridPositionY()),Message);

        station->move((station->getGridPositionX()) * station->width(), (station->getGridPositionY()) * station->height());
    }
    gridSizeY = p.getGridSize().y;
    gridSizeX = p.getGridSize().x;

    ///////////

    Log::log("added all Gui Station: grid size {x:" + to_string(gridSizeX) +" , y:" +to_string(gridSizeY)+ "}",Info);

    Log::log("Start Timer",Info);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(100);
    Log::log("Main window Done",Message);

    show();

    // to calc the box size is necessary to create on
    BaseWorkpiece *wp = new BaseWorkpiece(43,"shall not be part of the simulation!!");
    startStation->insertBox(wp,50);
    update();
    GuiBox *gb = objectMapper->getGuiBox(wp);
    objectMapper->dropBox(wp);
    if(!dropBox(wp)){
        Log::log("Gui Box failed to delete Box",Error);
    }
    delete gb;
    delete wp;

}


void MainWindow::update() {
    Log::log("update gui",Debug);
    BaseProductionStation *station = startStation;
    station->runSimulationStep(); // update simulation
    while (station != nullptr){
        GuiStation *g =  objectMapper->getGuiStation(station);
        g->update();
        g->handleBoxes();
        station = station->getNextStationInChain();
    }

}

bool MainWindow::dropBox(BaseWorkpiece *wp) {
    if(wp == nullptr){
        Log::log("Gui: dropbox recevied nullptr",Error);
        return false;
    }
    BaseProductionStation *station = startStation;
    while(startStation != nullptr){
                if(station->hasBox(wp)){
                    station->dropBox(wp);
                    return true;
                }
                station = station->getNextStationInChain();
    }
    Log::log("cound not find a box wit the name: "+ wp->getName(),Message);
    return false;
}

void MainWindow::resizeEvent( QResizeEvent *e) {
    if(stationSet == nullptr) return;
    Log::log(" handle resize event from: " + to_string(e->oldSize().width()) + "," + to_string(e->oldSize().height()) +
             "  to new size: " + to_string(e->size().width()) + "," + to_string(e->size().height()), DebugL2);
    for (int i = 0; i < stationSet->size(); i++) {
        GuiStation *s = stationSet->at(i);
        int scaleX = std::get<0>(s->stationScaleFaktors);
        int scaleY = std::get<1>(s->stationScaleFaktors);

        s->resize(e->size().width() / gridSizeX * scaleX, e->size().height() / gridSizeY * scaleY);
        s->move(s->getGridPositionX() * e->size().width() / gridSizeX,
                s->getGridPositionY() * e->size().height() / gridSizeY);

    }
    int baseSize = e->size().width() / gridSizeX;
    if (e->size().height() / gridSizeY < baseSize)
        baseSize = e->size().height() / gridSizeY;


    for (int i = 0; i < boxSet->size(); i++) {
        int t = baseSize/boxSet->at(i)->connectedWorkpiece->getWorkpieceSize();
        boxSet->at(i)->resize(t,t);
    }

}