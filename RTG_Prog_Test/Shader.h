/*Class Shader, hosts the functionality to generate a compiled shader, and useful utility functions
This class is a modified based on the Original file created by Joey de Vries found at: http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/shader.h &
http://www.learnopengl.com/code_viewer.php?code=in-practice/breakout/shader
*/
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>;
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	
	// The program ID
	GLuint Program;

	// Constructor
	Shader() { }

	// Function that compiles the shader
	// Param: vShaderSource, the vertex shader source string (code)
	// Param: fShaderSource, the fragment shader source string (code)
	void Compile(const GLchar* vShaderSource, const GLchar* fShaderSource);

	// Function that sets the Matrix4 for the shader
	// Param: name, the name of the variable to set
	// Param: matrix, the mat4 value to set
	// Param: userShader, flag to use the shader
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
	
	// Function that sets the Integer for the shader
	// Param: name, the name of the variable to set
	// Param: value, the GLint value to set
	// Param: userShader, flag to use the shader
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	
	// Function that sets the Vector3f for the shader
	// Param: name, the name of the variable to set
	// Param: matrix, the vec3 value to set
	// Param: userShader, flag to use the shader
	void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);

	// Function that sets the float for the shader
	// Param: name, the name of the variable to set
	// Param: matrix, the float value to set
	// Param: userShader, flag to use the shader
	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader);
	
	// Function that when called indicates to use the program
	Shader  &Use();

private:
	// Function that checks if compilation or linking failed and if so, print the error logs
	// Param: object, GLuint object to enquire
	// Param: type, string representation of the object types name
	void    checkCompileErrors(GLuint object, std::string type);
};

#endif