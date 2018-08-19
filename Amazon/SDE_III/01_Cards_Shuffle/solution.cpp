/*
 * Implement cards class that suport:
 * 1. Shuffle the cards
 * 2. GiveOneCard
 *
 * May. 14. 2017 Update:
 * 1. Add "Laizi" rule, that has "bai da".
 * 2. Add "No shuffle" rule
 * */
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

typedef unsigned char CardID;
typedef enum {
    Hearts = 0,
    Diamonds,
    Clubs, 
    Spades,
    CARD_TOTAL_TYPES
} CardType;

const CardID END_OF_CARDS = 0xff; // A, 2, 3, ... 10, J, Q, K
class Cards{
private:
    const unsigned char mNumTypesOneCard = CARD_TOTAL_TYPES; // 4 types for each card, Hearts, Diamonds, Clubs and Spades
    const unsigned char mNumUniqCards = 13;   // A, 2, 3, ... 10, J, Q, K
    const unsigned char CARD_TYPE_MASK = 0x30; // 2 bits
    const unsigned char CARD_NUM_MASK = 0x0f;  // 4 bits
    unsigned long mNumTotalCards;            
    vector<vector<int>> mCards;
    int mNumSuits;
    int mNumCardsOut;

private:
    void initCards() {
        mNumCardsOut = 0;
        mNumTotalCards = mNumUniqCards * mNumTypesOneCard * mNumSuits;
        srand(time(nullptr));
        vector<int> tmp; 
        for (unsigned char ctype = 0; ctype < mNumTypesOneCard; ctype++) {
            tmp.push_back(mNumSuits);
        }
        for (CardID cardId = 0; cardId < mNumUniqCards; cardId++) {
            mCards.push_back(tmp);
        }
    }

    CardID getCardID(unsigned char cn, CardType ct) {
        return ((unsigned char)ct << 4) | cn;
    }

public:
    Cards(int numSuits = 1) : mNumSuits (numSuits) {
        initCards();
    }
    ~Cards() {
        mCards.clear();
    }
    void shuffle() {
        mCards.clear();
        initCards();
    }

    inline unsigned char getCardNum(CardID cardId) {
        return cardId & CARD_NUM_MASK;
    }
    inline CardType getCardType(CardID cardId) {
        return static_cast<CardType>((cardId & CARD_TYPE_MASK) >> 4);
    }

    CardID getOneCard() {
        if (mNumCardsOut == mNumTotalCards)
            return END_OF_CARDS;

        unsigned char cn; 
        CardType ct; 
    
        do {
            cn = rand() % mNumUniqCards;
            ct = static_cast<CardType> (rand() % mNumTypesOneCard);
        } while (!mCards[cn][ct]);

        mCards[cn][ct]--;
        mNumCardsOut++;
        assert(mNumCardsOut <= mNumTotalCards);
        return getCardID(cn, ct);
    }
};

int main() {
    Cards c(1);
    c.shuffle();
    CardID cid;
    unsigned char cn;
    CardType ct;
    int totalCards = 0;
    while ((cid = c.getOneCard()) != END_OF_CARDS) { 
        totalCards++;
        cn = c.getCardNum(cid);
        ct = c.getCardType(cid);
        cout << "No: "<< (int)cn << ", Type: " << ct << endl;
    } 
    
    cout << "TotalCards: " << totalCards << endl;
    return 1;
}
