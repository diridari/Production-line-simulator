//
// Created by basti on 11.11.2020.
//
#include <src/main.h>
#include "MainWindow.h"
#include "GuiStation.h"


void GuiStation::setPosition(int posX_, int posY_) {
    Log::log("gui: set Position of " + connectedStation->getStationName() + " to x:" + to_string(posX_) + " , y:"+ to_string(posY_),Info);
    posX = posX_;
    posY = posY_;
}
Direction GuiStation::getInputDirection() {
    return inputDirection;
}

Direction GuiStation::getOutputDirection() {
    return outputDirection;
}

GuiStation::GuiStation(BaseProductionStation *connectedStation, Direction inputDirection, Direction outputDirection,
                       QWidget *parent): QWidget(parent),outputDirection(outputDirection),inputDirection(inputDirection),connectedStation(connectedStation) {
    l = new QLabel(this);
    l->setPixmap(QPixmap("../img/BaseStation.png").scaled(MinStationSize,MinStationSize,Qt::KeepAspectRatio));
    setMinimumSize(MinStationSize,MinStationSize);
    l->setScaledContents(true);
}

void GuiStation::handleBoxes() {
    Log::log("update gui for station "+ connectedStation->getStationName(),Debug);
    vector<BaseWorkpiece*> * boxes = connectedStation->getBoxesOnStation();
    for(int i = 0; i< boxes->size();i++){
        BaseWorkpiece *wp = boxes->at(i);
        GuiBox *gb = objectMapper->getGuiBox(wp);
        if(gb == nullptr){
            gb = new GuiBox(wp,this);
            objectMapper->addBox(wp,gb);
        }
        gb->setParent(this); // forece take ownership
        uint32_t widgetSize = this->size().height();
        gb->move((widgetSize/100)*wp->getPosition(),widgetSize/2);

    }

}

