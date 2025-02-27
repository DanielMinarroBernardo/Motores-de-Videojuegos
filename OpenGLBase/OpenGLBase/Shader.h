#pragma once
#include <iostream>
#include "vectors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Shader
{
	unsigned int programID;
public:

	Shader(std::string vertexShaderFuente, std::string fragmentShaderFuente);
	void use();

	//Opcionalmente acceso a los uniforms

	void setColor(vec3 color);
};

