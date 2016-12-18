class Circle
{
	public:
		float x, y;
		float radius;

		Circle()
		{
			x = 0;
			y = 0;
			radius = 1;
		}
		
		Circle(float _x, float _y, float _radius)
		{
			x = _x;
			y = _y;
			radius = _radius;
		}

		void set(float _x, float _y, float _radius)
		{
			x = _x;
			y = _y;
			radius = _radius;
		}

		bool intersetcs(Circle circle)
		{
			return MathUtils::distance(circle.x, x, circle.y, y) <= (radius + circle.radius);
		}
};