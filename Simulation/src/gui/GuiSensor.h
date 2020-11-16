//
// Created by basti on 16.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUISENSOR_H
#define PRODUCTION_LINE_SIMULATOR_GUISENSOR_H


#include <src/sensors/BaseSensor.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#define SensorOFFIMG "../img/lightSensIdle.png"
#define SensorONIMG "../img/lightSensDetect.png"
class GuiSensor : public QWidget{
    BaseSensor * connectedSensor;
    QLabel *l;
    sensorState lastState = SENSOR_OFF;
public:
    GuiSensor(BaseSensor *connectedSensor_, QWidget *parent, Direction inputDirection,
              Direction outPutDirection);
    /**
     * calculate the new positio based on the widget pos
     * @param BaseOffset base offset
     * @param baseWidgetSizeX size of station widget
     * @param baseWidgetSizeY size of station widget
     * @return new abs pos
     */
    QPoint getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY, Direction inputDirection = directionUp,Direction outputDirection = directionDown );

    void update();
};


#endif //PRODUCTION_LINE_SIMULATOR_GUISENSOR_H
