#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

#include "tiny_obj_loader.h"

#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

namespace Model
{

	class Models
	{
	public:
		Models(std::string sMeshPath, std::string sVertPath, std::string sFragPath);

		GLuint getShaderProgram();

		void SetColor(const glm::vec3& color);
		void DrawModel(glm::mat4 transform_matrix, glm::mat4 projection_matrix, glm::mat4 view_matrix, glm::vec3 cameraPos);
		void CleanUp();

	private:
		void LoadShaders(std::string sVertPath, std::string sFragPath);
		void LoadModel(std::string sMeshPath);
		void VertexInit();
		void TexInit();

	private:
		GLuint VAO, VBO, EBO, VBO_UV, texture, norm_tex;
		tinyobj::attrib_t attributes;
		std::vector<GLuint> mesh_indices;
		std::vector<GLfloat> fullVertexData;
		tinyobj::index_t vData;

		GLuint shaderProgram;


	};
}

#endif