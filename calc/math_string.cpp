
/*
  Nathaniel Collier
  5/5/2007
  String Math Shared Library (Dynamic Linked Library)
*/
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


extern stringstream log;


/* nstring.cpp */
string reverse_string( string x );
/* local functions */
string add_string( string a, string b );
string subtract_positive_string( string a, string b );
string subtract_string( string a, string b );
vector<string> divide_string( string a, string b );
string multiply_largeA_by_singleB( string a, int b );
string multiply_string( string a, string b );
char compare_str_numbers( string a, string b );
string factoral_string( string a );
string eliminate_zeros( string number );



const unsigned short multiplication_table[10][10]= {
       //0    1		2	3	4	5	6	7	8	9 
	   { 0,   0,	0,	0,	0,	0,	0,	0,	0,	0 },
	   { 0,	  1,	2,	3,	4,	5,	6,	7,	8,	9 },
	   { 0,	  2,	4,	6,	8,	10,	12,	14,	16,	18 },
       { 0,	  3,	6,	9,	12,	15,	18,	21,	24,	27 },
	   { 0,	  4,	8,	12,	16,	20,	24,	28,	32,	36 },
	   { 0,	  5,	10,	15,	20,	25,	30,	35,	40,	45 },
	   { 0,	  6,	12,	18,	24,	30,	36,	42,	48,	54 },
	   { 0,	  7,	14,	21,	28,	35,	42,	49,	56,	63 },
	   { 0,	  8,	16,	24,	32,	40,	48,	56,	64,	72 },
	   { 0,	  9,	18,	27,	36,	45,	54,	63,	72,	81 }

};


const unsigned short addition_table[10][10]= {
	  //   0	1	2	3	4	5	6	7	8	9
	  {	   0,	1,	2,	3,	4,	5,	6,	7,	8,	9 },
	  {	   1,	2,	3,	4,	5,	6,	7,	8,	9,	10 },
	  {	   2,	3,	4,	5,	6,	7,	8,	9,	10,	11 },
	  {    3,	4,	5,	6,	7,	8,	9,	10,	11,	12 },
	  {    4,	5,	6,	7,	8,	9,	10,	11,	12,	13 },
	  {    5,	6,	7,	8,	9,	10,	11,	12,	13,	14 },
	  {    6,	7,	8,	9,	10,	11,	12,	13,	14,	15 },
	  {    7,	8,	9,	10,	11,	12,	13,	14,	15,	16 },
	  {    8,	9,	10,	11,	12,	13,	14,	15,	16,	17 },
	  {    9,	10,	11,	12,	13,	14,	15,	16,	17,	18 }
};

/*
const  short subtraction_table[10][10]={
	  //   0	1	2	3	4	5	6	7	8	9
	  {	    0,	-1,	-2,	-3,	-4,	-5,	-6,	-7,	-8,	-9 },
	  {	   -1,	 0,	 1,	 2,	 3,	 4,	 5,	 6,	 7,	 9 },
	  {	   -2,	-1,	 0,	 1,	 2,	 3,	 4,	 5,	 6,	 7 },
	  {    -3,	-2,	-1,	 0,	 1,	 2,	 3,	 4,	 5,	 6 },
	  {    -4,	-3,	-2,	-1,	 0,	 1,	 2,	 3,	 4,	 5 },
	  {    -5,	-4,	-3,	-2,	-1,	 0,	 1,	 2,	 3,	 4 },
	  {    -6,	-5,	-4,	-3,	-2,	-1,	 0,	 1,	 2,	 3 },
	  {    -7,	-6,	-5,	-4,	-3,	-2,	-1,	 0,	 1,	 2 },
	  {    -8,	-7,	-6,	-5,	-4,	-3,	-2,	-1,	 0,	 1 },
	  {    -9,	-8,	-7,	-6,	-5,	-4,	-3,	-2,	-1,	 0 }
};
*/
const unsigned short subtraction_table[10][10]={
	  //    0	 1	 2	 3   4	 5	 6	 7	 8	 9
	  {	    0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0 },
	  {	    0,	 0,	 1,	 2,	 3,	 4,	 5,	 6,	 7,	 9 },
	  {	    0,	 0,	 0,	 1,	 2,	 3,	 4,	 5,	 6,	 7 },
	  {     0,	 0,	 0,	 0,	 1,	 2,	 3,	 4,	 5,	 6 },
	  {     0,	 0,	 0,	 0,	 0,	 1,	 2,	 3,	 4,	 5 },
	  {     0,	 0,	 0,	 0,	 0,	 0,	 1,	 2,	 3,	 4 },
	  {     0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,	 2,	 3 },
	  {     0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1,	 2 },
	  {     0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1 },
	  {     0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0 }
};




