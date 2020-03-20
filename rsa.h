#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>
#include<boost/multiprecision/miller_rabin.hpp>
#define CAPACITY 256
typedef boost::multiprecision::int1024_t DataType;
struct Key {
	DataType _ekey;
	DataType _dkey;
	DataType _pkey;
};

class RSA {
public:
	RSA();
	Key GetallKey();
	void GetKeys();
	bool IsPrime(DataType data);
	bool BigPrime(DataType data);
	void Ecrept(const char* filename, const char* fileout);
	void Decrept(const char* filename, const char* fileout);
	DataType Ecrept(DataType data, DataType ekey, DataType pkey);
	DataType Decrept(DataType data, DataType dkey, DataType pkey);
	DataType GetPrimeNum();
	DataType GetPKey(DataType prime1,DataType prime2);
	DataType GetEuler(DataType prime1, DataType prime2);
	DataType GetEKey(DataType Euler);
	DataType GetDkey(DataType ekey, DataType Euler);
	DataType GetGcd(DataType data1, DataType data2);
	DataType ExpandGcd(DataType a, DataType b, DataType& x, DataType& y);
private:
	Key _key;
};