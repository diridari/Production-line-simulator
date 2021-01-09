//
// Created by basti on 16.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUISENSOR_H
#define PRODUCTION_LINE_SIMULATOR_GUISENSOR_H


#include <src/sensors/BaseSensor.h>
#include <src/productionStation/BaseProductionStation.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#define SensorOFFIMG "../img/lightSensIdle.png"
#define SensorONIMG "../img/lightSensDetect.png"
class GuiSensor : public QWidget{
    BaseSensor * connectedSensor;
    QLabel *l;
    sensorState lastState = SENSOR_OFF;
    BaseProductionStation *station;
    /**
   * calculate the new positio based on the widget pos
   * @param BaseOffset base offset
   * @param baseWidgetSizeX size of station widget
   * @param baseWidgetSizeY size of station widget
   * @return new abs pos
   */
    QPoint getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY);

public:
    GuiSensor(BaseSensor *connectedSensor_, BaseProductionStation *station, QWidget *parent);

    void update();
};


#endif //PRODUCTION_LINE_SIMULATOR_GUISENSOR_H
