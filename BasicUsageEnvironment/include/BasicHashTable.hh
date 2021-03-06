// Basic Hash Table implementation
// C++ header

#ifndef _BASIC_HASH_TABLE_HH
#define _BASIC_HASH_TABLE_HH

#ifndef _HASH_TABLE_HH
#include "HashTable.hh"
#endif
#ifndef _NET_COMMON_H
#include <NetCommon.h> // to ensure that "uintptr_t" is defined
#endif

// A simple hash table implementation, inspired by the hash table
// implementation used in Tcl 7.6: <http://www.tcl.tk/>

#define SMALL_HASH_TABLE_SIZE 4

class BasicHashTable: public HashTable
{
private:
    class TableEntry; // forward

public:
    BasicHashTable(int keyType);
    virtual ~BasicHashTable();

    // Used to iterate through the members of the table:
    class Iterator; 
    friend class Iterator; // to make Sun's C++ compiler happy
    class Iterator: public HashTable::Iterator
    {
    public:
        Iterator(BasicHashTable &table);

    private: // implementation of inherited pure virtual functions
        void *next(char const *&key); // returns 0 if none

    private:
        BasicHashTable &fTable;     // 引用
        unsigned fNextIndex;        // index of next bucket to be enumerated after this
        TableEntry *fNextEntry;     // next entry in the current bucket  //下一个索引
    };

private: // implementation of inherited pure virtual functions
    virtual void *Add(char const *key, void *value);
    // Returns the old value if different, otherwise 0
    virtual Boolean Remove(char const *key);
    virtual void *Lookup(char const *key) const;
    // Returns 0 if not found
    virtual unsigned numEntries() const;

private:
    class TableEntry
    {
    public:
        TableEntry *fNext;   // 结点
        char const *key;     // key值
        void *value;         // Value值
    };

    // 查找键值
    TableEntry *lookupKey(char const *key, unsigned &index) const;
    // returns entry matching "key", or NULL if none
    
    //键值是否匹配
    Boolean keyMatches(char const *key1, char const *key2) const;
    // used to implement "lookupKey()"

    //插入新的结点
    TableEntry *insertNewEntry(unsigned index, char const *key);
    // creates a new entry, and inserts it in the table
    void assignKey(TableEntry *entry, char const *key);
    // used to implement "insertNewEntry()"

    void deleteEntry(unsigned index, TableEntry *entry);
    void deleteKey(TableEntry *entry);
    // used to implement "deleteEntry()"

    void rebuild(); // rebuilds the table as its size increases

    unsigned hashIndexFromKey(char const *key) const;
    // used to implement many of the routines above

    //产生一个随机的索引值
    unsigned randomIndex(uintptr_t i) const
    {
        return (unsigned)(((i * 1103515245) >> fDownShift) & fMask);
    }

private:
    TableEntry **fBuckets;                              // pointer to bucket array
    TableEntry *fStaticBuckets[SMALL_HASH_TABLE_SIZE];  // used for small tables
    unsigned fNumBuckets, fNumEntries, fRebuildSize, fDownShift, fMask;
    int fKeyType;                                       // 键值的类型
};

#endif
