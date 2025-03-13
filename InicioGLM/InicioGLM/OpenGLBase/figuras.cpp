
#include "figuras.h"


const float& Linea2D::longitud() {
	return vec2::moduloVec2(this->final - this->inicio);
}


bool Circulo::colision(Circulo c) {
	return this->radio + c.radio <
		vec2::moduloVec2(
			this->centro - c.centro);
}
/*
bool Circulo::colision(Rectangulo r) {
	return r.colision(*this);
} */


bool Rectangulo::colision(Rectangulo r) {
	return this->pos.x >
		r.pos.x + r.diagonal.x &&
		this->pos.y >
		r.pos.y + r.diagonal.y;
}

bool Rectangulo::colision(Circulo c) {

	Punto2D temp(pos);

	// El centro del circulo esta la izq del origen del rect
	if (c.centro.x < this->pos.x) {
		temp.x = this->pos.x; // temp son rectas
	}
	// El centro del circulo esta la dcha del rect (origen + ancho)
	else if (c.centro.x > this->pos.x + this->diagonal.x) {
		temp.x = this->pos.x + this->diagonal.x;
	}

	// El centro del circulo esta la arriba del origen del rect
	else if (c.centro.y < this->pos.y) {
		temp.y = this->pos.y; // temp son rectas
	}
	// El centro del circulo esta la debajo del rect (origen + alto)
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

float* Rectangulo::toArray() {
	float myArray[] = {
		this->pos.x, this->pos.y,
		this->pos.x, this->pos.y + this->diagonal.y,
		this->pos.x + this->diagonal.x, this->pos.y + this->diagonal.y,
		this->pos.x + this->diagonal.x, this->pos.y
	};
	return myArray;
}
void Rectangulo::draw() {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//unsigned int VBO; // vertex buffer object
		//glGenBuffers(1, &this->VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, this->toArray(), GL_DYNAMIC_DRAW);
		// GL_STREAM_DRAW -> meto los datos 1 vez, pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 vez, y se utilizan mucho, pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// 1º 0, porque hemos dicho que (position = 0)
		// 2º 2, porque cada vertice esta en 2D, 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertices -> stride
		// 6º puntero 
		glEnableVertexAttribArray(0);
	}
	else {
		if (dirty_flaf == true) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, this->toArray(), GL_DYNAMIC_DRAW);
			glBindVertexArray(this->VAO);

		}
		
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glDrawArrays(GL_LINE_LOOP, 0, 4);
		this->dirty_flaf = false;
	}
}


bool Triangulo::colision(Punto2D p) {
	// ay - bx == 0 si el punto pertenece a una recta
	// dicha recta es la dada por el vector (a,b)

	vec2 ab = this->b - this->a;
	int c = -(ab.x * p.x + ab.y * p.y);

	std::cout << c << std::endl;

	return false;

}

float* Triangulo::toArray() {
	float myArray[] = {
		this->a.x, this->a.y,
		this->b.x, this->b.y,
		this->c.x, this->c.y
	};
	return myArray;
}

void Triangulo::draw() {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		unsigned int VBO; // vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		//ArrayGlobal::push(this->toArray(), 3);


		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, /*ArrayGlobal::arrayGlobal*/this->toArray(), GL_DYNAMIC_DRAW);
		// GL_STREAM_DRAW -> meto los datos 1 vez, pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 vez, y se utilizan mucho, pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// 1º 0, porque hemos dicho que (position = 0)
		// 2º 2, porque cada vertice esta en 2D, 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertices -> stride
		// 6º puntero 
		glEnableVertexAttribArray(0);
	}
	else {
		if (dirty_flaf == true) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, this->toArray(), GL_DYNAMIC_DRAW);
			glBindVertexArray(this->VAO);

		}

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		this->dirty_flaf = false;
	}
}

//void ArrayGlobal::push(float array[], int num_vertex)
//{
//	for (int i = libre; i < libre + num_vertex * 2; i++) {
//		ArrayGlobal::arrayGlobal[i] = array[i - libre];
//	}
//	libre = libre + num_vertex * 2;
//}
