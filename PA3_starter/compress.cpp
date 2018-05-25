#include <iostream>
#include <fstream>
#include <vector>

#include "HCTree.h"
//#include "HCTree.cpp"
#include "HCNode.h"
//#include "HCNode.cpp"

using namespace std;
/*  compress.cpp needs to create a Huffman tree, read in a text file, encode it, insert it into the tree, and then write to a new file the encoding.
1. Open input file for reading
2. Read bytes from the file. Count the number of occurences of each byte value (put it in freqs[i]. Close the file.
3. Use the byte counts to construct a Huffman coding tree (CALL BUILD)
4. Open the output file for writing
5. Write enough information "file header" to the output file to enable the coding tree to be reconstructed when the file is read by uncompress.
6. Open input file for reading, again
7. Using the huffman coding tree, translate each byte from the input file into its code and append these codes as a sequence of bits to the output file after the header. 
8. close the input and output files
called by ./compress infile outfile
FILE HEADER FOR CHECKPOINT:
a sequence of 256 integers at the beginning of the compressed file.
each line contains a single int written as plain text
*/

int main (int argc, char** argv)
{
	ifstream toCompress;
	vector<int> freqs = vector<int>(256, 0);

/*	vector<int> * freqs = new vector<int>;
	for(int j = 0; j < 256; ++j) {
		freqs->push_back(0);
	}	
*/
	int i;
	toCompress.open(argv[1]);
///	toCompress.seekg (0, toCompress.end);
//	int endOfFile = toCompress.tellg();
//	toCompress.seekg (0, toCompress.beg);
//	char * buffer = new char[endOfFile];
//	toCompress.read(buffer, endOfFile);
/*	if(toCompress.is_open())
	{
		for(i = 0; i < endOfFile; i++)
		{
				//toCompress.read(buffer, 8);
			freqs[buffer[i]]++;
			cout<<buffer[i]<<"  "<<freqs[buffer[i]]<<endl;
		}
	}
*/
	if(toCompress.gcount() == 0) { return 1; }
	
	char read;
	
	/* increases the frequency of each byte every time it occurs */
	while(toCompress.get(read)){
//		toCompress.get(read);
		freqs[(int)read] = freqs[(int)read] + 1;
	}

	/* close the input file*/	
	toCompress.close();

	/* call BUILD */
	HCTree* tree = new HCTree();
	
	tree->build(freqs);

	ofstream toWrite;
	toWrite.open(argv[2]);
	
	/* writes each frequency to a line of its own for the file header	*/
	if(toWrite.is_open()) {
		for(int i = 0; i < freqs.size(); i++) {
			toWrite << freqs[i] << endl;

		}
	}

	/* open the compressing file again*/
	
	toCompress.open(argv[1]);
	toCompress.seekg (0, toCompress.beg);

	/*7. Using the huffman coding tree, translate each byte from 
	 * the input file into its code and append these codes as a 
	 * sequence of bits to the output file after the header. 
	 */
	
	while(toCompress.get(read)){
//		toCompress.get(read);
		tree->encode(read, toWrite);
	}
	
	toCompress.close();
	toWrite.close();

}