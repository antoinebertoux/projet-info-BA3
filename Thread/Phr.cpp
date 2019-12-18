#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Phr.h"

using namespace std;
Phr::Phr(){}
Phr::Phr(char* name){
	filename=name;
	filename+=".phr";
}

Phr::~Phr(){}

string Phr::read_phr(int offsetphr){
	file.open(filename.c_str(), ios::in | ios::binary); //ouverture base de donnees
	if(!file) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}
	uint8_t len = find_len(offsetphr);
	find_length(len);
	char names[len]; // read n'accept pas les string
	file.read((char*)names, sizeof(names));	
	nom=(names);
	file.close();
	return nom;
}

uint8_t Phr::find_len(int offsetphr){
	uint8_t len;
	file.seekg(offsetphr);
	file.read((char*)&len, sizeof(uint8_t));
	while(len!=uint8_t(0x1A)){
		file.read((char*)&len, sizeof(uint8_t));
	}
	file.read((char*)&len, sizeof(uint8_t));
	return len;
}

void Phr::find_length(uint8_t len){
	bool etatDuBitN = (((len >> 7) & 1) == 1);
	if ( (len>>7)&1 ){ // si le n'eine bit est a 1
		len = len & ~(1<<7) ;   //force a 0
		int length;
		file.read((char*)&length, int(len)*sizeof(char));
		len=length;
	}
}

string Phr::get_name(){
	return nom;
}

