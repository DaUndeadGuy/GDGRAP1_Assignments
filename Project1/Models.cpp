#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "Models.h"

using namespace Model;

/*
  7--------6
 /|       /|
4--------5 |
| |      | |
| 3------|-2
|/       |/
0--------1
*/
//Vertices for the cube
float skyboxVertices[]{
    -1.f, -1.f, 1.f, //0
    1.f, -1.f, 1.f,  //1
    1.f, -1.f, -1.f, //2
    -1.f, -1.f, -1.f,//3
    -1.f, 1.f, 1.f,  //4
    1.f, 1.f, 1.f,   //5
    1.f, 1.f, -1.f,  //6
    -1.f, 1.f, -1.f  //7
};

//Skybox Indices
unsigned int skyboxIndices[]{
    1,2,6,
    6,5,1,

    0,4,7,
    7,3,0,

    4,5,6,
    6,7,4,

    0,3,2,
    2,1,0,

    0,1,5,
    5,4,0,

    3,7,6,
    6,2,3
};

Models::Models(std::string sMeshPath, std::string sVertPath, std::string sFragPath, std::string skyVertPath, std::string skyFragPath)
{
    this->LoadShaders(sVertPath, sFragPath);
    this->LoadSkyboxShaders(skyVertPath, skyFragPath);
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

void Models::LoadSkyboxShaders(std::string sVertPath, std::string sFragPath)
{
    this->skyboxProgram = glCreateProgram();

    //Vertex Shader
    std::fstream vertSrc(sVertPath);
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);
    glAttachShader(skyboxProgram, vertShader);


    //Fragment Shader
    std::fstream fragSrc(sFragPath);
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    glAttachShader(skyboxProgram, fragShader);


    glLinkProgram(skyboxProgram);
}

void Models::LoadModel(std::string sMeshPath)
{
    std::string path = sMeshPath;
    std::string path2 = "3D/djSword_o.obj";
    std::vector<tinyobj::shape_t> shapes, shapes2;
    std::vector<tinyobj::material_t> material, material2;
    std::string warning, error;
    bool success = tinyobj::LoadObj(
        &this->attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    bool success2 = tinyobj::LoadObj(
        &this->attributes,
        &shapes2,
        &material2,
        &warning,
        &error,
        path2.c_str());



    for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        this->mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        this->mesh_indices.push_back(shapes2[0].mesh.indices[i].vertex_index);

    }

    for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        vData = shapes[0].mesh.indices[i];
        vData2 = shapes2[0].mesh.indices[i];
        float x = this->attributes.vertices[vData.vertex_index * 3];
        float y = this->attributes.vertices[vData.vertex_index * 3 + 1];
        float z = this->attributes.vertices[vData.vertex_index * 3 + 2];

        //X
        this->fullVertexData.push_back(
            this->attributes.vertices[vData.vertex_index * 3]
        );

        ////Y
        this->fullVertexData.push_back(
            this->attributes.vertices[vData.vertex_index * 3 + 1]
        );

        ////Z
        this->fullVertexData.push_back(
            this->attributes.vertices[vData.vertex_index * 3 + 2]
        );

    	////X
     //   this->fullVertexData.push_back(
     //       this->attributes.colors[vData.vertex_index * 3]
     //   );

     //   ////Y
     //   this->fullVertexData.push_back(
     //       this->attributes.colors[vData.vertex_index * 3 + 1]
     //   );

     //   ////Z
     //   this->fullVertexData.push_back(
     //       this->attributes.colors[vData.vertex_index * 3 + 2]
     //   );

        //Normals (XYZ)

        //X
        this->fullVertexData.push_back(
            this->attributes.normals[vData.normal_index * 3]
        );

        //Y
        this->fullVertexData.push_back(
            this->attributes.normals[vData.normal_index * 3 + 1]
        );

        //Z
        this->fullVertexData.push_back(
            this->attributes.normals[vData.normal_index * 3 + 2]
        );

        /*Texcoords - There's two implementations included. One is planar mapping and one is
			loading the texcoords from a different model and using it into the file*/

        //U - UV from djSword_o.obj

        this->fullVertexData.push_back(
            this->attributes.texcoords[vData2.texcoord_index * 2]
        );

        //V

        this->fullVertexData.push_back(
            this->attributes.texcoords[vData2.texcoord_index * 2 + 1]
        );

        //this->fullVertexData.push_back(x * 0.5f); // U Planar Mapping
        //this->fullVertexData.push_back(y * 0.1f); // V
    }

    this->TexInit();
    this->VertexInit();
}

