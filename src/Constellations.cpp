#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>

#include <rtdk.h>

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Project files
#include "Vector2.cpp"

class Constellations
{
	private:
		//Catches CTRL + C to allow a controlled termination of the application
		static void catchSignal(int sig){}

		static void waitExitSignal(void)
		{
			signal(SIGTERM, catchSignal);
			signal(SIGINT, catchSignal);

			//Wait for CTRL+C or sigterm
			pause();
		}

	public:
		//Initialize
		static int initialize()
		{
			//Perform auto-init of rt_print buffers if the task doesn't do so
			rt_print_auto_init(1);

			//Lock memory to prevent paging
			mlockall(MCL_CURRENT|MCL_FUTURE);

			//60 fps target
			int period = 16666666;

			//Update task
			RT_TASK task_update;
			if(rt_task_create(&task_update, "Update", 0, 99, 0))
			{
				rt_printf("Error creating update task");
				return -1;
			}
			rt_task_start(&task_update, &update, (void *)&period);

			//Render task
			RT_TASK task_render;
			if(rt_task_create(&task_render, "Render", 0, 95, 0))
			{
				rt_printf("Error creating render task");
				return -1;
			}
			rt_task_start(&task_render, &render, (void *)&period);

			//Wait for termination signal
			waitExitSignal();

			return 0;
		}
		
		//Update simulation logic
		static void update(void *task_period_ns)
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
			}
		}

		//Render stuff into screen
		static void render(void *task_period_ns)
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
			}
		}
};

//Launch program
int main(int argc, char *argv[])
{
	Constellations app;

	app.initialize();
}
