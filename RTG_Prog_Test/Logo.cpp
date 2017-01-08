#include "Logo.h"


Logo::Logo() : LogoPosition(0, 0), CurrentFrame(), Size(200, 200){
}

Logo::Logo(glm::vec2 position, Texture2D frame, glm::vec2 size) : LogoPosition(position), CurrentFrame(frame), Size(size) {
}

void Logo::Draw(FrameRenderer &renderer) {
	renderer.Render(this->CurrentFrame, this->LogoPosition.x, this->LogoPosition.y);
}

void Logo::init(glm::vec2 pos, glm::vec2 vel, glm::vec2 size, Texture2D frame, const bool(&bound)[4]) {
	
	inBounds = false;
	this->CurrentFrame = frame;
	this->LogoPosition = pos;
	this->Velocity = vel;
	this->Size = size;

	// Set activeBounds to false
	for (int i = 0; i < 4; i++) {
		activeBounds[i] = bound[i];
	}
	
	//function to initialise the starting position and current frame and velocity
	
}

glm::vec2 Logo::Move(GLfloat dt, GLuint window_width, GLuint window_height) {

	// Will need some code for init movement to get into the frame

	this->LogoPosition += this->Velocity * dt;

	// Window Bound checking

	if (this->LogoPosition.x <= 0.0f && activeBounds[0]) {
		this->Velocity.x = -this->Velocity.x;
		this->LogoPosition.x = 0.0f;

	}
	else if (this->LogoPosition.x + this->Size.x >= window_width && activeBounds[2]) {
		this->Velocity.x = -this->Velocity.x;
		this->LogoPosition.x = window_width - this->Size.x;
	}
	else if (this->LogoPosition.y <= 0.0f  && activeBounds[1]) {
		this->Velocity.y = -this->Velocity.y;
		this->LogoPosition.y = 0.0f;
	}
	else if (this->LogoPosition.y + this->Size.y >= window_height  && activeBounds[3]) {
		this->Velocity.y = -this->Velocity.y;
		this->LogoPosition.y = window_height - this->Size.y;
	}
	
	if(!inBounds) {
		
		if (!activeBounds[0] && this->LogoPosition.x > 0.0f) {
			activeBounds[0] = true;
		}

		if (!activeBounds[1] && this->LogoPosition.y > 0.0) {
			activeBounds[1] = true;
		}

		if (!activeBounds[2] && this->LogoPosition.x + this->Size.x < window_width) {
			activeBounds[2] = true;
		}

		if (!activeBounds[3] && this->LogoPosition.y + this->Size.y < window_height) {
			activeBounds[3] = true;
		}
		
		if (activeBounds[0] && activeBounds[1] && activeBounds[2] && activeBounds[3]) {
			inBounds = true;
	
		}
	}
	
	return this->LogoPosition;

}