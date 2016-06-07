#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main( void )
{
    gl_Position =  cameraToView * worldToCamera * modelToWorld * vec4(vertexPosition_modelspace, 1.0);
    TexCoords = texCoords;
}
