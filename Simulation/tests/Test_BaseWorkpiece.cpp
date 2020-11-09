//
// Created by basti on 03.11.2020.
//

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