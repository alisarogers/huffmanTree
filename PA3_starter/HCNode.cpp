#include "HCTree.h"
#include "HCNode.h"

typedef unsigned char byte;

using namespace std;


/*HCNode* HCNode(int ct, byte sym, HCNode* left, HCNode* right, HCNode* parent) {
	HCNode* newNode;
	newNode = HCNode(ct, sym, left, right, parent);
	newNode->c0 = left;
	newNode->c1 = right;
	newNode->p = parent;
*/

bool HCNode::operator<(const HCNode& other) {
	return this->count < other.count;
	}


/* HCNode * newNode(int ct, byte sym, HCNode* left, HCNode* right, HCNode *parent) {
	
	HCNode newNode;
	newNode = HCNode(ct, sym, left, right, parent);
	newNode.c0 = left;
	newNode.c1 = right;
	newNode.p = parent;
}
*/
