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
};