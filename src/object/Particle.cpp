class Particle
{
	public:
		Vector2 position, speed;

		float friction, mass;
		float turbulence;

		Player owner;
		
		Particle()
		{
			position = Vector2(MathUtils::random(0, 500), MathUtils::random(0, 500));
			speed = Vector2(0, 0);
			
			friction = 1.0; //0.99;
			turbulence = 0.04;
			mass = 1;
		}

		Particle(Player _owner)
		{
			position = Vector2(MathUtils::random(0, 500), MathUtils::random(0, 500));
			speed = Vector2(0, 0);
			
			friction = 0.99;
			turbulence = 0.002;
			mass = 1;

			owner = _owner;
		}

		//Set Particle owner
		void setOwner(Player _owner)
		{
			owner = _owner;
		}

		//Update particle state
		void update(unsigned int delta)
		{
			speed.add(MathUtils::random(-turbulence, turbulence), MathUtils::random(-turbulence, turbulence));

			position.add(speed);

			speed.multConst(friction);
		}	

		//Render particle
		void render(SDL_Renderer* renderer, Camera camera)
		{
			ShapeRenderer::renderRectangle(renderer, camera, owner.color, Rectangle(position.x - 1, position.y - 1, 2, 2));
		}
};