class World
{
	public:
		list<Particle> particles;
		list<Planet> planets;

		World()
		{
			Player player_a = Player();
			Player player_b = Player();

			for(unsigned int i = 0; i < 10000; i++)
			{	
				Particle particle = Particle();
				particle.setOwner(&player_a);

				particles.push_back(particle);
			}

			for(unsigned int i = 0; i < 10; i++)
			{
				planets.push_back(Planet());
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
					
					
					particle->speed.add(direction);

					planet->update(delta);
				}

				particle->update(delta);
			}
		}

		//Render world elements
		void render(SDL_Renderer* renderer, Camera camera)
		{
			for(list<Particle>::iterator it = particles.begin(); it != particles.end(); it++)
			{
				(*it).render(renderer, camera);
			}

			for(list<Planet>::iterator it = planets.begin(); it != planets.end(); it++)
			{
				(*it).render(renderer, camera);
			}
		}
};