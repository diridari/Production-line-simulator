//
// Created by basti on 11.11.2020.
//

#include "MainWindow.h"
#include <QTimer>

#include <QtWidgets/QApplication>
#include <src/main.h>
#include <QMenuBar>

MainWindow::MainWindow(BaseProductionStation *startStation, QWidget *parent) : startStation(startStation), QWidget(parent){
    Log::log("generate Main window",Message);
    stationSet = new vector<GuiStation*>;
    BaseProductionStation *station = startStation;
    int gridX= 0,gridY=0;
    int gridSizeX = 1;
    int gridSizeY = 1;
    int gridMinX = 1;
    int gridMinY = 1;
    Direction     lastDir =  noDirection;

    while(station != nullptr){
        GuiStation *guiStation = new  GuiStation(station,station->getInputDirection(),station->getOutputDirection(),this);
        guiStation->setGridPosition(gridX, gridY); // add the minimum size to the position to get the total position
        switch (station->getOutputDirection()) {
            case directionDown  : if(lastDir == directionLeft) {gridX-=2;}   else if(lastDir == directionRight){gridX+=2;}    else if(lastDir == directionDown ) {gridY +=2;}
                break;
            case directionUp    : if(lastDir == directionLeft) {gridX-=2;}  else if(lastDir == directionRight){gridX+=2;}   else if(lastDir == directionUp ){gridY -=2;}
                break;
            case directionLeft  : if(lastDir == directionUp)  {gridY -=2;}    else if(lastDir == directionDown) {gridY -=2;}   else if(lastDir == directionLeft ){gridX -=2;}
                break;
            case directionRight : if(lastDir == directionUp)  {gridY -=2;}    else if(lastDir == directionDown) {gridY +=2;}   else if(lastDir == directionRight ) {gridX +=2;}
                break;
        }
        stationSet->push_back(guiStation);
        objectMapper->addStation(station,guiStation);
        if(gridX > gridSizeX) gridSizeX = gridX;
        if(gridY > gridSizeY) gridSizeY = gridY;
        if(gridX < gridMinX) gridMinX = gridX;
        if(gridY < gridMinY) gridMinY = gridY;

        lastDir = station->getOutputDirection();
        station = station->getNextStationInChain();
    }

    //
    for(int i = 0; i<stationSet->size();i++ ){
        GuiStation * station = stationSet->at(i);
        station->setGridPosition(station->getGridPositionX()-gridMinX,station->getGridPositionY()-gridMinY);
        station->move((station->getGridPositionX()) * station->width(), (station->getGridPositionY()) * station->height());
    }

    ///////////

    Log::log("added all Gui Station: grid size {x:" + to_string(gridSizeX) +" , y:" +to_string(gridSizeY)+ "}",Info);

    Log::log("Start Timer",Info);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(100);
    Log::log("Main window Done",Message);

    // Resize


}


void MainWindow::update() {
    Log::log("update gui",Debug);
    BaseProductionStation *station = startStation;
    station->runSimulationStep(); // update simulation
    while (station != nullptr){
        objectMapper->getGuiStation(station)->handleBoxes();
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
    return;

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