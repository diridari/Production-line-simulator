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
    int MinX = 0;
    int MinY = 0;
    int MaxX = 0;
    int MaxY = 0;
    int currentX = 0;
    int currentY = 0;
    Direction     lastDir =  noDirection;

    while(station != nullptr){
        GuiStation *guiStation = new  GuiStation(station,station->getInputDirection(),station->getOutputDirection(),this);
        stationSet->push_back(guiStation); //generate all stations
        objectMapper->addStation(station,guiStation);
        // calculate the needed grid
        switch (station->getOutputDirection()) {
            case directionDown  : if(lastDir == directionLeft) {currentX-=2;}   else if(lastDir == directionRight){currentX+=2;}    else if(lastDir == directionDown ) {currentY +=2;}
                break;
            case directionUp    : if(lastDir == directionLeft) {currentX-=2;}  else if(lastDir == directionRight){currentX+=2;}   else if(lastDir == directionUp ){currentY -=2;}
                break;
            case directionLeft  : if(lastDir == directionUp)  {currentY -=2;}    else if(lastDir == directionDown) {currentY -=2;}   else if(lastDir == directionLeft ){currentX -=2;}
                break;
            case directionRight : if(lastDir == directionUp)  {currentY -=2;}    else if(lastDir == directionDown) {currentY +=2;}   else if(lastDir == directionRight ) {currentX +=2;}
                break;
        }
        if(currentX > MaxX) MaxX = currentX;
        if(currentX < MinX) MinX = currentX;
        if(currentY < MinY) MinY = currentY;
        if(currentY > MaxY) MaxY = currentY;

        lastDir = station->getOutputDirection();
        station = station->getNextStationInChain();
    }
    Log::log("Grid min/Max Pos: " + to_string(MinX) + ","+to_string(MinY),Info);
    gridSizeX = (-MinX)+MaxX+1;
    gridSizeY = (-MinY) + MaxY+2;
    Log::log("Grid size " + to_string(gridSizeX) + ","+to_string(gridSizeY),Info);

    currentX = 0;
    currentY = 0;
    setMinimumSize((-MinX+MaxX)*MinStationSize,(-MinY+MaxY)*MinStationSize);
    lastDir =  noDirection;
    for(int i = 0; i<stationSet->size();i++){

        GuiStation * station = stationSet->at(i);
        switch (station->getOutputDirection()) {
            case directionDown  : if(lastDir == directionLeft) {currentX-=1;}   else if(lastDir == directionRight){currentX+=2;}    else if(lastDir == directionDown ) {currentY +=2;} else {currentY +=1;}
                break;
            case directionUp    : if(lastDir == directionLeft) {currentX-=1;}  else if(lastDir == directionRight){currentX+=2;}   else if(lastDir == directionUp ){currentY -=2;} else {currentY -=1;}
                break;
            case directionLeft  : if(lastDir == directionUp)  {currentY -=1;}    else if(lastDir == directionDown) {currentY -=2;}   else if(lastDir == directionLeft ){currentX -=2;} else {currentX -=1;}
                break;
            case directionRight : if(lastDir == directionUp)  {currentY -=1;}    else if(lastDir == directionDown) {currentY +=2;}   else if(lastDir == directionRight ) {currentX +=2;} else {currentX +=1;}
                break;
        }
        station->setGridPosition(currentX + (-MinX), currentY + (-MinY)); // add the minimum size to the position to get the total position
        lastDir = station->getOutputDirection();
        station->move(station->getGridPositionX() * station->width(), station->getGridPositionY() * station->height());
    }
    Log::log("added all Gui Station: grid size {x:" + to_string((-MinX)+MaxX) +" , y:" +to_string((-MinY)+MaxY)+ "}",Info);

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