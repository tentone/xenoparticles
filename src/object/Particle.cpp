class Particle
{
	public:
		Vector2 position;
		Vector2 speed;

		float friction;
		float mass;

		Player* owner;
		
		Particle()
		{
			position = Vector2(MathUtils::random(0, 500), MathUtils::random(0, 500));
			speed = Vector2(0, 0);
			
			friction = 0.99;
			mass = 1;

			owner = nullptr;
		}

		//Set Particle owner
		void setOwner(Player* _owner)
		{
			owner = _owner;
		}

		//Update particle state
		void update(unsigned int delta)
		{
			speed.add(MathUtils::random(-0.1, 0.1), MathUtils::random(-0.1, 0.1));

			position.add(speed);

			speed.multConst(friction);
		}

		//Render particle
		void render(SDL_Renderer* renderer, Camera camera)
		{
			ShapeRenderer::renderRectangle(renderer, camera, Color(200, 30, 30), Rectangle(position.x - 1, position.y - 2, 2, 2));
		}
};