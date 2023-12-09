#include "looongint.hpp"
#include <iostream>

using namespace std;

int main() {
	std::string input("");
	while (true) {
		cout << "first num: ";
		cin >> input;
		if (input == "e") {
			return 0;
		}
		const LooongInt fnum(input);
		cout << "second num: ";
		cin >> input;
		if (input == "e") {
			return 0;
		}
		const LooongInt snum(input);
		cout << "action: ";
		cin >> input;
		if (input == "e") {
			return 0;
		}
		cout << "result: ";
		if (input == "+") {
			cout << fnum.get() << " + " << snum.get() <<
					" = " << (fnum + snum).get() << endl;
		}
		if (input == "-") {
			cout << fnum.get() << " - " << snum.get() <<
					" = " << (fnum - snum).get() << endl;
		}
		if (input == "x" || input == "*") {
			cout << fnum.get() << " x " << snum.get() <<
				" = " << (fnum * snum).get() << endl;
		}
	}
	return 0;
}