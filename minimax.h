

#include <climits>
#include "Node.h"

#ifndef __MINIMAX_H__
#define __MINIMAX_H__

int minimax(Node<int> *tree);
int max_value(Node<int> *tree, int alpha, int beta);
int min_value(Node<int> *tree, int alpha, int beta);
#endif // __MINIMAX_H__
