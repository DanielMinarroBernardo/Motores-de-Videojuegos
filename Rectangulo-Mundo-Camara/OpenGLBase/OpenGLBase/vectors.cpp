
#include "vectors.h"

vec2::vec2() {
	this->x = 0;
	this->y = 0;
}

vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

vec2& vec2::operator+ (vec2 otro) {
	vec2 resultado(0, 0);
	resultado.x = this->x + otro.x;
	resultado.y = this->y + otro.y;
	return resultado;
}

vec2& vec2::operator- (vec2 otro) {
	vec2 resultado(0, 0);
	resultado.x = this->x - otro.x;
	resultado.y = this->y - otro.y;
	return resultado;
}

vec2& vec2::suma (vec2 otro) {
	return *this + otro;
}

float& vec2::operator[] (int indice) {
	if (indice == 0) {
		return this->x;
	}
	else if (indice == 1) {
		return this->y;
	}
	else {
		// lanzar error
	}
}

const bool& vec2::operator== (vec2 otro) {
	return this->x == otro.x &&
		this->y == otro.y;
}




const float& vec2::modulo() {
	return sqrt(this->x * this->x + 
		this->y * this->y);
}

const float& vec2::moduloVec2(vec2 otro) {
	return sqrt(otro.x * otro.x +
		otro.y * otro.y);
}

float vec2::prodEscalar(vec2 otro) {
	return this->x * otro.x +
		this->y * otro.y;
}

const double& vec2::angulo(vec2 otro) {
	return acos(this->prodEscalar(otro) / 
		( this->modulo() * otro.modulo() ) 
	);
}

const double& vec2::anguloX() {
	vec2 otro(1,0);
	return acos(this->prodEscalar(otro) /
		(this->modulo() * otro.modulo())
	);
}




vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3& vec3::operator+ (vec3 otro) {
	vec3 resultado(0, 0, 0);
	resultado.x = this->x + otro.x;
	resultado.y = this->y + otro.y;
	resultado.z = this->z + otro.z;
	return resultado;
}

vec3& vec3::operator-(vec3 otro)
{
	vec3 resultado(0, 0, 0);
	resultado.x = this->x - otro.x;
	resultado.y = this->y - otro.y;
	resultado.z = this->z - otro.z;
	return resultado;
}
 
vec3& vec3::operator=(vec3 otro)
{
	vec3 resultado(0, 0, 0);
	resultado.x = otro.x;
	resultado.y = otro.y;
	resultado.z = otro.z;
	return resultado;
}

float& vec3::operator[] (int indice) {
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
		// lanzar error
	}
}

float vec3::prodEscalar(vec3 otro) {
	return this->x * otro.x +
		this->y * otro.y +
		this->z * otro.z;
}

vec3 vec3::prodVectorial(vec3 otro) {
	vec3 resultado(0, 0, 0);
	resultado.x = this->y * otro.z - this->z * otro.y;
	resultado.y = this->x * otro.z - this->z * otro.x;
	resultado.z = this->x * otro.y - this->y * otro.x;
	return resultado;
}

glm::mat4 vec3::lookAt(vec3 cam_pos, vec3 obj_pos, vec3 up)
{
	glm::vec3 cam_pos_glm(cam_pos.x, cam_pos.y, cam_pos.z);
	glm::vec3 obj_pos_glm(obj_pos.x, obj_pos.y, obj_pos.z);
	glm::vec3 up_glm(up.x, up.y, up.z);

	glm::vec3 vector_direccion = glm::normalize(cam_pos_glm - obj_pos_glm);
	glm::vec3 vector_derecha = glm::normalize(glm::cross(up_glm, vector_direccion));
	glm::vec3 vector_arriba = glm::cross(vector_direccion, vector_derecha);

	glm::mat4 result(
		glm::vec4(vector_derecha, 0),
		glm::vec4(vector_arriba, 0),
		glm::vec4(vector_direccion, 0),
		glm::vec4(0,0,0, 1)
	);
	glm::mat4 translacion(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-cam_pos_glm.x, -cam_pos_glm.y, -cam_pos_glm.z, 1
	);
	return result * translacion;
}


