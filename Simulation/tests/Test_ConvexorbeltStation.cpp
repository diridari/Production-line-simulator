//
// Created by basti on 09.11.2020.
//

#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
#include "../src/workpiece/BaseWorkpiece.h"


TEST(ConvexorbeltStation,moveOneBox){
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

TEST(ConvexorbeltStation,moveTwoBoxes){
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