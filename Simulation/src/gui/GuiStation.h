//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUISTATION_H
#define PRODUCTION_LINE_SIMULATOR_GUISTATION_H


#include <QtWidgets/QWidget>
#include <src/productionStation/BaseProductionStation.h>
#include <QLabel>

class GuiStation : public QLabel{
    BaseProductionStation *connectedStation;
    uint32_t posx, posY;
    QLabel *l;
public:
    GuiStation(BaseProductionStation *connectedStation, QLabel*parent = nullptr);
    /**
     * return gui psoition
     * @return
     */
    // TODO getPosition();

};


#endif //PRODUCTION_LINE_SIMULATOR_GUISTATION_H
