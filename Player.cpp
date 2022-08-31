#include "Player.h"

Player::Player(glm::vec3 position, int clientW, int clientH) {
	Player::position = position;
	camera.width = clientW;
	camera.height = clientH;
	camera.position = position;
	Player::clientW = clientW;
	Player::clientH = clientH;
}

void Player::updateCamMatrix(float fovDeg, float nearPlane, float farPlane) {
	camera.updateMatrix(fovDeg, nearPlane, farPlane);
}

void Player::input(GLFWwindow* window) {
	// keyboard inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// matrix multiplication to get direction (think crossing 2 vectors)
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.24f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.06f;
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		// debug mode
		debugging = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe on
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_RELEASE) {
		// debug mode off
		debugging = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // wireframe off
	}

	// mouse inputs
	if (fpsMode) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, clientW / 2, clientH / 2);
			firstClick = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (clientH / 2)) / clientH;
		float rotY = sensitivity * (float)(mouseX - (clientW / 2)) / clientW;

		// cross (and normalize) gives x axis, rotX is angle to rotate about x axis
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		// limit up and down vision
		if (!((glm::angle(newOrientation, up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -up) <= glm::radians(5.0f)))) {
			orientation = newOrientation;
		}

		// no limit to left and right vision
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		glfwSetCursorPos(window, (clientW / 2), (clientH / 2));
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

	// toggle mouseInputs
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		// fps mode toggle
		escPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_RELEASE) {
		if (escPressed) {
			fpsMode = !fpsMode;
			escPressed = false;
		}
	}
	camera.position = position;
	camera.orientation = orientation;
}

bool Player::isDebug() {
	return debugging;
}