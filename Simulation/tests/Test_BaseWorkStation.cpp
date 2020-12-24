//
// Created by basti on 09.11.2020.
//

#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
#include "../src/workpiece/BaseWorkpiece.h"
#include <src/workpiece/Placing.h>


TEST(BaseWorkstation,canStationReceiveBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece("b1");
    s1.insertBox(&wp1);
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 0));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 1));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 5));
    wp1.setPosition(5);
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 11));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 10));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 9));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 8));
    wp1.setPosition(6);
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 11));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 10));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 9));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 8));
}
TEST(BaseWorkstation,canStationReceiveBoxGetFirstBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece("b1");
    BaseWorkpiece wp2 = BaseWorkpiece(20);
    s1.insertBox(&wp1);
    s1.insertBox(&wp2);
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 0));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 1));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 5));
    wp1.setPosition(5);
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 11));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 10));
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 9));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 8));
    wp1.setPosition(6);
    ASSERT_FALSE(Placing::canStationReceiveNewWorkpiece(&s1, 11));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 10));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 9));
    ASSERT_TRUE(Placing::canStationReceiveNewWorkpiece(&s1, 8));
}

