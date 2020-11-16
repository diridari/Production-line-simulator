//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUISTATION_H
#define PRODUCTION_LINE_SIMULATOR_GUISTATION_H


#include <QtWidgets/QWidget>
#include <src/productionStation/BaseProductionStation.h>
#include <QLabel>

class GuiStation : public QWidget{
    BaseProductionStation *connectedStation;
    uint32_t posX, posY;
    QLabel *l;
    Direction inputDirection,outputDirection;


public:
    GuiStation(BaseProductionStation *connectedStation, Direction inputDirection, Direction outputDirection,  QWidget *parent = nullptr);
    Direction getInputDirection();
    Direction getOutputDirection();

    /**
     * return gui psoition
     * @return
     */
     void setPosition(int posX, int posY);
     uint32_t getGridPositionX(){
         return posX;
     }
    uint32_t getGridPositionY(){
         return posY;
     }
    void handleBoxes();


};


#endif //PRODUCTION_LINE_SIMULATOR_GUISTATION_H
