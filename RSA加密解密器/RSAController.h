/*
 *  RSAController.h
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

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "BigInt.h"
#include "myRSA.h"
#include "randpool.h"
#include "aes.h"
#include "hex.h"
#include "files.h"
#include "osrng.h"
#include "myAES.h"


#include "cryptlib.h"

#pragma comment( lib, "cryptlib.lib" )
using namespace std;
using namespace CryptoPP;

class RSAController{
public:

	~RSAController(){
		if (rsaController != NULL){
			delete rsaController;
			rsaController = NULL;
		}
	}

	static RSAController *rsaController;
	static RSAController *getInstance(){
		if (rsaController == NULL){
			rsaController = new RSAController;
		}
		return rsaController;
	}
	static void destroy(){
		if (rsaController != NULL){
			delete rsaController;
			rsaController = NULL;
		}
	}
	
	void menu();
	void welcome();
	bool encry();
	bool decode();
	void print();

private:
	Rsa rsa;
};
