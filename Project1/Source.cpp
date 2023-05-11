#include <GLFW/glfw3.h>
#include <cmath>
#define M_PI 3.14159265359

void renderPenta(float centerX, float centerY, float sideLength)
{
    const float angleOffset = M_PI / 2.0; // Offset the angle to start from the top vertex
    const float angleIncrement = 2.0 * M_PI / 5.0; // Angle increment for each vertex
    const float radius = sideLength / (2.0 * sin(M_PI / 5.0)); // Calculate the radius of the circumscribed circle

    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        float angle = angleOffset + i * angleIncrement;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Jose Romulo Guzman", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        float centerX = 0.0f; // X-coordinate of the center point
        float centerY = 0.0f; // Y-coordinate of the center point
        float sideLength = 1.f; // Length of each side of the pentagon
        renderPenta(centerX, centerY, sideLength);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }





    glfwTerminate();
    return 0;
}
