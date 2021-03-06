/*
 *  myRSA.cpp
 *
 *  Created by Leslie Yang on 07/15/14.
 *  Copyright 2014 https://github.com/LeslieFire All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *  OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  ************************************************************************************ */ 

#include "myRSA.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<ctime>
#include<cstdlib>

using std::cout;
using std::endl;
using std::ostringstream;
using namespace std;

Rsa::Rsa()
{//add by leslie @2014/06/28
	e = 65537;
}

Rsa::~Rsa()
{
}

void Rsa::init(unsigned int n)
{
	srand(time(NULL));
	//产生大素数p、q
	cout << "create prime p..." << endl;
	_p = createPrime(n, 10);
	cout << "create prime q..." << endl;
	_q = createPrime(n, 10);
	//计算N
	N = _p*_q;
	//计算出欧拉数
	_ol = (_p - 1)*(_q - 1);
	//加密指数e
	cout << "create d..." << endl;
	createExp(_ol);
	// d
	// @begin-------------------add by leslie @2014/07/03
	ofstream outPrivate("rsaPrivate.key");
	outPrivate << _d << endl;
	outPrivate << N;
	outPrivate.close();

	ofstream outPublic("rsaPublic.key");
	outPublic << e << endl;
	outPublic << N;
	outPublic.close();
	// @end---------------------add by leslie @2014/07/03
}

BigInt Rsa::createOddNum(unsigned int n)
{//生成长度为n的奇数
	n=n/4;
	static unsigned char hex_table[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	if(n)
	{
		ostringstream oss;
		for(std::size_t i=0;i<n-1;++i)
			oss<<hex_table[rand()%16];
		oss<<hex_table[1];
		string str(oss.str());
		return BigInt(str);
	}
	else
		return BigInt::Zero;
}

bool Rsa::isPrime(const BigInt& n,const unsigned int k)
{//判断素数
	assert(n!=BigInt::Zero);
	if(n==BigInt::Two)
		return true;

	BigInt n_1=n-1;
	BigInt::bit b(n_1);//二进制位
	if(b.at(0)==1)
		return false;

	for(std::size_t t=0;t<k;++t)
	{
		BigInt a=createRandomSmallThan(n_1);//随机数
		BigInt d(BigInt::One);
		for(int i=b.size()-1;i>=0;--i)
		{
			BigInt x=d;
			d=(d*d)%n;
			if(d==BigInt::One && x!=BigInt::One && x!=n_1)
				return false;

			if(b.at(i))
			{
				assert(d!=BigInt::Zero);
				d=(a*d)%n;
			}
		}
		if(d!=BigInt::One)
			return false;
	}
	return true;
}

BigInt Rsa::createRandomSmallThan(const BigInt& a)
{
	unsigned long t=0;
	do
	{
		t=rand();
	}while(t==0);

	BigInt mod(t);
	BigInt r=mod%a;
	if(r==BigInt::Zero)
		r=a-BigInt::One;	
	return r;
}

BigInt Rsa::createPrime(unsigned int n,int it_count)
{//生成长度为n的素数
	assert(it_count>0);
	BigInt res=createOddNum(n);
	while(!isPrime(res,it_count))
	{
		res.add(BigInt::Two);
	}
	return res;
}

bool   Rsa::readPrivateKey(const string& file){
	ifstream infile(file);
	if (!infile.is_open()){
		return false;
	}

	string temp;
	infile >> temp;
	if (!islegal(temp)){
		cout << "illegal private key d!" << endl;
		return false;
	}
	_d = temp;

	temp.clear();
	infile >> temp;
	if (!islegal(temp)){
		cout << "illegal key N!" << endl;
		return false;
	}
	N = temp;
	//infile >> _d >> N;
	infile.close();
	infile.clear();

	return true;
}

bool   Rsa::readPublicKey(const string& file){
	ifstream infile(file);
	if (!infile.is_open()){
		return false;
	}
	string temp;
	infile >> temp;
	if (!islegal(temp)){
		cout << "illegal public key e!" << endl;
		return false;
	}
	e = temp;

	temp.clear();
	infile >> temp;
	if (!islegal(temp)){
		cout << "illegal key N!" << endl;
		return false;
	}
	N = temp;
	//infile >> e >> N;

	infile.close();
	infile.clear();
	
	return true;
}

void Rsa::createExp(const BigInt& ou)
{//从一个欧拉数中生成公钥、私钥指数
	//e=5;
	e = 65537;
	_d=e.extendEuclid(ou);
}

BigInt Rsa::encryptByPu(const BigInt& m)
{//公钥加密
	return m.moden(e,N);
}

BigInt Rsa::decodeByPr(const BigInt& c)
{//私钥解密
	return c.moden(_d,N);
}

BigInt Rsa::encryptByPr(const BigInt& m)
{//私钥加密
	return decodeByPr(m);
}

BigInt Rsa::decodeByPu(const BigInt& c)
{//公钥解密
	return encryptByPu(c);
}

