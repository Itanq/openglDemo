#include"stars.h"



int Star::GenerateCircle()
{
	int index = 0;
	GLfloat R = this->radius;
	for (int i = 0; i <= 360; ++i)
	{
		float u = i*(PI / 180.0f);
		float x = R*cos(u);
		float y = R*sin(u);
		trackData[index++] = x;
		trackData[index++] = y;
		trackData[index++] = 0.0f;
	}
	return index;
}

Star::Star(Shader& sphereShader, Shader& trackShader, GLfloat radius)
{
	this->sphereShader = sphereShader;
	this->trackShader = trackShader;
	this->radius = radius;
}
Star::~Star()
{
	glDeleteShader(this->sphereShader.Program);
	glDeleteShader(this->trackShader.Program);
}

void Star::init(GLuint& VAO)
{
	sphereVAO = VAO;
	trackCount = GenerateCircle();
	GLuint trackVBO;
	glGenVertexArrays(1, &trackVAO);
	glGenBuffers(1, &trackVBO);
	glBindVertexArray(trackVAO);
	glBindBuffer(GL_ARRAY_BUFFER, trackVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trackData), trackData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void Star::setStar(glm::vec3 size,GLfloat selfSpeed,GLfloat speed,GLboolean sun)
{
	view = glm::mat4();
	projection = glm::mat4();
	view = camera.GetViewMatrix(); 
	projection = glm::perspective(camera.Zoom, 800.0f/600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->sphereShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(this->sphereShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	this->size = size;
	GLfloat x = (GLfloat)cos(glfwGetTime()*speed)*radius;
	GLfloat y = (GLfloat)sin(glfwGetTime()*speed)*radius;
	if(sun) model = glm::mat4();
	else model = translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(x, y, 0.0f));
	model = glm::scale(model, size);
	model = glm::rotate(model, (GLfloat)glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::rotate(model, (GLfloat)glm::radians(glfwGetTime()*selfSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(radius, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(this->sphereShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

void Star::drawStar(GLint sphereCount)
{

	glBindVertexArray(trackVAO);
	//glDrawArrays(GL_LINES, 0, trackCount);
	glBindVertexArray(0);

	glBindVertexArray(sphereVAO);
	glDrawArrays(GL_LINES, 0, sphereCount);
	glBindVertexArray(0);
}



