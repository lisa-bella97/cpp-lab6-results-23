#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include <memory>
#include "ComplexMatrix.h"
#include "Ptr.h"

using namespace std;
using namespace placeholders;

void addNumber(int& number, int j) { number += j; }
void addIndex(int& number, int& ind) { number += ind++; }
bool isSolution_1(int x, int k, int b) { return k*x + b == 0; }
bool isLess(int number, int bound) { return number < bound; }
bool isSolution_2(int x, int a, int b, int c) { return a*x*x + b*x + c == 0; }

template<class T, class U>
vector<U> convert(vector<T> vect)
{
	vector<U> res;
	for (int i = 0; i < vect.size(); i++)
		res.push_back(static_cast<U>(vect[i]));
	return res;
}

template<class T, class U>
list<U> convert(list<T> l)
{
	list<U> res;
	for (auto it = l.begin(); it != l.end(); it++)
		res.push_back(static_cast<U>(*it));
	return res;
}

template<class T, class U>
ComplexMatrix<U> convert(ComplexMatrix<T> matrix)
{
	return ComplexMatrix<U>(matrix);
}

void foo(Shared_ptr<int> p)
{
	Shared_ptr<int> p1(p);
	Shared_ptr<int> p2(p);
	cout << "p2: " << p2.use_count() << '\n';
}

int main()
{
	int** matrix1 = new int*[2];
	for (int i = 0; i<2; i++)
		matrix1[i] = new int[2];
	int** matrix2 = new int*[2];
	for (int i = 0; i<2; i++)
		matrix2[i] = new int[1];

	matrix1[0][0] = 0;
	matrix1[0][1] = -2;
	matrix1[1][0] = 3;
	matrix1[1][1] = 4;

	matrix2[0][0] = 1;
	matrix2[1][0] = 2;
	
	ComplexMatrix<int> complMatrix1(matrix1, 2, 2);
	ComplexMatrix<int> complMatrix2(matrix2, 2, 1);

	int k = 1, l = 0;
	int bound = 3;
	int a = 1, b = 0, c = -4, value = 0, num = 3;
	// Сложение каждого элемента матрицы с заданным числом
	for_each(complMatrix2.begin(), complMatrix2.end(), bind(addNumber, _1, a));
	cout << complMatrix2 << endl;
	// Сложение каждого элемента матрицы с его порядковым номером (foreach), номера назначаются построчно
	for_each(complMatrix2.begin(), complMatrix2.end(), bind(addIndex, _1, 0));
	cout << complMatrix2 << endl;
	// Нахождение количества элементов в матрице, равных заданному числу
	cout << count(complMatrix1.begin(), complMatrix1.end(), num) << endl;
	// Нахождение количества элементов в матрице, удовлетворяющих решению уравнения kx + b = 0
	cout << count_if(complMatrix1.begin(), complMatrix1.end(), bind(isSolution_1, _1, k, l)) << endl;
	// Нахождение количества элементов в матрице меньше заданного числа
	cout << count_if(complMatrix1.begin(), complMatrix1.end(), bind(isLess, _1, bound)) << endl;
	// Нахождение первого элемента, удовлетворяющего решению уравнения ax^2 + bx + c = 0
	cout << *find_if(complMatrix1.begin(), complMatrix1.end(), bind(isSolution_2, _1, a, b, c)) << endl;
	// Проверка в матрице наличия заданного элемента
	cout << *find(complMatrix1.begin(), complMatrix1.end(), value) << endl;

	try
	{
		complMatrix1.setZero(0);
		complMatrix2.setZero(0);
		ComplexMatrix<int> result1 = complMatrix1 | complMatrix2;
		ComplexMatrix<int> result2 = complMatrix1*complMatrix2;
		ofstream fout("Complex.txt");
		fout << complMatrix1 << endl;
		fout << ~complMatrix1 << endl;
		fout << result1 << endl;
		fout << result2 << endl;
		fout.close();
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	for (int i = 0; i < 2; i++)
		delete [] matrix1[i];
	delete [] matrix1;

	for (int i = 0; i < 2; i++)
		delete [] matrix2[i];
	delete [] matrix2;

	vector<char> vec;
	vec.push_back('a');
	vec.push_back('v');
	vector<int> v = convert<char, int>(vec);
	for (int i = 0; i < 2; i++)
		cout << v[i] << "  ";
	cout << endl;

	list<double> list_1;
	list_1.push_back(3.4);
	list_1.push_back(5.7);
	list<int> list_2 = convert<double, int>(list_1);
	for (auto it = list_2.begin(); it != list_2.end(); it++)
		cout << *it << "  ";
	cout << endl;

	ComplexMatrix<char> result = convert<int, char>(complMatrix1);
	cout << result;

	Shared_ptr<int> p1;
	Shared_ptr<int> p2 (new int);
	Shared_ptr<int> p3 (p2);

	cout << "use_count:\n";
	cout << "p1: " << p1.use_count() << '\n';
	cout << "p2: " << p2.use_count() << '\n';
	cout << "p3: " << p3.use_count() << '\n';
	foo(p2);
	cout << "p2: " << p2.use_count() << '\n';

	system("pause");
	return 0;
}
