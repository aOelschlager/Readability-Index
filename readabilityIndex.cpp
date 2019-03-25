/****************************************************************
   FILE:      readabiltyIndex.cpp
   AUTHOR:    Anne-Marie Oelschlager

   PURPOSE:   Program reads text file/s passed from the command line
	      to the program. It then keeps a count of each word,
	      syllable, and sentence in the file and calculates the
	      readability index of that file.
****************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using std::cout;
using std::string;
using std::endl;
using std::left;
using std::cin;
using std::setw;
using std::ifstream;
using std::ios;
using std::setprecision;

void processWord(const char*);
void calculateReadability(int, int, int);


int main(int argc, char *argv[])
   {
	// if no file name was given
	if(argc == 1)
	   {
		cout << "No file was passed" << endl;
	   }

	// loops through each filename passed to the program
	for(int i = 1; i <= (argc - 1); i++)
           {
		string fileName = argv[i];   // string that holds the name of the file
                cout << endl << fileName;
		processWord(argv[i]);
           }

	return 0;
   }

/**************************************************************
   FUNCTION: void processWord(const char*)

   ARGUMENTS: fileN - A constant pointer to a file name

   RETURNS: Nothing.

   NOTES: Function receives a file name and opens the file and then
	  it reads each word from the file. It counts the number of
	  words and checks for and counts punctuation. It then checks
	  for vowels and makes sure that the vowel is not next to
	  another vowel or at the end of the word and the letter e.
	  It counts the vowels that are valid. It then closes
	  the file.
**************************************************************/
void processWord(const char* fileN)
   {
	ifstream inFile;          // an Input file stream variable
	string word;              // a string that holds the word read from the file
	int wordCount = 0;        // an integer that holds the count of words in the file
	int syllableCount = 0;    // an integer that holds the count of syllables in the file
	int sentenceCount = 0;    // an integer that holds the count of sentances in the file

	// Declares an input file stream variable named fileN.
	inFile.open(fileN);

	// Checks to make sure the file was opened successfully.
	if (!inFile)
	   {
		cout << "Error - unable to open input file " << fileN << endl;
		exit(1);
	   }

	cout << endl;

	// Reads word from inFile.
	inFile >> word;

	// Runs loop while not at end of file.
	while (inFile)
	   {
		// counts number of words
		wordCount += 1;

		int temp = (word.length() - 1);  // integer that holds length of each word

		// check for punctuation that indicates the end of a sentence and if true it is counted
		if(word[temp] == '.' || word[temp] == ':' || word[temp] == ';' || word[temp] == '?' || word[temp] == '!')
		   {
			sentenceCount += 1;
		   }

		int count = 0;  // integer that helps keep syllable count.

		// loops through word and checks for syllables
		for(int i = 0; i < (int)word.length(); ++i)
		   {
			// true if the letter is a vowel
			if(word[i] == 'a' || word[i] == 'A' || word[i] == 'e' || word[i] == 'E' || word[i] == 'i' || word[i] == 'I' || word[i] == 'o' || word[i] == 'O' || word[i] == 'u' || word[i] == 'U')
			   {
				// true if the letter next to the vowel is a punctuation
				if(word[i +1] == '\0' || word[i +1] == '.' || word[i +1] == '?' || word[i +1] == '!' || word[i +1] == ';' || word[i +1] == ',' || word[i +1] == ':' || word[i +1] == '"' || word[i +1] == '-')
                                   {
					// is counted if the vowel is not e.
					if(!(word[i] == 'e'))
					   {
						syllableCount += 1;
                                                count += 1;
					   }
				   }
				// is counted if the vowel is not next to another vowel
				else if(!(word[i +1] == 'a' || word[i +1] == 'A' || word[i +1] == 'e' || word[i +1] == 'E' || word[i +1] == 'i' || word[i +1] == 'I' || word[i +1] == 'o' || word[i +1] == 'O' || word[i +1] == 'u' || word[i +1] == 'U'))
				   {
					syllableCount += 1;
                                        count += 1;
				   }
			   }
		   }

		// is counted if the word was not counted in the previous loop
		if(count == 0)
		   {
			syllableCount += 1;
		   }

		// Reads word from inFile.
		inFile >> word;
	   }
	// Closes the file stream.
	inFile.close();

	calculateReadability(wordCount, syllableCount, sentenceCount);
   }



/**************************************************************
   FUNCTION: void calculateReadability(int, int, int)

   ARGUMENTS: wordCount, syllableCount, sentenceCount - Intergers that store data about the words

   RETURNS: Nothing.

   NOTES: Function runs calculations on the counts kept and outputs the results.
**************************************************************/
void calculateReadability(int wordCount, int syllableCount, int sentenceCount)
   {
	double L = ((double)wordCount / sentenceCount);     // double that holds the average sentance length
        double N = ((double)syllableCount / wordCount);     // double that holds the average number of syllables per word
        double gradeL = ((L * 0.39) + (N * 11.8)) - 15.59;  // double that holds the grade level
        double readA = ((L * 0.39) + (N * 11.8)) - 10.59;   // double that holds the reading age

        cout << endl << "Grade level is: " << setprecision(4) << gradeL;
        cout << endl << "Reading Age is: " << setprecision(4) << readA << endl;
   }
