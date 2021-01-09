//
// Created by basti on 19.12.2020.
//

#include "GuiPlacing.h"


GridPosition GuiPlacing::addStation(BaseProductionStation *toInsert) {


    switch (toInsert->getOutputDirection()) {
        case directionDown  :
            if(lastDirection == directionRight)     { currentX+=2;}
            else if(lastDirection == directionLeft) { currentX--; }
            else if (lastDirection == noDirection)  { }
            else {currentY +=2;                                               }
            setBorder( currentX, currentX + 1, currentY , currentY +2);
            break;
        case directionUp    :
            if(lastDirection == directionRight)     {currentX+=2; currentY-=1;  }
            else if(lastDirection == directionLeft) { currentX--; currentY-=1; }
            else if (lastDirection == noDirection)  {  currentY=-2;}
            else { currentY -=2;                                               ;}
            setBorder( currentX, currentX + 1, currentY , currentY +2);
            break;
        case directionLeft  :
            if(lastDirection == directionUp)        { currentY--; currentX-=1;  }
            else if(lastDirection == directionDown) { currentY+=2;currentX-=1;    }
            else if (lastDirection == noDirection)  {  currentX=-2; }
            else {currentX -=2;                                                }
            setBorder( currentX, currentX + 2, currentY , currentY +1);
            break;
        case directionRight :
            if(lastDirection == directionUp)        {currentY--;    }
            else if(lastDirection == directionDown) {currentY+=2;    }
            else if (lastDirection == noDirection)  {}
            else {currentX += 2;                                               }
            setBorder( currentX, currentX + 2, currentY , currentY +1);

            break;
    }
    GridPosition gp = GridPosition(currentX,currentY);
    lastDirection = toInsert->getOutputDirection();
    if(currentX > maxX) maxX = currentX;
    if(currentY > maxY) maxY = currentY;
    if(currentX < minX) minX = currentX;
    if(currentY < minY) minY = currentY;

    return gp;
}

GridPosition GuiPlacing::getGridSize() {
    return GridPosition(maxX-minX,maxY-minY);
}

GridPosition GuiPlacing::getCurrentOffset() {
    return GridPosition(minX, minY);
}

void GuiPlacing::setBorder(int minx_, int maxx_, int miny_, int maxy) {
    if(maxx_ > maxX) maxX = maxx_;
    if(maxy > maxY) maxY = maxy;
    if(minx_ < minX) minX = minx_;
    if(miny_ < minY) minY = miny_;
}

