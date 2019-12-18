#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Blosum.h"

using namespace std;

Blosum::~Blosum(){}

Blosum::Blosum(char* blfiles){
	blfile=blfiles;
	ifstream blosum_file(blfile); // ouverture fichier (fichier de la proteine)
	if (!blosum_file.is_open()) { 
		cout << "erreur ouverture fichier" << endl;
		exit(1);
	}
	char truc;
	char junk1[256]; //je mets les infos de la premiere ligne du fichier P00533 dans junk(si jamais on en a besoin pour plus tard)
	while(blosum_file >> truc){
		if(truc == '#'){	// premiere ligne du fichier P00533 (se debarasse de cette ligne en la mettant dans junk)
			blosum_file.getline(junk1,256); //prends la 1ere pour la mettre dans junk	
		}
		else {
			blosum_file.getline(junk1,256); 
			break;
		}
	}	
	blosum_file.close();
}

void Blosum::get_blosum(int bl_final[][28]){
	ifstream blosum_file(blfile); // ouverture fichier (fichier de la proteine)
	if (!blosum_file.is_open()) { 
		cout << "erreur ouverture fichier" << endl;
		exit(1);
	}
	char truc;
	char junk1[256]; //je mets les infos de la premiere ligne du fichier P00533 dans junk(si jamais on en a besoin pour plus tard)
	while(blosum_file >> truc){
		if(truc == '#'){	// premiere ligne du fichier P00533 (se debarasse de cette ligne en la mettant dans junk)
			blosum_file.getline(junk1,256); //prends la 1ere pour la mettre dans junk	
		}
		else {
			blosum_file.getline(junk1,256); 
			break;
		}
	}	
	int bl[28][28];
	char lettre[28];
	int ligne=-1;
	int colone=0;
	int n;
    char c;
	int posi;
    // Loop until reading fails.
    while (blosum_file.get(c)) {
		
        if ((c >= '0' && c <= '9') ) {
			posi = (int)blosum_file.tellg();
			blosum_file.seekg(posi-1);
			blosum_file >> n;
			bl[ligne][colone]=n;
			colone++;
        } 
        else if(c=='-'){
			posi = (int)blosum_file.tellg();
			blosum_file.seekg(posi-1);
			blosum_file >> n;
			bl[ligne][colone]=n;
			colone++;
		}
		else if(c!=' ' && c!='\n' && c!='\0'){
			ligne++;
			lettre[ligne]=c;
			colone=0;
		}    
    }
    	
	int lettre_order[28];
	for (int i = 0; i < 28; i++){
			if(lettre[i]>='A' && lettre[i]<='I'){
				lettre_order[i]=lettre[i]-64;
			}
			else if(lettre[i]>='K' && lettre[i]<='N'){
				lettre_order[i]=lettre[i]-65;
			}
			else if(lettre[i]>='P' && lettre[i]<='T'){
				lettre_order[i]=lettre[i]-66;	
			}
			else if(lettre[i]>='V' && lettre[i]<='Z'){
				lettre_order[i]=lettre[i]-67;
			}
			else if(lettre[i]=='-'){lettre_order[i]=0;}
			else if(lettre[i]=='J'){lettre_order[i]=27;}
			else if(lettre[i]=='O'){lettre_order[i]=26;}
			else if(lettre[i]=='U'){lettre_order[i]=24;}
			else if(lettre[i]=='*'){lettre_order[i]=25;}//convertire
	}
	for (int l=0;l<28;l++){
		int cop =lettre_order[l];
		for (int y=0;y<28;y++){
			bl_final[y][cop]=bl[y][l];
		}	
	}
	for(int i = 0; i < 28; ++i){
	   for(int j = 0; j < 28 ; ++j) {
		  bl[i][j]=bl_final[i][j];
	   }
	}
	for (int l=0;l<28;l++){
		int cop =lettre_order[l];
		for (int y=0;y<28;y++){
			bl_final[cop][y]=bl[l][y];
		}
	}
	blosum_file.close();
}
