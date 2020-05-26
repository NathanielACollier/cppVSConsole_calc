
/*
 Nathaniel Collier
 7/12/2007
  Moved this stuff into a different file to prevent
  clutter
*/
#include <vector>
#include <string>
#include <sstream>

using namespace std;


#define NUMBER_LIST "0123456789"
#define ALPHA_LIST "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

/* calc.cpp */
extern stringstream log;


/* math_string.cpp */
string multiply_string( string a, string b );
string add_string( string a, string b );
string subtract_string( string a, string b );
vector<string> divide_string( string a, string b );
string factoral_string( string a );
string eliminate_zeros( string number );
/* local functions */
vector<string> parse_input( string input );
vector<string> infix_to_postfix( vector<string> infix );
vector<string> reverse_stack( vector<string>& stk );
string evaluate_stack( vector<string>& postfix );
int op_order( char op );
bool isop( char x  );
string evaluate_expression( string expression );
/* function_handler.cpp */
string math_function_handler( string key, vector<string>& args );
int math_function_lookup( string key );
/* variable.cpp */
string variable_lookup( string variable );
void add_variable( string variable, string value );

string evaluate_expression( string expression )
{
  vector<string> input_array;
  vector<string> postfix;
  vector<string> reversed_input;
  vector<string> reverse_postfix;

  input_array = parse_input( expression ); // parse the input into arguments

	  
  // since this operates using a stack we need to reverse it
  // so that it will be in the proper order when it is poped
  reversed_input = reverse_stack( input_array );
  postfix = infix_to_postfix( reversed_input );

  // reverse postfix so that evaluation happens in the right order
  reverse_postfix = reverse_stack( postfix );
  return evaluate_stack( reverse_postfix );
}

/*
  check to see if a character is an operator
*/
bool isop( char x  )
{
  if( x == '+' || x == '-' || x == '*' || x == '/' || 
	  x == '^' || x == ';' || x == ')' || x == '(' || 
	  x == '%' || x == '!' || x == '=' )
  {
    return true;
  }
  return false;
}

/* 
  returns the operation order of a operator
    used to determine precidence in an expression
*/
int op_order( char op )
{
  int order = 0;
  switch( op )
  {
	 
     case '+': order = 0; break;
     case '-': order = 0; break;
     case '*': order = 1; break;
	 case '!': order = 1; break; // factoral is basicly just multiplication
     case '/': order = 1; break;
	 case '%': order = 1; break; // modulus returns remainder
     case '^': order = 2; break;
     case ')': order = 3; break;
     case '(': order = 3; break;
	 case '=': order = 4; break; // I think we want this to be the last order
     default: order = 0; break;
  }
  return order;
}


vector<string> reverse_stack( vector<string>& stk )
{
  vector<string> temp;

  // copy it backwards
  for( int i=stk.size()-1; i >= 0; --i )
  {
    temp.push_back( stk[i] );
  }
  return temp;
}

/*
  Takes input in the form of a infix expression of some type
  parses the expression into operators/functions/strings/numbers
  all stored as strings
*/
vector<string> parse_input( string input )
{
  vector<string> text;
  int x = 0; // that are in the argument

  for( int i=0; i < input.size(); ++i )
  {
    // an operator will be obvious so we don't have to do much with it
    if( isop( input[i] ) )
	{
		text.push_back( input.substr( i,1) );
	}
	else
	if( isdigit( input[i] ) ) // numbers should also be pretty easy
	{
		x = (( x = input.substr( i, input.size() - i ).find_first_not_of( NUMBER_LIST )) == - 1 ) 
			? (input.size())
			: ( x + i );
		text.push_back( input.substr( i, x - i ) );
		i += x - i - 1;
	}
	else
    if( isalpha( input[i] ) ) // for functions and words it is just as easy
	{
		x = (( x = input.substr( i, input.size() - i ).find_first_not_of( ALPHA_LIST )) == - 1 ) 
			? (input.size())
			: ( x + i );
		text.push_back( input.substr( i, x - i ) );
		i += x - i - 1;

	}
  }

  return text;
}



