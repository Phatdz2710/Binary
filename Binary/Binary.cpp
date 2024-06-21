#include "Binary.h"
#include "FText.h"
#include <iomanip>

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

void Bin::SimulateManualDivision(Bin bin_1, Bin bin_2)
{
	//Mo phong phep chia bang tay
	cout << fc(F_LIGHT_CYAN) << "==*== SIMULATE MANUAL DIVISION ==*==" << fc::Reset << endl;

	cout << "DEVIDENT: " << fc(F_LIGHT_RED) << bin_1.bin << " (" << bin_1.ToDecimal() << ')' << fc::Reset << endl;
	cout << "DIVISOR: " << fc(F_LIGHT_RED) << bin_2.bin << " (" << bin_2.ToDecimal() << ')' << fc::Reset << endl;

	int k = 8;
	Bin A(0);
	cout << fc(F_GREEN) << "Declare A = 0: " << fc(F_CYAN) << A << fc::Reset << endl;
	cout << fc(F_GREEN) << "Declare Q " << fc(F_YELLOW) << "(If Divident is positive, keep the number as is,\nbut if it is negative, takes the 2's complement.): ";
	Bin Q((bin_1.bin[0] == '0') ? bin_1 : ~(bin_1 - Bin(1)));
	cout << fc(F_CYAN) << Q << fc::Reset << endl;
	Bin M(bin_2);
	cout << fc(F_GREEN) << "Declare M" << fc(F_YELLOW) << " (is Divisor) : " << fc(F_CYAN) << M << fc::Reset << endl;

	Bin temp;
	cout << fc(F_LIGHT_CYAN) << "\nSTART THE LOOP " << fc::Reset << endl;
	cout << fc(F_LIGHT_YELLOW) << setw(15) << left << "A" << setw(15) << left << "Q" << fc::Reset << endl;
	cout << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q << fc::Reset << endl << endl;
	while (k > 0)
	{
		A = A << 1;
		A.bin[7] = Q.bin[0];
		Q = Q << 1;
		temp = A;

		cout << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q << fc(F_LIGHT_GREEN) << setw(15) << left << "Shift" << endl;

		if (A.bin[0] == M.bin[0]) { A = A - M; 
			cout << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q << fc(F_LIGHT_GREEN) << setw(15) << left << "A = A - M" << fc(F_RED) << "(A[0] == M[0])" << endl;
		}
		else {
			A = A + M; 
			cout << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q << fc(F_LIGHT_GREEN) << setw(15) << left << "A = A + M" << fc(F_RED) << "(A[0] != M[0])" << endl;
		}


		if (A.bin[0] == temp.bin[0]) Q.bin[7] = '1';
		else
		{
			Q.bin[7] = '0';
			//restore A
			A = temp;
			cout << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q << fc(F_LIGHT_GREEN) << setw(15) << left << "Restore A"
				<< fc(F_RED) << "bit[0] of A" << fc(F_LIGHT_GREEN) << " isn't the same as " << fc(F_RED) << "bit[0] of previous A" << endl;
		}
		cout << endl;
		k--;
	}

	cout << fc(F_LIGHT_YELLOW) << "--> Q: " << fc(F_LIGHT_BLUE) << Q << endl;
	cout << fc(F_LIGHT_YELLOW) << "--> A: " << fc(F_LIGHT_BLUE) << A << endl;

	cout << fc(F_YELLOW) << "If sign of divident is the same as the divisor, then keep it is as,\notherwise take the two's complement of Q." << endl;

	if (bin_1[0] != bin_2[0])
	{
		cout << fc(F_LIGHT_CYAN) << "\nQUOTIENT: " << ~Q + Bin(1) << " (" << (~Q + Bin(1)).ToDecimal() << ')' << endl;
	}
	else
		cout << fc(F_LIGHT_CYAN) << "\nQUOTIENT: " << Q << " (" << Q.ToDecimal() << ')' << endl;

	cout << fc(F_LIGHT_RED) << "REMAINDER: " << A << " (" << A.ToDecimal() << ')' << fc::Reset << endl;

	cout << fc::Reset << endl;
}

