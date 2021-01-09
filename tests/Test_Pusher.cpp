//
// Created by basti on 28.12.2020.
//

#include <gtest/gtest.h>
#include <src/workpiece/BaseWorkpiece.h>
#include "src/actuators/pusher.h"
#include "src/productionStation/PushStation.h"


TEST(pusher,runPusherUntilBox){
    pusher p("");
    BaseWorkpiece wp1 = BaseWorkpiece(41,"",10); // 36
    p.setDirection(PushDirection::Forward);
    vector <BaseWorkpiece*> *v= new vector <BaseWorkpiece*>();
    v->push_back(&wp1);
    PushStation * s = new PushStation(nullptr);
    s->insertBox(&wp1,41);



    for(int i =1; i<=18;i++ ){
        p.runActuator(v, s);
        ASSERT_EQ(p.getPosition(),i*2);
        ASSERT_EQ(wp1.getPosition(),41);
    }

}

TEST(pusher,runPusher){
    pusher p("");
    BaseWorkpiece wp1 = BaseWorkpiece(7,"",10); // 36
    p.setDirection(PushDirection::Forward);
    vector <BaseWorkpiece*> *v= new vector <BaseWorkpiece*>();
    v->push_back(&wp1);
    PushStation * s = new PushStation(nullptr);
    s->insertBox(&wp1,7);
    p.runActuator(v, s);
    ASSERT_EQ(p.getPosition(),2);
    ASSERT_EQ(wp1.getPosition(),7);
    p.runActuator(v, s);
    ASSERT_EQ(p.getPosition(),4);
    ASSERT_EQ(wp1.getPosition(),9);

    p.runActuator(v, s);
    ASSERT_EQ(p.getPosition(),6);
    ASSERT_EQ(wp1.getPosition(),11);
}

