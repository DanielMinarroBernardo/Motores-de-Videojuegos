#pragma once
#include "vectors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "ext.hpp"
#include "Shader.h"



typedef vec2 Punto2D;
typedef vec3 Punto3D;


struct Cubo {
	Punto3D pos = { 0,0,0 };
	float scl = 1.0f;
	float rot = 0.0f;

	vec3 vel = { 0,0 ,0 };
	vec3 diagonal;
	glm::mat4 transf_interna = glm::mat4(1.0f);

	unsigned int VBO = 0, IBO = 0, VAO = 0;
	bool dirty_flag = false;
	Cubo(Punto3D pos, vec3 diagonal) :
		pos(pos), diagonal(diagonal) {
	}
	Cubo(vec3 diagonal) :
		diagonal(diagonal) {
	}

	// transformaciones
	void transform(glm::mat4 transformacion);

	// renderizado
	void draw(Shader sh);

	// colisiones
	bool colision(Rectangulo r);
	bool colision(Cubo c);

	// fisicas
	void move(double tiempo_trasncurrido);
};

