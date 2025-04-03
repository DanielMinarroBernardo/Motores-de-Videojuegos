#include<iostream>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <cmath>

#include "figuras.h"
#include "Shader.h"

#include <glm.hpp>
#include <ext.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLFWwindow* ventana;
const unsigned int W_WIDTH = 1024;
const unsigned int W_HEIGHT = 768;

float last_x = W_WIDTH / 2, last_y = W_HEIGHT / 2;
float yaw = -90.0f, pitch = 0;

glm::vec3 pos_camara = glm::vec3(0, 0, 3);
glm::vec3 frente_camara = glm::vec3(0, 0, -1);
glm::vec3 up_camara = glm::vec3(0, 1, 0);

bool primerMov = true;

void funcion_mouse(GLFWwindow* ventana, double x, double y);


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


	// 3D

	std::string vertexShaderCode2 =
		"#version 330 core\n"

		"layout (location = 0) in vec3 posicion; \n"
		"layout (location = 1) in vec3 color; \n"
		"layout (location = 2) in vec2 coordenadas; \n"


		"out vec3 colorVertice;\n"
		"out vec2 textCoord;\n"


		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 proj;\n"

		

		"void main() {\n"

		"	gl_Position = proj * view * model * vec4(posicion, 1.0f);\n"
		"	colorVertice = color;\n"
		"	textCoord = coordenadas;\n"
		"}\0";

	/// FRAGMENT SHADER
	std::string fragmentShaderCode2 =
		"#version 330 core\n"

		"out vec4 FragColor; \n"
		"in vec3 colorVertice;\n"
		"in vec2 textCoord;\n"
		"uniform sampler2D datosTextura; \n"

		"void main() {\n"
		//"    FragColor = vec4(colorVertice, 1.0f); \n"
		"    sampler2D = texture(datosTextura,coordenadas); \n"
		"}\0";

	Shader sh2(vertexShaderCode2, fragmentShaderCode2);




	Cubo cubo(
		{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }
	);

	//float coordsTextura[] = {
	//};


	//DEF TRIANGULO ------------------------------------------------------------------
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);


	unsigned int EBO2;
	glGenBuffers(1, &EBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);


	unsigned int trianguloverticesIndex[] = {
		0,1,2
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3, trianguloverticesIndex, GL_STATIC_DRAW);



	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	
	float triangulovertices[] = {
		//x,y,z,	colores			texturas
		0,0,0,	0,0.5,0.5,			0,0,
		0,1,0,	0,0.5,0.5,			0,1,
		1,1,0,	0,0.5,0.5,			1,1
	
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, triangulovertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	//DEF TRIANGULO ------------------------------------------------------------------
	

	//Texturas -----------------------------------------------------------------------
	

	float coordTextura[] = {
		0,0,
		0,1,
		1,1
	};

	// Generadores de texturas

	unsigned int texture1Id;
	glGenTextures(1, &texture1Id);
	glBindTexture(GL_TEXTURE_2D, texture1Id);

	//Parametros

	//Texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//Filtro al aumentar o disminuir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);

	 //Libreria stg_image.h
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load("texture.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//Dimensiones
		// Mipmap Level
		// Canales de la textura a generar
		// Dimensiones d ela original
		// 0 border
		// Canal y tipo de la imagen original
		// datos
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	




	//Texturas -----------------------------------------------------------------------


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
			0.0f, 0.0f,0.0,					0.0f, 1.0f, 0.0f, // Eje x
			1.0f, 0.0f,0.0,					0.0f, 1.0f, 0.0f,
			0.0f, 0.0f,0.0,					0.0f, 1.0f, 0.0f, // Eje y
			0.0f, 1.0f,0.0,					0.0f, 1.0f, 0.0f,
			0.0f, 0.0f,0.0,					0.0f, 1.0f, 0.0f, // Eje z
			0.0f, 0.0,1.0f,					0.0f, 1.0f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);






	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST); // FACE CULLING


	
	glm::vec3 mouse_dir;
	
	//
	// direccion.x = cos(yaw) * cos(pitch)
	// direccion.y = sin(pitch)
	// direccion.z = sin(yaw) * cos(pitch)

	glfwSetInputMode(ventana, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// INICIO

		
		sh2.use();
		
		/*timePastValue = timeActualValue;
		timeActualValue = glfwGetTime();*/

		//verde_cambiante = sin(timeValue);


		//std::cout << timeActualValue - timePastValue << "\n";


		// Input

		if (glfwGetKey(ventana, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(ventana, true);
		}

		if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			/*r.vel.x = 100.0f;
			r.dirty_flag = true;*/
			cubo.pos.x += 0.05f;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_PRESS) {
			/*r.vel.x = -100.0f;
			r.dirty_flag = true;*/
			cubo.pos.x -= 0.05f;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_RELEASE &&
			glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_RELEASE) {
			/*r.vel.x = 0.0f;*/
		}

		if (glfwGetKey(ventana, GLFW_KEY_UP) == GLFW_PRESS) {
			/*r.vel.y = -100.0f;
			r.dirty_flag = true;*/
			cubo.scl += 0.05;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_PRESS) {
			/*r.vel.y = 100.0f;
			r.dirty_flag = true;*/
			cubo.scl -= 0.05;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE && 
			glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE) {
			//r.vel.y = 0.0f;
		}

		if (glfwGetKey(ventana, GLFW_KEY_Q) == GLFW_PRESS) {
			/*r.vel.y = -100.0f;
			r.dirty_flag = true;*/
			cubo.rot += 0.5;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_E) == GLFW_PRESS) {
			/*r.vel.y = 100.0f;
			r.dirty_flag = true;*/
			cubo.rot -= 0.5;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_E) == GLFW_RELEASE &&
			glfwGetKey(ventana, GLFW_KEY_Q) == GLFW_RELEASE) {
			//r.vel.y = 0.0f;
		}


		/// FIRST PERSON VIEW
		

		const float speed_camera = 0.05f;
		if (glfwGetKey(ventana, GLFW_KEY_W) == GLFW_PRESS) {
			pos_camara += speed_camera * frente_camara;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_S) == GLFW_PRESS) {
			pos_camara -= speed_camera * frente_camara;
		}

		if (glfwGetKey(ventana, GLFW_KEY_A) == GLFW_PRESS) {
			pos_camara -= glm::normalize( glm::cross ( frente_camara, up_camara ) ) * speed_camera;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_D) == GLFW_PRESS) {
			pos_camara += glm::normalize(glm::cross(frente_camara, up_camara)) * speed_camera;
		}
		
		glfwSetCursorPosCallback(ventana, funcion_mouse);

		

		// PROYECCION

		glm::mat4 transf_proj = glm::mat4(1.0f);

		//transf_proj = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, -300.0f, 130.0f);
		transf_proj = glm::perspective(glm::radians(45.0f),
			(float)W_WIDTH / W_HEIGHT,
			0.1f,
			100.0f
		);

		sh2.setProjMatrix(transf_proj);


		// CAMARA


		//camera_direction = camara_pos - cubo.pos;

		glm::mat4 transf_camara = glm::mat4(1.0f);

		transf_camara = glm::lookAt(
			pos_camara,
			pos_camara + frente_camara,
			up_camara
		);
	
		/*transf_camara = vec3::lookAt(
			vec3(camX, 0, camZ),
			vec3(0, 0, 0),
			vec3(0, 1, 0)
		);*/
		
		//transf_camara = glm::translate(transf_camara, glm::vec3(0.0f, 0.0f, -90.0f));
		
		sh2.setViewMatrix(transf_camara);




		// Render

		//Dibujo de los ejes

		glm::mat4 transf_ejes = glm::mat4(1.0f);
		sh2.setModelMatrix(transf_ejes);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 6);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		// Dibujo del rectangulo

		/*
		cubo.draw(sh2);
		std::cout << cubo.pos.x << std::endl;
		*/

		//triangulo con textura
		glBindTexture(GL_TEXTURE_2D, texture1Id);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		

		
		//FINAL
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana) == 0);

	glfwTerminate();


	return 0;
}




void funcion_mouse(GLFWwindow* ventana, double x, double y) {

	if (primerMov) {
		last_x = x;
		last_y = y;
		primerMov = false;
	}
	
	float cambio_x = last_x - x;
	float cambio_y = last_y - y;
	last_x = x;
	last_y = y;

	const float sensitivity = 0.01f;
	cambio_x *= sensitivity;
	cambio_y *= sensitivity;


	yaw += cambio_x;
	pitch += cambio_y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	frente_camara = glm::normalize(direction);



}