//
//  Set.cpp
//  Project2
//
//  Created by Jonathan Woong on 4/18/14.
//  Copyright (c) 2014 CS32. All rights reserved.
//

#include "Set.h"

Set::Set()
{
    dummyNode = new Node; // does not count as 1st interesting node
    dummyNode->nextNode = NULL;
    dummyNode->previousNode = NULL;
    head = dummyNode;
    tail = dummyNode;
    totalElements=0;
}

Set::~Set()
{
    clearSet();
    head = dummyNode;
    tail = dummyNode;
}

Set::Set(const Set& sourceSet)
{
    
    ///// sourceSet.totalElements = 0 /////
    if (sourceSet.totalElements == 0)
    {
        dummyNode = new Node;
        dummyNode->nextNode = NULL;
        dummyNode->previousNode = NULL;
        head = dummyNode;
        tail = dummyNode;
        totalElements=0;
    }

    ///// sourceSet.totalElements >= 1 /////
    
    if (sourceSet.totalElements >=1)
    {
        dummyNode = new Node;
        dummyNode->nextNode = NULL;
        dummyNode->previousNode = NULL;
        head = dummyNode;
        tail = dummyNode;
        totalElements=0;
        
        Node* sourceTraveler = sourceSet.dummyNode->nextNode; // begin traveling at 1st interesting node
        
        while (sourceTraveler->nextNode != NULL) // insert nodes from source to this set, travel-->
        {
            insert(sourceTraveler->nodeItem);
            sourceTraveler = sourceTraveler->nextNode;
        } // exits loop when reaching last node
        
        insert(sourceTraveler->nodeItem); // insert last node
        tail = sourceTraveler; //set tail to last node
    }
}

Set& Set::operator=(const Set& sourceSet)
{
    ///// sourceSet.totalElements = 0 /////
    
    if(sourceSet.empty())
    {
       clearSet();
    }
    
    ///// sourceSet.totalElements > 1 /////
    
    Set copySet(sourceSet); // create copy of sourceSet
    swap(copySet); //swap current set with copySet
    return *this;
    
    //////////
}

bool Set::empty() const
{
    if (totalElements == 0)
    {
        return true;
    }
    return false;
    
}// Return true if the set is empty, otherwise false.



int Set::size() const
{
    return totalElements;
}

bool Set::insert(const ItemType& value)
{    
    ///// totalElements >= 0 /////
    
    if (!contains(value))
    {
        Node* insertedNode = new Node; // initialize new node
        insertedNode->nodeItem = value; // set value for new node
        insertedNode->nextNode = NULL; // set new node's nextNode to NULL
        insertedNode->previousNode = tail; // new node's previousNode points to one node before it
        tail->nextNode = insertedNode; // node's (that comes before new node) nextNode points to new node
        tail = insertedNode; // tail set to last node
        totalElements++; // size incremented
        return true;
    }
    return false;
}// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Return false if the
// value was not inserted (perhaps because it is already in the set
// or because the set has a fixed capacity and is full).


bool Set::erase(const ItemType& value)
{
    
    ///// totalElements = 0 /////
    
    if (empty())
    {
        return false;
    }
    
    if(tail->nodeItem == value) // special case
    {
        Node* oneBeforeTail = tail->previousNode;
        oneBeforeTail->nextNode = NULL; // pointer adjustment
        delete tail;
        tail = oneBeforeTail; //pointer adjustment
        totalElements--; //decrement size
        return true;
    }
    
    ///// totalElements >= 1 /////
    
    if (contains(value)) // required condition
    {
        Node* traveler = tail; // traveling node begins at tail, travels <--
        Node* oneBeforeTraveler = tail->previousNode; // pointer to one node before traveler
        
        while (traveler != dummyNode) // leave loop after visiting all interesting nodes
        {
            if (traveler->nodeItem == value) // upon reaching node that will be deleted
            {
                if (traveler == tail)
                {
                    oneBeforeTraveler->nextNode = NULL;
                    tail = oneBeforeTraveler;
                    delete traveler;
                    return true;
                }
                goto A;
            }
            traveler = oneBeforeTraveler; // traveler moves one node <-- if not pointing to node with value
            oneBeforeTraveler = oneBeforeTraveler->previousNode; // oBT moves one node <-- as well
        } // if totalElements > 1, traveler now points to node with value
        
    A:
        Node* oneAfterTraveler = traveler->nextNode; // pointer to one node after traveler
        oneBeforeTraveler->nextNode = oneAfterTraveler; // pointer adjustment
        oneAfterTraveler->previousNode = oneBeforeTraveler; // pointer adjustment
        delete traveler; // node with value deleted
        totalElements--; // decrement size
        return true;
    }
    return false;
    
    //////////
    
}// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

bool Set::contains(const ItemType& value) const
{
    
    ///// totalElements = 0 /////
    
    if (empty())
    {
        return false;
    }
    
    ///// totalElements >= 1 /////
    Node* traveler = tail; // traveling node begins at tail, travels <--
    
    while (traveler != dummyNode) // leave loop after visiting all interesting nodes
    {
        if (traveler->nodeItem == value) // upon reaching node that holds value
        {
            return true;
        }
        traveler = traveler->previousNode; // traveler moves one node <-- if not pointing to node with value
    }
    return false;
    //////////
    
}// Return true if the value is in the set, otherwise false.

