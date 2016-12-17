class Vector2
{
	public:
		float x, y;

		Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		void add(float _x, float _y)
		{
			x += _x;
			y += _y;
		}

		float distance(Vector2 vec)
		{
			return (vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y);
		}
};