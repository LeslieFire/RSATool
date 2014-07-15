// RSA公钥密钥生成器.cpp : 定义控制台应用程序的入口点。
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
	cout << "正在生成1024位RSA密钥文件和公钥文件...." << endl;
	long t1 = clock();
	rsa.init(512);
	long t2 = clock();
	cout << "RSA密钥公钥生成完成." << endl;
	cout << "用时:" << (t2 - t1) / 1000 << "s." << endl;

	getchar();
	return 0;
}

