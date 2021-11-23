/**********************************************************
 * File: HuffmanEncoding.cpp
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
Map<ext_char, int> getFrequencyTable(istream& file) {
	/* Initialise the map. */ 
	Map<ext_char, int> frequencies;
	/* Make sure no whitespace character is skipped during file analysis. */ 
	noskipws(file);
	char character;
	/* Map each file character to its amount of occurrences in the file. */ 
	while(file >> character) frequencies[character]++;
	/* Add pseudo-end-of-file to the map. */ 
	frequencies[PSEUDO_EOF] = 1;
	/* This function returns the map of frequencies. */ 
	return frequencies;	
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	/* Initialise the priority queue. */ 
	PriorityQueue<Node*> frequencyPQ;
	/* Create leaf nodes from frequency map characters and let the
	   priority queue sort them based on their frequency value. */ 
	foreach(ext_char character in frequencies){
		Node* leafNode = new Node();
		leafNode->character = character;
		leafNode->weight = frequencies[character];
		frequencyPQ.enqueue(leafNode, leafNode->weight);
	}
	/* Create the binary encoding tree using the Huffman algorithm. */ 
	while(frequencyPQ.size() != 1){
		Node* interiorNode = new Node();
		interiorNode->character = NOT_A_CHAR;
		interiorNode->zero = frequencyPQ.dequeue();
		interiorNode->one = frequencyPQ.dequeue();
		interiorNode->weight = interiorNode->zero->weight + interiorNode->one->weight; 
		frequencyPQ.enqueue(interiorNode, interiorNode->weight);
	}
	/* This function returns the root (top) node of the encoding tree. */ 
	return frequencyPQ.peek();
}

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	/* Delete the encoding tree by deleting its every node. */ 
	if(root == NULL) return;
	freeTree(root->zero);
	freeTree(root->one);
	delete root;
}

/* Function: buildEncodingMap
 * Usage: buildEncodingMap(encodingTree, encodingMap, binary);
 * --------------------------------------------------------
 * This additional function creates a map which maps characters to
 * their new binary sequences derived from the optimal binary tree.
 */ 
void buildEncodingMap(Node* encodingTree, Map<ext_char, string>& encodingMap, string binary){
	/* Assume the next character of the binary sequence to be zero. */ 
	if(encodingTree->zero != NULL){
		binary = binary + "0";
		buildEncodingMap(encodingTree->zero, encodingMap, binary);
		binary = binary.substr(0, binary.length() - 1);
	}
	/* Assume the next character of the binary sequence to be one. */
	if(encodingTree->one != NULL){
		binary = binary + "1";
		buildEncodingMap(encodingTree->one, encodingMap, binary);
		binary = binary.substr(0, binary.length() - 1);
	}
	/* If a leaf node is found then add it to the encoding map. */ 
	if(encodingTree->zero == NULL && encodingTree->one == NULL){
		encodingMap.put(encodingTree->character, binary);
	}   
}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	/* Initialise the encoding map. */ 
	string binary;
	Map<ext_char, string> encodingMap;
	buildEncodingMap(encodingTree, encodingMap, binary);
	/* Encode the source file with new binary representations. */ 
	char character;
	while(infile.get(character)){
		/* Assign regular character value to an extended type. */ 
		ext_char extendedChar = character;	
		/* Find the new binary representation and write it into the output file. */ 
		string binary = encodingMap[extendedChar];
		for(int i = 0; i < binary.length(); i++){
			outfile.writeBit(binary[i] - '0');
		}
	}
	/* Add the pseudo-end-of-file binary interpretation at the end 
	   of the output file. */ 
	for(int i = 0; i < encodingMap[PSEUDO_EOF].length(); i++){
		outfile.writeBit(encodingMap[PSEUDO_EOF][i] - '0');
	}
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	/* Assign a new node to the encoding tree root for tracing the leaf node. */ 
	Node* tracker = encodingTree;
	/* Initialise extended character type. */ 
	ext_char leafNodeChar = NULL;
	/* Declare a variable that will store one binary figure (zero or one). */ 
	int binary;
	/* Make sure no whitespace character is skipped during file analysis. */ 
	noskipws(infile);
	/* Decode file by tracing the encoding tree for leaf nodes until the leaf 
	   node is pseudo-end-of-file. */ 
	while(leafNodeChar != PSEUDO_EOF){
		binary = infile.readBit();
		if(binary == 0) tracker = tracker->zero;
		if(binary == 1) tracker = tracker->one;
		if(tracker->character == PSEUDO_EOF) break;
		leafNodeChar = tracker->character;
		if(tracker->character != NOT_A_CHAR){
			/* Assign extended type value to a regular character. */ 
			char character = (char)leafNodeChar;
			file.put(character);
			/* After finding a leaf node and adding it to the file, the tracker
			   goes back to the top (root) node of the encoding tree. */ 
			tracker = encodingTree;
		}
	}
}

/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
	/* The "summary" process of compressing the infile. */ 
	Map<ext_char, int> frequencies = getFrequencyTable(infile);
	Node* root = buildEncodingTree(frequencies);
	writeFileHeader(outfile, frequencies);
	infile.rewind();
	encodeFile(infile, root, outfile);
	freeTree(root);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
	/* The "summary" process of decompressing the outfile. */ 
	Map<ext_char, int> header = readFileHeader(infile);
	Node* root = buildEncodingTree(header);
	decodeFile(infile, root, outfile);
	freeTree(root);
}