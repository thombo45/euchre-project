#include "Player.hpp"
#include "Card.hpp"
#include <vector>
#include <algorithm>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Simple : public Player {
    public:
    Card get_card(int i) override {
        return hand[i];
    }
    Simple(const string &inName) {
        name = inName;
    }
    const string & get_name() const override {
        return name;
    }
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override {
        assert(round == 1 || round == 2);
        if (round == 1) {
            int trumpFace = 0;
            for (int i = 0, size = hand.size(); i != size; ++i) {
                if ((hand[i].is_trump(upcard.get_suit()) && hand[i].is_face_or_ace())
            || hand[i].is_left_bower(upcard.get_suit())) {
                ++trumpFace;
            }
            }
            if(trumpFace >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        else if (round == 2) {
            Suit nextSuit = Suit_next(upcard.get_suit());
            if (is_dealer) {
                order_up_suit = nextSuit;
                return true;
            }
            for (int i = 0, size = hand.size(); i != size; ++i) {
                if ((hand[i].is_trump(nextSuit) && hand[i].is_face_or_ace())
                || hand[i].is_left_bower(nextSuit)) {
                    order_up_suit = nextSuit;
                    return true;
                }
            }
        }
        return false;
    }
    void add_and_discard(const Card &upcard) override {
        assert(hand.size() >= 1);
        int handIndex = 0;
        Card low = hand[0];
        for (int i = 0, size = hand.size(); i != size; ++i) {
            if (Card_less(hand[i], low, upcard.get_suit())) {
                low = hand[i];
                handIndex = 1;
            }
        }
        hand.erase(hand.begin() + handIndex);
    }
    Card lead_card(Suit trump) override {
        Card high;
        int nonTrump = 0;
        int handIndex = 0;
        for (int i = 0, size = hand.size(); i != size; ++i) {
            if(nonTrump == 0) {
                if (!hand[i].is_trump(trump)) {
                    high = hand[i];
                    handIndex = i;
                    nonTrump = 1;
                }
            }
            if(!hand[i].is_trump(trump) && hand[i] > high) {
                high = hand[i];
                handIndex = i;
            }
        }
        if (nonTrump == 0) {
            for (int i = 0, size = hand.size(); i != size; ++i) {
                if (!Card_less(hand[i], high, trump)) {
                    high = hand[i];
                    handIndex = i;
                }
            }
        }
        hand.erase(hand.begin() + handIndex);
        return high;
    }
     Card play_card(const Card &led_card, Suit trump) override {
        Card high, low;
        int comparisonHigh = 0;
        int comparisonLow = 0; 
        int indexHigh = 0;
        int indexLow = 0;

        for (int i = 0, size = hand.size(); i != size; ++i) {
            if (comparisonLow == 0){
                if (hand[i].get_suit() != led_card.get_suit()){
                    low = hand[i];
                    comparisonLow = 1;
                    indexLow = i;
                    continue;
                }
            }
            if (comparisonHigh == 0){
                if (hand[i].get_suit() == led_card.get_suit()
                    && !hand[i].is_left_bower(trump)){
                    high = hand[i];
                    comparisonHigh = 1;
                    indexHigh = i;
                    continue;
                }
            }
            if (comparisonLow == 1) {
                if (Card_less(hand[i], low, led_card, trump)){
                    low = hand[i];
                    indexLow = i;
                }
            }
            if (comparisonHigh == 1) {
                if (hand[i] > high 
                    && hand[i].get_suit() == led_card.get_suit()) {
                    high = hand[i];
                    indexHigh = i;
                }
            }
        }
        if (comparisonHigh == 1){
            hand.erase(hand.begin() + indexHigh);
            return high;
        }
        hand.erase(hand.begin() + indexLow);
        return low;
    }
private:
    string name;
    std::vector<Card> hand;
};

class Human : public Player {
public:
    void printHand() const {
        std::vector<Card> temp = hand;
        std::sort(temp.begin(), temp.end());

        for (int i = 0, size = temp.size(); i != size; ++i) {
            std::cout << "Human player " << name << "'s hand: " << "[" << i << "] " << temp[i] << '\n';
        }
    }
    Card get_card(int i) override {
        return hand[i];
    }
    Human(const string &inName) {
        name = inName;
    }
    const string & get_name() const override {
        return name;
    }
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override {
        assert(round == 1 || round == 2);
        string decision;      
        printHand();

        cout << "Human player "<< name << ", please enter a suit, or \"pass\":" << "\n";
        cin >> decision;

        if (decision == "Spades"){
            cout << name << " orders up Spades" << "\n\n";
            order_up_suit = SPADES;
            return true;
        }
        
        else if (decision == "Hearts"){
            cout << name << " orders up Hearts" << "\n\n";
            order_up_suit = HEARTS;
            return true;
        }

        else if (decision == "Clubs"){
            cout << name << " orders up Clubs" << "\n\n";
            order_up_suit = CLUBS;
            return true;
        }

        else if (decision == "Diamonds"){
            cout << name << " orders up Diamonds" << "\n\n";
            order_up_suit = DIAMONDS;
            return true;
        }
        cout << name << " passes" << endl;
        return false;
    }
    void add_and_discard(const Card &upcard) override {
        int cardNumber;
        sort(hand.begin(), hand.end());

        for (int i = 0, size = hand.size(); i != size; ++i){
            cout << "Human player "<< name << "'s hand: " << "[" << i << "] " << hand[i] << endl;
        }
        hand.push_back(upcard);

        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name << ", please select a card to discard:" <<endl;
        cin >> cardNumber;

        if (cardNumber == -1){
            hand.pop_back();
        }
        else {
            hand.erase(hand.begin() + cardNumber);
        }
    }
    Card lead_card(Suit trump) override {
        int cardNumber;
        Card leadCard;
        sort(hand.begin(), hand.end());

        for (int i = 0, size = hand.size(); i != size; ++i){
            cout << "Human player "<< name << "'s hand: " << "[" << i << "] " << hand[i] << endl;
        }
        cout << "Human player " << name << ", please select a card:" <<endl;
        cin >> cardNumber;
        cout << hand[cardNumber] << " led by " << name << endl;
        
        leadCard = hand[cardNumber];
        hand.erase(hand.begin() + cardNumber);
        
        return leadCard;
    }   
    Card play_card(const Card &led_card, Suit trump) override {
        return lead_card(trump);
    }
private:
    string name;
    std::vector<Card> hand;
};

 

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    if (strategy == "Simple") {
        return new Simple(name);
    }
    if (strategy == "Human") {
        return new Human(name);
    }
    assert(false);
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}
