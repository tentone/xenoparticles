#define PLANET_ATTRACTOR 0
#define PLANET_REPULSER 1

using namespace std;

class Planet
{
	public:
		Vector2 position;
		float radius, mass;
		int type;

		Planet()
		{
			position.set(MathUtils::random(0, 600), MathUtils::random(0, 600));
			radius = MathUtils::random(20, 30);
			
			mass = 1000;
			type = PLANET_ATTRACTOR;
		}

		Planet(float x, float y, float _radius)
		{
			position.set(x, y);
			radius = _radius;
			
			mass = 1000;
			type = PLANET_ATTRACTOR;
		}

		//Change planet type
		void toggleType()
		{
			type = (type == PLANET_ATTRACTOR) ? PLANET_REPULSER : PLANET_ATTRACTOR;
		}

		//Check is planet contains point
		bool contains(float _x, float _y)
		{
			return MathUtils::distance(_x, position.x, _y, position.y) <= radius;
		}

		//Update planet state
		void update(unsigned int delta){}

		//Render planet to screen
		void render(SDL_Renderer* renderer, Camera camera)
		{
			ShapeRenderer::renderCircle(renderer, camera, Color(100, 20, 100), Circle(position.x, position.y, radius));
		}
};