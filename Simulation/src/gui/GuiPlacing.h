//
// Created by basti on 19.12.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUIPLACING_H
#define PRODUCTION_LINE_SIMULATOR_GUIPLACING_H


#include <src/productionStation/BaseProductionStation.h>

typedef struct GridPosition{
    int x = 0;
    int y = 0;
    GridPosition (int x, int y):x(x), y(y){};
}GridPosition;
class GuiPlacing {
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;
    Direction lastDirection = Direction::noDirection;
    int currentX = 0;
    int currentY = 0;
    void setBorder(int minx_, int maxx_, int miny_, int maxy);
public:
    /**
     * get the relativ grid position of a station
     * @param toInsert
     * @return
     */
    GridPosition addStation(BaseProductionStation * toInsert);
    /**
     * get the offset to the point 0,0
     * @return grid ofset
     */
    GridPosition getCurrentOffset();


    GridPosition getGridSize();

};


#endif //PRODUCTION_LINE_SIMULATOR_GUIPLACING_H
