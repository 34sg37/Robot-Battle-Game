#ifndef ROBOTS_H
#define ROBOTS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

const int GRID_SIZE = 10;
const int ROBOT_AMOUNT_EACH =5;
using namespace std;

class Robot {
    public:
        Robot();
        Robot(int t, int s,int h, string n);
        virtual ~Robot();
        virtual string getType()const;
        int getStrength()const;
        int getHitpoints()const;
        string getName()const;
        void setStrength(int s);
        void setHitpoints(int h);
        virtual int getDamage()const;
        bool isOccupied()const;
        bool hasMoved()const;
        void markMove(bool b);
    private:
        int type,strength,hitpoints;
        string name;
        bool occupied,moved = false;
};
class Bulldozer : public Robot{
    public:
        Bulldozer();
        Bulldozer(string n);
        string getType()const override;
        int getDamage()const override;
};
class Roomba : public Robot{
    public:
        Roomba();
        Roomba(string n);
        string getType()const override;
        int getDamage() const override;
};
class Humanic : public Robot{
    public:
        Humanic();
        Humanic(int t, int s,int h, string n);
        int getDamage() const override;
};
class OptimusPrime : public Humanic{
    public:
        OptimusPrime();
        OptimusPrime(string n);
        string getType()const override;
        int getDamage()const override;
};
class Robocop : public Humanic{
    public:
        Robocop();
        Robocop(string n);
        string getType()const override;
        int getDamage()const override;
};

#endif