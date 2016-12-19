class ShapeRenderer
{
	public:
		static void renderRectangle(SDL_Renderer* renderer, Camera camera, Color color, Rectangle rectangle)
		{
			SDL_Rect rect;
			rect.x = (rectangle.position.x + camera.x) * camera.zoom;
			rect.y = (rectangle.position.y + camera.y) * camera.zoom;
			rect.w = rectangle.size.x * camera.zoom;
			rect.h = rectangle.size.y * camera.zoom;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
			
			SDL_RenderFillRect(renderer, &rect);
		}

		static void renderCircle(SDL_Renderer* renderer, Camera camera, Color color, Circle circle)
		{
			filledCircleColor(renderer, (circle.x + camera.x) * camera.zoom, (circle.y + camera.y) * camera.zoom, circle.radius * camera.zoom, color.getHex());
		}
};