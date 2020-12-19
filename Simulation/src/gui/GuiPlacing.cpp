//
// Created by basti on 19.12.2020.
//

#include "GuiPlacing.h"

GridPosition GuiPlacing::addStation(BaseProductionStation *toInsert) {

     GridPosition gp = GridPosition(currentX,currentY);
    switch (toInsert->getOutputDirection()) {
        case directionDown  :
            if(lastDirection == directionRight)     {currentX++; currentY++; gp.x++;}
            else if(lastDirection == directionLeft) { currentX--; currentY++;gp.x--;}
            else if (lastDirection == noDirection)  {  maxY=2;maxX=1;}
            else {currentY +=2;                                              gp.y += 2;}
            break;
        case directionUp    :
            if(lastDirection == directionRight)     {currentX++; currentY--;   gp.x++; }
            else if(lastDirection == directionLeft) { currentX--; currentY--;  gp.x--; }
            else if (lastDirection == noDirection)  {  currentY=-2;maxX=1;}
            else { currentY -=2;                                               gp.y -= 2;}
            gp = GridPosition(currentX,currentY);

            break;
        case directionLeft  :
            if(lastDirection == directionUp)        { currentY--; currentX--;   gp.y--;}
            else if(lastDirection == directionDown) { currentY++;currentX--;    gp.y++;}
            else if (lastDirection == noDirection)  {  currentX=-2;maxY=1;}
            else {currentX -=2;                                                  gp.x -= 2;}
            gp = GridPosition(currentX,currentY);
            break;
        case directionRight :
            if(lastDirection == directionUp)        {currentY--;currentX++;    gp.y--;}
            else if(lastDirection == directionDown) {currentY++;currentX++;    gp.y++; }
            else if (lastDirection == noDirection)  {maxX=2;maxY=1;}
            else {currentX += 2;                                                gp.x += 2;}
            break;
    }
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

GridPosition GuiPlacing::getCurrentOfset() {
    return GridPosition(minX, minY);
}
