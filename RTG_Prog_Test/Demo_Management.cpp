#include "Demo_Management.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

// Initialise
Shader								DemoManagement::LogoShader;
Texture2D							DemoManagement::Frames[8];
bool DemoManagement::runAnimation = true;
glm::vec2 DemoManagement::Size = glm::vec2(150, 150);


Shader DemoManagement::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile) {
	LogoShader = loadShaderFromFile(vShaderFile, fShaderFile);
	return LogoShader;
}

Shader DemoManagement::GetShader() {
	return LogoShader;
}

Texture2D DemoManagement::LoadFrame(const GLchar *file, GLboolean alpha, int idx) {
	Frames[idx] = loadTextureFromFile(file, alpha);
	return Frames[idx];
}

Texture2D DemoManagement::GetFrame(int idx) {
	return Frames[idx];
}

void DemoManagement::Clear() {
	// (Properly) delete the shader	
	glDeleteProgram(LogoShader.Program);
	// (Properly) delete all textures
	for (auto iter : Frames)
		glDeleteTextures(1, &iter.ID);

}

void DemoManagement::SetRunAnimation(bool isRunning) {
	runAnimation = isRunning;
}

bool DemoManagement::CanWeContinue() {
	return runAnimation;
}

Shader DemoManagement::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile) {
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);
	return shader;
}

Texture2D DemoManagement::loadTextureFromFile(const GLchar *file, GLboolean alpha) {
	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}

