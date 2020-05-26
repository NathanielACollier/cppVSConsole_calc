
/*
  Nathaniel Collier
  6/7/2007
  String based calculator
*/

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

stringstream log;
ofstream log_file;

/* calc_ops.cpp */
string evaluate_expression( string expression );
/* baseconv_string.cpp */
string dec_to_base( string number, string base );
/* function_handler.cpp */
void setup_mth_func_hashing();

const bool convert_result = false; // maybe make this a user input or config file kind of thing
const bool log_results = false;
const bool log_print_to_screen = false;
const char* log_filename = "log.txt";

int main()
{
   string input;
   string result;
   string result_hex;
   string result_bin;
   string result_oct;

   setup_mth_func_hashing();

   if( log_results == true )
      log_file.open( log_filename );

   cout << "\nConsole Calculator: ";
   while( input != "quit" )
   {
      cout << "\n_> ";
	  getline( cin, input ); // get input from the keyboard
      if( input == "quit" )
	  {
         break; // out of while loop
	  }
	  result = evaluate_expression( input );


	  if( convert_result == true )
	  {
		  result_hex = dec_to_base( result, "16" );
		  result_bin = dec_to_base( result, "2" );
		  result_oct = dec_to_base( result, "8" );
	  }


	    if( log_results == true )
		{
		  if( log_print_to_screen == true )
			  cout << log.str();

		  log_file << log.str();
		  log.clear();
		}
			  // display the result ( NO CALCULATION HERE USE VARIABLES SO IT WILL BE LOGGED )

	   if( convert_result == true )
	   {
			cout << "\nResult: " << result << flush
	    		 << "\nHex:    " << result_hex
				 << "\nBin:    " << result_bin
				 << "\nOct:    " << result_oct;
	   }
	   else
	   {
			cout << "\nResult: " << result << flush;
	   }

   }// while 
   
   if( log_results == true )
	 log_file.close();

	return 0;
}


