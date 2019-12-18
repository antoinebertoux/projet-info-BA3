#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Pin.h"

using namespace std;


Pin::Pin(char* name){
	filename=name;
	filename+=".pin";
	file.open(filename.c_str(), ios::in | ios::binary); //ouverture base de donnees
	if(!file) {
		cout << "Cannot open file!" << endl;
		exit(0);
	}
	read_pin();
	file.close();
}

Pin::~Pin(){}

void Pin::read_pin(){
	find_version();
	find_dbtype();
	find_length_title();
	find_length_titlestamp();
	find_N();
	find_maxlength();
}

void Pin::find_length_title(){
	int pos=sizeof(int)*2;
	file.seekg(pos);
	file.read((char*)&length_title, sizeof(int));
	length_title=__builtin_bswap32(length_title);
	char titles[length_title];
	file.read((char*)&titles,length_title);
	title =(titles);
	
}


void Pin::find_length_titlestamp(){
	int pos=sizeof(int)*3+length_title;
	file.seekg(pos);
	file.read((char*)&length_titlestamp, sizeof(int));
	length_titlestamp=__builtin_bswap32(length_titlestamp);
	char ts[length_titlestamp];
	file.read((char*)&ts,length_titlestamp);
	titlestamp =(ts);
}

void Pin::find_N(){
	int pos=4*sizeof(int)+length_title+length_titlestamp;
	file.seekg(pos);
	file.read((char*)&N, sizeof(int));
	N=__builtin_bswap32(N);
	nbreprot = N;
}



void Pin::find_version(){
	int pos=0;
	file.seekg(pos);
	file.read((char*)&length_version, sizeof(int));
	length_version=__builtin_bswap32(length_version);
	version = length_version;
}

void Pin::find_dbtype(){
	int pos=sizeof(int);
	file.seekg(pos);
	file.read((char*)&dbtype, sizeof(int));
	dbtype=__builtin_bswap32(dbtype);
	typedb = dbtype;
}

void Pin::find_maxlength(){
	int pos=5*sizeof(int)+sizeof(int64_t)+length_title+length_titlestamp;
	file.seekg(pos);
	file.read((char*)&max, sizeof(int));
	max=__builtin_bswap32(max);
	maxlength = max;
}


int Pin::get_offsetphr(int offsetpsq){
	file.open(filename, ios::in | ios::binary); //ouverture base de donnees
	if(!file) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}
	int protnumber=find_protnumber(offsetpsq);
	int offsetphr=find_offsetphr(protnumber);
	file.close();
	return offsetphr;
}

int Pin::find_protnumber(int offsetpsq){
	int protnumber=-1;
	int pos=6*sizeof(int)+sizeof(int64_t)+length_title+length_titlestamp+(N+1)*sizeof(int);
	file.seekg(pos);
	int test;
	while(file.read((char *)&test, sizeof(int))){
		if(__builtin_bswap32(test)==offsetpsq){
			break;
		}
		protnumber++;
	}
	return protnumber;
}

int Pin::find_offsetphr(int protnumber){
	int offsetphr;
	int pos=6*sizeof(int)+sizeof(int64_t)+length_title+length_titlestamp+(protnumber)*sizeof(int);
	file.seekg(pos);
	file.read((char*)&offsetphr, sizeof(int));
	offsetphr=__builtin_bswap32(offsetphr);
	return offsetphr;
}

string Pin::get_title(){
	return title;
}

string Pin::get_titlestamp(){
	return titlestamp;
}

int Pin::get_nbreprot(){
	return nbreprot;
}

int Pin::get_version(){
	return version;
}

int Pin::get_typedb(){
	return typedb;
}

int Pin::get_maxlength(){
	return maxlength;
}

