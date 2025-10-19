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
        for(int i = 0; i < 12; i++){
            cout << argv[i] << " ";
        }
        cout << endl;
        
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
            cout << "Error opening " << pack_name << endl;
            was_error = true;
            return;
        }
        Pack pack(infile);

        
        
    };
    bool get_was_error(){
        return was_error;
    }
    int get_team_1_pts(){
        return team_1_pts;
    }
    int get_team_2_pts(){
        return team_2_pts;
    }
    
    void play(){
        for (int i = 0;
             get_team_1_pts() < points_to_win && get_team_2_pts() < points_to_win;
             i++){
            cout << "Hand " << i << endl << endl;
            shuffle(); //will only do if needed
            cout << endl << idx_dealer << " = idx dealer" << endl;
            deal();
            make_trump();
            play_hand();
        }
        if(team_1_pts > team_2_pts){
            cout << players[2] -> get_name() << " and " << players[0] -> get_name()
            << " win!";
        }
        if(team_2_pts > team_1_pts){
            cout << players[3] -> get_name() << " and " << players[1] -> get_name()
            << " win!";
        }
    };
    
private:
    vector <Player*> players;
    int idx_dealer = 0;
    int team_1_pts = 0; //player 0 and 2
    int team_2_pts = 0; //player 1 and 3
    int who_made_trump;
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
    void inc_player(int &idx){
        idx = idx + 1;
        if(idx > 3){
            idx = 0;
        }
    }
    
    void shuffle(){
        if (will_shuffle == true){
            pack.shuffle();
        }
    };
    void deal(){
        
        
        for(int i = 0; i < 5; i++){
            players[0] -> add_card(pack.deal_one());
            players[1] -> add_card(pack.deal_one());
            players[2] -> add_card(pack.deal_one());
            players[3] -> add_card(pack.deal_one());
        }
        cout << players[idx_dealer] -> get_name() << " deals" << endl;
        upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
    };
    void make_trump(){
        int idx_P;
        if(idx_dealer == 3){
            idx_P = 0;
        }
        else {idx_P = idx_dealer + 1;}
        
        for(int i = 0; i < 4; i++){
            if(idx_P == idx_dealer){
                if(players[idx_P] -> make_trump(upcard, true, 1, trump) == true){
                    players[idx_dealer] -> add_and_discard(upcard);
                    who_made_trump = idx_P;
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
                    who_made_trump = idx_P;
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
        
       
        for(int i = 0; i < 4; i++){
            if(idx_P == idx_dealer){
                if(players[idx_P] -> make_trump(upcard, true, 2, trump) == true){
                    inc_dealer();
                    who_made_trump = idx_P;
                    return;
                }
            }
            else{
                if(players[idx_P] -> make_trump(upcard, false, 2, trump) == true){
                    inc_dealer();
                    who_made_trump = idx_P;
                    return;
                }
                else{
                    cout << players[idx_P] -> get_name() << " passes" << endl;
                }
            }
            inc_player(idx_P);
        }
        cout << endl;
    };
    void play_hand(){
        int idx_P;
        Card Max;
        int Current_winner;
        int hands_won_by_team_1 = 0;
        int hands_won_by_team_2 = 0;
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
        //next 3 players play
        for(int i = 0; i < 2; i++){
            Card played;
            played = players[idx_P] -> play_card(lead_card, trump);
            cout << played << " played by " << players[idx_P] -> get_name() << endl;
            if(Card_less(Max, played, lead_card, trump)){
                Max = played;
                Current_winner = idx_P;
            }
            inc_player(idx_P);
        }
        
        //keep track of who won first trick
        if(Current_winner == 0 || Current_winner == 2){
            hands_won_by_team_1++;
        }
        if(Current_winner == 1 || Current_winner == 3){
            hands_won_by_team_2++;
        }
        
        //next 4 tricks leader of previous hand leads
        for(int i = 0; i < 3; i++){
            //last winner leads
            lead_card = players[Current_winner] -> lead_card(trump);
            Max = lead_card;
            idx_P = Current_winner;
            cout << lead_card << " led by " << players[idx_P] -> get_name() << endl;
            inc_player(idx_P);
            //next three players play
            for(int ix = 0; ix < 2; ix++){
                Card played;
                played = players[idx_P] -> play_card(lead_card, trump);
                cout << played << " played by " << players[idx_P] -> get_name() << endl;
                if(Card_less(Max, played, lead_card, trump)){
                    Max = played;
                    Current_winner = idx_P;
                }
                inc_player(idx_P);
            }
            if(Current_winner == 0 || Current_winner == 2){
                hands_won_by_team_1++;
            }
            if(Current_winner == 1 || Current_winner == 3){
                hands_won_by_team_2++;
            }
        }
        
        //award points for the hand
        bool team_1_made_trump;
        if(who_made_trump == 0 || who_made_trump == 2){
            team_1_made_trump = true;
        }
        else{team_1_made_trump = false;}
        
        
        if(hands_won_by_team_1 > hands_won_by_team_2){
            cout << players[2] -> get_name() << " and "
            << players[0] -> get_name() << " win the hand" << endl;
        }
        if(hands_won_by_team_2 > hands_won_by_team_1){
            cout << players[3] -> get_name() << " and "
            << players[1] -> get_name() << " win the hand" << endl;
        }
        
        if(hands_won_by_team_1 == 5 && team_1_made_trump == true){
            cout << "march!" << endl;
            team_1_pts = team_1_pts + 2;
        }
        else if (hands_won_by_team_2 == 5 && team_1_made_trump == false){
            cout << "march!" << endl;
            team_2_pts = team_2_pts + 2;
        }
        else if (hands_won_by_team_1 > 2 && team_1_made_trump == false){
            cout << "euchred!" << endl;
            team_1_pts = team_1_pts + 2;
        }
        else if (hands_won_by_team_2 > 2 && team_1_made_trump == true){
            cout << "euchred!" << endl;
            team_2_pts = team_2_pts + 2;
        }
        else if (hands_won_by_team_1 > hands_won_by_team_2){
            team_1_pts++;
        }
        else{
            team_2_pts++;
        }
        
        inc_dealer();
        
        cout << players[2] -> get_name() << " and "
        << players[0] -> get_name() << " have " << team_1_pts << " points" << endl;
        cout << players[3] -> get_name() << " and "
        << players[1] -> get_name() << " have " << team_2_pts << " points" << endl << endl;
    };
    
};



int main(int argc, char* argv[]) {
    Game game(argc, argv);
    if(game.get_was_error() == true){ //may be a better way of doing this
        return 1;
    }
    game.play();
    
}
