#pragma once

#include<iostream>
#include "vectors.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

class Shader {

	unsigned int programID;

public:
	Shader(std::string vertexShaderFuente, 
		std::string fragmentShaderFuente);
	void use();

	// Opcionalmente, acceso a los uniforms

	void setColor(vec3 color);
	void setViewMatrix(glm::mat4 transform);
	void setModelMatrix(glm::mat4 transform);
	void setProjMatrix(glm::mat4 transform);
};


