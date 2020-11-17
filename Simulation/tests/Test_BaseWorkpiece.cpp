//
// Created by basti on 03.11.2020.
//

#include <src/productionStation/conveyorbeltStation.h>
#include "gtest/gtest.h"
#include "../src/workpiece/BaseWorkpiece.h"
#include <src/workpiece/Placing.h>


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
TEST(BoxPlacing, canBoxBePlacedOnEmptyStationWithNoNext){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 0));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 10));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 90));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 95));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 100));
}

TEST(BoxPlacing, canBoxBePlacedOnEmptyStationWithNext){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 0));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 10));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 90));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 95));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 100));
}

TEST(BoxPlacing, canBoxBePlacedOnEmptyStationWithNextBlockedAt5){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(5);
    s2.insertBox(&wp2,5);
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 0));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 10));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 90));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 95));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 100));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s2, &wp1, -5));
}
TEST(BoxPlacing, canBoxBePlacedOnEmptyStationWithNextBlockedAt10){
    conveyorbeltStation s2(nullptr);
    conveyorbeltStation s1(&s2);
    BaseWorkpiece wp1 = BaseWorkpiece(40);
    BaseWorkpiece wp2 = BaseWorkpiece(10);
    s2.insertBox(&wp2,10);
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 0));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 10));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 90));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 95));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 99));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s2, &wp1, -1));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 101));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s2, &wp1, 0));

}

TEST(BaseWorkPiece, canBoxBePlacedOnitSelf){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(10);
    BaseWorkpiece wp2 = BaseWorkpiece(50);
    s1.insertBox(&wp1,10);
    s1.insertBox(&wp2,50);
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 0));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 5));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 6));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 10));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 15));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 16));


}

TEST(BoxPlacing, canBoxBePlacedOnStationWithOneOtherBox){
    conveyorbeltStation s1(nullptr);
    BaseWorkpiece wp1 = BaseWorkpiece(10);
    BaseWorkpiece wp2 = BaseWorkpiece(50);
    s1.insertBox(&wp1,10);
    s1.insertBox(&wp2,50);
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 39));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 45));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 50));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 54));
    ASSERT_FALSE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 60));
    ASSERT_TRUE(Placing::canWorkpieceBePlacedAt(&s1, &wp1, 61));
}