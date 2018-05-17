/*  compress.cpp needs to create a Huffman tree, read in a text file, encode it, insert it into the tree, and then write to a new file the encoding.
1. Open input file for reading
2. Read bytes from the file. Count the number of occurences of each byte value (put it in freqs[i]. Close the file.
3. Use the byte counts to construct a Huffman coding tree (CALL BUILD)
4. Open the output file for writing
5. Write enough information "file header" to the output file to enable the coding tree to be reconstructed when the file is read by uncompress.
6. Open input file for reading, again
7. Using the huffman coding tree, translate each byte from the input file into its code and append these codes as a sequence of bits to the output file after the header. 
8. close the input and output files

called by ./compress infile outfile

FILE HEADER FOR CHECKPOINT:
a sequence of 256 integers at the beginning of the compressed file.
each line contains a single int written as plain text

*/
