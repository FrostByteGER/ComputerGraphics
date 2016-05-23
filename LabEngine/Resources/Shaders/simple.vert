#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main( void )
{
 gl_Position =  cameraToView * worldToCamera * modelToWorld * vec4(vertexPosition_modelspace, 1.0);
}
