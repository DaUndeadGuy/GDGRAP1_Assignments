#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "CameraClass.h"
#include "Models.h"

float thetaX = 90.0f;
float thetaY = 0.0f;
float FOV = 60.0f;

glm::vec3 translate = glm::vec3(0.0f, 0.0f, -5.0f);
glm::vec3 scale = glm::vec3(2.0f, 2.0f, 2.0f);
glm::vec3 rotateX = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 rotateY = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;

bool persEnabled = false;
bool othroEnabled = false;


void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    //Movement
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        translate.x += 0.1f;
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        translate.x -= 0.1f;
    }
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        translate.y += 0.1f;
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        translate.y -= 0.1f;
    }

    //Rotate Y
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        thetaX -= 0.1f;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        thetaX += 0.1f;
    }

    //Rotate X
    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        thetaY -= 0.1f;
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        thetaY += 0.1f;
    }

    //Zoom
    if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        FOV -= 1.0f;
    }
    if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        FOV += 1.0f;
    }

    //Scale
    if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        scale.x += 0.05f;
        scale.y += 0.05f;
        scale.z += 0.05f;
    }
    if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        scale.x -= 0.05f;
        scale.y -= 0.05f;
        scale.z -= 0.05f;
    }

    if (key == GLFW_KEY_1 && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        persEnabled = true;
        othroEnabled = false;
    }
    if (key == GLFW_KEY_2 && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        othroEnabled = true;
        persEnabled = false;
    }

}



void Mouse_Callback(GLFWwindow* window, double xPos, double yPos)
{

}

int main(void)
{
    GLFWwindow* window;
    float width = 600.0f;
    float height = 600.0f;

    //glm::mat4 projection = glm::ortho(-2.f, 2.f, -2.f, 2.f, -1.f, 1.f);



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


    Model::Models object("3D/plane.obj", "Shaders/sample.vert", "Shaders/sample.frag");

    glfwSetKeyCallback(window, Key_Callback);

    glViewport(0,                      //min x
        0,                      //min y
        (GLsizei)width,         //max x
        (GLsizei)height);       //max y


    glm::mat4 identity_matrix = glm::mat4(1.0f);
    Camera::baseCamera camera{};
    Camera::orthoCamera othroCam{};
    Camera::persCamera persCam{};

    glEnable(GL_DEPTH_TEST);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA);

        glm::mat4 transform_matrix = glm::translate(identity_matrix, translate);
        transform_matrix = glm::scale(transform_matrix, scale);
        transform_matrix = glm::rotate(transform_matrix, thetaX, rotateX);
        transform_matrix = glm::rotate(transform_matrix, thetaY, rotateY);



        camera.InitializeViewMatrix(object.getShaderProgram());
        camera.InitCameraPos(camera.GetCameraPos());
        persCam.InitPersCam(height, width);

        othroCam.InitOrthoCam();

        camera.AssignView(object.getShaderProgram());

        if (persEnabled == true && othroEnabled == false)
        {
            persCam.AssignPersCam(persCam.GetPersMatrix(), object.getShaderProgram());
        }
        else if (othroEnabled == true && persEnabled == false)
        {
            othroCam.AssignOrthoCam(othroCam.GetOrthoMatrix(), object.getShaderProgram());
        }

        //object.SetColor(glm::vec3(0.4f, 0.f, 0.f));
        object.DrawModel(transform_matrix);
        camera.AssignCameraPos(object.getShaderProgram());
        object.DrawFunction();
        thetaX += 0.001f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    object.CleanUp();

    glfwTerminate();
    return 0;
}