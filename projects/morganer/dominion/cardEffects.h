#ifndef _CARD_EFFECTS_H
#define _CARD_EFFECTS_H

#include "dominion.h"

int baronCardEffect(struct gameState *state, int currentPlayer, int choice1);
int minionCardEffect(struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos);
int ambassadorCardEffect(struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos);
int tributeCardEffect(struct gameState *state, int currentPlayer, int nextPlayer);
int mineCardEffect(struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos);

#endif