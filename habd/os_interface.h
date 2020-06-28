#ifndef OS_INTERFACE
#define OS_INTERFACE 

typedef enum task_stat{
	RUNNING,
	PAUSED,
	SUSPENDED,
	STOPPED
}task_stat_t;

typedef struct task_{
	void (*Callback)(void);
	u32 Periodicity;
	u32 FirstDelay;
}os_task_t;

typedef struct sched_task{
	os_task_t os_task;
	u32 ticksToExecute;
	task_stat_t Status;
	u32 PauseTickDuration;
}os_sched_task_t;


void OS_SysTickCallbackFnc(void);
STD_ERR OS_Init(void);
void OS_Start(void);
void OS_Schedular(void);
STD_ERR OS_CreateTask(os_task_t* Copy_os_task_t_ptr,u32 Copy_u32Priority);
STD_ERR OS_PauseTask(u32);
void OS_SuspendTask();
void OS_KillTask();

#endif