#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogo{
    int suit, value;
} Card;

enum suit{
    Spades, Diamonds, Heart, Clubs
};

enum val{
    Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};

typedef enum hand{
    HighCard, Pair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush
}PokerHand;

int checkHand(Card* card){
    int i=0, j=0;
    Card aux;

    //ORDENAR AS CARTAS
    for (i = 0; i < 5; i++){
        for (j = i+1; j < 5; j++){
            if(card[j].value > card[i].value){
                aux = card[i];
                card[i] = card[j];
                card[j] = aux;
            }
        }
    }

    //CASO OS NAIPES SEJAM IGUAIS
    if(card[0].suit==card[1].suit && card[1].suit==card[2].suit && card[2].suit==card[3].suit && card[3].suit==card[4].suit){
        //ROYAL FLUSH
        if(card[4].value == Ace && card[0].value == King && card[1].value == Queen && card[2].value == Jack && card[3].value == Ten){
            return RoyalFlush;
        }
        //STRAIGHT FLUSH
        else if(card[0].value == (card[1].value+1) && card[1].value == (card[2].value+1) && card[2].value == (card[3].value+ 1) && card[3].value == (card[4].value+1)){
            return StraightFlush;
        }
        //FLUSH
        else if(card[0].value != card[1].value+1 && card[1].value != card[2].value+1 && card[2].value != card[3].value+1 && card[3].value != card[4].value+1){
            return Flush;
        }
    }
    //FOUR OF A KIND
    else if((card[0].value==card[1].value && card[1].value==card[2].value && card[2].value==card[3].value) || 
    (card[1].value==card[2].value && card[2].value==card[3].value && card[3].value==card[4].value)){
        return FourOfAKind;
    }
    //FULL HOUSE
    else if((card[0].value==card[1].value && card[1].value==card[2].value && card[3].value==card[4].value) || 
    (card[2].value==card[3].value && card[3].value==card[4].value && card[0].value==card[1].value)){
        return FullHouse;
    }
    //STRAIGHT
    else if(card[0].value == card[1].value+1 && card[1].value == card[2].value+1 && card[2].value == card[3].value+1 && card[3].value == card[4].value+1){
        return Straight;
    }
    //THREE OF A KIND
    else if((card[0].value==card[1].value && card[1].value==card[2].value && card[3].value!=card[4].value )|| (card[1].value==card[2].value && card[2].value==card[3].value) || 
    (card[2].value==card[3].value && card[3].value==card[4].value&& card[0].value!=card[1].value)){
        return ThreeOfAKind;
    }
    //TWO PAIR
    else if((card[0].value==card[1].value && card[2].value==card[3].value) || (card[1].value==card[2].value && card[3].value==card[4].value)||
    (card[0].value==card[1].value && card[3].value==card[4].value)){
        return TwoPair;
    }
    else if((card[0].value==card[1].value)||(card[1].value==card[2].value)|| (card[2].value==card[3].value)||(card[3].value==card[4].value)){
        return Pair;
    }
    else{
        return HighCard;
    }
}

int main() {
    int i;
    Card hands[][5] = {
        {  // Royal Flush
            { Diamonds, Ace },
            { Diamonds, King },
            { Diamonds, Queen }, 
            { Diamonds, Jack }, 
            { Diamonds, Ten } 
        },
        { // Full house
          { Heart, Jack },   
          { Spades, Jack },   
          { Clubs, Jack },     
          { Spades, Two  },    
          { Heart, Two } 
        },   
        { // Three of a Kind
          { Diamonds, Ten }, 
          { Spades, Seven },  
          { Diamonds, Four },  
          { Spades, Four  },   
          { Heart, Four } 
        },  
        { // Pair
          { Spades, Ace  },  
          { Heart, Jack },    
          { Spades, Jack },    
          { Heart, Seven },    
          { Clubs, Four } 
        },  
        { // High Card (No pair)
          { Clubs, Nine },   
          { Heart, Seven },   
          { Diamonds, Six },   
          { Spades, Four  },   
          { Heart, Two } 
        },   
    };
    Card myCards[5];
    Card oponentCards[5];
    
    unsigned handIndex;
    scanf("%u", &handIndex);
    for( i = 0; i < 5; i++) {
        myCards[i] = hands[handIndex][i];
        scanf("%u %u", &oponentCards[i].suit, &oponentCards[i].value);
    }
    PokerHand myHand = checkHand(myCards);
    PokerHand oponentHand = checkHand(oponentCards);
    if (myHand > oponentHand) {
        switch(myHand) {
            case RoyalFlush:
                printf("É... simplesmente não tinha como me bater!\n");
                break;
            case StraightFlush:
            case FourOfAKind:
            case FullHouse:
                printf("Já era! Você não tinha chance!\n");
                break;
            case Flush:
            case Straight:
            case ThreeOfAKind:
                printf("É boy! Quem sabe da próxima vez...\n");
                break;
            default:
                printf("Tive sorte!\n");
        }
    }
    else if (oponentHand > myHand) {
        printf("Não valeu! Cê tá roubando!!!\n");
    }
    else if (myCards[0].value > oponentCards[0].value) {
        printf("Ufa! Por pouco!");
    }
    else {
        printf("Nan!! Bicho melado da gota!\n");
    }
    return 0;
}