//
// Created by basti on 17.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUIACTUATOR_H
#define PRODUCTION_LINE_SIMULATOR_GUIACTUATOR_H


#include <src/actuators/BaseActuator.h>
#include <QtCore/QPoint>
#include <QLabel>

class GuiActuator: public QWidget {
    QPoint BaseOffset;
    BaseActuator * connectedActuator;
    QLabel *l;
    BaseProductionStation *station;
    string lastImg = "";
    QTransform rot;
    QSize actuatorSize;
    /**
   * calculate the new position based on the widget pos
   * @param BaseOffset base offset
   * @param baseWidgetSizeX size of station widget
   * @param baseWidgetSizeY size of station widget
   * @return new abs pos
   */
    QPoint getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY);
public:
    GuiActuator(BaseActuator *connectedActuator_, BaseProductionStation *station, QWidget *parent);

    void update();
};


#endif //PRODUCTION_LINE_SIMULATOR_GUIACTUATOR_H
