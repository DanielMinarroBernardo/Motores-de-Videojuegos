#include "vectors.h"


/// VECTOR 2

vec2::vec2()
{
	this->x = 0;
	this->y = 0;
}

vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

vec2 & vec2:: operator+(vec2 otro) {
	vec2 resultado(0, 0);
	resultado.x = this->x + otro.x;
	resultado.y = this->y + otro.y;
	return resultado;
}

vec2& vec2::operator-(vec2 otro)
{
	vec2 resultado(0, 0);
	resultado.x = this->x - otro.x;
	resultado.y = this->y - otro.y;
	return resultado;
}

const bool& vec2::operator==(vec2 otro) {
	return this->x == otro.x && this->y == otro.y;
}

float& vec2::operator[](int indice)
{
	if (indice == 0) {
		return this->x;
	}
	if (indice == 1) {
		return this->y;
	}
	else {
		//lanzar error
	}
}


float vec2::pordEscalar(vec2 otro)
{
	float escalar;
	escalar = this->x * otro.x + this->y * otro.y;
	return escalar;
}

const float& vec2::modulo()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

const float& vec2::moduloVec2(vec2 otro)
{
	return sqrt(otro.x * otro.x + otro.y * otro.y);

}

const double& vec2::angulo(vec2 otro)
{
	return acos(this->pordEscalar(otro) / this->modulo() * otro.modulo());
}
const double& vec2::anguloX()
{
	vec2 otro(1,0);
	return acos(this->pordEscalar(otro) / this->modulo() * otro.modulo());
}

const vec2& vec2::unitario()
{
	return vec2(this->x / this->modulo(), this->y / this->modulo());
}



/// VECTOR 3

vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3& vec3:: operator+(vec3 otro) {
	vec3 resultado(0, 0, 0);
	resultado.x = this->x + otro.x;
	resultado.y = this->y + otro.y;
	resultado.z = this->z + otro.z;
	return resultado;
}

float& vec3::operator[](int indice)
{
	if (indice == 0) {
		return this->x;
	}
	else if (indice == 1) {
		return this->y;
	}
	else if (indice == 2) {
		return this->z;
	}
	else {
		//lanzar error
	}
}

float vec3::pordEscalar(vec3 otro)
{
	float escalar;
	escalar = this->x * otro.x + this->y * otro.y + this->z * otro.z;
	return escalar;
}

vec3 vec3::pordVectorial(vec3 otro)
{

	return vec3(0,0,0);
}