void Models::VertexInit()
{

    glGenVertexArrays(1, &this->skyboxVAO);
    glGenBuffers(1, &this->skyboxVBO);
    glGenBuffers(1, &this->skyboxEBO);

    glBindVertexArray(this->skyboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    //glGenBuffers(1, &this->VBO_UV);
    //glGenBuffers(1, &this->EBO);

    //tells OPENGL that we're working on this VAO
    glBindVertexArray(this->VAO);

    //use shaders
    glUseProgram(this->shaderProgram);

    //Assign a VBO to the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO); 

    glBufferData(
        GL_ARRAY_BUFFER,                                //type of buffer
        sizeof(GL_FLOAT) * this->fullVertexData.size(),  //size in bytes
        this->fullVertexData.data(),                  //data array
        GL_STATIC_DRAW
    );

    //tell OPENGL what to do with the data
    glVertexAttribPointer(
        0, //position data in the transform
        3, //xyz
        GL_FLOAT, //array data type
        GL_FALSE,
        //XYZ UV
        8 * sizeof(GL_FLOAT),
        (void*)0
    );

    GLintptr normalPtr = 3 * sizeof(float);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)normalPtr
    );

    //XYZ UV
    //012 3
    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GL_FLOAT),
        (void*)uvPtr
    );

    //enable index 0

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //    sizeof(GLuint) * this->mesh_indices.size(),
    //    this->mesh_indices.data(),
    //    GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, this->VBO_UV);
    //glBufferData(GL_ARRAY_BUFFER,
    //    sizeof(GLfloat) * (sizeof(UV) / sizeof(UV[0])),
    //    &UV[0],
    //    GL_DYNAMIC_DRAW);

    ////Add in to interpret array
    //glVertexAttribPointer(
    //    2, //2 for UV or TEX coords
    //    2, //UV
    //    GL_FLOAT, //Type of array
    //    GL_FALSE,
    //    2 * sizeof(float), //Every 2 index
    //    (void*)0
    //);


    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2); //Enable 2 for UV / Tex Coords

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


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

    std::string facesSkybox[]
    {
        "Skybox/rainbow_rt.png",
        "Skybox/rainbow_lf.png",
        "Skybox/rainbow_up.png",
        "Skybox/rainbow_dn.png",
        "Skybox/rainbow_ft.png",
        "Skybox/rainbow_bk.png"
    };

    glGenTextures(1, &this->skyboxTex);
    glGenTextures(1, &this->texture);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int w, h, skyCChanel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(
            facesSkybox[i].c_str(),
            &w,
            &h,
            &skyCChanel,
            0
        );

        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                w,
                h,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }

        stbi_image_free(data);
    }

    stbi_set_flip_vertically_on_load(true);


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

void Models::DrawModel(glm::mat4 transform_matrix, glm::mat4 projection_matrix, glm::mat4 view_matrix, glm::vec3 cameraPos)
{
    glm::vec3 lightPos = glm::vec3(-10, 3, 4);
    glm::vec3 lightColor = glm::vec3(1, 1, 1);

    float ambientStr = 0.5f;
    glm::vec3 ambientColor = lightColor;

    float specStr = 0.5f;
    float specPhong = 16;


    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    glUseProgram(this->skyboxProgram);
    glm::mat4 sky_view = glm::mat4(1.0f);
    sky_view = glm::mat4(

        glm::mat3(view_matrix)
    );

    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_matrix));

    unsigned int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    unsigned int skyProjectionLoc = glGetUniformLocation(this->skyboxProgram, "projection");
    glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    unsigned int skyViewLoc = glGetUniformLocation(this->skyboxProgram, "view");
    glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

    glBindVertexArray(this->skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTex);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glUseProgram(this->shaderProgram);


    GLuint tex0Address = glGetUniformLocation(shaderProgram, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture);

    GLuint lightAddress = glGetUniformLocation(shaderProgram, "lightPos");
    glUniform3fv(lightAddress, 1, glm::value_ptr(lightPos));
    
    GLuint lightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
    glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

    GLuint ambientStrAddress = glGetUniformLocation(shaderProgram, "ambientStr");
    glUniform1f(ambientStrAddress, ambientStr);

    GLuint ambientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
    glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambientColor));

    GLuint cameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPos));

    GLuint specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
    glUniform1f(specStrAddress, specStr);

    GLuint specPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
    glUniform1f(specPhongAddress, specPhong);

    glUniform1i(tex0Address, 0);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->fullVertexData.size() / 8);


    //glDrawElements(
    //    GL_TRIANGLES,
    //    this->mesh_indices.size(),
    //    GL_UNSIGNED_INT,
    //    0
    //);
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