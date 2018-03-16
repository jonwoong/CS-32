#include "Set.h"
#include <iostream>
#include <cstring>

using namespace std;

Set::Set()
{
    m_size = 0;
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
    if (m_size == 0)
    {
        m_item[0] = value;
        m_size++;
        return true;
    }
    if (m_size < DEFAULT_MAX_ITEMS)
    {
        for (int r=0; r < m_size-1; r++)
        {
            if (contains(value))
            {
                return false;
            }
        }
        m_item[m_size-1] = value;
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
    if (m_size == 0)
    {
        return false;
    }
    for (int r=0; r < m_size-1; r++)
    {
        if (m_item[r] == value)
        {
            m_item[r] = m_item[r+1];
            m_size--;
            return true;
        }
    }
    return false;
}
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
bool Set::contains(const ItemType& value) const
{
    if (m_size == 0)
    {
        return false;
    }
    for (int r=0; r <= m_size-1; r++)
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
    if (m_size == 0)
    {
        return false;
    }
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
    for (int r= 0; r < m_size; r++)
    {
        temp.insert(m_item[r]);
        erase(m_item[r]);
    }
    for (int r=0; r< other.m_size; r++)
    {
        insert(other.m_item[r]);
        erase (other.m_item[r]);    
    }
    for (int r=0; r< temp.m_size; r++)
    {
        other.insert(temp.m_item[r]);
        erase(temp.m_item[r]);
    }
}
    // Exchange the contents of this set with the other one.



