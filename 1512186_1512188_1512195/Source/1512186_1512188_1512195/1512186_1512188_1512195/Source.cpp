#include "Header.h"

//Surface
void QInt::scan(string operant, int input_kind){
	if (input_kind == 2)
		this->BinToQInt(operant);    //he 2 sang QInt
	else if (input_kind == 10)
		this->DecToQInt(operant);	 //he 10 sang QInt
	else
		this->HexToQInt(operant);	 //he 16 sang QInt
}
string QInt::print(int output_kind){
	if (output_kind == 2)
		return this->QIntToBin();     //QInt sang he 2
	else if (output_kind == 10)
		return this->QIntToDec();	  //QInt sang he 10
	else
		return this->QIntToHex();     //QInt sang he 16
}
void Surface(char a[], char b[]){
	fstream in;
	in.open(a, ios_base::in);
	fstream out;
	out.open(b, ios_base::out);
	while (!in.eof())
	{
		int i = 0;
		int count = 1;  //Bien dem phan tu
		QInt operant1, operant2, result;
		string line, a1, a2, a3, a4;
		getline(in, line);
		for (int j = 0; j < line.size(); j++)    //KT xem line do co bao nhieu phan tu
		{
			if (line[j] == ' ')
				count++;
		}
		while (line[i] != ' ')          // Get a1
		{
			a1 += line[i];
			i++;
		}
		i++;
		while (line[i] != ' ')          // Get a2
		{
			a2 += line[i];
			i++;
		}
		i++;
		while (i != line.size() && line[i] != ' ')     // Get a3
		{
			a3 += line[i];
			i++;
		}
		if (count == 4)    //Neu line co 4 phan tu thi get a4
		{
			i++;
			while (i != line.size())
			{
				a4 += line[i];
				i++;
			}
		}

		int input_kind = 0, output_kind = 0;

		if (count == 3)         //Xet truong hop line co 3 phan tu
		{
			input_kind = stoi(a1);            //a1 va a3 chac chac la input_kind va operant
			operant1.scan(a3, input_kind);
			if (a2[0] == '~' || a2[0] == 'r')  //Neu la NOT va ror/rol thi input_kind = output_kind = stoi(a1);
			{
				output_kind = stoi(a1);
				if (a2[0] == '~')
				{
					operant1.NOT();
				}
				else
				{
					if (a2[2] == 'l')
						operant1.ROL();
					else
						operant1.ROR();
				}
			}
			else
			{
				output_kind = stoi(a2);    //Neu la ham chuyen doi chi can return la he can xet
			}
			result = operant1;
		}
		else     //TrH 4 phan tu
		{
			input_kind = output_kind = stoi(a1);   //input va output giong nhau
			operant1.scan(a2, input_kind);
			if (a3[0] == '>' || a3[0] == '<')      //Neu la cac ham SHL va SHR thi a4 phai la so lam Shift
			{
				int number = stoi(a4);
				if (a3[0] == '>')
				{
					for (int i = 0; i < number; i++)
					{
						operant1.SHR();
					}
				}
				else
				{
					for (int i = 0; i < number; i++)
					{
						operant1.SHL();
					}
				}
				result = operant1;
			}
			else       // Neu la cac thuat toan khac thi a4 la operant
			{
				operant2.scan(a4, input_kind);
				switch (a3[0])
				{
				case '+': result = operant1 + operant2; break;
				case '-': result = operant1 - operant2; break;
				case '*': result = operant1 * operant2; break;
				case '/': result = operant1 / operant2; break;
				case '&': result = operant1.AND(operant2); break;
				case '|': result = operant1.OR(operant2); break;
				case '^': result = operant1.XOR(operant2); break;
				}
			}
		}
		out << result.print(output_kind) << endl;   //Xuat ra file voi output_kind
	}
	in.close();
	out.close();
}

//Bonus
int kt0(string a){
	int length = a.size();
	int i = 0;
	a.push_back('-1');
	for (i;; i++){
		if (a[i] != '0')
			break;
	}
	if (i + 1 > length)
		return 1;
	return 0;
}
void QInt::Bu2(){
	this->NOT();
	QInt result;
	result.setBit(1, 0);
	*this = *this + result;
}

//Construct, destruct
QInt::QInt(){
	for (int i = 0; i < MAX_BYTE / 4; i++)
		this->data[i] = 0;
}
QInt::QInt(int a){
	for (int i = 0; i < 4; i++)
		this->data[i] = -1;
}
QInt::QInt(const QInt& p){
	if (p.data == NULL)
		*this->data = NULL;
	else
		for (int i = 0; i < MAX_BYTE / 4; i++)
			this->data[i] = p.data[i];
}

istream& operator>>(istream& is, QInt& p){
	string a, b;
	cout << "Nhap so: ";
	cin >> a;
	for (int i = 0; i < a.size(); i++){
		b.push_back(a[i]);
	}
	p.BinToQInt(b);
	return is;
}
ostream& operator<<(ostream& os, QInt& p){
	cout << "Result: " << endl;
	cout << "Bin: ";
	cout << p.QIntToBin();
	cout << endl;

	cout << "Dec: " << p.QIntToDec() << endl;

	cout << "Hex: ";
	cout << p.QIntToHex();
	cout << endl;
	return os;
}

