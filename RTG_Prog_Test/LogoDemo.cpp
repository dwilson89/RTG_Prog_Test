#include "LogoDemo.h"
#include "demo_management.h"
#include "frame_renderer.h"

#include <stdlib.h>
#include <time.h>
#include <glm/glm.hpp>

FrameRenderer	*Renderer;

LogoDemo::LogoDemo(GLuint width, GLuint height) 
	: Width(width), Height(height)
{
}

LogoDemo::~LogoDemo() {
	delete Renderer;
}

void LogoDemo::Init() {

	// Load Shader
	DemoManagement::LoadShader("shaders/frame.vs", "shaders/frame.frag");

	// Configure Shader
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	DemoManagement::GetShader().Use().SetInteger("image", 0);
	DemoManagement::GetShader().SetMatrix4("projection", projection);
	
	// Set render controller
	Renderer = new FrameRenderer(DemoManagement::GetShader());
	
	// Load in frames
	DemoManagement::LoadFrame("textures/logof0.png", GL_TRUE, 0);
	DemoManagement::LoadFrame("textures/logof1.png", GL_TRUE, 1);
	DemoManagement::LoadFrame("textures/logof2.png", GL_TRUE, 2);
	DemoManagement::LoadFrame("textures/logof3.png", GL_TRUE, 3);
	DemoManagement::LoadFrame("textures/logof4.png", GL_TRUE, 4);
	DemoManagement::LoadFrame("textures/logof5.png", GL_TRUE, 5);
	DemoManagement::LoadFrame("textures/logof6.png", GL_TRUE, 6);
	DemoManagement::LoadFrame("textures/logof7.png", GL_TRUE, 7);
	
	// Seed random number generator
	srand(time(NULL));

	// Initiate position, velocity, currentFrame
	InitAnimatedLogo();
}

void LogoDemo::Update(GLfloat dt) {
	
	// If no one is "playing" move and update the frame
	if (DemoManagement::CanWeContinue()) { 
		this->move(dt);
		this->updateFrame(dt); 
	}
}

void LogoDemo::UpdateDimensions(GLuint width, GLuint height) {
	
	// Updated the dimensions
	this->Width = width;
	this->Height = height;

	// Update the projection matrix
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	DemoManagement::GetShader().SetMatrix4("projection", projection);
}

void LogoDemo::RenderLogo() {
	
	// If no one is "playing" render the frame
	if (DemoManagement::CanWeContinue()) {
		Renderer->Render(this->currentFrame, this->logoPosition.x, this->logoPosition.y);
	}
}


void LogoDemo::updateFrame(GLfloat dt) {
	this->currentFrameTime += dt; // Increment the time between frames

	// If the current time in between frames is greater that 0.125
	if (this->currentFrameTime >= SWITCH_TIME) {
		// Reset the time
		this->currentFrameTime = 0;
		// Determine the frame number (0 - 7), %8 keeps it in this range
		this->currentFrameNo = this->currentFrameNo % 8;
		// Update the frame
		this->currentFrame = DemoManagement::GetFrame(this->currentFrameNo++);
	}
}

void LogoDemo::InitAnimatedLogo() {
	
	// Set the starting frame and time
	this->currentFrameNo = 0;
	this->currentFrameTime = 0;

	// Get the size
	this->size = DemoManagement::Size;

	// Set all frames to true - only one will be false at the beginning
	this->activeBounds[WEST] = true;
	this->activeBounds[NORTH] = true;
	this->activeBounds[EAST] = true;
	this->activeBounds[SOUTH] = true;

	// Determine which side to start on - randomly selected; 0 West, 1 North, 2 East, 3 South
	switch (rand() % 4) { 
	case WEST:
		this->logoPosition.x = -this->size.x; // x is fixed
		this->logoPosition.y = (rand() % (int)(this->Height + this->size.y)) - this->size.y; // y is between -Size.y and height
		this->activeBounds[WEST] = false;
		break;
	case NORTH:
		this->logoPosition.x = (rand() % (int)(this->Width + this->size.x)) - this->size.x; // x is between -Size.x and width
		this->logoPosition.y = -size.y; // y is fixed
		this->activeBounds[NORTH] = false;
		break;
	case EAST:
		this->logoPosition.x = this->Width; // x is fixed
		this->logoPosition.y = (rand() % (int)(this->Height + this->size.y)) - this->size.y; // y is between -Size.y and height
		this->activeBounds[EAST] = false;
		break;
	case SOUTH:
		this->logoPosition.x = (rand() % (int)(this->Width + this->size.x)) - this->size.x; // x is between -Size.x and width
		this->logoPosition.y = this->Height; // y is fixed
		this->activeBounds[SOUTH] = false;
		break;
	}

	// Set the velocity
	this->velocity = glm::vec2(100.0f, 100.0f);

	// Determine the correct direction to to send it

	// When position.x > (width + Size.x)/2, x will be negative
	if (this->logoPosition.x > (this->Width + this->size.x) / 2) {
		this->velocity.x = -this->velocity.x;
	}

	// When position.y > (height + Size.y)/2, y will be negative
	if (this->logoPosition.y > (this->Height + this->size.y) / 2) {
		this->velocity.y = -this->velocity.y;
	}

	// Set the beginning frame
	this->currentFrame = DemoManagement::GetFrame(currentFrameNo);
}

void LogoDemo::move(GLfloat dt) {

	// Calculate the next position
	this->logoPosition += this->velocity * dt;

	// Window Bound checking
	// if it overlaps a current boundary, set it position against that boundary (accounting for size) and flip its velocity
	if (this->logoPosition.x <= 0.0f && this->activeBounds[WEST]) {
		this->velocity.x = -this->velocity.x;
		this->logoPosition.x = 0.0f;
	}
	else if (this->logoPosition.x + this->size.x >= this->Width && this->activeBounds[EAST]) {
		this->velocity.x = -this->velocity.x;
		this->logoPosition.x = Width - this->size.x;
	}
	else if (this->logoPosition.y <= 0.0f  && this->activeBounds[NORTH]) {
		this->velocity.y = -this->velocity.y;
		this->logoPosition.y = 0.0f;
	}
	else if (this->logoPosition.y + this->size.y >= this->Height  && this->activeBounds[SOUTH]) {
		this->velocity.y = -this->velocity.y;
		this->logoPosition.y = Height - this->size.y;
	}

	// Checks if the logo has finished moving into frame
	if (!inBounds) {

		if (!this->activeBounds[WEST] && this->logoPosition.x > 0.0f) {
			this->activeBounds[WEST] = true;
		}

		if (!this->activeBounds[NORTH] && this->logoPosition.y > 0.0) {
			this->activeBounds[NORTH] = true;
		}

		if (!this->activeBounds[EAST] && this->logoPosition.x + this->size.x < this->Width) {
			this->activeBounds[EAST] = true;
		}

		if (!this->activeBounds[SOUTH] && this->logoPosition.y + this->size.y < this->Height) {
			this->activeBounds[SOUTH] = true;
		}

		// If its fully in frame, its in bounds!!
		if (this->activeBounds[WEST] && this->activeBounds[NORTH] && this->activeBounds[EAST] && this->activeBounds[SOUTH]) {
			this->inBounds = true;

		}
	}
}