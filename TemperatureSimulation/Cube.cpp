#include "Cube.h"

#include <random>
#include <math.h>
#include <cmath>

#include <glm/gtx/string_cast.hpp>

int side_length;

std::vector<Cube> cubes;

void initCubes(int samples)
{
	cubes.resize(samples * samples * samples);
	side_length = samples;
	
	generateCubes();
}

void generateCubes()
{
	int z = 0;
	for (uint32_t z = 0; z < side_length; z++)
	{
		int y = 0;
		for (uint32_t y = 0; y < side_length; y++)
		{
			int x = 0;
			for (uint32_t x = 0; x < side_length; x++)
			{
				int index = (z * side_length * side_length) + (y * side_length) + x;
				cubes[index].vertices[0] = { {x, y, z }, COLOR_VECTOR_BLUE };
				cubes[index].vertices[1] = { {x + 1, y, z},  COLOR_VECTOR_BLUE };
				cubes[index].vertices[2] = { {x, y + 1, z}, COLOR_VECTOR_BLUE };
				cubes[index].vertices[3] = { {x + 1, y + 1, z}, COLOR_VECTOR_BLUE };
				cubes[index].vertices[4] = { {x, y, z + 1}, COLOR_VECTOR_BLUE };
				cubes[index].vertices[5] = { {x + 1, y, z + 1}, COLOR_VECTOR_BLUE };
				cubes[index].vertices[6] = { {x, y + 1, z + 1}, COLOR_VECTOR_BLUE };
				cubes[index].vertices[7] = { {x + 1, y + 1, z + 1}, COLOR_VECTOR_BLUE };

				//There's gotta be a better way to do this

				//Cube - 6 Faces, 2 Tris per face, 3 indices per Tri = (6 * 2) * 3 = 36 indices
				cubes[index].indices[0] = 0;
				cubes[index].indices[1] = 1;
				cubes[index].indices[2] = 2;
				//F0
				cubes[index].indices[3] = 3;
				cubes[index].indices[4] = 2;
				cubes[index].indices[5] = 1;

				cubes[index].indices[6] = 0;
				cubes[index].indices[7] = 1;
				cubes[index].indices[8] = 4;
				//F1
				cubes[index].indices[9] = 1;
				cubes[index].indices[10] = 4;
				cubes[index].indices[11] = 5;

				cubes[index].indices[12] = 4;
				cubes[index].indices[13] = 5;
				cubes[index].indices[14] = 6;
				//F2
				cubes[index].indices[15] = 5;
				cubes[index].indices[16] = 6;
				cubes[index].indices[17] = 7;

				cubes[index].indices[18] = 0;
				cubes[index].indices[19] = 2;
				cubes[index].indices[20] = 6;
				//F3
				cubes[index].indices[21] = 0;
				cubes[index].indices[22] = 4;
				cubes[index].indices[23] = 6;

				cubes[index].indices[24] = 7;
				cubes[index].indices[25] = 3;
				cubes[index].indices[26] = 1;
				//F4
				cubes[index].indices[27] = 7;
				cubes[index].indices[28] = 5;
				cubes[index].indices[29] = 1;

				cubes[index].indices[30] = 2;
				cubes[index].indices[31] = 3;
				cubes[index].indices[32] = 6;
				//F5
				cubes[index].indices[33] = 7;
				cubes[index].indices[34] = 6;
				cubes[index].indices[35] = 3;

			}
		}
	}

	/*
	for (int i = 0; i < heatspots; i++)
	{
		spots[i].center = {};
		spots[i].center.x = center_selector(gen);
		spots[i].center.y = center_selector(gen);
		spots[i].center.z = center_selector(gen);
		spots[i].radius = radius_selector(gen);
	}

	int count = 0;
	for (uint32_t z = 0; z < samples; z++)
	{
		for (uint32_t y = 0; y < samples; y++)
		{
			for (uint32_t x = 0; x < samples; x++)
			{
				int index = (z * samples * samples) + (y * samples) + x;
				cubes[index].temperature = 0;
				cubes[index].vertices[0] = { x, y, z };
				cubes[index].vertices[1] = { x + 1, y, z };
				cubes[index].vertices[2] = { x, y + 1, z };
				cubes[index].vertices[3] = { x + 1, y + 1, z };
				cubes[index].vertices[4] = { x, y, z + 1 };
				cubes[index].vertices[5] = { x + 1, y, z + 1 };
				cubes[index].vertices[6] = { x, y + 1, z + 1 };
				cubes[index].vertices[7] = { x + 1, y + 1, z + 1 };

				for (int i = 0; i < heatspots; i++)
				{
					int d = (int)std::sqrt(std::pow(spots[i].center.x - x, 2) + std::pow(spots[i].center.y - y, 2) + std::pow(spots[i].center.z - z, 2));
					if (d < spots[i].radius)
					{
						cubes[index].temperature = 100;
					}
				}
			}
		}

	}
		*/
}


void placeHotSpots()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> spot_selector(1.0, 5.0);

	int heatspots = spot_selector(gen);

	std::uniform_real_distribution<double> center_selector(0.0, (double)side_length);
	std::uniform_real_distribution<double> radius_selector(1, side_length / 2);

	std::vector<Heatspot> spots(heatspots);
}

void updateTemperatures()
{
}

void copyToDisplayBuffer(std::vector<Vertex> &vertices, std::vector<uint16_t> &indices)
{
	int offset = 0;
	for (Cube& cube : cubes)
	{
		for (int i = 0; i < cube.vertices.size(); i++)
		{
			vertices.push_back(cube.vertices[i]);
		}

		for (int i = 0; i < cube.indices.size(); i++)
		{
			indices.push_back(cube.indices[i] + offset);
		}

		offset += 8;
	}
}


//DEBUG ONLY, recommended to use for small sample sizes only
void printCubes()
{
	for (uint32_t z = 0; z < side_length; z++)
	{
		for (uint32_t y = 0; y < side_length; y++)
		{
			for (uint32_t x = 0; x < side_length; x++)
			{
				int index = (z * side_length * side_length) + (y * side_length) + x;
				std::cout << "CUBE# " << index << std::endl;
				std::cout << "X: " << cubes[index].vertices[0].pos.x << " Y: " << cubes[index].vertices[0].pos.y << " Z: " << cubes[index].vertices[0].pos.z << std::endl;
				std::cout << "R: " << cubes[index].vertices[0].color.x << " G: " << cubes[index].vertices[0].color.y<< " B: " << cubes[index].vertices[0].color.z<< std::endl;
			}
		}
	}
}