#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include "HashTableBase.h"

template <typename Key, typename Value>
class LinearHashTable : public HashTableBase<Key, Value>
{
protected:

	//because we're doing a linear probe, we simply increment our hash by one.
	//In other collision resolution techniques, we may want to change this
	//behavior, which is why I've declared the fuction virtual.
	virtual int getNextProbe(int starting_hash)
	{
		return (starting_hash + 1) % _items.size();
	}

	//Not really used for linear probing, but might be helpful for other 
	//probing techniques.
	virtual int getNextProbe(int starting_hash, int probe_count)
	{
		return getNextProbe(starting_hash);
	}

	//determines whether or not we need to resize
	//to turn off resize, just always return false
	virtual bool needsResize()
	{
		//linear probing seems to get worse after a load factor of about 70%
		if (_number_of_elements > (.7 * _primes[_local_prime_index]))
		{
			return true;
		}
		return false;
	}

	//called to check to see if we need to resize
	virtual void resizeCheck()
	{
		//Right now, resize when load factor > .75; it might be worth it to experiemnt with 
		//this value for different kinds of hashtables
		if (needsResize())
		{
			_local_prime_index++;

			HasherBase<Key> *hasher = HasherFactory::copyHasher<Key>(*_hasher);
			LinearHashTable<Key, Value> new_hash{ hasher, _primes[_local_prime_index] };

			for (auto item : _items)
			{
				if (item.isEmpty() == false)
				{
					//add to new hash table 
					new_hash.addElement(item.getKey(), item.getValue());
				}
			}

			//MOVE IS COOL!
			*this = move(new_hash);
		}
	}

public:

	LinearHashTable(HasherBase<Key> *hasher, int number_of_elements = 11)
		: HashTableBase(hasher, number_of_elements)
	{

	}

	LinearHashTable(LinearHashTable<Key, Value> &other)
		: HashTableBase(other)
	{

	}

	LinearHashTable(LinearHashTable<Key, Value> &&other)
		: HashTableBase(other)
	{

	}

	LinearHashTable & operator=(LinearHashTable<Key, Value> &other)
	{
		HashTableBase::operator=(other);
		return *this;
	}

	LinearHashTable & operator=(LinearHashTable<Key, Value> &&other)
	{
		HashTableBase::operator=(other);
		return *this;
	}

	//concrete implementation for parent's addElement method
	virtual void addElement(const Key &key, const Value &value)
	{
		//check for size restrictions
		resizeCheck();

		//calculate hash based on key
		int hash = HashTableBase::getHash(key);

		//loop until we find an empty spot
		HashItem<Key, Value> *slot = &_items[hash];
		int probe_count = 1;
		int loop_counter = 0;
		while (slot->isEmpty() == false && slot->getKey() != key)
		{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot = &_items[hash];
			probe_count++;
		}

		//move operator -- should be faster!
		_items[hash] = HashItem<Key, Value>{ key, value, false };

		//remember how many things we're presently storing
		_number_of_elements++;
	}

	//removes supplied key from hash table
	virtual void removeElement(Key key)
	{
		//calculate hash
		int hash = HashTableBase::getHash(key);

		//loop until we find the slot that has our desired key
		HashItem<Key, Value> *slot = &_items[hash];
		int loop_counter = 0;
		while (slot->getKey() != key)
		{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot = &_items[hash];

			//have we cycled through our entire array of _items?
			if (loop_counter > _items.size())
			{
				throw exception("Key not found.");
			}

		}

		//reset emptiness of slot.  No need to delete actualy value.
		slot->setIsEmpty(true);
		_number_of_elements--;
	}

	//returns true if the key is contained in the hash table
	virtual bool containsElement(Key key)
	{
		int hash = HashTableBase::getHash(key);
		HashItem<Key, Value> *slot = &_items[hash];
		int loop_counter = 0;
		while (slot->getKey() != key)
		{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot = &_items[hash];

			//have we cycled through our entire array of _items?
			if (loop_counter > _items.size())
			{
				//must not be in hash table
				return false;
			}

		}

		//item found, but deleted
		if (slot->isEmpty() == true)
		{
			return false;
		}
		return true;
	}

	//returns the item pointed to by key
	virtual Value &getElement(string key)
	{
		int hash = HashTableBase::getHash(key);
		HashItem<Key, Value> *slot = &_items[hash];

		//again, we loop until we find what we're looking for.
		int loop_counter = 0;
		while (slot->getKey() != key)
		{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot = &_items[hash];

			//have we cycled through our entire array of _items?
			if (loop_counter > _items.size())
			{
				throw exception("Key not found.");
			}

		}

		//item found, but deleted
		if (slot->isEmpty() == true)
		{
			throw exception("Key not found.");
		}
		return slot->getValue();
	}
};

#endif