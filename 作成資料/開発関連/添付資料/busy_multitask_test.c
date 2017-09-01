#include <stdio.h>
#include "includes.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2

/* Prints "Hello World" and sleeps for one second */
void task1(void* pdata)
{
	int i;
	for(i=0;i<10; i++)
    {
        printf("Hello from task1\n");
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
	OSTaskDel(TASK2_PRIORITY);
    printf("killed task2\n");

    while (1)
    {
        printf("Hello from task1\n");
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

/* Prints "Hello World" and sleeps for one second */
void task2(void* pdata)
{
	int i;
	  while (1)
	  {
		  printf("Hello from task2\n");

		  for(i=0; i<100000; i++)
		  {

		  }
	  }
}

/* The main function creates two task and starts multi-tasking */
int main(void)
{

  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);


  OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSStart();
  return 0;
}

