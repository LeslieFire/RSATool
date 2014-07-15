#include "myAES.h"


void myAES::generateAESKey(unsigned char *k, int size){
	// 生成AES密钥
	AutoSeededRandomPool rnd;

	// Generate a random key
	unsigned char key[AES::MAX_KEYLENGTH] = { 0x00 };
	rnd.GenerateBlock(key, size);

	memcpy(k, key, size);
}

void myAES::generateAESKey(string &k){

	// Generate a random key
	unsigned char key[AES::MAX_KEYLENGTH] = { 0x00 };
	generateAESKey(key, AES::MAX_KEYLENGTH);

	k = ConvertUtility::uchar2HexString(key, AES::MAX_KEYLENGTH);
}


bool myAES::AESBasicEncrypt(string input, unsigned char *aeskey, int length, string output){
	ifstream inputTextF;
	ofstream outputF(output.c_str(), ofstream::binary);
	inputTextF.open(input.c_str(), ifstream::binary);
	AESEncryption aesEncryptor;


	unsigned char aesText2[16] = { 0 };
	char inputT[16] = { 0 };
	unsigned char outBlock[AES::BLOCKSIZE] = { 0 };
	unsigned char xorBlock[AES::BLOCKSIZE];
	memset(xorBlock, 0, AES::BLOCKSIZE);
	if (!inputTextF){
		cout << "the " + input + " not found or error" << endl;
		return false;
	}

	int endNum = 0;

	aesEncryptor.SetKey(aeskey, length);
	/*cout << "key length : " << length * 8 << endl;

	cout << "output encryption Text     : " << endl;*/
	while (!inputTextF.eof())
	{
		memset(inputT, 0, AES::BLOCKSIZE);
		inputTextF.read(inputT, 16);
		endNum = inputTextF.gcount();
		if (endNum<16){
			for (int i = endNum; i<16; i++){
				inputT[i] = 16 - endNum;
			}
		}
		memcpy(aesText2, inputT, 16);

		aesEncryptor.ProcessAndXorBlock(aesText2, xorBlock, outBlock);

		for (int i = 0; i<16; i++) {
			outputF << outBlock[i];

			//cout << hex << (int)outBlock[i] << " ";


		}
		outputF.flush();
	}
	inputTextF.close();
	inputTextF.clear();
	outputF.close();
	outputF.clear();
	//cout << endl;
}

bool myAES::AESBasicEncrypt(string input, string key, string output){
	
	ifstream inputKeyF;
	char aesKey[32] = { 0 };
	unsigned char aesKey2[32] = { 0 };

	inputKeyF.open(key.c_str(), ifstream::binary);
	if (!inputKeyF){
		cout << "the " + key + " not found or error" << endl;
		return false;
	}
	inputKeyF.read(aesKey, 32);
	int  end_pos;
	end_pos = inputKeyF.gcount();
	memcpy(aesKey2, aesKey, end_pos);

	AESBasicEncrypt(input, aesKey2, end_pos, output);

	inputKeyF.close();
	inputKeyF.clear();	
	return true;
}


bool myAES::AESBasicDecrypt(string input, unsigned char *aeskey, int length, string output){
	ifstream inputTextF;
	ofstream outputF(output.c_str(), ofstream::binary);
	inputTextF.open(input.c_str(), ifstream::binary);
	AESDecryption aesDecryptor;

	int  endNum;
	unsigned char aesText2[16] = { 0 };
	char inputT[16] = { 0 };
	unsigned char outBlock[AES::BLOCKSIZE] = { 0 };
	unsigned char xorBlock[AES::BLOCKSIZE];
	memset(xorBlock, 0, AES::BLOCKSIZE);

	if (!inputTextF){
		cout << "the " + input + " not found or error" << endl;
		return false;
	}

	aesDecryptor.SetKey(aeskey, length);  //设定加密密钥  
	/*cout << " key length : " << length * 8 << endl;*/


	memset(inputT, 0, AES::BLOCKSIZE);
	/*cout << "output Decryption Text     : " << endl;*/

	while (inputTextF.peek() != EOF)
	{
		inputTextF.read(inputT, 16);
		endNum = 16;
		memcpy(aesText2, inputT, 16);

		aesDecryptor.ProcessAndXorBlock(aesText2, xorBlock, outBlock);  //加密  
		if (inputTextF.peek() == EOF){
			endNum = 16 - outBlock[15];
		}
		for (int i = 0; i<endNum; i++) {
			outputF << outBlock[i];

			//cout << hex << (int)outBlock[i] << " ";


		}
		//cout << endl;
		outputF.flush();
		memset(inputT, 0, AES::BLOCKSIZE);
	}
	inputTextF.close();
	inputTextF.clear();
	outputF.close();
	outputF.clear();
	/*cout << endl;*/
	return true;
}

bool myAES::AESBasicDecrypt(string input, string key, string output)
{
	ifstream inputKeyF;
	inputKeyF.open(key.c_str(), ifstream::binary);
	if (!inputKeyF){
		cout << "the " + key + " not found or error" << endl;

		return false;
	}
	char aesKey[32] = { 0 };
	unsigned char aesKey2[32] = { 0 };

	inputKeyF.read(aesKey, 32);
	int  end_pos;
	end_pos = inputKeyF.gcount();
	memcpy(aesKey2, aesKey, end_pos);

	AESBasicDecrypt(input, aesKey2, end_pos, output);

	inputKeyF.close();
	inputKeyF.clear();
	return true;
}

