#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include "Vector.h"
#include "Vertex.h"
#include "Material.h"
#include <math.h>
#include "Ray.h"
#include "Config.h"
#include <random>
#include <limits>
#include <vector>

class Helpers
{
public:

	struct SurfaceFunc
	{
		
		static Vector CalculateSurfaceNormal(const std::vector<Vertex> &v)
		{
			Vector rtn = Vector();
			for (int i = 0; i < v.size(); i++) {

				Vector current = v[i].m_pos;
				Vector next = v[(i + 1) % v.size()].m_pos;

				rtn.m_x = rtn.m_x + ((current.m_y - next.m_y) * (current.m_z + next.m_z));
				rtn.m_y = rtn.m_y + ((current.m_z - next.m_z) * (current.m_x + next.m_x));
				rtn.m_z = rtn.m_z + ((current.m_x - next.m_x) * (current.m_y + next.m_y));
			}
			rtn = rtn.Normalize();
			return rtn;
		}

		static double Vec2Distance(Vector v1, Vector v2) {
			return sqrt(((v1.m_x - v2.m_x) * (v1.m_x - v2.m_x))
				+ ((v1.m_y - v2.m_y) * (v1.m_y - v2.m_y)));
		}

		static double Vec3Distance(Vector v1, Vector v2) {
			return sqrt(((v1.m_x - v2.m_x) * (v1.m_x - v2.m_x))
				+ ((v1.m_y - v2.m_y) * (v1.m_y - v2.m_y))
				+ ((v1.m_z - v2.m_z) * (v1.m_z - v2.m_z)));
		}

		static Vector Reflect(Vector dir, Vector normal) {
			Vector bounce = dir - 2.0f * (dir.DotProduct(normal) * normal);
			return bounce;
		}

		static Ray Reflect(Material mat, Vector nextOrgin, Vector dir, Vector nextNormal) {

			Vector pureBounce = Reflect(dir, nextNormal);
			//this is a shit way todo this.
			//TODO this is a shit way todo this. so make it better
			if (mat.reflect < 1.0f)
			{
				Vector rv = Vector(Rand::RandomBilateral(),
					Rand::RandomBilateral(),
					Rand::RandomBilateral()
				);
				Vector RandomBounce = (nextNormal + rv).Normalize();
				nextNormal = RandomBounce.Lerp(pureBounce, mat.reflect).Normalize();
			}
			else
			{
				nextNormal = pureBounce;
			}
			return Ray(nextOrgin, nextNormal);
		}

	};

	struct Rand
	{
		static float RandomBilateral() {
			//TODO make this better
			int rnd = rand() % 101;
			return (float)((float)(rnd) / 101.0f);
		}
	};

	static void MaxChunks(int * w, int *h) {
		*w = Config::ImageWidth / Config::ChunkWidth; //This might be wrong.
		*h = Config::ImageHeight / Config::ChunkWidth;
	}

	static void MaxChunks(const int &cw, const int &ch,int * w, int *h) {
		*w = Config::ImageWidth / cw; //This might be wrong.
		*h = Config::ImageHeight / ch;
	}

	static void GetChunkXY(const int &chunkID, int * x, int *y) {

		int chunkW;
		int chunkH;

		MaxChunks(&chunkW, &chunkH);

		int chunkX = chunkID % chunkW;
		int chunkY = (int)floor(chunkID / chunkH);
		*x = Config::ChunkWidth * chunkX;
		*y = Config::ChunkHeight * chunkY;
	}

	static void GetChunkArea(const int &chunkID, int * x, int *y, int * w, int * h) {

		int chunkW;
		int chunkH;

		MaxChunks(&chunkW, &chunkH);

		int chunkX = chunkID % chunkW;
		int chunkY = (int)floor(chunkID / chunkH);
		*x = Config::ChunkWidth * chunkX;
		*y = Config::ChunkHeight * chunkY;
		*w = *x + Config::ChunkWidth;
		*h = *y + Config::ChunkHeight;
	}

	static void GetChunkArea(const int &chunkID, const int &cw, const int &ch, int * x, int *y, int * w, int * h) {

		int chunkW;
		int chunkH;

		MaxChunks(cw, ch, &chunkW, &chunkH);

		int chunkX = chunkID % chunkW;
		int chunkY = (int)floor(chunkID / chunkH);
		*x = cw * chunkX;
		*y = ch * chunkY;
		*w = *x + cw;
		*h = *y + ch;
	}

	static int MaxChunks(const int &w, const int &h, const int &cw, const int &ch) {
		int maxChunksX = w / cw; //This might be wrong.
		int maxChunksY = h / ch;
		return maxChunksX * maxChunksY;
	}

};

#endif // !HELPERS_H_INCLUDED