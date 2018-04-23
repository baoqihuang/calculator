/*
 * QUEUE
 *
 *  Created on: Jul 10, 2017
 *      Author: michaelhuang
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
   // Structure for the queue nodes
   struct QueueNode
   {
      T value;          // Value in the node
      QueueNode *next;  // Pointer to next node
   };

   QueueNode *front;    // Pointer to the queue front
   QueueNode *rear;     // Pointer to the queue rear
   int count;

public:
   //Constructor
   Queue(){front = rear = NULL; count = 0;}

   // Destructor
   ~Queue();

   // Stack operations
   bool enqueue(const T);
   bool dequeue(T &);
   bool isEmpty()  const;
   void print() const;
};

/**~*~*
   Destructor
*~**/
template <class T>
Queue<T>::~Queue()
{
   QueueNode *currNode, *nextNode;

   // Position nodePtr at the top of the stack.
   currNode = front;

   // Traverse the list deleting each node.
   while (currNode) //while (currNode != NULL)
   {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}




/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class T>
bool Queue<T>::isEmpty()  const
{
   return count == 0;
}

/**~*~*
  Member function enqueue inserts the argument into
  the queue.
*~**/
template <class T>
bool Queue<T>::enqueue(const T item)
{
   QueueNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new QueueNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = NULL;

   if( front == NULL )        // insert to an empty queue
       front = newNode;
   else
       rear->next = newNode;

   count++;
   rear = newNode;

   return true;
}

/**~*~*
  Member function dequeue deletes the value at the front
  of the queue, and copies it into the variable
  passed as an argument.
*~**/
template <class T>
bool Queue<T>::dequeue(T &item)
{
    QueueNode *pDel; // Temporary pointer

    // empty queue
    if (count == 0)
       return false;

   // delete the value at the front of the queue
    item = front->value;
    pDel = front;

    if( count == 1 )
      rear = front = NULL;
    else
      front = front->next;

    count--;
    delete pDel;

   return true;
}


/**~*~*
  Member function print prints every single node in the queue respectively, separate by blank.
*~**/
template <class T>
void Queue<T>::print()  const
{

	cout << "Contents of queue: ";
	QueueNode *nodePtr = front;
	while (nodePtr != nullptr)
	{
		cout << nodePtr->value << " ";
		nodePtr = nodePtr->next;
	}
	cout << endl;
}

#endif /* QUEUE_ */
