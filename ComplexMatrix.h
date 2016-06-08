#ifndef _COMPLEXMATRIX_H_
#define _COMPLEXMATRIX_H_

#include <iostream>
#include <fstream>

template<class T>
class ComplexMatrix
{
private:
	T** _matrix;
	size_t _rows;
	size_t _columns;
	T _zero;
public:
	class MatrixIterator : public std::iterator<std::input_iterator_tag, T>
	{
	private:
		T** _data;
		size_t _n;
		size_t _m;
		size_t _index;
	public:
		MatrixIterator(T** data, size_t n, size_t m, size_t index) : _data(data), _n(n), _m(m), _index(index) { }
		MatrixIterator(const MatrixIterator& it) : _data(it._data), _n(it._n), _m(it._m), _index(it._index) { }
		MatrixIterator& operator++() { ++_index; return *this; }
		MatrixIterator& operator++(int) { _index++; return *this; }
		MatrixIterator& operator+(size_t ind)
		{
			_index += ind;
			return *this;
		}
		T& operator*() const
		{
			if (_index >= _n*_m)
				throw std::out_of_range("Out of range");
			return _data[_index / _m][_index % _m];
		}
		bool operator==(const MatrixIterator& it) const { return _index == it._index; }
		bool operator!=(const MatrixIterator& it) const { return _index != it._index; }
	};

	ComplexMatrix();
	ComplexMatrix(const ComplexMatrix<T>& matrix);
	ComplexMatrix(T** matrix, size_t rows, size_t columns);
	ComplexMatrix(size_t rows, size_t columns, T filler);
	template <class U>
	ComplexMatrix(const ComplexMatrix<U>& matrix);
	void setZero(T zero) { _zero = zero; }
	size_t getRows() const { return _rows; }
	size_t getColumns() const { return _columns; }
	T** getMatrix() const { return _matrix; }
	ComplexMatrix<T>& operator=(const ComplexMatrix<T> & matrix);
	ComplexMatrix<T> operator*(const ComplexMatrix<T> & matrix) const;
	ComplexMatrix<T> operator*(T num) const;
	friend ComplexMatrix<T> operator*(const T & num, const ComplexMatrix<T> & matrix);
	ComplexMatrix<T> operator+(const ComplexMatrix<T> & matrix) const;
	ComplexMatrix<T> operator|(const ComplexMatrix<T> & matrix) const;
	ComplexMatrix<T> operator~() const;
	MatrixIterator begin() { return MatrixIterator(_matrix, _rows, _columns, 0); }
	MatrixIterator end() { return MatrixIterator(_matrix, _rows, _columns, _rows*_columns); }
	T operator()(size_t npos, size_t mpos) const;
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
	friend std::ostream & operator<<(std::ostream & os, ComplexMatrix<T> & matrix)
	{
		for (int i = 0; i < matrix._rows; i++)
		{
			for (int j = 0; j < matrix._columns; j++)
				os << matrix._matrix[i][j] << "  ";
			os << "\n";
		}
		return os;
	}
	~ComplexMatrix();
};

template<class T>
ComplexMatrix<T>::ComplexMatrix()
{
	 _matrix = _rows = _columns = 0;
}

template<class T>
ComplexMatrix<T>::ComplexMatrix(const ComplexMatrix<T>& matrix)
{
	_matrix = new T*[matrix._rows];
	for (int i = 0; i < matrix._rows; i++)
		_matrix[i] = new T[matrix._columns];
	_rows = matrix._rows;
	_columns = matrix._columns;
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			_matrix[i][j] = matrix._matrix[i][j];
}

template<class T>
ComplexMatrix<T>::ComplexMatrix(T** matrix, size_t rows, size_t columns)
{
	_matrix = new T*[rows];
	for (int i = 0; i < rows; i++)
		_matrix[i] = new T[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			_matrix[i][j] = matrix[i][j];
	_rows = rows;
	_columns = columns;
}

template<class T>
ComplexMatrix<T>::ComplexMatrix(size_t rows, size_t columns, T filler)
{
	_matrix = new T*[rows];
	for (int i = 0; i < rows; i++)
		_matrix[i] = new T[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			_matrix[i][j] = filler;
	_rows = rows;
	_columns = columns;
}

template <class T>
template <class U>
ComplexMatrix<T>::ComplexMatrix(const ComplexMatrix<U>& matrix)
{
	_matrix = new T*[matrix.getRows()];
	for (int i = 0; i < matrix.getRows(); i++)
		_matrix[i] = new T[matrix.getColumns()];
	_rows = matrix.getRows();
	_columns = matrix.getColumns();
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			_matrix[i][j] = static_cast<T>(matrix.getMatrix()[i][j]);
}

template<class T>
ComplexMatrix<T>& ComplexMatrix<T>::operator=(const ComplexMatrix<T> & matrix)
{
	if (this == &matrix)
		return *this;

	_matrix = new T*[matrix._rows];
	for (int i = 0; i < matrix._rows; i++)
		_matrix[i] = new T[matrix._columns];
	_rows = matrix._rows;
	_columns = matrix._columns;
	
	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			_matrix[i][j] = matrix._matrix[i][j];
	return *this;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator*(const ComplexMatrix<T> & matrix) const
{
	if (_columns != matrix._rows)
		throw std::logic_error("Error in multiplication of matrixes.");

	ComplexMatrix<T> result(_rows, matrix._columns, _zero);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < matrix._columns; j++)
			for (int k = 0; k < _columns; k++)
				result._matrix[i][j] = result._matrix[i][j] + _matrix[i][k] * matrix._matrix[k][j];

	return result;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator*(T num) const
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
ComplexMatrix<T> ComplexMatrix<T>::operator|(const ComplexMatrix<T> & matrix) const
{
	if (_rows != matrix._rows)
		throw std::logic_error("Error in concatenation of matrixes.");
	ComplexMatrix<T> result(_rows, _columns + matrix._columns, _zero);
	int j;
	for (int i = 0; i < _rows; i++)
	{
		for (j = 0; j < _columns; j++)
			result._matrix[i][j] = _matrix[i][j];
		for (int k = 0; k < matrix._columns; k++)
			result._matrix[i][k + j] = matrix._matrix[i][k];
	}
	return result;
}

template<class T>
ComplexMatrix<T> ComplexMatrix<T>::operator~() const
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
T ComplexMatrix<T>::operator()(size_t npos, size_t mpos) const
{
	if (npos >= _rows || mpos >= _columns)
		throw std::out_of_range("Error: bad index.");

	return _matrix[npos][mpos];
}

template<class T>
ComplexMatrix<T>::~ComplexMatrix()
{
	for (int i = 0; i < _rows; i++)
		delete [] _matrix[i];
	delete [] _matrix;
}

#endif
