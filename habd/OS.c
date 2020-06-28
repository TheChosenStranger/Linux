/*
 * OS.c
 *
 *  Created on: Mar 24, 2020
 *      Author: Electronica CARE
 */

#include "STD_TYPES.h"
#include "SYSTICK_cfg.h"
#include "SYSTICK_interface.h"
#include "OS_cfg.h"
#include "OS.h"

/* bs mosh 3arfa enno static w hat set aslan f function el callback beta3t el systick da keda 3ady
 * wala eh wala ne5aleh global */
static u8 schedStartFlag = 0;

static taskInfo_t* Systasks[MAXTASKNUM];

/* Call back fuction for systick handler it is to set the flag that the tick has arrived */
void Sched_SystickCbf(void)
{
	schedStartFlag = 1;
}

/* at cfg file
 * Tick time must be configured in ms	*/
STD_ERROR Sched_init(void)
{
	/* Init SYSTICK to make an interrupt every tick time in micro sec */
	if(!SYSTICK_Init())
		return NOT_OK;
	if(!SYSTICK_SetTime(TICKTIMEUS))
		return NOT_OK;
	if(!SYSTICK_SetCallBack(&Sched_SystickCbf))
		return NOT_OK;

	return OK;
}

STD_ERROR Sched_Start(void)
{
	if(SYSTICK_Start() == NOT_OK )	/* Start Systick to start count */
		return NOT_OK;
	while(1)
	{
		while(!schedStartFlag);			/* when tick is arrived schedStartFlag will be 1 */
		schedStartFlag = 0;				/* return the flag again to 0 */
		Sched_Runnable();				/* then Sched will be executed */
	}
	return OK;
}

/* task struct has:
 * task Periodicity -> it must be in micro sec
 * firstDelayTicks -> number of ticks that scheduler stars count from
 * Runnable -> task function to execute
 * taskPriority -> it will return error if it exceeds the array of tasks limit */
STD_ERROR Sched_CreatTask(task_t* task,u32 taskPriority)
{
	if( (taskPriority >= MAXTASKNUM) || (TICKTIMEUS == 0) )
		return NOT_OK;
	Systasks[taskPriority]->AppTask->Runnable = task->Runnable;
	Systasks[taskPriority]->AppTask->Periodicity = task->Periodicity;
	Systasks[taskPriority]->AppTask->firstDelayTicks = task->firstDelayTicks;
	Systasks[taskPriority]->ticksToExecute = (task->Periodicity / TICKTIMEUS) - 1 ;
	Systasks[taskPriority]->taskState = READY;
	return OK;
}

STD_ERROR Task_Suspend(taskInfo_t* task)
{
	ErrorStatus loc_err = NOT_OK;
	/* task must be ready first to make it suspended */
	if(task->taskState == READY)
	{
		task->taskState = SUSPENDED;
		loc_err = OK;
	}

	return loc_err;
}

STD_ERROR Task_Resume(taskInfo_t* task)
{
	task->flagIfResume = 1;
	return OK;
}

/* Period -> must be in micro sec
 * and it must be smaller than task periodicity time
 * Copy_taskID -> must be one of the application tasks id */
STD_ERROR Task_Pause(taskInfo_t* task, u32 Period)
{
	ErrorStatus loc_err = NOT_OK;
	/* task must be ready first to make it suspended */
	/* and Period must be larger than task Periodicity */
	if((task->taskState == READY)&&(Period>task->AppTask->Periodicity))
	{
		task->taskState = PAUSED;
		task->countIfPause = Period / task->AppTask->Periodicity;
		loc_err = OK;
	}

	return loc_err;
}

STD_ERROR Task_Delete(taskInfo_t* task)
{
	task->taskState = IDEAL;
	task->AppTask->Runnable = NULL;

	return OK;
}

void Sched_Runnable(void)
{
	u32 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i]->ticksToExecute == 0)
		{
			switch(Systasks[i]->taskState)
			{
			case READY:
				if(Systasks[i]->AppTask->Runnable == NULL)
					break;
				Systasks[i]->AppTask->Runnable();
				break;
			case PAUSED:
				Systasks[i]->countIfPause--;
				if(Systasks[i]->countIfPause == 0)
					Systasks[i]->taskState = READY;
				break;
			case SUSPENDED:
				if(Systasks[i]->flagIfResume)
				{
					Systasks[i]->taskState = READY;
					Systasks[i]->flagIfResume = 0;
				}
				break;
			}

			Systasks[i]->ticksToExecute = (Systasks[i]->AppTask->Periodicity / TICKTIMEUS) - 1 ;
		}
		else
			Systasks[i]->ticksToExecute--;
	}
}




