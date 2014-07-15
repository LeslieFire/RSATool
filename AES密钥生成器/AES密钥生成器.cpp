/*
 *  AES密钥生成器.cpp
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
 *s
 *  ************************************************************************************ */ 


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include "randpool.h"
#include "aes.h"
#include "hex.h"
#include "files.h"
#include "cryptlib.h"
#include "osrng.h"
#include "BigInt.h"

#pragma comment( lib, "cryptlib.lib" )
using namespace std;
using namespace CryptoPP;

string uchar2HexString(unsigned char *array, int length){
	ostringstream oss;
	for (int i = 0; i < length; ++i){
		if (array[i] <= 0x0f) oss << std::hex << 0;  // ����hex��λ��0��ostringstream�͸����Բ���ʾ��
		oss << std::hex << (int)array[i];
	}
	return oss.str();
}

unsigned char char2Hex(char c){
	unsigned char ret;
	switch (c){
	case '0':ret = 0; break;
	case '1':ret = 1; break;
	case '2':ret = 2; break;
	case '3':ret = 3; break;
	case '4':ret = 4; break;
	case '5':ret = 5; break;
	case '6':ret = 6; break;
	case '7':ret = 7; break;
	case '8':ret = 8; break;
	case '9':ret = 9; break;
	case 'A':
	case 'a':ret = 10; break;
	case 'B':
	case 'b':ret = 11; break;
	case 'C':
	case 'c':ret = 12; break;
	case 'D':
	case 'd':ret = 13; break;
	case 'E':
	case 'e':ret = 14; break;
	case 'F':
	case 'f':ret = 15; break;
	default:
		break;
	}
	return ret;
}

void HexString2uchar(string str, unsigned char *array, int &length){
	/*ʮ�������ַ����Ĵ��ڣ�
	������Ϊ�˷����Ķ���
	��������ʱ����Ҫ����ת����uchar��
	����֮������string��2���ַ��ϳ�Ϊ1��byte(unsigned char)
	*/
	int len = str.length();
	length = len / 2;		

	for (int i = 0; i < length; ++i){
		byte b1 = char2Hex(str.at(2*i));
		byte b2 = char2Hex(str.at(2 * i + 1));
		array[i] = (b1 << 4) | (b2 & 0x0F);
	}
}


int main()
{
	AutoSeededRandomPool rnd;
	
	// Generate a random key
	cout << AES::MAX_KEYLENGTH << endl;
	unsigned char key[AES::MAX_KEYLENGTH] = {0x00};
	rnd.GenerateBlock(key, AES::MAX_KEYLENGTH);

	string hexStr = uchar2HexString(key, AES::MAX_KEYLENGTH);
	cout << hexStr << endl;
	
	BigInt bigInt(hexStr);
	ofstream outfile("aes.key");
	outfile << bigInt;
	outfile.close();

	cout << "���������˳�..." << endl;
	getchar();
	return 0;
}
