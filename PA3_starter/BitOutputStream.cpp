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
	char bit_rep = 0;
	//cout<<"Second bit:"<<bit<<endl;
	if(nbits == 8)
	{
		//I know we're calling flush on our BitOutputStream object, but im not sure im calling it right.
		this->flush();
	}
	//from discussion slides
	buf = (buf | (bit <<(7 - nbits)));
	bit_rep = (bit_rep | (bit<<(7-nbits)));
	/*idk why but this next line makes it work, for some reason it doesnt 
	  seem like buf updates correctly*/

	buf = bit_rep;
	//tests
	//cout<<"Third bit: "<<(bit <<(7 - nbits))<<endl;
	//cout<< "Char_Rep: "<<buf<< endl;



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
	//create ostream to give as argument to initialize BitOutputStream
	ostream & output = writing;


	BitOutputStream * kstream = new BitOutputStream(output);
	//string test = "01001010";
	unsigned int i = 01001010;
	//for(i = 0; i < test.length(); i++){

		kstream->writeByte(i);
	kstream->flush();
	writing.close();

	//}
}
#endif