// 
// - Your implementation should not require that you change this file at all.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include "QueueManager.h"

int main(void)
{
	using namespace QueueManager;
	initializeQueueManager();
	
	QueueHandle queue0 = createQueue();
	enQueue(queue0, 0);
	enQueue(queue0, 1);

	QueueHandle queue1 = createQueue();
	enQueue(queue1,3);
	enQueue(queue0, 2);
	enQueue(queue1, 4);
	
	printf("%d ", deQueue(queue0));
	printf("%d\n", deQueue(queue0));
	
	enQueue(queue0, 5);
	enQueue(queue1, 6);

	printf("%d ", deQueue(queue0));
	printf("%d\n",deQueue(queue0));

	destroyQueue(queue0);

	printf("%d ", deQueue(queue1));
	printf("%d ", deQueue(queue1));
	printf("%d\n", deQueue(queue1));

	destroyQueue(queue1);
	getchar();
		return 0;
}

namespace QueueManager
{
	void onOutOfMemory()
	{
		std::cerr << "QueueHandle out of memory" << std::endl;
		exit(1);
	}

	void onIllegalOperation(const char* fmt, ...)
	{
		if (fmt == NULL)
		{
			std::cerr << "Unknown illegal operation" << std::endl;
			exit(1);
		}
		else
		{
			char	buf[8192];

			va_list argptr;
			va_start(argptr, fmt);
			vsprintf_s(buf, fmt, argptr);
			va_end(argptr);

			std::cerr << "Illegal operation: \"" << buf << "\"" << std::endl;
			exit(1);
		}
	}
}

