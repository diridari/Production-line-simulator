//
// Created by basti on 19.12.2020.
//
#include <gtest/gtest.h>
#include <src/gui/GuiPlacing.h>

TEST(GUIPlacing,emptyGui){
    GuiPlacing p;
    EXPECT_EQ(p.getGridSize().x, 0);
    EXPECT_EQ(p.getGridSize().y , 0);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y , 0);

}
TEST(GUIPlacing,1StationUpDown){
    GuiPlacing p;
    BaseProductionStation b;
    b.setDirection(directionUp,directionDown);
    GridPosition g = p.addStation(&b);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,0);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, 0);
    EXPECT_EQ(p.getGridSize().x, 1);
    EXPECT_EQ(p.getGridSize().y , 2);
}
TEST(GUIPlacing,1DownUp){
    GuiPlacing p;
    BaseProductionStation b;
    b.setDirection(directionDown,directionUp);
    GridPosition g = p.addStation(&b);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -2);
    EXPECT_EQ(p.getGridSize().x, 1);
    EXPECT_EQ(p.getGridSize().y , 2);
}
TEST(GUIPlacing,1LR){
    GuiPlacing p;
    BaseProductionStation b;
    b.setDirection(directionLeft,directionRight);
    GridPosition g = p.addStation(&b);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,0);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, 0);
    EXPECT_EQ(p.getGridSize().x, 2);
    EXPECT_EQ(p.getGridSize().y , 1);
}
TEST(GUIPlacing,1RL){
    GuiPlacing p;
    BaseProductionStation b;
    b.setDirection(directionRight,directionLeft);
    GridPosition g = p.addStation(&b);
    EXPECT_EQ(g.x,-2);
    EXPECT_EQ(g.y,0);
    EXPECT_EQ(p.getCurrentOffset().x, -2);
    EXPECT_EQ(p.getCurrentOffset().y, 0);
    EXPECT_EQ(p.getGridSize().x, 2);
    EXPECT_EQ(p.getGridSize().y , 1);
}

TEST(GUIPlacing,2uL){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionLeft);
    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,-1);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, -1);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    EXPECT_EQ(p.getGridSize().x, 2);
    EXPECT_EQ(p.getGridSize().y , 3);
}
TEST(GUIPlacing,2uR){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionRight);
    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    EXPECT_EQ(p.getGridSize().x, 2);
    EXPECT_EQ(p.getGridSize().y , 3);
}

TEST(GUIPlacing,3uRR){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    BaseProductionStation b3;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionRight);
    b3.setDirection(directionLeft,directionRight);
    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b3);
    EXPECT_EQ(g.x,2);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    EXPECT_EQ(p.getGridSize().x, 4);
    EXPECT_EQ(p.getGridSize().y , 3);
}

TEST(GUIPlacing,4uRRD){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    BaseProductionStation b3;
    BaseProductionStation b4;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionRight);
    b3.setDirection(directionLeft,directionRight);
    b4.setDirection(directionRight,directionDown);

    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b3);
    EXPECT_EQ(g.x,2);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    g = p.addStation(&b4);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getGridSize().x, 5);
    EXPECT_EQ(p.getGridSize().y , 3);
}
TEST(GUIPlacing,5uRRDD){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    BaseProductionStation b3;
    BaseProductionStation b4;
    BaseProductionStation b5;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionRight);
    b3.setDirection(directionLeft,directionRight);
    b4.setDirection(directionRight,directionDown);
    b5.setDirection(directionUp,directionDown);

    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b3);
    EXPECT_EQ(g.x,2);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    g = p.addStation(&b4);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b5);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-1);
    EXPECT_EQ(p.getGridSize().x, 5);
    EXPECT_EQ(p.getGridSize().y , 4);
}
TEST(GUIPlacing,5uRRDL){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    BaseProductionStation b3;
    BaseProductionStation b4;
    BaseProductionStation b5;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionRight);
    b3.setDirection(directionLeft,directionRight);
    b4.setDirection(directionLeft,directionDown);
    b5.setDirection(directionUp,directionLeft);

    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b3);
    EXPECT_EQ(g.x,2);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    g = p.addStation(&b4);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b5);
    EXPECT_EQ(g.x,3);
    EXPECT_EQ(g.y,-1);
    EXPECT_EQ(p.getGridSize().x, 5);
    EXPECT_EQ(p.getGridSize().y , 3);
}
TEST(GUIPlacing,uRRDDD){
    GuiPlacing p;
    BaseProductionStation b1;
    BaseProductionStation b2;
    BaseProductionStation b3;
    BaseProductionStation b4;
    BaseProductionStation b5;
    b1.setDirection(directionDown,directionUp);
    b2.setDirection(directionDown,directionRight);
    b3.setDirection(directionLeft,directionRight);
    b4.setDirection(directionRight,directionDown);
    b5.setDirection(directionUp,directionDown);

    GridPosition g = p.addStation(&b1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);
    g = p.addStation(&b2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b3);
    EXPECT_EQ(g.x,2);
    EXPECT_EQ(g.y,-3);
    EXPECT_EQ(p.getCurrentOffset().x, 0);
    EXPECT_EQ(p.getCurrentOffset().y, -3);
    g = p.addStation(&b4);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-3);
    g = p.addStation(&b4);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-1);
    g = p.addStation(&b5);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,1);
    EXPECT_EQ(p.getGridSize().x, 5);
    EXPECT_EQ(p.getGridSize().y , 6);
}

TEST(GuiPlacing, example){
    BaseProductionStation *c6 = new BaseProductionStation(nullptr,"End");
    BaseProductionStation *c5 = new BaseProductionStation(c6,"Pusher2");
    BaseProductionStation *c4 = new BaseProductionStation(c5,"Drill");
    BaseProductionStation *c3 = new BaseProductionStation(c4,"Mill");
    BaseProductionStation *c2 = new BaseProductionStation(c3,"Pusher1");
    BaseProductionStation *c1 = new BaseProductionStation(c2,"Start");
    c1->setDirection(directionDown, directionUp);
    c2->setDirection(directionDown, directionRight);
    c3->setDirection(directionLeft, directionRight);
    c4->setDirection(directionLeft, directionRight);
    c5->setDirection(directionLeft, directionDown);
    c6->setDirection(directionUp, directionDown);
    GuiPlacing p;
    GridPosition g = p.addStation(c1);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-2);

    g = p.addStation(c2);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,-3);

    g = p.addStation(c3);
    EXPECT_EQ(g.x,2);
    EXPECT_EQ(g.y,-3);

    g = p.addStation(c4);
    EXPECT_EQ(g.x,4);
    EXPECT_EQ(g.y,-3);

    g = p.addStation(c5);
    EXPECT_EQ(g.x,6);
    EXPECT_EQ(g.y,-3);

    g = p.addStation(c6);
    EXPECT_EQ(g.x,6);
    EXPECT_EQ(g.y,-1);

}