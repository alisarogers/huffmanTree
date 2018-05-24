/* dummy file */
#include <iostream>

class BitOutputStream {

private:
	char buf;	//one byte buffer of bits
	int nbits;	//how many bits have been written
	std::ostream & out; //reference to the output stream to use

public:
	
	/** Initialize a BitOutputStream that will use the given
	 * ostream for output.
	 */
	BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
	//clear buffer and bit counter
	}
	
	/** send the buffer to the output, and clear it */
	void flush () {
		out.put(buf);
		out.flush();
		buf = nbits = 0;
	}

	/** Write the least signfiicant bit of the argument to the bit
	 * buffer, and increment the bit buffer index. but flush the 
	 * buffer first, if it is full */
	void writeBit(int i) {
		// is the bit buffer full? Then flush it

		// write the least significant bit of i into the buffer
		// at the current index


		//increment the index
	}
}