struct carry_type
{
  int pos;
  int num;
};



/*
  A problem has arrisen involving multiple zeros being the same as 0
  so that we have "0000" = "00" = "000000000"
  We need a way to tell if the number is zero and if it is we need to eliminate all zeros

*/
string eliminate_zeros( string number )
{
	int sum = 0;



	for( int i=0; i < number.size(); ++i )
	{
		if( number[i] != '0' ) return number; // leave the second we found a number that has any digit > 0
	}

	return "0";

}



/*
  Swap function written for strings
  
*/
void swap( string& a, string& b )
{
  string temp = b;
  b = a;
  a = temp;
}


/*
  Compares two numbers and returns the result of 
     a compared to b
  Results are returned as a character
   '>'  a is greater than b
   '<'  a is less than b
   '='  a is equal to b
*/
char compare_str_numbers( string a, string b )
{
  char result = '!';
  int x = 0;
	if( a.size() == b.size() )
	{
      // we compare the numbers 1 by 1
	  while( a[x] == b[x] && x < a.size() )
	  {
        ++x;
	  }

	  if( x == a.size() )
	  {
        result = '=';
	  } 
	  else
	  if( a[x] > b[x] )
	  {
        result = '>';
	  }
	  else
	  if( a[x] < b[x] )
	  {
        result = '<';
	  }
	}
	else
	if( a.size() > b.size() )
	{
      result = '>';
	}
	else
	if( a.size() < b.size() )
	{
      result = '<';
	}
  return result;
}


/*
 * This function does not have what I call writer comments because do to some misplaced
 *   commands on the terminal this function was deleted after 3 hours or so of work so
 *   the function you see below was written very quickly from memory in about 20 minutes
 *   so the writers comments that I usualy make are not there but I am in the process of
 *   adding them back.
 */
string add_string( string a, string b )
{
  string final;
  short cur_a = 0,
        cur_b = 0,
	    result = 0;

  vector< carry_type > carry_list;

  carry_type c;
  
  // we find out the maximum number by testing to see if
  // a is the maximum.
  bool a_max = ( a.size() > b.size() ) ? true : false;

  // here we compute the size of the answer since properties
  // of adition dictate that it can be as large as the largest number
  // pluss one.  Since a carry could occur at the end.
  // sizeof( a + b ) = sizeof( max( a,b) ) + 1
  int size = (( a_max == true ) ? a.size() : b.size() ) + 1;

  // we need to reverse the strings since numbers are written from left to
  // right but in the decimal system place value moves up from right to left
  // so the numbers must be processed by place value.
  a = reverse_string( a );
  b = reverse_string( b );

  for( int i = 0; i < size; ++i )
  {
    if( i >= a.size() ) cur_a = 0;
	else 
	  cur_a =  a[i] - '0' ;
	
	if( i >= b.size() ) cur_b = 0;
	else
	  cur_b = b[i] - '0';

	result = addition_table[cur_a][cur_b];
    log << "\n" << cur_a << " + " << cur_b << " = " << result;

     //check to see if any carry overs need to be added to the result
	for( int j = 0; j < carry_list.size(); ++j )
	{
      if( carry_list[j].pos == i )
	  {
	    int debug_result = result;
        result += carry_list[j].num;
	    log << "\nAdd carry " << carry_list[j].num << " to " << debug_result << " = " << result;
	  }
	}

    if( (c.num = (int)(result / 10) ) > 0 )
	{
      // there is a carry that needs to occur
	  c.pos = i + 1;
	  carry_list.push_back( c );
	  result -= c.num * 10;
	  log  << "\n" << result << " Carry " << c.num << " to position " << c.pos;
	}
    
	final += '0' + result;
  }

  final = reverse_string( final );
  // strip 0s and spaces out of final awnser



  if( final.find_first_not_of( "0 " ) != -1 )
  {
    final = final.substr( final.find_first_not_of( "0 " ), string::npos );
  }



  return final;
}

