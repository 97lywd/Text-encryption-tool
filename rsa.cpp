#include"rsa.h"
#include<time.h>
#include<math.h>
#include<iostream>
#include<fstream>
RSA::RSA() {
	GetKeys();
}
void RSA::Ecrept(const char* filename, const char* fileout) {
	std::ifstream fin(filename,std::ifstream::binary);
	std::ofstream fout(fileout,std::ifstream::binary);
	if (!fin.is_open()) {
		perror("input failed");
		return;
	}
	char* buff = new char[CAPACITY];
	DataType* buffout = new DataType[CAPACITY];
	while (!fin.eof()) {
		fin.read(buff, CAPACITY);
		int Byte = fin.gcount();
		for (int i = 0; i < Byte; i++) {
			buffout[i] = Ecrept((DataType)buff[i], _key._ekey, _key._pkey);
		}
		std::cout << std::endl;
		fout.write((char*)buffout,  Byte * sizeof(DataType));
	}
	delete[]buff; 
	delete[]buffout;
	fin.close();
	fout.close();
}
void RSA::Decrept(const char* filename, const char* fileout) {
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ofstream::binary);
	if (!fin.is_open()) {
		perror("open failed");
		return;
	}
	DataType* buff = new DataType[CAPACITY];
	char* buffout = new char[CAPACITY];
	while (!fin.eof()) {
		fin.read((char*)buff, CAPACITY * sizeof(DataType));
		int num = fin.gcount();
		num /= sizeof(DataType);
		for (int i = 0; i < num; i++) {
			buffout[i] = (char)Decrept(buff[i], _key._dkey, _key._pkey);
		}
		std::cout << std::endl;
		fout.write(buffout, num);
	}
	delete[]buff;
	delete[]buffout;
	fin.close();
	fout.close();
}
void RSA::GetKeys() {
	DataType prime1 = GetPrimeNum();
	DataType prime2 = GetPrimeNum();
	while (prime1 == prime2) {
		prime2 = GetPrimeNum();
	}
	DataType Euler = GetEuler(prime1, prime2);
	_key._pkey = GetPKey(prime1,prime2);
	_key._ekey = GetEKey(Euler);
	_key._dkey = GetDkey(_key._ekey,Euler);
}
DataType RSA::Ecrept(DataType data, DataType ekey, DataType pkey) {
	DataType Ai = data;
	DataType msg = 1;
	while (ekey) {
		if (ekey & 1) {
			msg = (msg * Ai) % pkey;
		}
		ekey >>= 1;
		Ai = (Ai * Ai) % pkey;
	}
	return msg;
}
DataType RSA::Decrept(DataType data, DataType dkey, DataType pkey) {
	return Ecrept(data, dkey, pkey);  
}
DataType RSA::GetPrimeNum() {
	std::cout << "Getprime" << std::endl;
    boost::random::mt19937 gen(time(NULL));
    boost::random::uniform_int_distribution<DataType> dist(0, DataType(1) << 256);
	DataType prime;
	//srand(time(NULL));
	while (1) {
        prime = dist(gen);
		//prime = rand() % 10 + 2;
		//std::cout << "BIGnum::" << prime << std::endl;
		if (BigPrime(prime))
			break;
	}
	std::cout << "finish" << std::endl;
	return prime;
}
bool RSA::IsPrime(DataType data) {
	std::cout << "IsPrime()" << std::endl;
	for (int i = 2; i <= sqrt(data); i++) {
		if (data % i == 0) {
			return false;
		}
	}
	std::cout << "isprime finish" << std::endl;
	return true;
}
bool RSA::BigPrime(DataType data) {
	boost::random::mt11213b gen(time(NULL));
	if (miller_rabin_test(data, 25, gen)) {
		if (miller_rabin_test((data - 1) / 2, 25, gen)) {
			return true;
		}
	}
	return false;
}
DataType RSA::GetPKey(DataType prime1, DataType prime2) {
	return prime1 * prime2;
}
DataType RSA::GetEuler(DataType prime1, DataType prime2) {
	return (prime1 - 1) * (prime2 - 1);
}
DataType RSA::GetEKey(DataType Euler) {
	// 1 < e < f(n)
	boost::random::mt19937 gen(time(NULL));
	boost::random::uniform_int_distribution<DataType> dist(2, Euler);
	DataType ekey;
	while (1) {
		ekey = dist(gen);
		if (ekey > 1 && GetGcd(ekey, Euler) == 1) {
			return ekey;
		}
	}
}

DataType RSA::GetDkey(DataType ekey, DataType Euler) {
	//d: e*d % f(n) == 1
	DataType x = 0; 
	DataType y = 0;
	ExpandGcd(ekey, Euler, x, y);
	return (x % Euler + Euler) % Euler;
	/*DataType dkey = Euler / ekey;
	while (1) {
		if ((dkey * ekey) % Euler == 1)
			return dkey;
		++dkey;
	}*/
}

DataType RSA::GetGcd(DataType data1, DataType data2) {
	DataType residual;
	while (residual = data1 % data2) {
		data1 = data2;
		data2 = residual;
	}
	return data2;
}
DataType RSA::ExpandGcd(DataType a, DataType b,DataType &x,DataType &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd = ExpandGcd(b, a % b, x, y);
	DataType x1 = x;
	DataType y1 = y;
	x = y1;
	y = x1 - a / b * y1;
	return gcd;
}
Key RSA::GetallKey() {
	return _key;
}

