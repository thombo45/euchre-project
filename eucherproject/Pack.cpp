#include "Card.hpp"
#include "Pack.hpp"
#include <array>
#include <string>

const int firstCard = 0;
const int LastCard = 23;
const int startArray = 7;
const int ranks = 13;
const int suits = 4;


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack() {
    next = firstCard;
    int j  = startArray;
    int k = 0;
    for (int i = 0; i != PACK_SIZE; ++i) {
      Card card(static_cast<Rank>(j), static_cast<Suit>(k));
      cards[i] = card;
      ++j;
      if (j == ranks) {
        j = startArray;
        ++k;
      }
    }
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(std::istream& pack_input) {
    next = firstCard;
    std::string rank;
    std::string suit;
    std::string of;

    for (int i = 0; i != PACK_SIZE; ++i) {
        pack_input >> rank >> of >> suit;
        Rank r = string_to_rank(rank);
        Suit s = string_to_suit(suit);
        Card card(r, s);
        cards[i] = card;
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    return cards[next++];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = firstCard;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle() {
    int shuffles = 7;
    std::array <Card, PACK_SIZE / 2> first_half, second_half;

    while (shuffles != 0) {
        for (int i = 0; i != PACK_SIZE / 2; ++i) {
            first_half[i] = cards[i];
            second_half[i] = cards[PACK_SIZE / 2 + i];
        }
        for (int i = 0, j = 0; i != PACK_SIZE; i += 2, ++j) {
            cards[i] = second_half[j];
            cards[i + 1] = first_half[j];
        }
        --shuffles;
    }
    next = 0;
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const {
    if (next == LastCard + 1) {
        return true;
    }
    return false;
  }