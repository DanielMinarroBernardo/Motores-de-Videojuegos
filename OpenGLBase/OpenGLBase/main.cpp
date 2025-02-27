#include  <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

GLFWwindow* ventana;

int main() {

	//ventana
	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	ventana = glfwCreateWindow(1024, 768, "Testeo", NULL, NULL);

	glfwMakeContextCurrent(ventana);
	glewExperimental = GL_TRUE;

	glewInit();
	//venatana fin



	// VERTEX SHADER INICIO
	std::string vertexShaderCode =
		"#version 330 core\n"
		"layout(location = 0) in vec2 posicion; \n"
		"void main() {\n"
		"	gl_Position = vec4(posicion.x ,posicion.y , 0.5, 1.0);  \n"
		"}\0";
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* temp_vs = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &temp_vs, NULL);
	glCompileShader(vertexShader);

	int exito;
	char info[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &exito);
	if (exito) {
		std::cout << "Compilado el Vertex Shader";
	}
	else {
		std::cout << "No se ha compilado el Vertex Shader";
	}
	// VERTEX SHADER FIN

	// FRAGMENT SHADER INICIO
		std::string fragmentShaderCode =
		"#version 330 core\n"
		"out vec4 FragColor; \n"
		"uniform vec4 MyColor;\n"
		"void main() {\n"
		"	FragColor = MyColor;\n"
		"}\0";
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* temp_fs = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &temp_fs, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &exito);
	if (exito) {
		std::cout << "Compilado el Fragment Shader";
	}
	else {
		std::cout << "No se ha compilado el Fragment Shader";
	}
	// FRAGMENT SHADER FIN

	//SHADER PROGRAM

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	// FIN SHADSER PROGRAM


	/// VERTICES A DIBUJAR

	float vertices[]{
		0.0f,0.0f,
		1.0f,0.0f,
		0.5f,1.0f
	};
	


	unsigned int VAO; //Vertex array Object

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO; //Vertex Buffer Object

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// GL_STREAM_DRAW-> meto los datos 1 vez , pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 ve y se utilizan mucho,pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// 1º 0, porque hemos dicho que (posicion = 0)
		// 2º 2, porque cada vertice esta en 2D, en 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertice -> stride
		// 6º puntero
	glEnableVertexAttribArray(0);


	float verde_cambiante = 0.0f;

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		//inicio
		int modificador_color = glGetUniformLocation(shaderProgram, "MyColor");

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		float timeValue = glfwGetTime();
		verde_cambiante = sin(timeValue);


		
		//4f por vec4 de floats
		glUniform4f(modificador_color, 0.5f, verde_cambiante, 0.5f, 1.0f);

		
		glDrawArrays(GL_TRIANGLES,0,3);


		//final
		glfwSwapBuffers(ventana);
		glfwPollEvents();

	} while (glfwWindowShouldClose(ventana)==0);

	glfwTerminate();

	return 0;
}