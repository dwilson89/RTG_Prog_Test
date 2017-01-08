/*Class DemoManagement, hosts general functionality and important logo demo variables.
This class has been modified and based on the Original file created by Joey de Vries found at: http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/resource_manager.h
& http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/resource_manager
*/

#ifndef DEMO_MANAGEMENT_H
#define DEMO_MANAGEMENT_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture2d.h"
#include "shader.h"


/* A static singleton class that hosts several functions that handles the loading and storing
of textures and shaders used by the LogoDemo application.
*/
class DemoManagement
{
public:

	static Shader LogoShader;

	static Texture2D Frames[8];

	static glm::vec2 Size; // Size of the logo

	// Function that loads a shader program from file loading vertex, fragment shader's source code.
	// Param: vShaderFile, the file path
	// Param: fShaderFile, the file path
	static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile);
	
	// Function that retrieves the stored shader
	static Shader   GetShader();
	
	// Function that loads (and generates) a texture from file
	// Param: file, the file path
	// Param: alpha, alpha flag
	// Param: idx, the index of the frame
	static Texture2D LoadFrame(const GLchar *file, GLboolean alpha, int idx);
	
	// Function that retrieves a stored texture
	// Param: idx, the index of the frame
	// Return: Texture2, requested frame
	static Texture2D GetFrame(int idx);
	
	// Function that [roperly de-allocates all loaded resources
	static void      Clear();

	// Function that sets the run animation state
	// Param: isRunning, animation flag
	static void SetRunAnimation(bool isRunning);
	
	// Function that returns a flag indicated if the animation is to be continued
	// Return: bool, will return Boolean true if the animation can continue but false should the animation need to exit
	static bool CanWeContinue();

private:
	DemoManagement() { }

	// Loads and generates a shader from file
	// Param: vShaderFile, the vertex shader file path
	// Param: fShaderFile, the fragment shader file path
	static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);
	
	// Loads a single texture from file
	// Param: file, the file path
	// Param: alpha, alpha flag
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);

	static bool runAnimation;
	
};

#endif