/*
 Nathaniel Collier
 8/15/2007
 This file will contain all of the internal functions
   that are created.
*/

#include <vector>
#include <string>

using namespace std;



/* math_string.cpp */
string multiply_string( string a, string b );
string add_string( string a, string b );
string subtract_string( string a, string b );
vector<string> divide_string( string a, string b );
string factoral_string( string a );
char compare_str_numbers( string a, string b );
/* 
  local functions
*/
string pow( vector<string>& arg );
string avg( vector<string>& arg );
string lcm( vector<string>& arg );
string IsComposite( vector<string>& arg );
string IsPrime( vector<string>& arg );


struct math_function_type
{
  string ( * function )  ( vector<string>& args );
  int id;
  string name;
  bool numeric_result;
};

const int NUM_MTH_FUNC = 5;

// outside access to NUM_MTH_FUNC
//    incriment the above number everytime a function is added
int get_num_func(){ return NUM_MTH_FUNC; }

struct math_function_type math_function_list[NUM_MTH_FUNC] = {
    { pow, 0, "pow", true },
	{ avg, 1, "avg", true },
	{ lcm, 2, "lcm", true },
	{ IsPrime, 3, "isprime", false },
	{ IsComposite, 4, "iscomposite", false }

};



string avg( vector<string>& arg )
{
   string sum = "0";
   string counter = "0";
   int i;
   char buf[(sizeof(int)*8+1)];

   if( arg.size() < 2 )
   {
     return "error";
   }

   for(  i=0; i < arg.size(); ++i )
   {
     sum = add_string( arg[i], sum );
   }
   
   sprintf( buf, "%d", i );

   // return the quotient since we do not have a decimal method
   // yet
   return divide_string( sum , buf )[0];
}


string pow( vector<string>& arg )
{
  
  return "32";
}



vector<string> factor( string number )
{
	vector<string> f; // factorization


	return f;
}

string lcm( vector<string>& arg )
{
	
	return "0";
}


string IsComposite( vector<string>& arg )
{
	string a;

	a = subtract_string( arg[0], "1" ); // (n-1)

	a = factoral_string( a ); // (n-1)!

	vector<string> result = divide_string( a, arg[0] ); // (n-1)! mod n

	string remainder = result[1];
	string quotient = result[0];


	if( compare_str_numbers( remainder, "0" ) == '=' )
	   return "1";
	return "0";
}

string IsPrime( vector<string>& arg )
{
	return ( IsComposite( arg ) == "1" ) ? "0" : "1";
}