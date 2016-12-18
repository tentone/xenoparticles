class Rectangle
{
	public:
		Vector2 position, size;

		Rectangle(float x, float y, float width, float height)
		{
			position.set(x, y);
			size.set(width, height);
		}

		void set(float x, float y, float width, float height)
		{
			position.set(x, y);
			size.set(width, height);
		}

		bool intersetcs(Rectangle rect)
		{
			//TODO <ADD CODE HERE>
		}
};