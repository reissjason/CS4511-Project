
#include <climits>

#include "Turn.h"
#include "Node.h"

#ifndef __TURN_MINIMAX_H__
#define __TURN_MINIMAX_H__

int turn_minimax(Node<Turn> *tree);
int max_value(Node<Turn> *tree, int alpha, int beta);
int min_value(Node<Turn> *tree, int alpha, int beta);

#endif // __TURN_MINIMAX_H__