//Get_Set
void QInt::setBit(int bit, int i){
	int j = MAX_BYTE / 4 - 1 - i / 32;
	if (bit == 1)
		this->data[j] |= 1 << (i % 32);
	else
		this->data[j] &= ~(1 << i % 32);
}
bool QInt::getBit(int i){
	int bit;
	QInt tmp;
	tmp = *this;
	int j = MAX_BYTE / 4 - 1 - i / 32;
	bit = (tmp.data[j] >> (i % 32)) & 1;
	return bit;
}

//Convert_Output
string QInt::QIntToBin(){
	int i = MAX_BIT - 1;
	for (i; i >= 1; i--){
		if (this->getBit(i) == 1)
			break;
	}
	string result;
	for (i; i >= 0; i--)
		result.push_back(this->getBit(i) + '0');
	return result;
}
string QInt::QIntToHex(){
	int val = 0, p = 1;
	int i = MAX_BYTE * 2 - 1;
	for (i; i >= 1; i--){
		for (int j = 0; j < 4; j++, p *= 2){
			val += this->getBit(i * 4 + j)*p;
		}
		p = 1;
		if (val > 0)
		{
			val = 0;
			break;
		}

	}
	string result;
	for (i; i >= 0; i--){
		for (int j = 0; j < 4; j++, p *= 2){
			val += this->getBit(i * 4 + j)*p;
		}
		if (val < 10)
			result.push_back(val + '0');
		else
			result.push_back('A' + val % 10);
		val = 0;
		p = 1;
	}
	return result;
}
string QInt::QIntToDec(){
	string result = "0";
	int i;
	int dau = 1;
	if (this->getBit(127) == 1)  //KT xem this co phai la so am hay khong
	{
		this->Bu2();			 //Bu 2
		dau = -1;
	}
	for (i = MAX_BIT - 1; i >= 0; i--){   // Quet chuoi bit den khi gap so 1 dau tien
		if (this->getBit(i) == 1)
			break;
	}
	for (i; i >= 0; i--)
	{
		if (this->getBit(i) == 1)                 
			result = Add("1", Multi2(result));		//result = result*2 + bit
		else
			result = Add("0", Multi2(result));
	}
	if (dau == -1)
	{
		result = '-' + result;   //Neu la so am thi them dau - vao result
		this->Bu2();
	}
	return result;
}

//Convert_Input
void QInt::BinToQInt(string bit){
	for (int i = 0; i < bit.size(); i++){
		this->setBit(bit[i] - 48, bit.size() - 1 - i);     //Do mang string luu tu 0 -> n con bit luu tu n -> 0 nen set ngc lai
	}
}
void QInt::DecToQInt(string a){
	if (a[0] != '-')
		this->DecToQInt_NoS(a);  // neu this la so khong am
	else{
		a.erase(a.begin());      // Bo dau '-' roi chuyen thanh QInt nhu so khong dau
		this->DecToQInt_NoS(a);
		this->Bu2();             // Bu 2
	}
}
void QInt::DecToQInt_NoS(string a){
	string b;
	bool tmp_Binary[128];
	int j = 0, tmp = 0, Q = 0, a1 = 0, a2 = 0, du = 0, i = 0;
	if (kt0(a) == 1)
		return;
	else
		while (kt0(a) == 0){
			Q = a[a.size() - 1] - 48;
			if (Q % 2 == 0)
				tmp_Binary[i] = 0;
			else
			{
				a[a.size() - 1]--;
				tmp_Binary[i] = 1;
			}
			while (j < a.size()){
				if (du == 1)
					tmp = (a[j - 1] - 48) * 10 + a[j] - 48;
				else
					tmp = a[j] - 48;
				if (tmp % 2 == 1)
					du = 1;
				a[j] = tmp % 2 + 48;
				tmp = tmp / 2;
				b.push_back(tmp + 48);
				j++;
			}
			a = b;
			b.clear();
			j = 0;
			i++;
			du = 0;
		}
	i = i - 1;
	for (i; i >= 0; i--)
		this->setBit(tmp_Binary[i], i);
}
void QInt::HexToQInt(string a){
	int bit = 0;
	for (int i = a.size() - 1; i >= 0; i--){
		if (a[i] >= '0' && a[i] <= '9')
			a[i] -= '0';
		else
			a[i] = a[i] - 'A' + 10;
		for (int j = 0; j < 4; j++, a[i] /= 2){    // xxxx he 2 = X he 16
			bit = a[i] % 2;
			this->setBit(bit, (a.size() - 1 - i) * 4 + j);
		}
	}
}

