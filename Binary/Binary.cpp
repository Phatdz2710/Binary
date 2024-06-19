#include "Binary.h"

#pragma region BIN
Bin::Bin() : bin(nullptr)
{
	bin = new char[9] {"00000000"};
}

Bin::Bin(const char* _bin) : bin(nullptr)
{
	char* a = new char[9] {"00000000"};
	int index = 0;
	int k = (int)(strlen(_bin) - 1);
	for (int i = 0; i <= k; i++)
	{
		if (_bin[k - i] == '1')
		{
			a[7 - index] = '1';
			index++;
		}
		else if (_bin[k - i] == '0' || (_bin[k - i] != '0' && _bin[k - i] != '1' && _bin[k - i] != ' ')) index++;
	}
	a[8] = '\0';
	bin = new char[9];
	for (int i = 0; i < 9; i++)
	{
		bin[i] = a[i];
	}

	delete[] a;
}

Bin::Bin(const Bin& _bin) : bin(nullptr)
{
	bin = new char[9];
	strcpy_s(bin, 9, _bin.bin);
}

Bin::Bin(const std::string& _bin) : Bin(_bin.c_str()) {}

Bin::Bin(const int& _dec) : bin(nullptr)
{
	bin = new char[9] {"00000000"};
	int dec = _dec;
	int i = 0;
	while (i < 8)
	{
		bin[7 - i] = ((dec >> i) & 1) + '0';
		i++;
	}
	bin[8] = '\0';
}

Bin::~Bin()
{
	delete[] bin;
}

ostream& operator<<(ostream& os, const Bin& _bin)
{
	os << _bin.bin;
	return os;
}
istream& operator>>(istream& is, Bin& _bin)
{
	char* temp = new char[9];
	is >> temp;
	_bin = Bin(temp);
	delete[] temp;
	return is;
}

char& Bin::operator[](const int& index) const
{
	return bin[index];
}

Bin Bin::operator~()
{
	char* result = new char[9] {"00000000"};
	strcpy_s(result, 9, bin);
	for (int i = 0; i < 8; i++)
	{
		result[i] = (result[i] == '0') ? '1' : '0';
	}
	
	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator&(const Bin& other)
{
	char* result = new char[9] {"00000000"};
	for (int i = 0; i < 8; i++)
	{
		if (bin[i] == '1' && other.bin[i] == '1') result[i] = '1';
	}

	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator|(const Bin& other)
{
	char* result = new char[9] {"00000000"};
	for (int i = 0; i < 8; i++)
	{
		if (bin[i] == '1' || other.bin[i] == '1') result[i] = '1';
	}

	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator^(const Bin& other)
{
	char* result = new char[9] {"00000000"};
	for (int i = 0; i < 8; i++)
	{
		if (bin[i] == '1' && other.bin[i] == '0' || bin[i] == '0' && other.bin[i] == '1') result[i] = '1';
	}

	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator<<(const int& n)
{
	if (n < 0) return *this >> -n;

	int _n = n % 8;
	char* result = new char[9] {"00000000"};
	for (int i = 0; i < 8 - _n; i++)
	{
		result[i] = bin[i + _n];
	}
	for (int i = 8 - _n; i < 8; i++)
	{
		result[i] = '0';
	}

	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator>>(const int& n)
{
	if (n < 0) return *this << -n;

	int _n = n % 8;
	char* result = new char[9] {"00000000"};
	for (int i = 0; i < 8 - _n; i++)
	{
		result[i + _n] = bin[i];
	}
	for (int i = 0; i < _n; i++)
	{
		result[i] = '0';
	}

	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator+(const Bin& other)
{
	int sd = 0;
	char* result = new char[9] {"00000000"};
	bool ts = false;

	for (int i = 7; i >= 0; i--)
	{
		if (bin[i] == '1' && other.bin[i] == '1')
		{
			result[i] = (sd == 1) ? '1' : '0';
			sd = 1;
		}
		else if (bin[i] == '0' && other.bin[i] == '0')
		{
			result[i] = (sd == 1) ? '1' : '0';
			sd = 0;
		}
		else
		{
			result[i] = (sd == 1) ? '0' : '1';
			if (result[i] == '1') sd = 0;
			else sd = 1;
		}

	}

	Bin res(result);
	delete[] result;
	return res;
}

Bin Bin::operator-(const Bin& other)
{
	Bin temp(other);
	return (*this) + (~temp + Bin(1));
}

//Booth's algorithm
Bin Bin::operator*(const Bin& other)
{
	int k = 8;
	char Qs = '0';
	Bin A(0);
	Bin Q(*this);

	Bin temp(other);

	while (k > 0)
	{
		if (Q.bin[7] == '1' && Qs == '0')
		{
			A = A - temp;
		}
		else if (Q.bin[7] == '0' && Qs == '1')
		{
			A = A + temp;
		}

		Qs = Q.bin[7];
		Q = Q >> 1;
		Q.bin[0] = A.bin[7];
		A = A >> 1;
		k--;
	}

	return Q;
}

Bin Bin::operator/(const Bin& other)
{
	int k = 8;
	Bin A(0);
	Bin Q((bin[0] == '0') ? (*this) : ~((*this) - Bin(1)));
	Bin M(other);

	Bin temp;

	while (k > 0)
	{
		A = A << 1;
		A.bin[7] = Q.bin[0];
		Q = Q << 1;
		temp = A;

		if (A.bin[0] == M.bin[0]) A = A - M;
		else A = A + M;

		if (A.bin[0] == temp.bin[0]) Q.bin[7] = '1';
		else
		{
			Q.bin[7] = '0';
			//restore A
			A = temp;
		}
		k--;
	}

	if ((*this)[0] != other[0])
	{
		return ~Q + Bin(1);
	}

	return Q;
}

Bin& Bin::operator=(const Bin& other)
{
	if (this == &other) return *this;

	delete[] bin;
	bin = new char[9];
	strcpy_s(bin, 9, other.bin);
	return *this;
}

int Bin::ToDecimal() const
{
	int result = (bin[0] == '0') ? 0 : -1;

	for (int i = 1; i < 8; i++)
	{
		result = result << 1;
		result |= (bin[i] == '0') ? 0 : 1;
	}

	return result;
}


#pragma endregion


