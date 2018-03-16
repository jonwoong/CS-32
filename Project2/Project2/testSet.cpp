#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    ///// DEFAULT CONSTRUCTOR /////
    Set s;
    assert(s.size() == 0); //test size
    assert(s.empty()); //test empty
    assert(!s.erase("TEST")); //ensure nothing to erase
    
    ///// INSERTING /////
    ItemType T = "A";
    ItemType T2 = "B";
    ItemType T3 = "C";
    ItemType T4 = "D";
    assert(s.insert(T)); //test ability to insert
    assert(s.insert(T3));
    assert(!s.insert(T));
    
    ///// GET /////
    
    assert(s.get(0,T) && (T == "A")); //test actual inserted item
    assert(s.get(1,T4) && (T4 == "C")); //test that value can change
    
    ///// CONTAINS /////
    assert(s.contains(T)); //test contain function
    assert(!s.contains(T2));
    assert(s.contains(T3));
    
    ///// COPY CONSTRUCTOR /////
    Set b(s); //intentional naming
    assert(b.contains(T) && b.contains(T3)); //test copied elements
    
    ///// ASSIGNMENT OPERATOR /////
    Set d;
    d = s; //test assignment operator compiles
    assert(d.contains(T) && d.contains(T3)); //test actual values
    assert(d.size() == 2); //test size
    
    ///// ERASING /////
    assert(s.erase(T)); //test ability to erase
    assert(s.size() == 1); //test actual erasing
    assert(s.erase(T3));
    assert(s.size() == 0);
    
    ///// SWAPPING /////
    Set a;
    Set c;
    ItemType A = "R";
    ItemType B = "T";
    a.insert(A);
    c.insert(B);
    a.swap(c); //test swap
    assert(a.contains(B)); //test values after swap
    assert(c.contains(A));
    assert(a.size() == 1 && c.size() == 1); //test size after swap
    
    ///// UNITE /////
    Set e;
    unite(a,c,e); //test unite
    assert(e.contains(A) && e.contains(B)); //test result
    assert(e.size() == 2);

    
    ///// SUBTRACT /////
    Set f;
    f.insert("two");
    f.insert("eight");
    f.insert("three");
    f.insert("nine");
    f.insert("five");
    
    Set g;
    g.insert("six");
    g.insert("three");
    g.insert("eight");
    g.insert("five");
    g.insert("ten");
    
    Set h;
    
    subtract(f,g,h); //test subtract
    
    assert(h.contains("two") && h.contains("nine")); //test that unique values inserted
    assert(!h.contains("eight") && !h.contains("three") && !h.contains("five") && !h.contains("six") && !h.contains("ten")); //test that shared values are not present
    assert(h.size() == 2); // test size
    
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}