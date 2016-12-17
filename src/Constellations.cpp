#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>

#include <rtdk.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define TASK_MODE 0 //No flags
#define TASK_STKSZ 0 //Default stack size

#define TASK_A_PRIO 99 //Priority [0..99]
#define TASK_A_PERIOD_NS 1000000000 //Period in ns

#define TASK_B_PRIO 90
#define TASK_B_PERIOD_NS 45000000 

#define TASK_LOAD_NS 10000000 // Task execution time, in ns (same to all tasks)

class Constellations
{
	private:
	
	//Task decriptor
	RT_TASK task_a_desc; 
	RT_TASK task_b_desc;

	//Catches CTRL + C to allow a controlled termination of the application
	static void catch_signal(int sig){}

	static void wait_for_ctrl_c(void)
	{
		signal(SIGTERM, Constellations::catch_signal);
		signal(SIGINT, Constellations::catch_signal);

		// Wait for CTRL+C or sigterm
		pause();
		
		// Will terminate
		rt_printf("Terminating ...\n");
	}

	//Simulates the computational load of tasks
	static void simulate_load(RTIME load_ns)
	{
		RTIME ti, tf;
		
		ti = rt_timer_read();
		tf = ti+load_ns;
		while(rt_timer_read() < tf); // Busy wait

		return;
	}


	//Task body implementation
	static void task_code(void *task_period_ns)
	{
		RT_TASK *curtask;
		RT_TASK_INFO curtaskinfo;
		int *task_period;

		RTIME to = 0,ta = 0;
		unsigned long overruns;
		int err;
		
		//Get task information
		curtask = rt_task_self();
		rt_task_inquire(curtask,&curtaskinfo);
		rt_printf("%s init\n", curtaskinfo.name);
		task_period = (int *)task_period_ns;
		
		//Set task as periodic
		err = rt_task_set_periodic(NULL, TM_NOW, *task_period);
		while(1)
		{
			err = rt_task_wait_period(&overruns);
			ta = rt_timer_read();
			
			if(err)
			{
				rt_printf("%s overrun!!!\n", curtaskinfo.name);
				break;
			}
			
			rt_printf("%s activation\n", curtaskinfo.name);
			if(to != 0) 
			{
				rt_printf("Measured period (ns) =  %lu\n",ta-to);
			}

			to = ta;

			simulate_load(TASK_LOAD_NS);
		}

		return;
	}

	public:

	//Main function
	int main(int argc, char *argv[])
	{
		int err, 
		task_a_period_ns = TASK_A_PERIOD_NS, 
		task_b_period_ns = TASK_B_PERIOD_NS;

		//Perform auto-init of rt_print buffers if the task doesn't do so
		rt_print_auto_init(1);

		//Lock memory to prevent paging
		mlockall(MCL_CURRENT|MCL_FUTURE);

		//Create RT task
		// Args: descriptor, name, stack size, prioritry [0..99] and mode (flags for CPU, FPU, joinable ...)
		err = rt_task_create(&task_a_desc, "Task a", TASK_STKSZ, TASK_A_PRIO, TASK_MODE);
		if(err)
		{
			rt_printf("Error creating task a (error code  =  %d)\n",err);
			return err;
		} 
		else 
		{
			rt_printf("Task a created successfully\n");
		}

		err = rt_task_create(&task_b_desc, "Task b", TASK_STKSZ, TASK_B_PRIO, TASK_MODE);
		if(err)
		{
			rt_printf("Error creating task b (error code  =  %d)\n",err);
			return err;
		}
		else
		{ 
			rt_printf("Task b created successfully\n");
		}

		//Start RT task
		//Args: task decriptor, address of function/implementation and argument
		rt_task_start(&task_a_desc, &Constellations::task_code, (void *)&task_a_period_ns);
		rt_task_start(&task_b_desc, &Constellations::task_code, (void *)&task_b_period_ns);

		//Wait for termination signal
		wait_for_ctrl_c();

		return 0;
	}
};

int main(int argc, char *argv[])
{
	Constellations app;

	app.main(argc, argv);
}
