//
//  euchre.cpp
//  eucherproject
//
//  Created by Thomas Boyle on 10/17/25.
//

#include "euchre.hpp"
#include "Player.hpp"
#include "Pack.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>


using namespace std;

class Game {
public:
    Game(int argc, char* argv[]){
        int Errors = 0;
        if(argc != 12){
            Errors += Errors;
        }
        
        string Will_shuffle = argv[2];
        if(Will_shuffle == "shuffle"){
            pack.shuffle();
        }
        else if (Will_shuffle == "noshuffle"){
            
        }
        else{
            Errors += Errors;
        }
        points_to_win = atoi(argv[3]);
        if(points_to_win < 1 || points_to_win > 100){
            Errors += Errors;
        }
        
        players.push_back(Player_factory(argv[4], argv[5]));
        players.push_back(Player_factory(argv[6], argv[7]));
        players.push_back(Player_factory(argv[8], argv[9]));
        players.push_back(Player_factory(argv[10], argv[11]));
        
        if(Errors < 0){
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
                 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
                 << "NAME4 TYPE4" << endl;
            was_error = true;
            return;
        }
            
        string ex_name = argv[0];
        string pack_name = argv[1];
        ifstream infile(pack_name);
        if (!infile.is_open()) {
            cout << "Error opening  " << pack_name << endl;
            was_error = true;
            return;
        }
        Pack pack(infile);

        
        
    };
    bool get_was_error(){
        return was_error;
                       };
    void play();
    
private:
    vector <Player*> players;
    Pack pack;
    int points_to_win;
    bool was_error;
    
    
    void shuffle();
    void deal();
    void make_trump();
    void play_hand();
    
};



int main(int argc, char* argv[]) {
    Game game(argc, argv);
    if(game.get_was_error() == true){ //may be a better way of doing this
        return 1;
    }
}
