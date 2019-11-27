#ifndef PHR_H
#define PHR_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>


using namespace std;

class Phr
{
private:
	ifstream file;
	int offsetphr;
	uint8_t len;
	string name;
	void find_len();
	void find_lenght();
public:
	Phr(char* name, int n_offsetphr);
	~Phr();
	void read_phr();
	string get_name();
};

#endif
