#ifndef PIN_H
#define PIN_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>


using namespace std;

class Pin
{
private:
	string filename;
	string title ;
	string titlestamp;
	int version;
	int nbreprot;
	int typedb;
	int maxlength;
	ifstream file;
	int length_title;
	int length_titlestamp;
	int length_version;
	int dbtype;
	int max;
	int N;
	
	void find_length_title();
	void find_length_titlestamp();
	void find_N();
	int  find_protnumber(int offsetpsq);
	int find_offsetphr(int protnumber);
	void find_version();
	void find_dbtype();
	void find_maxlength();
public:
	Pin(char* name);
	~Pin();
	void read_pin();
	int get_offsetphr(int n_offsetpsq);
	string get_title();
	string get_titlestamp();
	int get_version();
	int get_nbreprot();
	int get_typedb();
	int get_maxlength();
	
};

#endif
