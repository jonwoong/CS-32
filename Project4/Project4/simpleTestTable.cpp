/*

#include "SymbolTable.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    SymbolTable st;
    assert(st.declare("alpha", 1));
	assert(st.declare("beta", 2));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.find("beta") == 2);    // the beta declared in line 2
	assert(st.find("gamma") == -1);  // Error!  gamma hasn't been declared
	st.enterScope();
	assert(st.declare("beta", 7));
	assert(st.declare("gamma", 8));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.find("beta") == 7);    // the beta declared in line 7
	assert(st.find("gamma") == 8);   // the gamma declared in line 8
	st.enterScope();
	assert(st.declare("alpha", 13));
	assert(st.declare("beta", 14));
	assert(!st.declare("beta", 15)); // Error! beta already declared
	assert(st.find("alpha") == 13);  // the alpha declared in line 13
	assert(st.exitScope());
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.find("beta") == 7);    // the beta declared in line 7
	st.enterScope();
	assert(st.declare("beta", 21));
	assert(st.find("beta") == 21);   // the beta declared in line 21
	assert(st.exitScope());
	assert(st.exitScope());
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.find("beta") == 2);    // the beta declared in line 2
	assert(st.find("gamma") == -1); // Error! gamma is not in scope
    cout << "PASSED ALL TESTS!" << endl;
}

*/