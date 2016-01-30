#ifndef STUDENT_HASHER_H
#define STUDENT_HASHER_H


#include "HasherBase.h"
#include <string>
using namespace std;

class StudentHasher : public HasherBase<string>
{
	virtual int getHash(const string &item, int mod_by)
	{
		//MA #4 TODO: IMPLEMENT! 
		return 0;
	}

};
#endif
