#ifndef BLOSUM_H
#define BLOSUM_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>


using namespace std;

class Blosum
{
private:
char* blfile;
public:
	Blosum(char* blfiles);
	void get_blosum(int bl_final[][28]);
	~Blosum();
};

#endif
