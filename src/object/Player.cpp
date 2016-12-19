using namespace std;

class Player
{
	public:
		unsigned int id;
		string name;
		
		Color color;

		Player()
		{
			id = random();
			name = "player";
			color.set(255, 0, 0);
		}

		void setColor(unsigned int r, unsigned int g, unsigned int b)
		{
			color.set(r, g, b);
		}
};