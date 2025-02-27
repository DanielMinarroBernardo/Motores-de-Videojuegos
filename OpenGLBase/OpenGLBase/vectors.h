#pragma once
#include <iostream>
#include <cmath>

struct vec2 {

	float x;
	float y;

	vec2();
	vec2(float x, float y);
	vec2& operator+(vec2 otro);
	vec2& operator-(vec2 otro);
	const bool& operator==(vec2 otro);
	float& operator[] (int i);
	float pordEscalar(vec2 otro);
	const float& modulo();
	static const float& moduloVec2(const vec2 otro);
	const double& angulo(vec2 otro);
	const double& anguloX();
	const vec2& unitario();
};


struct vec3 {

	float x;
	float y;
	float z;

	vec3(float x, float y, float z);
	vec3& operator+(vec3 otro);
	float& operator[] (int i);
	float pordEscalar(vec3 otro);
	vec3 pordVectorial(vec3 otro);
};
