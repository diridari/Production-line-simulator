//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEWORKPIECE_H
#define PRODUCTION_LINE_SIMULATOR_BASEWORKPIECE_H
#include <stdint.h>
#include <string>
#include <iostream>
#include <src/productionStation/BaseProductionStation.h>

#define WORKPIECE_MAX_INCREASE 10000
#define MAXPOSITION 1000000
using namespace std;
class BaseProductionStation;
class BaseWorkpiece {
private:
    uint32_t position;
    uint8_t size;
    const string workpieceName;

public:
    BaseWorkpiece();
    /**
     * create workpiece by name
     * position = 0
     * @param name name of obj
     */
    explicit BaseWorkpiece(string name);

    /**
    * create workpiece by name
    * @param name name of obj
    * @param position_ pos of obj
    */
    explicit BaseWorkpiece(uint32_t position_, string name = "Baseworkpiece", uint32_t size = 10);

    /**
     * get to current position of the obj
     * @return position
     */
    uint32_t getPosition() const;

    /**
     * set to obj position
     * Max : MAXPOSITION
     * Min : 0
     * @param pos
     * @return
     */
    uint8_t setPosition(uint32_t pos);

    /**
     * get obj name
     * @return
     */
    string getName() const;

    /**
     * can a box be plased on a position whitout bumping into on other box
     * @param posToPlace  base position to be placed. Can be negative to determine that the base position is on the prev station
     * @param toPlace box to be placed
     * @return can be placed on posToPlace
     */
    bool canWorkpieceBePlacedAt(int32_t posToPlace,BaseProductionStation *stationToPlace);

    /**
     * increase or decrease position by the paramter
     * @param increasePosition add position (max by WORKPIECE_MAX_INCREASE)
     * @return 1 == success
     */
    uint8_t moveBy(int32_t increasePosition);

    uint8_t getWorkpieceSize();

    friend std::ostream &operator<<(std::ostream &strm, BaseWorkpiece a);


};

#endif //PRODUCTION_LINE_SIMULATOR_BASEWORKPIECE_H
