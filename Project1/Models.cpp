#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "Models.h"

using namespace Model;


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

Models::Models(std::string sMeshPath, std::string sVertPath, std::string sFragPath)
{
    this->LoadShaders(sVertPath, sFragPath);
    this->LoadModel(sMeshPath);
}

void Models::LoadShaders(std::string sVertPath, std::string sFragPath)
{
    this->shaderProgram = glCreateProgram();

    //Vertex Shader
    std::fstream vertSrc(sVertPath);
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);
    glAttachShader(shaderProgram, vertShader);


    //Fragment Shader
    std::fstream fragSrc(sFragPath);
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);
    glAttachShader(shaderProgram, fragShader);


    glLinkProgram(shaderProgram);
}

void Models::LoadModel(std::string sMeshPath)
{
    std::string path = sMeshPath;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    bool success = tinyobj::LoadObj(
        &this->attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        this->mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    this->TexInit();
    this->VertexInit();
}

void Models::VertexInit()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->VBO_UV);
    glGenBuffers(1, &this->EBO);

    //tells OPENGL that we're working on this VAO
    glBindVertexArray(this->VAO);

    //use shaders
    glUseProgram(this->shaderProgram);

    //Assign a VBO to the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(
        GL_ARRAY_BUFFER,                                //type of buffer
        sizeof(GL_FLOAT) * this->attributes.vertices.size(),  //size in bytes
        &this->attributes.vertices[0],                  //data array
        GL_STATIC_DRAW
    );

    //tell OPENGL what to do with the data
    glVertexAttribPointer(
        0, //position data in the transform
        3, //xyz
        GL_FLOAT, //array data type
        GL_FALSE,
        3 * sizeof(GL_FLOAT),
        (void*)0
    );

    //enable index 0
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * this->mesh_indices.size(),
        this->mesh_indices.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_UV);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GLfloat) * (sizeof(UV) / sizeof(UV[0])),
        &UV[0],
        GL_DYNAMIC_DRAW);

    //Add in to interpret array
    glVertexAttribPointer(
        2, //2 for UV or TEX coords
        2, //UV
        GL_FLOAT, //Type of array
        GL_FALSE,
        2 * sizeof(float), //Every 2 index
        (void*)0
    );

    glEnableVertexAttribArray(2); //Enable 2 for UV / Tex Coords

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void Models::TexInit()
{
    int img_width,
        img_height,
        colorChannels;

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
        0, //Texture 0
        GL_RGBA, //Target color format of texture
        img_width,
        img_height,
        0,
        GL_RGBA, //Color format
        GL_UNSIGNED_BYTE,
        tex_bytes); //Load texture in bytes

    glGenerateMipmap(GL_TEXTURE_2D); //Generate mipmaps

    stbi_image_free(tex_bytes);


}


void Models::SetColor(const glm::vec3& color)
{
    unsigned int colorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));
}

void Models::DrawModel(glm::mat4 transform_matrix, glm::mat4 projection_matrix)
{
    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_matrix));

    //unsigned int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glUniform1i(tex0Address, 0);

    glBindVertexArray(this->VAO);

    glDrawElements(
        GL_TRIANGLES,
        this->mesh_indices.size(),
        GL_UNSIGNED_INT,
        0
    );
}

void Models::CleanUp()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

GLuint Models::getShaderProgram()
{
    return this->shaderProgram;
}