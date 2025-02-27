
#include "figuras.h"

const float Linea2D::longitud()
{
	return vec2::moduloVec2(this->final - this->inicio);
}

bool Circulo::colision(Circulo c2)
{
	/*float distanciacentros = vec2::moduloVec2(c2.
	float radio1 = this->radio;
	float radio2 = c2.radio;
	if (distanciacentros < radio1 + radio2){
		return true;
	}
	else {
		return false;
	}*/

	return this->radio + c2.radio < 
		vec2::moduloVec2(this->centro - c2.centro);
}

//bool Circulo::colision(Rectangulo r)
//{
//	return r.colision(*this);
//
//}

bool Rectangulo::colision(Rectangulo r) {
	return this->pos.x > r.pos.x + r.diagonal.x && 
		this->pos.y > r.pos.y + r.diagonal.y;
}

bool Rectangulo::colision(Circulo c)
{
	Punto2D temp(pos);
	
	//El centro del circulo esta a la izq del origen del Rectangulo
	if (c.centro.x < this->pos.x) { 
		temp.x = this->pos.x; //temp son rectas con condiciones
	}
	//El centro del circulo esta a la derecha del recta(origen + ancho)
	else if (c.centro.x > this->pos.x + this->diagonal.x) {
		temp.x = this->pos.x + this->diagonal.x;
	}

	// El centro del circulo esta a la izq del origen del Rectangulo
	else if (c.centro.y < this->pos.y) {
		temp.y = this->pos.y; //temp son rectas con condiciones
	}
	//El centro del circulo esta a la derecha del recta(origen + alto)
	else if (c.centro.y > this->pos.y + this->diagonal.y) {
		temp.y = this->pos.y + this->diagonal.y;
	}
	else {
		return true;
	}


	float distX = c.centro.x - temp.x;
	float distY = c.centro.y - temp.y;


	if (abs(distX) < c.radio || abs(distY) < c.radio) {
		return true;
	}
	else {
		return false;
	}

}

bool Triangulo::colission(Punto2D p)
{
	//ax -by == 0 si el punto pertenece a una recta
	//dicha recta es la dada por el vector(a,b)

	vec2 ab = this->b - this->a;
	int c = -(ab.x * p.x + ab.y * p.y);

	return false;
}
