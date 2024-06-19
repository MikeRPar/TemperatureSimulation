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

std::vector<Cube> cubes;

struct Cube {
	uint32_t cube_index;
	uint32_t color;
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};

void initCubes(int samples);

void generateCubes(int samples);

void placeHotSpots();

void updateTemperatures();

void copyToDisplayBuffer();

#endif

