#include "CameraClass.h"

using namespace Camera;

baseCamera::baseCamera() {

}

void baseCamera::InitCameraPos(glm::vec3 camPosition) {
    this->cameraPos = camPosition;
}

void baseCamera::InitializeViewMatrix(GLuint shaderProgram) {

    glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1.0f, 0));
    glm::vec3 cameraCenter = glm::vec3(x_mod, y_mod, 0);

    glm::vec3 F = (cameraCenter - cameraPos);
    F = glm::normalize(F);

    glm::vec3 R = glm::cross(F, worldUp);
    glm::vec3 U = glm::cross(R, F);

    glm::mat4 cameraOrientation = glm::mat4(1.0f);

    // Matrix[C][R]
    //R
    cameraOrientation[0][0] = R.x;
    cameraOrientation[1][0] = R.y;
    cameraOrientation[2][0] = R.z;
    //U
    cameraOrientation[0][1] = U.x;
    cameraOrientation[1][1] = U.y;
    cameraOrientation[2][1] = U.z;
    //-F
    cameraOrientation[0][2] = -F.x;
    cameraOrientation[1][2] = -F.y;
    cameraOrientation[2][2] = -F.z;

    glm::mat4 tempMatrix = cameraOrientation * cameraPosMatrix;

    this->viewMatrix = tempMatrix;
}

void baseCamera::AssignView(GLuint shaderProgram) {
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->viewMatrix));
}

glm::mat4 baseCamera::GetViewMatrix() {
    return this->viewMatrix;
}

glm::vec3 baseCamera::GetCameraPos() {
    return this->cameraPos;
}

void baseCamera::AssignCameraPos(GLuint shaderProgram) {
    GLuint cameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(cameraPosAddress, 1, glm::value_ptr(this->cameraPos));
}

void persCamera::InitPersCam(float windowHeight, float windowWidth) {

    this->perspectiveCamera = glm::perspective(glm::radians(60.0f),  // FOV
                                               windowHeight / windowWidth,   // Aspect Ratio
                                               0.1f,   // Near
                                               100.0f);    // Far
}

void persCamera::AssignPersCam(glm::mat4 projectionMatrix, GLuint shaderProgram) {

    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, //Addess of transform variable
        1,                           // how many matrices to assign
        GL_FALSE,
        value_ptr(projectionMatrix));
}

glm::mat4 persCamera::GetPersMatrix() {
    return this->perspectiveCamera;
}

void orthoCamera::InitOrthoCam() {
    this->orthographicMatrix = glm::ortho(-7.f,    // left most point
                                          7.f,    // right most point
                                          -7.f,    // bottom most point
                                          7.f,    // top most point
                                          -7.0f,   // nearest point
                                          50.0f);  // farthest point
}

void orthoCamera::AssignOrthoCam(glm::mat4 orthographicMatrix, GLuint shaderProgram) {

    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, //Addess of transform variable
        1,                           // how many matrices to assign
        GL_FALSE,
        value_ptr(orthographicMatrix));
}

glm::mat4 orthoCamera::GetOrthoMatrix() {
    return this->orthographicMatrix;
}