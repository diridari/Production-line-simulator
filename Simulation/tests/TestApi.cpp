//
// Created by basti on 12.12.2020.
//
#include <gtest/gtest.h>
#include <src/api/api.h>
#include <src/productionStation/conveyorbeltStation.h>
#include <src/productionStation/PushStation.h>
#include <src/productionStation/MillAndDrillStation.h>

TEST(API,getStationByName){
    conveyorbeltStation *c6 = new conveyorbeltStation(nullptr,"End");
    PushStation *c5 = new PushStation(c6,"Push 2");
    MillAndDrillStation *c4 = new MillAndDrillStation(c5,"Drill");
    MillAndDrillStation *c3 = new MillAndDrillStation(c4,"Mill");
    PushStation *c2 = new PushStation(c3,"Push1");
    conveyorbeltStation *c1 = new conveyorbeltStation(c2,"Start");
    api api1(c1);
    ASSERT_EQ(api1.getStationByName("Push 2"),c5);
    ASSERT_EQ(api1.getStationByName("Start"),c1);
    ASSERT_EQ(api1.getStationByName("End"), c6);
    ASSERT_EQ(api1.getStationByName("Push X2"), nullptr);
}
TEST(API,getToken){
    conveyorbeltStation *c6 = new conveyorbeltStation(nullptr,"End");
    PushStation *c5 = new PushStation(c6,"Push 2");
    MillAndDrillStation *c4 = new MillAndDrillStation(c5,"Drill");
    MillAndDrillStation *c3 = new MillAndDrillStation(c4,"Mill");
    PushStation *c2 = new PushStation(c3,"Push1");
    conveyorbeltStation *c1 = new conveyorbeltStation(c2,"Start");
    api api1(c1);
    string s = "abc def xx   554";
    string token = api1.getNextToken(&s);
    ASSERT_EQ(token,"abc");
    ASSERT_EQ(s,"def xx   554");

    token = api1.getNextToken(&s);
    ASSERT_EQ(token,"def");
    ASSERT_EQ(s,"xx   554");

    token = api1.getNextToken(&s);
    ASSERT_EQ(token,"xx");
    ASSERT_EQ(s,"  554");

    token = api1.getNextToken(&s);
    ASSERT_EQ(token,"554");
    ASSERT_EQ(s,"");

    token = api1.getNextToken(&s);
    ASSERT_EQ(token,"");
    ASSERT_EQ(s,"");

}