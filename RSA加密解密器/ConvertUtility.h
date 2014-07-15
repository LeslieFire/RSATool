
/*
 *  ConvertUtility.h
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

#include <string>
#include <sstream>

using namespace std;

class ConvertUtility
{
public:
	static string uchar2HexString(unsigned char *array, int length){
		ostringstream oss;
		for (int i = 0; i < length; ++i){
			if (array[i] <= 0x0f) oss << std::hex << 0; // 如果hex高位是0，ostringstream就给忽略不显示了
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
		/*十六进制字符串的存在，
		仅仅是为了方便阅读，
		在运算的时候，要将其转换成uchar，
		简言之，就是string的2个字符合成为1个byte(unsigned char)
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
