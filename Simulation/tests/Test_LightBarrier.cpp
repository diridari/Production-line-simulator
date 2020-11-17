//
// Created by basti on 09.11.2020.
//
#include <src/sensors/lightBarrier.h>
#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
TEST(lightBarrier,emptySet){
    lightBarrier l1(5);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
    l1.checkSensor(nullptr);
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
}

TEST(lightBarrier,BoxesNotInLight){
    lightBarrier l1(4);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2);
    s1.insertBox(&wp1);

    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
    l1.checkSensor(nullptr);
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
}
TEST(lightBarrier,BoxesOnInLight1){
    lightBarrier l1(5);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2,wp2.getPosition());
    s1.insertBox(&wp1,wp1.getPosition());
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_ON);

}
TEST(lightBarrier,BoxesOnInLight2){
    lightBarrier l1(10);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(10);
    BaseWorkpiece wp2 = BaseWorkpiece(40);
    s1.insertBox(&wp2,wp2.getPosition());
    s1.insertBox(&wp1,wp1.getPosition());
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_ON);
}
TEST(lightBarrier,BoxesOnInLight3){
    lightBarrier l1(15);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2,wp2.getPosition());
    s1.insertBox(&wp1,wp1.getPosition());
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_ON);
}
TEST(lightBarrier,BoxesOnInLight4){
    lightBarrier l1(16);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2);
    s1.insertBox(&wp1);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
}
TEST(lightBarrier,BoxesOnInLight5){
    lightBarrier l1(35);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2,10);
    s1.insertBox(&wp1,40);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_ON);
}
TEST(lightBarrier,BoxesOnInLight6){
    lightBarrier l1(34);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2,40);
    s1.insertBox(&wp1,10);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
}
TEST(lightBarrier,BoxesOnInLight7){
    lightBarrier l1(45);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp2,10);
    s1.insertBox(&wp1,40);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_ON);
}
TEST(lightBarrier,BoxesOnInLight8){
    lightBarrier l1(46);
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s1.insertBox(&wp1,40);
    s1.insertBox(&wp2,10);
    l1.checkSensor(s1.getBoxesOnStation());
    ASSERT_EQ(l1.getSensorState(),SENSOR_OFF);
}