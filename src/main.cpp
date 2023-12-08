#include "looongint.hpp"
#include <iostream>

using namespace std;

int main() {
	LooongInt l("99999999999999999999999999999999999999999999999999999999"),
		r("77777777777777777777777777777777777777777777777777777777777777");
	cout << l.get() << "\n+\n" << r.get() << "\n=\n"
		<< (l + r).get() << endl;
	return 0;
}