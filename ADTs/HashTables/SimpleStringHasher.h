#ifndef SIMPLE_STRING_HASHER_H
#define SIMPLE_STRING_HASHER_H

#include "HasherBase.h"
#include <string>
using namespace std;

class SimpleStringHasher : public HasherBase<string>
{
	virtual int getHash(const string &item, int mod_by)
	{
		int hash = 0;
		for (char ch : item)
		{
			hash += ch;
		}
		return hash % mod_by;
	}
	
};
#endif
