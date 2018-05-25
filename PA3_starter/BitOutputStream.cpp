#ifndef BITOUTPUTSTREAM_CPP
#define BITOUTPUTSTREAM_CPP
#include "BitOutputStream.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void BitOutputStream::flush()
{
	out.put(buf);
	out.flush();
	buf = nbits = 0;
}

/*Use bitwise OR operation to update buff with the next bit*/
void BitOutputStream::writeBit(int bit)
{
	if(nbits == 7)
	{
		//I know we're calling flush on our BitOutputStream object, but im not sure im calling it right.
		this->flush();
	}
	//from discussion slides
	buf = buf | (bit <<(7 - nbits));

	/*update nbits so that next time writeBit is called, 
	the correct next bit is written to buff*/
	nbits++;
}

void BitOutputStream::writeByte(int byte)
{
	int i;
	for(i = 0; i < 8; i++)
	{
		writeBit(byte);
	}
}
//Purely for testing
int main(int argc, char** argv)
{
	ofstream writing;
	//int i;
	writing.open(argv[1]);


	BitOutputStream * kstream = new BitOutputStream(writing);
	//string test = "01001010";
	unsigned int i = 74;
	//for(i = 0; i < test.length(); i++){

		kstream->writeByte(i);
	//kstream->flush();
	writing.close();

	//}
}
#endif