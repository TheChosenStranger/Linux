#ifndef OS_H
#define OS_H

typedef u8 taskState_t;
#define NULL ((void *)0)

#define SUSPENDED			0
#define READY				1
#define PAUSED				2
#define IDEAL				3

/* struct for user */
/* da elle el user bydhony ya3ny fieh el 7agat ele m7tagha men el user */
typedef struct
{
	taskRunnable_t Runnable;			/* Pointer to Task Function */
	u32 Periodicity;
	u32 firstDelayTicks;				/* Number of ticks to start task at it */
	u32 taskID;							/* id for each task */
} task_t;

/* da ba2a fie el zyadat ele btt7seb hena bona2n 3ala elle by7sal  */
typedef struct
{
	task_t* AppTask;
	u32 ticksToExecute;
	u8 countIfPause;
	u8 flagIfResume=0;
	taskState_t taskState;
} taskInfo_t ;

extern STD_ERROR Sched_init(void);
extern STD_ERROR Sched_CreatTask(task_t* task,u32 taskPriority);
extern STD_ERROR Sched_Start(void);
extern void Sched_Runnable(void);
extern void Sched_SystickCbf(void);
extern STD_ERROR Task_Suspend(u32 Copy_taskID);
extern STD_ERROR Task_Pause(u32 Copy_taskID, u32 Period);
extern STD_ERROR Task_Delete(u32 Copy_taskID);

#endif
