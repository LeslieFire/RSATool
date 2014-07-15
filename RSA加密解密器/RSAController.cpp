#include "RSAController.h"

RSAController *RSAController::rsaController = NULL;

void RSAController::menu(){
	cout << "--------------------��ѡ��--------------------" << endl
		<< "                   e: ����                   " << endl
		<< "                   d: ����                   " << endl
		<< "                   p: ��ʾ                   " << endl
		<< "                   q: �˳�                   " << endl;

	cout << "input your choice : " << endl;
}

void RSAController::welcome(){
	char ch;
	string str;

	while (true)
	{
		menu();//�˵���ʾ
		cout << ">";
		cin >> str;
		if (!cin)
			return ;

		if (str.length()<1)
			cout << "��������" << endl;
		else
		{
			ch = str.at(0);
			switch (ch)
			{
			case 'e':
			case 'E':
				encry();//����
				break;
			case 'd':
			case 'D':
				decode();//����
				break;
			case 'p':
			case 'P':
				print();//�����˽Կ��Ϣ
				break;
			case 'q':
			case 'Q':
				return ;
			}
		}
	}
}


bool RSAController::decode()
{//����
	string input;
	string output;
	string aesfile;

	do
	{
		cout << ">������RSA��Կ�ļ���:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	if (!rsa.readPrivateKey(input)){
		cout << "��ȡRSA��Կ�ļ�ʧ�ܣ�" << endl;
		return false;
	}

	do
	{
		cout << ">������AES key �����ļ���:";
		cin >> aesfile;
	} while (cin && aesfile.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">����������Ҫ���ܵ��ļ���:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">��������ܺ���ļ���:";
		cin >> output;
	} while (cin && output.length() < 1);
	if (!cin)
		return false;

	ifstream infile;
	infile.open(aesfile);
	if (!infile){
		cout << "ȱ��" << aesfile << "��Կ�ļ�." << endl;
		return false;
	}

	string str;
	infile >> str;
	infile.close();
	// ���Ƚ�AES��Կ���ܳ���
	BigInt c(str);

	long t1 = clock();
	BigInt m = rsa.decodeByPr(c);
	long t2 = clock();
	cout << "��ʱ:" << (t2 - t1) << "ms." << endl;

	// ��BigIntת����byte����������AES����
	byte aeskey[AES::MAX_KEYLENGTH];
	int length;
	m.copyTo(str);
	ConvertUtility::HexString2uchar(str, aeskey, length);

	// ��AES��Կ�����ļ�
	if (!myAES::AESBasicDecrypt(input, aeskey, length, output)){
		cout << "AES Decryption failed!" << endl;
		return false;
	}

	return true;
}

bool RSAController::encry()
{//����
	string input;
	string output;
	string aesfile;
	do
	{
		cout << ">������RSA��Կ�ļ���:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	if (!rsa.readPublicKey(input)){
		cout << "��ȡRSA��Կ�ļ�ʧ�ܣ�" << endl;
		return false;
	}

	do
	{
		cout << ">����������Ҫ���ܵ��ļ���:";
		cin >> input;
	} while (cin && input.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">��������ܺ���ļ���:";
		cin >> output;
	} while (cin && output.length() < 1);
	if (!cin)
		return false;

	do
	{
		cout << ">��Ϊ�Զ����ɵ�AES key����ȡ��:";
		cin >> aesfile;
	} while (cin && aesfile.length() < 1);
	if (!cin)
		return false;

	// AES����
	byte aeskey[AES::MAX_KEYLENGTH];
	myAES::generateAESKey(aeskey, AES::MAX_KEYLENGTH);
	if (!myAES::AESBasicEncrypt(input, aeskey, AES::MAX_KEYLENGTH, output)){
		cout << "AES Encryption failed!" << endl;
		return false;
	}

	/*ofstream AES("openAES.key");
	AES << ConvertUtility::uchar2HexString(aeskey, AES::MAX_KEYLENGTH);*/

	// RSA����AES��Կ
	BigInt m(ConvertUtility::uchar2HexString(aeskey, AES::MAX_KEYLENGTH));

	ofstream encryptedAES(aesfile);
	BigInt c = rsa.encryptByPu(m);

	// ���汻���ܵ�AES��Կ���ļ�
	encryptedAES << c;
	cout << "���ܳɹ�... ..." << endl;

	return true;
}

void RSAController::print()
{//���
	cout << rsa << endl;
}
