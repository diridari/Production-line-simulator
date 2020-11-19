//
// Created by basti on 17.11.2020.
//

#include "Placing.h"

bool Placing::canWorkpieceBePlacedAt(BaseProductionStation *stationToPlace, BaseWorkpiece* wp, int32_t posToPlace) {
    if(stationToPlace == nullptr){ // end of Chain
        uint8_t radius = (wp->getWorkpieceSize()/2 + wp->getWorkpieceSize()%2);
        return posToPlace <-radius; // Prevent that a box can be moved over the end of the last Station
    }
    if(!stationToPlace->stationCanReceiveNewBoxes()){
        Log::log("box can not be placed because station is blocked",Debug);
    }

    uint8_t radius = (wp->getWorkpieceSize()/2 + wp->getWorkpieceSize()%2);
    int32_t box_min = posToPlace-radius;
    int32_t box_max = posToPlace+radius;
    vector<BaseWorkpiece*> *boxSet = stationToPlace->getBoxesOnStation();
    if(boxSet->size() >0){ // has boxes
        for(int i = 0; i<boxSet->size();i++){ // check each box

            BaseWorkpiece *box = boxSet->at(i);
            if(box != wp) { // do not check with itself
                uint8_t radius = (box->getWorkpieceSize() / 2 + box->getWorkpieceSize() % 2);
                int32_t tmp_min = box->getPosition() - radius;
                int32_t tmp_max = box->getPosition() + radius;
                if (box_min >= tmp_min && box_min <= tmp_max || box_max >= tmp_min && box_min <= tmp_max) {
                    return false;
                }
            }
        }
    }
    if(box_max >= BaseProductionStation::sizeOfStation - (BaseWorkpiece::getMaxUsedSize()/2+BaseWorkpiece::getMaxUsedSize()%2)){ // box hung into the next station
        int32_t posOnNextStation = posToPlace-BaseProductionStation::sizeOfStation;
        return Placing::canWorkpieceBePlacedAt(stationToPlace->getNextStationInChain(), wp, posOnNextStation);
    }

    return true;
}

bool Placing::canStationReceiveNewWorkpiece(BaseProductionStation * station, uint8_t sizeOfBox) {
    if(station == nullptr){
        Log::log("Placing canStationReceiveNewWorkpiece",Error);
        return false;
    }
    // get left box
    for(int i = 0; i<station->getBoxesOnStation()->size();i++){ // has boxes
        BaseWorkpiece *box = station->getBoxesOnStation()->at(i);
        if(box->getPosition() <=  (sizeOfBox/2 + sizeOfBox%2)){
            return false;
        }
    }

    return true;
}

guiPos Placing::calculateGuiPosition(BaseWorkpiece *wp, BaseProductionStation *station) {
    if(wp == nullptr){
        Log::log("Placing calculateGuiPosition received nullpointer",Error);
        return guiPos(0,0);
    }
    return calculateGuiPosition(wp->getPosition(),station);
}

guiPos Placing::calculateGuiPosition(uint32_t pos, BaseProductionStation *station) {
    if(station == nullptr){
        Log::log("Placing calculateGuiPosition received nullpointer",Error);
        return guiPos(0,0);
    }
    uint32_t posX,posY;
    // Calculate the pos depending of station direction
    if(pos <= 50){
        switch (station->getInputDirection()) {
            case directionUp    : posX = 50; posY = pos;        break;
            case directionDown  : posX = 50; posY = 100-pos;    break;
            case directionLeft  : posX = pos; posY = 50;        break;
            case directionRight : posX = 100- pos; posY = 50;   break;
        }
    }else {
        switch (station->getOutputDirection()) {
            case directionUp    : posX = 50; posY = 100-pos;    break;
            case directionDown  : posX = 50; posY = pos;        break;
            case directionLeft  : posX = 100 - pos; posY = 50;  break;
            case directionRight : posX = pos; posY = 50;        break;
        }

    }
    return  guiPos(posX,posY);
}
