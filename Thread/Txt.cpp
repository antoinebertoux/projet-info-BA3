#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Txt.h"
using namespace std;

Txt::Txt(char* file){
	ifstream cible_file(file); // ouverture du fichier de la proteine
	if (!cible_file.is_open()) { 
		cout << "erreur ouverture fichier" << endl;
		exit(1);
	}
	char word;
	char junk[256]; 
	while(cible_file >> word){
		if(word == '>'){	// premiere ligne du fichier P00533 (se debarasse de cette ligne en la mettant dans junk)
			cible_file.getline(junk,256); //prends la 1ere pour la mettre dans junk
		}
		else{
			sequence.push_back(word);
		}
	}
	cible_file.close();
	sequence_lenght=sequence.size();
}

Txt::~Txt(){}

void Txt::translate_to_binary(char* sequence_binnaire){
	
	map<char,char> translate{{'-',0},{'A',1},{'B',2},{'C',3},{'D',4},{'E',5},{'F',6},{'G',7},{'H',8},{'I',9},{'J',27},{'K',10},{'L',11},{'M',12},{'N',13},{'O',26},{'P',14},{'Q',15},{'R',16},{'S',17},{'T',18},{'U',24},{'V',19},{'W',20},{'X',21},{'Y',22},{'Z',23},{'*',25}};
	for (int i = 0; i < sequence.size(); i++){
		sequence_binnaire[i]=translate[sequence[i]];
	}
}
int Txt::getsequence_lenght(){
	return sequence_lenght;
}

vector<char> Txt::get_sequence(){
	return sequence;
}
