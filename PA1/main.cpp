#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unordered_map>
#include "QuadraticHashTable.h"
#include "SimpleStringHasher.h"
#include "StringSplitter.h"
using namespace std;

int main(int argc, char *argv[])
{
	//open file for writing
	ofstream output_file{ "output.txt" };

	//how to loop through command-line arguments
	for (int i = 1; i < argc; i++)
	{
		cout << argv[i] << endl;
		output_file << argv[i] << endl;
	}
}