#pragma once
#include"BigInt.h"
class Rsa
{
public:
	Rsa();
	~Rsa();
	void init(unsigned int n);//��ʼ����������˽Կ��

	friend void test();
public:
	BigInt encryptByPu(const BigInt& m);//˽Կ����
	BigInt decodeByPr(const BigInt& c);//��Կ����

	BigInt encryptByPr(const BigInt& m);//��Կ����
	BigInt decodeByPu(const BigInt& m);//˽Կ����

	// @begin-------------add by leslie @2014/07/08
	bool   readPrivateKey(const string& file);
	bool   readPublicKey(const string& file);
	bool   islegal(const string& str)
	{//�ж������Ƿ�Ϸ�
		for (string::const_iterator it = str.begin(); it != str.end(); ++it)
			if (!isalnum(*it))//������ĸ����
				return false;
		return true;
	}
	// @end--------------add by leslie @2014/07/08
private:
	BigInt createOddNum(unsigned int n);//���ɳ���Ϊn������
	bool isPrime(const BigInt& a,const unsigned int k);//�ж�����
	BigInt createPrime(unsigned int n,int it_cout);//���ɳ���Ϊn������
	void createExp(const BigInt& ou);//��һ��ŷ���������ɹ�Կ��˽Կָ��
	BigInt createRandomSmallThan(const BigInt& a);//����С��
	friend ostream& operator <<(ostream& out,const Rsa& rsa)//���
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
	BigInt e,N;//��Կ
private:
	BigInt _d;//˽Կ
	BigInt _p,_q;//
	BigInt _ol;//ŷ����
};