#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

in vec3 lightPosition;
out vec3 LightPosition;

// Modelmatrix
uniform mat4 modelToWorld;
// Viewmatrix
uniform mat4 worldToCamera;
// Projectionmatrix
uniform mat4 cameraToProjection;

void main( void )
{
    gl_Position =  cameraToProjection * worldToCamera * modelToWorld * vec4(vertexPosition_modelspace, 1.0);
    FragPos = vec3(worldToCamera * modelToWorld * vec4(vertexPosition_modelspace, 1.0));
    Normal = mat3(worldToCamera * modelToWorld) * normal;
    LightPosition = vec3(worldToCamera * vec4(lightPosition, 1.0));
    TexCoords = texCoords;
}
