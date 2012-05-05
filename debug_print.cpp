#include <iostream>
using namespace std;

#define DEBUG 1

void dprint(char* str, int level = 1) {
	if (DEBUG >= level) {
		cout << str << endl;
	}
}
