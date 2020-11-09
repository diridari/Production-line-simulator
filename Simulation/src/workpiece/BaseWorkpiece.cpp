//
// Created by basti on 03.11.2020.
//

#include "BaseWorkpiece.h"
#include <logging.h>
#include <sstream>

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

