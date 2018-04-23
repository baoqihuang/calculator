//============================================================================
// Name        : project1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <cctype>
#include <string>
#include <cmath>
using namespace std;

/**~*~*
  Function prototype
*~**/
bool validateChar(string );
bool enqueueInfix (string , Queue <char> & );
void postfix (Queue <char> &, Stack <char> &, Queue <char> &);
void evaluate (Queue <char> &, Stack <int> &);
bool checkIcp(char , char);
void farewell();


int main()
{
	string maexpression;				// a string to accept the user input
	Stack<char> S1;
	Stack<int> S2;
	Queue<char> Q1,Q2;
	bool statue = false;
	// Greeting
	cout << "Hello ! Welcome to my first project !" << endl
		 << "This program is helping you to evaluate mathematical expressions" <<endl;
	// Check if enqueue successfully
	if(statue != enqueueInfix(maexpression, Q1))
	{
        postfix (Q1, S1, Q2);			//revoke postfix function
		cout << "Expression in postfix: ";
		Q2.print();						// print content in Q2
		evaluate (Q2, S2);				//revoke evaluate function
	}
	else
	cout <<"Fail to enqueue" <<endl;

	farewell();							//Farewell



	return 0;
}

/**~*~*
 enqueueInfix function to accept expression entered by user
 and enqueue to Q1
*~**/
bool enqueueInfix (string maexpression, Queue <char> &Q1)
{
	bool statue = false;
	while(statue == false)
	{
		cout << "Please enter an expression and end with enter" <<endl;
		getline(cin, maexpression);
		cout << "You typed: " << maexpression <<endl;

		if (!validateChar(maexpression))        //Check if the expression is valid
			continue;						   //if the expression invalid thenask user to enter again
		statue = true;						   //if true
		if(statue == true)					   //if valid assign true to statue
		{
			for (int i = 0; maexpression[i] != '\0'; i++)
			{
				if(!isspace(maexpression[i]))   // check if the space character
				{
					if(!Q1.enqueue(maexpression[i]))     //enqueue to Q1
						cout <<"Error ! Fail to enqueue." <<endl;

				}
			}

		}
	}
return statue;
}



/**~*~*
  Postfix function accepts expression from Q1 and use S1 to store the operator
  then store the posfix of the expression in Q2
*~**/
void postfix (Queue <char> &Q1, Stack <char> &S1, Queue <char> &Q2)

{

	char c, topOfStack, op;
	bool statue = false;
	Q1.enqueue('#');			//Enqueue end-of-input marker'#' into Q1
	S1.push('#');			//Enqueue end-of-input marker'#' into S1
	Q1.print();				//Print content in Q1
	while(Q1.dequeue(c) && (c != '#'))   //Dequeue from Q1 into c and c is not end-of-input marker '#'
	{

			if(isdigit(c))    //check whether c is digit
			{
				if(!Q2.enqueue(c))		//enqueue c to Q2
				{
					cout << "Error ! Fail to enqueue" <<endl;
				}
			}
			else if(c == ')')			//if c is ')'
			{
				//S1 is not empty and top of stack is not '('
				while(statue == S1.isEmpty() && statue != S1.getTop(topOfStack) && topOfStack != '(')
				{
					if(statue != S1.pop(op))  //pop from S1 and store in op
					{
						if(!Q2.enqueue(op))		//enqueue op to Q2
							cout << "Error ! Fail to enqueue" <<endl;
					}
				}
				if(statue == S1.pop(op))			//pop from S1 and store in op
					cout << "Error ! Fail to pop" <<endl;
			}
			else
			{
				// S1 is not empty and isp >= icp
				while (statue == S1.isEmpty() && statue != S1.getTop(topOfStack) && statue !=
						checkIcp(c, topOfStack))
				{
					if(statue == S1.pop(op))		//pop from S1 and store in op
						cout << "Error ! Fail to pop" <<endl;
					if(statue == Q2.enqueue(op))		//enqueue op to Q2
						cout << "Error ! Fail to enqueue" <<endl;
				}
				if(!S1.push(c))  //push c to S1
				{
					cout << "Error ! Fail to push" <<endl;
				}


			 }


	}
	if(statue == S1.isEmpty())   //if S1 is not empty
	{
		//S1 is not empty and top of stack is not '#'
		while(statue == S1.isEmpty() && statue != S1.getTop(topOfStack) && topOfStack != '#' )
		{
			if(!S1.pop(op))     //pop from S1 and store in op
			{
				cout << "Error ! Fail to pop";
			}
			else
			{
				if(statue == Q2.enqueue(op))		//enqueue op to Q2
					cout << "Error ! Fail to enqueue";
			}

		}
	}
}


