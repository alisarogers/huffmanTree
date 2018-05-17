/* uncompress needs to read the contents of the file named by its first command line arg, which is a file that was created by compress
 then use the contents of that file to reconstruct the original, uncompressed version, and write it to a file given by second command line arg
1. open the input file for reading
2. read the file header at the beginning of the input file and reconstruct the Huffman coding tree
3. Open the output file for writing
4. use the coding tree, decode the bits from input file to the appropriate sequence of bytes, writing to output file
5. close input and output files

*/
