#include "Config.h"

UInt64 Config::Ray::MaxBounce = 5;
ColourRGBA Config::Ray::ColourWhite = ColourRGBA(255.0f, 255.0f, 255.0f, 0.0f);
ColourRGBA Config::Ray::Nothing = ColourRGBA(0.0f, 0.0f, 0.0f, 255.0f);
ColourRGBA Config::Ray::SkyColour = ColourRGBA(255.0f, 125.0f, 125.0f, 255.0f);


float Config::Tolerance = 0.0001f;
Vector Config::Orgin = Vector(0.00f, 0.00f, 0.00f);
Vector Config::UP = Vector(0.0f, 0.0f, 1.0f);
float Config::MinTolerance = 0.0001f;
float Config::MinHitDistance = 0.001f;