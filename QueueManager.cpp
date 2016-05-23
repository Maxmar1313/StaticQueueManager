
#include "QueueManager.h"
#include <bitset>

namespace QueueManager
{
	short numberOfQueues = 0;
	//Bitset used to hold informations,whether particular QueueHandle is used or not
	std::bitset<MAX_QUEUES> bitset;

	struct cell
	{
		unsigned char data;
		QueueHandle handler;
		cell *next;
	}
	memoryBlock[MAX_DATA_SIZE];

	cell *head;
	cell *tail;
	short availableMemory = MAX_DATA_SIZE;

	void isQueueDestroyed(QueueHandle queueHandle);
	void pop(cell *next, cell *previous);
	void isItForbiddenQueueHandleValue(QueueHandle queueHandle);

	// Performs any necessary initialization of the QueueManager.
	void initializeQueueManager()
	{
		//at this time, memory block is empty, so head and tail of memory block are its first element
		head = &memoryBlock[0];
		tail = &memoryBlock[0];
		bitset.reset();
	}

	// Creates a FIFO byte queue, returns the handle for the created queue.
	QueueHandle createQueue()
	{
		//this functions,checks if queue can be registred
		if (numberOfQueues == MAX_QUEUES)
		{
			onIllegalOperation("No more queues can be registred");
		}
		 //if there is any available Queuehandle(bitset element with 0 value), "creates"/"register" queue and returns handle value
		for (unsigned char i = 1; i <MAX_QUEUES; i++)
		{
			if (!bitset.test(i))
			{
				bitset.set(i);
				++numberOfQueues;
				return i;
			}
		}
	}

	// Destroy the queue specified by queueHandle.
	void destroyQueue(QueueHandle queueHandle)
	{
		isItForbiddenQueueHandleValue(queueHandle);
		//this function, checks if queueHandle is already destroyed, if so, print error
		isQueueDestroyed(queueHandle);

		/*pop every element in memoryBlock that have handler equal to queueHandle
		increase availableMemory by 1 for every pop operation made
		reset queueHandle(th) bitsets element(set to 0 value)*/
		cell *current = head;
		cell *previous = NULL;

		for (int i = 0; i < MAX_DATA_SIZE; i++)
		{
			if (current->handler == queueHandle)
			{
				pop(current, previous);
				++availableMemory;
			}
			else
			{
				cell *tempcell = current;
				current = tempcell->next;
			}
			previous = current;
		}

		bitset.reset(queueHandle);
		--numberOfQueues;
	}

	 // Adds a new byte to the queue specified by queueHandle.
	void enQueue(QueueHandle queueHandle, unsigned char value)
	{
		isItForbiddenQueueHandleValue(queueHandle);
		//this function, checks if queue was't already destroyed, if so, print error
		isQueueDestroyed(queueHandle);

		//test whether or not there is any available memory 
		if (availableMemory == 0)
		{
			onOutOfMemory();
		}
		else
		{	/*find first free cell in memoryBlock,and allocate that cell
			decrease available memory by 1.*/
			for (int i = 0; i < MAX_DATA_SIZE; i++)
			{
				if (memoryBlock[i].handler == 0)
				{
					memoryBlock[i].data = value;
					memoryBlock[i].handler = queueHandle;
					tail->next = &memoryBlock[i];
					tail = &memoryBlock[i];
					--availableMemory;
					break;
				}
			}
		}
	}

	// Pops the next byte off the queue specified by queueHandle.
	unsigned char deQueue(QueueHandle queueHandle)
	{
		isItForbiddenQueueHandleValue(queueHandle);
		isQueueDestroyed(queueHandle);

		//take head of a list
		cell *current = head;
		cell *previous = NULL;

		/*find first element in list with handler equal to queueHandle and pop that element
		increase availableMemory by 1, if no element found with provided queue handle, print error (attempt to deque empty queue.)*/
		for (int i = 0; i < MAX_DATA_SIZE; i++)
		{
			if (current->handler == queueHandle)
			{
				pop(current, previous);
				++availableMemory;
				return current->data;
			}
			else
			{
				cell *tempcell = current;
				current = tempcell->next;
			}
			previous = current;
		}
		onIllegalOperation("Queue is empty");
	}
	//function that swaps previous cells pointer to next cell pointer
	void pop(cell *current, cell *previous)
	{
		/*check,whether element to be poped is head of a list
		if so, next element of a list is head now.*/
		if (current == head)
		{
			head = current->next;
			current->handler = 0;
		}
		else
			if (current == tail)
			{
				current->handler = 0;
				tail = previous;
			}
			else//pop element and swap previous elements "next" pointer, to next element.
			{
				current->handler = 0;
				previous->next = current->next;
			}
	}
	
	void isQueueDestroyed(QueueHandle queueHandle)
	{
		if (!bitset.test(queueHandle))
		{
			onIllegalOperation("Queue was destroyed");
		}
	}
	void isItForbiddenQueueHandleValue(QueueHandle queueHandle)
	{
		if (queueHandle == 0)
		{
			onIllegalOperation("Access with queueHandle of 0 value");
		}
	}
};
