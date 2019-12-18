Here is a program to find the correspondance between 2 proteins using a data base and a blosum matrix.
The algorithm used to perform this search of correspondance is the Smith Waterman algorithm.
Here is an example on how to launch the program : 
type "make", and then "./main ./P00533.fasta ./uniprot_sprot.fasta ./BLOSUM62.txt"
- ./P00533.fasta is the protein that you want to compare, the query
- ./uniprot_sprot.fasta is the data base
- ./BLOSUM62.txt is a text file of a blosum matrix (need to correspond to the NCBI blosum matrix format)
The program uses Parallel Execution.
The result is store in a text file name "result.txt",
This file contains the name, the raw score and the best alignment for the top 10 best correspondances between the query and a protein of the database;
some general informations about the data base are also presented in the file. 
By default,the code is using the blossum62 matrix, a « gap_open » penalty of 11 and a « gap_extension » penalty of 1*lengthofthegap but the user is able to modify the blosum matrix or the penalty attributed to a gap, to do that three arguments must be added in the main() function :
- argv[3] to change the blossum matrix
- argv[4] to change the gap_open
- argv[5] to change the gap_extension
There are various versions of the code: 
- one in which the functions "trace_back" and "parcourire_buffer" are directly placed in the main, another exists in which the functions are placed in a class (but it is slower).
- one adapted for machine with only one core, this code doesn't use threads.
- one adapted for machine with several cores, using threads (a mutex has been implemented too).


