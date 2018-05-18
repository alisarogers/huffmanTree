#ifndef HCTREE_CPP
#define HCTREE_CPP
#include "HCTree.h"
#include <string>
#include <algorithm>
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
			leaves[i] = new HCNode(freqs[i], i);
			minHeap.push(leaves[i]);
		}
	}
	
	while (minHeap.size() != 1) {
		smallerNode = minHeap.top();
		minHeap.pop();
		
		largerNode = minHeap.top();
		minHeap.pop();

		parentNode = new HCNode(smallerNode->count + largerNode->count, smallerNode->symbol, smallerNode, largerNode, 0);
		smallerNode->p = parentNode;
		largerNode->p = parentNode;
	
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
	int checkFreq = 0;
	int i = 0;	
	string str;
	HCNode * checkNode;
	/* go through the leaves vector, find the leaf containing the
	 * symbol, get that frequency, then we search starting at the
	 * root of the tree for that frequency */
	while(i < this->leaves.size()) {
		if (this->leaves[i]) {
			if (this->leaves[i]->symbol == symbol) {
				checkNode = this->leaves[i];
				break;
			} else { 
				i++;
			}
		}
		i++;
	} 
	
	if(checkNode == 0) { return; }

	/* i think we just travel the tree lookin`g for the symbol
	 * and if we go left, print 0, and if we go right, print 1
	*/

	HCNode* currNode = checkNode;

	while(currNode->p) {
		if(currNode->p->c0 == currNode) {
			//use 0
			str.append("0");
		} else {
			//use 1
			str.append("1");
		}
		currNode = currNode->p;

	}

	reverse(str.begin(), str.end());		

	out << str;
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
	
    string HCTree::decode(ifstream& in) const {
	/* read in the bits, travel down the tree going left if it is
	 * 0 and right if 1. when we reach a symbol, return that symbol		*/

	HCNode* currNode = this->root;
	string str;
	char c;
	if(!(currNode->c0 || currNode->c1)) {
		str.push_back(currNode->symbol);
		currNode = this->root;
	}
	
	while(in.get(c)) {	
		if(!currNode) { break; }
		c = c-48;
		if (c == 1) 
		{
			currNode = currNode->c1;
		} else if (c == 0)
		{	
			currNode = currNode->c0;
		}
		if(!(currNode->c0 || currNode->c1)) {
			str.push_back(currNode->symbol);
			currNode = this->root;
		}
	}
	return str;

    }

#endif //HCTREE_CPP
