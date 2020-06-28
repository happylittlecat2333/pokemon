/* code:UTF8 */
#include<iostream>
#include<cmath>
using namespace std;

class Point 	//Point类
{
	private:
		int X, Y;
	public:
		Point();				 //初始化不输入时,为(0,0)
		Point(float x, float y); //初始化时为(x,y)	
		float GetX(){return X;}; //返回X
		float GetY(){return Y;}; //返回Y
		void SetXY(float x, float y){X=x, Y=y;}; //设置X，Y		
		float distance(Point p);	//两点距离

		~Point();	//析构
};

class Round 	//圆形类
{
	private:
		int num;		//序号
		float radius;	//半径
		Point CCircle;	//圆心坐标
	public:
		Round(int num);	//初始化
		float GetR(){return radius;}; 		//返回半径的值
		int GetNum(){return num;};			//返回序号
		Point PointOut(){return CCircle;};	//返回Point类CCircle
		friend void Cross(Round r1, Round r2);	//友元，可以访问private
		~Round();	//析构
};

Point::Point(){
	X=0, Y=0;
}

Point::Point(float x, float y){
	X=x, Y=y;
}


float Point::distance(Point p){	//返回与p之间的距离(同类可以访问私有)
	float distance=sqrt(pow(this->X - p.X, 2) + pow(this->Y - p.Y, 2));
	return distance;
}

Point::~Point(){
	cout << "deleting Point\n";
}


Round::Round(int num){		//初始化(x, y, radius)
	cout << "Initial Round " << num << "(x, y, radius):\n";
	float x,y;
	cin >> x >> y;
	cin >> radius;
	CCircle.SetXY(x, y);
	this->num=num;
}


void Cross(Round r1, Round r2){		//判断r1和r2是否相交
	float sum_radius=r1.radius + r2.radius;
	cout << "sum_radius : " << sum_radius << endl;

	float distance=r1.CCircle.distance(r2.CCircle);
		//函数参数为类对象，调用拷贝构造函数r2.CCirle
	cout << "distance : " << distance << endl;

	if(sum_radius >= distance)
		cout << "Crossing\n";
	else cout << "Not Crossing\n";
}


Round::~Round(){	//析构函数
	cout << "deleting Round "<< GetNum() << endl;
}

int main(){
	Round round_1(1);	//初始化圆形
	Round round_2(2);	
	Cross(round_1, round_2);	//函数参数为类对象，调用拷贝构造函数，复制round_1, round_2
	return 0;
}

