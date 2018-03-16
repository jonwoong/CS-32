#include <string>
#include <iostream>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3
//int countIncludes(const string a1[], int n1, const string a2[], int n2)
//{
//    if (n1 <= 0)
//    {
//      n1 = 0;
//}
//
//if (n2 <= 0)
//{
//        n2 = 0;
//    }
    
//    if ()
        
//    return -999;  // This is incorrect.
//}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < barrier come before all the other elements,
// and all the elements whose value is > barrier come after all
// the other elements.  Upon return, firstNotLess is set to the index
// of the first element in the rearranged array that is >= barrier,
// or n if there is no such element, and firstGreater is set to
// the index of the first element that is > barrier, or n if
// there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < barrier
//   * for firstNotLess <= i < firstGreater, a[i] == barrier
//   * for firstGreater <= i < n, a[i] > barrier
// All the elements < barrier end up in no particular order.
// All the elements > barrier end up in no particular order.
//void takeSides(string a[], int n, string barrier,
//               int& firstNotLess, int& firstGreater)
//{
 //   if (n < 0)
  //      n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < barrier
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == barrier
    //  Every element from firstUnknown to firstGreater-1 is not
    //     known yet
    //  Every element at position firstGreater or later is > barrier
    
  //  firstNotLess = 0;
   // firstGreater = n;
   // int firstUnknown = 0;
   // while (firstUnknown < firstGreater)
   // {
   //     if (a[firstUnknown] > barrier)
    //    {
     //       firstGreater--;
      //      exchange(a[firstUnknown], a[firstGreater]);
       // }
       // else
       // {
       //     if (a[firstUnknown] < barrier)
        //    {
          //      exchange(a[firstNotLess], a[firstUnknown]);
           //     firstNotLess++;
            //}
            //firstUnknown++;
       // }
    //}
//}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if ( n <= 1)
    {
        return;
    }
    else
    {
        if (a[n] > a[n-1])
        {
            order(a,n-1);
        }
        else
        {
            a[n] = a[n-1];
            order(a,n);
        }
    }
    return;  // This is not always correct.
}