

#include<iostream>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <cmath>

#include "figuras.h"
#include "Shader.h"

#include <glm.hpp>
#include <ext.hpp>



GLFWwindow* ventana;
const unsigned int W_WIDTH = 1024;
const unsigned int W_HEIGHT = 768;

int main() {

	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	ventana = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Testeo", NULL, NULL);

	glfwMakeContextCurrent(ventana);
	glewExperimental = GL_TRUE;

	glewInit();


	/// VERTEX SHADER
	std::string vertexShaderCode =
		"#version 330 core\n"

		"layout (location = 0) in vec2 posicion; \n"

		"void main() {\n"
		"   gl_Position = vec4( (posicion.x - 512) / 512, \n" 
		"	(384 - posicion.y) / 384, 0.5, 1.0); \n"
		"}\0";

	/// FRAGMENT SHADER
	std::string fragmentShaderCode =
		"#version 330 core\n"

		"out vec4 FragColor; \n"
		"uniform vec4 miColor; \n"

		"void main() {\n"
		"    FragColor = miColor; \n"
		"}\0";

	Shader sh1(vertexShaderCode, fragmentShaderCode);

	//ArrayGlobal::libre = 0;
	
	Triangulo t(
		{40,40}, {140,230}, {70,530}
	);
	Rectangulo r(
		{ 240,300 }, { 70,150 }
	);






	//PROJECTION
	glm::mat4 Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	//VIEW
	glm::mat4 View = glm::mat4(1.);
	View = glm::translate(View, glm::vec3(2.0f, 4.0f, -25.0f));

	//MODEL
	glm::mat4 Model = glm::mat4(1.0);
	//Scale by factor 0.5
	//Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	Model = glm::rotate(Model, 0.03f, glm::vec3(0.0f, 1.0f, 0.0f));

	std::cout << Model[0][0];





	float verde_cambiante = 0.0f;
	do {
		glClear(GL_COLOR_BUFFER_BIT);
		// INICIO

		
		sh1.use();
		float timeValue = glfwGetTime();
		verde_cambiante = sin(timeValue);


		sh1.setColor({ 0.5f, verde_cambiante, 0.5f });


		if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			t.a.x = t.a.x + 5;
			t.b.x = t.b.x + 5;
			t.c.x = t.c.x + 5;
			t.dirty_flaf = true;
		}
		if (glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_PRESS) {
			t.a.x = t.a.x - 5;
			t.b.x = t.b.x - 5;
			t.c.x = t.c.x - 5;
			t.dirty_flaf = true;
		}


		t.draw();
		r.draw();

	




		//FINAL
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana) == 0);

	glfwTerminate();


	return 0;
}