#include <iostream>
#include "Protein.h"
#include <string>
#include <vector>

using namespace std;

Protein::Protein(vector<char>  sequence){
	translate_to_binary(sequence);
}

Protein::~Protein(){}

void Protein::translate_to_binary(vector<char> sequence){
	for (int i = 0; i < sequence.size(); i++){
		if(sequence[i]>='A' && sequence[i]<='I'){
			sequence_binnaire.push_back(sequence[i]-64);
		}
		else if(sequence[i]>='K' && sequence[i]<='N'){
			sequence_binnaire.push_back(sequence[i]-65);
		}
		else if(sequence[i]>='P' && sequence[i]<='T'){
			sequence_binnaire.push_back(sequence[i]-66);	
		}
		else if(sequence[i]>='V' && sequence[i]<='Z'){
			sequence_binnaire.push_back(sequence[i]-67);
		}
		else if(sequence[i]=='-'){sequence_binnaire.push_back(0);}
		else if(sequence[i]=='J'){sequence_binnaire.push_back(27);}
		else if(sequence[i]=='O'){sequence_binnaire.push_back(26);}
		else if(sequence[i]=='O'){sequence_binnaire.push_back(24);}
		else if(sequence[i]=='*'){sequence_binnaire.push_back(25);}//convertire
	}
}

bool Protein::isequal(vector<int8_t> chaine, string name_of_test){
	for(int i=0;i< sequence_binnaire.size(); i++){
		if(sequence_binnaire[i]!=chaine[i]){
			return false;
		}
	}
	name=name_of_test;
	return true;
}

string Protein::getname(){
	return name;
}

vector<int8_t> Protein::getsequence_binnaire(){
	return sequence_binnaire;
}
