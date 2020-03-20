#pragma once
#include<string>
#include<utility>
#include<iostream>
class BigNum {
public:
	BigNum();
	BigNum(const std::string& num);
	BigNum(const int num);
	BigNum operator+(BigNum& bi);
	BigNum operator-(BigNum& bi);
	BigNum operator*(BigNum& bi);
	BigNum operator/(BigNum& bi);
	BigNum operator%(BigNum& bi);
	friend std::ostream& operator<<(std::ostream& _cout, const BigNum& bi);
private:
	std::string add(std::string num1, std::string num2);
	std::string sub(std::string num1, std::string num2);
	std::string mul(std::string num1, std::string num2);
	std::pair<std::string,std::string>dev(std::string num1, std::string num2);
	bool less(std::string& num1, std::string& num2);
	std::string _num;
};
