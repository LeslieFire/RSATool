// RSA��Կ��Կ������.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "BigInt.h"
#include "myRSA.h"

#include "randpool.h"
#include "aes.h"
#include "hex.h"
#include "files.h"

#include "cryptlib.h"

#pragma comment( lib, "cryptlib.lib" )

using namespace CryptoPP;
using namespace std;

int main()
{
	Rsa rsa;
	cout << "��������1024λRSA��Կ�ļ��͹�Կ�ļ�...." << endl;
	long t1 = clock();
	rsa.init(512);
	long t2 = clock();
	cout << "RSA��Կ��Կ�������." << endl;
	cout << "��ʱ:" << (t2 - t1) / 1000 << "s." << endl;

	getchar();
	return 0;
}

