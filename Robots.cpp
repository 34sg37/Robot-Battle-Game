#include "Robots.h"

Robot::Robot() : occupied(false){} // when called like: = new Robot(), default constructor works, default constructor is used when first
                                   // initializing the grid or when a robot is dead or moves, so when this is called, the cell is not occupied
Robot::Robot(int t, int s,int h, string n) : type(t), strength(s), hitpoints(h), name(n), occupied(true) {} // while placing the robot to the grid this constructor is called
                                                                                                            // so the cell is occupied
Robot::~Robot() {}
string Robot::getType()const{
    switch(type){
        case 0: return "optimusprime";
        case 1: return "robocop";
        case 2: return "roomba";
        case 3: return "bulldozer";
    }
    return "unknown";
}
int Robot::getStrength()const{return strength;}
int Robot::getHitpoints()const{return hitpoints;}
string Robot::getName()const{return name;}
void Robot::setStrength(int s){strength=s;}
void Robot::setHitpoints(int h){hitpoints=h;}
int Robot::getDamage()const{
    int damage= (rand() % strength)+1;
    cout<<getType()<<" attacks for "<<damage <<" points!"<<endl;
    return damage;
}
bool Robot::isOccupied()const{return occupied;} //returns true if there is a robot in the cell
bool Robot::hasMoved()const{return moved;} //returns true if the robot has moved
void Robot::markMove(bool b){moved=b;} //to set the moved variable to true after moving a robot or to set the moved variable of all alive robots to false when all robots moved

Bulldozer::Bulldozer() : Robot(3,50,200,"noname") {} //default
Bulldozer::Bulldozer(string n) : Robot(3,50,200,n) {}
string Bulldozer::getType()const {return "bulldozer";}
int Bulldozer::getDamage()const {return Robot::getDamage();} //calls robot::getdamage

Roomba::Roomba() : Robot(2,3,10,"noname") {} 
Roomba::Roomba(string n) : Robot(2,3,10,n) {}
string Roomba::getType()const {return "roomba";}
int Roomba::getDamage() const { //roomba has its own attack method
    cout<<getType()<<" attacks twice!"<<endl;
    int damage= Robot::getDamage(); //again calls robot::getdamage
    int damage2= Robot::getDamage();
    int total_damage=damage+damage2;
    cout<<getType()<<" dealt total of "<<total_damage<<" damage!"<<endl;
    return total_damage;
}

Humanic::Humanic(){} 
Humanic::Humanic(int t, int s,int h, string n) : Robot(t,s,h,n){} //calls robot class constructor
int Humanic::getDamage() const { //humanic has its own attack method
    int damage= Robot::getDamage();
    if (rand() % 10 == 0){
        damage+=50;
        cout<<getType()<<" inflicts a tactical nuke attack! +50 points! New damage point: "<<damage<<endl;
    }
    return damage;
}

OptimusPrime::OptimusPrime() : Humanic(0,100,100,"noname"){}  //calls humanic constructor which also calls robot constructor
OptimusPrime::OptimusPrime(string n) : Humanic(0,100,100,n){}
string OptimusPrime::getType()const {return "optimusprime";}
int OptimusPrime::getDamage()const { //optimusprime has its own attack method
    int damage = Humanic::getDamage(); //calls humanic::getdamage which also calls robot::getdamage
    if (rand()% 15 ==0){ 
        damage *=2;
        cout<<getType()<< " inflicts a strong attack! Double the damage! New damage point: "<<damage<<endl;
    }
    return damage;
}

Robocop::Robocop() : Humanic(1,30,40,"noname"){}
Robocop::Robocop(string n) : Humanic(1,30,40,n) {}  //calls humanic constructor which also calls robot constructor
string Robocop::getType()const {return "robocop";}
int Robocop::getDamage()const {return Humanic::getDamage();}  //calls humanic::getdamage which also calls robot::getdamage