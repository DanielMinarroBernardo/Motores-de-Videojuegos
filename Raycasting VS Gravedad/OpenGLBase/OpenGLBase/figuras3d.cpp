
#include "figuras.h"


bool Cubo::colision(Cubo r) {
	return this->pos.x + this->diagonal.x > r.pos.x &&
		this->pos.x < r.pos.x + r.diagonal.x &&
		this->pos.y + this->diagonal.y > r.pos.y &&
		this->pos.y < r.pos.y + r.diagonal.y &&
		this->pos.z + this->diagonal.z > r.pos.z &&
		this->pos.z < r.pos.z + r.diagonal.z;
}




void Cubo::draw(Shader sh) {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// CON IBOs
		//unsigned int IBO  // index buffer object
		glGenBuffers(1, &this->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);

		unsigned int indices[] = {
			0,3,2,
			2,1,0,

			1,2,6,
			6,5,1,

			3,7,6,
			6,2,3,

			4,0,1,
			1,5,4,

			7,4,5,
			5,6,7,

			3,0,4,
			4,7,3
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * 2 * 6, indices, GL_DYNAMIC_DRAW);


		//unsigned int VBO; // vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		float vertices[] = {
				0.0f, 0.0f, 0.0f,								1.0f, 0.0f, 0.0f,												0,0, // 0
				0.0f, diagonal.y, 0.0f,							255.0f / 255.0f , 105.0 / 255.0f, 18.0f / 255.0f,				0,1, // 1
				diagonal.x, diagonal.y, 0.0f,					1.0f, 1.0f, 0.0f,												1,1, // 2
				diagonal.x, 0.0f, 0.0f,							0.0f, 1.0f, 0.0f,												1,0, // 3

				0.0f, 0.0f, diagonal.z,							0.0f, 1.0f, 1.0f,												1,1, // 4
				0.0f, diagonal.y, diagonal.z,					0.0f, 0.0f, 1.0f,												1,0, // 5
				diagonal.x, diagonal.y, diagonal.z,				1.0f, 0.0f, 1.0f,												0,0, // 6
				diagonal.x, 0.0f, diagonal.z,					0.5f, 0.5f, 0.5f,												0,1, // 7


				0.0f, 0.0f, 0.0f,								0.0f, 0.0f, 1.0f,												0,0, // 8
				0.0f, diagonal.y * 2, 0.0f,						0.0f, 0.0f, 1.0f,												0,1, // 9

				0.0f, 0.0f, 0.0f,								0.0f, 0.0f, 1.0f,												0,0, // 10
				diagonal.x * 2, 0.0f, 0.0f,						0.0f, 0.0f, 1.0f,												0,1, // 11

				0.0f, 0.0f, 0.0f,								0.0f, 0.0f, 1.0f,												0,0, // 12
				0.0f, 0.0f, diagonal.z * 2,						0.0f, 0.0f, 1.0f,												0,1, // 13
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 14, vertices, GL_DYNAMIC_DRAW);
		// GL_STREAM_DRAW -> meto los datos 1 vez, pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 vez, y se utilizan mucho, pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 1º 0, porque hemos dicho que (position = 0)
		// 2º 2, porque cada vertice esta en 2D, 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertice -> stride
		// 6º offset 

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {

		glBindVertexArray(this->VAO);

		// Declarar posicion, rotacion y escala en el render
		// La pos, rot, scl las conoces antes
		glm::mat4 transf_rect = glm::mat4(1.0f);
		transf_rect = glm::translate(transf_rect, glm::vec3(pos.x, pos.y, pos.z));
		transf_rect = glm::scale(transf_rect, glm::vec3(scl, scl, scl));
		transf_rect = glm::rotate(transf_rect, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));

		sh.setModelMatrix(transf_rect);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glDrawArrays(GL_LINES, 8, 6);

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}


//void Rectangulo::transform(glm::mat4 transformacion) {
//	this->transf_interna = transformacion * this->transf_interna;
//}
//

void Cubo::move(double tiempo_trasncurrido) {

	//Manera ilusa (suponer suelo totalmente plano e infinito)

	//// Velocidad
	//pos.x = pos.x + vel.x * tiempo_trasncurrido;
	//pos.z = pos.z + vel.z * tiempo_trasncurrido;

	//if (pos.y >= -5) {
	//	pos.y = pos.y + vel.y * tiempo_trasncurrido;
	//}
	//else {
	//	pos.y = -5;
	//	vel.y = 0;
	//}
	//// Aceleracion
	//vel.y = vel.y - 9.8f / 4 * tiempo_trasncurrido;



	// Manera por colisiones

	// Velocidad
	pos.x = pos.x + vel.x * tiempo_trasncurrido;
	pos.y = pos.y + vel.y * tiempo_trasncurrido;
	pos.z = pos.z + vel.z * tiempo_trasncurrido;
	
	// Aceleracion
	vel.y = vel.y - 9.8f / 4 * tiempo_trasncurrido;

}




bool Ray::colision(glm::vec3 Punto) {
	if (Punto == this->pos) {
		return true;
	}
	
	glm::vec3 dir_punto = glm::normalize(Punto - this->pos);

	//Considerar cierto error como adecuado
	float epsilon = 0.005f;
	float result = glm::dot(this->direccion, dir_punto);
	if (result >= 1.0f - epsilon &&
		result <= 1.0f + epsilon) {
		return true;
	}
	else {
		return false;
	}

}


float Raycast::raycast(Cubo cubo, Ray ray) {
	// Metodo iluso, solo me muevo en x, en y, o en z
	if (ray.direccion.y != 0.0) {
		// Punto mas cercano
		float distancia = fminf(cubo.pos.y - ray.pos.y, cubo.pos.y + cubo.diagonal.y - ray.pos.y);

		// pos_final -> si me choco sera pos del cubo con el que me choco
		// pos_final = pos_inicial + vel * tiempo
		// vel * tiempo = pos_final - pos_inicial = distancia
		// tiempo = distancia / vel

		return distancia / ray.magnitud;
	}
}