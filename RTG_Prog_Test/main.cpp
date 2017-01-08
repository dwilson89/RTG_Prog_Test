// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "LogoDemo.h"
#include "demo_management.h"

// Function Prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


const GLuint DEFAULT_SCREEN_WIDTH = 800;
const GLuint DEFAULT_SCREEN_HEIGHT = 600;

LogoDemo Demo(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);


int main(int argc, char *argv[]) {

	// Set up the glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Assume it resizable at anytime
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "LogoDemo", nullptr, nullptr);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Manages function pointers for opengl
	glewExperimental = GLU_TRUE;
	glewInit();
	glGetError();
	
	// Set glfw callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	// Give the windows a minimum size
	glfwSetWindowSizeLimits(window, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
	
	// Configure OpenGL
	glViewport(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Initialise the Logo Demo
	Demo.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Control Loop
	while (!glfwWindowShouldClose(window)) {

		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		
		// Update Game state
		Demo.Update(deltaTime);

		// Clear the buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Render
		Demo.RenderLogo();

		glfwSwapBuffers(window);

	}
	// Run Clean up
	DemoManagement::Clear();
	glfwTerminate();
	return 0;
}

/*Callback function for user input (keyboard presses), and performs actions dependings on keys pressed*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS && key == GLFW_KEY_P) {
			// Player wants to 'play'
			DemoManagement::SetRunAnimation(false);
		}
		else if (action == GLFW_PRESS && key == GLFW_KEY_R) { // To 'restart' the animation
			DemoManagement::SetRunAnimation(true);
			Demo.InitAnimatedLogo();
		}
		
	}
}

/*Callback function for window resizing, updates the glViewport and current width and height dimensions variables used*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Demo.UpdateDimensions(width,height);
}
