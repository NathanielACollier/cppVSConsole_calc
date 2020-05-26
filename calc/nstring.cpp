
/*
  This is a placeholder for the actual nstring.cpp file
*/
#include <string>

using namespace std;


/* local functions */
string reverse_string( string x );


/*
 *
 */
string reverse_string( string x )
{
  string reverse;

  for( int i = x.size() - 1; i >= 0; --i )
  {
    reverse += x[i];
  }
  return reverse;
}


string strip_whitespace( string & line )
{
  string new_line;
  char current;
  
  for( int i=0; i < line.size(); ++i )
  {
    current = line[i];

	if( current != ' ' && current != '\n' && current != '\t' )
	{
      new_line += current;
	}
  }

  return new_line;
}




