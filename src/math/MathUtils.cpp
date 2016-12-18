class MathUtils
{
	public:
		static float random()
		{
			return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}

		static float random(float min, float max)
		{
			return min + random() * (max - min);
		}

		static float distance(float xa, float xb, float ya, float yb)
		{
			return sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
		}
};