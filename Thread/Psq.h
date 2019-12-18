#ifndef PSQ_H
#define PSQ_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <pthread.h>
#include <errno.h>
#include <thread>
#include <algorithm>

using namespace std;

class Psq
{
private:
	int lSize;
	string filename;
	FILE *psq_file;
public:
	Psq(char* name);
	void rsize_psq();
	int get_size();
	void read_psq(char* buffer);
	void trace_back(int offsetpsq,char* sequence_binnaire,int bl_final[][28],int size_proteine,ofstream &f,char* buffer);

};

#endif

