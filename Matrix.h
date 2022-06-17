#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>
#include <string>
#include <conio.h>

using std::runtime_error;

template <class E>
class Matrix{
	private:
		int m, n, l=0;
		E** matrix;
		float pivot, coefficient;
		E array = {};
		
	public:
		//CONSTRUCTOR
		Matrix(int m, int n) {
			this->m = m;
			this->n = n;
			matrix = new E*[m];
			for(int i=0; i<m; i++) {
				matrix[i] = new E[n];
			}
		}
		
		//DESTRUCTOR
		~Matrix(){
			//std::cout<<"Inside the destructor"<<std::endl;
			for(int i=0; i<m; i++){
				delete[] matrix[i];
			}
			delete[] matrix;
		}

		void solveSystem() {
			for(int i=0; i<this->m; i++){
				if(matrix[i][l]==0){
					for(int j=0; j<this->n; j++){
						array = matrix[i][j];
						matrix[i][j] = matrix[i+1][j];
						matrix[i+1][j] = array;
					}
				}
				pivot = matrix[i][l];
				for(int j=0; j<this->n; j++){					
					matrix[i][j] /= pivot;
				}
				for(int k=0; k<this->m; k++){		
					if(k!=i){
						coefficient = (matrix[k][l])*-1;	
						for(int j=0; j<this->n; j++){							
							matrix[k][j] += (matrix[l][j]*coefficient);
						}		
					}
				}
				l++;
			}
		}
		
		void matrixAddSub(int opt) {
			int x, numMxToAdd=2;
			float value, matrixValue;
			Matrix<float> matrixResult(this->m, this->n);
					
			switch(opt) {
				case 1:
					std::cout<<"\nWho many matrices do you want to add? "; std::cin>>numMxToAdd;
					break;
				case 2:
					std::cout<<"\nWho many matrices do you want to add? "; std::cin>>numMxToAdd;
					break;
			}
		
			Matrix<float> *matricesToAdd[numMxToAdd];
					
			system("CLS");
			std::cout<<"\n\tImportant! The matrices to sum will have the same length!\n\n\n\tPress enter to continue."<<std::endl;
			getch();
			system("CLS");
					
			for(int i=0; i<numMxToAdd; i++) {
				matricesToAdd[i] = new Matrix<float>(this->m, this->n);
				system("CLS");
				std::cout<<"\n\n";
				matricesToAdd[i]->setData();
				std::cout<<"\n";
				matricesToAdd[i]->checkMatrixData();
			}
					
			system("CLS");
					
			switch(opt) {
				case 1: 
					for(int i=0; i<this->m; i++) {
						for(int j=0; j<this->n; j++) {
							for(l=0; l<numMxToAdd; l++) {
								matrixValue += matricesToAdd[l]->getValue(i,j);
							}
							value = this->getValue(i,j) + matrixValue;
							matrixResult.setValue(i,j,value);
							matrixValue = 0;	
						}
					}
					break;
				
				case 2:
					for(int i=0; i<this->m; i++) {
						for(int j=0; j<this->n; j++) {
							for(l=0; l<numMxToAdd; l++) {
								matrixValue += matricesToAdd[l]->getValue(i,j);
							}
							value = this->getValue(i,j) - matrixValue;
							matrixResult.setValue(i,j,value);
							matrixValue = 0;	
						}
					}
					break;
			}
					
			system("CLS");
			std::cout<<"The result is:\n\n";
			matrixResult.printMatrix();
			std::cout<<"\n\n\tPress enter to continue."<<std::endl;
			getch();
			system("CLS");
		}
		
		void multiplication() {
			int m, n, numMxToAdd=2;
			float x, value, matrixValue;
					
			std::cout<<"\nDigit the dimension of the matrix to multiply.\n\n";
			std::cout<<"Digit the number of rows: "; std::cin>>m;
			std::cout<<"Digit the number of columns: "; std::cin>>n;
			system("CLS");
					
			if(this->n == n) {
				Matrix<float> matrixToMultiply(m, n);
				Matrix<float> matrixResult(this->m, n);
				
				matrixToMultiply.setData();
				matrixToMultiply.checkMatrixData();
						
				for(int i=0; i<this->m; i++) {
					for(int j=0; j<this->n; j++) {
						for(int l=0; l<this->n; l++) {
							x += this->getValue(i,l) * matrixToMultiply.getValue(i,j);
						}
						matrixResult.setValue(i,j,x);
					}
				}
							
				system("CLS");
				std::cout<<"The result is:\n\n";
				matrixResult.printMatrix();
				std::cout<<"\n\n\tPress enter to continue."<<std::endl;
				getch();
				system("CLS");
			}
		}

