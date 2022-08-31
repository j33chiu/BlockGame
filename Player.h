#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "Camera.h"

class Player {
public:
	Camera camera;

	std::string name = "testName";
	bool debugging = false;
	int clientW, clientH;
	glm::vec3 position;
	int chunkLoadDist = 4; // "radius" in chunks to load for the player

	bool escPressed = false;
	bool fpsMode = true;

	// sens when looking around
	float sensitivity = 100.0f;
	// move speed (when changing position)
	float speed = 0.06f;
	// orientation/direction of the camera (starts looking in the NEGATIVE z direction)
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	// which way is "up"
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	// stop player camera from jumping on the first click
	bool firstClick = true;

	Player(glm::vec3 position, int clientW, int clientH);

	void updateCamMatrix(float fovDeg, float nearPlane, float farPlane);
	void input(GLFWwindow* window);
	bool isDebug();

};

#endif