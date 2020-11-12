//
// Created by basti on 11.11.2020.
//

#include <QtWidgets/QGridLayout>
#include "MainWindow.h"
#include <QTimer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QApplication>
#include <lib/SimpleLogging/include/logging.h>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    Log::log("generate Main window",Info);

    gridLayout = new QGridLayout;
    mainWidget = new QWidget();
    QLabel *l1 = new QLabel;
    l1->setPixmap(QPixmap("../img/BaseStation.png").scaled(200,200,Qt::KeepAspectRatio)); // insert image and define resulution
    l1->setScaledContents(true); // adjust image to WIndo size
   // gridLayout->addWidget(new GuiStation(nullptr),1,1,1,1);
  //  gridLayout->addWidget(new GuiStation(nullptr),0,0,1,1);

    mainWidget->setMinimumSize(600,600);


    boxSet = new vector<GuiBox*>();

    // Add the previous two inner layouts
    mainWidget->setLayout(gridLayout);
    mainWidget->show();
}


void MainWindow::update() {
    Log::log("update gui",Message);
    for(int i = 0; i< boxSet->size();i++){
        boxSet->at(i)->updateBoxPos();
    }
}

