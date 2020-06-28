#include<iostream>
using namespace std;

class Point
{
	private:
		float x, y;
	public:
		Point(){x=y=0;}	//构造
		Point& operator++(){	//++p 相当于p.Point::operator++() (p=p+1;  b=p)
			x++; y++;
			return *this;	//返回的是引用
		}
		Point operator++(int){	//p++ 相当于p.Point::operator++(0) (b=p; p=p+1) 
			Point tmp = *this;	//拷贝构造，函数结束后析构
			x++; y++;
			return tmp;
		}
		Point& operator--(){	//p-- (p=p-1; b=p)
			x--; y--;
			return *this;
		}
		Point operator--(int){	//p-- (b=p; p=p-1)
			Point tmp = *this;
			x--; y--;
			return tmp;
		}
		void getXY(){cout << "(" << x << ", " << y << ")\n";}
		~Point(){cout << "deleting\n";}; //析构
};

int main(){
	Point point, tmp;
	cout << "point Initial:\n";
	point.getXY();
	cout << endl;

	tmp = point++;				//执行b=p++ (b=p; p=p+1)
	cout << "tmp=point++:\n";
	cout << "point:"; point.getXY();
	cout << "tmp:"; tmp.getXY();
	cout << endl;

	tmp = ++point;				//执行b=++p (p=p+1; b=p)
	cout << "tmp=++point:\n";
	cout << "point:"; point.getXY();
	cout << "tmp:"; tmp.getXY();
	cout << endl;

	tmp = point--;				//执行b=p--	(b=p; p=p-1)
	cout << "tmp=point--:\n";
	cout << "point:"; point.getXY();
	cout << "tmp:"; tmp.getXY();
	cout << endl;

	tmp = --point;				//执行b=--p (p=p-1; b=p)
	cout << "tmp=--point:\n";
	cout << "point:"; point.getXY();
	cout << "tmp:"; tmp.getXY();

	return 0;
}