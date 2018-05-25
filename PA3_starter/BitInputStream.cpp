/* dummy file */

#include "BitInputStream.h"

	void BitInputStream::fill() {
		buf = in.get();
		nbits = 0;
	}

	int BitInputStream::readBit() {

		int ret;	
		//if all bits are read, fill the buffer first
		if(nbits == 8) {
			fill();
		}

		//get the bit at the appropriate location in the bit
		//buffer, and return the appropriate int
		ret = (buf >> nbits) & 0x1;


	
		//increment the index

		nbits++;
		return ret;		
	}
