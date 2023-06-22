#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "tiny_obj_loader.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

namespace Models3D
{
	class ModelObject
	{
	public:
		ModelObject(string meshPath, string vertShadePath, string fragShadePath);	//Constructor

		GLuint getShaderProgram();

		void AssignColor(const vec3& color);	//Assigns the color of the model.
		void RenderModel(mat4 projectionMatrix);	//performs operations to render the model.
		void Clear();	//A function to clean up right before the program closes.
		
		// MODEL VALUES FOR LINEAR TRANSFORMATION AND CAMERA ALTERATION //
		float x_mod = 0;
		float y_mod = 0;

		float trans_x = 0, trans_y = -1, trans_z = -2;
		float scale_x = 2, scale_y = 2, scale_z = 2;
		float axis_x = 1, axis_y = 1, axis_z = 1;
		float theta = 0;
		
		// FUNCTIONS TO ALTER MODEL VALUES //
		void MoveRight();
		void MoveLeft();
		void MoveForward();
		void MoveBack();

		void LookLeft();
		void LookRight();
		void LookUp();
		void LookDown();
		
	private:
		void LoadShader(string vertShadePath, string fragShadePath);	// Loads in the fragment and vertex shader files.
		void LoadModel(string meshPath);	// Loads in the model to be used.
		void InitializeVert();	// Initializes the Vertex shader.
		void InitializeTex();	// Initializes the Fragment shader.

	private:
		GLuint VAO, VBO, EBO, VBO_UV, texture;
		tinyobj::attrib_t attributes;
		std::vector<GLuint> meshIndices;

		GLuint shaderProgram;
	};
}
#endif