#include <iostream>
#include <fstream>
#include <string>

// Static structures

struct Token {
	int count;
	std::string word;
};

// Data

Token* vocabulary = new Token[10000];
std::string* stopWords = new std::string[200];
int rowsOnPage = 45;
std::string fileName = "file.txt";
std::string stopWordsFileName = "stopWords.txt";

// Code

int main() {
	std::fstream inFile(fileName);
	std::fstream stopWordsInFile(stopWordsFileName);
	std::string line = "";
	std::string word = "";
	bool isStopWord = false;
	int topN = 0;
	int wordPosition = -1;
	int wordsCount = 0;
	int stopWordsCount = 0;
	int wordToPrint = 0;
	int out = 0;
	int in = 0;
	int j;
	int i;

	std::cout << "How many words you want to be printed?" << std::endl;
	std::cin >> topN;

	if (!inFile.is_open())
		std::cout << "Failed to open file" << std::endl; 
	if (!stopWordsInFile.is_open())
		std::cout << "Failed to open file" << std::endl;

	/***************
	* MAIN SEGMENT *
	***************/
	
Reading: // reading file line by line
	i = 0;
	if (!std::getline(inFile, line)) goto _Reading;
	
	word = "";
	goto ParsingLine;
	_ParsingLine:

	goto Reading;
_Reading:

ReadingStopWords: // reading stop words from file
	if (!std::getline(stopWordsInFile, line)) goto _ReadingStopWords;
	stopWords[stopWordsCount] = line;
	stopWordsCount++;
	goto ReadingStopWords;
_ReadingStopWords:

Sorting: // Sorting vocabulary
OutterLoop:
	in = 1;
InnerLoop:
	if (vocabulary[in - 1].count < vocabulary[in].count)
	{
		Token temp = vocabulary[in - 1];
		vocabulary[in - 1] = vocabulary[in];
		vocabulary[in] = temp;
	}
	in++;
	if (in < wordsCount - out) goto InnerLoop;
	out++;
	if (out < wordsCount - 1) goto OutterLoop;
_Sorting:
	
PrintingResult: // printing resulting tokens: "word - ???"
	wordToPrint++;
	isStopWord = false;
	i = 0;
	goto CheckStopWord;
	_CheckStopWord:

	if (!isStopWord)
	{
		topN--;
		std::cout << vocabulary[wordToPrint].word << " - " << vocabulary[wordToPrint].count << std::endl;
	}

	if (wordToPrint < wordsCount && topN) goto PrintingResult;
_PrintingResult:

	inFile.close();
	stopWordsInFile.close();

	return 0;

	/********************************************
	* CODE PARTS THAT WE CALL FROM MAIN SEGMENT *
	********************************************/
	
ParsingLine: // parsing read line to words
	if (line[i] >= 'A' && line[i] <= 'Z') {
		word.push_back(line[i] + 32);
	}
	else if (line[i] >= 'a' && line[i] <= 'z' || (line[i] == '-' || line[i] == '\'') && word.size() != 0) {
		word.push_back(line[i]);
	}
	else if ((line[i] == ' ' || line[i] == ',' || line[i] == '.' || i == line.size()-1) && !word.empty()) {
		
		goto UpdatingVocabulary;
		_UpdatingVocabulary:
		word = "";
	}
	i++;
	if (i < line.size()) goto ParsingLine;
	goto _ParsingLine;

UpdatingVocabulary: // adding new or updating existing word count
	wordPosition = -1;
	goto findWord;
	_findWord:
	if (wordPosition == -1){
		vocabulary[wordsCount] = {1, word};
		wordsCount++;
	}
	else {
		vocabulary[wordPosition].count++;
	}
	goto _UpdatingVocabulary;

findWord: // searching for word in vocabulary
	j = 0;
	loop:
		if (vocabulary[j].word == word) {
			wordPosition = j;
			j = wordsCount;
		}
		j++;
		if (j < wordsCount) goto loop;
	goto _findWord;

CheckStopWord: // Check if word is not a stop word before printing it
	if (vocabulary[wordToPrint].word == stopWords[i])
	{
		isStopWord = true;
		goto _CheckStopWord;
	}
	i++;
	if (i < stopWordsCount) goto CheckStopWord;
	goto _CheckStopWord;
}