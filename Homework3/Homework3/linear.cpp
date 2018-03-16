#include <string>
#include <cassert>
#include <iostream>
using namespace std;

/* Replace the incorrect implementations of these functions with correct ones that use recursion in a useful way; your solution must not use the keywords while, for, or goto. You must not use global variables or variables declared with the keyword static, and you must not modify the function parameter lists. If you write any auxiliary functions, they must not have any parameters of a reference type, and any parameter of a pointer type must be of type const string*.
 
 You may find it helpful to remember that a function parameter x declared T x[] for any type T means exactly the same thing as if it had been declared T* x. If any of the parameters n, n1, or n2 is negative, act as if it were zero.
 
 You will not receive full credit if for nonnegative n, anyEmpty, countEmpties, or firstEmpty performs more than n tests to determine whether strings are empty, or if indexOfLeast or includes causes a string comparison function (e.g. <= or ==) to be called more than n or n1 times, respectively. (For example, in determining how many of the n elements of an array are empty strings, you must not perform more than n tests to see whether a string is empty; you must solve this by causing each of the strings in the array to be tested no more than once.)
 
 Each of these functions can be implemented in a way that meets the spec without calling any of the other four functions. (If you implement a function so that it does call one of the other functions, then it will probably not meet the limit stated in the previous paragraph.)
 */

// Return true if any of the strings in the array is empty, false
// otherwise.
bool anyEmpty(const string a[], int n)
{
    if (n < 0)
    {
        n = 0;
    }
    if (a[n].empty())
    {
        return true;
    }
    else
    {
        anyEmpty(a,n-1);
    }
    return false;
    
}

// Return the number of empty strings in the array.
int countEmpties(const string a[], int n)
{
    if (n < 0)
    {
        return false;
    }
    
    int counter = 0;
    
    if (a[0] != "")
    {
        countEmpties(a+1,n-1);
    }
    else
    {
        countEmpties(a+1,n-1);
        counter ++;
    }
    
    return counter;
}

// Return the subscript of the first empty string in the array.
// If no element is empty, return -1.
int firstEmpty(const string a[], int n)
{
    if (n < 0 )
    {
        n = 0;
    }
    
    int counter = 0;
    
    if (a[0] != "")
    {
        firstEmpty(a+1, n-1);
        counter++;
    }
    else
    {
        return counter;
    }
    
    return -1;  // This is incorrect.
}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const string a[], int n)
{
    if (n < 0)
    {
        n = 0;
    }
    
    if (a[0] < a[n])
    {
        indexOfLeast(a,n-1);
        return 0;
    }
    else
    {
        indexOfLeast(a+1,n);
        return n;
    }
    
    return -1;  // This is incorrect.
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"

//bool includes(const string a1[], int n1, const string a2[], int n2)
//{
  //  if (n1 < 0)
   // {
    //    n1 = 0;
    //}
    //if (n2 < 0)
    //{
     //   n2 = 0;
    //}
    
   // if (a1[n1-1] == a2[n2-1])
   // {
    //    includes(a1,n1,a2,n-2);
   // }
    
  //  if (includes(a1,n1,a2,n2))
   // {
        
  //  }
   // return false;  // This is not always correct.
//}

