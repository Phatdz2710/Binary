#pragma once
#include <iostream>
using namespace std;

class Bin
{
protected:
	char* bin;

	//void TwoComplement();
public:
	Bin();
	Bin(const char* _bin);
	Bin(const Bin& other);
	Bin(const string& _bin);
	Bin(const int& _dec); 
	~Bin();

	virtual int ToDecimal() const;

	// Override
	Bin operator+(const Bin& other);
	Bin operator-(const Bin& other);
	Bin operator*(const Bin& other);
	Bin operator/(const Bin& other);
	Bin operator<<(const int& n);
	Bin operator>>(const int& n);
	Bin operator&(const Bin& other);
	Bin operator|(const Bin& other);
	Bin operator^(const Bin& other);
	Bin operator~();

	Bin& operator=(const Bin& other);
	char& operator[](const int& index) const;
	
	friend istream& operator>>(istream& in, Bin& _bin);
	friend ostream& operator<<(ostream& out, const Bin& _bin);

	static void SimulateManualDivision(Bin, Bin);
	static void SimulateManualMultiplication(Bin, Bin);
	static void SimulateManualAddition(Bin, Bin);
	static void SimulateManualSubtraction(Bin, Bin);
	//void AND(const Bin& other);
	//void OR(const Bin& other);
	//void XOR(const Bin& other);
	//void NOT();

};
