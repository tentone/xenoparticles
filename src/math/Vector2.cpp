class Vector2
{
	public:
		float x, y;
		
		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		void set(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		void add(Vector2 vec)
		{
			x += vec.x;
			y += vec.y;
		}

		void add(float _x, float _y)
		{
			x += _x;
			y += _y;
		}

		void multConst(float value)
		{
			x *= value;
			y *= value;
		}

		float distance(Vector2 vec)
		{
			return pow((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y), 2);
		}
};