string subtract_string( string a, string b )
{
  string final;
  	 /* subtraction rules
	     -----------------------------------------------------
		 ***********These checks are performed before strings are reversed*******
		 1.)  Rules to determine if answer will be negative
	*/

	switch( compare_str_numbers( a,b ) )
	{
	  case '=':
		   final = "0";
	    break;
	  case '<':
		   final = "-" + subtract_positive_string( b,a );
	    break;
	  case '>':
           final = subtract_positive_string( a, b );
	    break;
	}



  // strip 0s and spaces out of final awnser
  if( final.find_first_not_of( "0 " ) != -1 )
  {
    final = final.substr( final.find_first_not_of( "0 " ), string::npos );
  }



   return final;
}

/*
 *  This function does strait subtraction the other function determines
 *     positive/negative result and sets things up
 */
string subtract_positive_string( string a, string b )
{
   string final;   
   int cur_a,
       cur_b,
	   result,
	   size;
   vector< carry_type > carry_list;
 	// a - b

    // the biggest the end result can be is the size of the largest number
	bool a_max = ( a.size() > b.size() ) ? true : false;
    // this will basicly work the same way addition works
    
    carry_type c;

	size = ( a_max == true ) ? a.size() : b.size();

     /*
		  Performance of Subtraction once negation is determined
          -----------------------------------------------------------
		  Reverse the strings A and B
		  if( A[i] < B[i] )
		  {
            A[i] += 10
			A[i+1] -= 1  use the carry structure though
			             in subtraction the carrys will be -1
			perform the subtraction 
			result = A[i] - B[i]
		  }
	  */

    a = reverse_string( a );
	b = reverse_string( b );

	for( int i = 0; i < size; ++i )
	{
      if( i >= a.size() ) cur_a = 0;
	  else 
	  cur_a =  a[i] - '0' ;
	
	  if( i >= b.size() ) cur_b = 0;
	  else
	  cur_b = b[i] - '0';

	  // check for carry that needs to be taken away from a[i]
      for( int j = 0; j < carry_list.size(); ++j )
	  {
         if( carry_list[j].pos == i )
		 {
           cur_a += c.num; // actualy cur_a  + -1 but whatever it the same thing as --cur_a
		 }
	  }

	  // check if we need to borrow from the next placevalue
	  // ( see if a carry need to happen in the future )
      if( cur_a < cur_b )
	  {
        cur_a += 10;
        c.pos = i + 1;
		c.num = -1;
		carry_list.push_back( c );
	  }

      result = cur_a - cur_b;
	  log  << "\n" << cur_a << " - " << cur_b << " = " << result;

	  final += '0' + result;
	}
   
   return reverse_string( final );
}


