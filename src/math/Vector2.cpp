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

		Vector2 clone()
		{
			return Vector2(x, y);
		}

		void set(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		void copy(Vector2 vec)
		{
			x = vec.x;
			y = vec.y;
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

		void sub(Vector2 vec)
		{
			x -= vec.x;
			y -= vec.y;
		}

		void sub(float _x, float _y)
		{
			x -= _x;
			y -= _y;
		}

		void norm()
		{
			float len = length();
			
			if(len != 0)
			{
				x = x / len;
				y = y / len;
			}
		}

		float length()
		{
			return sqrt(x * x + y * y);
		}
 
		void multConst(float value)
		{
			x *= value;
			y *= value;
		}

		float distance(Vector2 vec)
		{
			return MathUtils::distance(x, vec.x, y, vec.y);
		}
};