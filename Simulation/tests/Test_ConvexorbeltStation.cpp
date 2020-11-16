//
// Created by basti on 09.11.2020.
//

#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
#include "../src/workpiece/BaseWorkpiece.h"


TEST(ConveyorbeltStation,moveOneBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece();
    ASSERT_TRUE(s1.insertBox(&wp1));
    for(int i = 0; i<10; i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),0);
    s1.setConveyorbeltState(ACTUATOR_ON);
    for(int i = 0; i<10; i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),20);
    s1.setConveyorbeltState(ACTUATOR_OFF);
    for(int i = 0; i<10; i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),20);
}
TEST(ConveyorbeltStation,RunFull){
    conveyorbeltStation s1(nullptr);
    s1.setConveyorbeltState(ACTUATOR_ON);
    BaseWorkpiece wp1 = BaseWorkpiece(90);
    s1.insertBox(&wp1);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),92);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),94);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),94);
}

TEST(ConveyorbeltStation,RunOverStation){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    s1.setConveyorbeltState(ACTUATOR_ON);
    s2.setConveyorbeltState(ACTUATOR_ON);
    BaseWorkpiece wp1 = BaseWorkpiece(90);
    s1.insertBox(&wp1);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),92);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),94);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),96);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),98);
    ASSERT_EQ(s1.getBoxesOnStation()->size(),1);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),0);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),0);
    ASSERT_EQ(s1.getBoxesOnStation()->size(),0);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),1);
    s1.runSimulationStep();
    ASSERT_EQ(wp1.getPosition(),2);
    ASSERT_EQ(s1.getBoxesOnStation()->size(),0);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),1);
}
TEST(ConveyorbeltStation,RunTOWPOverStation){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    s1.setConveyorbeltState(ACTUATOR_ON);
    s2.setConveyorbeltState(ACTUATOR_ON);
    BaseWorkpiece wp1 = BaseWorkpiece(90);
    BaseWorkpiece wp2 = BaseWorkpiece(78);
    BaseWorkpiece wp3 = BaseWorkpiece(45);
    s1.insertBox(&wp1);
    s1.insertBox(&wp2);
    s1.insertBox(&wp3);
    for(int i = 0; i<4;i++){
        s1.runSimulationStep();
        ASSERT_EQ(s1.getBoxesOnStation()->size(),3);
        ASSERT_EQ(s2.getBoxesOnStation()->size(),0);
    }
    for(int i = 0; i<5;i++){
        s1.runSimulationStep();
        ASSERT_EQ(s1.getBoxesOnStation()->size(),2);
        ASSERT_EQ(s2.getBoxesOnStation()->size(),1);
    }
    for(int i = 0; i<6;i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(s1.getBoxesOnStation()->size(),1);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),2);
    ASSERT_EQ(wp1.getPosition(),20);
    ASSERT_EQ(wp2.getPosition(),8);
    ASSERT_EQ(wp3.getPosition(),75);
}

TEST(ConveyorbeltStation,RunTOWPOverStationAndBumpIntoEachother) {
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    s1.setConveyorbeltState(ACTUATOR_ON);
    s2.setConveyorbeltState(ACTUATOR_OFF);
    BaseWorkpiece wp1 = BaseWorkpiece(90);
    BaseWorkpiece wp2 = BaseWorkpiece(70);
    BaseWorkpiece wp3 = BaseWorkpiece(40);
    s1.insertBox(&wp1);
    s1.insertBox(&wp2);
    s1.insertBox(&wp3);
    ASSERT_EQ(s1.getBoxesOnStation()->size(),3);
    for(int i = 0;i<5;i++){
        s1.runSimulationStep();

    }
    ASSERT_EQ(s1.getBoxesOnStation()->size(),2);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),1);
    ASSERT_EQ(wp1.getPosition(),0);
    ASSERT_EQ(wp2.getPosition(),80);
    ASSERT_EQ(wp3.getPosition(),50);

    for(int i = 0;i<5;i++){
        s2.runSimulationStep();
        s1.runSimulationStep();

    }

    ASSERT_EQ(s1.getBoxesOnStation()->size(),2);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),1);
    ASSERT_EQ(wp1.getPosition(),0);
    ASSERT_EQ(wp2.getPosition(),88);
    ASSERT_EQ(wp3.getPosition(),60);
    for(int i = 0;i<30;i++){
        s2.runSimulationStep();
        s1.runSimulationStep();

    }
    ASSERT_EQ(s1.getBoxesOnStation()->size(),2);
    ASSERT_EQ(s2.getBoxesOnStation()->size(),1);
    ASSERT_EQ(wp1.getPosition(),0);
    ASSERT_EQ(wp2.getPosition(),88);
    ASSERT_EQ(wp3.getPosition(),76);

    s2.setConveyorbeltState(ACTUATOR_ON);

    for(int i = 0;i<5;i++){
        s1.runSimulationStep();

    }
    ASSERT_EQ(wp1.getPosition(),10);
    ASSERT_EQ(wp2.getPosition(),98);
    ASSERT_EQ(wp3.getPosition(),86);
    for(int i = 0;i<5;i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),20);
    ASSERT_EQ(wp2.getPosition(),8);
    ASSERT_EQ(wp3.getPosition(),96);
}

TEST(ConveyorbeltStation,moveTwoBoxes){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(0);
    ASSERT_TRUE(s1.insertBox(&wp1));
    ASSERT_TRUE(s1.insertBox(&wp2));
    for(int i = 0; i<10; i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),40);
    ASSERT_EQ(wp2.getPosition(),0);
    s1.setConveyorbeltState(ACTUATOR_ON);
    for(int i = 0; i<10; i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),60);
    ASSERT_EQ(wp2.getPosition(),20);
    s1.setConveyorbeltState(ACTUATOR_OFF);
    for(int i = 0; i<10; i++){
        s1.runSimulationStep();
    }
    ASSERT_EQ(wp1.getPosition(),60);
    ASSERT_EQ(wp2.getPosition(),20);
}