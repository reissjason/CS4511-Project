
#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include <iostream>
#include <limits.h>
#include "debug_print.h"
#include "minimax.h"
#include "Node.h"
#include "Move.h"


using namespace std;
//
Node<Move>* minimax(Node<Move> *tree);
Node<Move>* max_value(Node<Move> *tree, Node<Move> *alpha, Node<Move> *beta);
Node<Move>* min_value(Node<Move> *tree, Node<Move>* alpha, Node<Move>* beta);
Node<Move>* minimum(Node<Move>* val1, Node<Move>* val2);
Node<Move>* maximum(Node<Move>* val1, Node<Move>* val2);


Node<Move>* minimax(Node<Move> *tree) {

	Node<Move> *v = max_value(tree, new Node<Move>(new Move(INT_MIN)), new Node<Move>(new Move(INT_MAX)));
	return v;
}

Node<Move>* max_value(Node<Move> *tree, Node<Move> *alpha, Node<Move> *beta) {
  if (!tree->hasChildren()) return tree;

  Node<Move> *temp = tree->getChildren();
  Node<Move> *v = new Node<Move>(new Move(INT_MIN));
  while (temp != NULL) {
    v = maximum(v, min_value(temp, alpha, beta));
    if (v->getValue()->getValue() <= alpha->getValue()->getValue()) return v;
    beta = minimum(beta, v);
    temp = temp->getNext();
  }
  return v;
}

Node<Move>* min_value(Node<Move> *tree, Node<Move>* alpha, Node<Move>* beta) {
	if (!tree->hasChildren()) return tree;

	Node<Move> *temp = tree->getChildren();
	Node<Move>* v = new Node<Move>(new Move(INT_MAX));
	while (temp != NULL) {
		v = minimum(v, max_value(temp, alpha, beta));
		if (v->getValue()->getValue() <= alpha->getValue()->getValue()) return v;
		beta = maximum(beta, v);
		temp = temp->getNext();
	}
	return v;
}

Node<Move>* minimum(Node<Move>* val1, Node<Move>* val2) {
	Node<Move>* min = NULL;
  if (val1->getValue()->getValue() < val2->getValue()->getValue())
    min = val1;
  else
    min = val2;

    return min;
}


Node<Move>* maximum(Node<Move>* val1, Node<Move>* val2) {
	Node<Move>* max = NULL;
  if (val1->getValue()->getValue() > val2->getValue()->getValue())
    max = val1;
  else
    max = val2;

    return max;
}

#endif
