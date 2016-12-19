class Color
{
	public:
		Uint8 r, g, b;

		Color()
		{
			r = 0;
			g = 0;
			b = 0;
		}

		Color(Uint8 _r, Uint8 _g, Uint8 _b)
		{
			r = _r;
			g = _g;
			b = _b;
		}

		void set(Uint8 _r, Uint8 _g, Uint8 _b)
		{
			r = _r;
			g = _g;
			b = _b;
		}

		int getHex()
		{
			return (255 << 24) + (b << 16) + (g << 8) + r;
		}
};