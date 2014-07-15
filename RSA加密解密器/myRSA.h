#pragma once
#include"BigInt.h"
class Rsa
{
public:
	Rsa();
	~Rsa();
	void init(unsigned int n);//初始化，产生公私钥对

	friend void test();
public:
	BigInt encryptByPu(const BigInt& m);//私钥加密
	BigInt decodeByPr(const BigInt& c);//公钥解密

	BigInt encryptByPr(const BigInt& m);//公钥加密
	BigInt decodeByPu(const BigInt& m);//私钥解密

	// @begin-------------add by leslie @2014/07/08
	bool   readPrivateKey(const string& file);
	bool   readPublicKey(const string& file);
	bool   islegal(const string& str)
	{//判断输入是否合法
		for (string::const_iterator it = str.begin(); it != str.end(); ++it)
			if (!isalnum(*it))//不是字母数字
				return false;
		return true;
	}
	// @end--------------add by leslie @2014/07/08
private:
	BigInt createOddNum(unsigned int n);//生成长度为n的奇数
	bool isPrime(const BigInt& a,const unsigned int k);//判断素数
	BigInt createPrime(unsigned int n,int it_cout);//生成长度为n的素数
	void createExp(const BigInt& ou);//从一个欧拉数中生成公钥、私钥指数
	BigInt createRandomSmallThan(const BigInt& a);//创建小数
	friend ostream& operator <<(ostream& out,const Rsa& rsa)//输出
	{
		out<<"N:"<<rsa.N<<"\n";
		out<<"p:"<<rsa._p<<"\n";
		out<<"q:"<<rsa._q<<"\n";
		out<<"e:"<<rsa.e<<"\n";
		out<<"d:"<<rsa._d;
		return out;
	}
	// add by leslie 2014/6/28
	friend ifstream& operator >>(ifstream &in, Rsa& rsa)
	{
		in >> rsa._d >> rsa.N;
		return in;
	}
public:
	BigInt e,N;//公钥
private:
	BigInt _d;//私钥
	BigInt _p,_q;//
	BigInt _ol;//欧拉数
};