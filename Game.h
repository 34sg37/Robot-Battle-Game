#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Robots.h"
using namespace std;

class Game{
    public:
        Game();
        void placeGrid();
        void printGrid();
        bool searchEnemy(const Robot* attacker);
        bool fight(Robot* attacker, Robot* defender);
        void play();
        ~Game();
    private:
        vector<vector<Robot*>> grid;
        int robotsAlive,movedRobotAmount;
        int defender_x, defender_y, attacker_x, attacker_y;
};

#endif