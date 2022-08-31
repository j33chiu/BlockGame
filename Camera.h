#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera {
public:
	// position of camera
	glm::vec3 position;
	// orientation/direction of the camera (starts looking in the NEGATIVE z direction)
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	// which way is "up"
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// width and height of window
	int width;
	int height;

	// constructor
	Camera();
	Camera(int width, int height, glm::vec3 position);

	void updateMatrix(float fovDeg, float nearPlane, float farPlane);
	void exportMatrix(Shader& shader, const char* uniform);

};

#endif
