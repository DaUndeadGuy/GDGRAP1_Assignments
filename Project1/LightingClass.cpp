#include "LightingClass.h"

Light::baseLight::baseLight() {

}

void Light::baseLight::AssignAmbientColor(GLuint shaderProgram) {
	GLuint ambientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
	glUniform3fv(ambientColorAddress, 1, glm::value_ptr(this->ambientColor));
}

void Light::baseLight::AssignAmbientStr(GLuint shaderProgram) {
	GLuint ambientStrAddress = glGetUniformLocation(shaderProgram, "ambientStr");
	glUniform1f(ambientStrAddress, this->ambientStr);
}

void Light::baseLight::AssignLightColor(GLuint shaderProgram) {
	GLuint lightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
	glUniform3fv(lightColorAddress, 1, glm::value_ptr(this->lightColor));

}

void Light::pointLight::AssignLightPos(GLuint shaderProgram) {
	GLuint lightAddress = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3fv(lightAddress, 1, glm::value_ptr(this->lightPos));
}

void Light::baseLight::AssignSpecPhong(GLuint shaderProgram) {
	GLuint specPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
	glUniform1f(specPhongAddress, this->specPhong);
}

void Light::baseLight::AssignSpecStr(GLuint shaderProgram) {
	GLuint specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
	glUniform1f(specStrAddress, this->specStr);
}

void Light::baseLight::InitBaseLight(glm::vec3 lightCol, float ambientStrength, float specStrong, float specPh) {

	this->lightColor = lightCol;
	this->ambientStr = ambientStrength;
	this->ambientColor = this->lightColor;
	this->specStr = specStrong;
	this->specPhong = specPh;
}

void Light::pointLight::InsertLightPos(glm::vec3 lightPosition) {
	this->lightPos = lightPosition;
}

void Light::directLight::AssignDirectionalPos(GLuint shaderProgram) {
	GLuint lightAddress = glGetUniformLocation(shaderProgram, "lightDirection");
	glUniform3fv(lightAddress, 1, glm::value_ptr(this->DirectionalPos));
}

void Light::directLight::InsertDirectionalPos(glm::vec3 directionalPosition) {
	this->DirectionalPos = directionalPosition;
}

void Light::pointLight::ChangeColor(glm::vec3 color) {
	this->lightColor = color;
}

void Light::pointLight::MoveRight()
{
	this->lightPos.x -= 0.2f;
}

void Light::pointLight::MoveLeft()
{
	this->lightPos.x += 0.2f;
}

void Light::pointLight::MoveForward()
{
	this->lightPos.z += 0.2f;
}

void Light::pointLight::MoveBack()
{
	this->lightPos.z -= 0.2f;
}

void Light::pointLight::MoveUp()
{
	this->lightPos.y += 0.2f;
}

void Light::pointLight::MoveDown()
{
	this->lightPos.y -= 0.3f;
}

void Light::pointLight::IntensityUp() {
	this->ambientStr += 0.1f;
	this->specStr += 0.1f;
}

void Light::pointLight::IntensityDown() {
	this->ambientStr -= 0.1f;
	this->specStr -= 0.1f;
}

void Light::directLight::IntensityUp() {
	this->ambientStr += 0.1f;
	this->specStr += 0.1f;
}

void Light::directLight::IntensityDown() {
	this->ambientStr -= 0.1f;
	this->specStr -= 0.1f;
}