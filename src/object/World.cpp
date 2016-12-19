class World
{
	public:
		list<Particle> particles;
		list<Planet> planets;

		World()
		{
			Player a = Player();
			a.setColor(200, 20, 20);

			Player b = Player();
			b.setColor(20, 20, 200);

			//Create Creatures
			for(unsigned int i = 0; i < 15000; i++)
			{	
				particles.push_back(Particle(a));
				particles.push_back(Particle(b));
			}

			//Create planets
			for(unsigned int i = 0; i < 10; i++)
			{
				planets.push_back(Planet());
			}
		}

		//Randomize planet positions
		void randomizePlanets()
		{
			for(list<Planet>::iterator planet = planets.begin(); planet != planets.end(); planet++)
			{
				planet->position.set(MathUtils::random(0, 600), MathUtils::random(0, 600));
			}
		}

		//Update world elements
		void update(unsigned int delta)
		{
			for(list<Particle>::iterator particle = particles.begin(); particle != particles.end(); particle++)
			{
				//Calculate planet gravity
				for(list<Planet>::iterator planet = planets.begin(); planet != planets.end(); planet++)
				{
					Vector2 direction = planet->position.clone();
					direction.sub(particle->position);
					direction.norm();
					
					float distance = particle->position.distance(planet->position);

					if(distance > planet->radius)
					{
						direction.multConst(1 / distance);	
					}
					else
					{
						direction.multConst(-0.3);
					}
					
					particle->speed.add(direction);

					planet->update(delta);
				}

				//Update particle movement
				particle->update(delta);
			}
		}

		//Render world elements
		void render(SDL_Renderer* renderer, Camera camera)
		{
			//Draw particles
			for(list<Particle>::iterator it = particles.begin(); it != particles.end(); it++)
			{
				(*it).render(renderer, camera);
			}

			//Draw planets
			for(list<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
			{
				(*it).render(renderer, camera);
			}
		}
};