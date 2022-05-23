#pragma once

#include <glm.hpp>

/**
 * Structure that groups together all the properties that define a single vertex
 *     (i.e. its position, color, texture coordinates, and normal).
 */
struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};
