/* code:UTF8 */

#include<iostream>
using namespace std;

int Lines, Rows;	//决定矩阵大小

class Matrix
{
	private:
		int lines, rows;	//矩阵大小
		int *ptr;			//根据矩阵大小动态申请
	public:
		int num;	//矩阵序号
		Matrix(int num);	//矩阵初始化，构造函数
		Matrix(int num, int lines, int rows);
		Matrix(Matrix& M);	//拷贝构造函数
		void MatrixIn();	//输入
		void MatrixOut();	//输出
		Matrix MatrixAdd(const Matrix& M1);//矩阵相加；引用常量方式，防止修改；返回新的矩阵
		Matrix MatrixSub(const Matrix& M1);//矩阵相减
		Matrix& operator=(const Matrix& M);//赋值重载，将M赋值到*this
		Matrix& operator+=(const Matrix& M);
		Matrix& operator-=(const Matrix& M);
		~Matrix();	//析构函数
};

Matrix::Matrix(int num){	//根据序号初始化
	cout << "Construct" << num << endl;
	this->lines=Lines, this->rows=Rows, this->num=num;
	ptr = new int[lines*rows];	//ptr[i*rows+j]表示ptr[i][j]
}

Matrix::Matrix(int num, int lines, int rows){	//构造函数
	this->lines=lines, this->rows=rows, this->num=num;
	ptr = new int[lines*rows];	//ptr[i*rows+j]表示ptr[i][j]
}

Matrix::Matrix(Matrix& M){	//拷贝构造函数
	cout << "Copy Constructor:" << M.num << "-->" << this->num << endl;
	lines=M.lines, rows=M.rows;
	for(int i=0;i<lines;i++)
		for(int j=0;j<rows;j++)
			ptr[i*rows+j]=M.ptr[i*rows+j];
}

void Matrix::MatrixIn(){	//输入
	cout << "Initial Matrix " << num <<":\n";
	for(int i=0;i<lines;i++)
		for(int j=0;j<rows;j++)
			cin >> ptr[i*rows+j];
}

void Matrix::MatrixOut(){	//输出
	cout << "Matrix " << num <<":\n";
	for(int i=0;i<lines;i++){
		for(int j=0;j<rows;j++)
			cout << ptr[i*rows+j] << ' ';
		cout << endl;
	}
}	

Matrix Matrix::MatrixAdd(const Matrix& M1){	//相加；引用常量方式，防止修改；返回新的矩阵
	Matrix M(0); //临时矩阵
	cout << "Matrix Add " << this->num <<"+"<< M1.num << "-->" << M.num <<"\n";
	for(int i=0;i<lines;i++){
		for(int j=0;j<rows;j++)
			M.ptr[i*rows+j]=(this->ptr)[i*rows+j]+M1.ptr[i*rows+j];
	}
	return M;
}

Matrix Matrix::MatrixSub(const Matrix& M1){	//相减；引用常量方式，防止修改；返回新的矩阵
	Matrix M(0); //临时矩阵
	cout << "Matrix Sub " << this->num <<"-"<< M1.num << "-->" << M.num <<"\n";
	for(int i=0;i<lines;i++){
		for(int j=0;j<rows;j++)
			M.ptr[i*rows+j]=(this->ptr)[i*rows+j]-M1.ptr[i*rows+j];
	}
	return M;
}

Matrix& Matrix::operator=(const Matrix& M){	//赋值操作符“=”重载；引用常量方式
	cout << "Matrix Copy" << endl;
	if(this == &M) return *this;
	lines=M.lines, rows=M.rows;
	for(int i=0;i<lines*rows;i++) ptr[i]=M.ptr[i];
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& M){
	cout << "Matrix +=" << endl;
	lines=M.lines, rows=M.rows;
	for(int i=0;i<lines*rows;i++) ptr[i]+=M.ptr[i];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& M){
	cout << "Matrix -=" << endl;
	lines=M.lines, rows=M.rows;
	for(int i=0;i<lines*rows;i++) ptr[i]-=M.ptr[i];
	return *this;
}

Matrix::~Matrix(){	//析构函数
	cout << "deleting Matrix " << num <<"\n";
	delete [] ptr;
}


int main(){
	// Lines=2, Rows=3;
	cout << "input (Lines Rows):\n";
	cin >> Lines >> Rows;
	int sum=Lines*Rows;

	Matrix A1(1), A2(2), A3(3);	//定义3个矩阵（传递序号）

	A1.MatrixIn();	//初始化A1，A2
	A2.MatrixIn();

	A3=A1.MatrixAdd(A2); //A3=A1+A2
	A3.MatrixOut();

	A3=A1.MatrixSub(A2); //A3=A1-A2
	A3.MatrixOut();

	cout << "\n-----Using New to Create Matrix-----\n";

	Matrix* pA1=new Matrix(1, Lines, Rows);	//使用new动态申请Matrix
	Matrix* pA2=new Matrix(2, Lines, Rows);
	Matrix* pA3=new Matrix(3, Lines, Rows);

	pA1->MatrixIn();	//初始化
	pA2->MatrixIn();

	(*pA3)=pA1->MatrixAdd(*pA2);	//A3=A1+A2
	pA3->MatrixOut();

	(*pA3)=pA1->MatrixSub(*pA2);	//A3=A1-A2
	pA3->MatrixOut();

	delete pA1;	//释放
	delete pA2;
	delete pA3;

	return 0;
}


