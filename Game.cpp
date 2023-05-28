#include "Game.h"

Game::Game() : robotsAlive(ROBOT_AMOUNT_EACH*4){
    placeGrid();
    play();
}
void Game::placeGrid() {
    vector<vector<Robot*>> newGrid(GRID_SIZE,vector<Robot*>(GRID_SIZE)); //grid
    for(int i=0; i< GRID_SIZE;i++){
        for(int j=0; j<GRID_SIZE; j++){
            newGrid[i][j]=new Robot(); //for each cell Robot() constructor is called
        }
    }
    for (int i = 0; i < ROBOT_AMOUNT_EACH; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        //if the randomly selected index is occupied then try again
        while (newGrid[x][y]->isOccupied()) {x = rand() % GRID_SIZE; y = rand() % GRID_SIZE;} 
        //replace the Robot() object in the cell with OptimusPrime object which is named like optimusprime_0, optimusprime_1... etc.
        newGrid[x][y] = new OptimusPrime("optimusprime_"+to_string(i));

        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
        while (newGrid[x][y]->isOccupied()) {x = rand() % GRID_SIZE; y = rand() % GRID_SIZE;}
        newGrid[x][y] = new Robocop("robocop_"+to_string(i)); //same thing with robocop

        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
        while (newGrid[x][y]->isOccupied()) {x = rand() % GRID_SIZE; y = rand() % GRID_SIZE;}
        newGrid[x][y] = new Roomba("roomba_"+to_string(i)); //same thing with roomba

        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
        while (newGrid[x][y]->isOccupied()) {x = rand() % GRID_SIZE; y = rand() % GRID_SIZE;}
        newGrid[x][y] = new Bulldozer("bulldozer_"+to_string(i)); //same thing with bulldozer
    }
    grid=newGrid;
}
void Game::printGrid(){ //print grid function if needed, (currently not being used)
    vector<vector<char>> pg(GRID_SIZE,vector<char>(GRID_SIZE));
    for(int i=0; i<GRID_SIZE; i++){
        for(int j=0; j<GRID_SIZE; j++){
            if(!grid[i][j]->isOccupied()) pg[i][j]='.';
            else if(grid[i][j]->getType()=="optimusprime") pg[i][j]='0';
            else if(grid[i][j]->getType()=="robocop") pg[i][j]='1';
            else if(grid[i][j]->getType()=="roomba") pg[i][j]='2';
            else if(grid[i][j]->getType()=="bulldozer") pg[i][j]='3';
        }
    }
    for(int i=0; i<GRID_SIZE; i++){
        for(int j=0; j<GRID_SIZE; j++){
            cout<<pg[i][j]<<" ";
        }
        cout<<endl;
    }
}
//search enemy, return true if found, false if no enemy remains
bool Game::searchEnemy(const Robot* attacker){
    if (robotsAlive<=1) return false;
    else{
        bool found=false;
        while(!found){
            int dir= rand() %4; //direction
            switch(dir){
                case 0: //up
                    if(attacker_y==0) break; //if y index is 0, cant go up
                    //if a grid is occupied by a different robot than the attacker keep the indexes of defender
                    else if(grid[attacker_y-1][attacker_x]->isOccupied() && attacker->getName()!=grid[attacker_y-1][attacker_x]->getName()){
                        defender_x=attacker_x; 
                        defender_y=attacker_y-1;
                        found=true;
                    }
                    else attacker_y=attacker_y-1; //if not occupied then move to the possition 
                    break;
                case 1: //down
                    if(attacker_y==GRID_SIZE-1) break; //if y index is GRID_SIZE-1, cant go down
                    else if(grid[attacker_y+1][attacker_x]->isOccupied() && attacker->getName()!=grid[attacker_y+1][attacker_x]->getName()){
                        defender_x=attacker_x;
                        defender_y=attacker_y+1;
                        found=true;
                    }
                    else attacker_y=attacker_y+1;
                    break;
                case 2: //left
                    if(attacker_x==0) break;
                    else if(grid[attacker_y][attacker_x-1]->isOccupied() && attacker->getName()!=grid[attacker_y][attacker_x-1]->getName()){
                        defender_x=attacker_x-1;
                        defender_y=attacker_y;
                        found=true;
                    }
                    else attacker_x=attacker_x-1;
                    break;
                case 3: //right
                    if(attacker_x==GRID_SIZE-1) break;
                    else if(grid[attacker_y][attacker_x+1]->isOccupied() && attacker->getName()!=grid[attacker_y][attacker_x+1]->getName()){
                        defender_x=attacker_x+1;
                        defender_y=attacker_y;
                        found=true;
                    }
                    else attacker_x=attacker_x+1;
                    break;
            }
        }
    }
    return true;
}
bool Game::fight(Robot* attacker, Robot* defender){ //return true: if attacker won, return false: if defender won
    int att_hp=attacker->getHitpoints();
    int def_hp=defender->getHitpoints();
    while(att_hp>0 && def_hp>0){
        int att_damage= attacker->getDamage(); //attacker's hit damage
        cout<<attacker->getName()<<"("<<attacker->getHitpoints()<<")"<<" hits "<<defender->getName()<<"("<<defender->getHitpoints()<<") with "<<att_damage<<endl;
        def_hp-=att_damage; 
        defender->setHitpoints(def_hp); //update defender hp
        cout<<"The new hitpoints of "<<defender->getName()<<" is "<<defender->getHitpoints()<<endl<<endl;
        if (def_hp<=0){ //if defender is dead
            cout<<defender->getName()<<" is dead."<<endl<<endl;
            return true;
        }

        int def_damage= defender->getDamage(); //defender's hit damage
        cout<<defender->getName()<<"("<<defender->getHitpoints()<<")"<<" hits "<<attacker->getName()<<"("<<attacker->getHitpoints()<<") with "<<def_damage<<endl;
        att_hp-=def_damage;
        attacker->setHitpoints(att_hp); //update attacker hp
        cout<<"The new hitpoints of "<<attacker->getName()<<" is "<<attacker->getHitpoints()<<endl<<endl;
        if(att_hp<=0){ //if attacker is dead
            cout<<attacker->getName()<<" is dead."<<endl<<endl;
            return false;
        }
    }
    return true;
}
void Game::play(){ //play game
    Robot* winner = new Robot(); //winner
    while(robotsAlive>1){
        //search grid
        for(int i=0; i<GRID_SIZE; i++){
            for(int j=0; j<GRID_SIZE; j++){
                if(grid[i][j]->isOccupied() && !grid[i][j]->hasMoved()){ //if a cell is occupied and the robot inside hasnt moved yet
                    //keep it's coordinates
                    attacker_x=j; 
                    attacker_y=i;
                    if(searchEnemy(grid[i][j])){ //search for enemy, dont do anything if not found
                        //fight the found enemy
                        if(fight(grid[i][j], grid[defender_y][defender_x])){ //if attacker won
                            grid[i][j]->markMove(true); //set moved variable to true
                            movedRobotAmount++; //counter to hold moved robot amount
                            grid[defender_y][defender_x]=grid[i][j]; //attacker places into defender's cell
                            grid[i][j] = new Robot(); //attacker's old cell is replaced with new Robot(), which is default constructor thats sets occupied variable to false
                            //attacker's new coordiantes are defender's old coordinates
                            attacker_x=defender_x; 
                            attacker_y=defender_y;
                        }
                        else grid[i][j] = new Robot(); //if attacker lost, replace its cell with new Robot()
                        
                        robotsAlive--; //a robot is dead
                        /*printGrid();
                        cout<<endl;*/
                    }
                }
                else{ 
                    if(movedRobotAmount>=robotsAlive){ //when moved robot amount is bigger than robots alive, this means all alive robots have moved
                        for(int i=0; i<GRID_SIZE; i++)
                            for(int j=0; j<GRID_SIZE; j++)
                                if(grid[i][j]->isOccupied()) grid[i][j]->markMove(false); //set all moved variables to false 

                        movedRobotAmount=0;
                    }
                }
                if(robotsAlive<=1){ //if only 1 robot is left
                    for(int i=0; i<GRID_SIZE; i++)
                        for(int j=0; j<GRID_SIZE; j++)
                            if(grid[i][j]->isOccupied()) winner = grid[i][j]; //find that robot and it is the winner
                }
            }
        }
    }
    cout<<"Game over, the winner is: "<<winner->getName()<<"!"<<endl;
}
Game::~Game() { //destructor
    for (auto& row : grid) {
        for (auto& robot : row) {
            delete robot;
            robot=nullptr;
        }
    }
}