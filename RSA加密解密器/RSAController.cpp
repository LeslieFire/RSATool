#include "RSAController.h"

RSAController *RSAController::rsaController = NULL;

void RSAController::menu(){
	cout << "--------------------请选择--------------------" << endl
		<< "                   e: 加密                   " << endl
		<< "                   d: 解密                   " << endl
		<< "                   p: 显示                   " << endl
		<< "                   q: 退出                   " << endl;

	cout << "input your choice : " << endl;
}

void RSAController::welcome(){
	char ch;
	string str;

	while (true)
	{
		menu();//菜单显示
		cout << ">";
		cin >> str;
		if (!cin)
			return ;

		if (str.length()<1)
			cout << "重新输入" << endl;
		else
		{
			ch = str.at(0);
			switch (ch)
			{
			case 'e':
			case 'E':
				encry();//加密
				break;
			case 'd':
			case 'D':
				decode();//解密
				break;
			case 'p':
			case 'P':
				print();//输出公私钥信息
				break;
			case 'q':
			case 'Q':
				return ;
			}
		}
	}
}


bool RSAController::decode()
{//解密
	string input;
	string output;
	string aesfile;

	do
	{
		cout << ">请输入RSA密钥文件名:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	if (!rsa.readPrivateKey(input)){
		cout << "读取RSA密钥文件失败！" << endl;
		return false;
	}

	do
	{
		cout << ">请输入AES key 密文文件名:";
		cin >> aesfile;
	} while (cin && aesfile.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">请输入你想要解密的文件名:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">请输入解密后的文件名:";
		cin >> output;
	} while (cin && output.length() < 1);
	if (!cin)
		return false;

	ifstream infile;
	infile.open(aesfile);
	if (!infile){
		cout << "缺少" << aesfile << "密钥文件." << endl;
		return false;
	}

	string str;
	infile >> str;
	infile.close();
	// 首先将AES密钥解密出来
	BigInt c(str);

	long t1 = clock();
	BigInt m = rsa.decodeByPr(c);
	long t2 = clock();
	cout << "用时:" << (t2 - t1) << "ms." << endl;

	// 将BigInt转换成byte，以适用于AES解密
	byte aeskey[AES::MAX_KEYLENGTH];
	int length;
	m.copyTo(str);
	ConvertUtility::HexString2uchar(str, aeskey, length);

	// 用AES密钥解密文件
	if (!myAES::AESBasicDecrypt(input, aeskey, length, output)){
		cout << "AES Decryption failed!" << endl;
		return false;
	}

	return true;
}

bool RSAController::encry()
{//加密
	string input;
	string output;
	string aesfile;
	do
	{
		cout << ">请输入RSA公钥文件名:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	if (!rsa.readPublicKey(input)){
		cout << "读取RSA公钥文件失败！" << endl;
		return false;
	}

	do
	{
		cout << ">请输入你想要加密的文件名:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">请输入加密后的文件名:";
		cin >> output;
	} while (cin && output.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">请为自动生成的AES key密文取名:";
		cin >> aesfile;
	} while (cin && aesfile.length() < 1);
	if (!cin)
		return false;

	// AES加密
	byte aeskey[AES::MAX_KEYLENGTH];
	myAES::generateAESKey(aeskey, AES::MAX_KEYLENGTH);
	if (!myAES::AESBasicEncrypt(input, aeskey, AES::MAX_KEYLENGTH, output)){
		cout << "AES Encryption failed!" << endl;
		return false;
	}

	/*ofstream AES("openAES.key");
	AES << ConvertUtility::uchar2HexString(aeskey, AES::MAX_KEYLENGTH);*/

	// RSA加密AES密钥
	BigInt m(ConvertUtility::uchar2HexString(aeskey, AES::MAX_KEYLENGTH));

	ofstream encryptedAES(aesfile);
	BigInt c = rsa.encryptByPu(m);

	// 保存被加密的AES密钥到文件
	encryptedAES << c;
	cout << "加密成功... ..." << endl;

	return true;
}

void RSAController::print()
{//输出
	cout << rsa << endl;
}