/*
  Human algorithm to perform limitless divisions
  it is only limited by a number length of 2^32-1 since that is 
  the maximum integer obtainable
  does not yet do anything with the remainder
  it will eventualy.
   final[0] is the quotient
   final[1] is the remainder
*/
vector<string> divide_string( string a, string b )
{
  vector<string> final(2);
  string remainder;
  string sub_num;
  int bring_down = 0;
  int div_count = 0;
  //final[0] = "0";
  //final[1] = "0";
  /*
   * Division looks quite hard at the moment
   * since there is no known algorithm that I have found
   * that does not rely on guessing which computers do
   * not do
   */

  /*
      a / b
  subtract a[ 0 to b.size() ] - b
  then if that is negative do the subtraction  
    of  a[ 0 to b.size() + 1 ] that should get the divison algorithm started
  */
  
  if( compare_str_numbers( a, b ) == '<' )
  {
	  log  << "\nDividing a number " << a << " smaller than " << b << " Produces \nRem: " << a << "\nQuotient: " << 0 << ".";

	final[0] = "0"; // the quotient is 0
	final[1] = a; // the remainder is the number you tried to divide b into I think
	return final;
  }
  else
  if( compare_str_numbers( "0", b ) == '=' )
  {
    // division by zero
	log << "\nDivision By Zero Error\n";
    return final;
  }
  

  // we get the piece of a that is equal to the size of b
  //  It is pointed out latter in the code, but sub_num will equal a if b.size() == a.size()
  sub_num = a.substr(0,b.size() );
  // so that we can use it to subtract sub_num - b

  log << "\nSUBNUM: " << sub_num << "\n";

  // bring_down should be the position where
  //       aaaaaaaaa
  //       bbbbb
  //            ^
  //            |
  //            bring_down should point to this position
  //       sssss
  bring_down = sub_num.size();

  // if the two numbers are equal in size we don't have a bring_down
  if( a.size() == b.size() )
	  bring_down = -1;

  do
  {
    // now we determine the new sub_num
    
	div_count = 0;

    log << "\n" << sub_num << " " << compare_str_numbers( sub_num, b ) << " " << b;
    while( compare_str_numbers( sub_num, b ) != '<'  )
    {
	  log << "\n" << sub_num << " - " << b;
      sub_num = subtract_string( sub_num, b );
	  ++div_count; // how many times can b go into sub_num
      
      log << "= " << sub_num << "\n";
	  //system( "pause" );
    }

      log << "\nEnd of LOOP\n";

      final[0] += div_count + '0'; 
	  // bring down a number

       // if we do a bring_down ( Meaning a.size() > b.size() also meaning sub_num != a )
	   //      sub_num should be equal to a if b and a are the same size
       if( bring_down != -1 && bring_down < a.size() )
	   {
		   // we performed a subtractrion above with sub_num which may have resulted
		   //    in sub_num containing "0" well we don't want to add a number to that which
		   //    would result in "07" or something like that so if sub_num == "0" we set
		   //    sub_num = ""
		  if( sub_num == "0" )
			   sub_num = "";
		  sub_num += a[bring_down]; // HUGE PROBLEM HERE this adds a null character to the end of sub_num VERY BAD
          ++bring_down;
	   }
	   else
	   {
			// if there is nothing more to bring down why are we still running through the loop
		   break;
	   }


      log << "\nSubNum: \"" << sub_num << "\"";
      log << endl;
	
      log << "\nBringDown: " << bring_down << " ASize: " << a.size() << endl;

	  
  }while( bring_down < (a.size()+1) );

  final[1] = ( sub_num[0] == NULL ) ? "0" : sub_num;
  // strip 0s and spaces out of the start of the final awnser
  final[0] = final[0].substr( final[0].find_first_not_of( "0 " ), string::npos );

    log << "\n-------------------------"
		 << "\nQuotient:  \"" << final[0] << "\""
         << "\nRemainder: \"" << final[1] << "\""
		 << "\n-------------------------" << endl;

  // this reduces errors by guarenteeing that all zeros = "0" 

  
  return final;
}


