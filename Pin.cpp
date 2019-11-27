#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Pin.h"

using namespace std;

Pin::Pin(char* name){
	filename=name;
	file.open(filename, ios::in | ios::binary); //ouverture base de donnees
	if(!file) {
		cout << "Cannot open file!" << endl;
		exit(0);
	}
	read_pin();
	file.close();
}

Pin::~Pin(){}

void Pin::read_pin(){
	find_lenght_title();
	find_lenght_titlestamp();
	find_N();
}

void Pin::find_lenght_title(){
	pos=sizeof(int)*2;
	file.seekg(pos);
	file.read((char*)&lenght_title, sizeof(int));
	lenght_title=__builtin_bswap32(lenght_title);
}

void Pin::find_lenght_titlestamp(){
	pos=sizeof(int)*3+lenght_title;
	file.seekg(pos);
	file.read((char*)&lenght_titlestamp, sizeof(int));
	lenght_titlestamp=__builtin_bswap32(lenght_titlestamp);
}

void Pin::find_N(){
	pos=4*sizeof(int)+lenght_title+lenght_titlestamp;
	file.seekg(pos);
	file.read((char*)&N, sizeof(int));
	N=__builtin_bswap32(N);
}

int Pin::get_offsetphr(int offsetpsq){
	file.open(filename, ios::in | ios::binary); //ouverture base de donnees
	if(!file) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}
	find_protnumber(offsetpsq);
	find_offsetphr();
	file.close();
	return offsetphr;
}

void Pin::find_protnumber(int offsetpsq){
	pos=6*sizeof(int)+sizeof(int64_t)+lenght_title+lenght_titlestamp+(N+1)*sizeof(int);
	file.seekg(pos);
	int test;
	while(file.read((char *)&test, sizeof(int))){
		if(__builtin_bswap32(test)==offsetpsq){
			break;
		}
		protnumber++;
	}
}

void Pin::find_offsetphr(){
	pos=6*sizeof(int)+sizeof(int64_t)+lenght_title+lenght_titlestamp+(protnumber)*sizeof(int);
	file.seekg(pos);
	file.read((char*)&offsetphr, sizeof(int));
	offsetphr=__builtin_bswap32(offsetphr);
}
