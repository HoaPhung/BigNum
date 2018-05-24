#ifndef _BinaryBignum_
#define _BinaryBigNum_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define MAX_BYTE 16
#define MAX_BIT 128

class QInt
{
protected:
	int data[4];
public:
	//Constructor
	QInt();
	QInt(int);
	QInt(const QInt&);

	//Get, Set
	void setBit(int, int);
	bool getBit(int);

	// (a) QInt_ConvertTo_Output
	string print(int);
	string QIntToBin();
	string QIntToHex();
	string QIntToDec();

	// (b) Input_ConvertTo_QInt
	void scan(string, int);
	void BinToQInt(string);
	void DecToQInt(string);
	void DecToQInt_NoS(string);
	void HexToQInt(string);

	// (c) Toan tu: =, +, -, *, /
	QInt& operator=(const QInt&);
	QInt operator+(QInt);
	QInt operator-(QInt);
	QInt operator*(QInt);
	QInt operator/(QInt);

	// (d) Toan tu AND, OR, XOR, NOT
	void Bu2();
	QInt AND(QInt);
	QInt OR(QInt);
	QInt XOR(QInt);
	void NOT();

	// (e) Toan <<, >>
	void SHL();
	void SHR();

	// (f) ROR, ROL
	void ROR();
	void ROL();

	//cout, cin
	friend istream& operator>>(istream&, QInt&);
	friend ostream& operator<<(ostream&, QInt&);
};
string Add(string a, string b);
string Multi2(string a);
void Surface(char a[], char b[]);
#endif