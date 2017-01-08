/*Class LogoDemo, hosts the functionality that controls the animation and movement of the Logo
displayed in the window*/

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "texture2d.h"
#include "frame_renderer.h"

// Constants
const int MAX_FRAME_COUNT = 8;
const int WEST = 0;
const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const GLfloat SWITCH_TIME(0.125f);// 8 frames per second

class LogoDemo
{
public:

	GLuint Width, Height;

	// Constructor
	// Param: width, width of the window
	// Param: height, height of the window
	LogoDemo(GLuint width, GLuint height);
	
	// Destructor
	~LogoDemo();

	// Function that initialises the demo, buy loading in shaders, textures and setting intial variables.
	void Init();

	// Function when called updates the demo's position and frame.
	// Param: dt, deltatime used for calculating movement and frame change
	void Update(GLfloat dt);
	
	// Function that calls the renderer to render the currentframe in the calculated position.
	void RenderLogo();

	// Function that when called updates the stored dimensions, and updates the projection matrix used by the shader.
	// Param: width, width of the window
	// Param: height, height of the window
	void UpdateDimensions(GLuint width, GLuint height);
	
	// Function that when called initiates the animated logo, including but not limited to its position (randomly determined), 
	// state, velocity and the starting frame. 
	void InitAnimatedLogo();

private:
	
	// Private vars
	GLfloat currentFrameTime; // Current time passed since the last frame
	bool inBounds; // Variable to indicate when to use the window bounds for movement 
	bool activeBounds[4]; // Boundaries active
	int currentFrameNo; // Current frame number 0-7 (8 frame animation)
	Texture2D currentFrame; // Current frame (texture)
	
	glm::vec2 logoPosition;
	glm::vec2 size;
	glm::vec2 velocity;
	
	// Function that updates the animation frame, by determining if enough time has passed.
	// Param: dt, deltatime used for determined frame change 
	void updateFrame(GLfloat dt);

	// Function that calculates the position of the animated logo
	// Param: dt, deltatime used for calculating movement 
	void move(GLfloat dt);
};

#endif
