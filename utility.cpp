#include "utility.h"
#include "structs.h"
#include <cstdio>
#include <SDL.h>
// narysowanie napisu txt na powierzchni screen, zaczynajc od punktu (x, y)
// charset to bitmapa 128x128 zawierajca znaki

namespace DrawingFunctions
{
	void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset, float scale)
	{
		int px, py, c;
		SDL_Rect s, d;
		s.w = 8;
		s.h = 8;
		d.w = static_cast<int>(8 * scale);
		d.h = static_cast<int>(8 * scale);
		while (*text)
		{
			c = *text & 255;
			px = (c % 16) * 8;
			py = (c / 16) * 8;
			s.x = px;
			s.y = py;
			d.x = x;
			d.y = y;
			SDL_BlitScaled(charset, &s, screen, &d);
			x += static_cast<int>(8 * scale);
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

	void DrawSprite(SDL_Renderer *screen, SDL_Texture *sprite, const float x, const float y, float scale, SDL_RendererFlip flip, int camera_x, int camera_y)
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
		dest.x = static_cast<int>(x - camera_x);
		dest.y = static_cast<int>(y - camera_y);
		dest.w = w * scale;
		dest.h = h * scale;

		// debug
		if (utility::DEBUG_MODE)
		{
			printf("Drawing at X: %d, Y: %d, W: %d, H: %d\n", dest.x, dest.y, dest.w, dest.h);
		}

		SDL_RenderCopyEx(screen, sprite, NULL, &dest, 0, NULL, flip);
	};

	void DrawBackground(SDL_Renderer *screen, SDL_Texture *background, float x, float y, float scale)
	{

		if (background == nullptr)
		{
			printf("Error: background texture is null!\n");
			return;
		}

		SDL_Rect camera_rect;
		camera_rect.x = static_cast<int>(x);
		camera_rect.y = static_cast<int>(y);
		camera_rect.w = utility::SCREEN_WIDTH;
		camera_rect.h = utility::SCREEN_HEIGHT;

		SDL_RenderCopyEx(screen, background, &camera_rect, NULL, 0, NULL, SDL_FLIP_NONE);
	};

	void DrawFrame(SDL_Renderer *screen, const position_t pos, const float scale, const SDL_RendererFlip flip, const position_t camera, animation_t animation, const float offset)
	{
		SDL_Rect dest;
		dest.x = static_cast<int>(pos.x - camera.x);
		dest.y = static_cast<int>(pos.y - camera.y - pos.z);
		dest.w = animation.size.width * scale; // hight of the sprite sheet scaled
		dest.h = animation.size.height * scale;

		SDL_Rect src;

		// what part of the sprite sheet to render
		src.x = animation.current_frame * static_cast<int>(animation.size.width + offset);
		src.y = static_cast<int>(animation.current_action) * static_cast<int>(animation.size.height);

		// how big the cutout should the rectangle be
		src.w = static_cast<int>(animation.size.width);
		src.h = static_cast<int>(animation.size.height);

		if (utility::DEBUG_MODE)
			printf("Frame: %d | SrcRect X: %d | Width: %d\n", animation.current_frame, src.x, src.w);

		SDL_RenderCopyEx(screen, animation.sprite_sheet, &src, &dest, 0, NULL, flip);
	};
}

namespace InGameManagers
{
	SDL_Texture *LoadSpriteSheet(SDL_Renderer *screen, const char *path, int *width, int *height)
	{
		SDL_Surface *temp_surface = SDL_LoadBMP(path);
		SDL_Texture *new_texture = nullptr;

		if (temp_surface == nullptr)
		{
			printf("err while loading sprite sheet : %s \n", SDL_GetError());
		}
		else
		{
			// set background to transparent from white
			Uint32 colorkey = SDL_MapRGB(temp_surface->format, 255, 255, 255);
			SDL_SetColorKey(temp_surface, SDL_TRUE, colorkey);

			// create texture from surface
			new_texture = SDL_CreateTextureFromSurface(screen, temp_surface);
		}

		if (new_texture == nullptr)
		{
			printf("err while loading sprite sheet : %s \n", SDL_GetError());
		}

		// assign values to width height of an object
		int w = 0;
		int h = 0;
		if (SDL_QueryTexture(new_texture, NULL, NULL, &w, &h))
		{
			printf("Err while querrying texture %s\n", SDL_GetError());
		}
		
		if (width != nullptr || height != nullptr)
		{
			*width = w;
			*height = h;
		}

		if(utility::DEBUG_MODE)
		{
			printf("PATH: %s | W: %d | H:%d\n", path, w, h);
		}

		SDL_FreeSurface(temp_surface);
		return new_texture;
	}
}

namespace UtilityFunctions
{
	int GetStringLength(const char *string)
	{
		char c = 'A';
		int n = 0;

		while (c != '\0')
		{
			c = string[n];
			++n;
		}

		return n - 1;
	}
}