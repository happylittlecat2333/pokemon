#include<iostream>
#include<cmath>
#define pi 3.14
using namespace std;

class Shape
{
	protected:
		float area;	//派生类可以访问protected，外部访问不了；派生类共有
	public:
		Shape();		//构造函数
		float Area();	//同名隐藏；输出area
		~Shape();		//析构函数
};

class Rectangle : public Shape
{
	private:
		float length, width;	//长宽
	public:
		Rectangle(float length, float width); //构造
		float Area();	//计算area，并输出
		~Rectangle();	//析构
};

class Round : public Shape
{
	private:
		float radius;	//半径
	public:
		Round(float radius);	//构造
		float Area();	//计算area，并输出
		~Round();		//析构
};

class Square : public Rectangle
{
	private:
		float l;	//边长
	public:
		Square(float l);	//构造
		float Area(); 	//计算area，并输出
		~Square();		//析构
};

Shape::Shape(){
	cout << "construct Shape\n";
	area=0;
}

float Shape::Area(){
	cout << "Shape Area:" << area << endl;
	return area;
}

Shape::~Shape(){
	cout << "deleting Shape\n";
	area=0;
}

Round::Round(float radius){
	cout << "construct Round\n";
	this->radius=radius;
}

float Round::Area(){
	area=pi*radius*radius;
	cout << "Round Area:" << area << endl;
	return area;
}

Round::~Round(){
	cout << "deleting Round\n";
}

Rectangle::Rectangle(float length, float width){
	cout << "construct Rectangle\n";
	this->length=length, this->width=width;
}

float Rectangle::Area(){
	area=length*width;
	cout << "Rectangle Area:" << area << endl;
	return area;
}

Rectangle::~Rectangle(){
	cout << "deleting Rectangle\n";
}

Square::Square(float l):Rectangle(l ,l){ //派生类的构造函数；同时赋值给基类Rectangle
	cout << "construct Square\n";
	this->l = l;
}

float Square::Area(){
	area=l*l;
	cout << "Square Area:"<< area << endl;
	return area;
}

Square::~Square(){
	cout << "deleting Square\n";
}

int main(){
	float l; 
	cout << "input square length:\n";
	cin >> l;
	Square square(l);
	cout << endl;
	square.Area();				//同名隐藏规则
	square.Rectangle::Area();	//限定类名
	square.Shape::Area();

	float r;
	cout << "\ninput Round radius:\n";
	cin >> r;
	Round round(r);
	cout << endl;
	round.Area();			//同名隐藏规则
	round.Shape::Area();	//限定类名

	float length, width; 
	cout << "input Rectangle (length, width):\n";
	cin >> length >> width;
	Rectangle rectanle(length, width);
	cout << endl;
	rectanle.Area();			//同名隐藏规则
	rectanle.Shape::Area();		//限定类名

	cout << endl;

	return 0;
}
