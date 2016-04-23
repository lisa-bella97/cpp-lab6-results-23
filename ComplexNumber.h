#ifndef _COMPLEXNUMBER_H_
#define _COMPLEXNUMBER_H_

#include <fstream>
#include <string>
#include <vector>

class ComplexNumber
{
private:
	double _real; 
	double _imaginary; 
public:
	ComplexNumber() : _real(0.0), _imaginary(0.0) { }
	ComplexNumber(double r, double im) : _real(r), _imaginary(im) { }
	ComplexNumber(const ComplexNumber& num) : _real(num._real), _imaginary(num._imaginary) { }
	static std::vector<ComplexNumber> GetNumbersFromString(std::string source); 
	ComplexNumber& operator=(const ComplexNumber & number);
	ComplexNumber operator+(const ComplexNumber & number) const;
	ComplexNumber operator*(const ComplexNumber & number) const;
	ComplexNumber operator*(double x) const;
	friend ComplexNumber operator*(double x, const ComplexNumber & number);
	friend std::ofstream & operator<<(std::ofstream & ofs, const ComplexNumber & number);
	friend std::ifstream & operator>>(std::ifstream & ifs, ComplexNumber & number);
};

/* Parsing Functions */
double BeforePlus(std::string str, int pos); 
double AfterPlus(std::string str, int pos);
void BetweenNumbers(std::string str, int pos); 
char ChangeSymbol(char& symbol);

std::vector<ComplexNumber> ComplexNumber::GetNumbersFromString(std::string source)
{
	char nextSymbol = '(';
	std::vector<ComplexNumber> nums;
	ComplexNumber* number = new ComplexNumber();
	for (int i = 0; i < source.size(); i++)
	{
		if (source[i] == nextSymbol)
		{
			switch (ChangeSymbol(nextSymbol))
			{
			case ')':
				number->_imaginary = AfterPlus(source, i + 1);
				nums.push_back(*number);
				number = new ComplexNumber();
				break;
			case '+':
				number->_real = BeforePlus(source, i + 1);
				break;
			case '(':
				BetweenNumbers(source, i + 1);
				break;
			}
		}
	}
	return nums;
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber & number)
{
	if (this == &number)
		return *this;
	_real = number._real;
	_imaginary = number._imaginary;
	return *this;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber & number) const
{
	return ComplexNumber(_real + number._real, _imaginary + number._imaginary);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber & number) const
{
	return ComplexNumber(_real * number._real - _imaginary * number._imaginary, _real * number._imaginary + number._real * _imaginary);
}

ComplexNumber ComplexNumber::operator*(double x) const
{
	return ComplexNumber(x * _real, x * _imaginary);
}

ComplexNumber operator*(double x, const ComplexNumber & number)
{
	return number*x;
}

std::ofstream & operator<<(std::ofstream & ofs, const ComplexNumber & number)
{
	ofs << "(" << number._real << " + " << number._imaginary << "i)";
	return ofs;
}

std::ifstream & operator>>(std::ifstream & ifs, ComplexNumber & number)
{
	char nextSymbol = '(';
	std::string str;
	while (getline(ifs, str))
	{
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == nextSymbol)
			{
				switch (ChangeSymbol(nextSymbol))
				{
				case ')':
					number._imaginary = AfterPlus(str, i + 1);
					return ifs;
				case '+':
					number._real = BeforePlus(str, i + 1);
					break;
				case '(':
					break;
				}
			}
		}
	}
	return ifs;
}

double BeforePlus(std::string str, int pos)
{
	int k = pos;
	while (str[pos] != '+')
		pos++;
	char* substr = new char[pos - k + 1];
	for (int i = 0; i < pos - k; i++)
		substr[i] = str[i + k];
	substr[pos - k] = '\0';
	char* ptrEnd;
	double res = strtod(substr, &ptrEnd);
	for (int i = 0; i < strlen(ptrEnd); i++)
		if (ptrEnd[i] != '\0' && ptrEnd[i] != ' ')
			throw "Incorrect real part in number";
	delete[] substr;
	return res;
}

double AfterPlus(std::string str, int pos)
{
	int k = pos;
	while (str[pos] != ')')
		pos++;
	char* substr = new char[pos - k + 1];
	for (int i = 0; i < pos - k; i++)
		substr[i] = str[i + k];
	substr[pos - k] = '\0';
	char* ptrEnd;
	double res = strtod(substr, &ptrEnd);
	bool flag = false; 
	for (int i = 0; i < strlen(ptrEnd); i++)
	{
		if (ptrEnd[i] == 'i')
			flag = true;
		else if ((ptrEnd[i] != '\0' || ptrEnd[i] != ' ') && !flag)
			throw "Incorrect imaginary part in number";
	}
	delete[] substr;
	return res;
}

void BetweenNumbers(std::string str, int pos)
{
	for (int i = pos; i < str.size() && str[i] != '('; i++)
		if (str[i] != ' ')
			throw "Incorrect symbol between numbers";
}

char ChangeSymbol(char& symbol)
{
	switch (symbol)
	{
	case '(': symbol = '+'; break;
	case '+': symbol = ')'; break;
	case ')': symbol = '('; break;
	}
	return symbol;
}

#endif
