//
// Created by basti on 19.12.2020.
//
#include <gtest/gtest.h>
#include <src/gui/GuiPlacing.h>

TEST(GUIPlacing,emptyGui){
    GuiPlacing p;
    EXPECT_EQ(p.getGridSize().x, 0);
    EXPECT_EQ(p.getGridSize().y , 0);
    EXPECT_EQ(p.getCurrentOfset().x, 0);
    EXPECT_EQ(p.getCurrentOfset().y , 0);

}
TEST(GUIPlacing,1StationUpDown){
    GuiPlacing p;
    BaseProductionStation b;
    b.setDirection(directionUp,directionDown);
    GridPosition g = p.addStation(&b);
    EXPECT_EQ(g.x,0);
    EXPECT_EQ(g.y,0);
    EXPECT_EQ(p.getCurrentOfset().x,0);
    EXPECT_EQ(p.getCurrentOfset().y,0);
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
    EXPECT_EQ(p.getCurrentOfset().x,0);
    EXPECT_EQ(p.getCurrentOfset().y,-2);
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
    EXPECT_EQ(p.getCurrentOfset().x,0);
    EXPECT_EQ(p.getCurrentOfset().y,0);
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
    EXPECT_EQ(p.getCurrentOfset().x,-2);
    EXPECT_EQ(p.getCurrentOfset().y,0);
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
    EXPECT_EQ(p.getCurrentOfset().x,-1);
    EXPECT_EQ(p.getCurrentOfset().y,-3);
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
    EXPECT_EQ(p.getCurrentOfset().x,0);
    EXPECT_EQ(p.getCurrentOfset().y,-3);
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
    EXPECT_EQ(p.getCurrentOfset().x,0);
    EXPECT_EQ(p.getCurrentOfset().y,-3);
    EXPECT_EQ(p.getGridSize().x, 4);
    EXPECT_EQ(p.getGridSize().y , 3);
}

