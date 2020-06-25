#include <iostream>
#include <chrono>
#include <random>
using namespace std;
int main()
{
    // 随机数种子
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 rand_num(seed);	 // 大随机数
	for(int i=0; i<5; i++) cout << rand_num() << endl;
	return 0;
}