/**~*~*
  evaluate function accepts postfix expression from Q2 and use S2 to store the operands
  and result in the end
*~**/
void evaluate (Queue <char> &Q2, Stack <int> &S2)
{
	char op;
	int result = 0, op1 = 0, op2 = 0, op_int;
	while(! Q2.isEmpty())   		//Q2 is not empty
	{
		if(Q2.dequeue(op))		//dequeue from Q2 and store in op
		{
			Q2.print();			//dequeue content of Q2

			if(isdigit(op))		//if op is a digit character
			{
				op_int = static_cast<int>(op)-48;  //convert op to int and store in op_int
				if(! S2.push(op_int))		//push op_int to S2
					cout << "Error ! Fail to push" <<endl;
				else
					S2.print();			//print content of S2
			}
			else
			{
				if(!S2.pop(op2))			//pop form S2 and store in op2
					cout << "Error ! Fail to pop" <<endl;
				if(!S2.pop(op1))			//pop from S2 and store in op1
					cout << "Error ! Fail to pop" <<endl;
				//if op is operator and perform op1 op op2
				if(op == '+')
				{

					result = op1 + op2;
				}
				else
				{
					if(op == '-')
					{
						result = op1 - op2;
					}
					else
					{
						if(op == '*')
						{
							result = op1 * op2;

						}
						else
						{
							if(op == '/')
							{
								result = op1 / op2;
							}
							else
							{
								if(op == '^')
								{
								result = pow(op1, op2);
								}
								else
									cout << "Invalid operator." <<endl;
							}
						}
					}
				}
				if(! S2.push(result))	   //push result to S2
					cout << "Error ! Fail to push";
				else
					S2.print();				//print content of S2


			}
		}
	}
}


/**~*~*
  checkIcp function compare operator pop from Q2 and compare to
  operator at the top of S2. Return true if isp >= icp
*~**/
bool checkIcp(char come, char in)
{
	char comeOperator, topOfStack;
	comeOperator = come;
	topOfStack = in;
	//compare two operator
	if(comeOperator == '^' || comeOperator == '(')
	{
		return false;
	}
	else if(comeOperator == '*' || comeOperator == '/')
	{
		if (topOfStack == '*' || topOfStack == '/' || topOfStack == '^')
			return true;
	}
	else if (comeOperator == '+' || comeOperator == '-')
	{
		if (topOfStack == '^' || topOfStack == '*' || topOfStack == '/' || topOfStack == '+'
				|| topOfStack == '-')
			return true;
	}


	return false;
}

/**~*~*
  Farewell function to thanks for use
*~**/
void farewell()
{
	cout << "Thank you for using my program!" <<endl;
}

/**~*~*
validateChar function check if the expression entered by user
is valid. If not ask user to enter again
*~**/
bool validateChar(string maexpression)
{
	int parenthses_count = 0;
	if((maexpression.empty()))	//if empty return false
		return false;

	for (int i = 0; maexpression[i] != '\0'; i++)
	{
				//if entered illegal return false
				if (!isspace(maexpression[i]) && !isdigit(maexpression[i])
					&& maexpression[i] != '+' && maexpression[i] != '-'
					&& maexpression[i] != '*' && maexpression[i] != '/'
					&& maexpression[i] != '^' && maexpression[i] != '('
					&& maexpression[i] != ')')
				{
					cout << "Invalid characters"<<endl;
					return false;
				}

				//if operator is not at end
				if(maexpression[i + 1] == '\0' && (maexpression[i] == '+' || maexpression[i] == '-'
						|| maexpression[i] == '*' || maexpression[i] == '/'
						|| maexpression[i] == '^' ))
				{
					cout << "Operator in the end"<<endl;
					return false;
				}


				//if two operators are together
				 if(maexpression[i] == '+' || maexpression[i] == '-'
			     	|| maexpression[i] == '*' || maexpression[i] == '/'
					|| maexpression[i] == '^' )
				 {
					 if(maexpression[i+1] == '+' || maexpression[i+1] == '-'
					 	|| maexpression[i+1] == '*' || maexpression[i+1] == '/'
					 	|| maexpression[i+1] == '^' || maexpression[i-1] == '+'
					 	|| maexpression[i-1] == '-' || maexpression[i-1] == '*'
					 	|| maexpression[i-1] == '/' || maexpression[i-1] == '^')
					 	{
					 		cout << "Two operators are together"<<endl;
					 		return false;
					 	}
				 }


				//if the denominator is zero
				if (maexpression[i] == '/'
				   && maexpression[i + 1] == '0'	)
				{
					cout << "Can not divide zero"<<endl;
					return false;
				}
				//if open parentheses or end parentheses
				if(maexpression[i] == '(')
					parenthses_count ++;
				if(maexpression[i] == ')')
					parenthses_count --;
				if(parenthses_count < 0)
				{
					cout << "Parentheses in wrong order !";  //if end parentheses goes first return false
					return false;
				}
	}
	//if parentheses do not match return false
	if(parenthses_count != 0)
		{
			cout << "Parentheses do not match!"<< endl;
			return false;
		}

	return true;

}

