
#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include <iostream>
#include <limits.h>
#include "debug_print.h"
#include "minimax.h"


using namespace std;

template <class S>
S* minimax(S *tree) {

  S *v = max_value(tree, new S(new int(INT_MIN)), new S(new int(INT_MAX)));
  return v;
}

template <class S>
S* max_value(S *tree, S *alpha, S *beta) {
  if (!tree->hasChildren()) return tree;

  S *temp = tree->getChildren();
  S *v = new S(new int(INT_MIN));
  while (temp != NULL) {
    v = maximum(v, min_value(temp, alpha, beta));
    if (*v->getValue() <= *alpha->getValue()) return v;
    beta = minimum(beta, v);
    temp = temp->getNext();
  }
  return v;
}

template <class S>
S* min_value(S *tree, S* alpha, S* beta) {
	if (!tree->hasChildren()) return tree;

	S *temp = tree->getChildren();
	S* v = new S(new int(INT_MAX));
	while (temp != NULL) {
		v = minimum(v, max_value(temp, alpha, beta));
		if (*v->getValue() <= *alpha->getValue()) return v;
		beta = maximum(beta, v);
		temp = temp->getNext();
	}
	return v;
}

template <class T>
T* minimum(T* val1, T* val2) {
  T* min = NULL;
  if (*val1->getValue() < *val2->getValue())
    min = val1;
  else
    min = val2;

    return min;
}

template <class T>
T* maximum(T* val1, T* val2) {
  T* max = NULL;
  if (*val1->getValue() > *val2->getValue())
    max = val1;
  else
    max = val2;

    return max;
}

#endif
