#pragma once

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

namespace Camera
{
	class baseCamera {
	public:

		baseCamera();

		glm::vec3 cameraPos = glm::vec3(0, 0, 10.f);
		glm::mat4 cameraPosMatrix = translate(
			glm::mat4(1.0f),
			cameraPos * -1.0f
		);

		glm::mat4 viewMatrix;

		float x_mod = 0;
		float y_mod = 0;

		void InitCameraPos(glm::vec3);
		void InitializeViewMatrix(GLuint shaderProgram);
		void AssignView(GLuint shaderProgram);
		void AssignCameraPos(GLuint shaderProgram);
		glm::mat4 GetViewMatrix();
		glm::vec3 GetCameraPos();
	};

	class orthoCamera : public baseCamera
	{
	public:
		orthoCamera() : baseCamera() {};

		glm::mat4 orthographicMatrix{};

		void InitOrthoCam();
		void AssignOrthoCam(glm::mat4 orthographicMatrix, GLuint shaderProgram);
		glm::mat4 GetOrthoMatrix();
		//void AssignOrthographicLocation(mat4 orthographicMatrix, GLuint shaderProgram);
	};

	class persCamera : public baseCamera
	{
	public:
		persCamera() : baseCamera() {};

		glm::mat4 perspectiveCamera;

		void InitPersCam(float windowHeight, float windowWidth);
		void AssignPersCam(glm::mat4 projectionMatrix, GLuint shaderProgram);
		glm::mat4 GetPersMatrix();
		//void AssignPerspectiveLocation(mat4 projectionMatrix, GLuint shaderProgram);
	};
}
