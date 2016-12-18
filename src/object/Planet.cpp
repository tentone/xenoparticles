using namespace std;

class Planet
{
	public:
		Vector2 position;
		float radius;

		float mass;

		Planet()
		{
			position.set(MathUtils::random(0, 640), MathUtils::random(0, 480));
			radius = MathUtils::random(20, 30);
			
			mass = 1000;
		}

		void update(unsigned int delta)
		{
			//TODO <ADD CODE HERE>
		}

		void render(SDL_Renderer* renderer, Camera camera)
		{
			ShapeRenderer::renderCircle(renderer, camera, Color(20, 20, 200), Circle(position.x, position.y, radius));
		}
};