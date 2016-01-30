#ifndef HASHER_FACTORY_H
#define HASHER_FACTORY_H

#include "SimpleStringHasher.h"
#include "StudentHasher.h"

class HasherFactory
{
public:

	template <typename HashType>
	static HasherBase<HashType> *copyHasher(HasherBase<HashType> &to_copy)
	{
		if (typeid(to_copy) == typeid(SimpleStringHasher{}))
		{
			return new SimpleStringHasher{};
		}
		else if (typeid(to_copy) == typeid(StudentHasher{}))
		{
			return new StudentHasher{};
		}
		return new SimpleStringHasher{};
	}
};

#endif