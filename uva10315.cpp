// Author: João Xavier
// Date: 25-10-2011

/*  @JUDGE_ID   '00000' 10315	C++	"Poker Hands"   */

/*  @BEGIN_OF_SOURCE_CODE   */

#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

enum HandType { HC, PA, TP, TK, ST, FL, FH, FK, SF };
map<char, int> c_to_i;

struct Hand {
    vector<string> cards;
    map<char, int> values;
    map<char, int> suits;
    
    int highest;
    HandType result;
    
    Hand(): highest(0) {
        cards = vector<string>(5);
    }
};

inline void init() {
    for (int i = 2; i <= 9; i++)
        c_to_i['0' + i] = i;
        
    c_to_i['T'] = 10;
    c_to_i['J'] = 11;
    c_to_i['Q'] = 12;
    c_to_i['K'] = 13;
    c_to_i['A'] = 14;
}

bool cmp(string const& s1, string const& s2) {
    return (c_to_i[s1[0]] <= c_to_i[s2[0]]);
}

void score(Hand& hand) {
    sort(hand.cards.begin(), hand.cards.end(), cmp);
    
    // straight flush
    if (hand.suits.size() == 1) {
        bool sequential = true;
        hand.highest = c_to_i[hand.cards[4][0]]; // last
        
        for (int i = 0; i < 4; i++)
            if ((c_to_i[hand.cards[i+1][0]] - c_to_i[hand.cards[i][0]]) != 1) {
                sequential = false;
                break;
            }
        
        hand.result = (sequential ? SF : FL);
        
        if (sequential)
            return;
    }
    
    // 4 of a kind or full house
    if (hand.values.size() == 2) {
        char keys[2];
        
        map<char, int>::iterator it = hand.values.begin();
        
        keys[0] = it->first;
        it++;
        keys[1] = it->first;
     
        switch (hand.values[keys[0]]) {
            case 1:
                hand.highest = c_to_i[keys[1]];
                hand.result = FK;
                return;
            
            case 2:
                hand.highest = c_to_i[keys[1]];
                hand.result = FH;
                return;
            
            case 3:
                hand.highest = c_to_i[keys[0]];
                hand.result = FH;
                return;
            
            case 4:
                hand.highest = c_to_i[keys[0]];
                hand.result = FK;
                return;
        }
    }
    
    // flush
    if (hand.result == FL)
        return;
        
    // straight
    bool sequential = true;
    for (int i = 0; i < 4; i++)
        if ((c_to_i[hand.cards[i+1][0]] - c_to_i[hand.cards[i][0]]) != 1) {
            sequential = false;
            break;
        }
    
    if (sequential) {
        hand.highest = c_to_i[hand.cards[4][0]];
        hand.result = ST;
        return;
    }
    
    // 3 of a kind or two pairs
    if (hand.values.size() == 3) {
        for (map<char, int>::iterator it = hand.values.begin(); it != hand.values.end(); it++) {
            if (it->second == 3) {
                hand.highest = c_to_i[it->first];
                hand.result = TK;
                return;
            }
            
            if ((it->second == 2) && (c_to_i[it->first] > hand.highest))
                hand.highest = c_to_i[it->first];
        }
        
        hand.result = TP;
        return;
    }
    
    // pair
    if (hand.values.size() == 4) {
        for (map<char, int>::iterator it = hand.values.begin(); it != hand.values.end(); it++)
            if (it->second == 2) {
                hand.highest = c_to_i[it->first];
                break;
            }
            
        hand.result = PA;
        return;
    }
    
    // high card
    hand.highest = c_to_i[hand.cards[4][0]];
    hand.result = HC;
}

int main() {
    string card;
    int cardCounter;
    Hand white, black;
    
    init();
    
    while (!cin.eof()) {
        cardCounter = 0;
        white = Hand();
        black = Hand();
   
        for (; cardCounter < 5; cardCounter++) {
            cin >> card;
            black.cards[cardCounter] = card;
            black.values[card[0]]++;
            black.suits[card[1]]++;
        }
        
        score(black);
        
        for (; cardCounter < 10; cardCounter++) {
            cin >> card;
            white.cards[cardCounter-5] = card;
            white.values[card[0]]++;
            white.suits[card[1]]++;
        }
        
        score(white);
        
        if (white.result > black.result)
            printf("White wins.\n");
        else if (black.result > white.result)
            printf("Black wins.\n");
        else {
            if ((white.result == HC) || (white.result == FL)) {    
                for (int i = 4; i >= 0; i--)
                    if (white.highest == black.highest) {
                        white.highest = c_to_i[white.cards[i][0]];
                        black.highest = c_to_i[black.cards[i][0]];
                    } else
                        break;
            }
            else if ((white.result == PA) && (white.highest == black.highest)) {
                int blackhighest[3];
                int whitehighest[3];
                int countb = 0, countw = 0;
                
                for (int i = 4; i >= 0; i--) {
                    if (c_to_i[black.cards[i][0]] != black.highest)
                        blackhighest[countb++] = c_to_i[black.cards[i][0]];
                        
                    if (c_to_i[white.cards[i][0]] != white.highest)
                        whitehighest[countw++] = c_to_i[white.cards[i][0]];
                }
                
                for (int i = 0; i != 3; i++) {
                    black.highest = blackhighest[i];
                    white.highest = whitehighest[i];
                    
                    if (black.highest != white.highest)
                        break;
                }
            }
            else if ((white.result == TP) && (white.highest == black.highest)) {
                int othercard[2];
                int secondhighest[2];
                
                for (map<char, int>::iterator it = black.values.begin(); it != black.values.end(); it++) {
                    if ((it->second == 2) && (c_to_i[it->first] != black.highest))
                        secondhighest[0] = c_to_i[it->first];
                    
                    if (it->second == 1)
                        othercard[0] = c_to_i[it->first];
                }
            
                for (map<char, int>::iterator it = white.values.begin(); it != white.values.end(); it++) {
                    if ((it->second == 2) && (c_to_i[it->first] != white.highest))
                        secondhighest[1] = c_to_i[it->first];
                    
                    if (it->second == 1)
                        othercard[1] = c_to_i[it->first];
                }
            
                black.highest = secondhighest[0];
                white.highest = secondhighest[1];
            
                if (white.highest == black.highest) {
                    black.highest = othercard[0];
                    white.highest = othercard[1];
                }
            }
            
            if (white.highest > black.highest)
                printf("White wins.\n");
            else if (black.highest > white.highest)
                printf("Black wins.\n");
            else
                printf("Tie.\n");
        }
    }
    
    return 0;
}

/*	@END_OF_SOURCE_CODE	*/
