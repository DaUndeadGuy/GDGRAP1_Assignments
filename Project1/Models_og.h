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
		void DrawModel(glm::mat4 projection_matrix);
		void CleanUp();

		void MoveRight();
		void MoveLeft();
		void MoveForward();
		void MoveBack();
		void LookLeft();
		void LookRight();
		void LookUp();
		void LookDown();

	private:
		void LoadShaders(std::string sVertPath, std::string sFragPath);
		void LoadModel(std::string sMeshPath);
		void VertexInit();
		void TexInit();

	private:
		GLuint VAO, VBO, EBO, VBO_UV, texture;
		tinyobj::attrib_t attributes;
		std::vector<GLuint> mesh_indices;

		GLuint shaderProgram;

		float trans_x;
		float trans_y;
		float trans_z;
		float x_mod;
		float y_mod;
		float scale_x;
		float scale_y;
		float scale_z;

		float theta;
		float axis_x;
		float axis_y;
		float axis_z;
	};
}

#endif