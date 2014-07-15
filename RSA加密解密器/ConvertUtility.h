#pragma once

#include <string>
#include <sstream>

using namespace std;

class ConvertUtility
{
public:
	static string uchar2HexString(unsigned char *array, int length){
		ostringstream oss;
		for (int i = 0; i < length; ++i){
			if (array[i] <= 0x0f) oss << std::hex << 0; // ���hex��λ��0��ostringstream�͸����Բ���ʾ��
			oss << std::hex << (int)array[i];
		}
		return oss.str();
	}

	static unsigned char char2Hex(char c){
		static char table[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
		if (isdigit(c))
			c -= '0';
		else if (islower(c))
			c -= 'a' - 10;
		else if (isupper(c))
			c -= 'A' - 10;
		return table[c];
	}

	static void HexString2uchar(string str, unsigned char *array, int &length){
		/*ʮ�������ַ����Ĵ��ڣ�
		������Ϊ�˷����Ķ���
		�������ʱ��Ҫ����ת����uchar��
		����֮������string��2���ַ��ϳ�Ϊ1��byte(unsigned char)
		*/
		int len = str.length();
		length = len / 2;
		for (int i = 0; i < length; ++i){
			byte b1 = char2Hex(str.at(2 * i));
			byte b2 = char2Hex(str.at(2 * i + 1));
			array[i] = (b1 << 4) | (b2 & 0x0F);
		}
	}
};