//Operator =, +, - , *, /
QInt& QInt::operator=(const QInt& p){
	if (this == &p)
		return *this;
	else
		for (int i = 0; i < MAX_BYTE / 4; i++)
			this->data[i] = p.data[i];
	return *this;
}
QInt QInt::operator+(QInt p){
	int length = MAX_BIT;
	int a0 = 0, b0 = 0, sum = 0, carry = 0;
	bool tmp;
	QInt result;

	for (int i = 0; i < length; i++){
		a0 = this->getBit(i);
		b0 = p.getBit(i);
		sum = a0 + b0 + carry;
		carry = sum / 2;
		tmp = sum % 2;
		result.setBit(tmp, i);
	}
	return result;
}
QInt QInt::operator-(QInt p){
	p.Bu2();
	return *this + p;   //this + (-p)
}
QInt QInt::operator*(QInt p){
	QInt A;
	int k = MAX_BIT;
	bool bit = 0;
	bool Q1 = 0;
	while (k > 0)
	{
		if (p.getBit(0) == 1 && Q1 == 0)
			A = A - *this;
		else if (p.getBit(0) == 0 && Q1 == 1)
			A = A + *this;
		bit = A.getBit(MAX_BIT-1);
		Q1 = p.getBit(0);
		p.SHR();
		p.setBit(A.getBit(0), MAX_BIT - 1);
		A.SHR();
		A.setBit(bit, MAX_BIT - 1);
		k--;
	}
	return p;
}
QInt QInt::operator/(QInt p){
	int i = MAX_BIT, bit = 0;
	QInt tmp_a = *this;
	QInt tmp_p = p;
	int count = 0;
	QInt A;
	for (int j = 0; i < 4; i++){   //kt xem p co phai la 0
		if (p.data[i] == 0)
			count++;
	}
	if (count != 4)
	{
		if (tmp_a.getBit(127) == 1)
			tmp_a.Bu2();
		if (tmp_p.getBit(127) == 1)
			tmp_p.Bu2();
		while (i > 0){
			A.SHL();
			bit = tmp_a.getBit(MAX_BIT - 1);
			A.setBit(bit, 0);
			tmp_a.SHL();
			A = A - tmp_p;
			if (A.getBit(127) == 1){
				tmp_a.setBit(0, 0);
				A = A + tmp_p;
			}
			else
				tmp_a.setBit(1, 0);
			i--;
		}
		if (this->getBit(127) != p.getBit(127))
			tmp_a.Bu2();
	}
	return tmp_a;
}

//Operator AND, OR, XOR, NOT
QInt QInt::AND(QInt a){
	QInt result;
	for (int i = 0; i < 4; i++)
		result.data[i] = this->data[i] & a.data[i];
	return result;
}
QInt QInt::OR(QInt a){
	QInt result;
	for (int i = 0; i < 4; i++)
		result.data[i] = this->data[i] | a.data[i];
	return result;
}
QInt QInt::XOR(QInt a){
	QInt result;
	for (int i = 0; i < 4; i++)
		result.data[i] = this->data[i] ^ a.data[i];
	return result;
}
void QInt::NOT(){
	for (int i = 0; i < 4; i++)
		this->data[i] = ~this->data[i];
}

//<<, >>
void QInt::SHL(){
	int bit;
	for (int i = MAX_BIT - 2; i >= 0; i--){
		bit = this->getBit(i);
		this->setBit(bit, i + 1);
	}
	this->setBit(0, 0);
}
void QInt::SHR(){
	int bit;
	for (int i = 0; i < MAX_BIT - 1; i++){
		bit = this->getBit(i + 1);
		this->setBit(bit, i);
	}
	this->setBit(0, MAX_BIT - 1);
}

//ROR, ROL
void QInt::ROR(){
	bool bit = this->getBit(0);
	this->SHR();
	this->setBit(bit, MAX_BIT - 1);
}
void QInt::ROL(){
	bool bit = this->getBit(MAX_BIT - 1);
	this->SHL();
	this->setBit(bit, 0);
}

//Test
string Add(string a, string b){
	int length = 0, stack = 0;
	int a0 = 0, b0 = 0, sum = 0, carry = 0;
	string result = "", tmp = "";
	if (a.size() < b.size()){
		tmp = a;
		a = b;
		b = tmp;
	}
	stack = a.size() - b.size();
	length = b.size();
	for (int i = length - 1; i >= 0; i--){
		a0 = a[i + stack] - 48;
		b0 = b[i] - 48;
		sum = a0 + b0 + carry;
		carry = sum / 10;
		tmp = sum % 10 + 48;
		result = tmp + result;
	}
	for (int i = stack - 1; i >= 0; i--){
		a0 = a[i] - 48;
		tmp = a0 + 48;
		if (carry != 0){
			sum = a0 + carry;
			carry = sum / 10;
			tmp = sum % 10 + 48;
		}
		result = tmp + result;
	}
	if (carry > 0)
	{
		tmp = carry + 48;
		result = tmp + result;
	}
	return result;
}
string Multi2(string a){
	int val = 0, carry = 0, a0 = 0;
	string result = a;
	for (int i = a.size() - 1; i >= 0; i--){
		a0 = a[i] - 48;
		val = a0 * 2 + carry;
		carry = val / 10;
		result[i] = val % 10 + 48;
	}
	if (carry > 0)
	{
		char crr = carry + 48;
		result = crr + result;
	}
	return result;
}