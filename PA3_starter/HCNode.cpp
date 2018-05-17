#include "HCTree.h"
#include "HCNode.h"

typedef unsigned char byte;

using namespace std;


  HCNode(int ct, byte sym, HCNode* left, HCNode* right, HCNode* parent) {
	count = ct;
	symbol = sym;
	c0 = left;
	c1 = right;
	p = parent;
}

#endif // HCNODE_CPP
