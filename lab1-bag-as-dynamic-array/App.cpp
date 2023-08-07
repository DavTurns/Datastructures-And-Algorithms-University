#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>


using namespace std;




int main() {

    test_has_same_elements();
	testAll();
    cout << "Short tests over" << endl;
	testAllExtended();
	cout << "All test over" << endl;




	return 0;
}