		void multByScalar() {
			float scalar, value;
			Matrix<float> matrixResult(this->m,this->n);
			
			std::cout<<"\nWhat number do you want to multiply your matrix by?: "; std::cin>>scalar;
			
			for(int i=0; i<this->m; i++) {
				for(int j=0; j<this->n; j++) {
					value = this->getValue(i,j)*scalar;
					matrixResult.setValue(i,j,value);
				}
			}
			
			system("CLS");
			std::cout<<"The result is:\n\n";
			matrixResult.printMatrix();
			std::cout<<"\n\n\tPress enter to continue."<<std::endl;
			getch();
			system("CLS");
		}

		void validInvMatrix() {
			bool flag = false;
			
			if(this->m!=this->n || this->m>3) {
				system("CLS");
				std::cout<<"\n\tImpossible! The matrix must have the same rows and columns length and cannot exceed third length"<<std::endl;
				flag = true;
			} else if(this->m>3) {
				system("CLS");
				std::cout<<"\n\tImpossible! The matrix cannot exceed third length"<<std::endl;
				flag = true;
			} else if(this->checkDeterminant() == 0) {
				system("CLS");
				std::cout<<"\n\tImpossible! The matrix cannot have determinant equal to 0"<<std::endl;
				flag = true;
			} else {
				this->copyInvMatrix(false);
			}
			
			if(flag) {
				this->makeNewInvMatrix();
			}
		}
		
		void makeNewInvMatrix() {
			int opt;
			char mOpt;
			bool isNewM = false; // if the matrix was selected again
			
			std::cout<<"\n\nDo you want to select a new matrix? Y/N: "; std::cin>>mOpt;
								
			switch(mOpt) {
				case 'Y':
					isNewM = true;
					this->copyInvMatrix(isNewM);
					break;
				case 'N':
					opt = 6;
					break;
			}
		}
		
		void copyInvMatrix(bool isNewM) {
			int x;
			
			if(!isNewM) {
				Matrix<float> matrixInvObj(this->m,2*this->n);
			
				for(int i=0; i<this->m; i++) {
					for(int j=0; j<this->n; j++) {
						x = this->getValue(i,j);
						matrixInvObj.setValue(i,j,x);
					}
				}

				matrixInvObj.computeInverseMatrix();
			}
			
			else {
				int m,n;
				
				system("CLS");						
				std::cout<<"\nDigit the length of the new matrix: "; std::cin>>m;
				n=m;
													
				Matrix<float> newMatrixObj(m,n);
				Matrix<float> matrixInvObj(m,2*n);
							
				std::cout<<"\n";
				newMatrixObj.setData();
				newMatrixObj.checkMatrixData();
				
				for(int i=0; i<m; i++) {
					for(int j=0; j<n; j++) {
						x = newMatrixObj.getValue(i,j);
						matrixInvObj.setValue(i,j,x);	
					}
				}
				
				matrixInvObj.computeInverseMatrix();
			}				
		}
		
		void computeInverseMatrix() {
			
			for(int i=0; i<this->m; i++) {
				for(int j=n/2; j<this->n; j++) {
					if(i+this->m==j) {
						this->setValue(i,j,1);
					} else {
						this->setValue(i,j,0);
					}
				}
			}
				
			system("CLS");
			this->printMatrix();
			getch();
					
			this->solveSystem();
			std::cout<<"\n\nInverse matrix by Gauss-Jordan Algorithm:\n\n";
			this->printMatrix();
			getch();
		}
		
