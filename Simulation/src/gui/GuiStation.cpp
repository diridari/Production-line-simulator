//
// Created by basti on 11.11.2020.
//
#include <src/main.h>
#include "MainWindow.h"
#include "GuiStation.h"
#include "GuiSensor.h"
#include <QPushButton>
#include <src/workpiece/Placing.h>

void GuiStation::setGridPosition(int posX_, int posY_) {
    Log::log("gui: set Position of " + connectedStation->getStationName() + " to x:" + to_string(posX_) + " , y:" + to_string(posY_), Info);
    gridPosX = posX_;
    gridPosY = posY_;
}
Direction GuiStation::getInputDirection() {
    return inputDirection;
}

Direction GuiStation::getOutputDirection() {
    return outputDirection;
}

GuiStation::GuiStation(BaseProductionStation *connectedStation, Direction inputDirection, Direction outputDirection,
                       QWidget *parent): QWidget(parent),outputDirection(outputDirection),inputDirection(inputDirection),connectedStation(connectedStation) {
    Log::log("create new Gui Station for "+ connectedStation->getStationName(),Debug);
    QPixmap p;
    QTransform rot;
    QSize size;

    // get station direction to termine picmap and rotation matrix
    if(inputDirection == directionUp && outputDirection == directionDown || inputDirection == directionDown && outputDirection ==  directionUp) {
        imagePath = "../img/BaseStation.png";
        size = QSize(MinStationSize,MinStationSize*2);
    }else if (inputDirection == directionLeft && outputDirection == directionRight || inputDirection == directionRight && outputDirection ==  directionLeft){
        imagePath = "../img/BaseStation.png";
        rot = QTransform().rotate(90);
        size = QSize(MinStationSize*2,MinStationSize);
    }else if(inputDirection == directionUp && outputDirection == directionRight) {
        imagePath = "../img/BaseStationEdge.png";
        size = QSize(MinStationSize*2,MinStationSize);
    }else if(inputDirection == directionRight && outputDirection == directionUp){
        imagePath = "../img/BaseStationEdge.png";
        size = QSize(MinStationSize*2,MinStationSize);
        rot = QTransform().rotate(90);
        rot = rot.rotate(180,Qt::XAxis);
    }
    else if(inputDirection == directionRight && outputDirection == directionDown) {
        imagePath = "../img/BaseStationEdge.png";
        rot = QTransform().rotate(90);
        size = QSize(MinStationSize,MinStationSize*2);

    }
    else if(inputDirection == directionDown && outputDirection == directionRight){
        imagePath = "../img/BaseStationEdge.png";
        rot = rot.rotate(180);
        rot = rot.rotate(180,Qt::YAxis);
        size = QSize(MinStationSize*2,MinStationSize);
    }else if(inputDirection == directionDown && outputDirection == directionLeft) {
        imagePath = "../img/BaseStationEdge.png";
        rot = QTransform().rotate(180);
        size = QSize(MinStationSize*2,MinStationSize);

    }else if(inputDirection == directionLeft && outputDirection == directionDown){
        imagePath = "../img/BaseStationEdge.png";
        size = QSize(MinStationSize,MinStationSize*2);
        rot = QTransform().rotate(90);
        rot =rot.rotate(180,Qt::XAxis);


    }
    else if(inputDirection == directionLeft && outputDirection == directionUp || inputDirection == directionUp && outputDirection == directionLeft){
        imagePath = "../img/BaseStationEdge.png";
        rot = QTransform().rotate(270);
        size = QSize(MinStationSize,MinStationSize*2);

    }else{
        Log::log("Gui station could not find rotation matrix to determine station image: inputdir" + to_string(inputDirection) + " outputdir: "+ to_string(outputDirection),Error);
    }
    l = new QLabel(this);
    QPixmap pix = QPixmap(imagePath.c_str()).scaled(size,Qt::KeepAspectRatio).transformed(rot);
    l->setPixmap(pix);
    l->setScaledContents(true);
    l->setMinimumSize(size);
    setMinimumSize(size);
    setMaximumSize(size);
    Log::log("widget size: "+to_string(l->width())+to_string(l->height()) ,Info)

    Log::log("create station Info lable for"+ connectedStation->getStationName(),DebugL3);
    // PrintState Text
    stationState = new QLabel(this);
    stationState->setScaledContents(true);
    stationState->setText("station State gets updated on first Frame");
    stationState->adjustSize();
    stationState->show();

    // Display  Sensors
    Log::log("create station Sensors  ",DebugL3);
    guiSensors = new  vector<GuiSensor *>();
    vector<BaseSensor *> * sensors = connectedStation->getSensors();
    for(int i = 0; i<sensors->size();i++){
        GuiSensor *sen = new GuiSensor(sensors->at(i), connectedStation, this );
        guiSensors->push_back(sen);

    }
    // Display actuators
    Log::log("create station Actuator",DebugL3);
    vector<BaseActuator *> * actuators = connectedStation->getActuators();
    guiActuators = new vector<GuiActuator*>();
    for(int i = 0; i<actuators->size();i++){
        GuiActuator *guiActuator = new GuiActuator(actuators->at(i),connectedStation,this);
        guiActuator->raise();
        guiActuators->push_back(guiActuator);
    }
    Log::log("created all actuators",Debug);
    // Change actuator State Button
    stationActuator = new QPushButton(this);
    string s = "set "+string(connectedStation->getActuators()->at(0)->getActuatorName());
    stationActuator->setText(s.c_str());
    stationActuator->raise();
    stationActuator->move(this->size().width()-stationActuator->size().width(), 1);
    stationActuator->show();
    connect(stationActuator, SIGNAL(clicked()), this, SLOT(updateActuatorState()));
    if(connectedStation->getActuators()->size() >=2){
        stationActuator2 = new QPushButton(this);
        s = "set "+string(connectedStation->getActuators()->at(1)->getActuatorName());
        stationActuator2->setText(s.c_str());
        stationActuator2->raise();
        stationActuator2->move(this->size().width()-stationActuator2->size().width(), stationActuator2->size().height()+2);
        stationActuator2->show();
        connect(stationActuator2, SIGNAL(clicked()), this, SLOT(updateActuatorState2()));
    }


}

