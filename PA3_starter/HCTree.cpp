#include "HCTree.h"

using namespace std;


    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs) {
	priority_queue<int, vector<int>, HCNodePtrComp> minHeap;

	int i = 0;
	HCNode* smallerNode;
	HCNode* largerNode;
	HCNode* currNode;
	HCNode* parentNode;
	/* insert things into buildQueue, highest priority first*/
	while(!freqs.empty())
	{
		currNode = (freqs[i], i);
		leaves[i] = currNode;
		i++;
		minHeap.push(currNode);
		freqs.pop();
	}


	/* extract the two smallest, add them together, reinsert into the minHeap until there's only one left */
	while(minHeap.size() > 1) {
		smallerNode = minHeap.top();
		minHeap.pop();
		largerNode = minHeap.top();
		minHeap.pop();
		parentNode = HCNode(smallerNode->count + largerNode->count, 0, smallerNode, largerNode, 0);
		minHeap.push(parentNode);
	}
	
	root = minHeap.top();
    }

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const
    {
	int freq = 0;
	/* go through the leaves vector, find the leaf containing the
	 * symbol, get that frequency, then we search starting at the
	 * root of the tree for that frequency */
	while(i < leaves.size()) {
		if leaves[i]->symbol = symbol {
			freq = leaves[i]->count;
			break;
		} else { 
			i++;
		}
	} 

	if(freq = 0) { return; }

	/* i think we just travel the tree looking for the symbol
	 * and if we go left, print 0, and if we go right, print 1
	*/

	HCNode* currNode = root;
	
	while(currNode)
	{ 
		if(currNode->symbol = symbol)
		{
			return;
		} else if(currNode->c0->symbol = symbol)
		{
			//print 0;
			return;
		}
		else if(currNode->c0->symbol < symbol)
		{
			//print 0;
			currNode = currNode->c1;
		}
		else if(symbol < currNode->c0->symbol)
		{
			//print 1;
			currNode = currNode->c0;
		}
	}

    }

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void encode(byte symbol, ofstream& out) const;


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
	HCNode* currNode = root;

	while(currNode) {
		
		if(currNode->symbol)
		{	
			return currNode->symbol;
		}
		char c = in.get();
		if (c == 1) 
		{
			currNode = currNode->c1;
		} else if (c == 0)
		{	
			currNode = currNode->c0;
		}
	}
	return 0;
	
    int decode(ifstream& in) const {
	/* read in the bits, travel down the tree going left if it is
	 * 0 and right if 1. when we reach a symbol, return that symbol		*/


    }
};

#endif // HCTREE_CPP
