//
//  cards.c
//  blackjack
//
//  Created by Dragon Tan on 16/04/2019.
//  Copyright © 2019 Dragon Tan. All rights reserved.
//

#include "cards.h"
#include <ctype.h> // to include toupper
#include <stdlib.h>

card_t card_create (char suit, char value)
{
    card_t card;
    suit = toupper (suit);
    if (suit != 'S' && suit != 'C'
               && suit != 'H' && suit != 'D')
        // if suit is not S, C, H, or D
        card.suit = 'C';
    else
        card.suit = suit;
    
    card.value = value;
    
    return card;
}

char card_get_suit (card_t card)
{
    char suit;
    suit = card.suit;
    return suit;
}

int card_get_value (card_t card)
{
    int value;
    if (card.value == 'A')
        value = 1;
    else if (card.value == 'J')
        value = 11;
    else if (card.value == 'Q')
        value = 12;
    else if (card.value == 'K')
        value = 13;
    else
        value = card.value;
    return value;
}

int card_blackjack_points (card_t card)
{
    int gamepoints = 0; // initializing gamepoint
    
    if (card.value >= 10)
        gamepoints = 10;
    else
        gamepoints = card.value;
    return gamepoints;
}

void card_print (card_t card)
{
    if (card.value == 1)
        printf ("Ace");
    else if (card.value == 11)
        printf ("Jack");
    else if (card.value == 12)
        printf ("Queen");
    else if (card.value == 13)
        printf ("King");
    else
        printf ("%d", card.value);
    
    printf (" of ");
    
    if (card.suit == 'S')
        printf ("%cpades\n", card.suit);
    else if (card.suit == 'H')
        printf ("%cearts\n", card.suit);
    else if (card.suit == 'C')
        printf ("%clubs\n", card.suit);
    else
        printf ("%ciamonds\n", card.suit);
}

shoe_t shoe_create (int num_of_decks)
{
    shoe_t deck;
    deck.total_num = num_of_decks * 52;
    char suit = '\0';
    // creating dynamic array
    deck.cards = (card_t*) calloc (deck.total_num, sizeof(card_t));
    int a = 0, b, c;
    while (a < num_of_decks){ // a is the num of decks
        for (b = 0; b < 4; b++){
            // b is the suits
            c = 1;
            while (c < 14){
                if (b == 0) // spades
                    suit = 'S';
                else if (b == 1) // hearts
                    suit = 'H';
                else if (b == 2) // clubs
                    suit = 'C';
                else if (b == 3) // diamonds
                    suit = 'D';
                
                if (c < 14) // value is A
                    deck.cards[c+b*13+a*52 - 1] = card_create(suit, c);
        
                c++;
            }
        }
        a++;
    }
    shoe_reshuffle(&deck);
    
    return (deck);
}

card_t shoe_draw_card (shoe_t *deck)
{
    int cards_left;
    card_t draw_card;
    
    cards_left = shoe_cards_left(*deck);
    if (cards_left == 0){
        shoe_reshuffle(deck);
        draw_card = deck->cards[deck->next];
    
    }
    else {
        // card being drawn is the next card from deck
        draw_card = deck->cards[deck->next];
    }
    // initializing next card
    deck->next = deck->next+1;
    return draw_card;
}

int shoe_cards_left (shoe_t deck)
{
    int card_left;
    
    // total number - number of cards taken
    card_left = deck.total_num - deck.next;
    
    return card_left;
}
void shoe_reshuffle (shoe_t *deck)
{
    
    printf ("\nSHUFFLING!\n");
    int i, random_position = 0;
    // temporary deck
    card_t temp[deck->total_num];
    int total_card = deck->total_num;
    for (i = 0; i < total_card; i++){
        // randomized position based on time
        random_position = i + rand() % (total_card-i);
        temp[i] = deck->cards[i];
        // randomizing position of the cards in deck
        deck->cards[i] = deck->cards[random_position];
        deck->cards[random_position] = temp[i];
        //printf ("%d: %d of %c\n", i+1,deck->cards[i].value, deck->cards[i].suit);
    }
    // initializing next card as the first card of deck
    deck->next = 0;
}

void shoe_free (shoe_t *deck)
{
    // freeing dynamic array 
    free(deck->cards);
}

hand_t hand_create_empty (void)
{
    hand_t hand;
    // initializing num of cards to zero
    hand.num_of_card = 0;
    
    return hand;
}

void hand_print (hand_t hand)
{
    int i = 0;
    while (i < hand.num_of_card )
    {
        // printing i's card
        card_print(hand.x[i]);
        i++;
    }
}

void hand_print_first_card (hand_t hand)
{
    int i = 0;
    printf ("The Dealer is showing ");
    card_print(hand.x[i]);
}

void hand_add_card (hand_t *hand, card_t card)
{
    hand->num_of_card++;
    // -1 to get array number
    // adding to hand
    hand->x[hand->num_of_card - 1] = card;
}

int hand_blackjack_points (hand_t hand)
{
    int total_points = 0, i;
    for (i = 0; i < hand.num_of_card; i++){
        total_points = (total_points
                        + card_blackjack_points(hand.x[i]));
        if (total_points <= 11 && hand.x[i].value == 1)
            total_points = total_points + 10;
            
    }
        
    return total_points;
}
