#include <iostream>
using namespace std;

#define DEBUG 0

void dprint(char* str, int level = 1) {
	if (DEBUG >= level) {
		cout << str << endl;
	}
}
