
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

void Shader::setModelMatrix(glm::mat4 transform) {
	int matriz_transf = glGetUniformLocation(this->programID, "model");

	glUniformMatrix4fv(matriz_transf, 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::setViewMatrix(glm::mat4 transform) {
	int matriz_transf = glGetUniformLocation(this->programID, "view");

	glUniformMatrix4fv(matriz_transf, 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::setProjMatrix(glm::mat4 transform) {
	int matriz_transf = glGetUniformLocation(this->programID, "proj");

	glUniformMatrix4fv(matriz_transf, 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::setTexture() {
	glUniform1i(glGetUniformLocation(this->programID, "datosTextura"), 0);
}

void Shader::setColorAmbiente(vec3 color) {
	int modificador_color = glGetUniformLocation(this->programID, "colorAmbiente");

	glUniform3f(modificador_color, color.x, color.y, color.z);
}

void Shader::setPosLuz(vec3 pos) {
	int modificador_pos = glGetUniformLocation(this->programID, "lightPosition");

	glUniform3f(modificador_pos, pos.x, pos.y, pos.z);
}

void Shader::setPosView(glm::vec3 pos) {
	int modificador_pos = glGetUniformLocation(this->programID, "viewPosition");

	glUniform3f(modificador_pos, pos.x, pos.y, pos.z);
}




void Shader::setMaterial(glm::vec3 ambiente, glm::vec3 difuso, 
	glm::vec3 especular, float radio_brillo) {

	int modificador_amb = glGetUniformLocation(this->programID, "material.ambiente");
	int modificador_dif = glGetUniformLocation(this->programID, "material.difuso");
	int modificador_esp = glGetUniformLocation(this->programID, "material.especular");
	int modificador_bri = glGetUniformLocation(this->programID, "material.radio_brillo");

	glUniform3f(modificador_amb, ambiente.x, ambiente.y, ambiente.z);
	glUniform3f(modificador_amb, difuso.x, difuso.y, difuso.z);
	glUniform3f(modificador_amb, especular.x, especular.y, especular.z);
	glUniform1f(modificador_amb, radio_brillo);
}
