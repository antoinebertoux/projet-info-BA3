all: main.cpp Blosum.o Txt.o Psq.o Pin.o Phr.o 
	g++ Blosum.o Txt.o Psq.o Pin.o Phr.o main.cpp -o main -Ofast -s 
	time ./main ./P00533.fasta ./newE.fasta ./BLOSUM62.txt

Blosum.o: Blosum.cpp
	g++ -c Blosum.cpp

Txt.o: Txt.cpp
	g++ -c Txt.cpp
	
Psq.o: Psq.cpp
	g++ -c Psq.cpp
	
Pin.o: Pin.cpp
	g++ -c Pin.cpp
	
Phr.o: Phr.cpp
	g++ -c Phr.cpp

	
clean :
	rm*.o
	#time ./main ./Ptest.fasta ./dbtest.fasta.psq  ./dbtest.fasta.pin  ./dbtest.fasta.phr
	#time ./main ./P00533.fasta.txt uniprot_sprot.fasta.psq uniprot_sprot.fasta.pin uniprot_sprot.fasta.phr
    #5957
