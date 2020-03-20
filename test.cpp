#include"bignum.h"
#include"rsa.h"
#include<iostream>

//void testBigNum() {
//	int a = 98765;
//	int b = 12345;
//	std::cout << a - b << std::endl;
//	BigNum bi;
//	std::cout << bi.sub("98765", "12345") << std::endl;
//	std::cout << a + b << std::endl;
//	std::cout << bi.add("98765", "12345") << std::endl;
//	std::cout << a * b << std::endl;
//	std::cout << bi.mul("98765", "12345") << std::endl;
//	std::cout << a / b << std::endl;
//	std::cout << a % b << std::endl;
//	std::cout << bi.dev("98765", "12345").first << std::endl;
//	std::cout << bi.dev("98765", "12345").second << std::endl;
//}

void test() {
	RSA rsa;
	rsa.Ecrept("test.txt", "test.ecrept.txt");
	rsa.Decrept("test.ecrept.txt", "test.decrept.txt");

}
void testBigNum() {
	std::string s1 = "12345";
	std::string s2 = "67895";
	BigNum b1(s1);
	BigNum b2(s2);
	std::cout << b1 + b2 << std::endl;
}
int main()
{
	test();
	//testBigNum();
	return 0;
}