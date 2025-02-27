#include  <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "figuras.h"
#include "Shader.h"

GLFWwindow* ventana;

const unsigned int W_WIDTH = 1024;
const unsigned int W_HEIGHT = 768;

int main() {

	//ventana
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
	//venatana fin



	// VERTEX SHADER INICIO
	std::string vertexShaderCode =
		"#version 330 core\n"
		"layout(location = 0) in vec2 posicion; \n"
		"void main() {\n"
		"	gl_Position = vec4((posicion.x-512)/512 ,(384-posicion.y)/384 , 0.5, 1.0);  \n"
		"}\0";
	
	// VERTEX SHADER FIN

	// FRAGMENT SHADER INICIO
		std::string fragmentShaderCode =
		"#version 330 core\n"
		"out vec4 FragColor; \n"
		"uniform vec4 MyColor;\n"
		"void main() {\n"
		"	FragColor = MyColor;\n"
		"}\0";
	// FRAGMENT SHADER FIN

	Shader sh1(vertexShaderCode, fragmentShaderCode);


	Triangulo t({ 40,40 }, { 140,230 }, { 70,530 });


	/// VERTICES A DIBUJAR

	/*float vertices[]{
		0.0f,0.0f,
		1.0f,0.0f,
		0.5f,1.0f
	};*/
	
	/*float vertices[]{
		(W_WIDTH - t.a.x) / W_WIDTH, (W_HEIGHT - t.a.y) / W_HEIGHT,
		(W_WIDTH - t.b.x) / W_WIDTH, (W_HEIGHT - t.b.y) / W_HEIGHT,
		(W_WIDTH - t.c.x) / W_WIDTH, (W_HEIGHT - t.c.y) / W_HEIGHT,
	};*/

	float verde_cambiante = 0.0f;

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		//-----------------------------------------------------------------------------------------------------------------------------------------------
		//inicio

		sh1.use();
	

		float timeValue = glfwGetTime();
		verde_cambiante = sin(timeValue);	

		sh1.setColor({ 0.5f , verde_cambiante, 0.5f });

		if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			t.a.x = t.a.x + 5;
			t.b.x = t.b.x + 5;
			t.c.x = t.c.y + 5;
		}

		t.draw();
			

		//final
		//-----------------------------------------------------------------------------------------------------------------------------------------------
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana)==0);

	glfwTerminate();

	return 0;
}