void GuiStation::handleBoxes() {
    Log::log("update gui for station "+ connectedStation->getStationName(),Debug);
    vector<BaseWorkpiece*> * boxes = connectedStation->getBoxesOnStation();
    for(int i = 0; i< boxes->size();i++){
        BaseWorkpiece *wp = boxes->at(i);
        GuiBox *gb = objectMapper->getGuiBox(wp);
        if(gb == nullptr){
            Log::log("found no matching gui box --> create new one ",Debug);
            // Boxes habe the parent widget as parent because otherwise the box gets cut on the station edges
            gb = new GuiBox(wp,this->parentWidget());
            gb->show();
            objectMapper->addBox(wp,gb);
        }
        // move box
        gb->moveToNewPos(pos(),width(),height(), connectedStation);
    }

    // Update State text
    Log::log("update Station Sates on Gui",DebugL2);
    string stationStateText = "station State :\r\n";
    vector<BaseActuator *>* actators = connectedStation->getActuators();
    vector<BaseSensor *>* sensors = connectedStation->getSensors();
    for(int i = 0; i <actators->size();i++){
        stationStateText += actators->at(i)->getActuatorName() + " :" +  to_string(actators->at(i)->getActuatorState()) +"\r\n";
    }
    for(int i = 0; i <sensors->size();i++){
        stationStateText += sensors->at(i)->getSensorName() + " :" +  to_string(sensors->at(i)->getSensorState()) +"\r\n";
    }
    Log::log("current station state: " + stationStateText, DebugL3)
    stationState->setText(stationStateText.c_str());
    stationState->adjustSize();
    stationState->show();
    show();

    // update senspos
    for(int i = 0; i<guiSensors->size();i++){
        guiSensors->at(i)->update();
    }
    // update actuators
    for(int i = 0; i<guiActuators->size();i++){
        guiActuators->at(i)->update();
    }



}

void GuiStation::updateActuatorState() {
    Log::log("gui change actuator state for "+connectedStation->getStationName(),Debug);
    connectedStation->getActuators()->at(0)->toogleState();
    stationActuator->raise();

}
void GuiStation::updateActuatorState2() {
    Log::log("gui change actuator state for "+connectedStation->getStationName(),Debug);
    connectedStation->getActuators()->at(1)->toogleState();
    stationActuator->raise();

}


void GuiStation::setWidgetSize(uint32_t widgetSizeX_, uint32_t widgetSizeY_){
    widgetSizeX = widgetSizeX_;
    widgetSizeY = widgetSizeY_;
    l->setPixmap(QPixmap(imagePath.c_str()).scaled(widgetSizeX,widgetSizeY,Qt::KeepAspectRatio));

}

BaseProductionStation *GuiStation::getConnectedStation() {
    return connectedStation;
}

void GuiStation::mousePressEvent(QMouseEvent *event) {
    guiPos p(0,0);
    uint8_t proc;
    switch (event->button()) {
        case Qt::LeftButton :
            Log::log("clicked on Station"+connectedStation->getStationName() + "  with left --> try to insert box" ,Info);
            p = guiPos( event->x()*100 /width() ,event->y() *100 / height());
            proc = Placing::calculateProcessFromGuiPos(p,connectedStation);
            connectedStation->insertBox(new BaseWorkpiece(proc,"clickedWP"),proc);
            Log::log("click pos "+ to_string(event->x())+ "," + to_string( event->y()),Debug);
            Log::log("place obj at: "+ to_string(p.posX)+ "," + to_string(p.posY) + "that is : " + to_string(proc),Debug);
            break;
        case Qt::RightButton :
                Log::log("clicked on Station  with right --> no box here --> ignore",Debug); break;
        default:
            Log::log("clicked on Main  with "+ to_string(event->button())+ "  --> ignore" ,Info);break;
    }
}
