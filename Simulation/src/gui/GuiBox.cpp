//
// Created by basti on 11.11.2020.
//

#include "GuiBox.h"

GuiBox::GuiBox(BaseWorkpiece *connectedWorkpiece, GuiStation * currentStation, QWidget *parent):
            QWidget(parent), connectedWorkpiece(connectedWorkpiece),currentStation(currentStation) {
    l = new QLabel();
    l->setPixmap(QPixmap("../img/box.png").scaled(50,50));

    l->move(currentStation->pos().x(),currentStation->pos().y() + connectedWorkpiece->getPosition());
    l->show();
}

void GuiBox::updateBoxPos() {
    l->move(currentStation->pos().x(),currentStation->pos().y() + connectedWorkpiece->getPosition());
}

void GuiBox::setStation(GuiStation *gs) {
    currentStation = gs;
}
