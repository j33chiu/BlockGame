#include"VAO.h"

VAO::VAO() {
	// generate VAO with 1 object
	glGenVertexArrays(1, &ID);
}

VAO::VAO(int numObjects) {
	// generate VAO with n object
	glGenVertexArrays(numObjects, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	// layout: index of attribute (x, y, z) -> 0, (r, g, b) -> 1
	// numComponents: corresponds to number of elements in the attribute (x, y, z) -> 3, or (r, g, b) -> also 3
	// type: corresponds to the datatype in the vertices array (x, y, z), (r, g, b) -> float
	// stride: corresponds to the distance in bytes between each vertex (n * sizeof(GL_FLOAT))
	// offset: corresponds to the distance offset in bytes from 0. (x, y, z) -> 0, (r, g, b) -> (3 * sizeof(GL_FLOAT))



	VBO.Bind();
	// configure the vertex attribute so that openGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// enable the vertex attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind() {
	// make VAO the current vertex array object
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}