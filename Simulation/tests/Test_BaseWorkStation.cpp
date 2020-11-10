//
// Created by basti on 09.11.2020.
//

#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
#include "../src/workpiece/BaseWorkpiece.h"


TEST(BaseWorkstation,canStationReceiveBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece();
    s1.insertBox(&wp1);
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(0));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(1));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(5));
    wp1.setPosition(5);
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(11));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(10));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(9));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(8));
    wp1.setPosition(6);
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(11));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(10));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(9));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(8));
}
TEST(BaseWorkstation,canStationReceiveBoxGetFirstBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece();
    BaseWorkpiece wp2 = BaseWorkpiece(20);
    s1.insertBox(&wp1);
    s1.insertBox(&wp2);
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(0));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(1));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(5));
    wp1.setPosition(5);
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(11));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(10));
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(9));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(8));
    wp1.setPosition(6);
    ASSERT_FALSE(s1.canReceiveNewWorkpiece(11));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(10));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(9));
    ASSERT_TRUE(s1.canReceiveNewWorkpiece(8));
}

