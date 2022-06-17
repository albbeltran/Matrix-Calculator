#include <iostream>
#include <conio.h>
#include <time.h>
#include <string>
#include "Matrix.h"

using namespace std;

void mainMenu(Matrix<float>, int, int);
void operationsMenu(Matrix<float>, int, int);
void solveSystem(Matrix<float>, int, int);
int setRows(int,int);
int setColumns(int,int);

int main(int argc, char** argv) {
	int m, n, x;
	
	cout<<"Digit the length of the matrix or the digit 0 to generate a random length.\n\n";
	cout<<"Digit the number of rows: "; cin>>m;
	cout<<"Digit the number of columns: "; cin>>n;
	system("CLS");
	
	if(m==0) m = setRows(m,n);
	if(n==0) n = setColumns(m,n);
	
	Matrix<float> matrixObj(m,n);
	
	cout<<"\n";
	matrixObj.setData();
	matrixObj.checkMatrixData();
	
	operationsMenu(matrixObj,m,n);

	system("CLS");
	cout<<"\nThank you for using our program.\n\n\tPress enter to finish."<<endl;
	getch();

	return 0;
}

void mainMenu(Matrix<float> matrixObj, int m, int n) {
	int opt;
	
	system("CLS");
	cout<<"Your matrix is: \n"<<endl;
	matrixObj.printMatrix();
	
	do {
		system("CLS");
		cout<<"\nSelect an option: \n\n\t1. Operations \n\t2. Consult data \n\t3. Set values \n\t4. Change the matrix \n\t5. Exit\n\nOption: "; cin>>opt;
		
		switch(opt) {
			case 1:
				operationsMenu(matrixObj,m,n);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				if(opt!=5) {
					system("CLS");
					cout<<"\n\tERROR! You must select a valid option. Press enter to continue"<<endl;
					getch();
				}
		}
	} while(opt!=5);
}

void operationsMenu(Matrix<float> matrixObj, int m, int n) {
	int opt;
	
	system("CLS");
	cout<<"Your matrix is: \n"<<endl;
	matrixObj.printMatrix();
	
	do {
		system("CLS");
		cout<<"\nSelect an operation: \n\n\t1. Addition \n\t2. Subtraction\n\t3. Multiplication \n\t4. Multiplication by a scalar\n\t5. Inverse \n\t6. Solve system \n\t7. Exit \n\nOption: "; cin>>opt;
		
		switch(opt) {
			case 1:
				system("CLS");
				cout<<"\nMATRIX ADDITION"<<endl;
				matrixObj.matrixAddSub(1);
				break;
			case 2:
				system("CLS");
				cout<<"\nMATRIX SUBTRACTION"<<endl;
				matrixObj.matrixAddSub(2);
				break;
			case 3:
				matrixObj.multiplication();
				system("CLS");
				cout<<"\nMULTIPLICATION"<<endl;
				break;
			case 4:	
				system("CLS");
				cout<<"\nMULTIPLICATION BY SCALAR"<<endl;
				matrixObj.multByScalar();
				break;				
			case 5:
				matrixObj.validInvMatrix();
				break;
			case 6:
				solveSystem(matrixObj,m,n);
				break;	
			default:
				if(opt!=7) {
					system("CLS");
					cout<<"\n\tERROR! You must select a valid option. Press enter to continue"<<endl;
					getch();
				}
		}
	} while(opt!=7);
}

void solveSystem(Matrix <float> matrixObj, int m, int n){
	matrixObj.printMatrix();
	getch();
	matrixObj.solveSystem();
	cout<<"\n\nSolution by Gauss-Jordan Algorithm:\n\n";
	matrixObj.printMatrix();
	matrixObj.printRowsColumns();
	getch();
}

//RANDOM ROW LENGTH
int setRows(int m, int n){
	srand(time(NULL));
	if(n==0){
		n = 3 + rand()%(6);
		m = 2 + rand()%(n-1);
	}
	else m = 1 + rand()%(n-1);
	return m;
}

//RANDOM COLUMN LENGTH
int setColumns(int m, int n){
	srand(time(NULL));
	n = (m+1) + rand()%(6);
	return n;
}
