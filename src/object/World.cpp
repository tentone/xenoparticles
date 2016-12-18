class World
{
	public:
		array<Particle, 10000> particles;
		array<Planet, 10> planets;

		World()
		{
			//TODO <ADD CODE HERE>
		}

		//Update world elements
		void update(unsigned int delta)
		{
			for(unsigned int i = 0; i < particles.size(); i++)
			{
				particles[i].update(delta);
			}
		}

		//Render world elements
		void render(SDL_Renderer* renderer)
		{
			for(unsigned int i = 0; i < planets.size(); i++)
			{
				planets[i].render(renderer);
			}

			for(unsigned int i = 0; i < particles.size(); i++)
			{
				particles[i].render(renderer);
			}
		}
};