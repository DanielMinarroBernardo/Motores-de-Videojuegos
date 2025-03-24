#pragma once
#include "vectors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "ext.hpp"
#include "Shader.h"

typedef vec2 Punto2D;

class Linea2D {
	Punto2D inicio;
	Punto2D final;

public:
	Linea2D(Punto2D inicio, Punto2D final) 
		: inicio(inicio), final(final) {
	}

	const float& longitud();
	// const double angulo();
};


struct Circulo {
	Punto2D centro;
	float radio;
	unsigned int VBO = 0, IBO = 0, VAO = 0;
	bool dirty_flag = false;

	Circulo(float radio) : radio(radio) {}
	Circulo(float radio, Punto2D centro) : 
		radio(radio), centro(centro) {}
	bool colision(Circulo c);
	//bool colision(Rectangulo r);

	void draw(float num_segmentos);
};


struct Rectangulo {
	Punto2D pos = {0,0};
	float scl = 1.0f;
	float rot = 0.0f;

	vec2 vel = {0,0};
	vec2 diagonal;
	glm::mat4 transf_interna = glm::mat4(1.0f);

	unsigned int VBO = 0, IBO = 0, VAO = 0;
	bool dirty_flag = false;
	Rectangulo(Punto2D pos, vec2 diagonal) : 
		pos(pos), diagonal(diagonal) {}
	Rectangulo(vec2 diagonal) :
		diagonal(diagonal) {
	}

	// transformaciones
	void transform(glm::mat4 transformacion);

	// renderizado
	void draw(Shader sh);

	// colisiones
	bool colision(Rectangulo r);
	bool colision(Circulo c);

	// fisicas
	void move(double tiempo_trasncurrido);
};


struct RectanguloRotado {
	Punto2D centro = { 0,0 };
	vec2 vel = { 0,0 };
	vec2 semiLongitudH, semiLongitudV;
	glm::mat4 transf_interna = glm::mat4(1.0f);
	
	unsigned int VBO = 0, IBO = 0, VAO = 0;
	bool dirty_flag = false;
	RectanguloRotado(Punto2D centro, vec2 semiLongitudH, vec2 semiLongitudV) :
		centro(centro), semiLongitudH(semiLongitudH), semiLongitudV(semiLongitudV) {}

	RectanguloRotado(Punto2D centro, float semiLongitudH, float semiLongitudV, double angulo) :
		centro(centro), 
		semiLongitudH(semiLongitudH * cos(glm::radians(angulo)), semiLongitudV * sin(glm::radians(angulo))),
		semiLongitudV(semiLongitudH * cos(glm::radians(angulo + 90)), semiLongitudV * sin(glm::radians(angulo + 90))) {}

	
	// transformaciones
	void transform(glm::mat4 transformacion);

	// renderizado
	void draw();

	// colisiones
	bool colision(Rectangulo r);
	bool colision(Circulo c);

	// fisicas
	void move(double tiempo_trasncurrido);
};


struct Triangulo {
	Punto2D a, b, c;
	unsigned int VBO = 0, VAO = 0;
	bool dirty_flag = false;
	Triangulo(Punto2D a, Punto2D b, Punto2D c) :
		a(a), b(b), c(c) {
		
		vec2 ab = b - a;
		vec2 bc = c - b;

		vec2 uni_ab = vec2(ab.x / ab.modulo(), ab.y / ab.modulo());
		vec2 uni_bc = vec2(bc.x / bc.modulo(), bc.y / bc.modulo());

		//std::cout << uni_ab.x << ", " << uni_ab.y << std::endl;
		//std::cout << uni_bc.x << ", " << uni_bc.y << std::endl;

		if (uni_ab == uni_bc || uni_ab == vec2(0,0) - uni_bc) {

		}
	}

	void draw();

	bool colision(Punto2D p);
};







