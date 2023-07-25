#pragma once
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "tiny_obj_loader.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Light
{
	class baseLight {
	public:
		baseLight();

		glm::vec3 lightColor;
		float ambientStr;
		glm::vec3 ambientColor;
		float specStr;
		float specPhong;

		void AssignLightColor(GLuint shaderProgram);
		void AssignAmbientStr(GLuint shaderProgram);
		void AssignAmbientColor(GLuint shaderProgram);
		void AssignSpecStr(GLuint shaderProgram);
		void AssignSpecPhong(GLuint shaderProgram);

		void InitBaseLight(glm::vec3, float, float, float);
	};

	class directLight : public baseLight {

	public:
		directLight() : baseLight() {};

		glm::vec3 lightDirection;
		glm::vec3 DirectionalPos;

		void InsertDirectionalPos(glm::vec3);
		void AssignDirectionalPos(GLuint);
		void IntensityUp();
		void IntensityDown();
	};

	class pointLight : public baseLight {

	public:
		pointLight() : baseLight() {};

		glm::vec3 lightPos;
		void InsertLightPos(glm::vec3);
		void AssignLightPos(GLuint shaderProgram);

		void MoveRight();
		void MoveLeft();
		void MoveForward();
		void MoveBack();

		void MoveUp();
		void MoveDown();
		void IntensityUp();
		void IntensityDown();

		void ChangeColor(glm::vec3);
	};
}


