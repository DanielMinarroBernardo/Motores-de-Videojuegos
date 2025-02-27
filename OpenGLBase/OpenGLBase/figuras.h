#pragma once
#include "vectors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//Quiere decir que al ser lo mismo se usa el alias de Punto2D en vez de vec2
typedef vec2 Punto2D;


// Defino la clase linea2d
class Linea2D {
	Punto2D inicio;
	Punto2D final;

public:
	Linea2D(Punto2D inicio, Punto2D final) :inicio(inicio), final(final) {}

	const float longitud();
	//const double  angulo();
};


//Defino la clase de Ciruclo
struct Circulo {
	Punto2D centro;
	float radio;

	Circulo(float radio):radio(radio){}
	Circulo(float radio,Punto2D centro) :radio(radio),centro(centro) {}

	bool colision(Circulo c2);
	//bool colision(Rectangulo r);
};


//Defino la clase de Rectangulo
struct Rectangulo {
	Punto2D pos;
	vec2 diagonal;

	Rectangulo(Punto2D pos,vec2 diagonal):pos(pos),diagonal(diagonal){}
	Rectangulo(vec2 diagonal) :pos(Punto2D(0,0)), diagonal(diagonal) {}

	bool colision(Rectangulo r);
	bool colision(Circulo c); 
};

struct Triangulo {
	unsigned int VBO = 0, VAO = 0;
	Punto2D a, b, c;
	Triangulo(Punto2D a, Punto2D b, Punto2D c) :a(a), b(b), c(c) {

		vec2 ab = b - a;
		vec2 bc = c - b;

		vec2 uni_ab = vec2(ab.x / ab.modulo(), ab.y / ab.modulo());
		vec2 uni_bc = vec2(bc.x / bc.modulo(), bc.y / bc.modulo());
		

		if (uni_ab == uni_bc || uni_ab == vec2(0, 0) - uni_bc) {

		}

	}


	float* toArray();

	void draw();

	bool colission(Punto2D p);

};