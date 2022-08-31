#ifndef VERTEX_STRUCT_H
#define VERTEX_STRUCT_H

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec3 colour;
	glm::vec2 texCoord;
};

struct SimpleVertex {
	glm::vec3 position;
	glm::vec2 texCoord;
};

#endif
