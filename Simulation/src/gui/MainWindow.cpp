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
    int nextX = 0;
    int nextY = 0;
    while(station != nullptr){

        GuiStation *guiStation = new  GuiStation(station,station->getInputDirection(),station->getOutputDirection(),this);
        stationSet->push_back(guiStation); //generate all stations
        objectMapper->addStation(station,guiStation);
        // calculate the needed grid
        switch (station->getOutputDirection()) {
            case directionDown  : nextY++;    if(nextY > MaxX) MaxY = nextY; break;
            case directionUp    : nextY--;    if(nextY < MinX) MinY = nextY; break;
            case directionLeft  : nextX--;    if(nextX < MinY) MinX = nextX; break;
            case directionRight : nextX++;    if(nextX > MaxY) MaxX = nextX; break;
        }
        station = station->getNextStationInChain();
    }
    //setMinimumSize((-MinX+MaxX)*MinStationSize,(-MinY+MaxY)*MinStationSize);
    Log::log("added all Gui Station: grid size {x:" + to_string((-MinX)+MaxX) +" , y:" +to_string((-MinY)+MaxY)+ "}",Info);
    int currentX = 0;
    int currentY = 0;
    for(int i = 0; i<stationSet->size();i++){

        GuiStation * station = stationSet->at(i);
        station->setGridPosition(currentX + (-MinX), currentY + (-MinY)); // add the minimum size to the position to get the total position
        switch (station->getOutputDirection()) {
            case directionDown  : currentY++; break;
            case directionUp    : currentY--; break;
            case directionLeft  : currentX--; break;
            case directionRight : currentX++; break;
        }
        station->move(station->getGridPositionX() * MinStationSize, station->getGridPositionY() * MinStationSize);
    }
    Log::log("Start Timer",Info);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(100);
    Log::log("Main window Done",Message);

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

