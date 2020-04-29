#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include <SDL2/SDL.h>
#include "TypeDef.h"

class Renderer
{
public:
	Renderer();
	int InitRenderer(const int &w, const int &h);
	void SetPixel(const int &x, const int &y, const UInt8 &r, const Uint8 &g, const UInt8 &b);
	void SetPixelArea(const int &x, const int &y, const UInt8 &r, const Uint8 &g, const UInt8 &b);
	void SetPixelWithLock(const int &x, const int &y, const UInt8 &r, const Uint8 &g, const UInt8 &b);
	void SetPixelAreaWithLock(const int &x, const int &y, const UInt8 &r, const Uint8 &g, const UInt8 &b); //WARNING this doesn't work
	void LockTexture();
	void LockTextureArea(const int chunkID);
	void UnlockTexture();
	void Draw();
	void Clean();
private:
	int m_winWidth;
	int m_winHeight;
	SDL_Window * p_window; //!< The main display window.
	SDL_Renderer * p_renderer; //!< Used to render the texture too.
	SDL_Texture * p_texture; //!< The texture used to display the image to the the screen.
	void * p_pixels;
	int m_pitch;
	int m_chunkSize;
	int m_maxChunksX;
	int m_maxChunksY;
	int m_totalChunks;
	int m_currentLockChunk;
};

#endif // !RENDERER_H_INCLUDED