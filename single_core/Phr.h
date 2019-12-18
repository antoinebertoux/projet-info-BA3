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
	string filename;
	ifstream file;
	string nom;
	uint8_t find_len(int offsetphr);
	void find_length(uint8_t len);
public:
	Phr();
	Phr(char* name);
	~Phr();
	string read_phr(int n_offsetphr);
	string get_name();
};

#endif
