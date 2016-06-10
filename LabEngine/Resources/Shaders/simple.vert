#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

// Modelmatrix
uniform mat4 modelToWorld;
// Worldmatrix
uniform mat4 worldToCamera;
// Viewmatrix
uniform mat4 cameraToView;

void main( void )
{
    gl_Position =  cameraToView * worldToCamera * modelToWorld * vec4(vertexPosition_modelspace, 1.0);
    FragPos = vec3(modelToWorld * vec4(vertexPosition_modelspace, 1.0));
    Normal = mat3(modelToWorld) * normal;
    TexCoords = texCoords;
}
