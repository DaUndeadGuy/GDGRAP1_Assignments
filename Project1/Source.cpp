#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "Models.h"


void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod)
{

}

int main(void)
{
    GLFWwindow* window;
    float width = 600.0f;
    float height = 600.0f;
    float thetaX = 90.0f;
    float thetaY = 0.0f;
    float FOV = 60.0f;

    glm::mat4 identity_matrix = glm::mat4(1.0f);
    glm::vec3 translate = glm::vec3(0.0f, 0.0f, -5.0f);
    glm::vec3 scale = glm::vec3(15.0f, 15.0f, 15.0f);
    glm::vec3 rotateX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 rotateY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 rotateZ = glm::vec3(0.0f, 0.0f, 1.0f);


    glm::vec3 world_Up = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));    //World's Up

    glm::vec3 cameraPos_front = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraPos_side = glm::vec3(4.0f, 0.0f, 10.0f);
    glm::vec3 cameraPos_top = glm::vec3(-4.0f, 0.0f, 10.0f);

    glm::vec3 cameraCenter_front = glm::vec3(0.0f, 5.0f, 0.0f);               //camera's Target
    glm::vec3 cameraCenter_side = glm::vec3(4.0f, 1.0f, 0.0f);               //camera's Target
    glm::vec3 cameraCenter_top = glm::vec3(-4.0f, 0.0f, 0.0f);               //camera's Target


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow((int)width, (int)height, "Jose Romulo Guzman", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    Model::Models bunny("3D/bunny.obj", "Shaders/sample.vert", "Shaders/sample.frag");

    glfwSetKeyCallback(window, Key_Callback);

    glViewport(0,                      //min x
        0,                      //min y
        (GLsizei)width,         //max x
        (GLsizei)height);       //max y


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(FOV), (height / width), 0.1f, 100.0f);
        glm::mat4 transform_matrix_front = glm::translate(identity_matrix, translate);
        transform_matrix_front = glm::scale(transform_matrix_front, scale);
        transform_matrix_front = glm::rotate(transform_matrix_front, glm::radians(thetaX), rotateX);
        glm::mat4 view_front = glm::lookAt(cameraPos_front, cameraCenter_front, world_Up);


        bunny.DrawModel(transform_matrix_front, view_front, projection);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    bunny.CleanUp();

    glfwTerminate();
    return 0;
}