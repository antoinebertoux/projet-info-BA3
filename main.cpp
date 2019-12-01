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
	
	
	
	
	FILE *psq_file;
	long lSize;
	char *buffer;
	size_t result;

	psq_file = fopen ( argv[2] , "rb" );
	if (psq_file==NULL) {fputs ("File error",stderr); exit (1);}

	// obtain file size:
	fseek (psq_file , 0 , SEEK_END);
	lSize = ftell (psq_file);
	rewind (psq_file);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	// copy the file into the buffer:
	result = fread (buffer,1,lSize,psq_file);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	/* the whole file is now loaded in the memory buffer. */

	// terminate
	fclose (psq_file);
	
	
	


	char zero=char(0);
	vector<char> sequence_binnaire = protein->getsequence_binnaire();
	//buffer.read((char *)&ch, sizeof(int8_t));
	
	bool verif= false;
	bool continue_seq =true;
	int offsetpsq=-1;
	int pos = 1;

	while(pos<=lSize){ // ch servira a comparer avec la sequence de P00533 que tu dois transformer en binaire 
		while(buffer[pos]!=zero){
			if(continue_seq){
				for(int i=0;i< sequence_binnaire.size(); i++){
					if(sequence_binnaire[i]!=buffer[pos]){
						continue_seq=false;
						break;
					}
					pos++;
				}
			}
			else{
				pos++;
			}
			
		}
		
		if (continue_seq){
			offsetpsq=pos+1;//-(int)sequence.size()*sizeof(int8_t);
			cout << "offsetpsq : " << offsetpsq << endl;
			break;
		
		}
		else{
			continue_seq=true;
		}
		pos++;
			
		}
		
			
		
	cout << int(buffer[offsetpsq]) << endl;
	cout << int(buffer[offsetpsq-1]) << endl;
	
	
	Pin rpin(argv[3]);
	Phr rphr(argv[4], rpin.get_offsetphr(offsetpsq));
	cout << "name : " << rphr.get_name() << endl;
	delete protein; // ne pas oublier
	free (buffer);
	

	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
	return 0; 
}
