#include "STD_TYPES.h"
#include "SYSTICK_interface.h"
#include "os_interface.h"
#include "os_config.h"

static u8 OS_Flag;
static os_sched_task_t OS_tasks[MAX_TASKS];
static u32 TaskPriority;

/*function called by systick when a single tick passes increment os tick counter*/
void OS_SysTickCallbackFnc(void){
	OS_Flag++;
}
/*	init function for os
 *	inits systick
 *	sets tick time
 *	sets callback fnc
*/
STD_ERR OS_Init(void){
	STD_ERR Local_STD_ERR_Stat=OK;
	Local_STD_ERR_Stat=SYSTICK_Init();
	if(Local_STD_ERR_Stat==OK)
		Local_STD_ERR_Stat=SYSTICK_SetTime(TICKTIMEUS);
	if(Local_STD_ERR_Stat==OK)
		Local_STD_ERR_Stat=SYSTICK_SetCallback(&OS_SysTickCallbackFnc);
	return Local_STD_ERR_Stat;
}
/*	start os
 *	whenever a tick passes run schedular
*/
void OS_Start(void){
	SYSTICK_StartTimer();
	while(1){
		if(OS_Flag>0){
			/****disable int**/
			OS_Flag--;
			/***enable int***/
			OS_Schedular();
		}
	}
}
/*schedualar loops on system tasks and executes them in order of prioriry no preemption*/
void OS_Schedular(void){
	for (TaskPriority = 0; TaskPriority < MAX_TASKS; ++TaskPriority)
	{
		if(OS_tasks[TaskPriority]->Callback){
			if(OS_tasks[TaskPriority].ticksToExecute==0){
				switch(OS_tasks[TaskPriority].Status){
					case RUNNING:
						OS_tasks[TaskPriority].os_task.Callback();
						OS_tasks[TaskPriority].ticksToExecute=(Copy_os_task_t_ptr->Periodicity/TICKTIMEUS)-1;
						break;
					case PAUSED:
						OS_tasks[Copy_u32Priority].PauseTickDuration--;
						if(OS_tasks[Copy_u32Priority].PauseTickDuration==0)
							OS_tasks[TaskPriority].Status=RUNNING;
						break;
				}
			}
			else{
				OS_tasks[Copy_u32Priority].ticksToExecute--;
			}
		}
	}
}
/**/
STD_ERR OS_CreateTask(os_task_t* Copy_os_task_t_ptr,u32 Copy_u32Priority){
	STD_ERR Local_STD_ERR_Stat=OK;
	if(Copy_u32Priority>MAX_TASKS)
		Local_STD_ERR_Stat=NOT_OK;
	else{
		OS_tasks[Copy_u32Priority].os_task.Callback=Copy_os_task_t_ptr->Callback;
		OS_tasks[Copy_u32Priority].os_task.Periodicity=Copy_os_task_t_ptr->Periodicity;
		OS_tasks[Copy_u32Priority].os_task.FirstDelay=Copy_os_task_t_ptr->FirstDelay;
		OS_tasks[Copy_u32Priority].ticksToExecute=
					((Copy_os_task_t_ptr->Periodicity+Copy_os_task_t_ptr->FirstDelay)/TICKTIMEUS)-1;
		OS_tasks[Copy_u32Priority].Status=RUNNING;
		OS_tasks[Copy_u32Priority].PauseTickDuration=0;
	}
	return Local_STD_ERR_Stat;
}
STD_ERR OS_PauseTask(u32 Copy_u32PauseDurationUS){
	STD_ERR Local_STD_ERR_Stat=OK;
	if(Copy_u32PauseDurationUS>OS_tasks[TaskPriority].os_task.Periodicity)
		Local_STD_ERR_Stat=NOT_OK;
	else{
		OS_tasks[TaskPriority].PauseTickDuration=
			(Copy_u32PauseDurationUS/OS_tasks[TaskPriority].os_task.Periodicity);
		OS_tasks[TaskPriority].Status=PAUSED;
	}
	return Local_STD_ERR_Stat;
}
void OS_SuspendTask(){
	OS_tasks[TaskPriority].Status=SUSPENDED;
}
void OS_KillTask(){
	OS_tasks[TaskPriority].Status=STOPPED;
	OS_tasks[TaskPriority].os_task.Callback=NULL;
}
