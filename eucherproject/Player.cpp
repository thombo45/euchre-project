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
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const override {
        assert(round == 1 || round == 2);
        if (round == 1) {
            int trumpFace = 0;
            for (int i = 0, size = hand.size(); i != size; ++i) {
                if ((hand[i].is_trump(upcard.get_suit())
                     && hand[i].is_face_or_ace())
            || hand[i].is_left_bower(upcard.get_suit())) {
                ++trumpFace;
            }
            }
            if(trumpFace >= 2) {
                order_up_suit = upcard.get_suit();
                cout << name << " orders up " << order_up_suit << "\n\n";
                return true;
            }
            else {
                cout << name << " passes" << endl;
                return false;
            }
        }
        else if (round == 2) {
            Suit nextSuit = Suit_next(upcard.get_suit());
            if (is_dealer) {
                order_up_suit = nextSuit;
                cout << name << " orders up " << order_up_suit << "\n\n";
                return true;
            }
            for (int i = 0, size = hand.size(); i != size; ++i) {
                if ((hand[i].is_trump(nextSuit) && hand[i].is_face_or_ace())
                || hand[i].is_left_bower(nextSuit)) {
                    order_up_suit = nextSuit;
                    cout << name << " orders up " << order_up_suit << "\n\n";
                    return true;
                }
            }
        }
        cout << name << " passes" << endl;
        return false;
    }
    void add_and_discard(const Card &upcard) override {
        assert(hand.size() >= 1);
        int handIndex = 0;
        Card low = hand[0];
        hand.push_back(upcard);
        for (int i = 0, size = hand.size(); i != size; ++i) {
            if (Card_less(hand[i], low, upcard.get_suit())) {
                low = hand[i];
                handIndex = i;
            }
        }
        hand.erase(hand.begin() + handIndex);
    }
    Card lead_card(Suit trump) override {
        
        Card high;
        int nonTrump = 0;
        int handIndex = 0;
        for (int i = 0, size = hand.size(); i != size; ++i) {
            //cycle through cards
            if(nonTrump == 0) {
                //if we have yet to find a trump card
                if (!hand[i].is_trump(trump)) {
                    //if the current card is not trump
                    high = hand[i];
                    handIndex = i;
                    nonTrump = 1;
                }
            }
            if(!hand[i].is_trump(trump)
               && hand[i] > high) {
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
        Suit suit_of_led_card = determine_led_suit(led_card, trump);

        // Step 1: Try to play a right bower
        int right_index = find_right_bower(trump);
        if (right_index != -1 && suit_of_led_card == trump) {
            Card right_bower = hand[right_index];
            hand.erase(hand.begin() + right_index);
            return right_bower;
        }

        // Step 2: Try to play a left bower
        int left_index = find_left_bower(trump);
        if (left_index != -1 && suit_of_led_card == trump) {
            Card left_bower = hand[left_index];
            hand.erase(hand.begin() + left_index);
            return left_bower;
        }

        // Step 3: Normal follow/discard logic
        int chosen_index = choose_card_index(led_card, trump, suit_of_led_card);
        Card chosen = hand[chosen_index];
        hand.erase(hand.begin() + chosen_index);
        return chosen;
    }

    Suit determine_led_suit(const Card &led_card, Suit trump) {
        if (led_card.is_left_bower(trump)) {
            return trump;
        }
        return led_card.get_suit();
    }

    int find_right_bower(Suit trump) {
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].is_right_bower(trump)) {
                return i;
            }
        }
        return -1;
    }

    int find_left_bower(Suit trump) {
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].is_left_bower(trump)) {
                return i;
            }
        }
        return -1;
    }

    int choose_card_index(const Card &led_card, Suit trump, Suit suit_of_led_card) {
        Card high, low;
        int comparisonHigh = 0;
        int comparisonLow = 0; 
        int indexHigh = 0;
        int indexLow = 0;

        for (int i = 0, size = hand.size(); i != size; ++i) {
            // Pick first off-suit card as potential low
            if (comparisonLow == 0) {
                if (hand[i].get_suit() != suit_of_led_card) {
                    low = hand[i];
                    comparisonLow = 1;
                    indexLow = i;
                    continue;
                }
            }

            // Pick first matching-suit card as potential high
            if (comparisonHigh == 0) {
                if (suit_of_led_card == trump && hand[i].is_left_bower(trump)) {
                    comparisonHigh = 1;
                    high = hand[i];
                    indexHigh = i;
                } else if (hand[i].get_suit() == suit_of_led_card &&
                        !hand[i].is_left_bower(trump)) {
                    high = hand[i];
                    comparisonHigh = 1;
                    indexHigh = i;
                    continue;
                }
            }

            // Update lowest off-suit card
            if (comparisonLow == 1) {
                if (Card_less(hand[i], low, led_card, trump)) {
                    low = hand[i];
                    indexLow = i;
                }
            }

            // Update highest matching suit card
            if (comparisonHigh == 1) {
                if (led_card.get_suit() == trump && hand[i].is_left_bower(trump)) {
                    high = hand[i];
                    indexHigh = i;
                } else if (hand[i] > high && hand[i].get_suit() == suit_of_led_card) {
                    if (!hand[i].is_left_bower(trump)) {
                        high = hand[i];
                        indexHigh = i;
                    }
                }
            }
        }

        if (comparisonHigh == 1) {
            return indexHigh;
        }
        return indexLow;
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
            std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << temp[i] << '\n';
        }
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

        cout << "Human player "<< name
        << ", please enter a suit, or \"pass\":" << "\n";
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
            cout << "Human player "<< name << "'s hand: "
            << "[" << i << "] " << hand[i] << endl;
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
            cout << "Human player "<< name << "'s hand: "
            << "[" << i << "] " << hand[i] << endl;
        }
        cout << "Human player " << name << ", please select a card:" <<endl;
        cin >> cardNumber;
        
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
   // assert(false);
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}

