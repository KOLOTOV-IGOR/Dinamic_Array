#include "din_arr.h"

int main() {
	din_arr<double> v1;
	din_arr<double> v2;
	din_arr<double> v3;
	v1.assign(3, 8.0);
	v2.insert(-1); v2.insert(808); v2.insert(88);
	cout << v1 << endl;
	cout << v2 << endl;
	cout << v1 - v2 << endl;
	double a = 2;
	cout << v1 + a*v2 << endl;
	cout << v2*a << endl;

	return 0;
}