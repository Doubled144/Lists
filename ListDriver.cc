/*
  Filename   : ListDriver.cc
  Author     : Gary M. Zoppetti
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test methods of the List class
*/   

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <cassert>

/************************************************************/
// Local includes

#include "List.hpp"

/************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::string;
using std::ostringstream;

/************************************************************/
// Function prototypes/global vars/typedefs

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual);

/************************************************************/
// Force instantiation of all templated methods

template class List<int>;
template class ListNode<int>;
template class ListIterator<int>;
template class ListConstIterator<int>;

template
ostream&
operator<< <int> (ostream&, const List<int>&);

template
bool
operator== <int> (const ListIterator<int>&, const ListConstIterator<int>&);

template
bool
operator!= <int> (const ListIterator<int>&, const ListConstIterator<int>&);

/************************************************************/

int
main (int argc, char *argv[])
{
  
  List<int> A;

  // For holding the actual result
  ostringstream output;
  // Put the actual result into the output stream
  output << A;
  printTestResult ("no-arg ctor", "[ ]", output);

  // Must clear the output stream each time
  output.str ("");
  output << A.size ();
  printTestResult ("size", "0", output);

  List<int> B (3, 8);
  output.str ("");
  output << B;
  printTestResult ("size ctor", "[ 8 8 8 ]", output);
  
  return EXIT_SUCCESS;
}

/************************************************************/

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual)
{
  cout << "Test: " << test << endl;
  cout << "==========================" << endl;
  cout << "Expected: " << expected << endl;
  cout << "Actual  : " << actual.str () << endl;
  cout << "==========================" << endl << endl;

  // Ensure the two results are the same
  assert (expected == actual.str ());
}

/************************************************************/