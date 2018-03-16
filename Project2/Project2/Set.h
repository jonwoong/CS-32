//
//  Set.h
//  Project2
//
//  Created by Jonathan Woong on 4/18/14.
//  Copyright (c) 2014 CS32. All rights reserved.
//

#ifndef Project2_Set_h
#define Project2_Set_h
#include <string>//;
#include <iostream>
using namespace std;


typedef string ItemType;

class Set
{
public:
    Set();
    ~Set(); //destructor
    Set(const Set& rightSet); //copy constructor
    Set& operator=(const Set& sourceSet); //assignment operator
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    

    
private:
    struct Node
    {
        ItemType nodeItem;
        Node* nextNode;
        Node* previousNode;
    };
    Node* head;
    Node* tail;
    Node* dummyNode;
    int totalElements;
    bool clearSet();
    bool containsOne() const;
    Set& createCopy(Set copyThis);
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif
