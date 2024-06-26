#ifndef CUBE_H
#define CUBE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include <vector>
#include <iostream>
#include <optional>
#include <set>
#include <cstdint>

//This is bad since GraphicsEngine will use the Cube class but
//GraphicsEngine holds the defintion for the Vertex we need as well as the
//array we intend to fill, so for now this is fine, will restructure in future 
#include "GraphicsEngine.h"

#define COLOR_VECTOR_BLUE {0, 0 , 255}
#define COLOR_VECTOR_TEAL {0, 255, 191}
#define COLOR_VECTOR_WHITE {255, 255, 255}
#define COLOR_VECTOR_YELLOW {255, 246, 120}
#define COLOR_VECTOR_RED {255, 0, 0}


struct Cube {
	uint32_t temperature;
	uint32_t radius;
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	Cube() : vertices(8), indices(36) {}

	void updateColor(glm::vec3 color)
	{
		for (auto vertex : vertices)
		{
			vertex.color = color;
		}
	}
};

typedef struct Heatspot {
	int radius;
	Vertex center;
} Heatspot;

void initCubes(int samples);

void generateCubes();

void placeHotSpots();

void updateTemperatures();

void copyToDisplayBuffer(std::vector<Vertex> &vertices, std::vector<uint16_t> &indices);

void printCubes();

#endif

