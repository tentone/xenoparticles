#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

#include <iostream>
#include <array>
#include <string>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>

#include <rtdk.h>

#include "math/MathUtils.cpp"
#include "math/Vector2.cpp"
#include "math/Color.cpp"
#include "math/Rectangle.cpp"
#include "math/Circle.cpp"

#include "graphics/Camera.cpp"
#include "graphics/ShapeRenderer.cpp"

#include "object/Player.cpp"
#include "object/Planet.cpp"
#include "object/Particle.cpp"
#include "object/World.cpp"

using namespace std;

//SDL Renderer and window
SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event event;

//World and camera
World world;
Camera camera;

//Tasks
RT_TASK task_update_world, task_input;

//Program status
bool alive = true;

class Constellations
{
	public:
		//Initialize SDL and start update and render tasks
		static int initialize()
		{
			if(SDL_Init(SDL_INIT_EVERYTHING))
			{
				rt_printf("Failed to initialize SDL");
				return -1;
			}

			window = SDL_CreateWindow("Constellations", 100, 100, 1024, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			if(window == nullptr)
			{
				rt_printf("Failed to create SDL Window");
				return -1;
			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == nullptr)
			{
				rt_printf("Failed to create SDL Renderer");
				return -1;
			}

			const int flags = IMG_INIT_PNG | IMG_INIT_JPG;
			if(IMG_Init(flags) != flags)
			{
				rt_printf("Failed to load the Image loading extensions");
				return -1;
			}

			if(TTF_Init() != 0)
			{
				rt_printf("Failed to load TTF extension");
				return -1;
			}

			//Perform auto-init of rt_print buffers if the task doesn't do so
			rt_print_auto_init(1);

			//Lock memory to prevent paging
			mlockall(MCL_CURRENT | MCL_FUTURE);

			//Start tasks
			if(!startTasks())
			{
				return -1;
			}

			//Render loop
			while(alive)
			{
				render();
			}

			//Dispose program
			dispose();

			return 0;
		}
		
		//Start tasks
		static bool startTasks()
		{
			int period = 16666666;

			//Update world task
			if(rt_task_create(&task_update_world, "World", 0, 90, T_CPU(0)))
			{
				rt_printf("Error creating update task");
				return false;
			}
			rt_task_start(&task_update_world, &taskUpdateWorld, (void *)&period);

			//Update input task
			if(rt_task_create(&task_input, "Input", 0, 50, T_CPU(1)))
			{
				rt_printf("Error creating input task");
				return false;
			}
			rt_task_start(&task_input, &taskInput, (void *)&period);

			return true;
		}

		//Destroy running tasks
		static void destroyTasks()
		{
			//TODO <ADD CODE HERE>
		}

		//Update simulation logic
		static void taskInput(void *task_period_ns)
		{
			unsigned int last = 0, time = 0;
			unsigned long overruns;

			RT_TASK *task = rt_task_self();
			RT_TASK_INFO task_info;

			rt_task_inquire(task, &task_info);
			rt_printf("Init %s\n", task_info.name);
			
			int *task_period = (int*) task_period_ns;
			
			//Set task as periodic
			int error = rt_task_set_periodic(NULL, TM_NOW, 16666666);
			
			while(1)
			{
				error = rt_task_wait_period(&overruns);
				time = rt_timer_read();
				
				unsigned int delta = time - last;

				if(error)
				{
					rt_printf("Overun: %luns\n", delta);
					break;
				}
				
				if(last != 0) 
				{
					rt_printf("Input: %luns\n", delta);
				}

				while(SDL_PollEvent(&event))
				{
					if(event.type == SDL_QUIT)
					{
						alive = false;
					}
					else if(event.type == SDL_KEYDOWN)
					{
						int key = event.key.keysym.scancode;
						
						if(key == SDL_SCANCODE_ESCAPE)
						{
							alive = false;
						}
						else if(key == SDL_SCANCODE_SPACE)
						{
							world.randomizePlanets();
						}
					}
					else if(event.type == SDL_MOUSEMOTION)
					{
						if(event.motion.state == SDL_PRESSED)
						{
							bool found = false;
							
							//Check if pressing a planet
							for(list<Planet>::iterator planet = world.planets.begin(); planet != world.planets.end(); planet++)
							{
								float x = event.motion.x / camera.zoom - camera.x;
								float y = event.motion.y / camera.zoom - camera.y;

								if(planet->contains(x, y))
								{
									found = true;
									planet->position.add(event.motion.xrel / camera.zoom, event.motion.yrel / camera.zoom);
									break;
								}
							}

							//Move camera
							if(!found)
							{
								camera.x += event.motion.xrel / camera.zoom;
								camera.y += event.motion.yrel / camera.zoom;
							}
						}
					}
					else if(event.type == SDL_MOUSEWHEEL)
					{
						camera.zoom += event.wheel.y * 0.1;
					}
				}

				last = time;
			}
		}

		//Update simulation logic
		static void taskUpdateWorld(void *task_period_ns)
		{
			unsigned int last = 0, time = 0;
			unsigned long overruns;

			RT_TASK *task = rt_task_self();
			RT_TASK_INFO task_info;

			rt_task_inquire(task, &task_info);
			rt_printf("Init %s\n", task_info.name);
			
			int *task_period = (int*) task_period_ns;
			
			//Set task as periodic
			int error = rt_task_set_periodic(NULL, TM_NOW, 16666666);
			
			while(1)
			{
				error = rt_task_wait_period(&overruns);
				time = rt_timer_read();
				
				unsigned int delta = time - last;

				if(error)
				{
					rt_printf("Overun: %luns\n", delta);
					//break;
				}
				
				if(last != 0) 
				{
					rt_printf("World Update: %luns\n", delta);
				}

				world.update(delta);

				last = time;
			}
		}

		//Render stuff into screen
		static void render()
		{
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			world.render(renderer, camera);

			SDL_RenderPresent(renderer);
		}

		//Dispose program
		static void dispose()
		{
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);

			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
		}
};

//Launch program
int main(int argc, char *argv[])
{
	Constellations app;

	app.initialize();
}
