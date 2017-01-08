#ifndef LOGO_H
#define LOGO_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture2d.h"
#include "frame_renderer.h"


class Logo
{
public:


	Texture2D CurrentFrame;
	glm::vec2 LogoPosition;
	glm::vec2 Size;
	glm::vec2 Velocity;

	Logo();
	Logo(glm::vec2 position, Texture2D frame, glm::vec2 size);

	void init(glm::vec2 pos, glm::vec2 vel, glm::vec2 size, Texture2D frame, const bool (&bound)[4]);
	
	glm::vec2 Move(GLfloat dt, GLuint window_width, GLuint window_height);

	void Draw(FrameRenderer &renderer);

private:
	bool inBounds; // Variable to indicate when to use the window bounds for movement 
	bool activeBounds[4];
};

#endif