//
// Created by basti on 03.11.2020.
//

#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
#include "../src/workpiece/BaseWorkpiece.h"


TEST(BaseWorkPiece,CreateObj){
    BaseWorkpiece b1(0);
    BaseWorkpiece b2;
    BaseWorkpiece b3(10,"test");
    BaseWorkpiece b4("test");
    ASSERT_EQ(b1.getPosition(),0);
    ASSERT_EQ(b2.getPosition(),0);
    ASSERT_EQ(b3.getPosition(),10);
    ASSERT_EQ(b4.getPosition(),0);
}

TEST(BaseWorkPiece,moveObj) {
    BaseWorkpiece b1(0);
    ASSERT_TRUE(b1.moveBy(10));
    ASSERT_EQ(b1.getPosition(),10);
    ASSERT_TRUE(b1.moveBy(-5));
    ASSERT_EQ(b1.getPosition(),5);
    ASSERT_TRUE(b1.moveBy(-5));
    ASSERT_EQ(b1.getPosition(),0);
    ASSERT_FALSE(b1.moveBy(-1));
    ASSERT_EQ(b1.getPosition(),0);
}
TEST(BaseWorkPiece,moveByMax) {
    BaseWorkpiece b1(WORKPIECE_MAX_INCREASE*2);
    ASSERT_TRUE(b1.moveBy(WORKPIECE_MAX_INCREASE));
    ASSERT_FALSE(b1.moveBy(WORKPIECE_MAX_INCREASE+1));
    ASSERT_TRUE(b1.moveBy(-WORKPIECE_MAX_INCREASE));
    ASSERT_FALSE(b1.moveBy(-WORKPIECE_MAX_INCREASE-1));

}
TEST(BaseWorkPiece,maxPos) {
    BaseWorkpiece b1(MAXPOSITION-1);
    ASSERT_TRUE(b1.moveBy(1));
    ASSERT_FALSE(b1.moveBy(1));

}
TEST(BaseWorkPiece, canBoxBePlacedOnEmptyStationWithNoNext){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(0,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(10,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(90,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(95,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(100,&s1));
}

TEST(BaseWorkPiece, canBoxBePlacedOnEmptyStationWithNext){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(0,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(10,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(90,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(95,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(100,&s1));
}

TEST(BaseWorkPiece, canBoxBePlacedOnEmptyStationWithNextBlockedAt5){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(5);
    s2.insertBox(&wp2);
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(0,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(10,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(90,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(95,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(100,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(-5,&s2));
}
TEST(BaseWorkPiece, canBoxBePlacedOnEmptyStationWithNextBlockedAt10){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s2.insertBox(&wp2);
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(0,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(10,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(90,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(95,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(99,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(-1,&s2));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(101,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(0,&s2));

}

TEST(BaseWorkPiece, canBoxBePlacedOnitSelf){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(10);
    BaseWorkpiece wp2 = BaseWorkpiece(50);
    s1.insertBox(&wp1);
    s1.insertBox(&wp2);
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(0,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(5,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(6,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(10,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(15,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(16,&s1));


}

TEST(BaseWorkPiece, canBoxBePlacedOnStationWithOneOtherBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(10);
    BaseWorkpiece wp2 = BaseWorkpiece(50);
    s1.insertBox(&wp1);
    s1.insertBox(&wp2);
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(39,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(45,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(50,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(54,&s1));
    ASSERT_FALSE(wp1.canWorkpieceBePlacedAt(60,&s1));
    ASSERT_TRUE(wp1.canWorkpieceBePlacedAt(61,&s1));
}