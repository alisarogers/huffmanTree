#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "HCTree.h"
#include "HCNode.h"

using namespace std;
/* uncompress needs to read the contents of the file named by its first command line arg, which is a file that was created by compress
 then use the contents of that file to reconstruct the original, uncompressed version, and write it to a file given by second command line arg
1. open the input file for reading
2. read the file header at the beginning of the input file and reconstruct the Huffman coding tree
3. Open the output file for writing
4. use the coding tree, decode the bits from input file to the appropriate sequence of bytes, writing to output file
5. close input and output files

*/

int main(int argc, char** argv) {

	ifstream readIn;
	vector<int> freqs = vector<int>(256, 0);
	
	/**1. open the input file for reading*/
	readIn.open(argv[1], ios::binary);
	
 	int length = 0;
 	if(readIn) {
     
		readIn.seekg(0, readIn.end);
		length = readIn.tellg();
		readIn.seekg(0, readIn.beg);
    	}
 	if(length == 0)
 	{ 
		readIn.close();
		ofstream toWrite;
		toWrite.open(argv[2], ios::binary);
		toWrite.close();
 		return 1;
	}
 

	BitInputStream * bitRead = new BitInputStream(readIn);
	string read;
	int i = 0;
	/* read the file header, store in freqs*/
	while( i < freqs.size()) {
		getline(readIn, read);
			freqs[i] = stoi(read);
			i++;
	}

	/* get the total chars*/
	getline(readIn, read);
	int totalChars = stoi(read);

	/*reconstruct the Huffman coding tree*/
	HCTree* tree = new HCTree();
	tree->build(freqs);

	/* open the output file for writing*/
	ofstream toWrite;
	toWrite.open(argv[2], ios::binary);

	HCNode* currNode = tree->root;
	

	toWrite << tree->decode(*bitRead, totalChars);


}