void Bin::SimulateManualMultiplication(Bin bin_1, Bin bin_2)
{
	cout << fc(F_LIGHT_CYAN) << "==*== SIMULATE MANUAL MULTIPLICATION ==*==" << fc::Reset << endl;

	cout << "FACTOR 1: " << fc(F_LIGHT_RED) << bin_1.bin << " (" << bin_1.ToDecimal() << ')' << fc::Reset << endl;
	cout << "FACTOR 2: " << fc(F_LIGHT_RED) << bin_2.bin << " (" << bin_2.ToDecimal() << ')' << fc::Reset << endl;
	int k = 8;
	char Qs = '0';
	cout << fc(F_GREEN) << "Declare Qs: " << fc(F_CYAN) << "0" << endl;
	Bin A(0);
	cout << fc(F_GREEN) << "Declare A = 0: " << fc(F_CYAN) << A << fc::Reset << endl;
	Bin Q(bin_1);
	cout << fc(F_GREEN) << "Declare Q = Factor 1: " << fc(F_CYAN) << Q << fc::Reset << endl;
	cout << fc(F_GREEN) << "Declare M = Factor 2: " << fc(F_CYAN) << bin_2 << fc::Reset << endl;
	Bin temp(bin_2);

	cout << fc(F_LIGHT_CYAN) << "\nSTART THE LOOP " << fc::Reset << endl;

	cout << "A = A - M if Q0-Qs = 01 or Q0-Qs = 10" << endl;

	cout << fc(F_LIGHT_YELLOW) << setw(5) << left << "k" << setw(15)
		<< left << "Operation" << setw(15) << left << "A" << setw(15) << left << "Q" <<
		setw(15) << left << "Qs" << setw(15) << left << "M" << fc::Reset << endl;

	cout << setw(5) << left << ' ' << setw(15)
		<< left << fc(F_LIGHT_RED) << "Initialize" << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q <<
		setw(15) << left << Qs << setw(15) << left << temp << fc::Reset << endl;

	while (k > 0)
	{
		if (Q.bin[7] == '1' && Qs == '0')
		{
			A = A - temp;
			cout << fc(F_LIGHT_GREEN) << setw(5) << left << k << setw(15)
				<< left << fc(F_LIGHT_PURPLE) << "A = A - M" << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q <<
				setw(15) << left << Qs << setw(15) << left << temp << fc::Reset << endl;
		}
		else if (Q.bin[7] == '0' && Qs == '1')
		{
			A = A + temp;
			cout << fc(F_LIGHT_GREEN) << setw(5) << left << k << setw(15)
				<< left << fc(F_LIGHT_PURPLE) << "A = A + M" << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q <<
				setw(15) << left << Qs << setw(15) << left << temp << fc::Reset << endl;
		}

		Qs = Q.bin[7];
		Q = Q >> 1;
		Q.bin[0] = A.bin[7];
		A = A >> 1;
		

		cout << fc(F_LIGHT_GREEN) << setw(5) << left << k << setw(15)
			<< left << fc(F_LIGHT_PURPLE) << "SAR" << fc(F_LIGHT_BLUE) << setw(15) << left << A << setw(15) << left << Q <<
			setw(15) << left << Qs << setw(15) << left << temp << fc::Reset << endl;
		k--;
	}

	cout << fc(F_LIGHT_CYAN) << "\nRESULT: " << Q << " (" << Q.ToDecimal() << ')' << endl;
}

void Bin::SimulateManualAddition(Bin bin_1, Bin bin_2)
{
	int sd = 0;
	char* result = new char[9] {"00000000"};
	bool ts = false;

	cout << fc(F_LIGHT_CYAN) << "==*== SIMULATE MANUAL ADDITION ==*==" << fc::Reset << endl;
	cout << "TERM 1: " << fc(F_LIGHT_RED) << bin_1.bin << " (" << bin_1.ToDecimal() << ')' << fc::Reset << endl;
	cout << "TERM 2: " << fc(F_LIGHT_RED) << bin_2.bin << " (" << bin_2.ToDecimal() << ')' << fc::Reset << endl;
	cout << fc(F_LIGHT_YELLOW) << setw(15) << left << "A" << setw(15) << left << "B" << setw(15) << left << "Cin" << setw(15) << left << "Sum" << setw(15) << left << "Cout" << fc::Reset << endl;
	for (int i = 7; i >= 0; i--)
	{
		//cout << fc(F_LIGHT_BLUE) << setw(15) << left << bin_1 << setw(15) << left << bin_2 << setw(15) << left << sd << setw(15) << left << result << setw(15) << left << i << fc::Reset << endl;
		if (bin_1.bin[i] == '1' && bin_2.bin[i] == '1')
		{
			result[i] = (sd == 1) ? '1' : '0';
			sd = 1;
		}
		else if (bin_1.bin[i] == '0' && bin_2.bin[i] == '0')
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
		cout << fc(F_LIGHT_BLUE) << setw(15) << left << bin_1[0] << setw(15) << left << bin_2[0] << setw(15) << left << sd << setw(15) << left << result << setw(15) << left << i << fc::Reset << endl;
	}

	cout << fc(F_LIGHT_CYAN) << "\nRESULT: " << Bin(result) << " (" << Bin(result).ToDecimal() << ')' << endl << fc::Reset;
	delete[] result;
}

void Bin::SimulateManualSubtraction(Bin bin_1, Bin bin_2)
{
	int sd = 0;
	char* result = new char[9] {"00000000"};

	cout << fc(F_LIGHT_CYAN) << "==*== SIMULATE MANUAL SUBSTRACTION ==*==" << fc::Reset << endl;
	cout << "Convert to 2's complement of the second number, then add two numbers." << endl;
	cout << "TERM 1: " << fc(F_LIGHT_RED) << bin_1.bin << " (" << bin_1.ToDecimal() << ')' << fc::Reset << endl;
	cout << "TERM 2: " << fc(F_LIGHT_RED) << ~bin_2 + Bin(1) << " (" << bin_2.ToDecimal() << ')' << fc::Reset << endl;
	bin_2 = ~bin_2 + Bin(1);
	cout << fc(F_LIGHT_YELLOW) << setw(15) << left << "A" << setw(15) << left << "B" << setw(15) << left << "Cin" << setw(15) << left << "Sum" << setw(15) << left << "Cout" << fc::Reset << endl;
	for (int i = 7; i >= 0; i--)
	{
		//cout << fc(F_LIGHT_BLUE) << setw(15) << left << bin_1 << setw(15) << left << bin_2 << setw(15) << left << sd << setw(15) << left << result << setw(15) << left << i << fc::Reset << endl;
		if (bin_1.bin[i] == '1' && bin_2.bin[i] == '1')
		{
			result[i] = (sd == 1) ? '1' : '0';
			sd = 1;
		}
		else if (bin_1.bin[i] == '0' && bin_2.bin[i] == '0')
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
		cout << fc(F_LIGHT_BLUE) << setw(15) << left << bin_1[0] << setw(15) << left << bin_2[0] << setw(15) << left << sd << setw(15) << left << result << setw(15) << left << i << fc::Reset << endl;
	}

	cout << fc(F_LIGHT_CYAN) << "\nRESULT: " << Bin(result) << " (" << Bin(result).ToDecimal() << ')' << endl << fc::Reset;
	delete[] result;
}
#pragma endregion


