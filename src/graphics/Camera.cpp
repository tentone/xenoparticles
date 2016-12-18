class Camera
{
	public:
		float x, y;
		float zoom;

		Camera()
		{
			x = 0;
			y = 0;
			zoom = 1.0;
		}

		Camera(float _x, float _y, float _zoom)
		{
			x = _x;
			y = _y;
			zoom = _zoom;
		}
};