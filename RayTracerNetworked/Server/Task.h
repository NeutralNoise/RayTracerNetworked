#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED
#include "TypeDef.h"
#include "ColourRGBA.h"
#include "Config.h"

struct Task {
	Task() { };

	Task(const int &chunk) {
		this->chunk = chunk;
		chunk_width = Config::ChunkWidth;
		chunk_height = Config::ChunkHeight;
	}

	Task(const int &chunk, const int &width, const int &height) {
		this->chunk = chunk;
		chunk_width = width;
		chunk_height = height;
	}
	int chunk; //!< The chunk to be rendered.
	int chunk_width; //!< The width of the chunk.
	int chunk_height; //!< The height of the chunk.
};

struct CompletedTask {
	CompletedTask() {};
	CompletedTask(const int &x, const int &y, const ColourRGBA &colour) {
		this->x = x;
		this->y = y;
		this->colour = colour;
	};

	int x; //!< The global x position of the pixel.
	int y; //!< The global y position of the pixel.
	ColourRGBA colour; //!< The colour of the pixel.
};

#endif // !TASK_H_INCLUDED
