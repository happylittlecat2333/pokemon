#include <iostream>
using namespace std;
template <typename T>
T abs(T num){
	return num < 0 ? -num: num;
}
int main(){
	int n1 = -5;
	double n2 = -10;
	cout << abs(n1) << endl;
	cout << abs(n2) << endl;
	return 0;
}