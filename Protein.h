#ifndef PROTEIN_H
#define PROTEIN_H
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class Protein
{
private:
	vector<int8_t> sequence_binnaire;
	string name;
public:
	Protein(vector<char> sequence);
	~Protein();
	void translate_to_binary(vector<char> sequence);
	bool isequal(vector<int8_t>  chaine, string name_of_test);
	string getname();
	vector<int8_t> getsequence_binnaire();
};

#endif
