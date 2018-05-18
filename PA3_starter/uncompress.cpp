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
	readIn.open(argv[1]);
	string read;
	int i = 0;
	/* read the file header, store in freqs*/
	while( i < freqs.size()) {
		getline(readIn, read);
//		if(!read.equals('\n')) {
			freqs[i] = stoi(read);
			i++;
//		}
	}
	/*reconstruct the Huffman coding tree*/
	HCTree* tree = new HCTree();
	tree->build(freqs);

	/* open the output file for writing*/
	ofstream toWrite;
	toWrite.open(argv[2]);

	HCNode* currNode = tree->root;

	toWrite << tree->decode(readIn);


}
