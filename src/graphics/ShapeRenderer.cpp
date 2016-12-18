class ShapeRenderer
{
	public:
		static void renderRectangle(SDL_Renderer* renderer, Camera camera, Color color, Rectangle rectangle)
		{
			SDL_Rect rect;
			rect.x = rectangle.position.x + camera.x;
			rect.y = rectangle.position.y + camera.y;
			rect.w = rectangle.size.x;
			rect.h = rectangle.size.x;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
			
			SDL_RenderFillRect(renderer, &rect);
		}

		static void renderCircle(SDL_Renderer* renderer, Camera camera, Color color, Circle circle)
		{
			filledCircleRGBA(renderer, circle.x + camera.x, circle.y + camera.y, circle.radius * camera.zoom, color.r, color.g, color.b, 255);
		}
};