//=================================================================
// @file:		stacksTest.cpp
// @author:     Ana Macavei
// @version:    1.0
//
//  Demonstrates: This file contains the 'main' function where I
//	present the implementation of Stacks as Arrays. The 
//	class function is tested here and converts infix expressions
//	to postfix and then evaluates them.
//=================================================================

#include <iostream>
#include "Stacks.h"
#include <stack>
#include <string>
#include <cctype>

//prototypes
void removeSpaces(std::string& str);
int operatorPrec(char x);
bool errorCheck(std::string str);
void convertToPostfix(std::string str);
int evaluateEquation(std::string exp);
int executeOp(int x, int y, char op);

int main() {
	//declare an object of class Stack
	Stack<int> myStack;

	std::cout << "Author: Ana Macavei\n\n";

	//Testing
	std::string str1 = "5 # 2   ";
	std::string str2 = "5 * - 6 8 ";
	std::string str3 = "5*2  +  3 ";
	std::string str4 = "3 + 5 * (7-2) ";
	std::string str5 = "3 + ( (8-5) * (4+9) ) ";
	std::string str6 = "42 + (123 - 456 ) * (78-75)";
	std::string str7 = "-4 + -5 * 3";
	std::string str8 = "4.1 +4*4.25";

	// 5 # 2   
	std::cout << "Processing:" << str1 << std::endl;
	removeSpaces(str1);
	std::cout << "Infix: ";
	errorCheck(str1);			//should print error here!


	// 5 * - 6 8
	std::cout << "\nProcessing: " << str2 << std::endl;
	removeSpaces(str2);
	std::cout << "Infix: \t" << str2 << std::endl;
	std::cout << "Postfix: "; convertToPostfix(str2);
	std::cout << "Result: ";
	errorCheck(str2);			//should print here an Error!


	// 5*2  +  3
	std::cout << "\n\nProcessing:" << str3 << std::endl;
	removeSpaces(str3);
	std::cout << "Infix: \t" << str3 << std::endl;
	std::cout << "Postfix: "; convertToPostfix(str3);
	std::cout << "Result: " << evaluateEquation(str3);


	// 3 + 5 * (7-2)
	std::cout << "\n\nProcessing:" << str4 << std::endl;
	removeSpaces(str4);
	std::cout << "Infix: \t" << str4 << std::endl;
	std::cout << "Postfix: "; convertToPostfix(str4);
	std::cout << "Result: " << evaluateEquation(str4);


	// 3 + ( (8-5) * (4+9) )
	std::cout << "\n\nProcessing:" << str5 << std::endl;
	removeSpaces(str5);
	std::cout << "Infix: \t" << str5 << std::endl;
	std::cout << "Postfix: "; convertToPostfix(str5);
	std::cout << "Result: " << evaluateEquation(str5);

	//Extra Credit

	//42 + (123 - 456 ) * (78-75)
	std::cout << "\n\nProcessing:" << str6 << std::endl;
	removeSpaces(str6);
	std::cout << "Infix: \t" << str6 << std::endl;
	std::cout << "Postfix: "; convertToPostfix(str6);
	std::cout << "Result: " << evaluateEquation(str6);


	return 0;
}


//prototype code implementations

/*---------------------------------------------------------------
* removeSpaces - A function that removes spaces in string
* removes the spaces from the begining of the string to the end of the string
*
* @param - string
*/
void removeSpaces(std::string& str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end()); //making use of the C++ standard library
}																//where iterators erase(), remove(), begin(), end() come from

/*---------------------------------------------------------
* operatorPrec - function that returns order of precedence
* @param - x where I store the operator
* @return - precedence of the operator
*/
int operatorPrec(char x) { //I use this in my convertToPostfix function

	switch (x) {
	case '+':
	case '-':
		return 1;
	case '*':		//multiply and division operator
	case '/':		//have a greater precedence so return 2 
		return 2;
	}				//I used my parantheses in my evaluateEquation only because I would get a deque error if I restated it again in here.
	return -1;

}


