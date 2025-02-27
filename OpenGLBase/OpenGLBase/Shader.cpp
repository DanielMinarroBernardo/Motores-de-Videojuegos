#include "Shader.h"

Shader::Shader(std::string vertexShaderFuente, std::string fragmentShaderFuente) {
	//VERTEX SHADER COMPILE
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* temp_vs = vertexShaderFuente.c_str();
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


	//FRAGEMENT SHADER COMPILE
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* temp_fs = fragmentShaderFuente.c_str();
	glShaderSource(fragmentShader, 1, &temp_fs, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &exito);
	if (exito) {
		std::cout << "Compilado el Fragment Shader";
	}
	else {
		std::cout << "No se ha compilado el Fragment Shader";
	}

	//SHADER PROGRAM

	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertexShader);
	glAttachShader(this->programID, fragmentShader);
	glLinkProgram(this->programID);


	// FIN SHADSER PROGRAM
}

void Shader::use() {
	glUseProgram(this->programID);
}

void Shader::setColor(vec3 color) {
	int modificador_color = glGetUniformLocation(this->programID, "MyColor");


	//4f por vec4 de floats
	glUniform4f(modificador_color, color.x, color.y, color.z, 1.0f);

}