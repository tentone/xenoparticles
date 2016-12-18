class Circle
{
	public:
		Vector2 position;
		float radius;

		Circle(float x, float y, float _radius)
		{
			position.set(x, y);
			radius = _radius;
		}

		bool intersetcs(Circle circle)
		{
			return circle.position.distance(position) <= (radius + circle.radius);
		}
};