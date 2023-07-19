#version 330 core 

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
out vec2 texCoord;

//Lighting Variables
out vec3 normCoord; //Pass the Processed normals to the fragment shader later
out vec3 fragPos; //Pass the position of the vertex to the fragment shader later


void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0);

    normCoord = mat3(//Get the Normal Matrix and convert it to a 3x3 matrix
                        transpose(inverse(transform))
                        ) * vertexNormal; //Apply the normal matrix to the normal data

    fragPos = vec3(transform * vec4(aPos,1.0));

    texCoord = aTex;
}