#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION

#include "Models.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Models3D;

bool movingRight, movingLeft, movingForward, movingBack;
bool lookingRight, lookingLeft, lookingUp, lookingDown;
bool spawning;

void Key_CallBack(GLFWwindow* window, int key, int scancode, int action, int mod)
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
    // Declare variables for window dimensions.
    float window_height = 600.0f;
    float window_width = 600.0f;

    GLFWwindow* window;
    float i = 0;

    if (!glfwInit())
        return -1;

    //Make the window.
    window = glfwCreateWindow(600, 600, "Jose Romulo Guzman", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    vector<ModelObject> models;

    ModelObject startingObj("3D/myCube.obj", "Shaders/sample.vert", "Shaders/sample.frag");
    models.push_back(startingObj);

    glViewport(0,  
        0,      
        600,   
        600); 
    
    glfwSetKeyCallback(window, Key_CallBack);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f),
        window_height / window_width,
        0.1f,
        100.0f);

    glEnable(GL_DEPTH_TEST);
    
    //Timer for spawning.
    int sentinel = 300;

    //The main loop.
    while (!glfwWindowShouldClose(window))
    {
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
            ModelObject* spawnedModel = new ModelObject("3D/myCube.obj", "Shaders/sample.vert", "Shaders/sample.frag");
            models.push_back(*spawnedModel);

            sentinel = 0;
            spawning = false;
        }
        else
            spawning = false;

        if (sentinel < 300) {
            sentinel++;
        }
        
        for (int i = 0; i < models.size(); i++)
            models[i].RenderModel(projectionMatrix);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    for (int i = 0; i < models.size(); i++)
        models[i].Clear();

    glfwTerminate();
    return 0;
}