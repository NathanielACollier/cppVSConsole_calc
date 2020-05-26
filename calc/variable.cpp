/*
  Nathaniel Collier
   2/26/2008
  This file will contain functions to handle variable assignments and
   getting the results when it needs them.

  This file will also contain the functions that load and save the variable tables
    when the program starts and stops.
*/

#include <string>

using namespace std;

#include "ext_code/hash_table.h"


HashTable< string, string > VariableTable( "error",  0 );

/*
 Local Functions
*/
string variable_lookup( string variable );
void add_variable( string variable, string value );

/*
 This function will cause the table to search for a variable decleration
  if none is found "error" will be returned.
*/
string variable_lookup( string variable )
{
  string result = VariableTable[variable];

  return VariableTable[variable];
}


/*
  This sets the variable
*/
void add_variable( string variable, string value )
{

   // remove the old variable if it exsists first
	VariableTable.remove( variable );
	// assign new value
   VariableTable.insert( variable, value ); // insert value at pos variable
}

