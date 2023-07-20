//#define TINYOBJLOADER_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#include "Skybox.h"
//
//using namespace Sky;
//
///*
//  7--------6
// /|       /|
//4--------5 |
//| |      | |
//| 3------|-2
//|/       |/
//0--------1
//*/
////Vertices for the cube
//float skyboxVertices[]{
//    -1.f, -1.f, 1.f, //0
//    1.f, -1.f, 1.f,  //1
//    1.f, -1.f, -1.f, //2
//    -1.f, -1.f, -1.f,//3
//    -1.f, 1.f, 1.f,  //4
//    1.f, 1.f, 1.f,   //5
//    1.f, 1.f, -1.f,  //6
//    -1.f, 1.f, -1.f  //7
//};
//
////Skybox Indices
//unsigned int skyboxIndices[]{
//    1,2,6,
//    6,5,1,
//
//    0,4,7,
//    7,3,0,
//
//    4,5,6,
//    6,7,4,
//
//    0,3,2,
//    2,1,0,
//
//    0,1,5,
//    5,4,0,
//
//    3,7,6,
//    6,2,3
//};
//
//Skybox::Skybox(std::string skyVertPath, std::string skyFragPath)
//{
//    this->LoadSkyboxShaders(skyVertPath, skyFragPath);
//}
//
//void Skybox::LoadSkyboxShaders(std::string sVertPath, std::string sFragPath)
//{
//    this->skyboxProgram = glCreateProgram();
//
//    //Vertex Shader
//    std::fstream vertSrc(sVertPath);
//    std::stringstream vertBuff;
//    vertBuff << vertSrc.rdbuf();
//    std::string vertS = vertBuff.str();
//    const char* v = vertS.c_str();
//
//    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertShader, 1, &v, NULL);
//    glCompileShader(vertShader);
//    glAttachShader(skyboxProgram, vertShader);
//
//
//    //Fragment Shader
//    std::fstream fragSrc(sFragPath);
//    std::stringstream fragBuff;
//    fragBuff << fragSrc.rdbuf();
//    std::string fragS = fragBuff.str();
//    const char* f = fragS.c_str();
//
//    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragShader, 1, &f, NULL);
//    glCompileShader(fragShader);
//
//    glAttachShader(skyboxProgram, fragShader);
//
//
//    glLinkProgram(skyboxProgram);
//}
//
//void Skybox::SkyboxVert()
//{
//    glGenVertexArrays(1, &this->skyboxVAO);
//    glGenBuffers(1, &this->skyboxVBO);
//    glGenBuffers(1, &this->skyboxEBO);
//
//    glBindVertexArray(this->skyboxVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->skyboxEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//}
//
//void Skybox::SkyboxTex()
//{
//    std::string facesSkybox[]
//    {
//        "Skybox/rainbow_rt.png",
//        "Skybox/rainbow_lf.png",
//        "Skybox/rainbow_up.png",
//        "Skybox/rainbow_dn.png",
//        "Skybox/rainbow_ft.png",
//        "Skybox/rainbow_bk.png"
//    };
//
//    glGenTextures(1, &this->skyboxTex);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTex);
//
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//
//    for (unsigned int i = 0; i < 6; i++)
//    {
//        int w, h, skyCChanel;
//        stbi_set_flip_vertically_on_load(false);
//
//        unsigned char* data = stbi_load(
//            facesSkybox[i].c_str(),
//            &w,
//            &h,
//            &skyCChanel,
//            0
//        );
//
//        if (data)
//        {
//            glTexImage2D(
//                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//                0,
//                GL_RGB,
//                w,
//                h,
//                0,
//                GL_RGB,
//                GL_UNSIGNED_BYTE,
//                data
//            );
//        }
//
//        stbi_image_free(data);
//    }
//
//    stbi_set_flip_vertically_on_load(true);
//}
//
//void Skybox::DrawSkybox(glm::mat4 view_matrix, glm::mat4 projection_matrix)
//{
//    glDepthMask(GL_FALSE);
//    glDepthFunc(GL_LEQUAL);
//
//    glUseProgram(this->skyboxProgram);
//    glm::mat4 sky_view = glm::mat4(1.0f);
//    sky_view = glm::mat4(
//
//        glm::mat3(view_matrix)
//    );
//
//    unsigned int skyProjectionLoc = glGetUniformLocation(this->skyboxProgram, "projection");
//    glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
//
//    unsigned int skyViewLoc = glGetUniformLocation(this->skyboxProgram, "view");
//    glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));
//
//    glBindVertexArray(this->skyboxVAO);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyboxTex);
//
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//    glDepthMask(GL_TRUE);
//    glDepthFunc(GL_LESS);
//}
//
