
#include "figuras.h"
#include "vector"


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

void Circulo::draw(float num_segmentos) {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);


		//unsigned int VBO; // vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		float theta = 3.1415926 * 2 / num_segmentos;
		float factor_tang = tanf(theta);
		float factor_rad = cosf(theta);

		float x = radio;
		float y = 0;
		std::vector<float> vertices;

		for (int i = 0; i < num_segmentos; i++) {

			vertices.push_back(x + centro.x);
			vertices.push_back(y + centro.y);

			// Calculo el siguiente cambiando x e y
			float tx = -y;
			float ty = x;

			x += tx * factor_tang;
			y += ty * factor_tang;

			x *= factor_rad;
			y *= factor_rad;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
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


		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {

		glBindVertexArray(this->VAO);

		if (this->dirty_flag) {

			float theta = 3.1415926 * 2 / num_segmentos;
			float factor_tang = tanf(theta);
			float factor_rad = cosf(theta);

			float x = radio;
			float y = 0;

			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			std::vector<float> vertices;

			for (int i = 0; i < num_segmentos; i++) {

				vertices.push_back(x + centro.x);
				vertices.push_back(y + centro.y);

				// Calculo el siguiente cambiando x e y
				float tx = -y;
				float ty = x;

				x += tx * factor_tang;
				y += ty * factor_tang;

				x *= factor_rad;
				y *= factor_rad;
			}

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		glDrawArrays(GL_LINE_LOOP, 0, num_segmentos);
		//glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


}






bool Rectangulo::colision(Rectangulo r) {
	return 0.0f + this->diagonal.x > r.pos.x &&
		0.0f < r.pos.x + r.diagonal.x &&
		0.0f + this->diagonal.y > r.pos.y &&
		0.0f < r.pos.y + r.diagonal.y;
}

bool Rectangulo::colision(Circulo c) {

	Punto2D temp(pos);

	int colocacion_h = 0;
	int colocacion_v = 0;

	// El centro del circulo esta la izq del origen del rect
	if (c.centro.x <= 0.0f) {
		temp.x = 0.0f; // temp son rectas
		colocacion_h = 1;
	}
	// El centro del circulo esta la dcha del rect (origen + ancho)
	else if (c.centro.x >= 0.0f + this->diagonal.x) {
		temp.x = 0.0f + this->diagonal.x;
		colocacion_h = 2;
	}

	// El centro del circulo esta la arriba del origen del rect
	if (c.centro.y <= 0.0f) {
		temp.y = 0.0f; // temp son rectas
		colocacion_v = 1;
	}
	// El centro del circulo esta la debajo del rect (origen + alto)
	else if (c.centro.y >= 0.0f + this->diagonal.y) {
		temp.y = 0.0f + this->diagonal.y;
		colocacion_v = 2;
	}


	float distX = c.centro.x - temp.x;
	float distY = c.centro.y - temp.y;

	if (colocacion_h == 0 && colocacion_v == 0) { // Esta dentro 
		return true;
	}
	else if (colocacion_h > 0 && colocacion_v == 0 && abs(distX) <= c.radio) { // En Horizontal
		
		if (colocacion_h == 1) {
			this->vel.x = 300.0f;
		}
		else {
			this->vel.x = -300.0f;
		}
		return true;
	}
	else if (colocacion_h == 0 && colocacion_v > 0 && abs(distY) <= c.radio) { // En Vertical
		if (colocacion_v == 1) {
			this->vel.y = 300.0f;
		}
		else {
			this->vel.y = -300.0f;
		}
		return true;
	}
	else if (colocacion_h > 0 && colocacion_v > 0 && 
		distX * distX + distY *distY  <= c.radio * c.radio) {
		return true;
	}
	else {
		return false;
	}
}


void Rectangulo::draw(Shader sh) {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// CON IBOs
		//unsigned int IBO  // index buffer object
		glGenBuffers(1, &this->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);

		unsigned int indices[] = {
			0, 1, 2, // Primer triangulo
			2, 3, 0  // Segundo triangulo
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_DYNAMIC_DRAW);



		//unsigned int VBO; // vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);


		//   SIN IBOs
		//float vertices[] = {
		//		0.0f, 0.0f, // 0
		//		0.0f, 0.0f + this->diagonal.y, // 1
		//		0.0f + this->diagonal.x, 0.0f + this->diagonal.y, // 2

		//		0.0f + this->diagonal.x, 0.0f + this->diagonal.y, // 2
		//		0.0f + this->diagonal.x, 0.0f, // 3
		//		0.0f, 0.0f, // 0
		//};
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_DYNAMIC_DRAW);



		float vertices[] = {
				0.0f, 0.0f,													1.0f, 0.0f, 0.0f, // 0
				0.0f, 0.0f + diagonal.y,								1.0f, 0.0f, 0.0f, // 1
				0.0f + diagonal.x, 0.0f + diagonal.y,			1.0f, 0.0f, 0.0f, // 2
				0.0f + diagonal.x, 0.0f,								1.0f, 0.0f, 0.0f, // 3

				0.0f, 0.0f,													0.0f, 0.0f, 1.0f, // 4
				0.0f, 0.0f + diagonal.y * 2,							0.0f, 0.0f, 1.0f, // 5

				0.0f, 0.0f,													0.0f, 0.0f, 1.0f, // 6
				0.0f + diagonal.x * 2, 0.0f,							0.0f, 0.0f, 1.0f, // 7
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 40, vertices, GL_DYNAMIC_DRAW);
		// GL_STREAM_DRAW -> meto los datos 1 vez, pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 vez, y se utilizan mucho, pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces



		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 1º 0, porque hemos dicho que (position = 0)
		// 2º 2, porque cada vertice esta en 2D, 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertice -> stride
		// 6º offset 

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);


		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {

		glBindVertexArray(this->VAO);

		if (this->dirty_flag) {

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
			unsigned int indices[] = {
				0, 1, 2, // Primer triangulo
				2, 3, 0  // Segundo triangulo
			};
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);


			float vertices[] = {
				0.0f, 0.0f,													1.0f, 0.0f, 0.0f, // 0
				0.0f, 0.0f + diagonal.y,								1.0f, 0.0f, 0.0f, // 1
				0.0f + diagonal.x, 0.0f + diagonal.y,			1.0f, 0.0f, 0.0f, // 2
				0.0f + diagonal.x, 0.0f,								1.0f, 0.0f, 0.0f, // 3

				0.0f, 0.0f,													0.0f, 0.0f, 1.0f, // 4
				0.0f, 0.0f + diagonal.y * 2,							0.0f, 0.0f, 1.0f, // 5

				0.0f, 0.0f,													0.0f, 0.0f, 1.0f, // 6
				0.0f + diagonal.x * 2, 0.0f,							0.0f, 0.0f, 1.0f, // 7
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}



		//Declarar posicion, rotacion y scala en el render

		glm::mat4 transf_rect = glm::mat4(1.0f);
		transf_rect = glm::translate(transf_rect, glm::vec3(pos.x, pos.y, 0.0f));
		transf_rect = glm::scale(transf_rect, glm::vec3(scl,scl,scl));
		transf_rect = glm::rotate(transf_rect,glm::radians(rot), glm::vec3(1.0f,0.0f,1.0f));
		sh.setModelMatrix(transf_rect);


			
	
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDrawArrays(GL_LINES, 4, 4);

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}


void Rectangulo::transform(glm::mat4 transformacion) {
	this->transf_interna = transformacion * this->transf_interna;
}

void Rectangulo::move(double tiempo_trasncurrido) {
	float v = 100.0f;

	//std::cout << "Velocidad: " << v << "\n";
	//std::cout << "Tiempo: " << tiempo_trasncurrido << "\n";
	//std::cout << "Pos x0: " << pos.x << "\n";

	pos.x = pos.x + vel.x * tiempo_trasncurrido;
	pos.y = pos.y + vel.y * tiempo_trasncurrido;

	//std::cout << "Pos x final: " << pos.x << "\n";
}








void RectanguloRotado::transform(glm::mat4 transformacion) {
	this->transf_interna = transformacion * this->transf_interna;
}

void RectanguloRotado::draw() {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// CON IBOs
		//unsigned int IBO  // index buffer object
		glGenBuffers(1, &this->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);

		unsigned int indices[] = {
			0, 1, 2, // Primer triangulo
			2, 3, 0  // Segundo triangulo
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_DYNAMIC_DRAW);



		//unsigned int VBO; // vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);



		//glm::vec4 diagonal_transf(this->diagonal.x, this->diagonal.y, 0.0f, 1.0f);

		//diagonal_transf = this->transf_interna * diagonal_transf;

		std::cout << "Vertices" << std::endl;


		float vertices[] = {
				this->centro.x - (this->semiLongitudH - this->semiLongitudV).x, this->centro.y - (this->semiLongitudH - this->semiLongitudV).y, // 0
				this->centro.x - (this->semiLongitudH + this->semiLongitudV).x, this->centro.x - (this->semiLongitudH + this->semiLongitudV).y, // 1
				this->centro.x + (this->semiLongitudH - this->semiLongitudV).x, this->centro.y + (this->semiLongitudH - this->semiLongitudV).y, // 2
				this->centro.x + (this->semiLongitudH + this->semiLongitudV).x, this->centro.y + (this->semiLongitudH + this->semiLongitudV).y, // 3
		};

		for (int i = 0; i < 8; i += 2) {
			std::cout << vertices[i] << ", " << vertices [i + 1] << std::endl;
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_DYNAMIC_DRAW);
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


		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {

		glBindVertexArray(this->VAO);

		if (this->dirty_flag) {

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
			unsigned int indices[] = {
				0, 1, 2, // Primer triangulo
				2, 3, 0  // Segundo triangulo
			};
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			float vertices[] = {
				this->centro.x - (this->semiLongitudH - this->semiLongitudV).x, 
					this->centro.y - (this->semiLongitudH - this->semiLongitudV).y, // 0
				this->centro.x - (this->semiLongitudH + this->semiLongitudV).x, 
					this->centro.x - (this->semiLongitudH + this->semiLongitudV).y, // 1
				this->centro.x + (this->semiLongitudH - this->semiLongitudV).x, 
					this->centro.y + (this->semiLongitudH - this->semiLongitudV).y, // 2
				this->centro.x + (this->semiLongitudH + this->semiLongitudV).x, 
					this->centro.y + (this->semiLongitudH + this->semiLongitudV).y, // 3
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		//glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void Triangulo::draw() {

	if (this->VBO == 0) {
		//unsigned int VAO; // vertex array object
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//unsigned int VBO; // vertex buffer object
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		float vertices[] = {
			this->a.x, this->a.y,
			this->b.x, this->b.y,
			this->c.x, this->c.y
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW);
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

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {
		glBindVertexArray(this->VAO);

		if (this->dirty_flag) {
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			float vertices[] = {
				this->a.x, this->a.y,
				this->b.x, this->b.y,
				this->c.x, this->c.y
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		glDrawArrays(GL_LINE_LOOP, 0, 3);

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}