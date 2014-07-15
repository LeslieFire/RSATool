/*
 *  myRSA.h
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