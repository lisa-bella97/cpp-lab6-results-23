#ifndef _COMPLEXMATRIX_H_
#define _COMPLEXMATRIX_H_
#include "ComplexNumber.h"
#include <stdexcept>
#include <vector>

template<class T>
class ComplexMatrix
{
private:
	std::vector<std::vector<T> > _matrix; 
	unsigned int _rows; 
	unsigned int _columns; 
	
public:
	class MatrixIterator : public std::iterator<std::input_iterator_tag, T>
	{
	private:
		std::vector<std::vector<T> > _data;
		unsigned int _n;
		unsigned int _m;
		unsigned int _index;
	public:
		MatrixIterator(std::vector<std::vector<T> > data, unsigned int n, unsigned int m, unsigned int index) : _data(data), _n(n), _m(m), _index(index) { }
		MatrixIterator operator++() { ++_index; return *this; }
		MatrixIterator operator+(unsigned int ind) 
		{ 
			if (_index + ind >= n*m)
				throw std::out_of_range("Out of range");
			_index += ind; 
			return *this; 
		}
		T& operator*() 
		{  
			if (_index >= _n*_m)
				throw std::out_of_range("Out of range");
			return _data[_index / _m][_index % _m];
		}
		bool operator==(MatrixIterator it) { return true; }
		bool operator!=(MatrixIterator it) { return false; }

	};
	ComplexMatrix();
	ComplexMatrix(const ComplexMatrix<T>& matrix);
	ComplexMatrix(std::vector<std::vector<T> > matrix);
	ComplexMatrix<T>& operator=(const ComplexMatrix<T> & matrix);
	ComplexMatrix<T> operator*(const ComplexMatrix<T> & matrix) const;
	ComplexMatrix<T> operator*(const T & num) const;
	friend ComplexMatrix<T> operator*(const T & num, const ComplexMatrix<T> & matrix);
	ComplexMatrix<T> operator+(const ComplexMatrix<T> & matrix) const;
	ComplexMatrix<T> operator|(const ComplexMatrix<T> & matrix);
	ComplexMatrix<T> operator~();
	MatrixIterator begin() { return MatrixIterator(_matrix, _rows, _columns, 0); }
	MatrixIterator end() { return MatrixIterator(_matrix, _rows, _columns, _rows*_columns); }
	
	T operator()(unsigned int npos, unsigned int mpos) const;
	template<class T>
	friend std::ofstream & operator<<(std::ofstream & ofs, ComplexMatrix<T> & matrix)
	{
		for (int i = 0; i < matrix._rows; i++)
		{
			for (int j = 0; j < matrix._columns; j++)
				ofs << matrix._matrix[i][j] << "  ";
			ofs << "\n";
		}
		return ofs;
	}
	~ComplexMatrix();
};

template<class T>
ComplexMatrix<T>::ComplexMatrix()
{
	_matrix = std::vector<std::vector<T> >(0);
	_rows = _columns = 0;
}

template<class T>
ComplexMatrix<T>::ComplexMatrix(const ComplexMatrix<T>& matrix)
{
	_matrix = std::vector<std::vector<T> >(matrix._matrix);
	_rows = matrix._rows;
	_columns = matrix._columns;
}

template<class T>
ComplexMatrix<T>::ComplexMatrix(std::vector<std::vector<T> > matrix)
{
	for (int i = 0; i < matrix.size() - 1; i++)
		if(matrix[i].size() != matrix[i + 1].size())
			throw std::logic_error("Incorrect matrix.");

	_matrix = std::vector<std::vector<T> >(matrix);
	_rows = matrix.size();
	_columns = matrix[0].size();
}

template<class T>
ComplexMatrix<T>& ComplexMatrix<T>::operator=(const ComplexMatrix<T> & matrix)
{
	if (this == &matrix)
		return *this;

	_matrix = std::vector<std::vector<T>>(matrix._matrix);
	_rows = matrix._rows;
	_columns = matrix._columns;
	return *this;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator*(const ComplexMatrix<T> & matrix) const
{
	if (_columns != matrix._rows) 
		throw std::logic_error("Error in multiplication of matrixes.");

	ComplexMatrix<T> result;
	result._matrix = std::vector<std::vector<T> >(_rows);

	for (int i = 0; i < _rows; i++)
		result._matrix[i] = std::vector<T>(matrix._columns);

	result._rows = _rows;
	result._columns = matrix._columns;

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < matrix._columns; j++)
			for (int k = 0; k < _columns; k++)
				result._matrix[i][j] = result._matrix[i][j] + _matrix[i][k] * matrix._matrix[k][j];

	return result;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator*(const T & num) const
{
	ComplexMatrix<T> result(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			result._matrix[i][j] = result._matrix[i][j] * num;

	return result;
}

template<class T>
ComplexMatrix<T> operator*(const T & num, const ComplexMatrix<T> & matrix)
{
	return matrix * num;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator+(const ComplexMatrix<T> & matrix) const
{
	if (_rows != matrix._rows || _columns != matrix._columns)
		throw std::logic_error("Error in addition of matrixes.");

	ComplexMatrix<T> result(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			result._matrix[i][j] = _matrix[i][j] + matrix._matrix[i][j];

	return result;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator|(const ComplexMatrix<T> & matrix)
{
	if (_rows != matrix._rows)
		throw std::logic_error("Error in concatenation of matrixes.");
	ComplexMatrix<T> result;
	result._rows = _rows;
	result._columns = _columns + matrix._columns;
	result._matrix = std::vector<std::vector<T> >(_rows);
	for (int i=0; i<_rows; i++)
		result._matrix[i]=std::vector<T>(result._columns);
	int j;
	for (int i=0; i<_rows; i++)
	{
		for (j = 0; j < _columns; j++)
			result._matrix[i][j] = _matrix[i][j];
		for (int k = 0; k < matrix._columns; k++)
			result._matrix[i][k + j] = matrix._matrix[i][k];
	}	
	return result;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator~()
{
	if (_columns != _rows)
		throw std::logic_error("Error in transportation of matrix.");

	ComplexMatrix<T> result(*this);

	for (int i = 0; i < _columns; i++)
		for (int j = 0; j < i; j++)
		{
			result._matrix[i][j] = _matrix[j][i];
			result._matrix[j][i] = _matrix[i][j];
		}

	return result;
}

template<class T>
T ComplexMatrix<T>::operator()(unsigned int npos, unsigned int mpos) const
{
	if (npos >= _rows || mpos >= _columns)
		throw std::out_of_range("Error: bad index.");

	return _matrix[npos][mpos];
}

template<class T>
ComplexMatrix<T>::~ComplexMatrix()
{
	for (int i = 0; i < _rows; i++)
		_matrix[i].clear();

	_matrix.clear();
}

#endif

