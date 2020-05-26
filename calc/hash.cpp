

#include <string>

using namespace std;


/**
* Data Structures and Algorithm Analysis in c++
    Mark Allen Weiss
* A hash routine for string objects.
*/
int hash( const string & key, int tableSize )
{
   int hashVal = 0;

   for( int i = 0; i < key.length( ); i++ )
   {
     hashVal = 37 * hashVal + key[ i ];
   }
   
   hashVal %= tableSize;
   
   if( hashVal < 0 )
   {
      hashVal += tableSize;
   }
   
   return hashVal;
}


/**
 * Data Structures and Algorithm Analysis in c++
    Mark Allen Weiss
  * A hash routine for ints.
*/
int hash( int key, int tableSize )
{
  if( key < 0 ) key = -key;
  return key % tableSize;
}