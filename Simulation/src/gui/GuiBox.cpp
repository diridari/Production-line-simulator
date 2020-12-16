//
// Created by basti on 11.11.2020.
//

#include "GuiBox.h"
#include "MainWindow.h"
#include <src/workpiece/Placing.h>
#include <src/main.h>

GuiBox::GuiBox( BaseWorkpiece *connectedWorkpiece, QWidget *parent_):
        QWidget(parent_),connectedWorkpiece(connectedWorkpiece) {
    Log::log("new gui Box for " + connectedWorkpiece->getName(),Info);
    l = new QLabel(this);
    uint32_t size = MinStationSize*2/100*connectedWorkpiece->getWorkpieceSize();
    l->setPixmap(QPixmap("../img/box.png").scaled(size,size,Qt::KeepAspectRatio));
    l->show();

}

QPoint GuiBox::getNewPos(QPoint BaseOffset, uint32_t WidgetSizeX, uint32_t WidgetSizeY,BaseProductionStation *station  ) {
    guiPos p = Placing::calculateGuiPosition(connectedWorkpiece, station);
    uint32_t posX,posY;
    posX = BaseOffset.x() + (WidgetSizeX/100) * p.posX ;
    posY = BaseOffset.y() +(WidgetSizeY/100) * p.posY ;
    return QPoint(posX,posY);

}

void GuiBox::moveToNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,BaseProductionStation * station) {

    move(getNewPos(BaseOffset,baseWidgetSizeX,baseWidgetSizeY,station));
}

void GuiBox::mousePressEvent(QMouseEvent *event) {
    switch (event->button()) {
        case Qt::LeftButton :         Log::log("clicked on Box "+connectedWorkpiece->getName()+"  with left",Debug);break;
        case Qt::RightButton :         Log::log("clicked on Box"+connectedWorkpiece->getName()+"  with right --> erase box",Debug);
            objectMapper->dropBox(connectedWorkpiece);
            if(!((MainWindow *)parent())->dropBox(connectedWorkpiece)){
                Log::log("Gui Box failed to delete Box",Error);
            }
            delete this;
            break;
        default:
            Log::log("clicked on Main  with "+ to_string(event->button()),Message);break;
    }
}

void GuiBox::resizeEvent(QResizeEvent *e) {
    cout << "resize to " << e->size().height()<<endl;
    l->resize(e->size());
    l->show();
}

