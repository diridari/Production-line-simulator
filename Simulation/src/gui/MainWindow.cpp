//
// Created by basti on 11.11.2020.
//

#include <QtWidgets/QGridLayout>
#include "MainWindow.h"
#include <QTimer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QApplication>
#include <lib/SimpleLogging/include/logging.h>
#include <src/main.h>


MainWindow::MainWindow(BaseProductionStation *startStation, QWidget *parent) : startStation(startStation), QWidget(parent){
    Log::log("generate Main window",Info);
    stationSet = new vector<GuiStation*>;
    BaseProductionStation *station = startStation;
    int MinX = 0;
    int MinY = 0;
    int MaxX = 0;
    int MaxY = 0;
    int nextX = 0;
    int nextY = 0;
    while(station != nullptr){

        Log::log("create new Gui Station",Info);
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
    Log::log("added all Gui Station: grid size {x:" + to_string((-MinX)+MaxX) +" , y:" +to_string((-MinY)+MaxY)+ "}",Message);
    int currentX = 0;
    int currentY = 0;
    for(int i = 0; i<stationSet->size();i++){

        GuiStation * station = stationSet->at(i);
        station->setPosition(currentX  + (-MinX),currentY + (-MinY)); // add the minimum size to the position to get the total position
        switch (station->getOutputDirection()) {
            case directionDown  : currentY++; break;
            case directionUp    : currentY--; break;
            case directionLeft  : currentX--; break;
            case directionRight : currentX++; break;
        }
        station->move(station->getPositionX()*MinStationSize,station->getPositionY()*MinStationSize);
    }

}


void MainWindow::update() {
    Log::log("update gui",Message);
    BaseProductionStation *station = startStation;
    station->runSimulationStep(); // update simulation
    while (station != nullptr){
        objectMapper->getGuiStation(station)->handleBoxes();
        station = station->getNextStationInChain();
    }

}

