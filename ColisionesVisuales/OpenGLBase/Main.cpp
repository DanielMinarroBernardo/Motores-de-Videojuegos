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
		//"	  float x_norm = float ((posicion.x - 512) / 512);\n"	
		//"	  float y_norm = float ((384 - posicion.y) / 384);\n"
		"   gl_Position = vec4( (posicion.x - 512) / 512, \n"
		"	(384 - posicion.y) / 384, 0.5, 1.0); \n"
		//"    gl_Position = vec4(posicion.x, posicion.y, 0.5, 1.0); \n"
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

	Triangulo t(
		{ 230,100 }, { 60,600 }, { 15,15 }
	);


	Rectangulo r(
		{ 10,40 }, { 100,170 }
	);

	Rectangulo r2(
		{ 150,150 }, { 230,230 }
	);

	Circulo c(
		50, { 150, 190 }
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



	float timePastValue = 0;
	float timeActualValue = 0;
	float verde_cambiante = 0.5f;

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		// INICIO


		sh1.use();
		timePastValue = timeActualValue;
		timeActualValue = glfwGetTime();

		//verde_cambiante = sin(timeValue);


		//std::cout << timeActualValue - timePastValue << "\n";


		/*----------------------INPUT-----------------------------------------------*/
		if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			//r.pos.x += 0.5;
			r.vel.x = 100.0f;
			r.dirty_flag = true;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_PRESS) {
			r.vel.x = -100.0f;
			r.dirty_flag = true;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_RELEASE &&
			glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_RELEASE) {
			r.vel.x = 0.0f;
			r.dirty_flag = true;
		}

		if (glfwGetKey(ventana, GLFW_KEY_UP) == GLFW_PRESS) {
			r.vel.y = -100.0f;
			r.dirty_flag = true;
		}

		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_PRESS) {
			r.vel.y = 100.0f;
			r.dirty_flag = true;
		}

		else if (glfwGetKey(ventana, GLFW_KEY_UP) == GLFW_RELEASE
			&& glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE) {
			r.vel.y = 0.0f;
		}

		/*---------------------------FÍSICAS----------------------------------------*/

		if (r.colision(c)) {
			sh1.setColor({ 1.0f, 0.7f, 0.1f });
		}
		else {
			sh1.setColor({ 0.5f, verde_cambiante, 0.5f });
		}

		r.move(timeActualValue - timePastValue);

		/*------------------------------s----RENDER------------------------------------*/

		r.draw();
		//r2.draw();
		//t.draw();
		c.draw(50);



		//FINAL
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana) == 0);

	glfwTerminate();


	return 0;
}