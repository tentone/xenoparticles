using namespace std;

class Planet
{
	public:
		Vector2 position;
		float radius;

		float mass;

		Planet()
		{
			position = Vector2(MathUtils::random(0, 640), MathUtils::random(0, 480));

			radius = MathUtils::random(20, 40);
			mass = 1000;
		}

		void update(unsigned int delta)
		{
			//TODO <ADD CODE HERE>
		}

		void render(SDL_Renderer* renderer)
		{
			SDL_Rect rect;
			rect.x = position.x - radius;
			rect.y = position.y - radius;
			rect.w = radius * 2;
			rect.h = radius * 2;

			SDL_SetRenderDrawColor(renderer, 30, 30, 200, SDL_ALPHA_OPAQUE);

			SDL_RenderFillRect(renderer, &rect);
		}
};