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
        if(Will_shuffle != "shuffle" && Will_shuffle != "noshuffle"){
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
    }
    void play();
    
private:
    vector <Player*> players;
    int idx_dealer;
    int team_1_pts; //player 0 and 2
    int team_2_pts; //player 1 and 3
    Pack pack;
    Suit trump;
    Card upcard;
    int points_to_win;
    bool will_shuffle;
    bool was_error;
    
    void inc_dealer(){
        ++idx_dealer;
        if(idx_dealer < 3){
            idx_dealer = 0;
        }
    }
    void inc_player(int idx){
        ++idx;
        if(idx < 3){
            idx = 0;
        }
    }
    
    void shuffle(){
        if (will_shuffle == true){
            pack.shuffle();
        }
    };
    void deal(){
        cout << players[idx_dealer] -> get_name() << " deals" << endl;
        for(int i = 0; i < 5; i++){
            players[0] -> add_card(pack.deal_one());
            players[1] -> add_card(pack.deal_one());
            players[2] -> add_card(pack.deal_one());
            players[3] -> add_card(pack.deal_one());
        }
        upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
      
    };
    void make_trump(){
        int round = 1;
        int idx_P;
        if(idx_dealer == 3){
            idx_P = 0;
        }
        else {idx_P = idx_dealer + 1;}
        
        for(int i = 0; i < 4; i++){
            if(idx_P == idx_dealer){
                if(players[idx_P] -> make_trump(upcard, true, 1, trump) == true){
                    players[idx_dealer] -> add_and_discard(upcard);
                    cout << players[idx_P] -> get_name() << " orders up " << trump << endl;
                    inc_dealer();
                    return;
                }
                else{
                    cout << players[idx_P] -> get_name() << " passes" << endl;
                }
            }
            else{
                if(players[idx_P] -> make_trump(upcard, false, 1, trump) == true){
                    players[idx_dealer] -> add_and_discard(upcard);
                    cout << players[idx_P] -> get_name() << " orders up " << trump << endl;
                    inc_dealer();
                    return;
                }
                else{
                    cout << players[idx_P] -> get_name() << " passes" << endl;
                }
            }
            inc_player(idx_P);
        }
        round = 2;
       
        for(int i = 0; i < 4; i++){
            if(idx_P == idx_dealer){
                if(players[idx_P] -> make_trump(upcard, true, 2, trump) == true){
                    inc_dealer();
                    return;
                }
            }
            else{
                if(players[idx_P] -> make_trump(upcard, false, 2, trump) == true){
                    inc_dealer();
                    return;
                }
                else{
                    cout << players[idx_P] -> get_name() << " passes" << endl;
                }
            }
            inc_player(idx_P);
        }
        
    };
    void play_hand(){
        int idx_P;
        Card Max;
        int Current_winner;
        if(idx_dealer == 3){
            idx_P = 0;
        }
        else {idx_P = idx_dealer + 1;}
        //first trick player to left of dealer leads
        Card lead_card;
        lead_card = players[idx_P] -> lead_card(trump);
        Max = lead_card;
        Current_winner = idx_P;
        cout << lead_card << " led by " << players[idx_P] -> get_name() << endl;
        inc_player(idx_P);
        for(int i = 0; i < 3; i++){
            players[idx_P] -> play_card(lead_card, trump);
            
            inc_player(idx_P);
        }
        
        
    };
    
};



int main(int argc, char* argv[]) {
    Game game(argc, argv);
    if(game.get_was_error() == true){ //may be a better way of doing this
        return 1;
    }
}
