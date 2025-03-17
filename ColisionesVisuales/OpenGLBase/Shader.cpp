
#include "Shader.h"


Shader::Shader(std::string vertexShaderFuente, 
	std::string fragmentShaderFuente) {

	// Vertex Shader compile
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* temp_vs = vertexShaderFuente.c_str();
	glShaderSource(vertexShader, 1, &temp_vs, NULL);
	glCompileShader(vertexShader);

	int exito;
	char info[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &exito);
	if (exito) {
		std::cout << "Compilado el Vertex Shader\n";
	}
	else {
		std::cout << "No se ha compilado el Vertex Shader\n";
	}

	// Fragment Shader compile
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* temp_fs = fragmentShaderFuente.c_str();
	glShaderSource(fragmentShader, 1, &temp_fs, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &exito);
	if (exito) {
		std::cout << "Compilado el Fragment Shader\n";
	}
	else {
		std::cout << "No se ha compilado el Fragment Shader\n";
	}


	/// Shader Program

	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertexShader);
	glAttachShader(this->programID, fragmentShader);
	glLinkProgram(this->programID);
}


void Shader::use() {
	glUseProgram(this->programID);
}

void Shader::setColor(vec3 color) {
	int modificador_color = glGetUniformLocation(this->programID, "miColor");

	glUniform4f(modificador_color, color.x, color.y, color.z, 1.0f);
}

void Shader::setTransformMatrix(glm::mat4 transform) {
	int matriz_transf = glGetUniformLocation(this->programID, "transforms");
	
	glUniformMatrix4fv(matriz_transf, 1, GL_FALSE, glm::value_ptr(transform));
}