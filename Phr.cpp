#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Phr.h"

using namespace std;

Phr::Phr(char* name, int n_offsetphr){
	file.open(name, ios::in | ios::binary); //ouverture base de donnees
	offsetphr=n_offsetphr;
	if(!file) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}
	read_phr();
	file.close();
}

Phr::~Phr(){}

void Phr::read_phr(){
	find_len();
	find_lenght();
	char names[len]; // read n'accept pas les string
	file.read((char*)names, sizeof(names));	
	name=(names);
}

void Phr::find_len(){
	file.seekg(offsetphr);
	file.read((char*)&len, sizeof(uint8_t));
	while(len!=uint8_t(0x1A)){
		file.read((char*)&len, sizeof(uint8_t));
	}
	cout << hex << int(len) << '\n';
	file.read((char*)&len, sizeof(uint8_t));
}

void Phr::find_lenght(){
	bool etatDuBitN = (((len >> 7) & 1) == 1);
	cout << dec << "Etat du bit N : " << etatDuBitN << endl;
	cout << int(len) << endl;
	if ( (len>>7)&1 ){ // si le n'eine bit est a 1
		len = len & ~(1<<7) ;   //force a 0
		int lenght;
		file.read((char*)&lenght, int(len)*sizeof(char));
		cout << "len : " << int(len) << '\n';
		len=lenght;
	}
}

string Phr::get_name(){
	return name;
}
