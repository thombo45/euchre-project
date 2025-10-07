//
//  Player.cpp
//  eucherproject
//
//  Created by Thomas Boyle on 10/6/25.
//

#include <cassert>
#include "Player.hpp"
#include "Pack.hpp"//not sure if I should have added


using namespace std;
/*
 class Duck : public Bird {
 void talk() const override{
 cout << "quack" << endl
 }
 };
 
 */

class SimplePlayer : public Player{
 private:
    string name;
    vector<Card> hand;
public:
    const std::string & get_name() {
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c){
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
        
    };
    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const{ //could be wrong
        assert(round == 2 || round == 1);
        if(round == 1){
            int Num_of_High_Cards = 0;
            for(int i = 0; i < 4; i++){
                if( hand[i].get_rank() > 8){
                    if(hand[i].get_suit() == upcard.get_suit()){
                        Num_of_High_Cards += Num_of_High_Cards;
                    }
                }
            }
            if(Num_of_High_Cards >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }
            else{ return false;}
        }
        if(round == 2){
            for(int i = 0; i < 4; i++){
                if( hand[i].get_rank() > 8){
                    if(hand[i].get_suit() == upcard.get_suit() || hand[i].get_suit() == Suit_next(upcard.get_suit())){
                        order_up_suit = hand[i].get_suit();
                        return true;
                    }
                }
            }
            
            if(is_dealer == true){ //screw the dealer
                order_up_suit = upcard.get_suit();
                return true;
            }
            else{return false;}
            
        }
        return false;
    };
    
    
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard){
        assert(hand.size() > 0);
        hand.push_back(upcard);
        Card lowest = hand[0];
        int inx_lowest = 0;
        for(int i = 1; i < hand.size(); i++){
            if(hand[i] < lowest){
                lowest = hand[i];
                inx_lowest = i;
                
            }
            hand.erase(hand.begin() + inx_lowest);
            
        };
    };
      
    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump){
  
    
    
        };


    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump){
        
    }
    
    
    

};


Player * Player_factory(const std::string &name, const std::string &strategy) {
    
    // We need to check the value of strategy and return
      // the corresponding player type.
      if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
      }
      // Repeat for each other type of Player
      ...
      // Invalid strategy if we get here
      assert(false);
      return nullptr;
    
}


std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}
