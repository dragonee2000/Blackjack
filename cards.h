//
//  cards.h
//  blackjack
//
//  Created by Dragon Tan on 16/04/2019.
//  Copyright © 2019 Dragon Tan. All rights reserved.
//

#ifndef cards_h
#define cards_h
#define MAX 52
#define MAX_CARD 21
#include <stdio.h>

typedef struct{
    char suit;
    int value;
} card_t;

card_t card_create (char suit, char value);
char card_get_suit (card_t card);
int card_get_value (card_t card);
int card_blackjack_points (card_t card);
void card_print (card_t card);

typedef struct{
    card_t *cards;
    int total_num;
    int next;
} shoe_t;

shoe_t shoe_create (int num_of_decks);
card_t shoe_draw_card (shoe_t *deck);
int shoe_cards_left (shoe_t deck);
void shoe_reshuffle (shoe_t *deck);
void shoe_free (shoe_t *deck);

typedef struct{
    card_t x[MAX_CARD];
    int num_of_card;
} hand_t;

hand_t hand_create_empty (void);
void hand_print (hand_t hand);
void hand_print_first_card (hand_t hand);
void hand_add_card (hand_t *hand, card_t card);
int hand_blackjack_points (hand_t hand);

#endif /* cards_h */
