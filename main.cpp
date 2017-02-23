/*Developed By Sean Leavy

Program will take as its input a text file of any size named "input.txt" contained in the same directory
it will then create an output file named "output.txt" and print:
	- Each unique word contained in the input file.
	- The number of times that word appeared in the input file.
	- the line number and word position in that respective line for every occurrence of the word in the input file.
to the output file. This program was developed as a class project in one of my computer science elective classes called Advanced Object Oriented Programming in C++
*/

#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm> 
#include <sstream>
#include"invertedIndex.h"

using namespace std;


InvertedIndex::InvertedIndex(string input, string output)
{
	string word;
	fstream infile(input);
	ofstream outFile(output);
	int count = 0;
	vector<pair<string, int>> iIndex; //vector of pairs with word count and string value
	map<string, vector <pair<int, int> > > T;//a map containing a vector with the line and position of each word
	pair<int, int> p;
	map<string, int> m;


	//populate iIndex with each word and the number or times it appeas in the file
	while (infile >> word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower); //change all letter to lower case

		if (word.back() == '.' || word.back() == '!' || word.back() == ',' || word.back() == '?' || word.back() == ';')//delete punctuation at end of word
			word.pop_back();

		if (m.find(word) != m.end()) {
			m[word]++;
		}
		else {
			m[word] = 1;
		}

	}//while

	 //copy mapping m into iIndex
	copy(m.begin(), m.end(), back_inserter(iIndex));

	/*for (int i = 0; i < iIndex.size(); i++) {
	outFile << iIndex[i].first << " " << iIndex[i].second << endl;
	}*/
	//infile.clear();
	//infile.seekg(0, ios::beg);
	string line;
	int linecount;
	//populate wordPos with line and position of corresponding word contained at same index in iIndex
	for (int i = 0; i < iIndex.size(); i++) {
		linecount = 0;
		infile.clear();
		infile.seekg(0, ios::beg);
		int instanceCount = 0;
		while (!infile.eof()) {
			getline(infile, line);
			linecount++;
			istringstream iss(line);
			int posInLine = 0;
			while (iss >> word) {
				if (word.back() == '.' || word.back() == '!' || 
					word.back() == ',' || word.back() == '?' || 
					word.back() == ';' || word.back() == '(' || word.back()==')')//delete punctuation at end of word
					word.pop_back();
				posInLine++;
				if (iIndex[i].first == word) {
					p.first = linecount;
					p.second = posInLine;
					T[word].push_back(p);
					instanceCount++;

				}

			}//while read words in line
		}//while read lines in file
	}//for each unique word

	 /*
	 for (int i = 0; i < T["we"].size(); i++) {
	 outFile << T["we"][i].first;
	 }*/
	for (int i = 0; i < iIndex.size(); i++) {
		outFile << iIndex[i].first << " " << iIndex[i].second << " [ ";
		for (int j = 0; j < T[iIndex[i].first].size(); j++) {
			if (j != (T[iIndex[i].first].size() - 1))
				outFile << "(" << T[iIndex[i].first][j].first << "," << T[iIndex[i].first][j].second << "), ";
			else
				outFile << "(" << T[iIndex[i].first][j].first << "," << T[iIndex[i].first][j].second << ") ";
		}
		outFile << "]" << endl;
	}
}

int main() {
	InvertedIndex IVI("input.txt", "output.txt");
}