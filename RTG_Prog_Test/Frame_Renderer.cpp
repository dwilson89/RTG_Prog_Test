#include "Frame_Renderer.h"
#include "demo_management.h"


FrameRenderer::FrameRenderer(Shader &shader) {
	this->shader = shader;
	this->initRenderData();
}


FrameRenderer::~FrameRenderer() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void FrameRenderer::Render(Texture2D &frame, int x, int y) {

	// Activate shader
	this->shader.Use();
	glm::mat4 model;

	// Translate and scale it
	model = glm::translate(model, glm::vec3(glm::vec2(x, y), 0.0f));
	model = glm::scale(model, glm::vec3(DemoManagement::Size, 1.0f));
	
	// Set the model matrix
	this->shader.SetMatrix4("model", model);

	glm::vec3 color = glm::vec3(1.0f);

	// Set the color vector used by the shader
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	
	// Bind the frame
	frame.Bind();
	
	// Draw the object
	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0); 
}

void FrameRenderer::initRenderData() {
	
	// Configure VAO/VBO
	GLuint VBO;

	// Set the vertices
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	// Copy vertex array in a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Unbinds VAO

}