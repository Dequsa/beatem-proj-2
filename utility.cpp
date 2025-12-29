#include "utility.h"
#include <cstdio>
#include <SDL.h>
// narysowanie napisu txt na powierzchni screen, zaczynajc od punktu (x, y)
// charset to bitmapa 128x128 zawierajca znaki
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
				SDL_Surface *charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text)
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt �rodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y)
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};

// rysowanie linii o d�ugo�ci l w pionie (gdy dx = 0, dy = 1)
// b�d� poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++)
	{
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// rysowanie prostok�ta o d�ugo�ci bok�w l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
				   Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void draw_sprite(SDL_Renderer *screen, SDL_Texture *sprite, const float x, const float y, float scale, SDL_RendererFlip flip)
{

	if (sprite == nullptr)
	{
		printf("Error: sprite texture is null!\n");
		return;
	}

	int w = 0;
	int h = 0;
	if (SDL_QueryTexture(sprite, NULL, NULL, &w, &h))
	{
		printf("Error querying texture: %s\n", SDL_GetError());
		return;
	}

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w * scale;
	dest.h = h * scale;

	// debug
	if (utility::DEBUG_MODE) 
	{
		printf("Drawing at X: %d, Y: %d, W: %d, H: %d\n", dest.x, dest.y, dest.w, dest.h);
	}

	SDL_RenderCopyEx(screen, sprite, NULL, &dest, 0, NULL, flip);
};

// SDL_FLIP_NONE = 0x00000000,     /**< Do not flip */
// SDL_FLIP_HORIZONTAL = 0x00000001,    /**< flip horizontally */
// SDL_FLIP_VERTICAL = 0x00000002     /**< flip vertically */