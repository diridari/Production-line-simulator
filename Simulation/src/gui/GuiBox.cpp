//
// Created by basti on 11.11.2020.
//

#include "GuiBox.h"

GuiBox::GuiBox(BaseWorkpiece *connectedWorkpiece, GuiStation * currentStation, QLabel *parent):
        QLabel(parent), connectedWorkpiece(connectedWorkpiece),currentStation(currentStation) {
    Log::log("new gui statioon",Error);

    setPixmap(QPixmap("../img/box.png").scaled(50,50,Qt::KeepAspectRatio));
    setScaledContents(true);
    move(currentStation->pos().x(),currentStation->pos().y() + connectedWorkpiece->getPosition());
}

void GuiBox::updateBoxPos() {
    move(currentStation->pos().x(),currentStation->pos().y() + connectedWorkpiece->getPosition());
}

void GuiBox::setStation(GuiStation *gs) {
    currentStation = gs;
}
