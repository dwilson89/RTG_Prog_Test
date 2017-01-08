#include "Shader.h"



void Shader::Compile(const GLchar* vShaderSource, const GLchar* fShaderSource) {

	// Compile shaders
	GLuint vertex, fragment;

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, NULL);
	glCompileShader(vertex);
	// Print vertex compile errors if any
	checkCompileErrors(vertex, "VERTEX");

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, NULL);
	glCompileShader(fragment);
	
	// Print fragment compile errors if any
	checkCompileErrors(fragment, "FRAGMENT");

	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	// Print linking errors if any
	checkCompileErrors(this->Program, "PROGRAM");

	// Delete the shaders, no longer needed
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->Program, name), value);
}

void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z);
}

void Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader){
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->Program, name), value);
}


Shader &Shader::Use() {
	glUseProgram(this->Program);
	return *this;
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	} else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
