//
//  main.c
//  blackjack
//
//  Created by Dragon Tan on 16/04/2019.
//  Copyright © 2019 Dragon Tan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include <ctype.h>
#include <time.h>

int main(int argc, const char * argv[]){
    int num_of_decks, cards_left;
    shoe_t shoe; // the deck
    card_t draw_card;   // card drew
    hand_t dealer, player; // player's & dealer's hand
    int stake = 1000,    // starting amount
    bet, win;   // win amount (bet x 2)
    int p_score, d_score; // player points and dealer points
    char response;  // to hit or stand
    int count = 2; // number of cards after first two draws
    srand (time(0)); // random time to shuffle the cards
    
    printf ("Welcome to Blackjack!\n\n");
    printf ("How many decks do you wish to play with (1-10)? ");
    scanf ("%d", &num_of_decks);
    
    if (num_of_decks < 1)   // num of decks to be more than 0
    {
        printf ("Try again\n");
        printf ("How many decks do you wish to play with (1-10)? ");
        scanf ("%d", &num_of_decks);
    }
    
    shoe = shoe_create(num_of_decks);   // the shoe
    
    do
    {
        // initialize both hands to zero
        player = hand_create_empty();
        dealer = hand_create_empty();
        // intializing scores
        p_score = 0;
        d_score = 0;
        printf ("Your stake: $%d\n", stake);
        // cards left in shoe
        cards_left = shoe_cards_left(shoe);
        printf ("Cards left in the shoe: %d\n\n", cards_left);
        printf ("Enter your bet (negative to quit): ");
        scanf ("%d", &bet);
        win = bet * 2;
        if (bet < 0){
            shoe_free(&shoe);
            break; // negative to quit
        }
        // drawing card
        draw_card = shoe_draw_card(&shoe);
        // adding drawed card to hand
        hand_add_card(&dealer, draw_card);
        // print first card
        hand_print_first_card(dealer);
        
        printf ("\nYour cards:\n");
        // to get a starting of two cards
        while (player.num_of_card < 2){
            // drawing card
            draw_card = shoe_draw_card(&shoe);
            // adding drawed card to hand
            hand_add_card(&player, draw_card);
            // player score
            p_score = hand_blackjack_points(player);
        }
        hand_print(player); // printing players hand
        printf ("Score = %d\n",p_score);
        printf ("Do you want to (H)it or (S)tand? "); // to hit or stand
        scanf (" %c", &response);
        while (response == 'h')
        {
            // drawing card
            draw_card = shoe_draw_card(&shoe);
            // adding drawed card to hand
            hand_add_card(&player, draw_card);
            // player score
            p_score = hand_blackjack_points(player);
            hand_print(player); // printing players hand
            printf ("Score = %d\n",p_score);
            if (p_score <= 21){ // score less than 21 continue
                do
                { // to hit or stand
                    printf ("Do you want to (H)it or (S)tand? ");
                    scanf (" %c", &response);
                    
                    response = tolower(response);
                    
                    if ((response != 'h') && (response != 's'))
                        printf ("Please enter a h or s\n");
                    
                } while ((response != 'h') && (response != 's'));
            } else {
                printf ("You Busted. You Lose!\n");
                stake = stake - bet; // new stake
                break; // lost: restart; break from loop
            }
            count++;
        }
        
        // is player score is less than 21 and stands
        if (p_score <= 21 && response == 's'){
            printf ("Dealer cards:\n");
            while (d_score < 17) // loops if points less than 17
            {
                // drawing card
                draw_card = shoe_draw_card(&shoe);
                // adding drawed card to hand
                hand_add_card(&dealer, draw_card);
                // dealer's score
                d_score = hand_blackjack_points(dealer);
            }
            hand_print(dealer);  // printing dealer's hand
            if (d_score > 21) // dealer busts
                {
                    printf ("Dealer Busts. You Win $%d!\n", win);
                    stake = stake + bet; // stake increases by bet amount
                }else if (p_score > d_score){ // player wins
                    printf ("You win with a score of %d!", p_score);
                    printf ("   You win $%d\n", win);
                    stake = stake + bet;
                } else if (p_score < d_score){ // dealer wins
                    printf ("Dealer wins with a score of %d. You Lose!\n", d_score);
                    stake = stake - bet;    // stake decreases by bet amount
                } else
                    printf ("It's a tie. You get back $%d.", bet);
                    // stake does not decrease, so no movement
        }
        if (stake == 0){
            shoe_free(&shoe);
        }
    } while (stake != 0 && bet > 0);
    if (stake == 0){ // when stake is 0
        printf ("You've lost your entire stake!\n");
    }
    else // quitting the game
        printf ("You ended the night with $%d\n", stake);
    
     
    return 0;
}
