#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <string>
#include "Protein.h"
#include "Pin.h"
#include "Phr.h"
#include <time.h>

using namespace std;

int main (int argc, char **argv){
	float temps;
    clock_t t1, t2;
    t1 = clock();
	if (argc!=5){ //si le nombre d'arguments est mauvais
		cout << "Nombre d'arguments invalides" << endl;
		exit(1);
	}

	ifstream cible_file(argv[1]); // ouverture fichier (fichier de la proteine)
	
	if (!cible_file.is_open()) { 
		cout << "erreur ouverture fichier" << endl;
		exit(1);
	}
	
	char word;
	char junk[256]; //je mets les infos de la premiere ligne du fichier P00533 dans junk(si jamais on en a besoin pour plus tard)
	vector<char> sequence;
	while(cible_file >> word)
	{
		if(word == '>'){	// premiere ligne du fichier P00533 (se debarasse de cette ligne en la mettant dans junk)
			cible_file.getline(junk,256); //prends la 1ere pour la mettre dans junk
		}
		else{
			sequence.push_back(word);
		}
		
	}
	
	cible_file.close();
	Protein *protein=new Protein(sequence); // pourquoi cree un pointeur ?
	ifstream rf(argv[2], ios::in | ios::binary); //ouverture base de donnees
	if(!rf) {
		cout << "Cannot open file!" << endl;
		exit(1);
	}

	int8_t ch;
	int8_t zero=int8_t(0);
	vector<int8_t> data_base;
	rf.read((char *)&ch, sizeof(int8_t));
	bool verif= false;
	int offsetpsq=-1;
	while(rf.read((char *)&ch, sizeof(int8_t))){ // ch servira a comparer avec la sequence de P00533 que tu dois transformer en binaire 
		if(ch==zero){
			verif=protein->isequal(data_base, "nice");
			for (int i=0;i<data_base.size();i++){
				data_base.clear();
			}
			
			if (verif){
				offsetpsq=(int)rf.tellg();//-(int)sequence.size()*sizeof(int8_t);
				cout << "offsetpsq : " << offsetpsq << endl;
				break;
			}
		}
		else{
			data_base.push_back(ch);
		}
	}
	
	if(!rf.good()) {
		cout << endl << "Error occurred at reading time!" << endl;
		rf.close();
		exit(1);
	}
	rf.close();
	cout << "offsetpsq : " << offsetpsq << endl;
	Pin rpin(argv[3]);
	Phr rphr(argv[4], rpin.get_offsetphr(offsetpsq));
	cout << "name : " << rphr.get_name() << endl;

	delete protein; // ne pas oublier
	

	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
	return 0; 
}
