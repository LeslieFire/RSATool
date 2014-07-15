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
