#include "Models.h"

#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
using namespace Models3D;

GLfloat UV[]{
0.f, 1.f,
0.f, 0.f,
1.f, 1.f,
1.f, 0.f,
1.f, 1.f,
1.f, 0.f,
0.f, 1.f,
0.f, 0.f
};

// Function to initiate loading model and shaders in.
ModelObject::ModelObject(std::string meshPath, std::string vertShadePath, std::string fragShadePath)
{
    this->LoadShader(vertShadePath, fragShadePath);
    this->LoadModel(meshPath);
}

// Function to initialize the vertex shader.
void ModelObject::InitializeVert()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->VBO_UV);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glUseProgram(this->shaderProgram);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * this->attributes.vertices.size(),
        &this->attributes.vertices[0],
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GL_FLOAT),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * this->meshIndices.size(),
        this->meshIndices.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_UV);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GLfloat) * (sizeof(UV) / sizeof(UV[0])),
        &UV[0],
        GL_DYNAMIC_DRAW);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Function to initialize the Texture we're using.
void ModelObject::InitializeTex()
{
    int img_width,  // Declaration of some texture values.
        img_height,
        colorChannels;

    stbi_set_flip_vertically_on_load(true);

    stbi_set_unpremultiply_on_load(true);

    unsigned char* tex_bytes =
        stbi_load("3D/ayaya.png",
            &img_width,
            &img_height,
            &colorChannels,
            0);

    glGenTextures(1, &this->texture);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGBA,
        img_width,
        img_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        tex_bytes);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tex_bytes);
}

void ModelObject::AssignColor(const glm::vec3& color)
{
    unsigned int colorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));
}


void ModelObject::RenderModel(glm::mat4 projectionMatrix)
{
    glm::mat4 identity_matrix = glm::mat4(1.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.f);
    glm::mat4 cameraPosMatrix = glm::translate(
        glm::mat4(1.0f),
        cameraPos * -1.0f
    );

    glm::vec3 worldUp = glm::normalize(glm::vec3(0, 1.0f, 0));
    glm::vec3 cameraCenter = glm::vec3(this->x_mod, this->y_mod, 0);

    glm::vec3 F = (cameraCenter - cameraPos);
    F = glm::normalize(F);

    glm::vec3 R = glm::cross(F, worldUp);
    glm::vec3 U = glm::cross(R, F);

    glm::mat4 cameraOrientation = glm::mat4(1.0f);
    
    // Set camera orientation.
    cameraOrientation[0][0] = R.x;
    cameraOrientation[1][0] = R.y;
    cameraOrientation[2][0] = R.z;
    
    cameraOrientation[0][1] = U.x;
    cameraOrientation[1][1] = U.y;
    cameraOrientation[2][1] = U.z;
    
    cameraOrientation[0][2] = -F.x;
    cameraOrientation[1][2] = -F.y;
    cameraOrientation[2][2] = -F.z;

    glm::mat4 viewMatrix = cameraOrientation * cameraPosMatrix;

    glm::mat4 transformationMatrix = glm::translate(identity_matrix, glm::vec3(this->trans_x, this->trans_y, this->trans_z));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(this->scale_x, this->scale_y, this->scale_z));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(this->theta), glm::vec3(this->axis_x, this->axis_y, this->axis_z));

    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");     
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");     
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");  
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");   
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Address, 0);

    glUseProgram(shaderProgram);
    glBindVertexArray(this->VAO);

    glDrawElements(
        GL_TRIANGLES,
        this->meshIndices.size(),
        GL_UNSIGNED_INT,
        0
    );
}

void ModelObject::Clear()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

GLuint ModelObject::getShaderProgram()
{
    return this->shaderProgram;
}

void ModelObject::LoadShader(std::string vertShadePath, std::string fragShadePath)
{
    this->shaderProgram = glCreateProgram();

    std::fstream vertSrc(vertShadePath);
    std::stringstream vertShadeBuff;
    vertShadeBuff << vertSrc.rdbuf();
    std::string vertS = vertShadeBuff.str();
    const char* v = vertS.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);
    glAttachShader(shaderProgram, vertexShader);

    std::fstream fragSrc(fragShadePath);
    std::stringstream fragShadeBuff;
    fragShadeBuff << fragSrc.rdbuf();
    std::string fragS = fragShadeBuff.str();
    const char* f = fragS.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f, NULL);
    glCompileShader(fragmentShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
}

void ModelObject::LoadModel(std::string meshPath)
{
    std::string objPath = meshPath;
    std::vector<tinyobj::shape_t> objShapes;
    std::vector<tinyobj::material_t> objMat;
    std::string warning, error;

    bool success = tinyobj::LoadObj(
        &this->attributes,
        &objShapes,
        &objMat,
        &warning,
        &error,
        objPath.c_str());

    for (size_t i = 0; i < objShapes[0].mesh.indices.size(); i++)
    {
        this->meshIndices.push_back(objShapes[0].mesh.indices[i].vertex_index);
    }

    // Calls these functions next to continue the rendering process.
    this->InitializeTex();
    this->InitializeVert();
}

// MOVEMENT FUNCTIONS //

void ModelObject::MoveRight()
{
    this->trans_x -= 0.3f;
}

void ModelObject::MoveLeft()
{
    this->trans_x += 0.3f;
}

void ModelObject::MoveForward()
{
    this->trans_z += 0.3f;
}

void ModelObject::MoveBack()
{
    this->trans_z -= 0.3f;
}

void ModelObject::LookLeft()
{
    this->x_mod -= 1.00f;
}

void ModelObject::LookRight()
{
    this->x_mod += 1.00f;
}

void ModelObject::LookUp()
{
    this->y_mod += 1.00f;
}

void ModelObject::LookDown()
{
    this->y_mod -= 1.00f;
}