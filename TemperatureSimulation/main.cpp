/********************************************************************
* Project: Temperature Simulation Driver Source
* Author: Michael Richard Parlacoski
* Description:
* 
* Libraries used:
* Vulkan:
* GLFW:
* GLM:
* 
* Licensing:
* 
*********************************************************************/

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <glm/glm.hpp>

#include "GraphicsEngine.h"
#include "Cube.h"

int main()
{
	int samples = 10;

	GraphicsEngine graphicsEngine("Temperature Simulation");
	initCubes(samples);
	std::vector<Vertex> m_vertices;
	std::vector<uint16_t> m_indices;
	copyToDisplayBuffer(m_vertices, m_indices);
	graphicsEngine.fillArrays(m_vertices, m_indices);

	//Change camera start based on sample amount
	graphicsEngine.setCameraStartPosition(glm::vec3(samples * 2.0f, samples * 2.0f, samples * 2.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	graphicsEngine.setPerspective(45.0f, 0.1f, samples * samples * 10.0f);
	
	try {
		graphicsEngine.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	

	//printCubes();

	return EXIT_SUCCESS;
}