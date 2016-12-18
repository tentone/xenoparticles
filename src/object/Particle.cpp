
class Particle
{
	public:
		Vector2 position;
		Vector2 speed;

		float friction;
		float mass;

		//World* world;
		Player* owner;

		Particle()
		{
			position = Vector2(MathUtils::random(0, 640), MathUtils::random(0, 480));
			speed = Vector2(MathUtils::random(-1, 1), MathUtils::random(-1, 1));
			
			friction = 0.99;
			mass = 1;

			owner = nullptr;
		}

		//Update particle state
		void update(unsigned int delta)
		{
			position.add(speed);

			speed.multConst(friction);
		}

		//Render particle
		void render(SDL_Renderer* renderer)
		{
			SDL_Rect rect;
			rect.x = position.x - 2;
			rect.y = position.y - 2;
			rect.w = 4;
			rect.h = 4;

			SDL_SetRenderDrawColor(renderer, 200, 30, 30, SDL_ALPHA_OPAQUE);

			SDL_RenderFillRect(renderer, &rect);
		}
};