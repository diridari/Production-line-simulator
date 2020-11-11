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

void runGui(int argc, char **argv, BaseProductionStation *startStation) {
    QApplication app(argc, argv);
    MainWindow w(startStation);

    // Event loop
    Log::log("gui exit: " + to_string(app.exec()),Error);
    exit(-1);
}

MainWindow::MainWindow(BaseProductionStation *startStation_, QWidget *parent) : QWidget(parent), startStation(startStation_){

    QGridLayout *gridLayout = new QGridLayout;

    l1 = new QLabel;
    l2 = new QLabel;
    l3 = new QLabel;
    l4 = new QLabel(l1);


    l1->setPixmap(QPixmap("../img/BaseStation.png").scaled(200,200,Qt::KeepAspectRatio)); // insert image and define resulution
    l1->setScaledContents(true); // adjust image to WIndo size
    l2->setPixmap(QPixmap("../img/BaseStation.png").scaled(200,200,Qt::KeepAspectRatio)); // insert image and define resulution
    l2->setScaledContents(true); // adjust image to WIndo size
    l3->setPixmap(QPixmap("../img/BaseStation.png").scaled(200,200,Qt::KeepAspectRatio)); // insert image and define resulution
    l3->setScaledContents(true); // adjust image to WIndo size
    // addWidget(*Widget, row, column, rowspan, colspan)
    l4->setPixmap(QPixmap("../img/box.png").scaled(50,50,Qt::KeepAspectRatio)); // insert image and define resulution
    l4->move(100,0);
    l4->setScaledContents(true); // adjust image to WIndo size
    // 0th row

    gridLayout->addWidget(l1,0,0,1,1);
    gridLayout->addWidget(l2,1,0,1,1);
    gridLayout->addWidget(l3,2,0,1,1);
    // Outer Layer
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(l4);
    // Add the previous two inner layouts
    mainLayout->addLayout(gridLayout);
    QWidget *w = new QWidget();
    w->setLayout(mainLayout);


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(100);
    w->show();
    l1->show();
    l2->show();
    l3->show();
    l4->show();
    l4->raise(); // move lable to forground
}


void MainWindow::update() {
    QPoint pos = l4->pos();
    pos.setY((pos.y() + 2));
    if(pos.y() >l1->height()) {
        l4->setParent(l2);
        Log::log("move parent",Message);
        pos.setY(0);
    }

    l4->move(pos);
    l4->show();
    l4->raise();
}

