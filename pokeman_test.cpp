//============================================================================
// Name        : cs4511.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>

#include "Pokeman.h"

using namespace std;

int main(int args, char** argv) {

	TinyAttack t1("Cool Attack", 12);
	TinyAttack t2("Hot Attack", 20);

	Pokeman p(50, 70, t1, t2);

	Pokeman p2 = p;

	p.print();
	p2.print();

	return 0;
}
