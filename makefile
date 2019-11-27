all: main.cpp Protein.cpp Pin.cpp Phr.cpp
	g++ -o main Protein.cpp Pin.cpp Phr.cpp main.cpp
	./main P00533.fasta uniprot_sprot.fasta.psq  uniprot_sprot.fasta.pin  uniprot_sprot.fasta.phr
Protein.o: Protein.cpp
	g++ -c Protein.cpp
clean :
	rm*.o
