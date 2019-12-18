#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <pthread.h>
#include <errno.h>
#include <thread>
#include "Txt.h"
#include "Pin.h"
#include "Phr.h"
#include "Psq.h"
#include "Blosum.h"

using namespace std;
typedef struct datat{
 	multimap <int,int> *prot;
	pthread_mutex_t mutex;
	char *buffer;
	int bl_final [28][28];
	int borne_inf;
	int borne_sup;
	int gap_open_penalty;
	int gap_extension_penaly;
	int maxlenght;
	int size_proteine;
	char* sequence_binnaire;

} datat;
void print_result(Pin rpin, Txt rTxt, Phr rphr, multimap <int,int> &prot, int bl_final[][28]);
void trace_back(int offsetpsq,char* sequence_binnaire,int bl_final[][28],int size_proteine,ofstream &f,char* buffer,int maxlenght,int gap_open_penalty, int gap_extension_penaly){
	string allignement="";
	string original="";
	int pos=offsetpsq-2;
	while(buffer[pos]!='\0'){
		pos--;
	}
	pos++;
	int maxval=0;
	int score;
	int i;
	int save_i, save_j;
	int Memoj=0;
	int Memoi[size_proteine+1];
	const int ab=size_proteine+1;
	const int abc=maxlenght+1;
	int** N = new int*[abc];
	int** trace= new int*[abc];
	for(int i = 0; i < abc; ++i){
		N[i] = new int[ab];
		N[i][0]=0;
		trace[i] = new int[ab];
		trace[i][0]=0;
	}
	for(int i =0;i<ab;i++){
		N[0][i]=0;
		trace[0][i]=0;
	}
	
	i=1;
	memset(Memoi, 0, sizeof(Memoi));
	maxval=0;
	int count=0;
	int savepos=0;
	map<char,string> translate{{0,"-"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"F"},{7,"G"},{8,"H"},{9,"I"},{27,"J"},{10,"K"},{11,"L"},{12,"M"},{13,"N"},{26,"O"},{14,"P"},{15,"Q"},{16,"R"},{17,"S"},{18,"T"},{24,"U"},{19,"V"},{20,"W"},{21,"X"},{22,"Y"},{23,"Z"},{25,"*"}};
	int allignementpp=0;
	while(buffer[pos]!='\0'){
		Memoj=0;
		count++;
		for(unsigned int j=1; j<=size_proteine; j++){
			Memoi[j]=max(N[i-1][j]-gap_open_penalty,Memoi[j])-gap_extension_penaly; //vecteur fixe
			Memoj=max(N[i][j-1]-gap_open_penalty,Memoj)-gap_extension_penaly; //faire le max nous même
			allignementpp=N[i-1][j-1]+bl_final[sequence_binnaire[j-1]][buffer[pos]];
			score=max(max(max(Memoi[j],Memoj),allignementpp),0);
			N[i][j]=score;
			if(score==Memoi[j]){
				trace[i][j]=1;
			}
			else if(score==Memoj){
				trace[i][j]=2;
			}
			else if(score==allignementpp){
				trace[i][j]=3;		
			}
			else {
				trace[i][j]=0;
			}
			if(score>maxval){
				maxval=score;
				save_i=i;
				save_j=j;
				savepos=pos;
			}
		}
		i++;
		pos++;
	}
	pos=savepos;
	i=save_i;
	int j=save_j;
	int left = 1;
	int up = 2;
	int diag = 3;
	int lettre=(int)buffer[pos];
	allignement+=translate[buffer[pos]];
	original+=translate[sequence_binnaire[j]];
	while(i!=0&&j!=0){
		if (trace[i][j] == diag){
			j=j-1;
			i=i-1;
			pos--;		
			allignement+=translate[buffer[pos]];
			original+=translate[sequence_binnaire[j]];
		}
		else if (trace[i][j] == left){
			i=i-1;
			original+="-";
		}
		else if (trace[i][j] == up){
			j=j-1;
			pos--;
			allignement+="-";	
		}
		else{
			break;
		}
	}
	reverse(allignement.begin(), allignement.end());
	reverse(original.begin(), original.end());
	f << "original " << endl;
	f << original << endl;
	f << "alignement " << endl;
	f << allignement << endl;
}

