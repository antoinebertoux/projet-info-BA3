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
	char* filename;
	ifstream file;
	int lenght_title;
	int lenght_titlestamp;
	int N;
	int pos;
	int protnumber = -1; //0?
	int offsetphr;
	void find_lenght_title();
	void find_lenght_titlestamp();
	void find_N();
	void find_protnumber(int offsetpsq);
	void find_offsetphr();
public:
	Pin(char* name);
	~Pin();
	void read_pin();
	int get_offsetphr(int n_offsetpsq);
};

#endif
