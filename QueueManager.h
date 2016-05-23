// 
// - Your implementation should not require that you change this file at all.
//
#pragma once

#ifndef __QUEUEMANAGER_H__
#define __QUEUEMANAGER_H__

#define MAX_QUEUES    64
#define MAX_DATA_SIZE 2048

namespace QueueManager
{
	// Queue handles are a single byte.  Do not change the typedef!
	typedef unsigned char QueueHandle;

	// Performs any necessary initialization of the QueueManager.
	void initializeQueueManager();

	// Creates a FIFO byte queue, returns the handle for the created
	// queue.
	QueueHandle createQueue();

	// Destroy the queue specified by queueHandle.
	void destroyQueue(QueueHandle queueHandle);

	// Adds a new byte to the queue specified by queueHandle.
	void enQueue(QueueHandle queueHandle, unsigned char value);

	// Pops the next byte off the queue specified by queueHandle.
	unsigned char deQueue(QueueHandle queueHandle);

	// If you are unable to satisfy a request due to lack of memory your 
	// code should call this provided failure function (which will not return):
	void onOutOfMemory();

	// If the caller makes any illegal request your code should call this 
	// provided failure function (which will not return):
	void onIllegalOperation(const char* fmt = 0, ...);
	// eg:
	//   int errorCode;
	//   ...
	//   onIllegalOperation("Error in createQueue: %d", errorCode);
}

#endif
#pragma once