void *parcourire_buffer(void *datas){
	datat data = *((datat *)datas);
	multimap <int,int> *prot=data.prot;
	pthread_mutex_t mutex=data.mutex;
	char *buffer=data.buffer;
	int bl_final [28][28];
	memmove(bl_final, data.bl_final, sizeof(data.bl_final));
	int borne_inf=data.borne_inf;
	int borne_sup=data.borne_sup;
	int gap_open_penalty=data.gap_open_penalty;
	int gap_extension_penaly=data.gap_extension_penaly;
	const int maxlenght=data.maxlenght;
	char* sequence_binnaire=data.sequence_binnaire;
	int size_proteine=data.size_proteine;
	int res;
	unsigned int pos=borne_inf;
	int maxval=0,maxtot=0;
	int score;
	int i;
	int Memoj=0;
	int Memoi[size_proteine+1];
	const int ab=size_proteine+1;
	const int abc=maxlenght+1;
	int** N = new int*[abc];
	int allignement;
	for(int i = 0; i < abc; ++i){
		N[i] = new int[ab]; //free
		N[i][0]=0;
	}
	for(int i =0;i<ab;i++){
		N[0][i]=0;}
	while(buffer[pos]!='\0'){pos++;}
	while(pos<=borne_sup){ // thread 
		i=1;
		memset(Memoi, 0, sizeof(Memoi));
		maxval=0;
		while(buffer[pos]!='\0'){
			Memoj=0;
			for(unsigned int j=1; j<=size_proteine; j++){
				Memoi[j]=max(N[i-1][j]-gap_open_penalty,Memoi[j])-gap_extension_penaly; //vecteur fixe
				Memoj=max(N[i][j-1]-gap_open_penalty,Memoj)-gap_extension_penaly; //faire le max nous même
				allignement=N[i-1][j-1]+bl_final[sequence_binnaire[j-1]][buffer[pos]];
				score=max(max(max(Memoi[j],Memoj),allignement),0);
				N[i][j]=score;
				if(score>maxval){
					maxval=score;
				}
			}
			i++;
			pos++;
		}
		if(maxval>maxtot){
		    res = pthread_mutex_lock (&mutex);
			if (res != 0){
				perror ("Impossible de verrouiller la zone mémoire: ");
				pthread_exit (NULL);
			}
			prot->insert(pair <int,int> (maxval,pos+1));	
			if(prot->size()>10){
				prot->erase(prot->begin()); 	
				maxtot=prot->begin()->first;
			}
		    pthread_mutex_unlock (&mutex);
		}
		pos++;
	}
	for(int i = 0; i < abc; ++i){delete N[i];}
	delete N;
    pthread_exit (NULL);
}

int main (int argc, char* argv[]){
	if (argc<3||argc>6){ //si le nombre d'arguments est mauvais
		cout << "Nombre d'arguments invalides" << endl;
		exit(1);
	}
	char* blosum_file="BLOSUM62.txt";
	int gap_open_penalty=11;
	int gap_extension_penaly=1;
	if(argc>=4){blosum_file=argv[3];
	 if(argc>=5){gap_open_penalty=atoi(argv[4]);
		if(argc>=6){gap_extension_penaly=atoi(argv[5]);}}}
	Txt rTxt(argv[1]);
	int size_proteine=rTxt.getsequence_lenght();
	char* sequence_binnaire=new char[size_proteine];
	rTxt.translate_to_binary(sequence_binnaire);
	Pin rpin(argv[2]);
	int maxlenght=rpin.get_maxlength();
	int bl_final [28][28]{0};
	Blosum rBlosum(blosum_file);
	rBlosum.get_blosum(bl_final);
	Psq rpsq(argv[2]);
	rpsq.rsize_psq();
	char *buffer;
	int lSize=rpsq.get_size();
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
	rpsq.read_psq(buffer);
	int N_thread=thread::hardware_concurrency();
	pthread_t threads[N_thread];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	multimap <int,int> *prot=new multimap <int,int>();
	datat data[N_thread];
	int ret_val=0;
	for (int i=0; i<N_thread;i++){
		data[i].size_proteine=size_proteine;
		data[i].prot=prot;
		data[i].mutex=mutex;
		data[i].buffer=buffer;
		for(int j=0;j<28;j++){
			for(int u=0;u<28;u++){
				data[i].bl_final[j][u]=bl_final[j][u];
			}
		}
		data[i].borne_inf=i*lSize/N_thread;
		data[i].borne_sup=(i+1)*lSize/N_thread;
		data[i].gap_open_penalty=gap_open_penalty;
		data[i].gap_extension_penaly=gap_extension_penaly;
		data[i].maxlenght=maxlenght;
		data[i].sequence_binnaire=sequence_binnaire;
	    ret_val = pthread_create (&threads[i], NULL, parcourire_buffer, &data[i]);
		if (ret_val != 0){
			fprintf (stderr, "Création du thread: %s\n", strerror (ret_val));
			return EXIT_FAILURE;
		}
	}
	for (int i=0; i<N_thread;i++){
		pthread_join(threads[i], NULL);
	}
    ret_val = pthread_mutex_lock (&mutex);
    if (ret_val != 0){
        perror ("Main: mutex lock erreur ");
        return EXIT_FAILURE;
    }
    pthread_mutex_unlock (&mutex);
	Phr rphr(argv[2]);	
	string seq(rTxt.get_sequence().data());
	ofstream f ("./result.txt");
	if (!f.is_open()){
		cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
		exit(1);
	}
	
	f << "Version du fichier : " << rpin.get_version() << endl;
	f << "Type de database : " << rpin.get_typedb() << endl;
	f << "Title : " << rpin.get_title() << endl;
	f << "Titlestamp : " << rpin.get_titlestamp() << endl;
	f << "Nombre de protéines dans la database : " << rpin.get_nbreprot() << endl;
	f << "Taille de la plus grande séquence : " << rpin.get_maxlength() << endl;
	for (auto itr = --prot->end(); itr != --prot->begin(); itr--){
		rphr.read_phr(rpin.get_offsetphr(itr->second));
		f << "Score : " << itr->first << "   Name : " << rphr.get_name() << endl;
		trace_back(itr->second,sequence_binnaire, bl_final,rTxt.getsequence_lenght(), f,buffer,maxlenght,gap_open_penalty,gap_extension_penaly);
		f << endl;
	}
	f.close();
	delete sequence_binnaire;
	delete prot;
	free(buffer);
	return 0;
}
