#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <pthread.h>
#include <errno.h>
#include <thread>
#include <algorithm>
#include "Psq.h"


using namespace std;
void* parcourire_buffer(void *datas);

Psq::Psq(char* name){
	FILE *psq_file;
	filename=name;
	filename+=".psq";
}
void Psq::rsize_psq(){
	
	psq_file = fopen (filename.c_str(), "rb" );
	if (psq_file==NULL) {fputs ("File error",stderr); exit (1);}
	//pour avoir la size du fichier psq:
	fseek (psq_file , 0 , SEEK_END);
	lSize = ftell (psq_file);
	fclose (psq_file);
	
}
int Psq::get_size(){
	return lSize;
}

void Psq::read_psq(char* buffer){
	psq_file = fopen (filename.c_str(), "rb" );
	if (psq_file==NULL) {fputs ("File error",stderr); exit (1);}
	//copie les données dans le buffer:
	size_t result;
	result = fread (buffer,1,lSize,psq_file);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
	// ferme fichier psq
	fclose (psq_file);	
}




