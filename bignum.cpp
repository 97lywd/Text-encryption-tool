#include"bignum.h"
BigNum BigNum::operator+(BigNum& bi) {
	std::string ret = add(_num, bi._num);
	return BigNum(ret);
}
BigNum BigNum::operator-(BigNum& bi) {
	std::string ret = sub(_num, bi._num);
	return BigNum(ret);
}
BigNum BigNum::operator*(BigNum& bi) {
	std::string ret = mul(_num, bi._num);
	return BigNum(ret);
}
BigNum BigNum::operator/(BigNum& bi) {
	std::pair < std::string,std::string > ret = dev(_num, bi._num);
	return BigNum(ret.first);
}
BigNum BigNum::operator%(BigNum &bi){
	std::pair < std::string, std::string > ret = dev(_num, bi._num);
	return BigNum(ret.second);
} 
BigNum::BigNum(const std::string &num)                                 
	:_num(num)
{}
std::string BigNum::add(std::string num1, std::string num2) {
	//补齐位数
	int len1 = num1.size();
	int len2 = num2.size();
	int diffnum = abs(len1 - len2);
	int Longsize = len1 > len2 ? len1:len2;
	if (len1 < len2) {
		num1.insert(0, diffnum, '0');
	}
	else {
		num2.insert(0, diffnum, '0');
	}
	std::string ret;
	ret.resize(Longsize);
	//逐位相加
	int step = 0;
	for (int i = Longsize - 1; i >= 0; i--) {
		ret[i] = (num1[i] - '0') + (num2[i] - '0') + step;
		ret[i] += '0';
		if (ret[i] > '9') {
			ret[i] -= 10;
			step = 1;
		}else{
			step = 0;
		}
	}
	if (step == 1) {
		ret.insert(0, 1, '1');
	}
	return ret;
}

std::string BigNum::sub(std::string num1, std::string num2) {
	//补齐位数
	int len1 = num1.size();
	int len2 = num2.size();
	int diffnum = abs(len1 - len2);
	int Longsize = len1 > len2 ? len1 : len2;
	if (len1 < len2) {
		num1.insert(0, diffnum, '0');
	}
	else {
		num2.insert(0, diffnum, '0');
	}
	std::string ret;
	ret.resize(Longsize);
	for (int i = Longsize - 1; i >= 0; i--) {
		//判断是否需要借位
		if (num1[i] < num2[i]) {
			num1[i] += 10;
			num1[i - 1]--;
		}
		ret[i] = (num1[i] - '0') - (num2[i] - '0') + '0';		
	}
	while (ret.size() > 1 && ret[0] == '0') {
		ret.erase(0, 1);
	}
	return ret;
}
std::string BigNum::mul(std::string num1, std::string num2) {
	if (num2.size() > num1.size())
		swap(num1, num2);
	std::string ret = "0";
	for (int i = num2.size() - 1; i >= 0; i--) {
		int cur = num2[i] - '0';
		int step = 0;
		std::string temp = num1;
		for (int j = temp.size() - 1; j >= 0; j--) {
			temp[j] = (temp[j] - '0') * cur + step;
			if (temp[j] > 9) {
				step = temp[j] / 10;
				temp[j] %= 10;
			}
			else {
				step = 0;
			}
			temp[j] += '0';
		}
		//最后判断是否需要进位
		if (step > 0) {
			temp.insert(0, 1, step + '0');
		}
		//补零
		temp.append(num2.size() - i - 1, '0');
		ret = add(ret, temp);
	}
	return ret;
}


std::pair<std::string, std::string>BigNum::dev(std::string num1, std::string num2) {
	//商
	std::string ret;
	//余数
	std::string rdis = num1;
	//放大除数
	int diffNum = num1.size() - num2.size();
	num2.append(diffNum, '0');
	for (int i = 0; i <= diffNum; i++) {
		//记录减法执行的次数
		char record = '0';
		while (1) {
			if (less(rdis, num2))
				break;
			rdis = sub(rdis, num2);
			record++;
		}
		ret += record;
		num2.pop_back();
	}
	//删除前置0
	while (ret.size() > 1 && ret[0] == '0') {
		ret.erase(0, 1);
	}
	return make_pair(ret, rdis);
}
bool BigNum::less(std::string &num1, std::string &num2) {
	if (num1.size() < num2.size())
		return true;
	if (num1.size() > num2.size())
		return false;
	return num1 < num2;
}
std::ostream& operator<<(std::ostream& _cout, const BigNum& bi) {
	_cout << bi._num << std::endl;
	return _cout;
}