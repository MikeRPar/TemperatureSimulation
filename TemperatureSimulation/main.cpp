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
#include "GraphicsEngine.h"
#include "Cube.h"

int main()
{
	


	GraphicsEngine graphicsEngine("Temperature Simulation");
	initCubes(2);
	std::vector<Vertex> m_vertices;
	std::vector<uint16_t> m_indices;
	copyToDisplayBuffer(m_vertices, m_indices);

	for (auto whatever : m_vertices)
	{
		//std::cout
	}
	/*
	try {
		graphicsEngine.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	*/

	//printCubes();

	return EXIT_SUCCESS;
}