// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.

#include "SymbolTable.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


  // This class does the real work of the implementation.

class SymbolTableImpl
{
  public:
    SymbolTableImpl();
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
  private:
    unsigned int hashFunction(string key) const;
    unsigned int castrateHashValue(int hashValue) const;
    int numberOfBuckets;
    void increaseCapacity();
    
    
    struct itemToStore
    {
        int lineNumber;
        string declarationName;
        int scope;
        itemToStore* nextItem;
    };
    
    vector<itemToStore*> hashTable;
    int currentScope;
    int timesScopeEntered;
    int timesScopeExited;
    int numOfItems;
};

SymbolTableImpl::SymbolTableImpl()
: currentScope(0), numOfItems(0), timesScopeEntered(0), timesScopeExited(0), numberOfBuckets(10000)
{
    hashTable.resize(numberOfBuckets);
}

unsigned int SymbolTableImpl::castrateHashValue(int hashValue) const
{
    int shortenedHashIndex = hashValue % 10000;
    return shortenedHashIndex;
}

unsigned int SymbolTableImpl::hashFunction(string key) const
{
    
    // FNV hash algorithm
    unsigned int h=2166136261;
	for (int k=0; k!= key.size(); k++)
	{
		h+=key[k];
		h *= 16777619;
	}
    int returnThisValue = castrateHashValue(h);
    
	return abs(returnThisValue);
}


void SymbolTableImpl::enterScope()
{
    currentScope++;
    timesScopeEntered++;
}


bool SymbolTableImpl::exitScope()
{
    if (currentScope == 0 || (timesScopeEntered < timesScopeExited))
    {
        return false;
    }
    if (timesScopeEntered < timesScopeExited)
    {
        return false;
    }
      // Remove the scope entry marker itself.
    int n = numberOfBuckets;
    while (n != 0)
    {
        if (hashTable[n] != nullptr && hashTable[n]->scope == currentScope)
        {
            itemToStore* buffer = hashTable[n]->nextItem;
            delete hashTable[n];
            hashTable[n] = buffer;
        }
        n--;
    }

    currentScope--;
    timesScopeExited++;
    return true;
}

bool SymbolTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
    {
        return false;
    }
    

    int hashValue = hashFunction(id); // capture the hash index of current string
    
    itemToStore* p = new itemToStore;
    p->lineNumber = lineNum;
    p->scope = currentScope;
    p->declarationName = id;
    p->nextItem = nullptr;

    ///// SPECIAL CASES /////
    
    // IF SLOT IS EMPTY //
    
    if (hashTable[hashValue] == nullptr)
    {
        hashTable[hashValue] = p;
        numOfItems++;
        return true;
    }
    
    // IF SLOT IS OCCUPIED, BUT PLACEMENT IS NECESSARY //
    
    if (hashTable[hashValue]->declarationName == id &&
        hashTable[hashValue]->scope != currentScope)
    {
        p->nextItem = hashTable[hashValue];
        hashTable[hashValue] = p;
        numOfItems++;
        return true;
    }
    
    // IF IDENTICAL ITEM ALREADY EXISTS //
    if (hashTable[hashValue]->declarationName == id &&
        hashTable[hashValue]->scope == currentScope &&
        hashTable[hashValue]->lineNumber==lineNum)
    {
        return false;
    }
    return false;
}

int SymbolTableImpl::find(const string& id) const
{
    if (id.empty())
        return -1;

      // Search back for the most recent declaration still
      // available.
    int hashValue = hashFunction(id);
    if (hashTable[hashValue] == nullptr || hashTable[hashValue]->declarationName != id)
    {
        return -1;
    }
    itemToStore* traveler = hashTable[hashValue];
    
    if (hashTable[hashValue]->declarationName == id)
    {
        while (traveler->nextItem!=nullptr)
        {
            if (hashTable[hashValue]->scope <= currentScope)
            {
                return hashTable[hashValue]->lineNumber;
            }
            else
            {
                traveler = traveler->nextItem;
            }
        }
        return hashTable[hashValue]->lineNumber;
    }
    return -1;
}

//*********** SymbolTable functions **************

// For the most part, these functions simply delegate to SymbolTableImpl's
// functions.

SymbolTable::SymbolTable()
{
    m_impl = new SymbolTableImpl;
}

SymbolTable::~SymbolTable()
{
    delete m_impl;
}

void SymbolTable::enterScope()
{
    m_impl->enterScope();
}

bool SymbolTable::exitScope()
{
    return m_impl->exitScope();
}

bool SymbolTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int SymbolTable::find(const string& id) const
{
    return m_impl->find(id);
}
