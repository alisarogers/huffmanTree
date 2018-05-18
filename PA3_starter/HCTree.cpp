#ifndef HCTREE_CPP
#define HCTREE_CPP
#include "HCTree.h"

using namespace std;


    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs) {
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> minHeap;


	HCNode * smallerNode;
	HCNode * largerNode;
	HCNode * currNode;
	HCNode * parentNode;	
	HCTree* tree = new HCTree();

	for (int i = 0; i < this->leaves.size(); ++i) {
		if(freqs[i] > 0) {
			minHeap.push(new HCNode(freqs[i], i));
		}
	}
	
	while (minHeap.size() != 1) {
		smallerNode = minHeap.top();
		minHeap.pop();
		
		largerNode = minHeap.top();
		minHeap.pop();

		parentNode = new HCNode(smallerNode->count + largerNode->count, smallerNode->symbol, smallerNode, largerNode, 0);
	
		minHeap.push(parentNode);

	}

	this->root = minHeap.top();

}





/*
//	* insert things into buildQueue, highest priority first*
	while(!copy.empty())
	{
		currNode = HCNode(freqs[i], i);
		tree->leaves[i] = &currNode;
		i++;
		minHeap.push(&currNode);
		//popping for a vector
	//	vector<int>::const_iterator it = freqs.begin();
		copy.erase(copy.begin());
	}



	* extract the two smallest, add them together, reinsert into the minHeap until there's only one left *
	while(minHeap.size() > 1) {
		smallerNode = HCNode(minHeap.top()->count, minHeap.top()->symbol);
		minHeap.pop();
		largerNode = HCNode(minHeap.top()->count, minHeap.top()->symbol);
		minHeap.pop();
		parentNode = HCNode(smallerNode.count + largerNode.count, 0, &smallerNode, &largerNode, NULL);
		minHeap.push(&parentNode);
	}
	
	tree->root = (HCNode*)&minHeap.top();
    }
*/
    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     
     */
  
    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void HCTree::encode(byte symbol, ofstream& out) const 
    {
	int freq = 0;
	int i = 0;
	/* go through the leaves vector, find the leaf containing the
	 * symbol, get that frequency, then we search starting at the
	 * root of the tree for that frequency */
	while(i < this->leaves.size()) {
		if (this->leaves[i]) {
			if (this->leaves[i]->symbol = symbol) {
				freq = this->leaves[i]->count;
				break;
			} else { 
				i++;
			}
		}
		i++;
	} 
	
	if(freq = 0) { return; }

	/* i think we just travel the tree looking for the symbol
	 * and if we go left, print 0, and if we go right, print 1
	*/

	HCNode* currNode = HCTree::root;
	
	while(currNode)
	{ 
		if(currNode->symbol = symbol)
		{
			return;
		} else if(currNode->c0->symbol = symbol)
		{
			//print 0;
			out << 0;
			return;
		}
		else if(currNode->c0->symbol < symbol)
		{
			//print 0;
			out << 1;
			currNode = currNode->c1;
		}
		else if(symbol < currNode->c0->symbol)
		{
			//print 1;
			currNode = currNode->c0;
		}
	}

    }


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
   // int decode(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     T
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
	
    int HCTree::decode(ifstream& in) const {
	/* read in the bits, travel down the tree going left if it is
	 * 0 and right if 1. when we reach a symbol, return that symbol		*/

	HCNode* currNode = this->root;

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

    }

#endif //HCTREE_CPP