bool Set::get(int pos, ItemType& value) const
{
    ///// invalid pos /////
    
    if (pos < 0 || pos > totalElements)
    {
        return false;
    }
    
    ///// totalElements = 0 /////
    
    if (empty())
    {
        return false;
    }
    
    ///// totalElements >= 1 /////
    
    int positionCounter = size() -1; // notify traveler when to stop
    Node* traveler = tail; // traveling node begins at tail, travels <--
    while (traveler != dummyNode) // leave loop after visiting all interesting nodes
    {
        if (positionCounter == pos) // stop when reaching correct node
        {
            value = traveler->nodeItem; // set value as traveler's node value
            return true;
        }
        traveler = traveler->previousNode; // traveler moves one node <-- if not pointing to node with value
        positionCounter--; // position decremented
    }
    return false;
    
    //////////
    
} // If 0 <= i < size(), copy into value an item in the set and
// return true.  Otherwise, leave value unchanged and return false.
// (See below for details about this function.)

void Set::swap(Set& other)
{
    int otherTotalElements = other.totalElements; // represents other set's size
    other.totalElements = totalElements; // swap size
    totalElements = otherTotalElements; // swap size
    
    Node* thisHead = head; // points to this set's head
    Node* thisTail = tail; // points to this set's tail
    Node* thisDummy = dummyNode; // points to this set's dummyNode
    
    Node* thatHead = other.head; // points to other set's head
    Node* thatTail = other.tail; // points to other set's tail
    Node* thatDummy = other.dummyNode; // points to other set's dummyNode
    
    other.head = thisHead; // swap heads
    other.tail = thisTail; // swap tails
    other.dummyNode = thisDummy; // swap dummyNodes
    
    head = thatHead; // swap heads
    tail = thatTail; // swap tails
    dummyNode = thatDummy; // swap dummyNodes
    
}// Exchange the contents of this set with the other one.

bool Set::clearSet()
{
    
    ///// totalElements = 0 /////
    
    if (empty())
    {
        return false;
    }
    
    ///// totalElements = 1 /////
    if (containsOne())
    {
        delete dummyNode->nextNode;
        dummyNode->nextNode = NULL;
        tail = dummyNode;
        totalElements--;
        return true;
    }
    
    ///// totalElements > 1 /////
    if (size() > 1)
    {
        Node* deleteThis = dummyNode->nextNode;
        Node* oneAfterDeleteThis = deleteThis->nextNode;
        while(oneAfterDeleteThis->nextNode != NULL)
        {
            dummyNode->nextNode = oneAfterDeleteThis;
            oneAfterDeleteThis->previousNode = dummyNode;
            delete deleteThis;
            deleteThis = oneAfterDeleteThis;
            oneAfterDeleteThis = deleteThis->nextNode;
            totalElements--;
        } // exit loop when theres only one interesting element left
        dummyNode->nextNode = NULL; //delete last two nodes
        delete deleteThis;
        delete oneAfterDeleteThis;
        tail = dummyNode;
        totalElements-=2;
        return true;
    }
    
    return false;
    
    //////////
    
} //delete all nodes in set from tail to head

bool Set::containsOne() const
{
    if (totalElements==1)
    {
        return true;
    }
    return false;
} //return true if set contains only one element

Set& Set::createCopy(Set copyThis) // copy a set and return it
{
    Set bufferSet(copyThis);
    swap(bufferSet);
    return *this;
}

void unite(const Set& s1, const Set& s2, Set& result) // see psuedocode
{
    ///// DO NOT ASSUME RESULT IS EMPTY /////
    
    for (int n=0; n != result.size(); n++)
    {
        ItemType someValue;
        result.get(n,someValue);
        result.erase(someValue);
    }
    
    Set s1Copy(s1);
    Set s2Copy(s2);
    
    for (int n=0; n != s1Copy.size(); n++)
    {
        ItemType someValue;
        s1Copy.get(n, someValue);
        result.insert(someValue);
    }
    
    for (int n=0; n != s2Copy.size(); n++)
    {
        ItemType someValue;
        s2Copy.get(n, someValue);
        result.insert(someValue);
    }
    
}

void subtract(const Set& s1, const Set& s2, Set& result) // see psuedocode
{
    ///// DO NOT ASSUME RESULT IS EMPTY /////
    
    
    for (int n=0; n != result.size(); n++)
    {
        ItemType someValue;
        result.get(n,someValue);
        result.erase(someValue);
    }
    
    Set s1Copy(s1);
    Set s2Copy(s2);
    
    ItemType s1Value;
    ItemType s2Value;
    
    int requiredAction=0; // denotes loop order of operations
    
    for(int n=0; n != s1Copy.size(); n++)
    {
        
        for (int k=0; k!= s2Copy.size(); k++)
        {
            s1Copy.get(n,s1Value);
            s2Copy.get(k,s2Value);
            if (s2Value != s1Value) // compare s1 to all s2, if none of s2 == s1, insert into result
            {
                requiredAction = 0;
                continue;
            }
            else
            {
                requiredAction = 1; // if s2 == s1, skip this value and do not insert
                break;
            }
            
        }
        if(requiredAction == 0)
        {
            ItemType someValue;
            s1Copy.get(n, someValue);
            result.insert(someValue);
        }
        else if (requiredAction == 1)
        {
            requiredAction = 0; // reset this int when moving to next s1 element
            continue;
        }
    }
}



