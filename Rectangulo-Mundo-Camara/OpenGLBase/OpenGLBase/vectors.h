#pragma once

#include <iostream>
#include <cmath>

struct vec2 {
	float x;
	float y;

	vec2();
	vec2(float x, float y);
	vec2& operator+ (vec2 otro);
	vec2& operator- (vec2 otro);
	float& operator[] (int i);

	const bool& operator== (vec2 otro);

	vec2& suma(vec2 otro);
	const float& modulo();
	float prodEscalar(vec2 otro);
	const double& angulo(vec2 otro);
	const double& anguloX();

	static const float& moduloVec2(vec2 otro);
};


struct vec3 {
	float x;
	float y;
	float z;

	vec3(float x, float y, float z);
	vec3& operator+ (vec3 otro);
	vec3& operator- (vec3 otro);
	vec3& operator= (vec3 otro);
	float& operator[] (int i);
	float prodEscalar (vec3 otro);
	vec3 prodVectorial (vec3 otro);
};




