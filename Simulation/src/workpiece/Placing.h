//
// Created by basti on 17.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_PLACING_H
#define PRODUCTION_LINE_SIMULATOR_PLACING_H


#include <src/productionStation/BaseProductionStation.h>
/**
 * position on Gui
 * Range : 0-100
 */
struct guiPos{
    uint8_t posX,posY;
    guiPos(uint8_t posX, uint8_t posY): posX(posX),posY(posY){};
};
class Placing {
public:
    /**
    * can a box be plased on a position whitout bumping into on other box
    * @param toPlace box to be placed
    * @param posToPlace  base position to be placed. Can be negative to determine that the base position is on the prev station
    * @return can be placed on posToPlace
    */
    static bool canWorkpieceBePlacedAt(BaseProductionStation *stationToPlace, BaseWorkpiece* wp, int32_t posToPlace);

    /**
    * check whether a box can be placed at the front of the station
    * @param sizeOfBox
    * @return true if can be placed
    */
    static bool canStationReceiveNewWorkpiece(BaseProductionStation *station, uint8_t sizeOfBox = 1);

    /**
     * calculate dependent to the station direction the position
     * range 0-100
     * @return
     */
    static guiPos calculateGuiPosition(BaseWorkpiece *wp , BaseProductionStation *station );

    /**
    * calculate dependent to the station direction the position
    * range x,y: 0-100
    * @return
    */
    static guiPos calculateGuiPosition(uint32_t pos, BaseProductionStation *station );

    /**
     * calculate the processing state dependent to the gui pos
     * @param pos range 0-100
     * @return process staste
     */
    static uint8_t calculateProcessFromGuiPos(guiPos pos,BaseProductionStation *station);

};


#endif //PRODUCTION_LINE_SIMULATOR_PLACING_H