string multiply_largeA_by_singleB( string a, int b )
{
  unsigned short cur_a = 0,
				 result = 0;

  string final;
  vector< carry_type > carry_list;
  /* carry_type
   * int num
   * int pos
   */
  carry_type c;

  

 // a = reverse_string( a ); This happens in the multiply_string function

   for( int i = 0; i < a.size() + 1; ++i )
   {
      if( i >= a.size() ) cur_a = 0;
	  else 
	  cur_a =  a[i] - '0' ;
      result = multiplication_table[cur_a][b]; // max result of 9 * 9 = 81 so max carry of 8
       
	  log << "\n" << cur_a << " * " << b << " = " << result;

	  // need to add carrys to result
	  for( int j = 0; j < carry_list.size(); ++j )
	  {
         if( carry_list[j].pos == i )
		 {
		   int debug_result = result;
           result += carry_list[j].num;
		   log << "\nAdd carry " << carry_list[j].num << " to " << debug_result << " = " << result;
		 }
	  }
	  // then determine if a carry needs to be done
	  
	  // first determine if this is the last position as there is no carry in that position
	  if(  /*  ( i != a.size() - 1) && */ (c.num = (int)(result / 10) ) > 0   )
	  {
        // there is a carry that needs to occur
	    c.pos = i + 1;
	    carry_list.push_back( c );
	    result %= 10;
	    log << "\n" << result << " Carry " << c.num << " to position " << c.pos;
	  }
    
	final += '0' + result;

   }

   return reverse_string( final );
}


string multiply_string( string a, string b )
{
   string shift_postfix,
          current_level,
          final;
   int  cur_b = 0;

   log << "\n" << a << "\n" << b << "\n-----------------------------";
   
   
   if( compare_str_numbers( b, a ) == '>' )
   {
      log << "\nSwap A: " << a << " with B: " << b;
      swap( a, b ); // big numbers should be multiplied by smaller numbers
                    // not the other way around
      log << "\n     A: " << a << " B: " << b;
   }

   b = reverse_string( b ); // we need to reverse it so that multiplications
                            // happen starting from the right on b and the right on a
   a = reverse_string( a );

   // we need to start out with the final string populated with zeros
   // so that our answer will contain the correct number of place values
   for( int i = 0; i < a.size() + b.size(); ++i )
   {
      final += '0';
   }

   // there are b.size() levels so
   for( int level = 0; level < b.size(); ++level )
   {
      for( int i = 0; i != level; ++i )
	  {
        shift_postfix += '0'; 
	  }

	  if( level >= b.size() ) cur_b = 0;
    	else
	  cur_b = b[level] - '0';
 
      current_level =  multiply_largeA_by_singleB( a, cur_b ) + shift_postfix;

	  // and add in this level to the final
	  final = add_string( current_level, final );

      log  << "\n-------------------------------------------"
	       << "\nLEVEL#          " << level
	       << "\nSHIFT PREFIX:   " << shift_postfix
	       << "\nCURRENT_LEVEL:  " << current_level
		   << "\nFINAL_LEVEL:    " << final
		   << "\n-------------------------------------------";
    
	    log << "\n" << current_level;
	  shift_postfix.clear(); // clear for the next level
      
   }
      log << "\n---------------------------"
	     << "\n" << final;
     // strip 0s and spaces out of final awnser
  final = final.substr( final.find_first_not_of( "0 " ), string::npos );

   // this reduces errors by guarenteeing that all zeros = "0" 
  

   return final;
}

/*
  Implimentation of Factoral algorithm with string multiplication
*/
string factoral_string( string a )
{
	string factoral = "1";

	string number = a; // save a as number


	// if we aren't 1 allready
	if( compare_str_numbers( number, "1" ) != '=' )
	{
		// setup factor to be 1 less than the number for the first multiplication
		number = subtract_string( number, "1" );
		factoral = a;
	}


	while( compare_str_numbers( number, "1" ) == '>' )
	{
		factoral = multiply_string( factoral, number );
		number = subtract_string( number, "1" );
	}

	return factoral; 
}