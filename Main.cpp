#include <iostream>
#include <fstream>
#include "ComplexMatrix.h"
#include "Vector.h"
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

void addNumber(int& number) { number+=5; }

int main()
{
	/*vector<vector<ComplexNumber>> matrix1(2);
	for (int i=0; i<2; i++)
		matrix1[i] = vector<ComplexNumber>(3);
	vector<vector<ComplexNumber>> matrix2(3);
	for (int i=0; i<3; i++)
		matrix2[i] = vector<ComplexNumber>(1);
	vector<vector<ComplexNumber>> matrix3(2);
	for (int i=0; i<2; i++)
		matrix3[i] = vector<ComplexNumber>(2);

	matrix1[0][0] = ComplexNumber(1.,2.);
	matrix1[0][1] = ComplexNumber(2.,1.);
	matrix1[0][2] = ComplexNumber(1.,3.);
	matrix1[1][0] = ComplexNumber(2.,0.);
	matrix1[1][1] = ComplexNumber(4.,2.);
	matrix1[1][2] = ComplexNumber(2.,5.);


	matrix2[0][0] = ComplexNumber(2.,2.);
	matrix2[1][0] = ComplexNumber(1.,4.);
	matrix2[2][0] = ComplexNumber(2.,2.);

	matrix3[0][0] = ComplexNumber(1.,2.);
	matrix3[0][1] = ComplexNumber(2.,1.);
	matrix3[1][0] = ComplexNumber(1.,3.);
	matrix3[1][1] = ComplexNumber(2.,0.);*/

	vector<vector<int>> matrix1(2);
	for (int i=0; i<2; i++)
		matrix1[i] = vector<int>(2);
	vector<vector<int>> matrix2(2);
	for (int i=0; i<2; i++)
		matrix2[i] = vector<int>(1);
	vector<vector<int>> matrix3(2);
	for (int i=0; i<2; i++)
		matrix3[i] = vector<int>(2);

	matrix1[0][0] = 1;
	matrix1[0][1] = 2;
	matrix1[1][0] = 2;
	matrix1[1][1] = 4;

	matrix2[0][0] = 1;
	matrix2[1][0] = 2;
	
	ComplexMatrix<int> complMatrix1(matrix1);
	ComplexMatrix<int> complMatrix2(matrix2);
	
	//ComplexMatrix<ComplexNumber> complMatrix2(matrix2);
	//ComplexMatrix<ComplexNumber> complMatrix3(matrix3);

	ComplexNumber num(0., 0.);
	try
	{
		//complMatrix1.begin();
		for_each(complMatrix1.begin(), complMatrix1.end(), addNumber);
		//ComplexMatrix<int> result1 = complMatrix1|complMatrix2;
		//ComplexMatrix<ComplexNumber> result2 = complMatrix1 * complMatrix2;
		//ComplexMatrix<ComplexNumber> result3 = result1 + complMatrix3;
		//ComplexMatrix<ComplexNumber> result4 = complMatrix3 * num;
		ofstream fout("Complex.txt");
		fout << complMatrix1 << endl;
		/*fout << result1 << endl;
		fout << result2 << endl;
		fout << result3 << endl;
		fout << result4 << endl;*/
		fout.close();
	}
	catch(exception& e)
	{
      		cerr << e.what() << endl;
	}

	for (int i = 0; i < 2; i++)
		matrix1[i].clear();
	matrix1.clear();

	for (int i = 0; i < 2; i++)
		matrix2[i].clear();
	matrix2.clear();

	/*for (int i = 0; i < 2; i++)
		matrix3[i].clear();
	matrix3.clear();*/
	
	system("pause");
	return 0;
}