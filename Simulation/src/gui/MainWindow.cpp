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

void runGui(int argc, char *argv[], BaseProductionStation *startStation) {
    QApplication app(argc,argv);
    MainWindow w;
    // Event loop
    Log::log("gui exit: " + to_string(app.exec()),Error);
    exit(-1);
}
void runGui2(QApplication *app) {
    Log::log("gui exit: " + to_string(app->exec()),Error);
    exit(-1);
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){


    QGridLayout *gridLayout = new QGridLayout;
    boxSet = new vector<GuiBox*>();
    mainWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Add the previous two inner layouts
    mainLayout->addLayout(gridLayout);

    mainWidget->setLayout(mainLayout);
    mainWidget->show();
}


void MainWindow::update() {
    for(int i = 0; i< boxSet->size();i++){
        boxSet->at(i)->updateBoxPos();
    }
}

