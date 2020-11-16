//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUIBOX_H
#define PRODUCTION_LINE_SIMULATOR_GUIBOX_H


#include <src/productionStation/BaseProductionStation.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "GuiStation.h"

class GuiBox : public QWidget{
Q_OBJECT
    BaseWorkpiece *connectedWorkpiece;
    GuiStation *currentStation; // determine abs pos + direction of movement
    uint32_t AbsPosX,AbsPosY;
    QLabel *l;
public:
    GuiBox(BaseWorkpiece *connectedWorkpiece, QWidget *parent = nullptr);
    /**
     * calculate the new positio based on the widget pos
     * @param BaseOffset base offset
     * @param baseWidgetSizeX size of station widget
     * @param baseWidgetSizeY size of station widget
     * @return new abs pos
     */
    QPoint getNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY, Direction inputDirection = directionUp,Direction outputDirection = directionDown );
    /**
     * move to new position
     * @param BaseOffset base offset
     * @param baseWidgetSizeX size of station widget
     * @param baseWidgetSizeY size of station widget
     */
    void moveToNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,Direction inputDirection = directionUp,Direction outputDirection = directionDown );


};



#endif //PRODUCTION_LINE_SIMULATOR_GUIBOX_H
