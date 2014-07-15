#pragma once 

#include "randpool.h"
#include <modes.h>
#include <aes.h>
#include "hex.h"
#include "files.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include "BigInt.h"
#include "osrng.h"
#include "ConvertUtility.h"

using namespace std;
using namespace CryptoPP;


#pragma comment(lib, "cryptlib.lib")

const string aes = "AES";
const string ECB = "ECB";
const string InvAES = "InvAES";
const string CBC = "CBC";
const string InvCBC = "InvCBC";
const string InvECB = "InvECB";
//cout << "AES Parameters: " << endl;
//cout << "Algorithm name : " << AES::StaticAlgorithmName() << endl;
//cout << "Algorithm Type : " << argv[1] << endl;
//if ((argv[1] == aes || argv[1] == ECB) && argc >= 5){
//	cout << "Algorithm InputText : " << argv[2] << endl;
//	cout << "Algorithm InputKey : " << argv[3] << endl;
//	cout << "Algorithm OutputText  : " << argv[4] << endl;
//	cout << "Block size     : " << AES::BLOCKSIZE * 8 << endl;
//	AESBasicEncrypt(argv[2], argv[3], argv[4]);
//	system("pause");
//	return 0;
//}
//
//if (argv[1] == CBC&&argc >= 6){
//	cout << "Algorithm InputText : " << argv[2] << endl;
//	cout << "Algorithm InputKey : " << argv[3] << endl;
//	cout << "Algorithm IV : " << argv[4] << endl;
//	cout << "Algorithm OutputText  : " << argv[5] << endl;
//	cout << "Block size     : " << AES::BLOCKSIZE * 8 << endl;
//	AESCBCEncrypt(argv[2], argv[3], argv[4], argv[5]);
//	system("pause");
//	return 0;
//}
//if (argv[1] == InvCBC&&argc >= 6){
//	cout << "Algorithm InputText : " << argv[2] << endl;
//	cout << "Algorithm InputKey : " << argv[3] << endl;
//	cout << "Algorithm IV : " << argv[4] << endl;
//	cout << "Algorithm OutputText  : " << argv[5] << endl;
//	cout << "Block size     : " << AES::BLOCKSIZE * 8 << endl;
//	AESCBCDecrypt(argv[2], argv[3], argv[4], argv[5]);
//	system("pause");
//	return 0;
//}
//if ((argv[1] == InvAES || argv[1] == InvECB) && argc >= 5){
//	cout << "Algorithm InputText : " << argv[2] << endl;
//	cout << "Algorithm InputKey : " << argv[3] << endl;
//	cout << "Algorithm OutputText  : " << argv[4] << endl;
//	cout << "Block size     : " << AES::BLOCKSIZE * 8 << endl;
//	AESBasicDecrypt(argv[2], argv[3], argv[4]);
//	system("pause");
//	return 0;
//}
//cout << "the parameters has some error" << endl;

class myAES{
public:
	myAES();
	~myAES();

	static void generateAESKey(unsigned char key[], int size);
	static void generateAESKey(string &key);

	static bool AESBasicEncrypt(string input, string keyfile, string output);
	static bool AESBasicDecrypt(string input, string keyfile, string output);
	static void AESCBCEncrypt(string input, string keyfile, string iv, string output);
	static void AESCBCDecrypt(string input, string keyfile, string iv, string output);

	static bool AESBasicEncrypt(string input, unsigned char *aeskey, int length, string output);
	static bool AESBasicDecrypt(string input, unsigned char *aeskey, int length, string output);
	static void AESCBCEncrypt(string input, unsigned char *aeskey, int length, string iv, string output);
	static void AESCBCDecrypt(string input, unsigned char *aeskey, int length, string iv, string output);
	
private:
	static void  XorCharArray(unsigned char *a, unsigned char * b, int length);

};