/*
 Nathaniel Collier
 8/15/2007
 Function Handler
*/

#include <vector>

using namespace std;


#include "ext_code/hash_table.h"


struct math_function_type
{
  string ( * function )  ( vector<string>& args );
  int id;
  string name;
  bool numeric_result;
};

/* functions.cpp */
int get_num_func();
extern math_function_type math_function_list[];

HashTable< string, int> mth_fun_lookup_table( -1, 0 );


/* local functions */
void setup_mth_func_hashing();
int math_function_lookup( string key );
string math_function_handler( string key, vector<string>& args );
math_function_type get_function_from_index( int pos );
bool function_is_numeric( int function_number );



math_function_type get_function_from_index( int pos )
{
  return math_function_list[ pos ];
}

void setup_mth_func_hashing()
{
  for( int i = 0; i < get_num_func(); ++i )
  {
    mth_fun_lookup_table.insert( math_function_list[i].name, i );
  }
}

int math_function_lookup( string key )
{
  int pos = -1;
  pos = mth_fun_lookup_table[key];
  return pos;
}


string math_function_handler( string key, vector<string>& args )
{
  string result;
  int pos = 0;

  pos = math_function_lookup( key );
  if( pos == -1 )
  {
	return "error";
  }

  result = math_function_list[pos].function( args );

  return result;
}







