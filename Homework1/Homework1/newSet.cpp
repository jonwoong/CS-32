
#include "newSet.h"
#include <iostream>
#include <cstring>

using namespace std;

Set::Set()
{
    m_size = 0;
    max_size = DEFAULT_MAX_ITEMS;
    m_item = new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(const int& n)
{
    max_size = n;
    m_size = 0;
    m_item = new ItemType[max_size];
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        m_size = rhs.m_size;
        max_size = rhs.max_size;
        m_item = rhs.m_item;
    }
    return *this;
}


bool Set::empty()
{
    if (m_size == 0)
        return true;
    return false;
}// Return true if the set is empty, otherwise false.

int Set::size()
{
    return m_size;
}// Return the number of items in the set.

bool Set::insert(const ItemType& value)
{
    if (m_size < max_size)
    {
        for (int r=0; r < max_size; r++)
        {
            if (contains(value))
            {
                return false;
            }
        }
        Set temp(max_size);
        for (int r=0; r < m_size-1; r++)
        {
            temp.m_item[r] = m_item[r];
        }
        temp.m_item[m_size-1] = value;
        delete [] m_item;
        for (int r=0; r < m_size-1; r++)
        {
            m_item[r] = temp.m_item[r];
        }
        m_size++;
        return true;
    }
    return false;
}
// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Return false if the
// value was not inserted (perhaps because it is already in the set
// or because the set has a fixed capacity and is full).

bool Set::erase(const ItemType& value)
{
    for (int r=0; r < m_size-1; r++)
    {
        if (m_item[r] == value)
        {
            Set temp(max_size);
            temp.m_size = (m_size-1);
            for (int n=0; n < temp.m_size-1; n++)
            {
                temp.m_item[n] = m_item[n];
            }
        }
        return true;
    }
    return false;
}
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

bool Set::contains(const ItemType& value) const
{
    for (int r=0; r < m_size-1; r++)
    {
        if (m_item[r] == value)
        {
            return true;
        }
    }
    return false;
}
// Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value)
{
    if (i >= 0)
    {
        if (i < size())
        {
            value = m_item[i];
            return true;
        }
    }
    return false;
}
// If 0 <= i < size(), copy into value an item in the set and
// return true.  Otherwise, leave value unchanged and return false.
// (See below for details about this function.)

void Set::swap(Set& other)
{
    Set temp;
    temp.max_size = other.max_size;
    temp = other; //temp takes other Set's elements
    other = *this; //other takes original Set's elements
    other.max_size = max_size;
    other.m_size = m_size;
    *this = temp; //original Set takes temp(other's) elements
    max_size = temp.max_size;
    m_size = temp.m_size;
    
}
// Exchange the contents of this set with the other one.


