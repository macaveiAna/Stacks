//===================================================================
// @file:		Stacks.h
// @author:     Ana Macavei
// @version:    1.0
//
//  Demonstrates: Template Stack class definition and implementation.
//====================================================================
#ifndef STACKS_H
#define STACKS_H

template<typename type>
class Stack {
public:
	/**------------------------------------------------
	* Constructor
	*/
	Stack();

	/**------------------------------------------------
	* Pushes item on stack
	*
	*	@param itemToPush - the item to push onto the stack
	*	@return true if successful, false otherwise
	*/
	bool push(type itemToPush);

	/**------------------------------------------------
	* Pops item off of stack
	*
	*	@param itemPopped - the item removed from the stack (if successful)
	*	@return true if successful, false otherwise
	*/
	bool pop(type& itemPopped);

	/**------------------------------------------------
	* is stack full
	*
	*	@return true if full, false otherwise
	*/
	bool full();

	/**------------------------------------------------
	* is stack empty
	*
	*	@return true if empty, false otherwise
	*/
	bool empty();



private:
	const static type SIZE = 30;
	type topIndex; //index of top item; -1 if empty
	type data[SIZE];
};


//class implementation as template

template <typename type>
Stack<type>::Stack() {

	topIndex = -1;

}



template <typename type>
bool Stack<type>::push(type itemToPush) {

	if (full())
		return false;

	topIndex++;
	data[topIndex] = itemToPush;

	return true;

}

template <typename type>
bool Stack<type>::pop(type& itemPopped) {

	if (empty())
		return false;

	itemPopped = data[topIndex];
	topIndex--;
	return true;
}

template <typename type>
bool Stack<type>::full()
{
	if (topIndex == SIZE - 1)
		return true;
	else
		return false;
}

template <typename type>
bool Stack<type>::empty()
{
	if (topIndex < 0)
		return true;
	else
		return false;
}

#endif