/*-----------------------------------------------------------
* convertToPostfix - a function to convert infix epression
* to postfix expression and makes use of the class Stack.
* @param str
*
*/
void convertToPostfix(std::string str) {

	std::stack<char>myStack;
	myStack.push('N'); // 'N' is used to store operand/operator. Learning a lot.
	std::string newString;

	for (int i = 0; i < str.length(); i++) {

		if ((str[i] >= '0' && str[i] <= '9')) //if the character is an operand, add it to output string
			newString += str[i];

		else if (str[i] == '(') //if the character is an '(' push it to the stack
			myStack.push('(');

		//if the character is an ')', pop to output string from the stack
		//until an '(' is encountered.

		else if (str[i] == ')') {

			while (myStack.top() != 'N' && myStack.top() != '(') {

				char x = myStack.top();
				myStack.pop();
				newString += x;

			}
			if (myStack.top() == '(') {

				char x = myStack.top();
				myStack.pop();
			}
		}

		//if an operator
		else {
			while (myStack.top() != 'N' && operatorPrec(str[i]) <= operatorPrec(myStack.top())) {

				char x = myStack.top();
				myStack.pop();
				newString += x;
			}
			myStack.push(str[i]);
		}
	}

	//Pop all the remaining elements from the stack
	while (myStack.top() != 'N') {

		char x = myStack.top();
		myStack.pop();
		newString += x;
	}

	std::cout << newString << std::endl; //prints out the newly converted string

}


/*---------------------------------------------------------------
* errorCheck - checking every character in the string
* @param - string
* @return - true if valid, false otherwise printing error message
*/
bool errorCheck(std::string str) {


	for (int i = 0; i < str[i]; i++) {

		char isNum = str[i] >= '0' && str[i] <= '9';

		char isOp;

		switch (str[i]) {
		case '+':
		case '-':
		case '*':
		case '/':

			isOp = true;

			break;			//causes immediate exit from the switch structure


		default:

			isOp = false;
		}

		//if its NOT a number and is NOT an operater
		if (!isNum && !isOp) {

			std::cout << "Error\n";		//A thing I learned is where to place Error so that it prints once for each case of error check.
			return false;
		}
	}
	std::cout << "Error";
}


/*------------------------------------------------------
* executeOp - Function to perform arithmetic operations.
* @param - x, y, op
*/
int executeOp(int x, int y, char op) {

	switch (op) {

	case '+': return x + y; //if '+' then it should read it as an arithmetic, same goes for the rest!
	case '-': return x - y;
	case '*': return x * y;
	case '/': return x / y;
	}

}

///*---------------------------------------------------------------------------------
//* evaluateEquation - a function that returns a value of a given postfix expression. 
//					And makes use of the class Stack.
//* @param - string
//* @return - values.top() 
//*/
int evaluateEquation(std::string exp) { //going to use operatorPrec function and executeOp in this function

	int i;
	std::stack<int>values; //stack to store integer values

	std::stack<char>ops; //stack to store operators

	for (i = 0; i < exp.length(); i++) {

		//if it's whitespace then skip it
		if (exp[i] == ' ')
			continue; //terminats the current iteration and resumes the control to the next iteration of the loop.

		//if its an opening paranthases, push to 'ops' 
		else if (exp[i] == '(') {

			ops.push(exp[i]);
		}

		// if its a number then push it to the stack for numbers (values)
		else if (isdigit(exp[i])) { //isdigit is from cctype standard library which can be used to check if 
			int count = 0;			//the passed character is a digit or not.

			//this is in case the number being evaluated is more than one digit
			while (i < exp.length() && isdigit(exp[i])) {

				count = (count * 10) + (exp[i] - '0');
				i++;
			}
			values.push(count);

			//since the for loop increases the i, I would skip one token position
			//so I need to decrease the value of i by 1 to correct the offset.
			i--;
		}
		//if closing parantheses then solve entire equation in parantheses
		else if (exp[i] == ')') {

			while (!ops.empty() && ops.top() != '(') {

				int value2 = values.top();
				values.pop();

				int value1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(executeOp(value1, value2, op));
			}

			//pop opening paranthases
			if (!ops.empty())
				ops.pop();
		}

		//current expression is an operator
		else {

			//while top of 'ops' is equal to or greater precedence than the current token
			//put operator on top of 'ops' to top two elements in values stack.

			while (!ops.empty() && operatorPrec(ops.top()) >= operatorPrec(exp[i])) {
				int value2 = values.top();
				values.pop();

				int value1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(executeOp(value1, value2, op));
			}
			//push current token to 'ops'
			ops.push(exp[i]);
		}

	}

	//apply remaining ops to remaining values.
	while (!ops.empty()) {
		int value2 = values.top();
		values.pop();

		int value1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();
		values.push(executeOp(value1, value2, op));
	}

	//top of 'values' contains result, return it.
	return values.top();
}






