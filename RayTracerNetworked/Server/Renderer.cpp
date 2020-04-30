#include "Renderer.h"
#include <iostream>
#include <string>
#include <math.h> //floor

Renderer::Renderer()
{
	p_window = NULL; //use null here cause thats what SDL2 does.
	m_winWidth = 0;
	m_winHeight = 0;
	m_chunkSize = 50;
}

int Renderer::InitRenderer(const int &w, const int &h)
{
	m_winWidth = w;
	m_winHeight = h;
	m_maxChunksX = w / m_chunkSize; //This might be wrong.
	m_maxChunksY = h / m_chunkSize;
	m_totalChunks = m_maxChunksX * m_maxChunksY;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL2 Error\n";
		std::cout << SDL_GetError() << "\n";
	}
	else {
		std::cout << "SDL2 OK\n";
	}


	SDL_version sdlVersion;
	SDL_GetVersion(&sdlVersion);
	std::cout << "SDL Version:" + std::to_string(sdlVersion.major) + "." << std::to_string(sdlVersion.minor) + "." << std::to_string(sdlVersion.patch) + "\n";

	//Create the SDL2 Window.
	p_window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (p_window == NULL) {
		std::cout << "Failed to create SDL2 window.\n";
		std::cout << SDL_GetError() << "\n";
	}
	else {
		std::cout << "Created SDL2 Window.\n";
	}

	//Create a renderer for textures to be renderered too.
	p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
	p_texture = SDL_CreateTexture(p_renderer, SDL_GetWindowPixelFormat(p_window), SDL_TextureAccess::SDL_TEXTUREACCESS_STREAMING, w, h);

	return 0;
}

void Renderer::SetPixel(const int & x, const int & y, const UInt8 & r, const Uint8 & g, const UInt8 & b)
{
	unsigned int format = SDL_GetWindowPixelFormat(p_window);
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);
	unsigned int colour = SDL_MapRGB(mappingFormat, r, g, b);
	((unsigned int*)p_pixels)[m_winWidth * y + x] = colour;
	SDL_FreeFormat(mappingFormat);
}

void Renderer::SetPixelArea(const int & x, const int & y, const UInt8 & r, const Uint8 & g, const UInt8 & b)
{
	//TODO Fix this.it stops at y 400
	int pixCount = m_pitch / 4 * 50;
	int cx = m_currentLockChunk % m_maxChunksX;
	int cy = (int)floor(m_currentLockChunk / m_maxChunksY);
	unsigned int format = SDL_GetWindowPixelFormat(p_window);
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);
	unsigned int colour = SDL_MapRGB(mappingFormat, r, g, b);
	int ny = y * cy;
	((unsigned int*)p_pixels)[m_chunkSize * (y - ny) + (x-((m_chunkSize * cx)))] = colour;
	SDL_FreeFormat(mappingFormat);

}

void Renderer::SetPixelWithLock(const int &x, const int &y, const UInt8 &r, const Uint8 &g, const UInt8 &b)
{
	//Doing this will be slow as shit.
	void *pixels;
	int pitch;
	SDL_LockTexture(p_texture, NULL, &pixels, &pitch);
	UInt8 gColour = g;
	if ((x % m_chunkSize) == 0 || (y % m_chunkSize) == 0)
		gColour = 128;
	//SDL_LockTexture(p_texture, &rect, &pixels, &pitch);
	int pixCount = pitch / 4 * m_winHeight;
	unsigned int format = SDL_GetWindowPixelFormat(p_window);
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);
	unsigned int colour = SDL_MapRGB(mappingFormat, r, gColour, b);
	((unsigned int*)pixels)[m_winWidth * y + x] = colour;
	SDL_FreeFormat(mappingFormat);
	SDL_UnlockTexture(p_texture);
}

void Renderer::SetPixelAreaWithLock(const int & x, const int & y, const UInt8 & r, const Uint8 & g, const UInt8 & b)
{
	//TODO Fix this. it stops at y 400
	//These widths should not be hard coded.
	//TODO remove this hard coded size
	const int maxChunks = 800 / m_chunkSize;
	SDL_Rect chunkArea;
	chunkArea.x = (int)floor(x / m_chunkSize);
	chunkArea.y = (int)floor(y / m_chunkSize);
	//int chunkID = chunkArea.x + chunkArea.y * maxChunks;
	int chunkID = chunkArea.x + chunkArea.y * m_maxChunksX;

	SDL_Rect area;
	int chunkX = chunkID % m_maxChunksX;
	int chunkY = (int)floor(chunkID / m_maxChunksY);
	area.x = m_chunkSize * chunkX;
	area.y = m_chunkSize * chunkY;
	area.w = area.x + m_chunkSize;
	area.h = area.y + m_chunkSize;

	UInt8 gColour = g;
	if ((x % m_chunkSize) == 0 || (y % m_chunkSize) == 0)
		gColour = 128;
	void *pixels;
	int pitch;

	SDL_LockTexture(p_texture, &area, &pixels, &pitch);
	int pixCount = pitch / 4 * m_chunkSize;
	unsigned int format = SDL_GetWindowPixelFormat(p_window);
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);
	unsigned int colour = SDL_MapRGB(mappingFormat, r, gColour, b);
	((unsigned int*)pixels)[m_winWidth* (y - area.y) + (x - area.x)] = colour;
	SDL_FreeFormat(mappingFormat);
	SDL_UnlockTexture(p_texture);
}

void Renderer::LockTexture()
{
	SDL_LockTexture(p_texture, NULL, &p_pixels, &m_pitch);
}

void Renderer::LockTextureArea(const int chunkID)
{
	m_currentLockChunk = chunkID;
	SDL_Rect area;
	int chunkX = chunkID % m_maxChunksX;
	int chunkY = (int)floor(chunkID / m_maxChunksY);
	area.x = m_chunkSize * chunkX;
	area.y = m_chunkSize * chunkY;
	area.w = area.x + m_chunkSize;
	area.h = area.y + m_chunkSize;
	SDL_LockTexture(p_texture, &area, &p_pixels, &m_pitch);
}

void Renderer::UnlockTexture()
{
	SDL_UnlockTexture(p_texture);
	p_pixels = nullptr;
}

void Renderer::Draw()
{
	SDL_RenderClear(p_renderer);
	SDL_RenderCopy(p_renderer, p_texture, NULL, NULL);
	SDL_RenderPresent(p_renderer);
}

void Renderer::Clean()
{
	SDL_DestroyTexture(p_texture);
	SDL_DestroyRenderer(p_renderer);
	SDL_DestroyWindow(p_window);
}
