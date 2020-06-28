#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int Rand_int(int min, int max){ 	//返回1-1000的整数
	return (min + rand() % max);	//rand每次返回一个当前的种子对应的随机数
}

int main(){
	srand((int)time(0));	//srand用系统时间产生设置随机数种子
	int rand_int = Rand_int(1, 1000);	//产生随机数
	
	cout << "Guess Game Start!! (1-1000 integer):\n"; //提示用户猜价格

	int guess = 0;

	while(true){	
		cin >> guess;
		if(guess < 1 || guess > 1000)	//检查输入合法性
			cout << "Input Error. Please try again\n";
		else if(guess > rand_int)	//高了
			cout << "Too big, try again\n";
		else if(guess < rand_int)	//低了
			cout << "Too small, try again\n";
		else
			{cout << "Congratulation!!\n"; break;}
	}

	return 0;
}