class Color
{
	public:
		unsigned int r, g, b;

		Color()
		{
			r = 0;
			g = 0;
			b = 0;
		}

		Color(unsigned int _r, unsigned int _g, unsigned int _b)
		{
			r = _r;
			g = _g;
			b = _b;
		}

		void set(unsigned int _r, unsigned int _g, unsigned int _b)
		{
			r = _r;
			g = _g;
			b = _b;
		} 
};