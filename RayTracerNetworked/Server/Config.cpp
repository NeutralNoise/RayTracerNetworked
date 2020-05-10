#include "Config.h"

UInt64 Config::Ray::RaysPerPixel = 16;
UInt64 Config::Ray::MaxBounce = 5;
ColourRGBA Config::Ray::ColourWhite = ColourRGBA(255.0f, 255.0f, 255.0f, 0.0f);
ColourRGBA Config::Ray::Nothing = ColourRGBA(0.0f, 0.0f, 0.0f, 255.0f);
ColourRGBA Config::Ray::SkyColour = ColourRGBA(255.0f, 125.0f, 125.0f, 255.0f);

//Different window sizes.

//int Config::Width = 3840;
//int Config::Height = 2160;
//int Config::Width = 1280;
//int Config::Height = 720;
int Config::Width = 800;
int Config::Height = 800;
//int Config::Width = 300;
//int Config::Height = 300;
//int Config::Width = 10;
//int Config::Height = 10;

//int Config::ImageWidth = 3840;
//int Config::ImageHeight = 2160;
//int Config::ImageWidth = 1920;
//int Config::ImageHeight = 1080;
//int Config::ImageWidth = 1280;
//int Config::ImageHeight = 720;
int Config::ImageWidth = 800;
int Config::ImageHeight = 800;
//int Config::ImageWidth = 50;
//int Config::ImageHeight = 50;
//int Config::ImageWidth = 10;
//int Config::ImageHeight = 10;

int Config::ChunkWidth = 10;
int Config::ChunkHeight = 10;

float Config::Tolerance = 0.0001f;
Vector Config::Orgin = Vector(0.00f, 0.00f, 0.00f);
Vector Config::UP = Vector(0.0f, 0.0f, 1.0f);
float Config::MinTolerance = 0.0001f;
float Config::MinHitDistance = 0.001f;

int Config::MaxThreadCount = 6;