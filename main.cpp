#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Player.h"
#include "Block.h"
#include "TextureAtlas.h"
#include "World.h"

int main() {
	// init GLFW
	glfwInit();

	// window settings:
	int width = 1600; //1600;
	int height = 900; // 900;
	int refreshRate = 144;
	const char* windowName = "OpenGL Template";

	// tell glfw what version of opengl is being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// tell glfw to not allow window resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// create a window object
	GLFWwindow* mainWindow = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (mainWindow == NULL) { // error check for window
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// set to fullscreen
	bool fullscreen = false;
	GLFWmonitor* windowMonitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
	if (fullscreen) {
		int widthMM, heightMM;
		float xScale, yScale;
		glfwGetMonitorPhysicalSize(windowMonitor, &widthMM, &heightMM);
		glfwGetMonitorContentScale(windowMonitor, &xScale, &yScale);
		const GLFWvidmode* mode = glfwGetVideoMode(windowMonitor);
		width = mode->width;
		height = mode->height;
		refreshRate = mode->refreshRate;
		glfwSetWindowMonitor(mainWindow, windowMonitor, 0, 0, width, height, refreshRate);
	}

	// add window to current GLFW context
	glfwMakeContextCurrent(mainWindow);

	// load glad and specify viewport (goes from (x, y) = (0, 0) to (x, y) = (width, height)
	gladLoadGL();
	glViewport(0, 0, width, height);

	// clear buffer colour and use another one
	glClearColor(0.85f, 0.85f, 0.90f, 1.0f); // specify the colour (gray) of the background
	glClear(GL_COLOR_BUFFER_BIT); // clean the back buffer and assign the new colour
	glfwSwapBuffers(mainWindow); // swap the back buffer with the front buffer to display the colour

	// load shaders
	Shader defaultBlockShaderProgram("defaultBlocks.vert", "defaultBlocks.frag");

	// load textureatlas
	TextureAtlas atlas;

	Block drawingBlock(glm::vec3(0.0f, 0.0f, 0.0f), 0, atlas);

	// allows openGL to account for depth in 3d textures
	glEnable(GL_DEPTH_TEST);
	// GL_LESS: passes if the incoming depth value is equal to the stored depth value
	glDepthFunc(GL_LESS); // for fog and visualizing depth

	// face culling: when inside an object, we won't see its insides. IMPROVES FPS
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT); // almost always want front face
	glFrontFace(GL_CCW); // usually order of triangle indices is ccw, but note that gltf uses cw

	// create a player object
	Player player(glm::vec3(0.0f, 9.0f, 0.0f), width, height);

	// create world
	World dimension0(WorldType::SUPERFLAT);
	dimension0.addPlayer(player);


	// fps counter/performance measurements
	double prevTime = 0.0;
	double currentTime = 0.0;
	double timeDiff;
	unsigned int framesCounter = 0; // counts number of frames

	// input period
	double prevTimeIn = 0.0;
	double currentTimeIn = 0.0;
	double timeDiffIn;

	// while window should remain open:
	while (!glfwWindowShouldClose(mainWindow)) {
		currentTime = glfwGetTime();
		currentTimeIn = currentTime;

		timeDiff = currentTime - prevTime;
		timeDiffIn = currentTimeIn - prevTimeIn;

		framesCounter++;
		if (timeDiff >= 1.0 / 30.0) {
			std::string FPS = std::to_string((1.0 / timeDiff) * framesCounter);
			std::string MS = std::to_string((timeDiff / framesCounter) * 1000);
			std::string newTitle = "BlockGame: " + FPS + "FPS / " + MS + "ms";
			glfwSetWindowTitle(mainWindow, newTitle.c_str());
			prevTime = currentTime;
			framesCounter = 0;
		}


		// specify the colour (gray) of the background
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		// clean the back buffer and assign the new colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// camera
		// handle inputs: since we don't want inputs to vary by fps, we should take them at a set period
		if (timeDiffIn >= 1.0 / 1000.0) {
			player.input(mainWindow);
			prevTimeIn = currentTimeIn;
		}
		// update camera matrix in player
		player.updateCamMatrix(45.0f, 0.1f, 256.0f);

		// draw blocks
		// reset drawingblock
		drawingBlock.update(glm::vec3(0.0f, 0.0f, 0.0f), 0, atlas);

		dimension0.playerTick();

		/*
		drawingBlock.draw(defaultBlockShaderProgram, player.camera);
		drawingBlock.update(glm::vec3(0.0f, 0.0f, 1.0f), 0, atlas);
		drawingBlock.draw(defaultBlockShaderProgram, player.camera);
		drawingBlock.update(glm::vec3(1.0f, 0.0f, 0.0f), 0, atlas);
		drawingBlock.draw(defaultBlockShaderProgram, player.camera);
		drawingBlock.update(glm::vec3(1.0f, 0.0f, 1.0f), 0, atlas);
		drawingBlock.draw(defaultBlockShaderProgram, player.camera);
		drawingBlock.update(glm::vec3(2.0f, 0.0f, 2.0f), 0, atlas);
		drawingBlock.draw(defaultBlockShaderProgram, player.camera);
		drawingBlock.update(glm::vec3(-1.0f, -1.0f, -1.0f), 0, atlas);
		drawingBlock.draw(defaultBlockShaderProgram, player.camera);
		*/
		
		dimension0.draw(defaultBlockShaderProgram, player.camera, atlas, drawingBlock);

		bool shouldDebug = true;
		
		if (player.isDebug() || shouldDebug) {
			int playerChunkX = std::floor((float)player.position.x / 16.0f);
			int playerChunkZ = std::floor((float)player.position.z / 16.0f);

			std::cout << "\r                                                           "
				<< "\rposition: "
				<< player.position.x << ", "
				<< player.position.y << ", "
				<< player.position.z << " chunk: ("
				<< playerChunkX << ", " << playerChunkZ << ")";
		}
		

		// updates the frame by swaping back buffer with the front buffer
		glfwSwapBuffers(mainWindow);
		// handle all GLFW events
		glfwPollEvents();
	}

	// terminate GLFW
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}