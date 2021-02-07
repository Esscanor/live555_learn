// Generic Hash Table
// Implementation

#include "HashTable.hh"

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

HashTable::Iterator::Iterator()
{
}

HashTable::Iterator::~Iterator() 
{ 
}

void *HashTable::RemoveNext()
{
    Iterator *iter = Iterator::create(*this);
    char const *key;
    void *removedValue = iter->next(key);
    if (removedValue != 0) Remove(key);

    delete iter;
    return removedValue;
}
