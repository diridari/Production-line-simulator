//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUIBOX_H
#define PRODUCTION_LINE_SIMULATOR_GUIBOX_H


#include <src/productionStation/BaseProductionStation.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class GuiBox : public QWidget{
Q_OBJECT
    QLabel *l;

protected:
    void mousePressEvent(QMouseEvent * event);
public:
    BaseWorkpiece *connectedWorkpiece;

    GuiBox(BaseWorkpiece *connectedWorkpiece, QWidget *parent_ = nullptr);
    /**
     * calculate the new positio based on the widget pos
     * @param BaseOffset base offset
     * @param baseWidgetSizeX size of station widget
     * @param baseWidgetSizeY size of station widget
     * @return new abs pos
     */
    QPoint getNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY, BaseProductionStation *station );
    /**
     * move to new position
     * @param BaseOffset base offset
     * @param baseWidgetSizeX size of station widget
     * @param baseWidgetSizeY size of station widget
     */
    void moveToNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,BaseProductionStation * station);
    static int getWPSIze();
public slots:
    void resizeEvent( QResizeEvent *e);
    void update();



};



#endif //PRODUCTION_LINE_SIMULATOR_GUIBOX_H
