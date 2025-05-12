#pragma once
#include "vectors.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "ext.hpp"
#include "Shader.h"

typedef vec2 Punto2D;
typedef vec3 Punto3D;


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
	float rot = 0;
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



struct CollisionReport {
	bool isCollided;
	glm::vec3 dist_collision;

	CollisionReport(bool col, glm::vec3 dist) : isCollided(col), dist_collision(dist) {}
};

struct Cubo {
	glm::vec3 pos = { 0,0,0 };
	float scl = 1.0f;
	float rot = 0;
	glm::vec3 vel = { 0,0,0 };
	glm::vec3 diagonal;
	glm::mat4 transf_interna = glm::mat4(1.0f);
	

	unsigned int VBO = 0, IBO = 0, VAO = 0;
	bool dirty_flag = false;

	Cubo(glm::vec3 pos, glm::vec3 diagonal) {
		this->pos = pos;
		this->diagonal = diagonal;
	}
	Cubo(glm::vec3 diagonal) :
		diagonal(diagonal) {
	}

	// transformaciones
	void transform(glm::mat4 transformacion);

	// renderizado
	void draw(Shader sh);

	// colisiones
	bool colision(Cubo c);

	// fisicas
	void move(double tiempo_trasncurrido);
};



struct Ray {
	glm::vec3 pos;
	glm::vec3 direccion;
	float magnitud = 1;

	Ray() : pos(glm::vec3(0,0,0)), direccion(glm::vec3(0,0,1.0f)) {}
	Ray(glm::vec3 pos) : pos(pos), direccion(glm::vec3(0, 0, 1.0f)) {}
	Ray(glm::vec3 pos, glm::vec3 dir) : pos(pos), direccion(dir) {
		dir = glm::normalize(dir);
	}Ray(glm::vec3 pos, glm::vec3 dir, float magn) 
		: pos(pos), direccion(dir), magnitud(magn) {
		dir = glm::normalize(dir);
	}

	bool colision(glm::vec3 Punto);
};

struct Raycast {
	static float raycast(Cubo cubo, Ray ray);
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

	/*RectanguloRotado(vec2 semiLongitudH, vec2 semiLongitudV) :
		semiLongitudH(semiLongitudH), semiLongitudV(semiLongitudV) {
	}*/

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


enum TipoPhysicalObject {CUBO = 0, ESFERA};

class Esfera {

};


class PhysicalObject {
	

public:

	glm::vec3 pos_anterior;
	Cubo* c;
	Esfera* E;
	TipoPhysicalObject t;
	float masa = 1;
	CollisionReport cr_actual = { false, {0,0,0} };

	bool flag_static = false;
	bool flag_grounded = false;

	PhysicalObject(TipoPhysicalObject t) : t(t) {}
	
	void addCube(Cubo *c) {
		if (t == CUBO) {
			this->c = c;
		}
	}

	void setStatic() {
		flag_static = true;
	}

	void setSpeed(glm::vec3 vel) {
		if (t == CUBO) {
			this->c->vel = vel;
		}
	}

	void update(double tiempo_transcurrido) {
		if (!flag_static) {
			if (t == CUBO) {

				this->pos_anterior = this->c->pos;

				if (cr_actual.isCollided) {
					std::cout << cr_actual.dist_collision.y << std::endl;
					this->c->pos = this->c->pos - (cr_actual.dist_collision);
					//this->c->vel.y = 0;
					this->pos_anterior = this->c->pos;
				}

				this->c->move(tiempo_transcurrido);
			}
		}
	};


	void draw(Shader sh) {
		if (t == CUBO) {
			c->draw(sh);
		}
	};

	CollisionReport collision(Cubo cubo2) {

		if (this->c->colision(cubo2)) {

			glm::vec3 direccion = this->c->pos - this->pos_anterior;
			glm::vec3 distancia_penetracion(0,0,0);

			// Vc = Pcubo1_vector · unitario(Pcubo2 - Pcubo1) + Pcubo2_vector · unitario(Pcubo1 - Pcubo2)
			// Vc = - (Pcubo1_vector - Pcubo2_vector) · unitario(Pcubo1 - Pcubo2)
			// Vs = (Pcubo1_vector - Pcubo2_vector) · unitario(Pcubo1 - Pcubo2)
			// 
			// 
			// Ejes mas cercanos -> Pos es la mas cercana

			// EMPEZAR PONIENDO UN MINIMO DE DISTANCIA DE RECTIFICACION

			float epsilon = 0.01;

			//if(cubo2.static_flag)
			//if (direccion.x > 0 && (this->c->vel.x != 0 || cubo2.vel.x != 0)) {
			//	// Mov derecha
			//	// Lejano mio en el eje - Cercano del otro objeto en el eje
			//	distancia_penetracion.x = this->c->pos.x + this->c->diagonal.x - cubo2.pos.x + epsilon;
			//}
			//else if (this->c->vel.x != 0 || cubo2.vel.x != 0) {
			//	// Mov izquierda
			//	distancia_penetracion.x = this->c->pos.x - cubo2.pos.x + cubo2.diagonal.x + epsilon;
			//}

			//if (direccion.y > 0 && (this->c->vel.y != 0 || cubo2.vel.y != 0)) {
			//	// Mov arriba
			//	distancia_penetracion.y = this->c->pos.y + this->c->diagonal.y - cubo2.pos.y + epsilon;
			//}
			//else if (this->c->vel.y != 0 || cubo2.vel.y != 0) {
			//	// Mov abajo
			//	distancia_penetracion.y = this->c->pos.y - cubo2.pos.y + cubo2.diagonal.y + epsilon;
			//	std::cout << distancia_penetracion.y << std::endl;
			//}

			//if (direccion.z > 0 && (this->c->vel.z != 0 || cubo2.vel.z != 0)) {
			//	// Mov frente
			//	distancia_penetracion.z = this->c->pos.z + this->c->diagonal.z - cubo2.pos.z + epsilon;
			//}
			//else if (this->c->vel.z != 0 || cubo2.vel.z != 0) {
			//	// Mov fondo
			//	distancia_penetracion.z = this->c->pos.z - cubo2.pos.z + cubo2.diagonal.z + epsilon;
			//}

			this->cr_actual = CollisionReport(true, distancia_penetracion);

			glm::vec3 vel_aux = this->c->vel;
			this->c->vel = cubo2.vel;
			cubo2.vel = this->c->vel;

			return CollisionReport(true, distancia_penetracion);
		}

		this->cr_actual = CollisionReport(false, { 0,0,0 });

		return CollisionReport(false, { 0,0,0 });
	}

};





