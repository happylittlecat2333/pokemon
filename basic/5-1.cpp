#include<iostream>

using namespace std;

class Shape_1	//计算面积的方法定义为虚函数
{
	protected:
		float area;	
	public:
		Shape_1(){area=0;};		
		virtual float Area(){return area;}; //在派生类中，可以对基类的虚函数进行重写（覆盖），实现动态联编
		~Shape_1(){cout<<"deleting shape_1"<<endl;};	
};

class Rectangle_1 : public Shape_1
{
	private:
		float length, width;	//长宽
	public:
		Rectangle_1(float length, float width){this->length=length; this->width=width;}; 
		float Area(){area=length*width; return area;} //重写覆盖
		~Rectangle_1(){cout<<"deleting Rectangle_1"<<endl;};	
};



class Shape_2	//shape基类定义为抽象类
{
	protected:
		float area;	
	public:
		Shape_2(){area=0;};		
		virtual float Area()=0;	//在纯虚函数, 只定义方法调用的格式
		~Shape_2(){cout<<"deleting shape_2"<<endl;};	
};

class Rectangle_2 : public Shape_2
{
	private:
		float length, width;	//长宽
	public:
		Rectangle_2(float length, float width){this->length=length; this->width=width;}; 
		float Area(){area=length*width; return area;} //实现
		~Rectangle_2(){cout<<"deleting Rectangle_2"<<endl;};	
};

int main(){
	Shape_1 s_1;
	Rectangle_1 r_1(3,4);

	// Shape_2 s_2;	//报错，抽象类不能声明对象
	Rectangle_2 r_2(4,5);
	return 0;
}

/*	虚函数

1.虚函数为非静态，动态绑定（在程序运行时绑定所属的类）
2.在调用对象虚函数时，根据对象所属的派生类，决定调用哪个函数实现(动态联编)
3.只需要重写派生类的特殊部分的代码，其他都从基类中继承(最大限度的重用)，可以在基类的函数中调用派生类的函数
4.编译程序在编译时无法确定调用哪一个类的方法，需要在运行时动态地确定具体调用哪一个类的方法
*/


/*	抽象类

1.如果类中至少有一个函数被声明为纯虚函数，则这个类就是抽象类
2.纯虚函数, 只定义方法调用的格式，通过在声明中使用 "= 0" 来指定的
3.不能声明抽象类的对象，必须要在派生类中重写虚函数
4.抽象类的目的，是为了给其他类提供一个可以继承的适当的基类，函数留给派生类去实现

*/