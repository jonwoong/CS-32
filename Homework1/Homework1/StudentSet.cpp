
#include "Set.h"
#include "StudentSet.h"
#include <iostream>
using namespace std;



StudentSet::StudentSet()
{
    m_size = 0;
}// Create an empty student set.

StudentSet& StudentSet::operator=(const StudentSet& rhs) // assignment operator
{
    m_size = rhs.m_size;
    for (int n=0; n < m_size-1; n++)
    {
        m_set.insert(rhs.m_item[n]);
    }
    return *this;
}

StudentSet::StudentSet(const StudentSet& other) //copy constructor
{
    m_size = other.m_size;
    for (int r=0; r < m_size; r++)
    {
        m_set.insert(other.m_item[r]);
    }
}

StudentSet::~StudentSet() //destructor
{
    for (int r=0; r < m_size-1; r++)
    {
        m_set.erase(m_item[r]);
    }
}

bool StudentSet::add(unsigned long id)
{
    if (m_set.insert(id))
    {
        return true;
    }
    return false;
}
    // Add a student id to the StudentSet.  Return true if and only if the
    // id was actually added.
    
int StudentSet::size() const
{
    return m_size;
    
}// Return the number of ids in the StudentSet.
    
void StudentSet::print() const
{
    for (int r=0; r < m_size-1; r++)
    {
        cout << m_item[r] << endl;
    }
}
    // Print every student id in the StudentSet exactly once, one per line.
 

