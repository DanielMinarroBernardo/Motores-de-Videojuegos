

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



	// 3D

	std::string vertexShaderCode2 =
		"#version 330 core\n"

		"layout (location = 0) in vec2 posicion; \n"
		"layout (location = 1) in vec3 color; \n"

		"out vec3 colorVertice;\n"

		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 proj;\n"

		"void main() {\n"

		"	gl_Position = proj * view * model * vec4(posicion, 0.0f, 1.0f);\n"
		"	colorVertice = color;\n"
		"}\0";

	/// FRAGMENT SHADER
	std::string fragmentShaderCode2 =
		"#version 330 core\n"

		"out vec4 FragColor; \n"
		"in vec3 colorVertice;"
		//"uniform vec4 miColor; \n"

		"void main() {\n"
		"    FragColor = vec4(colorVertice, 1.0f); \n"
		"}\0";

	Shader sh2(vertexShaderCode2, fragmentShaderCode2);



	Triangulo t(
		{ 230,100}, { 60,600 }, {15,15}
	);


	/*Rectangulo r(
		{ 10,40 }, { 100,170 }
	);*/
	 
	/*Rectangulo r(
		{ 20.0f, 20.0f }, { 30.0f, 30.0f }
	);*/

	Rectangulo r(
		{ 0.25f, 0.25f }, { 0.5f, 0.5f }
	);
	//Rectangulo r2(
	//	{ 150,150 }, { 230,230 }
	//);

	//RectanguloRotado rr(
	//	{0.0f,0.0f}, {0.1f, 0.1f}, {-0.1f, 0.1f}
	//);
	/*RectanguloRotado rr(
		{0.0f,0.0f}, 0.25f, 0.1f, 90
	);*/

	Circulo c(
		50, { 150, 190 }
	);









	////PROJECTION
	//glm::mat4 Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	////VIEW
	//glm::mat4 View = glm::mat4(1.);
	//View = glm::translate(View, glm::vec3(2.0f, 4.0f, -25.0f));

	////MODEL
	//glm::mat4 Model = glm::mat4(1.0);
	////Scale by factor 0.5
	////Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	//Model = glm::rotate(Model, 0.03f, glm::vec3(0.0f, 1.0f, 0.0f));

	//std::cout << Model[0][0];






	float timePastValue = 0;
	float timeActualValue = 0;
	float verde_cambiante = 0.5f;



	unsigned int VAO; // vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int VBO; // vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	float vertices[] = {
			0.0f, 0.0f,					0.0f, 1.0f, 0.0f, // Eje x
			1.0f, 0.0f,					0.0f, 1.0f, 0.0f,
			0.0f, 0.0f,					0.0f, 1.0f, 0.0f, // Eje y
			0.0f, 1.0f,					0.0f, 1.0f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	float camara_x = 0;
	float camara_y = 0;

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		// INICIO

		
		sh2.use();
		/*timePastValue = timeActualValue;
		timeActualValue = glfwGetTime();*/

		//verde_cambiante = sin(timeValue);


		//std::cout << timeActualValue - timePastValue << "\n";


		// Input

	

		if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			/*r.vel.x = 100.0f;
			r.dirty_flag = true;*/
			r.pos.x += 0.05f;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_PRESS) {
			/*r.vel.x = -100.0f;
			r.dirty_flag = true;*/
			r.pos.x -= 0.05f;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_RELEASE &&
			glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_RELEASE) {
			/*r.vel.x = 0.0f;*/
		}

		if (glfwGetKey(ventana, GLFW_KEY_UP) == GLFW_PRESS) {
			/*r.vel.y = -100.0f;
			r.dirty_flag = true;*/
			r.scl += 0.05;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_PRESS) {
			/*r.vel.y = 100.0f;
			r.dirty_flag = true;*/
			r.scl -= 0.05;
		}

		if (glfwGetKey(ventana, GLFW_KEY_E) == GLFW_PRESS) {
			/*r.vel.y = -100.0f;
			r.dirty_flag = true;*/
			r.rot -= 0.5;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_Q) == GLFW_PRESS) {
			/*r.vel.y = 100.0f;
			r.dirty_flag = true;*/
			r.rot += 0.5;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE && 
			glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE) {
			//r.vel.y = 0.0f;
		}
		



		sh2.setColor({ 1.0f, 0.7f, 0.1f });


		//transf_total = glm::scale(transf_total, glm::vec3(0.5f, 1.0f, 1.0f));
		//transf_total = glm::rotate(transf_total, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//transf_model = glm::translate(transf_model, glm::vec3(0.5f, 0.0f, 0.0f));
		

		//transf_view = glm::translate(transf_view, glm::vec3(0.5f, 0.0f, 0.0f));

		



		//glm::mat4 transf_model = glm::mat4(1.0f);
		//transf_model = glm::scale(transf_model, glm::vec3(0.5f, 1.0f, 1.0f));
		//transf_model = glm::rotate(transf_model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//r.transform(transf_model);
		
		
		//// Fisicas
		//if (r.colision(c)) {
		//	sh1.setColor({ 1.0f, 0.7f, 0.1f });
		//}
		//else {
		//	sh1.setColor({ 0.5f, verde_cambiante, 0.5f });
		//}
		//
		/*r.move(timeActualValue - timePastValue);*/


		//PROYECCION 
		// matriz ortogonal
		//glm::mat4 transf_proj = glm::ortho(0.0f, 60.0f, 0.0f, 60.0f, 0.0f, 60.0f);
		// matriz perspectiva
		glm::mat4 transf_proj = glm::perspective(glm::radians(45.0f), (float)(W_WIDTH / W_HEIGHT), 0.0f, 100.0f);
		sh2.setProjMatrix(transf_proj);



		// CAMARA

		glm::mat4 transf_camara = glm::mat4(1.0f);
		//transf_camara = glm::translate(transf_camara, glm::vec3(0.0f, 0.0f, 0.0f));
		sh2.setViewMatrix(transf_camara);




		// Render

		//Dibujo de los ejes

		glm::mat4 transf_ejes = glm::mat4(1.0f);
		sh2.setModelMatrix(transf_ejes);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 4);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		// Dibujo del rectangulo

		r.draw(sh2);


		
		





		//r2.draw();
		//t.draw();
		/*c.draw(50);*/

		//rr.draw();


		
		//FINAL
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana) == 0);

	glfwTerminate();


	return 0;
}