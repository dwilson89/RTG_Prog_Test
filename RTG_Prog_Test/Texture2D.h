/*Class Texture2D, hosts texture information and the functionality to generate based on properties indicated.
This class has been based on the Original file created by Joey de Vries found at: http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/texture.h &
http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/texture
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture2D
{
public:

	// Texture Variables
	GLuint ID;
	GLuint Width, Height;

	GLuint Internal_Format;
	GLuint Image_Format;

	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Max;

	// Constructor
	Texture2D();
	
	// Function that generates texture from image data
	// Param: width, the image width
	// Param: height, the image height
	// Param: data, loaded image information
	void Generate(GLuint width, GLuint height, unsigned char* data);
	
	// Function that binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;
	
};

#endif