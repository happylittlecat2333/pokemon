/* code:UTF8 */
#include<iostream>
#define row 4	//定义矩阵大小
#define col 5
using namespace std;

void Initial(int **);				//矩阵初始化函数
void Print(int **);					//矩阵输出函数
void Add(int **, int **, int **);	//矩阵相加函数
void Sub(int **, int **, int **
);	//矩阵相减函数
void Delete_array(int **);			//释放矩阵函数

int main(){
	int **array_1, **array_2, **array_3; //new动态申请，保存在指针

	array_1 = new int *[row];		//动态申请
	array_2 = new int *[row];

	array_3 = new int *[row];

	for(int i=0; i<row; i++){		//动态申请2维数组
		array_1[i]=new int[col];
		array_2[i]=new int[col];
		array_3[i]=new int[col];		
	}

	Initial(array_1);			//初始化A1，A2
	Initial(array_2);

	Add(array_1, array_2, array_3); //计算并输出A3=A1+A2
	Sub(array_1, array_2, array_3); //计算并输出A3=A1-A2

	Delete_array(array_1);		//释放矩阵空间
	Delete_array(array_2);
	Delete_array(array_3);
	return 0;
}

void Initial(int **array){	//初始化
	cout << "Initial:\n";
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			cin >> array[i][j];
	}
}

void Print(int **array){	//输出矩阵，由Add, Sub函数调用
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			cout << array[i][j] << ' ';
		} 	
		cout << endl;
	}  
}

void Add(int **array_1, int **array_2, int **array_3){ //矩阵相加
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			array_3[i][j]=array_1[i][j]+array_2[i][j];
		}
	}
	cout << "A3=A1+A2:\n";
	Print(array_3);
}

void Sub(int **array_1, int **array_2, int **array_3){ //矩阵相减
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			array_3[i][j]=array_1[i][j]-array_2[i][j];
		}
	}
	cout << "A3=A1-A2:\n";	
	Print(array_3);
}

void Delete_array(int **array){		//释放
	for(int i=0; i<row; i++){
		delete [] array[i];
	}
}