/*
  Takes the infix stack that we read in from the keyboard and converts it to
    a postfix stack ( operators after operands  4+2 = 4 2 +
	infix means the operators are between the arguments ( lv + rv  )
	  and is the common form most americans use it is also the form used in
	  programming languages.
*/
vector<string> infix_to_postfix( vector<string> infix )
{
  vector<string> op_stack; // operators will temporarily go here
  vector<string> postfix; // output stack
  
  string top;
  
  while( infix.size() > 0 ) // run while we are not empty
  {
     // get the top thing on the stack
	  top = infix.back(); 
	  infix.pop_back();

     if( isdigit( top[0] ) )
	 {
       // numbers go directly to output
	   postfix.push_back( top );
	 }
	 else
	 if( isop( top[0] ) )
	 {
	     // operators are placed onto an op_stack
	     if( op_stack.size() == 0 ) // empty op_stack
	     {
		   op_stack.push_back( top ); // go ahead and just push it on
	     }
		 else // stack is not empty we need to find out some things
	     if( top[0] == ')' )
		 {
           // pop untill we reach a '('
		   while( op_stack.size() > 0 )
		   {
             top = op_stack.back();
			 op_stack.pop_back();

			 if( isop( top[0] ) && top[0] == '(' )
			 {
               // break out of the loop
			   break;
			 }
			 // push the operator to the output
			 postfix.push_back( top );
		   }//while
		 }//if
		 else
         if( op_order( top[0] ) <= op_order( op_stack.back()[0] ) )
		 {
           // we can safely put top on the stack since the current top
		   // operator is higher order than top is
		   op_stack.push_back( top );
		 }
		 else
		 {
           // there are operators on the stack that are lower order than top
		   // so we have to get them off
		   // while are older top is greater than what is on the stack we need
		   // to pop stuff off then we can push the old top onto the operator stack
		   while( op_stack.size() > 0 && op_order( top[0] ) > op_order( op_stack.back()[0] ) )
		   {  
			   postfix.push_back( op_stack.back() );
			   op_stack.pop_back();
		   }//while
		   // now that everything on the stack is higher order we can push top on
		   op_stack.push_back( top );
		 }//else
	 }//if
	 else
	 if( isalpha( top[0] ) ) // function
	 {
        string result;
		 vector<string> arguments;
		string function_name = top;


		/* Determine wether this is a function or a variable */
		if( math_function_lookup( top ) == -1 )
		{
          // variable
		  
		  // we might however want to check that the next symbol on the stack is an equals sign
		  if( infix.size() == 0 || infix.back() != "=" )
		  {
			  // look up the variable name and push back the result (If the variable name exsists )
			  if( variable_lookup( top ) != "error" )
			  {
				  infix.push_back( variable_lookup( top ) );
			  }
			  else
			  {
			    infix.push_back( "0" ); 
			  }
		  }
		  else
		  {
			  // this is a variable assignment and we want to deal with it at the assignment operator
			  postfix.push_back( top ); // push it onto the stack to be dealt with latter
		  }


		  continue; // found a variable so we need to skip over the function stuff
		}

		while( infix.size() > 0 )
		{
          top = infix.back();
		  infix.pop_back();

		  if( isop( top[0] ) && top == ";" )
		  {
             // end of function
		     break; // out of while loop
		  }
		  else
		  {
            arguments.push_back( top );
		  }
		}//while

		// find out which function this is
		// see if it's result is evaluated as a number
		// then run it
         
		 result = math_function_handler( function_name, arguments );

		 if( result != "error" )
		 {
           postfix.push_back( result );
		 }
		 else
		  postfix.push_back( "0" );
		 
		// do stuff with the result

	 }//if

   }//while

   // write operators left in the stack to the output
   while( op_stack.size() > 0 )
   {
     postfix.push_back( op_stack.back() );
	 op_stack.pop_back();
   }
  return postfix;
}


/*
  Evaluates a postfix stack
  and produces a result as a string
*/
string evaluate_stack( vector<string>& postfix )
{
  string top;
  vector<string> eval_stack;
  string left,
	     right;

  while( postfix.size() > 0 )
  {
    top = postfix.back();
	postfix.pop_back();

	if( isdigit( top[0] ) )
	{
      eval_stack.push_back( eliminate_zeros( top)  );
	}
	else
	if( isop( top[0] ) )
	{


      // Deal with unary operators like factoral
	  if( top[0] == '!' )
	  {
		  string opperand = eval_stack.back();
		  eval_stack.pop_back();
		  eval_stack.push_back( factoral_string( opperand) );
		  continue;
	  }
      // perform an evaluation using the operator
	  // right operator will be [1]
	  // left operator will be [0]
        right = eval_stack.back();
		eval_stack.pop_back();
		left = eval_stack.back();
		eval_stack.pop_back();




	  switch( top[0] )
	  {
	    case '+':
              eval_stack.push_back( add_string( left, right ) );
			break;
		case '-':
			eval_stack.push_back( subtract_string( left, right ) );
			break;
		case '*':
            eval_stack.push_back( multiply_string( left, right ) );
			break;
		case '/':
            eval_stack.push_back( divide_string( left, right )[0] );
			break;
		case '%':
			eval_stack.push_back( divide_string( left, right )[1] );
			break;
		case '=':
			log << "\nVariable: " << left << "\nValue: " << right << "\n";
			add_variable( left, right ); // left=variable and right=value
			eval_stack.push_back( "0" ); // have to have something to return
			break;
	  }
	}
	else
	if( top == "error" )
	{
      eval_stack.pop_back(); // remove it off the stack
	}
	else
	if( isalpha( top[0] ) )
	{
	  // variable assignment we hope
	  eval_stack.push_back( top );
	}
  }

  return eval_stack.back();
}
