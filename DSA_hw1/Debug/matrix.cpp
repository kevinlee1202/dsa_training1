#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

Matrix::Matrix(const int& r, const int& c) //constructor
{
	row = r;
	col = c;

	array = new double*[row];
	for (int i = 0; i < row; i++)
	{
		array[i] = new double[col];
	}

}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
	row = rhs.row;
	col = rhs.col;

	array = new double*[row];
	for (int i = 0; i < row; i++)
	{
		array[i] = new double[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			array[i][j] = rhs.array[i][j];
			array[i][j] = rhs.array[i][j];
		}
	}
}

Matrix::~Matrix() //destructor
{
	for (int i = 0; i < row; i++)
	{
		delete[] array[i];
	}
	delete[] array;
}

double* & Matrix::operator [](const int& idx) const
{
	return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment constructor
{


	//delete old data
	for (int i = 0; i < row; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	//
	row = rhs.row;
	col = rhs.col;
	array = new double*[row];
	for (int i = 0; i < row; i++)
	{
		array[i] = new double[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			array[i][j] = rhs.array[i][j];
			array[i][j] = rhs.array[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator -() const
{
	Matrix Copy_Of_Minus(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Copy_Of_Minus.array[i][j] = -array[i][j];
			Copy_Of_Minus.array[i][j] = -array[i][j];
		}
	}
	return Copy_Of_Minus;
}

Matrix Matrix::operator +() const
{
	Matrix Copy_Of_Plus(row, col);
	for (int i = 0; i < Copy_Of_Plus.row; i++)
	{
		for (int j = 0; j < Copy_Of_Plus.col; j++)
		{
			Copy_Of_Plus.array[i][j] = array[i][j];
			Copy_Of_Plus.array[i][j] = array[i][j];
		}
	}
	return Copy_Of_Plus;
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
	Matrix Binary_Minus(row, col);
	for (int i = 0; i < Binary_Minus.row; i++)
	{
		for (int j = 0; j <Binary_Minus.col; j++)
		{
			Binary_Minus.array[i][j] = array[i][j] - rhs.array[i][j];
			Binary_Minus.array[i][j] = array[i][j] - rhs.array[i][j];
		}
	}
	return Binary_Minus;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
	Matrix Binary_Plus(row, col);
	for (int i = 0; i < Binary_Plus.row; i++)
	{
		for (int j = 0; j < Binary_Plus.col; j++)
		{
			Binary_Plus.array[i][j] = array[i][j] + rhs.array[i][j];
			Binary_Plus.array[i][j] = array[i][j] + rhs.array[i][j];
		}
	}
	return Binary_Plus;
}

Matrix Matrix::operator *(const Matrix& rhs) const
{

	Matrix Copy_Of_Multiple(row, rhs.col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < rhs.col; j++)
		{
			Copy_Of_Multiple.array[i][j] = 0;
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < rhs.col; j++)
		{
			for (int k = 0; k < col; k++)
			{
				Copy_Of_Multiple.array[i][j] += array[i][k] * rhs.array[k][j];
			}
		}
	}
	return Copy_Of_Multiple;
}

Matrix Matrix::operator /(const Matrix& rhs) const
{
	Matrix result = ((*this).operator*(rhs.inverse()));
	return result;
}

Matrix Matrix::inverse() const
{
	Matrix reverse(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == j) reverse.array[i][j] = 1;
			else reverse.array[i][j] = 0;
		}

	}
	int Column = 0;
	//眔à痻皚 癸à絬常琌1
	while (Column < row)     {
		//狦癸à絬Τ箂 碞┕т獶箂蛤ユ传
		if (array[Column][Column] == 0)
		{
			int swap_row = Column + 1;
			while (array[swap_row][Column] == 0)
			{
				swap_row++;
			}
			for (int j = 0; j<col; j++)
			{
				//
				double tmp = (array[Column][j]);
				array[Column][j] = array[swap_row][j];
				array[swap_row][j] = tmp;
				//reverse璶ユ传
				double tmp2 = (reverse.array[Column][j]);
				reverse.array[Column][j] = reverse.array[swap_row][j];
				reverse.array[swap_row][j] = tmp2;
			}
		}
		//ユ传ЧΘ
		int currentRow = Column + 1;
		double divider = array[Column][Column];
		for (int i = Column; i < col; i++){

			array[Column][i] = array[Column][i] / divider;
		}
		for (int i = 0; i < col; i++){

			reverse.array[Column][i] = reverse.array[Column][i] / divider;
		}
		for (int k = 0; k < row; k++){

			if (k != Column)
			{
				double multiplier = array[k][Column];
				for (int i = 0; i < col; i++)
				{

					array[k][i] = array[k][i] - array[Column][i] * multiplier;
					reverse.array[k][i] = reverse.array[k][i] - reverse.array[Column][i] * multiplier;
				}
			}
		}

		Column++;
	}
	//à痻皚挡
	//パà痻皚程秨﹍笲衡
	//Column = row - 1;
	//while (Column>0){
	//int currentRow = Column - 1;
	// for (int k = currentRow; k >= 0; k--){
	// for (int i = 0; i < col; i++){
	//reverse.array[k][i] = reverse.array[k][i] - reverse.array[Column][i] * array[k][Column];

	// }

	//}
	//Column--;

	//}
	return reverse;
}

void Matrix::read(const char* fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if (fp == NULL){
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for (int i = 0; i < r; i++)
	for (int j = 0; j < c; j++)
		fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char* fn)
{
	FILE *fp = fopen(fn, "w");
	if (fp == NULL){
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for (int i = 0; i < row; i++)
	for (int j = 0; j < col; j++)
		fprintf(fp, "%lf%c", array[i][j], " \n"[j == col - 1]);
	fclose(fp);
}

void Matrix::print() const
{
	for (int i = 0; i < row; i++)
	for (int j = 0; j < col; j++)
		printf("%lf%c", array[i][j], " \n"[j == col - 1]);
}