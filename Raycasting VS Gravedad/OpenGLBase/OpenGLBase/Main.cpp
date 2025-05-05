

#include<iostream>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <cmath>

#include "figuras.h"
#include "Shader.h"

#include <glm.hpp>
#include <ext.hpp>
#include <gtc/matrix_transform.hpp>

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
		"layout (location = 3) in vec3 normales; \n"

		"out vec3 colorVertice;\n"
		"out vec2 TexCoord;\n"

		"out vec3 Normal; \n"
		"out vec3 Posicion_Frag; \n"

		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 proj;\n"

		"void main() {\n"

		"	gl_Position = proj * view * model * vec4(posicion, 1.0f);\n"
		
		"	Normal = normales;\n"
		"	Posicion_Frag = vec3(model * vec4(posicion, 1.0f));\n"
		
		"	colorVertice = color;\n"
		"	TexCoord = coordenadas;\n"
		"}\0";

	/// FRAGMENT SHADER
	std::string fragmentShaderCode2 =
		"#version 330 core\n"
		"out vec4 FragColor; \n"

		"in vec3 colorVertice; \n"
		"in vec2 TexCoord; \n"

		"in vec3 Normal; \n"
		"in vec3 Posicion_Frag; \n"

		"uniform sampler2D datosTextura; \n"
		"uniform vec3 colorAmbiente; \n"
		"uniform vec3 lightPosition; \n"

		"uniform vec3 viewPosition; \n"

		"struct Material {\n"
		"	vec3 ambiente;\n"
		"	vec3 difuso;\n"
		"	vec3 especular;\n"
		"	float radio_brillo;\n"
		"};\n"

		"uniform Material material;\n"

		"void main() {\n"
		
		// Luz ambiente
		"	vec3 luzAmbiente = colorAmbiente;\n"

		// Luz difusa
		"	vec3 normal_asegurada = normalize(Normal);\n"
		"	vec3 dir_luz = normalize( Posicion_Frag - lightPosition );\n"

		"	float angulo = max(dot(normal_asegurada, dir_luz), 0.0);\n"
		"	vec3 result_difusa = colorVertice * (angulo);\n"


		// Luz especular
		"	vec3 dir_view = normalize( viewPosition - Posicion_Frag );\n"
		"	vec3 dir_refl = reflect( -dir_view, normal_asegurada );\n"

		//"   FragColor = texture(datosTextura, TexCoord) * vec4(colorVertice, 1.0f); \n"
		"	vec3 result_abiente = colorVertice * luzAmbiente;\n"
		

		"	float nivel_espec = pow(max(dot(dir_view, dir_refl), 0.0), 128);\n"
		"	vec3 result_especular = colorVertice * nivel_espec * 0.5;\n"

		"   FragColor = vec4((result_especular + result_difusa + result_abiente), 1.0f);\n"
		"}\0";

	Shader sh2(vertexShaderCode2, fragmentShaderCode2);

	PhysicalObject cubo(CUBO);
	cubo.addCube(new Cubo({ 0.0f, 700.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));



	Cubo cubo(
		{ 0.0f, 700.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }
	);

	Cubo suelo(
		{ 0.0f, -5.0f, 0.0f }, { 30.0f, 0.01f, 30.0f }
	);
	


	// DEF - TRIANGULO
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2); // Empezar a definir el VAO del triangulo

	unsigned int IBO2;
	glGenBuffers(1, &IBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO2);

	unsigned int trianglVertexIndex[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 9, 
		trianglVertexIndex, GL_DYNAMIC_DRAW);

	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	float trianglVertex[] = {
		// x,y,z	 colores		texturas	normal
		0, 0, 0,	0.5, 0.5, 0,	0,0,		0,0,1,
		0, 1, 0,	0.5, 0.5, 0,	0,1,		0,0,1,
		1, 1, 0,	0.5, 0.5, 0,	1,1,		0,0,1,

		// x,y,z	 colores		texturas	normal
		0, 0, 0,	0.5, 0.5, 0,	0,0,		-1,0,0,
		0, 1, 0,	0.5, 0.5, 0,	0,1,		-1,0,0,
		0, 1, -1,	0.5, 0.5, 0,	1,1,		-1,0,0,

		// x,y,z	 colores		texturas	normal
		0, 1, 0,	0.5, 0.5, 0,	0,0,		0,1,0,
		1, 1, 0,	0.5, 0.5, 0,	0,1,		0,1,0,
		0, 1, -1,	0.5, 0.5, 0,	1,1,		0,1,0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * (3 + 3 + 2 + 3),

		trianglVertex, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 11, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 11, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 11, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 11, (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0); // Dejar de definir el VAO del triangulo


	// Texturas

	float coordTextura[] = {
		0, 0,
		0, 1,
		1, 1
	};


	// Generadores de texturas
	unsigned int text_1_id;
	glGenTextures(1, &text_1_id);
	glBindTexture(GL_TEXTURE_2D, text_1_id);

	// Parametros
	//	Texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//	Filtro al aumentar o disminuir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREAST_MIPMAP_LINEAR)
	//GL_NEAREST_MIPMAP_LINEAR
	//GL_LINEAR_MIPMAP_LINEAR
	//GL_NEAREST_MIPMAP_NEAREST
	//GL_LINEAR_MIPMAP_NEAREST

	//Libreria stb_image.h
	int width, height, nrChannels;

	//stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("box.jpeg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
			0, GL_RGB, GL_UNSIGNED_BYTE, data);
			// Dimensiones (1D, 2D)
			// MimMap level
			// Canales de la textura a generat
			// Dimensiones de la original
			// 0 borde
			// Canal y tipo de la imagen original
			// datos cargados
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load texture" << std::endl;
	}
	stbi_image_free(data);



	unsigned int VAO; // vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	unsigned int VBO; // vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	float vertices[] = {
			0.0f, 0.0f, 0.0f,					0.0f, 1.0f, 0.0f,		0,0, // Eje x
			1.0f, 0.0f, 0.0f,					0.0f, 1.0f, 0.0f,		0,1,
			0.0f, 0.0f, 0.0f,					0.0f, 1.0f, 0.0f,		0,0, // Eje y
			0.0f, 1.0f, 0.0f,					0.0f, 1.0f, 0.0f,		0,1,
			0.0f, 0.0f, 0.0f,					0.0f, 1.0f, 0.0f,		0,0, // Eje z
			0.0f, 0.0f, 1.0f,					0.0f, 1.0f, 0.0f,		0,1
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST); // FACE CULLING


	
	glm::vec3 mouse_dir;


	float deltaTime = 0.0f;
	float ultimo_tiempo = 0.0f;
	

	glfwSetInputMode(ventana, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glm::vec2 pos_antigua;

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// INICIO

		sh2.use();
		sh2.setTexture();
		sh2.setColorAmbiente(vec3(1.0, 1.0, 1.0));
		sh2.setPosLuz(vec3(0.0, 5.0, -10.0));

		// Input
		float tiempo = glfwGetTime();
		deltaTime = tiempo - ultimo_tiempo;
		ultimo_tiempo = tiempo;


		if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			cubo.vel.x = 2.5f;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_PRESS) {
			cubo.vel.x = -2.5f;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_RIGHT) == GLFW_RELEASE &&
			glfwGetKey(ventana, GLFW_KEY_LEFT) == GLFW_RELEASE) {
			cubo.vel.x = 0.0f;
		}

		if (glfwGetKey(ventana, GLFW_KEY_1) == GLFW_PRESS) {
			cubo.vel.y = 2.5f;
		}



		if (glfwGetKey(ventana, GLFW_KEY_UP) == GLFW_PRESS) {
		}
		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_PRESS) {
		}
		else if (glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE && 
			glfwGetKey(ventana, GLFW_KEY_DOWN) == GLFW_RELEASE) {
		}



		/// FIRST PERSON VIEW
		float speed_camera = 2.5f;
		if (glfwGetKey(ventana, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			speed_camera = 10.0f;
		}




		if (glfwGetKey(ventana, GLFW_KEY_W) == GLFW_PRESS) {
			pos_camara += speed_camera * frente_camara * deltaTime;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_S) == GLFW_PRESS) {
			pos_camara -= speed_camera * frente_camara * deltaTime;
		}

		if (glfwGetKey(ventana, GLFW_KEY_A) == GLFW_PRESS) {
			pos_camara -= glm::normalize( glm::cross ( frente_camara, up_camara ) ) * speed_camera * deltaTime;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_D) == GLFW_PRESS) {
			pos_camara += glm::normalize(glm::cross(frente_camara, up_camara)) * speed_camera * deltaTime;
		}

		if (glfwGetKey(ventana, GLFW_KEY_SPACE) == GLFW_PRESS) {
			pos_camara += up_camara * speed_camera * deltaTime;
		}
		else if (glfwGetKey(ventana, GLFW_KEY_R) == GLFW_PRESS) {
			pos_camara -= up_camara * speed_camera * deltaTime;
		}
		

		// FISICAS

		// Deteccion colisiones
		// Reolucion reactiva

		pos_antigua = cubo.pos;

		if (cubo.colision(suelo) && cubo.vel.y < 0) {
			cubo.vel.y = 0;
		}

		
		// Resolucion
		//manera ilusa de resolucion por prediccion
		float tiempo_de_impacto = Raycast::raycast(suelo, Ray(cubo.pos, cubo.vel, cubo.vel.y));
		std::cout << tiempo_de_impacto << std::endl;

		if (tiempo_de_impacto < deltaTime && tiempo_de_impacto != 0) {
			cubo.pos.y = -5;
			cubo.vel.y = 0;
		}

		cubo.move(deltaTime);




		glViewport(0, 0, W_WIDTH, W_HEIGHT);


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
		glfwSetCursorPosCallback(ventana, funcion_mouse);

		glm::mat4 transf_camara = glm::mat4(1.0f);

		transf_camara = glm::lookAt(
			pos_camara,
			pos_camara + frente_camara,
			up_camara
		);

		sh2.setPosView(pos_camara);
		sh2.setViewMatrix(transf_camara);


		// Render

		//Dibujo de los ejes

		glm::mat4 transf_ejes = glm::mat4(1.0f);
		sh2.setModelMatrix(transf_ejes);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 6);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Triangulo con textura

		sh2.setMaterial(
			{ 0.24725, 0.1995 , 0.0745 },
			{ 0.75164, 0.60648, 0.22648 },
			{ 0.628281, 0.555802, 0.366065 },
			0.4f * 32
		);

		/*glBindTexture(GL_TEXTURE_2D, text_1_id);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/
		

		// Dibujo del rectangulo
		cubo.draw(sh2);
		//std::cout << cubo.pos.x << std::endl;


		suelo.draw(sh2);



		
		//FINAL
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana) == 0 && glfwGetKey(ventana, GLFW_KEY_ESCAPE) != GLFW_PRESS);

	glfwTerminate();


	return 0;
}




void funcion_mouse(GLFWwindow* ventana, double x, double y) {

	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (primerMov) {
		last_x = xpos;
		last_y = ypos;
		primerMov = false;
	}

	float cambio_x = xpos - last_x;
	float cambio_y = last_y - ypos;
	last_x = xpos;
	last_y = ypos;

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
	direction.x = cos(glm::radians(yaw)) 
		* cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) 
		* cos(glm::radians(pitch));

	frente_camara = glm::normalize(direction);
	glm::vec3 dhca_camara = glm::normalize(glm::cross(frente_camara, glm::vec3(0,1,0)));
	up_camara = glm::normalize(glm::cross(dhca_camara, frente_camara));

}