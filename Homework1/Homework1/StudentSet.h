
#ifndef SS_H
#define SS_H

#include "Set.h"

class StudentSet
{
public:
    StudentSet();// Create an empty student set.
    ~StudentSet();
    StudentSet& operator=(const StudentSet& rhs);
    StudentSet(const StudentSet& other);
    
    
    bool add(unsigned long id);
    // Add a student id to the StudentSet.  Return true if and only if the
    // id was actually added.
    
    int size() const;  // Return the number of ids in the StudentSet.
    
    void print() const;
    // Print every student id in the StudentSet exactly once, one per line.
    
private:
    int m_size;
    Set m_set;
    ItemType m_item[];

    // Some of your code goes here.
};

#endif


