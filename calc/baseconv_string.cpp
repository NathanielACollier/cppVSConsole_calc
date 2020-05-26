
/*
  Nathaniel Collier
  7/12/2007
  Now that the preliminary versions of add subtract multiply and divide strings
  are completed we can now move to developing conversion between bases
  using numbers represented by strings.
*/
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/* calc.cpp */
extern stringstream log;


/* math_string.cpp */
string multiply_string( string a, string b );
string add_string( string a, string b );
string subtract_string( string a, string b );
vector<string> divide_string( string a, string b );
char compare_str_numbers( string a, string b );
/* nstring.cpp */
string reverse_string( string x );

/* local functions */
string dec_to_base( string number, string base );
string DecNumberToHexLetter( string number );





const int REMAINDER = 1;
const int QUOTIENT = 0;

string dec_to_base( string number, string base )
{
  vector<string> result(2);


  if( compare_str_numbers( number, base ) == '<' )
  {
     return DecNumberToHexLetter( number );
  }
  
  string final;
  string num;

  bool break_at_end = false;

  result[QUOTIENT] = "1";
  result[REMAINDER] = "1";
 
  log << "\nConverting: " << number << " to base "<< base << ".";
  num = number;
  while( result[QUOTIENT] != "0" )
  {
    if( compare_str_numbers( num, base ) == '<')
	{
      result[REMAINDER] = num;
	  result[QUOTIENT] = "0";
	  
	}
	else
	{
      result = divide_string( num, base );
	  log << "\n" << num << "/ "<<base<<"= " << result[QUOTIENT] << " R: " << result[REMAINDER];
	  num = result[QUOTIENT];
	  
	}	
	final += DecNumberToHexLetter( result[REMAINDER] ); // if its hex we need this function called
	                                                    // if its not hexidecimal this function is harmless
	                                                    // though in the production code we might want to check for a base of 16
	                                                    // before running this function
  }



  return reverse_string( final );
}



string DecNumberToHexLetter( string number )
{
	string result;

	if( number == "10" ) result = "A";
	else if( number == "11" ) result = "B";
	else if( number == "12" ) result = "C";
	else if( number == "13" ) result = "D";
	else if( number == "14" ) result = "E";
	else if( number == "15" ) result = "F";
	else result = number;

	return result;
}