void myAES::AESCBCEncrypt(string input, string key, string iv, string output){
	ifstream inputTextF;
	ifstream inputKeyF;
	ifstream ivF;
	ofstream outputF(output.c_str(), ofstream::binary);
	AESEncryption aesEncryptor;
	char aesKey[32] = { 0 };
	unsigned char aesKey2[32] = { 0 };
	char inputT[16] = { 0 };
	unsigned char aesText2[16] = { 0 };
	unsigned char outBlock[AES::BLOCKSIZE] = { 0 };
	char ivArray[16] = { 0 };
	unsigned char ivArrayU[16] = { 0 };
	unsigned char xorBlock[AES::BLOCKSIZE];
	int end_pos = 0, endNum = 0;
	memset(xorBlock, 0, AES::BLOCKSIZE);


	inputKeyF.open(key.c_str(), ifstream::binary);
	if (!inputKeyF){
		cout << "the " + key + " not found or error" << endl;

		return;
	}
	inputKeyF.read(aesKey, 32);
	end_pos = inputKeyF.gcount();
	memcpy(aesKey2, aesKey, end_pos);
	aesEncryptor.SetKey(aesKey2, end_pos);
	cout << " key length : " << end_pos * 8 << endl;

	ivF.open(iv.c_str(), ifstream::binary);
	if (!ivF){
		cout << "the " + iv + " not found or error" << endl;

		return;
	}
	ivF.read(ivArray, 16);
	memcpy(ivArrayU, ivArray, 16);
	ivF.close();

	inputTextF.open(input.c_str(), ifstream::binary);
	if (!inputTextF){
		cout << "the " + input + " not found or error" << endl;

		return;
	}
	/*cout << "output encryption Text     : " << endl;*/

	while (!inputTextF.eof())
	{
		memset(inputT, 0, AES::BLOCKSIZE);
		inputTextF.read(inputT, 16);
		endNum = inputTextF.gcount();
		if (endNum<16){
			for (int i = endNum; i<16; i++){
				inputT[i] = 16 - endNum;
			}
		}
		memcpy(aesText2, inputT, 16);
		XorCharArray(aesText2, ivArrayU, 16);
		aesEncryptor.ProcessAndXorBlock(aesText2, xorBlock, outBlock);
		memcpy(ivArrayU, outBlock, 16);
		for (int i = 0; i<16; i++) {
			outputF << outBlock[i];

			//cout << hex << (int)outBlock[i] << " ";


		}
		outputF.flush();
	}
	inputTextF.close();
	inputTextF.clear();
	inputKeyF.close();
	inputKeyF.clear();
	outputF.close();
	outputF.clear();
	//cout << endl;
}
void myAES::AESCBCDecrypt(string input, string key, string iv, string output)
{
	ifstream inputTextF;
	ifstream inputKeyF;
	ifstream ivF;
	ofstream outputF(output.c_str(), ofstream::binary);
	inputTextF.open(input.c_str(), ifstream::binary);
	AESDecryption aesDecryptor;
	char aesKey[32] = { 0 };
	unsigned char aesKey2[32] = { 0 };
	unsigned char aesText2[16] = { 0 };
	char inputT[16] = { 0 };
	unsigned char outBlock[AES::BLOCKSIZE] = { 0 };
	char ivArray[16] = { 0 };
	unsigned char ivArrayU[16] = { 0 };
	unsigned char xorBlock[AES::BLOCKSIZE];
	memset(xorBlock, 0, AES::BLOCKSIZE);



	if (!inputTextF){
		cout << "the " + input + " not found or error" << endl;
		return;
	}
	inputKeyF.open(key.c_str(), ifstream::binary);
	if (!inputKeyF){
		cout << "the " + key + " not found or error" << endl;
		return;
	}
	inputKeyF.read(aesKey, 32);
	int  end_pos, endNum;
	end_pos = inputKeyF.gcount();
	memcpy(aesKey2, aesKey, end_pos);


	aesDecryptor.SetKey(aesKey2, end_pos);  //设定密钥  
	cout << " key length : " << end_pos * 8 << endl;

	ivF.open(iv.c_str(), ifstream::binary);
	if (!ivF){
		cout << "the " + iv + " not found or error" << endl;
		return;
	}
	ivF.read(ivArray, 16);
	memcpy(ivArrayU, ivArray, 16);
	ivF.close();

	memset(inputT, 0, AES::BLOCKSIZE);


	/*cout << "output Decryption Text     : " << endl;*/

	while (inputTextF.peek() != EOF)
	{
		inputTextF.read(inputT, 16);
		endNum = 16;
		memcpy(aesText2, inputT, 16);
		aesDecryptor.ProcessAndXorBlock(aesText2, xorBlock, outBlock);
		XorCharArray(outBlock, ivArrayU, 16);
		//memcpy(xorBlock,outBlock,16);  
		memcpy(ivArrayU, aesText2, 16);


		if (inputTextF.peek() == EOF){
			endNum = 16 - outBlock[15];
		}
		for (int i = 0; i<endNum; i++) {
			outputF << outBlock[i];

			//cout << hex << (int)outBlock[i] << " ";


		}
		//cout << endl;
		outputF.flush();
		memset(inputT, 0, AES::BLOCKSIZE);
	}
	inputTextF.close();
	inputTextF.clear();
	inputKeyF.close();
	inputKeyF.clear();
	outputF.close();
	outputF.clear();
	//cout << endl;
}

void  myAES::XorCharArray(unsigned char *a, unsigned char * b, int length){
	for (int i = 0; i<length; i++){
		a[i] = a[i] ^ b[i];
	}
}