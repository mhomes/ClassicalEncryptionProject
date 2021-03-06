// ClassicalEncryptionProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;
const int ARRAYSIZE = 128;

void characterCount(char ch, int list[]);
void calcShift(int& shift, int list[]);
void writeOutput(ifstream &in, ofstream &out, int shift);

int main()
{
	int asciiCode = 0,
		shift = 0;
	char ch;
	string inputFileName;
	ifstream inputFile;
	ofstream outputFile;
	string reply;

	//Open input file
	cout << "Input file name: ";
	getline(cin, inputFileName);
	inputFile.open(inputFileName.c_str());

	if (!inputFile.is_open()) {
		cout << "Unable to open file or it doesn't exist." << endl;
		return 1;
	}

	//output file
	cout << "Output file name: ";
	getline(cin, inputFileName);
	outputFile.open(inputFileName.c_str());
	int list[ARRAYSIZE] = { 0 };
	while (inputFile.peek() != EOF)
	{
		inputFile.get(ch);
		characterCount(ch, list);
	}
	inputFile.clear();
	inputFile.seekg(0);
	calcShift(shift, list); //Calculate the shift based on the <strong class="highlight">most</strong> characters counted
	writeOutput(inputFile, outputFile, shift); //Decypher and write to the other document
	inputFile.close();
	outputFile.close();
	cout << "Press enter to continue...";
	getline(cin, reply);
	return 0;
}

void characterCount(char ch, int list[])
{
	if (ch >= 'A' && ch <= 'z') //If the character is in the alphabet...
	{
		int asciiCode = 0;
		asciiCode = static_cast<int>(ch); //Change it to the ASCII number
		list[asciiCode]++; //And note it on the array
	}
}

void calcShift(int& shift, int list[])
{

	int maxIndex = 0; //Asuming that list[0] is the largest
	for (int i = 1; i < ARRAYSIZE; i++)
	{
		if (list[maxIndex] < list[i])
			maxIndex = i; //If this is true, change the largest index
	}

	if (maxIndex >= 'A' && maxIndex <= 'Z') //Calculate shift for for upper-case letters
		shift = 'E' - maxIndex;

	if (maxIndex >= 'a' && maxIndex <= 'z') //For lower-case letters 
		shift = 'e' - maxIndex;


	cout << "Most frequent letter is " << shift << endl;
}

void writeOutput(ifstream &inputFile, ofstream &outputFile, int shift)
{
	char ch;
	while (inputFile.peek() != EOF) { //Until it is the end of the file...
		inputFile.get(ch); //Get the next character
		if (ch >= 'A' && ch <= 'Z') //If the character is in the alphabet...
		{
			ch = 'A' + (((ch - 'A') + shift + 26) % 26);
		}
		if (ch >= 'a' && ch <= 'z') //If the character is in the alphabet...
		{
			ch = 'a' + (((ch - 'a') + shift + 26) % 26);
		}

		outputFile << ch; //Print to the outfile
	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
