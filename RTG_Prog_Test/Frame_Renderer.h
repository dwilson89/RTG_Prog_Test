/*Class FrameRenderer, hosts the functionality that controls the rendering of frames for the demo 
This class has been modified and based on the Original file created by Joey de Vries found at: http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/sprite_renderer.h &
http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/sprite_renderer
*/

#ifndef FRAME_RENDERER_H
#define FRAME_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture2d.h"
#include "shader.h"

class FrameRenderer
{
public:
	// Constructor
	FrameRenderer(Shader &shader);
	
	// Destructor
	~FrameRenderer();

	// Function that renders the given frame (texture2d) in the allocated position
	// Param: frame, the frame to render
	// Param: x, the x coordinate
	// Param: y, the y coordinate
	void Render(Texture2D &frame, int x, int y);
private:
	
	Shader shader;
	GLuint quadVAO;
	
	// Function that initialises the renderer by configuring the VAO/VBO
	void initRenderData();

};

#endif