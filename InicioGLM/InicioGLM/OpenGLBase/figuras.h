#pragma once
#include "vectors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

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
	Circulo(float radio) : radio(radio) {}
	Circulo(float radio, Punto2D centro) : 
		radio(radio), centro(centro) {}
	bool colision(Circulo c);
	//bool colision(Rectangulo r);
};

//struct ArrayGlobal {
//
//	static float arrayGlobal[1000];
//	static int libre;
//	static void push(float array[], int num_vertex);
//};

struct Rectangulo {
	Punto2D pos;
	vec2 diagonal;
	unsigned int VBO = 0, VAO = 0;
	bool dirty_flaf = false;
	Rectangulo(Punto2D pos, vec2 diagonal) : 
		pos(pos), diagonal(diagonal) {}
	Rectangulo(vec2 diagonal) :
		diagonal(diagonal) {
	}
	bool colision(Rectangulo r);
	bool colision(Circulo c);
	float* toArray();
	void draw();
};


struct Triangulo {
	Punto2D a, b, c;
	unsigned int VBO = 0, VAO = 0;
	bool dirty_flaf = false;
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

	float* toArray();
	void draw();

	bool colision(Punto2D p);
};






