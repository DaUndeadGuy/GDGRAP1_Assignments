#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "Models.h"

bool movingRight, movingLeft, movingForward, movingBack;
bool lookingRight, lookingLeft, lookingUp, lookingDown;
bool spawning;

// Function for registering keyboard inputs.
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        movingRight = true;
    }
    else if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        movingLeft = true;
    }
    else if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        movingForward = true;
    }
    else if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
        movingBack = true;
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
        lookingLeft = true;
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
        lookingRight = true;
    }
    else if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
        lookingUp = true;
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
        lookingDown = true;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        spawning = true;
    }
}

int main(void)
{
    GLFWwindow* window;
    float width = 600.0f;
    float height = 600.0f;

    glm::mat4 identity_matrix = glm::mat4(1.0f);

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

    std::vector<Model::Models> models;

    Model::Models startObject("3D/myCube.obj", "Shaders/sample.vert", "Shaders/sample.frag");
    models.push_back(startObject);

    glfwSetKeyCallback(window, Key_Callback);

    glViewport(0,                      //min x
        0,                      //min y
        (GLsizei)width,         //max x
        (GLsizei)height);       //max y

    glm::mat4 projection_matrix = glm::perspective(glm::radians(60.0f),
        height / width,
        0.1f,
        100.0f);


    glEnable(GL_DEPTH_TEST);

    //Timer for spawning.
    int sentinel = 300;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // MOVEMENT FUNCTIONS //
        // Calls functions to alter individual model values for linear transformation.
        if (movingRight) {
            for (int i = 0; i < models.size(); i++) {
                models[i].MoveRight();
                movingRight = false;
            }
        }
        if (movingLeft) {
            for (int i = 0; i < models.size(); i++) {
                models[i].MoveLeft();
                movingLeft = false;
            }
        }
        if (movingForward) {
            for (int i = 0; i < models.size(); i++) {
                models[i].MoveForward();
                movingForward = false;
            }
        }
        if (movingBack) {
            for (int i = 0; i < models.size(); i++) {
                models[i].MoveBack();
                movingBack = false;
            }
        }

        if (lookingRight) {
            for (int i = 0; i < models.size(); i++) {
                models[i].LookRight();
                lookingRight = false;
            }
        }
        if (lookingLeft) {
            for (int i = 0; i < models.size(); i++) {
                models[i].LookLeft();
                lookingLeft = false;
            }
        }
        if (lookingUp) {
            for (int i = 0; i < models.size(); i++) {
                models[i].LookUp();
                lookingUp = false;
            }
        }
        if (lookingDown) {
            for (int i = 0; i < models.size(); i++) {
                models[i].LookDown();
                lookingDown = false;
            }
        }

        if (spawning && sentinel >= 300) {
            Model::Models* newModel = new Model::Models("3D/myCube.obj", "Shaders/sample.vert", "Shaders/sample.frag");
            models.push_back(*newModel);

            sentinel = 0;
            spawning = false;
        }
        else
            spawning = false;

        // spawning cooldown
        if (sentinel < 300) {
            sentinel++;
        }

        startObject.DrawModel(projection_matrix);

        //Renders all models inside the models vector
        for (int i = 0; i < models.size(); i++)
            models[i].DrawModel(projection_matrix);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    for (int i = 0; i < models.size(); i++)
    {
        models[i].CleanUp();
    }

    glfwTerminate();
    return 0;
}