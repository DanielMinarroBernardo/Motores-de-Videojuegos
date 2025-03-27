#include "figuras.h"
#include "figuras3d.h"


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
			3,0,4,
			4,7,3,
			7,4,5,
			5,6,7
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3*2*6, indices, GL_DYNAMIC_DRAW);



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
				0.0, 0.0, 0.0,								1.0, 0.0, 0.0,
				diagonal.x, 0.0, 0.0,						1.0, 0.3, 0.1,
				diagonal.x, diagonal.y, 0.0,				1.0, 0.5, 0.4,
				0.0,diagonal.y, 0.0,						0.0, 1.0, 0.0,
					
				0.0, 0.0, diagonal.z,						0.0, 1.0, 0.0,
				diagonal.x, 0.0, diagonal.z,				0.0, 0.0, 1.0,
				diagonal.x, diagonal.y, diagonal.z,			1.0, 0.0, 0.0,
				0.0, diagonal.y, diagonal.z,				0.0, 1.0, 0.5,

				0.0, 0.0, 0.0,								0.0, 0.5, 1.0,
				diagonal.x *2, 0.0, 0.0,					0.5, 0.0, 1.0,
							
				0.0, 0.0, 0.0,								0.5, 1.0, 0.0,
				0.0, diagonal.y *2, 0.0,					0.0, 1.0, 1.0,
				
				0.0, 0.0, 0.0,								0.0, 1.0, 0.3,
				0.0, 0.0, diagonal.z * 2,					0.0, 1.0, 1.0,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6*14, vertices, GL_DYNAMIC_DRAW);
		// GL_STREAM_DRAW -> meto los datos 1 vez, pero se utilizan poco
		// GL_STATIC_DRAW -> meto los datos 1 vez, y se utilizan mucho, pero no se mueven mucho
		// GL_DYNAMIC_DRAW -> meto los datos muchas veces



		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 1º 0, porque hemos dicho que (position = 0)
		// 2º 2, porque cada vertice esta en 2D, 2 parametros
		// 3º tipo de dato
		// 4º no hace falta normalizar
		// 5º tamaño de cada vertice -> stride
		// 6º offset 

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else {

		glBindVertexArray(this->VAO);




		//Declarar posicion, rotacion y scala en el render

		glm::mat4 transf_rect = glm::mat4(1.0f);
		transf_rect = glm::translate(transf_rect, glm::vec3(pos.x, pos.y, -30.0f));
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


void Cubo::transform(glm::mat4 transformacion) {
	this->transf_interna = transformacion * this->transf_interna;
}

void Cubo::move(double tiempo_trasncurrido) {
	float v = 100.0f;

	//std::cout << "Velocidad: " << v << "\n";
	//std::cout << "Tiempo: " << tiempo_trasncurrido << "\n";
	//std::cout << "Pos x0: " << pos.x << "\n";

	pos.x = pos.x + vel.x * tiempo_trasncurrido;
	pos.y = pos.y + vel.y * tiempo_trasncurrido;

	//std::cout << "Pos x final: " << pos.x << "\n";
}

