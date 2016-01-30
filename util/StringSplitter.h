#ifndef STRINGSPLITTER_H
#define STRINGSPLITTER_H

#include <string>
#include <vector>

using namespace std;

class StringSplitter
{
public:

	//Breaks apart the supplied text based on the given delimiter
	//static function do not affect the internal state
	//(e.g. variables) of a given class instance
	static vector<string> split(string text, string delimiter)
	{
		//define where our pieces will go
		vector<string> pieces{};

		//keep track of starting location for substring
		int start = 0;

		//find the first instance of our delimiter
		int location = text.find(delimiter);

		//go until we have no more delimiters
		while (location != string::npos)
		{
			//grab next piece
			string piece = text.substr(start, location - start);

			//add to vector
			pieces.push_back(piece);

			//find next delimiter
			start = location + 1;
			location = text.find(delimiter, start);
		}

		//right here, we have a bit of text that still needs
		//to be taken care of
		string piece = text.substr(start);

		//it's possible that our final piece is empty
		//(optional, could always add the piece regardless of state)
		if (piece.length() > 0)
		{
			pieces.push_back(piece);
		}

		//finally, all done
		return pieces;
	}
};

#endif