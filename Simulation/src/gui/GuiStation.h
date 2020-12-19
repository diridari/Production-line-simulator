//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUISTATION_H
#define PRODUCTION_LINE_SIMULATOR_GUISTATION_H


#include <QtWidgets/QWidget>
#include <src/productionStation/BaseProductionStation.h>
#include <QLabel>
#include <QtWidgets/QPushButton>
#include "GuiSensor.h"
#include "GuiActuator.h"
#include "GuiBox.h"
#include <QMouseEvent>
class GuiStation : public QWidget{
Q_OBJECT
    BaseProductionStation *connectedStation;
    uint32_t gridPosX, gridPosY;
    QLabel *l;
    Direction inputDirection,outputDirection;
    QLabel * stationState;
    uint32_t widgetSizeX,widgetSizeY;
    string imagePath;
    vector<GuiSensor *> * guiSensors;
    vector<GuiActuator*> *guiActuators;
    QPushButton *stationActuator = nullptr;
    QPushButton *stationActuator2 = nullptr ;

protected:
    void mousePressEvent(QMouseEvent * event);
public:
    BaseProductionStation *getConnectedStation();
    GuiStation(BaseProductionStation *connectedStation, Direction inputDirection, Direction outputDirection,  QWidget *parent = nullptr);
    Direction getInputDirection();
    Direction getOutputDirection();
    tuple<int,int> stationScaleFaktors = tuple<int,int>(2,1);;

    /**
     * return gui psoition
     * @return
     */
     void setGridPosition(int posX, int posY);
     uint32_t getGridPositionX(){
         return gridPosX;
     }
    uint32_t getGridPositionY(){
         return gridPosY;
     }
     void handleBoxes();

     void setWidgetSize(uint32_t widgetSizeX_, uint32_t widgetSizeY_);

public slots:
    void updateActuatorState();
    void updateActuatorState2();
    void resizeEvent( QResizeEvent *e);

};


#endif //PRODUCTION_LINE_SIMULATOR_GUISTATION_H
