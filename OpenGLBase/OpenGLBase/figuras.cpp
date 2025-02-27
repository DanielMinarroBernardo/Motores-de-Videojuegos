
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

float* Triangulo::toArray()
{
	float myarray[] = {this->a.x,this->a.y,this->b.x,this->b.y,this->c.x,this->c.y};
	
	return myarray;
}

void Triangulo::draw()
{
	if (this->VBO == 0) {
		//unsigned int VAO; //Vertex array Object

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//unsigned int VBO; //Vertex Buffer Object

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, this->toArray(), GL_DYNAMIC_DRAW);
		// GL_STREAM_DRAW-> meto los datos 1 vez , pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 ve y se utilizan mucho,pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		// 1º 0, porque hemos dicho que (posicion = 0)
		// 2º 2, porque cada vertice esta en 2D, en 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertice -> stride
		// 6º puntero
		glEnableVertexAttribArray(0);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, this->toArray(), GL_DYNAMIC_DRAW);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); 
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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
