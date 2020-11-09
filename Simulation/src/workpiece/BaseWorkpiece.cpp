//
// Created by basti on 03.11.2020.
//

#include "BaseWorkpiece.h"
#include <logging.h>
#include <sstream>
int32_t maxUsedSize = 0; // used to determine how far the next stage has to get checked to find other boxes

uint8_t BaseWorkpiece::moveBy(int32_t increasePosition) {
    if(increasePosition > WORKPIECE_MAX_INCREASE || increasePosition < -WORKPIECE_MAX_INCREASE){
        stringstream x;
        x << "Move box by " << increasePosition << "Max/Min Value are: +-"<<  WORKPIECE_MAX_INCREASE << " Obj: "<< *this;
        Log::log(x.str() ,Error);
        return 0;
    }
    uint32_t pos = getPosition() + increasePosition;

    return setPosition(pos);
}

BaseWorkpiece::BaseWorkpiece(string name): BaseWorkpiece(0,name) {
}
BaseWorkpiece::BaseWorkpiece(): BaseWorkpiece(0,"BaseWorkpiece"){
}

BaseWorkpiece::BaseWorkpiece(uint32_t position_, string name): position(position_),workpieceName(name),size(10) {
    if(size > maxUsedSize){
        maxUsedSize = size;
    }
}

string BaseWorkpiece::getName() const{
    return workpieceName;
}

uint32_t BaseWorkpiece::getPosition() const {
    return position;
}

uint8_t  BaseWorkpiece::setPosition(uint32_t newPos) {
    if(newPos <0 || newPos >MAXPOSITION){
        stringstream x;
        x << "Workpiece position is illegal.New pos should be: " << newPos <<"  Max position is: "<<  MAXPOSITION << " and Min  position is: 0.  Obj:" << *this;
        Log::log(x.str() ,Error);
        return 0;
    }
    position = newPos;
    return 1;
}



std::ostream &operator<<(ostream &strm, BaseWorkpiece a) {
    strm << "Workpiece : {" << a.getName() << ", pos:" << a.getPosition() <<"}" ;

    return strm << " ";
}

uint8_t BaseWorkpiece::getWorkpieceSize() {
    return size;
}

bool BaseWorkpiece::canWorkpieceBePlacedAt(int32_t posToPlace ,BaseProductionStation *stationToPlace) {
    if(stationToPlace == nullptr){ // end of Chain
        uint8_t radius = (getWorkpieceSize()/2 + getWorkpieceSize()%2);
        return posToPlace <-radius; // Prevent that a box can be moved over the end of the last Station
    }

    uint8_t radius = (getWorkpieceSize()/2 + getWorkpieceSize()%2);
    int32_t box_min = posToPlace-radius;
    int32_t box_max = posToPlace+radius;
    vector<BaseWorkpiece*> *boxSet = stationToPlace->getBoxesOnStation();
    if(boxSet->size() >0){ // has boxes
        for(int i = 0; i<boxSet->size();i++){ // check each box

            BaseWorkpiece *box = boxSet->at(i);
            if(box != this) { // do not check with itself
                uint8_t radius = (box->getWorkpieceSize() / 2 + box->getWorkpieceSize() % 2);
                int32_t tmp_min = box->getPosition() - radius;
                int32_t tmp_max = box->getPosition() + radius;
                if (box_min >= tmp_min && box_min <= tmp_max || box_max >= tmp_min && box_min <= tmp_max) {
                    return false;
                }
            }
        }
    }
    if(box_max >= BaseProductionStation::sizeOfStation - (maxUsedSize/2+maxUsedSize%2)){ // box hung into the next station
        int32_t posOnNextStation = posToPlace-BaseProductionStation::sizeOfStation;
        return canWorkpieceBePlacedAt(posOnNextStation,stationToPlace->getNextStationInChain());
    }

    return true;
}

