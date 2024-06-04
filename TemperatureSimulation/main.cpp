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

int main()
{
	GraphicsEngine graphicsEngine("Temperature Simulation");

	try {
		graphicsEngine.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}