		int checkDeterminant() {
			int diagonal[4], l=0, determinant, x, operations[6];
			
				switch(this->m) {
					case 2:
						for(int i=0; i<this->m; i++) {
							for(int j=0; j<this->n; j++) {
								diagonal[l] = this->getValue(i,j);
								l++;
							}
						}
						
						determinant = (diagonal[0]*diagonal[3]) - (diagonal[1]*diagonal[2]);
						break;
					case 3:
					{
						int dupRow = this->m+2; //5
						
						Matrix<float> matrixObjDuplicate(dupRow,n);
										
						for(int i=0; i<this->m; i++) {
							for(int j=0; j<this->n; j++) {
								x = this->getValue(i,j);
								matrixObjDuplicate.setValue(i,j,x);
							}
						}
												
						for(int i=0; i<this->n; i++) {
							x = matrixObjDuplicate.getValue(0,i);
							matrixObjDuplicate.setValue(3,i,x);
							x = matrixObjDuplicate.getValue(1,i);
							matrixObjDuplicate.setValue(4,i,x);
						}
						
						determinant = (matrixObjDuplicate.getValue(0,0))*(matrixObjDuplicate.getValue(1,1))*(matrixObjDuplicate.getValue(2,2))
						+(matrixObjDuplicate.getValue(1,0))*(matrixObjDuplicate.getValue(2,1))*(matrixObjDuplicate.getValue(3,2))
						+(matrixObjDuplicate.getValue(2,0))*(matrixObjDuplicate.getValue(3,1))*(matrixObjDuplicate.getValue(4,2))
						-(matrixObjDuplicate.getValue(0,2))*(matrixObjDuplicate.getValue(1,1))*(matrixObjDuplicate.getValue(2,0))
						-(matrixObjDuplicate.getValue(1,2))*(matrixObjDuplicate.getValue(2,1))*(matrixObjDuplicate.getValue(3,0))
						-(matrixObjDuplicate.getValue(2,2))*(matrixObjDuplicate.getValue(3,1))*(matrixObjDuplicate.getValue(4,0));
						
						break;
					}
					default:
						std::cout<<"This option can not solve matrices up to 3x3.\n\n\tPress enter to continue."<<std::endl;
						determinant = 0;
						break;
				}
			
			/*
			system("CLS");
			cout<<"\nThe determinant is: "<<determinant<<endl;
			cout<<"\n\n\tPress enter to continue."<<endl;
			getch();
			system("CLS");*/
			
			return determinant;
		}
		
		void printMatrix(){
			for(int i=0; i<this->m; i++){
				for(int j=0; j<this->n; j++){
					this->systemException(i,j);
					std::cout<<this->getValue(i,j)<<"\t";
				}
				std::cout<<"\n";
			}	
		}
		
		void checkMatrixData() {
			int changeValue,columnValue,rowValue,newValue;
		
			do {
				this->printMatrix();
				std::cout<<"\nPress 1 if you want to use this matrix or 0 if you want to change a value: "; std::cin>>changeValue;
		
				if(changeValue==0) {	
					std::cout<<"\n\tMatrix["<<this->m<<"]["<<this->n<<"]"<<std::endl;
					std::cout<<"\nDigit the new value and its position"<<std::endl;
					std::cout<<"\nRow: "; std::cin>>rowValue;
					std::cout<<"Column: "; std::cin>>columnValue;
					std::cout<<"New value: "; std::cin>>newValue;
					this->setValue(rowValue,columnValue,newValue);
					system("CLS");
					std::cout<<"\nThe changes have been made successfully.";
					std::cout<<"\n\n";
				} 
				
				else if(changeValue!=1) {
					system("CLS");
					std::cout<<"\n\tERROR: Press a valid key\n"<<std::endl;
				}
			} while(changeValue!=1);
		}
		
		void systemException(int row, int column){
			std::string value = std::to_string(matrix[row][column]);
			if(value=="nan") throw runtime_error("The system has no solution or has infinite solutions");
		}
		
		void valid(int row, int column){
			if(row < 0 || row >= m){
				throw runtime_error("Invalid row.");
			}
			if(column < 0 || column >= n){
				throw runtime_error("Invalid column.");
			}
		}
		
		void printRowsColumns(){
			std::cout<<"\n\nNumber of rows: "<<this->getRows()<<std::endl;
			std::cout<<"Number of columns: "<<this->getColumns()<<std::endl;
		}
		
		int getRows(){
			return m;
		}
		
		int getColumns(){
			return n;
		}
		
		E getValue(int row, int column){
			valid(row,column);
			return matrix[row][column];
		}

		void setData(){
			int x;
			
			for(int i=0; i<this->m; i++){
				for(int j=0; j<this->n; j++){
					std::cout<<"Digit the element ["<<i<<"]["<<j<<"]: "; std::cin>>x;
					this->setValue(i,j,x);
					system("CLS");
					std::cout<<"\n";
				}
			}
		}
		
		void setValue(int row, int column, E value){
			valid(row,column);
			matrix[row][column] = value;
		}
};

#endif // MATRIX_H
