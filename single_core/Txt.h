#ifndef TXT_H
#define TXT_H
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class Txt
{
private:
	vector<char> sequence;
	int sequence_lenght;
public:
	Txt(char* file);
	~Txt();
	char* translate_to_binary();
	void translate_to_binary(char* sequence_binnaire);
	vector<char> get_sequence();
	int getsequence_lenght();
};

#endif
